bst: main.o monsterType.o ListReader.o 
	g++ -g -std=c++11 -Wall main.cpp ListReader.cpp monsterType.cpp -o bst
main.o: main.cpp monsterType.cpp monsterType.h ListReader.h ListReader.cpp
	g++ -g -std=c++11 -Wall -c main.cpp
monsterType.o: monsterType.cpp monsterType.h
	g++ -g -std=c++11 -Wall -c monsterType.cpp
ListReader.o: ListReader.h ListReader.cpp
	g++ -g -std=c++11 -Wall -c ListReader.cpp
clean:
	rm *.o bst
	echo clean done 
