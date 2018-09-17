import sqlite3 as lite
from Tkinter import Tk, Label, Button, Toplevel, Text, INSERT, Frame
import sys


class DB(object):

    def __init__(self, connection, table):
        self.connection = connection
        self.table = table
        self.rows = self.select(connection, table)

    def select(self, connection, table):
        with connection:

            connection.row_factory = lite.Row

            cur = connection.cursor()
            cur.execute("SELECT * FROM " + table)

            rows = cur.fetchall()

            return rows



class GUI(object):

    def __init__(self, master):
        self.master = master
        master.title("Flashcards")
        for row in db.rows:

            self.card_button = Button(master, text=row['TITLE'], command=lambda question=row['QUESTION'], title=row['TITLE'], answer = row['ANSWER']: self.display_question(title, question, answer))
            self.card_button.pack()
            
        self.close_button = Button(master, text="Close", command=master.quit)
        self.close_button.pack()

    def display_question(self, title, question, answer):
        top = Frame(self.master)
        top.pack()
        label = Label(top, text=question)
        label.pack()
        answer_text = Text(top)
        answer_text.insert(INSERT, answer)
        button = Button(top, text="Got the answer?", command=lambda answer=answer_text: self.show_answer(answer))
        button.pack()
        

    def show_answer(self, answer):
        answer.pack()
        

con = lite.connect('../flashcards.db')
db = DB(con, 'flashcards')
root = Tk()
gui = GUI(root)
root.mainloop()
