'''class GUI(Tk):

    def __init__(self, *args, **kwargs):
        Tk.__init__(self, *args, **kwargs)
        self.title("Flashcards")
        for row in db.rows:

            self.card_button = Button(self, text=row['TITLE'], command=lambda question=row['QUESTION'], title=row['TITLE'], answer = row['ANSWER']: self.display_question(title, question, answer))
            self.card_button.pack()
            
        self.close_button = Button(self, text="Close", command=self.quit)
        self.close_button.pack()

    def display_question(self, title, question, answer):
        top = Frame(self)
        top.pack()
        label = Label(top, text=question)
        label.pack()
        answer_text = Text(top)
        answer_text.insert(INSERT, answer)
        button = Button(top, text="Got the answer?", command=lambda answer=answer_text: self.show_answer(answer))
        button.pack()
        

    def show_answer(self, answer):
        answer.pack()
'''
