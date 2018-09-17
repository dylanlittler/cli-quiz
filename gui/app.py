import web
render = web.template.render('templates/')

db = web.database(dbn='sqlite', db='flashcards.db')

urls = (
    '/', 'index',
    '/select', 'select'
)

app = web.application(urls, globals())

class index:
    def GET(self):
        questions = db.select('flashcards')
        return render.index(questions)

class select:
    def GET(self):
        i = web.input(id=None)
        card = db.select('flashcards', i, where="ID=$id")
        return render.select(card)
    
if __name__ == "__main__":
    app.run()
