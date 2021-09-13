#==========================================
#    Makefile: 	makefile for greasy
#    author  : 	SheLuChun
#    e-mail  :	1378930608@qq.com
#==========================================

CC=gcc
CFLAGS=-O -Wall

all: greasy

greasy: greasy.c greasy.h
	$(CC) $(CFLAGS) -o greasy greasy.c -lncurses

clean:
	rm -f greasy

distclean: clean

