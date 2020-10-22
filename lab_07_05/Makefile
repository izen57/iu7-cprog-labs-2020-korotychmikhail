# Переменные
CFLAGS = -std=c99 -Wall -Werror -pedantic -c
S = ./src/
O = ./out/
# $@ - цель
# $^ - список зависимостей
# $< - первая зависимость
unit: unit_tests.exe
	./$@
unit_tests.exe: $(O)check_main.o $(O)key.o $(O)mysort.o
	gcc -o $@ $^ -lcheck
app.exe: $(O)main.o $(O)key.o $(O)mysort.o
	gcc -o $@ $^
$(O)check_main.o: ./unit_tests/check_main.c
	gcc $(CFLAGS) $^ -o $@
$(O)main.o: $(S)main.c
	gcc $(CFLAGS) $^ -o $@
$(O)key.o: $(S)key.c
	gcc $(CFLAGS) $^ -o $@
$(O)mysort.o: $(S)mysort.c
	gcc $(CFLAGS) $^ -o $@
.PHONY: clean
clean:
	rm -f $(O)*.o *.exe