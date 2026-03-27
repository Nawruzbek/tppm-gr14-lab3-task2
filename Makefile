#Makefile for C-project and sqlite database

studentapp: build/main.o build/students.o
	gcc -o studentapp build/main.o build/students.o -l sqlite3

build/main.o: src/main.c src/students.h
	mkdir -p build
	gcc -c -o build/main.o src/main.c

build/students.o: src/students.c src/students.h
	gcc -c -o build/students.o src/students.c

clean:
	rm -rf build studentapp

run:
	./studentapp
