

INC_DIR = include

all: hw2

hw2: mainTerm.o atom.o variable.o number.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainTerm.o atom.o variable.o number.o -lgtest
else
	g++ -o hw2 mainTerm.o atom.o variable.o number.o -lgtest -lpthread
endif

number.o: number.cpp number.h atom.h variable.h term.h
	g++ -std=gnu++0x -c number.cpp

atom.o: atom.cpp number.h atom.h variable.h term.h
	g++ -std=gnu++0x -c atom.cpp
variable.o: variable.cpp atom.cpp number.h atom.h variable.h term.h
	g++ -std=gnu++0x -c variable.cpp

	
mainTerm.o: mainTerm.cpp utTerm.h number.h variable.h atom.h term.h
	g++ -std=gnu++0x -c mainTerm.cpp


clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif
