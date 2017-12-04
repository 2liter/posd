all: hw7




#madRace: mainMadRace.o
#	g++ -o madRace mainMadRace.o -lgtest -lpthread
mainMadRace.o: mainMadRace.cpp madRace.h utMadRace.h
	g++ -std=gnu++0x -c mainMadRace.cpp

#utAtom: mainAtom.o atom.o
#	g++ -o utAtom mainAtom.o atom.o -lgtest -lpthread
mainAtom.o: mainAtom.cpp utAtom.h atom.h utStruct.h struct.h
	g++ -std=gnu++0x -c mainAtom.cpp

atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp

utVariable: mainVariable.o atom.o
		g++ -o utVariable mainVariable.o atom.o -lgtest -lpthread
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=gnu++0x -c mainVariable.cpp


mainList.o: mainList.cpp list.o utList.h atom.h struct.h variable.h
		g++ -std=gnu++0x -c mainList.cpp list.o
#list.o: list.cpp list.h 
#		g++ -std=gnu++0x -c list.cpp 

struct.o:struct.cpp struct.h
	g++ -std=gnu++0x -c struct.cpp

node.o:node.cpp node.h
	g++ -std=gnu++0x -c node.cpp
	
list.o:list.cpp list.h
	g++ -std=gnu++0x -c list.cpp

hw7: mainIterator.o atom.o list.o struct.o node.o utIterator.h  iterator.h
ifeq (${OS}, Windows_NT)
	g++ -o hw7 mainIterator.o atom.o list.o struct.o node.o -lgtest
else
	g++ -o hw7 mainIterator.o atom.o list.o struct.o node.o -lgtest -lpthread
endif

#utScanner: mainScanner.o atom.o list.o scanner.h utScanner.h utParser.h parser.h
#	g++ -o utScanner mainScanner.o atom.o list.o -lgtest -lpthread

#mainParser.o: mainParser.cpp utParser.h scanner.h  atom.h struct.h variable.h parser.h node.h
#		g++ -std=gnu++0x -c mainParser.cpp

#exp: mainExp.o
#	g++ -o exp mainExp.o -lgtest -lpthread
#mainExp.o: mainExp.cpp exp.h global.h
#	g++ -std=gnu++0x -c mainExp.cpp

#utScanner: mainScanner.o scanner.h utScanner.h
#	g++ -o utScanner mainScanner.o -lgtest -lpthread
#mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h
#		g++ -std=gnu++0x -c mainScanner.cpp


mainIterator.o: mainIterator.cpp utIterator.h
	g++ -std=gnu++0x -c mainIterator.cpp

#utTerm: mainTerm.o term.o struct.o var.o list.o
#	g++ -o utTerm mainTerm.o term.o var.o struct.o list.o -lgtest -lpthread
#mainTerm.o: mainTerm.cpp utTerm.h term.h var.h utStruct.h struct.h list.h utList.h
#	g++ -std=gnu++0x -c mainTerm.cpp
#term.o: term.h term.cpp
#	g++ -std=gnu++0x -c term.cpp
#struct.o: struct.h struct.cpp
#	g++ -std=gnu++0x -c struct.cpp
#var.o: var.h var.cpp
#g++ -std=gnu++0x -c var.cpp
#list.o: list.h list.cpp term.h var.h
#	g++ -std=gnu++0x -c list.cpp
clean:
	rm -f *.o madRace utAtom utVariable utScanner hw6 hw7
stat:
	wc *.h *.cpp
