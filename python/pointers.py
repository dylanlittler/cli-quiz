db_name = "pointers.db"
select = "SELECT description, syntax, type FROM pointers"
insert = "INSERT INTO pointers (description, syntax, type) VALUES (?,?,'pointers')"
queries = []
queries.append("Enter description: ")
queries.append("Enter syntax: ")
spacing1 = 50
spacing2 = 10
