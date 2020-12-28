FLAGS = -std=c99 -Wall -Werror -pedantic

.PHONY: clean

main.py: lib.dll
	py $@
lib.dll: lib.o
	gcc -shared $^ -Wl,--subsystem,windows -o $@
lib.o: lib.c lib.h
	gcc $(FLAGS) -D LIB_EXPORTS -c $<

clean:
	rm -f *.dll *.o *.exe