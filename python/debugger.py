db_name = "debugger.db"
select = "SELECT DISTINCT command, description, debugger FROM debugger ORDER BY debugger"
insert = "INSERT INTO debugger (command, description, debugger) VALUES (?,?,?)"
queries = []
queries.append("Enter command: ")
queries.append("Enter description: ")
queries.append("Enter debugger name: ")
spacing1 = 20
spacing2 = 50
