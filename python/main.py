#!/usr/bin/env python3

import sqlite3 as db
import argparse
import sys
from importlib import import_module
import db_accessor
import conf_writer


parser = argparse.ArgumentParser()
parser.add_argument("command", help="database operation", type=str)
parser.add_argument("database", help="database name", type=str)
args = parser.parse_args()

def action(con, conf):
    with con:
        cur = con.cursor()
        rows = cur.execute(conf.select)
        if args.command == "select":
            db_accessor.select(rows, conf.spacing1, conf.spacing2)
        elif args.command == "insert":
            db_accessor.insert(conf.queries, con, conf.insert, rows, conf.spacing1, conf.spacing2)
        elif args.command == "review":
            review_type = int(input("Review type 1 or 2? "))
            db_accessor.review(rows, review_type)
        else:
            "Available commands: select, review or insert"
            sys.exit(1)


def create_db():
    print("""It looks like the database you requested doesn't exist.
Please enter the instructions to create the configuration file
and database table.""")
    conf_writer.write_conf(args.database)
    conf = import_module(args.database)
    con = db.connect(conf.db_name)
    conf_writer.create_table(con)
    with con:
        cur = con.cursor()
        rows = cur.execute(conf.select)
        db_accessor.insert(conf.queries, con, conf.insert, rows, conf.spacing1, conf.spacing2)
        db_accessor.select(rows, conf.spacing1, conf.spacing2)

        
try:
    conf = import_module(args.database)
    con = db.connect(conf.db_name)
    action(con, conf)
except ImportError:
    create_db()
