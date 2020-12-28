import ctypes
from tkinter import *

lib = ctypes.CDLL('D:\\c\\iu7-cprog-labs-2020-korotychmikhail\\lab_12_01_02\\lib.dll')

def shifting():
	a = array1.get().split()
	a = [int(a[i]) for i in range(len(a))]
	n = len(a)
	arr = (ctypes.c_int * n)(*a)
	shift = lib.shift
	shift.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int)
	shift.restypes = None
	shift(arr, n, int(position.get()))
	shift_result_entry.insert(0, list(arr))

def search():
	a = array2.get().split()
	a = [int(a[i]) for i in range(len(a))]
	n = len(a)
	arr1 = (ctypes.c_int * n)(*a)
	arr2 = (ctypes.c_int * n)()
	square_numbers = lib.square_numbers
	square_numbers.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.POINTER(ctypes.c_int))
	square_numbers.restypes = None
	square_numbers(arr1, n, arr2)
	arr2 = list(arr2)
	for i in range(len(arr2)):
		if not arr2[i]:
			arr2.remove(arr2[i])
	square_result_entry.insert(0, list(arr2))


main_window = Tk()
main_window.title('ЛР 12')
main_window.geometry('700x700')

header1 = Label(text = 'СДВИГ МАССИВА')
header1.place(x = 250, y = 5)

shift_array_label = Label(text = 'Введите через пробел элементы целого массива:')
shift_array_label.place(x = 5, y = 25)
array1 = StringVar()
shift_array_entry = Entry(textvariable = array1)
shift_array_entry.place(x = 290, y = 25)

shift_position_label = Label(text = 'Введите количество позиций для сдвига влево:')
shift_position_label.place(x = 5, y = 50)
position = StringVar()
shift_position_entry = Entry(textvariable = position)
shift_position_entry.place(x = 290, y = 50)

arrow_label = Button(text = '-->', command = shifting)
arrow_label.place(x = 430, y = 40)

shift_result_entry = Entry()
shift_result_entry.place(x = 465, y = 40)

header1 = Label(text = 'ПОИСК ПОЛНЫХ КВАДРАТОВ МАССИВА')
header1.place(x = 220, y = 70)

square_array_label = Label(text = 'Введите через пробел элементы целого массива:')
square_array_label.place(x = 5, y = 90)
array2 = StringVar()
square_array_entry = Entry(textvariable = array2)
square_array_entry.place(x = 290, y = 90)

arrow_label = Button(text = '-->', command = search)
arrow_label.place(x = 430, y = 90)

square_result_entry = Entry()
square_result_entry.place(x = 465, y = 90)

main_window.mainloop()