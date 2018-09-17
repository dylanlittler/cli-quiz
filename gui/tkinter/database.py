import sqlite3 as lite

class DB(object):

    def __init__(self, connection, table):
        self.connection = connection
        self.table = table


    def select(self, connection, sql):
        with connection:

            connection.row_factory = lite.Row

            cur = connection.cursor()
            cur.execute(sql)

            rows = cur.fetchall()

            return rows
