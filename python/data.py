db_name = "data.db"
select = "SELECT type, description, size FROM data ORDER BY size"
insert = "INSERT INTO data (type, description, size) VALUES (?,?,?)"
queries = []
queries.append("Enter type: ")
queries.append("Enter description: ")
queries.append("Enter size: ")
spacing1 = 15
spacing2 = 50
