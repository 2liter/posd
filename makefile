

INC_DIR = include

all: hw2

hw2: mainTerm.o atom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainTerm.o atom.o -lgtest
else
	g++ -o hw2 mainTerm.o atom.o -lgtest -lpthread
endif

atom.o: atom.cpp number.h atom.h
		g++ -std=gnu++0x -c atom.cpp
	
mainTerm.o: mainTerm.cpp utTerm.h number.h variable.h atom.h
		g++ -std=gnu++0x -c mainTerm.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif
