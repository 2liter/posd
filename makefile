
all: hw3


hw3: mainAtom.o atom.o number.o variable.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 mainAtom.o atom.o number.o variable.o -lgtest
else
	g++ -o hw3 mainAtom.o atom.o number.o variable.o -lgtest -lpthread
endif

mainAtom.o: mainAtom.cpp utAtom.h atom.h utStruct.h struct.h number.h variable.h
	g++ -std=gnu++0x -c mainAtom.cpp

	
atom.o: atom.cpp atom.h
	g++ -std=gnu++0x -c atom.cpp

number.o: number.cpp atom.h number.h
	g++ -std=gnu++0x -c number.cpp
variable.o: variable.cpp atom.h number.h variable.h
	g++ -std=gnu++0x -c variable.cpp
clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif

stat:
	wc *.h *.cpp
