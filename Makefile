FLAGS=-fopenmp -pg -O3
CC=gcc
RM=rm -f
EXEC=LU
EXEC512=LU512
EXEC1024=LU1024
EXEC2048=LU2048
PROFILE=gprof

all_512: $(EXEC512)
all_1024: $(EXEC1024)
all_2048: $(EXEC2048)

$(EXEC512):
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC)512.o
	$(CC) $(FLAGS) $(EXEC)512.o -o $(EXEC)512
	./$(EXEC)512 < $(EXEC)512.in
	$(PROFILE) $(EXEC)512 gmon.out > analise512.txt


$(EXEC1024):
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC)1024.o
	$(CC) $(FLAGS) $(EXEC)1024.o -o $(EXEC)1024
	./$(EXEC)1024 < $(EXEC)1024.in
	$(PROFILE) $(EXEC)1024 gmon.out > analise1024.txt
	

$(EXEC2048):
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC)2048.o
	$(CC) $(FLAGS) $(EXEC)2048.o -o $(EXEC)2048
	./$(EXEC)2048 < $(EXEC)2048.in
	$(PROFILE) $(EXEC)2048 gmon.out > analise2048.txt
	
clean:
	$(RM) $(EXEC).o $(EXEC) $(EXEC)512.o $(EXEC)512 $(EXEC)1024.o $(EXEC)1024 $(EXEC)2048.o $(EXEC)2048 gmon.out analise512.txt analise1024.txt analise2048.txt
