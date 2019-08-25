TARGET=spider
CC=g++

PARSER=src/grammar/parser
TOKENS=src/grammar/tokens
EXPRESSION=src/node/expression
STATEMENT=src/node/statement
MAIN=src/main

FILES=$(PARSER).cpp $(TOKENS).cpp \
	$(EXPRESSION).cpp $(STATEMENT).cpp \
	$(MAIN).cpp

all:
	bison -d -o $(PARSER).cpp $(PARSER).y
	flex -o $(TOKENS).cpp $(TOKENS).l
	$(CC) -o $(TARGET) $(FILES)
	mv $(TARGET) bin/

clean:
	rm -f $(PARSER).cpp $(PARSER).hpp $(TOKENS).cpp bin/$(TARGET)