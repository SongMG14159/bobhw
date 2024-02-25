all: packet-stat

packet-stat: process.o main.o
	g++ -o $@ process.o main.o -lpcap -lstdc++

main.o: process.h main.cpp
	g++ -c -o $@ main.cpp

process.o: process.h process.cpp
	g++ -c -o $@ process.cpp

clean:
	rm -f packet-stat
	rm -f *.o

run: packet-stat
	./packet-stat $(pcap_file)
