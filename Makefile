FLAGS=-fopenmp -pg -O3

CC=gcc

RM=rm -f

EXEC=LU

PROFILE=gprof

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)
	./$(EXEC) < $(EXEC).in
	$(PROFILE) $(EXEC) gmon.out > analise.txt

clean:
	$(RM) $(EXEC).o $(EXEC) gmon.out analise.txt
