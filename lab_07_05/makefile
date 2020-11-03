# Переменные
CFLAGS = -std=c99 -Wall -Werror -pedantic -c
S = ./src/
O = ./out/
I = ./inc/
# $@ - цель
# $^ - список зависимостей
# $< - первая зависимость
.PHONY: clean unit
app.exe: $(O)main.o $(O)key.o $(O)mysort.o
	gcc -o $@ $^
unit: unit_tests.exe
	./$^
unit_tests.exe: $(O)check_main.o $(O)key.o $(O)mysort.o
	gcc -o $@ $^ -lcheck
$(O)check_main.o: ./unit_tests/check_main.c $(I)key.h $(I)mysort.h
	gcc $(CFLAGS) $< -o $@
$(O)main.o: $(S)main.c $(I)key.h $(I)mysort.h
	gcc $(CFLAGS) $< -o $@
$(O)key.o: $(S)key.c $(I)key.h
	gcc $(CFLAGS) $< -o $@
$(O)mysort.o: $(S)mysort.c $(I)mysort.h
	gcc $(CFLAGS) $< -o $@
clean:
	rm -f $(O)*.o *.exe