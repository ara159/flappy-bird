build: clean FlappyBirdy.out
	# Build Complete ./FlappyBirdy.out!

FlappyBirdy.out:
	g++ -g $(wildcard src/*.cpp) -o FlappyBirdy.out -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f FlappyBirdy.out FlappyBirdy.out
