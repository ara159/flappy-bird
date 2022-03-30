build: clean gravity.out
	# Build Complete ./gravity.out!

gravity.out:
	g++ -g $(wildcard src/*.cpp) -o gravity.out -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f gravity.out gravity.out
