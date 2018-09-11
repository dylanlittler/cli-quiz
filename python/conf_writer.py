#!/usr/bin/env python3

def write_conf(file_name):
    db_name = 'db_name = "' + file_name + '.db"'
    select = 'select = "' + input("Enter select statement: ") + '"'
    insert = 'insert = "' + input("Enter insert statement: ") + '"'
    queries = "queries = []"
    num_queries = int(input("Enter query number: "))
    query_list = []
    for query in range(num_queries):
        query_list.append("queries.append(" + input("Enter query " + str(query) + ": ") + ")")
    spacing1 = "spacing1 = " + input("Enter spacing 1: ")
    spacing2 = "spacing2 = " + input("Enter spacing 2: ")

    with open(file_name + ".py", "w") as f:
        f.write(db_name + "\n")
        f.write(select + "\n")
        f.write(insert + "\n")
        f.write(queries + "\n")
        for query in query_list:
            f.write(query + "\n")
        f.write(spacing1 + "\n")        
        f.write(spacing2 + "\n")        
        
def create_table(con):
    sql = input("Enter SQLite table creation code: ")
    with con:
        cur = con.cursor()
        cur.execute(sql)
