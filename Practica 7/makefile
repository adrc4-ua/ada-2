#Adrian David Ruiz Cantillo
#01888198J

OPTS = -Wall -Wextra -O3 -std=c++0x

all: maze_greedy

maze_greedy: maze_greedy.cc
	g++ ${OPTS} -o maze_greedy maze_greedy.cc	 

tar: maze_greedy.cc makefile
	tar cvfz 01888198J.tar.gz maze_greedy.cc makefile

test: maze_greedy
	@fail=0; \
	for file in test/[0-9][0-9].maze; do \
		base=$$(basename $$file .maze); \
		echo "Testing $$file..."; \
		./maze_greedy --p2D -f $$file > test/$$base.out; \
		if diff -q test/$$base.out test/$$base.maze.sol_greedy > /dev/null; then \
			echo "OK $$file"; \
		else \
			echo "FAIL $$file"; \
			diff test/$$base.out test/$$base.maze.sol_greedy; \
			fail=1; \
		fi; \
	done; \
	exit $$fail

clean: 
	rm maze_greedy test/*.out