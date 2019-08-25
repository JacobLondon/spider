TARGET=spider
CC=g++

PARSER=parser
TOKENS=tokens
EXPRESSION=node/expression
STATEMENT=node/statement
MAIN=main

FILES=$(PARSER).cpp $(TOKENS).cpp \
	$(EXPRESSION).cpp $(STATEMENT).cpp \
	$(MAIN).cpp

all:
	bison -d -o $(PARSER).cpp $(PARSER).y
	flex -o $(TOKENS).cpp $(TOKENS).l
	$(CC) -o $(TARGET) $(FILES)

clean:
	rm -f $(PARSER).cpp $(PARSER).hpp $(TOKENS).cpp $(TARGET)