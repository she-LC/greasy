import turtle
import time
import sys

def print_with_turtle(outFile):

    with open(outFile, 'r') as myfile:
        data=myfile.read()



    t=turtle.Turtle()
    t.up()
    t.setpos(0,-1000)


    t.write(data,move=True,align="center", font=("Consolas",10, "normal"))

    win = turtle.Screen()
    win.exitonclick()
