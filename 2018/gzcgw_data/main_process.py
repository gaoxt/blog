# -*- coding: utf-8 -*-

from user_agent import generate_user_agent
import requests
from bs4 import BeautifulSoup
from dateutil.parser import parse
from pymongo import MongoClient
import re
import html
import hashlib
import time
import asyncio
import aiohttp
import random
from multiprocessing import Process, Queue, Pool, Manager

proxy = 'http://111.177.188.19:9999'
aio_proxy = 'http://119.101.112.63:9999'
proxies = {
    'http': proxy
}


ua = generate_user_agent()
headers = {
    'User-Agent': ua
}

conn = MongoClient('127.0.0.1', 27017)
collection = conn.gz_data.all_content


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


def md5(arg, code='utf-8'):
    md5_pwd = hashlib.md5(bytes('gz', encoding=code))
    md5_pwd.update(bytes(arg, encoding=code))
    return md5_pwd.hexdigest()


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
    # response = requests.get(url, headers=headers, proxies=proxies)
    response = requests.get(url, headers=headers)
    response.encoding = 'utf-8'
    soup = BeautifulSoup(response.text, 'html.parser')
    return soup


pattern = '<a.href="([^"]*)"[^>]*>(.*)</a>'
pattern_page = '<font.*[^>]*(.*)</font>'
page = 1
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


def format_item_info(key, item_soup):
    data = {}
    contents = item_soup.find_all(class_="main-table-td02")
    contents = filter_content(key, contents)
    data['content'] = contents[3].get_text().replace(u'\xa0', u' ')
    data['reply'] = contents[4].get_text().replace(u'\xa0', u' ')
    return data


def process_main_func(q, key, el):
    item_url, texts_arr, content_data = format_page_info(key, el)
    item_html = get_page_data(item_url)
    item_data = format_item_info(key, item_html)
    md5_str = md5(''.join(texts_arr) +
                  item_data.get('content') + item_data.get('reply'))
    q.put([md5_str, dict(**content_data, **item_data)])


data = {
    # 'zxjy': 'http://www.gzcgw.gov.cn/portal/site/site/portal/zmhd/zxjy.portal',
    # 'wtts': 'http://www.gzcgw.gov.cn/portal/site/site/portal/zmhd/wtts.portal',
    'jzxx': 'http://www.gzcgw.gov.cn/portal/site/site/portal/zmhd/jzxx.portal'
}

manager = Manager()
q = manager.Queue()
process_count = 8

for key, val in data.items():
    page_flag = True
    while True:
        url = '%s?pageNo=%d' % (val, page)
        soup = get_page_data(url)
        category_id = soup.select("div.id")
        page_info = soup.select(
            "table.center-table-cgwyh-01-titlelist-02 font")
        page_end = page_info[1].get_text().strip()

        page_data = soup.select("table.list-cgwyh-01-titlelist-02 tr")[1:]
        process_data = [page_data[n:n + process_count]
                        for n in range(0, len(page_data), process_count)]
        many_content = []
        sleep_num = random.randint(1, 2)
        time.sleep(sleep_num)

        for i in range(len(process_data)):
            print('total %d/%s  %d/%d sleep:%d' % (
                page, page_end, i + 1, len(process_data), sleep_num))

            p = Pool(process_count)
            for n in range(0, len(process_data[i])):
                p.apply_async(process_main_func, args=(
                    q, key, str(process_data[i][n])))

            p.close()
            p.join()

            while not q.empty():
                item = q.get()
                item_md5 = item[0]
                if collection.find_one({'content_md5': item_md5}):
                    page_flag = False
                    continue

                if item_md5 in [x.get('content_md5') for x in many_content]:
                    continue

                item_data = item[1]
                item_data['content_md5'] = item_md5
                many_content.append(item_data)

        if many_content:
            collection.insert_many(many_content)

        if page >= int(page_end):
            exit()
        page += 1
