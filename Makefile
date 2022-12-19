COMPILER=gcc

# Flags
CFLAGS=-O3 -Wall -std=gnu11 -pedantic -lm -fopenmp -pg -fno-inline

# Files to compile
OBJECTS=est_matriz_par.c
SEQ = est_matriz_seq.c

# Executable name
EXE=est_matriz_par
EXE2=est_matriz_seq


all: $(OBJECTS)
	$(COMPILER) $(OBJECTS) $(CFLAGS) -o $(EXE)
	$(COMPILER) $(SEQ) $(CFLAGS) -o $(EXE2)
	
run:
	./$(EXE) < input

clean:
	rm $(EXE) $(EXE2)

profile:
	./$(EXE) < input
	gprof $(EXE) < input gmon.out > analise.txt
