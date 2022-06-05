

exec : main.o internal_functions.o tetriminos.o displate.o
		gcc $^ -o bin/$@

main.o : src/main.c src/Headers.h
		gcc -c $< -o $@

internal_functions.o : src/internal_functions.c src/Headers.h
		gcc -c $< -o $@

tetriminos.o : src/tetriminos.c src/Headers.h
		gcc -c $< -o $@

displate.o : src/displate.c src/Headers.h
		gcc -c $< -o $@

clear :
	rm -f *.o
	rm -f bin/exec