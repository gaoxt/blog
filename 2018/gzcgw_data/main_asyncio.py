# -*- coding: utf-8 -*-

from user_agent import generate_user_agent
import requests
from bs4 import BeautifulSoup
from dateutil.parser import parse
from pymongo import MongoClient
import re
import html
import hashlib
import asyncio
import aiohttp
from multiprocessing import Process, Queue, Pool, Manager

proxy = 'http://119.101.112.9:9999'
aio_proxy = 'http://119.101.112.63:9999'
proxies = {
    'http': proxy
}

proxies_list = [
    {'http': 'http://119.101.113.202:9999'},
    {'http': 'http://119.101.117.21:9999'},
    {'http': 'http://119.101.112.23:9999'},
    {'http': 'http://119.101.116.226:9999'},
    {'http': 'http://119.101.115.168:9999'},
    {'http': 'http://119.101.112.9:9999'},
    {'http': 'http://119.101.113.200:9999'},
    {'http': 'http://119.101.114.248:9999'}
]

ua = generate_user_agent()
headers = {
    'User-Agent': ua
}

data = {
    # 'zxjy': 'http://www.gzcgw.gov.cn/portal/site/site/portal/zmhd/zxjy.portal',
    'wtts': 'http://www.gzcgw.gov.cn/portal/site/site/portal/zmhd/wtts.portal',
    'jzxx': 'http://www.gzcgw.gov.cn/portal/site/site/portal/zmhd/jzxx.portal'
}


conn = MongoClient('127.0.0.1', 27017)
collection = conn.gz_data.all_content


def md5(arg, code='utf-8'):
    md5_pwd = hashlib.md5(bytes('gz', encoding=code))
    md5_pwd.update(bytes(arg, encoding=code))
    return md5_pwd.hexdigest()


def filter_data(_type, data):
    if _type == 'zxjy':
        del data[1]
        del data[3]

    elif _type == 'wtts':
        del data[3]

    elif _type == 'jzxx':
        return data
    return data


def filter_content(_type, data):
    if _type == 'zxjy':
        del data[3]

    elif _type == 'wtts':
        return data

    elif _type == 'jzxx':
        return data

    return data


def format_item_info(key, item_soup):
    contents = item_soup.find_all(class_="main-table-td02")
    contents = filter_content(key, contents)
    data['content'] = contents[3].get_text().replace(u'\xa0', u' ')
    data['reply'] = contents[4].get_text().replace(u'\xa0', u' ')
    return data


def format_data(data):
    course = {
        'content_md5': data.get('content_md5'),
        'title': data.get('title'),
        'type': data.get('type'),
        'question_type': data.get('question_type'),
        'people': data.get('people'),
        'content': data.get('content'),
        'reply': data.get('reply'),
        'reply_time': parse(data.get('reply_time')),
        'create_time': parse(data.get('create_time'))
    }
    return course


def get_page_data(url):
    response = requests.get(url, headers=headers, proxies=proxies)
    response.encoding = 'utf-8'
    soup = BeautifulSoup(response.text, 'html.parser')
    return soup


pattern = '<a.href="([^"]*)"[^>]*>(.*)</a>'
pattern_page = '<font.*[^>]*(.*)</font>'
page = 12
page_end = 1


def format_page_info(key, el):
    data = {}
    txt = html.unescape(str(el))
    arr = re.finditer(pattern, txt)
    href = texts = ''
    for match in arr:
        href = match.group(1)
        texts += match.group(2) + '\n'
    texts_arr = texts.split()
    texts_arr = filter_data(key, texts_arr)
    data['question_type'] = texts_arr[0]
    data['title'] = texts_arr[1]
    data['people'] = texts_arr[2]
    data['reply_time'] = texts_arr[3]
    data['create_time'] = texts_arr[4]
    data['type'] = key
    url = 'http://www.gzcgw.gov.cn%s' % href
    return url, texts_arr, data


async def as_get_content(q, url, key):
    # timeout = aiohttp.ClientTimeout(total=30)
    async with aiohttp.ClientSession(headers=headers) as session:
        async with session.get(url, proxy=proxy) as response:
            content = await response.text()
            soup = BeautifulSoup(content, 'html.parser')
            contents = soup.find_all(class_="main-table-td02")
            contents = filter_content(key, contents)
            data = {}
            data['content'] = contents[3].get_text().replace(u'\xa0', u' ')
            data['reply'] = contents[4].get_text().replace(u'\xa0', u' ')
            q.put([url, data])


def process_main_func(q, key, el):
    item_url, texts_arr, content_data = format_page_info(key, el)
    item_html = get_page_data(item_url)
    item_data = format_item_info(key, item_html)
    md5_str = md5(''.join(texts_arr) +
                  item_data.get('content') + item_data.get('reply'))
    q.put([md5_str, dict(**content_data, **item_data)])


manager = Manager()
q = manager.Queue()
for key, val in data.items():
    while True:
        page_flag = True
        url = '%s?pageNo=%d' % (val, page)
        soup = get_page_data(url)

        page_info = soup.select(
            "table.center-table-cgwyh-01-titlelist-02 font")
        page_end = page_info[1].get_text().strip()

        page_data = soup.select("table.list-cgwyh-01-titlelist-02 tr")[1:]
        many_content = []
        url_list = []

        page_content = {}
        for el in page_data:
            item_url, texts_arr, content_data = format_page_info(key, el)
            url_list.append(item_url)
            page_content[item_url] = {}
            page_content[item_url]['content_data'] = content_data
            page_content[item_url]['texts_arr'] = texts_arr

        print('total %d/%s ' % (page, page_end))

        loop = asyncio.new_event_loop()
        asyncio.set_event_loop(loop)
        loop.run_until_complete(asyncio.wait(
            [as_get_content(q, url, key) for url in url_list]))
        loop.close()

        while not q.empty():
            item = q.get()
            item_url = item[0]
            item_content = item[1]
            item_data = page_content.get(item_url)
            new_data = item_data.get('content_data')
            md5_str = md5(''.join(item_data.get('texts_arr')) +
                          item_content.get('content') + item_content.get('reply'))

            if collection.find_one({'content_md5': md5_str}):
                page_flag = False
                continue

            if md5_str in [x.get('content_md5') for x in many_content]:
                continue

            new_data['content_md5'] = md5_str
            many_content.append(dict(**item_content, **new_data))

        if many_content:
            collection.insert_many(many_content)

        if page == page_end:
            break
        page += 1
