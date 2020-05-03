all: triangolo

triangolo: triangolo.cpp
	g++ -fmax-errors=1 triangolo.cpp -o triangolo

clean:
	rm -f *~ triangolo

