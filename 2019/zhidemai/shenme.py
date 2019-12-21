# !/usr/bin/env python
# -*- coding: utf-8 -*-

import requests
import time
import re
import datetime
from urllib import parse
from bs4 import BeautifulSoup, Tag
import sqlite3
import os

search_data = [
    # {'s': 'iphone', 'min_price': 2000},
    {'s': 'ipad+mini', 'min_price': 1000}
]

# 查询
conn = sqlite3.connect('shenme.sqlite')
c = conn.cursor()
sql = '''
create table if not exists today_shop (
id INTEGER PRIMARY KEY AUTOINCREMENT,
today varchar(20),
title varchar(100), 
price varchar(20),
platform varchar(10),
good int,
bad int,
comment_num int,
push TINYINT default 0,
UNIQUE (today,title,platform) ON CONFLICT REPLACE
)'''
c.execute(sql)


def get_good_percent(good, bad):
    percent = '0'
    if good + bad == 0:
        return percent
    percent = int(good / (good + bad) * 100)
    return str(percent)


def get_comment_percent(comment, people):
    percent = '0'
    if people == 0:
        return percent
    percent = int(comment / (people) * 100)
    return str(percent)


def get_custom_time(html):
    day_time = re.sub("\D", "", html)
    if len(day_time) == 4:
        day_time = time.strftime('%Y%m%d', time.localtime()) + day_time
    elif len(day_time) == 8:
        if int(day_time[0:4]) > 2000:
            day_time = day_time+'0000'
        else:
            day_time = time.strftime('%Y', time.localtime()) + day_time
    format = "%Y%m%d%H%M"
    return time.strftime("%Y-%m-%d", time.strptime(day_time, format))


for params in search_data:
    url = 'https://search.smzdm.com/?c=faxian&order=time&v=b&' + \
        parse.urlencode(params)
    headers = {
        "Host": 'search.smzdm.com',
        "Accept": 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3',
        "User-Agent": 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36',
    }
    html = requests.get(url, headers=headers)
    soup = BeautifulSoup(html.text, 'html5lib')
    for item in soup.find_all(attrs={'class': 'feed-row-wide'}):
        good = item.find_all(attrs={'class': 'unvoted-wrap'})[0].span.text
        bad = item.find_all(attrs={'class': 'unvoted-wrap'})[1].span.text
        day = get_custom_time(
            item.find(attrs={'class': 'feed-block-extras'}).text)
        platform = item.find(
            attrs={'class': 'feed-block-extras'}).span.text.replace('\n', '').strip()
        price = item.find(attrs={'class': 'z-highlight'}
                          ).text.replace('\n', '').strip()
        title = item.find(attrs={'class': 'feed-nowrap'}
                          ).text.replace('\n', '').strip()
        comment_num = item.find(
            attrs={'class': 'feed-btn-comment'}).text.replace('\n', '').strip()
        good_percent = get_good_percent(int(good), int(bad))
        if datetime.datetime.now().strftime('%Y-%m-%d') == day:
            # 点值率高于20% 或 大于20人评论展示
            if int(good_percent) > 20 or int(comment_num) > 20:
                sql = "select * from today_shop where today = '%s' and title = '%s' and platform = '%s'" % (
                    day, title, platform)
                data = c.execute(sql).fetchone()
                if data is None:
                    sql = "insert into today_shop (id,today,title,price,platform,good,bad,comment_num) values(null,'%s', '%s', '%s', '%s', %s, %s, %s)" % (
                        day, title, price, platform, good, bad, comment_num)
                    c.execute(sql)
                conn.commit()


grep_str = ['Apple 苹果', '智能手机', '手机', ' ']
desp = ''
sql = "select * from today_shop where today ='%s' and push = 0" % (
    time.strftime('%Y-%m-%d', time.localtime()))
push_data = c.execute(sql).fetchall()
if len(push_data) > 0:
    for item in push_data:
        id = item[0]
        title = item[2]
        price = item[3]
        platform = item[4]
        good = item[5]
        bad = item[6]
        comment_num = item[7]
        for grep in grep_str:
            title = title.replace(grep, '')

        desp += '##### %s %s %s' % (platform, price, title)
        desp += os.linesep
        good_percent = get_good_percent(int(good), int(bad))

        desp += '##### %s %s/%s/%s' % (good_percent +
                                       '%', good, bad, comment_num)
        desp += '<br/>' + os.linesep

        sql = "update today_shop set push = 1 where id = %d" % id
        c.execute(sql)

    conn.commit()

    content = {
        'text': 'shenmezhidemai',
        'desp': desp
    }
    push_url = 'https://sc.ftqq.com/xxx.send?' + parse.urlencode(
        content)
    requests.post(push_url)
