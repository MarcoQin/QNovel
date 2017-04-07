#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import os
import datetime

from scripts.peewee import SqliteDatabase, Model, CharField, DateField

pwd = os.path.dirname(__file__)
db_file = os.path.join(pwd, "../history.db")

db = SqliteDatabase(db_file)


class History(Model):
    name = CharField()
    path = CharField()
    description = CharField(null=True)
    create_time = DateField(null=True)
    last_open_time = DateField(null=True)

    class Meta:
        database = db

try:
    db.connect()
    db.create_table(History)
except:
    pass
