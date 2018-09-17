import sqlite3 as lite
from Tkinter import *
from tkFont import Font
import sys
from database import DB


class FlashcardApp(Tk):

    def __init__(self, *args, **kwargs):
        Tk.__init__(self, *args, **kwargs)

        self.title_font = Font(family="Helvetica", size=18, weight="bold", slant="italic")

        container = Frame(self)
        container.pack(side="top", fill="both", expand=True)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)
        self.frames = {}
        for F in (StartPage, Categories, Titles, Questions, Answers):
            page_name = F.__name__
            frame = F(parent=container, controller=self)
            self.frames[page_name] = frame
            frame.grid(row=0, column=0, sticky="nsew")
        self.show_frame("StartPage")

    def show_frame(self, page_name):
        frame = self.frames[page_name]
        frame.tkraise()

class StartPage(Frame):
    
    def __init__(self, parent, controller):
        Frame.__init__(self, parent)
        self.controller = controller
        label = Label(self, text="Flashcards", font=controller.title_font)
        label.pack(side="top", fill="x", pady=10)
        categories_button = Button(self, text="Flashcard Categories", command=lambda: controller.show_frame("Categories"))
        close_button = Button(self, text="Close", command=self.quit)
        categories_button.pack()
        close_button.pack()
        # new_card_button
        
class Categories(Frame):

    def __init__(self, parent, controller):
        Frame.__init__(self, parent)
        self.controller = controller
        label = Label(self, text="Categories", font=controller.title_font)
        label.pack(side="top", fill="x", pady=10)

        categories = db.select(con, "SELECT DISTINCT CATEGORY FROM flashcards")
        
        for category in categories:

            category_button = Button(self, text=category['CATEGORY'], command=lambda: controller.show_frame("Titles"))
            category_button.pack()
                                     
        start_button = Button(self, text="Go to the start page", command=lambda: controller.show_frame("StartPage"))
        close_button = Button(self, text="Close", command=self.quit)
        start_button.pack()
        close_button.pack()

class Titles(Frame):
    
    def __init__(self, parent, controller):
        Frame.__init__(self, parent)
        self.controller = controller
        label = Label(self, text="Cards", font=controller.title_font)
        label.pack(side="top", fill="x", pady=10)

        titles = db.select(con, "SELECT TITLE FROM flashcards WHERE CATEGORY = 'Hardware'")

        for title in titles:
            title_button = Button(self, text=title['TITLE'], command=lambda: controller.show_frame("Questions"))
            title_button.pack()

        start_button = Button(self, text="Back to start", command=lambda: controller.show_frame("StartPage"))
        close_button = Button(self, text="Close", command=self.quit)
        start_button.pack()
        close_button.pack()

class Questions(Frame):
    def __init__(self, parent, controller):
        Frame.__init__(self, parent)
        self.controller = controller
        label = Label(self, text="Cards", font=controller.title_font)
        label.pack(side="top", fill="x", pady=10)

        start_button = Button(self, text="Go to the start page", command=lambda: controller.show_frame("StartPage"))
        close_button = Button(self, text="Close", command=self.quit)
        start_button.pack()
        close_button.pack()


class Answers(Frame):
    def __init__(self, parent, controller):
        Frame.__init__(self, parent)
        self.controller = controller
        label = Label(self, text="Cards", font=controller.title_font)
        label.pack(side="top", fill="x", pady=10)

        start_button = Button(self, text="Go to the start page", command=lambda: controller.show_frame("StartPage"))
        close_button = Button(self, text="Close", command=self.quit)
        start_button.pack()
        close_button.pack()

        

if __name__ == "__main__":
    con = lite.connect('../flashcards.db')
    db = DB(con, 'flashcards')

    app = FlashcardApp()
    app.mainloop()
