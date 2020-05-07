all: baseProblem.exe flexiSearch.exe flexiSearchFast.exe

PGOPT:=

# Add -pg for gprof
%.o: %.cpp %.h
	g++ ${PGOPT} -Werror -fmax-errors=1 -O3 -c $< -o $@

%.so: %.cpp %.h
	g++ ${PGOPT} -Werror -fmax-errors=1 -shared -fPIC -std=c++11 -O3 $< -o $@

%.exe: %.cpp Move.o Coordinate.o Triangle.o
	g++ ${PGOPT} -Werror -fmax-errors=1 -O3 $< Move.o Coordinate.o Triangle.o -o $@

profile: flexiSearchFast.exe
	./flexiSearchFast.exe 5 1
	gprof ./flexiSearchFast.exe | gprof2dot/gprof2dot.py | dot -Tsvg -o output.svg

clean:
	rm -f *~ *.exe *.o *.png *.svg *.out

