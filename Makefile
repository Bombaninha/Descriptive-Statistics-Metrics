FLAGS=-fopenmp -pg -O3
CC=gcc
RM=rm -f
EXEC=LU
PROFILE=gprof

all_512: $(EXEC512)

all_1024: $(EXEC1024)

all_2048: $(EXEC2048)

$(EXEC512):
	$(CC) $(FLAGS) $(EXEC512).c -c -o $(EXEC512).o
	$(CC) $(FLAGS) $(EXEC512).o -o $(EXEC512)
	./$(EXEC512) < $(EXEC512).in
	$(PROFILE) $(EXEC512) gmon.out > analise512.txt


$(EXEC1024):
	$(CC) $(FLAGS) $(EXEC1024).c -c -o $(EXEC1024).o
	$(CC) $(FLAGS) $(EXEC1024).o -o $(EXEC1024)
	./$(EXEC1024) < $(EXEC1024).in
	$(PROFILE) $(EXEC1024) gmon.out > analise1024.txt
	

$(EXEC2048):
	$(CC) $(FLAGS) $(EXEC2048).c -c -o $(EXEC2048).o
	$(CC) $(FLAGS) $(EXEC2048).o -o $(EXEC2048)
	./$(EXEC2048) < $(EXEC2048).in
	$(PROFILE) $(EXEC2048) gmon.out > analise2048.txt
	
clean:
	$(RM) $(EXEC).o $(EXEC) $(EXEC512).o $(EXEC512) $(EXEC1024).o $(EXEC1024) $(EXEC2048).o $(EXEC2048) gmon.out analise512.txt analise1024.txt analise2048.txt
