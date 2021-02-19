all:
	gcc -g *.c -o game -lcsfml-graphics -lcsfml-window -lcsfml-audio
clean:
	rm -rf *.o game