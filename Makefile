COMPILER=gcc

# Flags
CFLAGS=-O3 -Wall -std=gnu11 -pedantic -lm -fopenmp -pg

# Files to compile
OBJECTS=est_matriz_seq.c

# Executable name
EXE=est_matriz_seq


all: $(OBJECTS)
	$(COMPILER) $(OBJECTS) $(CFLAGS) -o $(EXE)

run:
	./$(EXE) < input

clean:
	rm $(EXE)

profile:
	./$(EXE) < input
	gprof $(EXE) < input gmon.out > analise.txt
