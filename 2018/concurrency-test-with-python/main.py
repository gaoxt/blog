# 使用 gevent 可以遇到阻塞自动切换协程
# from gevent import monkey;monkey.patch_all()

import requests
from bs4 import BeautifulSoup
from multiprocessing import Process, Pool, Manager
from threading import Thread
import gevent
from user_agent import generate_user_agent
from multiprocessing import Queue
# gevent 和 异步 的方式使用的Queue ，测试请注释上面的 Queue
# from gevent.queue import Queue
import asyncio
import aiohttp
import os
import time
import random
import cProfile

proxies = {
    'http': 'http://119.101.117.148:9999',
    'https': 'https://121.63.199.133:9999'
}
proxy = 'http://119.101.114.239:9999'

headers = {
    'User-Agent': generate_user_agent(),
}
# 请求数量
max_page = 10

# 分片处理的最大数量
cut_count = 5

# 进程数量，请求数低于分片数则是单进程
process_count = 1 if int(
    max_page / cut_count) == 0 else int(
    max_page / cut_count)
url = "https://www.baidu.com/s?wd="
url_list = [url + str(i + 1) for i in range(0, max_page)]

process_data = [url_list[i:i + cut_count]
                for i in range(0, len(url_list), cut_count)]


def get_page_data(url):
    return url
    response = requests.get(url, headers)
    soup = BeautifulSoup(response.text, 'html.parser')
    return soup.select("#content_left .c-container h3")[0].get_text().strip()


def get_multi_page_data(q, urls):
    for url in urls:
        title = get_page_data(url)
        q.put({url: title})


def test_process():
    manager = Manager()
    q = manager.Queue()

    process_list = []
    for i in range(0, process_count):
        p = Process(target=get_multi_page_data, args=(q, process_data[i]))
        p.start()
        process_list.append(p)

    for i in process_list:
        i.join()

    print('total:%d process_num:%d' % (q.qsize(), process_count))
    while not q.empty():
        print(q.get())


def test_pool_process():
    # 子进程共享里的Queue不能直接创建，需要从Manager获得
    manager = Manager()
    q = manager.Queue()

    p = Pool(process_count)
    for i in range(0, process_count):
        p.apply_async(get_multi_page_data, args=(q, process_data[i]))
    p.close()
    p.join()
    print('total:%d process_num:%d' % (q.qsize(), process_count))
    while not q.empty():
        print(q.get())


def test_thread():
    q = Queue()

    thread_list = []

    for i in range(0, process_count):
        t = Thread(target=get_multi_page_data, args=(q, process_data[i]))
        t.start()
        thread_list.append(t)

    for i in thread_list:
        i.join()

    data = {}
    while not q.empty():
        data = {**data, **q.get()}
    print('total:%d  process_num:%d' % (len(data), process_count))
    print(data)


def test_coroutine():
    q = Queue()
    c = coroutine_consumer(q)
    coroutine_produce(c)

    print('total: %d' % q.qsize())
    while not q.empty():
        print(q.get())


def coroutine_consumer(q):
    while 1:
        title = yield get_page_data
        q.put(title)


def coroutine_produce(c):
    a = c.send(None)
    for i in range(0, process_count):
        [c.send(a(j)) for j in process_data[i]]
    c.close()


def test_coroutine_process():
    manager = Manager()
    q = manager.Queue()

    p = Pool(process_count)
    for i in range(0, process_count):
        p.apply_async(coroutine_process_func, args=(q, process_data[i]))
    p.close()
    p.join()

    print('total: %d' % q.qsize())
    while not q.empty():
        print(q.get())


def coroutine_process_func(q, data):
    c = coroutine_consumer(q)
    coroutine_process_produce(c, data)


def coroutine_process_produce(c, data):
    a = c.send(None)
    [c.send(a(i)) for i in data]
    c.close()


def test_gevent():
    q = Queue()
    gevent.joinall([gevent.spawn(test_gevent_get_page, q, url)
                    for url in url_list])
    print('total: %d' % q.qsize())
    while not q.empty():
        print(q.get())


def test_gevent_get_page(q, url):
    return q.put(url)
    response = requests.get(url, headers=headers)
    soup = BeautifulSoup(response.text, 'html.parser')
    q.put(soup.select("#content_left .c-container h3")
          [0].get_text().strip())


def test_asyncio():
    q = Queue()
    loop = asyncio.get_event_loop()
    loop.run_until_complete(asyncio.wait(
        [asyncio_get_page_data(q, url) for url in url_list]))
    loop.close()
    print('total: %d' % q.qsize())
    while not q.empty():
        print(q.get())


async def asyncio_get_page_data(q, url):
    q.put(url)
    # async with aiohttp.ClientSession(headers=headers) as session:
    #     async with session.get(url, proxy=proxy) as response:
    #         html = await response.text()
    #         soup = BeautifulSoup(html, 'html.parser')
    #         q.put(soup.select("#content_left .c-container h3")
    #               [0].get_text().strip())


def test_process_asyncio():
    manager = Manager()
    q = manager.Queue()
    p = Pool(process_count)
    for i in range(0, process_count):
        p.apply_async(test_process_asyncio_loop, args=(q, process_data[i]))
    p.close()
    p.join()

    print('total: %d' % q.qsize())
    while not q.empty():
        print(q.get())


def test_process_asyncio_loop(q, data, loop=None):
    if not loop:
        loop = asyncio.get_event_loop()
    loop.run_until_complete(asyncio.wait(
        [asyncio_get_page_data(q, url) for url in data]))
    loop.close()


def test_thread_asyncio():
    q = Queue()
    thread_list = []
    for i in range(0, process_count):
        loop = asyncio.new_event_loop()
        asyncio.set_event_loop(loop)
        t = Thread(target=test_process_asyncio_loop,
                   args=(q, process_data[i], loop))
        t.start()
        thread_list.append(t)

    for i in thread_list:
        i.join()

    print('total: %d' % q.qsize())
    while not q.empty():
        print(q.get())


if __name__ == '__main__':
    p = cProfile.Profile()

    # 多进程
    test_process()

    # 多进程池
    # test_pool_process()

    # 多线程
    # test_thread()

    # 协程
    # test_coroutine()

    # 协程，gevent方式
    # test_gevent()

    # 多进程+协程
    # test_coroutine_process()

    # 异步io
    # test_asyncio()

    # 多进程+异步io
    # test_process_asyncio()

    # 多线程+异步io
    # test_thread_asyncio()

    p.disable()
    p.print_stats(sort='tottime')
