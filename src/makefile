CC=clang++
FLAGS=-O3 -Wall -std=c++11
PROG=run.exe
ARGS=orders_example.txt

all: HardwoodSellerC.o 
	$(CC) $(FLAGS) -o $(PROG) HardwoodSellerC.o 

HardwoodSellerC.o: HardwoodSellerC.cpp
	$(CC) -c HardwoodSellerC.cpp 

clean:
	rm -f *.o $(PROG)

run: $(PROG)
	./$(PROG) $(ARGS)
