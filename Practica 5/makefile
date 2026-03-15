#Adrian David Ruiz Cantillo
#01888198J

OPTS = -Wall -Wextra -O3 -std=c++0x

all: pow2 pow2.Msteps graphs

graphs: pow2.Msteps pow2.gpi
	gnuplot pow2.gpi

pow2: pow2.cc
	g++ ${OPTS} -o pow2 pow2.cc	 

pow2.Msteps: pow2
	./pow2 | tail -n +5 > pow2.Msteps

tar: pow2.cc pow2.gpi makefile
	tar cvfz 01888198J.tar.gz pow2.cc pow2.gpi makefile

clean: 
	rm -f pow2 pow2.Msteps fit.log *png *~