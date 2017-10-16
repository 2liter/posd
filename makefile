
all: hw3


hw3: mainAtom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 mainAtom.o -lgtest
else
	g++ -o hw3 mainAtom.o -lgtest -lpthread
endif

mainAtom.o: mainAtom.cpp utAtom.h atom.h utStruct.h struct.h number.h
	g++ -std=gnu++0x -c mainAtom.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif

stat:
	wc *.h *.cpp
