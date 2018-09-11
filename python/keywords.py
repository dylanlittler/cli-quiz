db_name = "keywords.db"
select = "SELECT DISTINCT description, operator, type FROM keywords ORDER BY type"
insert = "INSERT INTO keywords (description, operator, type) VALUES (?,?,?)"
queries = []
queries.append("Enter description: ")
queries.append("Enter operator: ")
queries.append("Enter type: ")
spacing1 = 50
spacing2 = 12
