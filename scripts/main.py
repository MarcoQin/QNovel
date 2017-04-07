#!/usr/bin/env python3
# encoding: utf-8

import os
import sys
base_dir = os.path.abspath(os.path.join(os.path.abspath(os.path.dirname(__file__)), '../'))
sys.path.insert(1, base_dir)


from scripts.db import History

from master import *

def setHistoryListItems(widget):
    for record in History.select().order_by(History.last_open_time.desc()).limit(20):
        s = "%s\n%s#%s" % (record.name, record.path, record.id)
        widget.addItem(makeQString(s))


def setHistoryLabelInfo(id, label):
    try:
        h = History.get(History.id==id)
        s = "%s\n%s\n%s\n%s\n%s\n" % (h.name, h.path, h.description, h.create_time, h.last_open_time)
        label.setText(makeQString(s))
    except Exception as e:
        label.setText(makeQString("Error: %s" % e))
