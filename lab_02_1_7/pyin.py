from random import randint
with open('in_2.txt', 'w') as file:
    file.write('100000\n')
    for i in range(100000):
        file.write(str(randint(1, 1000)) + '\n')
