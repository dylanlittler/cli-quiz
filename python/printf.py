db_name = "printf.db"
select = "SELECT DISTINCT title, value, type FROM printf ORDER BY type"
insert = "INSERT INTO printf (title, value, type) VALUES (?,?,?)"
queries = []
queries.append("Enter character name: ")
queries.append("Enter character: ")
queries.append("Enter character type: ")
spacing1 = 20
spacing2 = 5
