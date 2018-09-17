import web

db = web.database(dbn='sqlite', db='flashcards.db')

questions = db.select('flashcards')

#for question in questions:
#    print question['QUESTION']
#    print question['ANSWER']
