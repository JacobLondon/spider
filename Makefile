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
SPIDER=build/spider
WFILES=$(SPIDER).cpp

.PHONY: all prepare spider web clean

all: web spider

prepare:
	mkdir -p bin

web: prepare
	bison -d -o $(PARSER).cpp $(PARSER).y
	flex -o $(TOKENS).cpp $(TOKENS).l
	$(CC) -o $(WTARGET) $(SFILES) $(CFLAGS)
	
	mv $(WTARGET) bin/

spider: prepare
	$(CC) -o $(STARGET) $(WFILES) $(CFLAGS)
	mv $(STARGET) bin/

clean:
	rm -f $(PARSER).cpp $(PARSER).hpp $(TOKENS).cpp \
		bin/$(WTARGET) bin/$(STARGET)
