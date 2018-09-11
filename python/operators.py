db_name = "operators.db"
select = "SELECT DISTINCT description, operator, type FROM operators ORDER BY type"
insert = "INSERT INTO operators (description, operator, type) VALUES (?,?,?)"
queries = []
queries.append("Enter description: ")
queries.append("Enter operator: ")
queries.append("Enter type: ")
spacing1 = 30
spacing2 = 10
review1 = "description"
review2 = "operator"
