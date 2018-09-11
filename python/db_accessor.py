import sqlite3 as db

def execute(con, sql, entries):
    '''Insert rows of data into database.'''
    with con:

        cur = con.cursor()
        cur.execute(sql, entries)
        con.commit()

def insert(queries, con, sql, rows, spacing1, spacing2):
    while True:
        if input("Do you want to insert another row? [Y/n]: ") == "n":
            print("exiting...")
            break
        else:
            entries = []
            for query in queries:
                text = input(query)
                entries.append(text)
            execute(con, sql, entries)
    print("\nNow displaying table contents...\n")
    select(rows, spacing1, spacing2)


def select(rows, spacing1, spacing2):
    ''' Print db rows in equally distanced columns '''
    for row in rows:
        print('{: <{width1}} {: <{width2}} {}'.format(
            row[0], row[1], row[2], width1=spacing1, width2=spacing2))


def review(rows, review_type):
    if review_type == 1:
        for row in rows:
            print("Q: " + row[0] + "?")
            input(">")
            print("A: " + row[1])
            input(">")
    elif review_type == 2:
        for row in rows:
            print("Q: " + row[1] + "?")
            input(">")
            print("A: " + row[0])
            input(">")
    else:
        print("Specify 1 for first column review or 2 for second column.")
        sys.exit(1)
