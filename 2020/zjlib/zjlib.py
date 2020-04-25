# !/usr/bin/env python
# -- coding:UTF-8 --

import requests
import datetime
import time
from bs4 import BeautifulSoup


class interApi:
    session = ''
    userData = {}
    SESSION_id = ''

    def __init__(self, userData, SESSION_id=''):
        self.userData = userData
        self.SESSION_id = SESSION_id

        main_headers = {
            "Host": "hd.interlib.cn",
            "Accept": 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
            "Accept-Language": 'zh-cn',
            "User-Agent": "Mozilla/5.0 (iPhone; CPU iPhone OS 13_3 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Mobile/15E148 MicroMessenger/7.0.10(0x17000a21) NetType/WIFI Language/zh_CN",
            "Content-type": 'application/x-www-form-urlencoded; charset=UTF-8',
        }
        main_cookie = {
            'UM_distinctid': '16ffffab72b21b-0493e09874a5e68-53607829-2c600-16ffffab72dc4',

        }
        if self.SESSION_id:
            main_cookie['SESSION'] = self.SESSION_id

        self.session = requests.session()
        self.session.cookies = requests.utils.cookiejar_from_dict(main_cookie)
        self.session.headers = main_headers

        # reg SESSION
        if not self.SESSION_id:
            self.registration()

    def registration(self):
        url = "http://hd.interlib.cn/mb/main/index?libcode=ZJLIB"
        res = self.session.get(url)
        url = "http://hd.interlib.cn/mb/reader/getOpenid"
        res = self.session.post(
            url, data={'code': '', 'openid': self.userData['openid']})
        print(res.text)

        data = {
            'rdid': self.userData['rdid'],
            'rdname': self.userData['name'],
            'rdcertify': self.userData['rdid'],
            'rdloginid': self.userData['mobile'],
            'openid': self.userData['openid'],
        }
        url = "http://hd.interlib.cn/mb/reader/registration"
        res = self.session.post(url, headers={
            'Referer': 'http://hd.interlib.cn/mb//reader/person'}, data=data).json()
        print(res)
        if res['code'] != 200:
            exit('reg error')

    def getPersonInfo(self):
        url = "http://hd.interlib.cn/mb/reader/person"
        res = self.session.get(url)
        userName = ''
        soup = BeautifulSoup(res.text, 'html5lib')
        dom = soup.select("p.u-info-name a")
        for i in dom:
            userName = i.get_text(strip=True)

        userList = ''
        dom = soup.select("ul.u-menu-list li a")
        for idx, i in enumerate(dom):
            if idx >= 2:
                break
            userList += i.get_text("|", strip=True) + " "
        print(userName, userList)

    def entry(self, specialId, dateId):
        data = {
            'specialId': specialId,
            'dateids': dateId,
            'attachDesc': '',
            'carryNum': 0,
        }
        url = "http://hd.interlib.cn/mb/activity/entry"
        res = self.session.post(url, headers={
            'Referer': 'http://hd.interlib.cn/mb/activity/actEnterFor/'+str(specialId)}, data=data).json()
        print(res)
        flag = False
        if res['code'] == 200:
            flag = True
        return flag

    def getDateId(self, specialId):
        dateId = 0
        url = "http://hd.interlib.cn/mb/activity/actEnterFor/"+str(specialId)
        res = self.session.get(url, headers={
            'Referer': 'http://hd.interlib.cn/mb/activity/actEnterFor/'+str(specialId)})
        soup = BeautifulSoup(res.text, 'html5lib')
        idText = soup.select("ul.act-center-cci li")
        for i in idText:
            dateId = i.get("value")
            break
        return dateId

    def activityList(self, day=''):
        specialId = 0
        specialIds = []
        days = []
        url = "http://hd.interlib.cn/mb/activity/activityList"
        res = self.session.get(url)
        soup = BeautifulSoup(res.text, 'html5lib')
        idText = soup.select("ul.index-tj-actlist li a")
        dayText = soup.select("div.tj-actlist-title span")

        for i in idText:
            specialIds.append(i.attrs['href'].split('/')[-1])

        for i in dayText:
            item = i.get_text(strip=True)
            if item != '' and item.find("浙江图书馆") < 0:
                days.append(item)
        print(specialIds, days)

        if not day:
            specialId = specialIds[0]
        else:
            for key, i in enumerate(days):
                if day in i:
                    specialId = specialIds[key]
                    break

        return specialId


data = {
    'name': 'your name',
    'rdid': 'your IDcard',
    'mobile': 'your mobile',
    'openid': 'your weixin_with_zjlib_openid',
}

inter = interApi(data)
startTime = int(str(time.time()).split('.')[0])
num = 1
while True:
    nowDatetiem = datetime.datetime.now()+datetime.timedelta(days=1)
    nowDay = nowDatetiem.strftime('%-m月%-d日')
    nowTime = nowDatetiem.strftime('%H:%M:%S')
    nowHour = nowDatetiem.strftime('%H')
    runTime = int(str(time.time()).split('.')[0])
    diffTime = runTime - startTime
    print(nowDay, nowTime, diffTime)

    if nowTime <= "15:00:00" or nowTime >= "15:05:00":
        # 重试次数时间增倍
        time.sleep(2*num)
        if num >= 10:
            print("num max 10,check your code!")
            break
        continue

    # 每小时重新注册一次
    if diffTime >= 60*60*1:
        startTime = int(str(time.time()).split('.')[0])
        inter.registration()

    num += 1
    specialId = inter.activityList(nowDay)
    dateId = inter.getDateId(specialId)
    flag = inter.entry(specialId, dateId)
    inter.getPersonInfo()
    if flag == True:
        break
