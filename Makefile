# list/Makefile
#
# Makefile for list implementation and test file.
#
# <Author>
build_list: list.c main.c
	gcc list.c main.c -o list
