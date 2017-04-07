#!/usr/bin/env python3
# encoding: utf-8

import requests
import sqlite3
import os

from master import *

pwd = os.path.dirname(__file__)

#  print("about to print pwd")
print(pwd)
conn = sqlite3.connect(os.path.join(pwd, "../a.db"))
c = conn.cursor()

# Create table
c.execute('''CREATE TABLE if not exists stocks
             (date text, trans text, symbol text, qty real, price real)''')

c.execute("INSERT INTO stocks VALUES ('2006-01-05','BUY','RHAT',100,35.14)")

conn.commit()
conn.close()


class test(object):

    def p(self):
        #  r = requests.get("http://www.baidu.com")
        #  print (r.text)
        print ("call from cpp")

    def haha(self):
        print ("return from python")
        return "hahahahaha!"

def func():
    print("call function from cpp")

def setHistoryListItems(widget):
    for i in range(3):
        s = "新纪元{}.novel\n~/marco/新纪元{}.novel#{}".format(i, i, i)
        widget.insertItem(0, makeQString(s))
