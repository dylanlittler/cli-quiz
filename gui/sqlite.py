import sqlite3 as db
import sys

con = db.connect('flashcards.db')

with con:

    con.row_factory = db.Row

    cur = con.cursor()
    cur.execute("SELECT * FROM flashcards")

    rows = cur.fetchall()

    for row in rows:
        print row['QUESTION']
        print row['ANSWER']
        print row['CATEGORY']
        print row['TITLE']





#try:
#    con = db.connect('flashcards.db')

#    cur = con.cursor()
#    cur.execute('SELECT * FROM flashcards')

#    data = cur.fetchall()

#    for row in data:
#        print row

#except db.Error, e:
#    print "Error: %s" % e.args[0]
#    sys.exit(1)

#finally:
#    if con:
#        con.close()
