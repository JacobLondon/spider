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

.PHONY: all spider web clean

all: spider web
	mkdir -p bin

spider:
	bison -d -o $(PARSER).cpp $(PARSER).y
	flex -o $(TOKENS).cpp $(TOKENS).l
	$(CC) -o $(STARGET) $(SFILES) $(CFLAGS)
	mv $(STARGET) bin/

web:
	$(CC) -o $(WTARGET) $(WFILES) $(CFLAGS)
	mv $(WTARGET) bin/

clean:
	rm -f $(PARSER).cpp $(PARSER).hpp $(TOKENS).cpp \
		bin/$(STARGET) bin/$(WTARGET)