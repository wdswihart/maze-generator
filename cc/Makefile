# Makefile for Maze Generator

CC = g++
CFLAGS = -Wall -c -std=c++11
LDFLAGS = -Wall -g -o

maze-gen: main.o cell.o
	$(CC) $(LDFLAGS) maze-gen main.o cell.o -lsfml-window -lsfml-graphics -lsfml-system

main.o: main.cc
	$(CC) $(CFLAGS) main.cc

cell.o: cell.cc
	$(CC) $(CFLAGS) cell.cc
