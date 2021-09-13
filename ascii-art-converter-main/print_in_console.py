import turtle
import time
import sys


def print_in_console(outFile):
    with open(outFile, 'r') as myfile:
        data=myfile.read()


    delay = 0.1

    for char in data:
        sys.stdout.write(char)
        sys.stdout.flush()
        time.sleep(0.0005)
