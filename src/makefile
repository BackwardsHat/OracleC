CC=clang++
FLAGS=-O3 -Wall -std=c++11
PROG=run.exe
ARGS=./testfiles/orders_example.txt

all: HardwoodSellerC.o Record.o WoodItem.o 
	$(CC) $(FLAGS) -o $(PROG) HardwoodSellerC.o Record.o WoodItem.o

HardwoodSellerC.o: HardwoodSellerC.cpp
	$(CC) $(FLAGS) -c HardwoodSellerC.cpp 

Record.o: Record.cpp
	$(CC) $(FLAGS) -c Record.cpp

WoodItem.o: WoodItem.cpp
	$(CC) $(FLAGS) -c WoodItem.cpp

clean:
	rm -f *.o $(PROG)

run: $(PROG)
	./$(PROG) $(ARGS)
