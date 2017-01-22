##############################################
# Makefile for CST320 labs
#
# Author: Philip Howard
# phil.howard@oit.edu
#
# Nov. 24, 2015
#

COPTS=-Wall -g -c -O0
OBJS=main.o \
	 langlex.o \
	 parse.o \
	 utils.o \
	 
COMP=g++

all: lang

clean:
	rm -f $(OBJS)
	rm -f langlex.c
	rm -f lang
	rm -f out

.c.o:
	$(COMP) $(COPTS) $? -o $@

.cpp.o:
	$(COMP) $(COPTS) $? -o $@

main.o: main.cpp langlex.c parse.cpp
	$(COMP) $(COPTS) main.cpp -o main.o

langlex.c: lang.l
	flex -o langlex.c lang.l

langlex.o: langlex.c
	$(COMP) $(COPTS) -Wno-sign-compare $? -o $@

utils.o: utils.cpp
	$(COMP) $(COPTS) utils.cpp -o utils.o

parse.o: parse.cpp
	$(COMP) $(COPTS) parse.cpp -o parse.o

lang: $(OBJS)
	$(COMP) $(OBJS) -o lang

