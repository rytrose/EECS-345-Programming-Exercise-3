COMPILER = gcc
SOURCE = ex3.c
OUTPUT = ex3.o

all:
	$(COMPILER) -o $(OUTPUT) $(SOURCE)
	./$(OUTPUT)
	rm -f $(OUTPUT)

clean:
	rm -f $(OUTPUT)
