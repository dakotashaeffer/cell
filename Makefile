cell: cell.o libcell.o
	gcc -O3 -o cell cell.o libcell.o -lncurses -lm

cell.o: main.c libcell.h
	gcc -O3 -c -o cell.o main.c -lncurses -lm

libcell.o: libcell.c libcell.h
	gcc -O3 -c -o libcell.o libcell.c -lncurses -lm

.PHONY: clean

clean: 
	rm *.o

PREFIX = /usr/local

.PHONY: install

install: cell
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp $< $(DESTDIR)$(PREFIX)/bin/cell