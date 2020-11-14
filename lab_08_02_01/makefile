# Переменные
CFLAGS = -std=c99 -Wall -Werror -pedantic -ggdb -c
S = ./src/
O = ./out/
I = ./inc/
# $@ - цель
# $^ - список зависимостей
# $< - первая зависимость
.PHONY: clean
app.exe: $(O)main.o $(O)inout.o $(O)task.o
	gcc -o $@ $^
unit: unit_tests.exe
	./$^
unit_tests.exe: $(O)check_main.o $(O)task.o $(O)inout.o
	gcc -o $@ $^ -lcheck
$(O)check_main.o: ./unit_tests/check_main.c $(I)task.h $(I)error_codes.h $(I)inout.h
	gcc $(CFLAGS) $< -o $@
$(O)main.o: $(S)main.c $(I)task.h $(I)inout.h $(I)error_codes.h
	gcc $(CFLAGS) $< -o $@
$(O)task.o: $(S)task.c $(I)task.h $(I)error_codes.h
	gcc $(CFLAGS) $< -o $@
$(O)inout.o: $(S)inout.c $(I)inout.h $(I)task.h $(I)error_codes.h
	gcc $(CFLAGS) $< -o $@
clean:
	rm -f $(O)*.o *.exe