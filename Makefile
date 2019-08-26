STARGET=spider
WTARGET=web
CC=g++
CFLAGS=-std=c++11

# target 1
PARSER=src/grammar/parser
TOKENS=src/grammar/tokens
EXPRESSION=src/node/expression
STATEMENT=src/node/statement
MAIN=src/main

SFILES=$(PARSER).cpp $(TOKENS).cpp \
	$(EXPRESSION).cpp $(STATEMENT).cpp \
	$(MAIN).cpp

# target 2
WEB=build/web
WFILES=$(WEB).cpp

.PHONY: all prepare spider web clean

all: spider web

prepare:
	mkdir -p bin

spider: prepare
	bison -d -o $(PARSER).cpp $(PARSER).y
	flex -o $(TOKENS).cpp $(TOKENS).l
	$(CC) -o $(STARGET) $(SFILES) $(CFLAGS)
	
	mv $(STARGET) bin/

web: prepare
	$(CC) -o $(WTARGET) $(WFILES) $(CFLAGS)
	mv $(WTARGET) bin/

clean:
	rm -f $(PARSER).cpp $(PARSER).hpp $(TOKENS).cpp \
		bin/$(STARGET) bin/$(WTARGET)
