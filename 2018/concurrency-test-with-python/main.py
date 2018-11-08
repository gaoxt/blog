import requests
from bs4 import BeautifulSoup
from multiprocessing import Process, Queue, Pool, Manager

max_page = 10
cut_count = 5
process_count = int(max_page / cut_count)
url = "https://www.baidu.com/s?wd="
url_list = [url + str(i + 1) for i in range(0, max_page)]

process_data = [url_list[i:i + cut_count]
                for i in range(0, len(url_list), cut_count)]


def get_page_data(url):
    # return url
    response = requests.get(url, headers={
                            'User-Agent': "Mozilla/5.0 (compatible; MSIE 8.0; Windows NT 6.2; Trident/4.0)"})
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

    print('total: %d' % q.qsize())
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

    print('total: %d' % q.qsize())
    while not q.empty():
        print(q.get())


if __name__ == '__main__':
    # test_process()
    test_pool_process()
