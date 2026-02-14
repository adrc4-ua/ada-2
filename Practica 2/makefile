#Adrián David Ruiz Cantillo
#01888198J

OPTS = -Wall -Wextra -O3 -std=c++0x

all: qs-vs-hs qs-vs-hs.Msteps graphs

graphs: qs-vs-hs.Msteps qs-vs-hs.gpi
	gnuplot qs-vs-hs.gpi

qs-vs-hs: qs-vs-hs.cc
	g++ ${OPTS} -o qs-vs-hs qs-vs-hs.cc

qs-vs-hs.Msteps: qs-vs-hs
	./qs-vs-hs > qs-vs-hs.Msteps

tar: qs-vs-hs.cc makefile
	tar cvfz 01888198J.tar.gz qs-vs-hs.cc makefile qs-vs-hs.gpi

clean: 
	rm -f qs-vs-hs qs-vs-hs.Msteps fit.log *.png *~
 
