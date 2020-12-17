// вариант 2
#include <stdio.h>
#include <stdlib.h>

struct Marks
{
	int *marks;
	struct Marks *previous;
	struct Marks *next;
};

struct Student
{
	char *name;
	int age;
	void *data;
	struct Student *previous;
	struct Student *next;
};

struct Marks *marks_create(int *marks)
{
	struct Marks *node = malloc(sizeof(struct Marks));
	if (node)
	{
		node->marks = marks;
		node->next = NULL;
		node->previous = NULL;
	}
	return node;
}

struct Student *student_add_end(struct Student *head, struct Student *student)
{
	if (!head)
		return student;
	struct Student *current = head;
	for (; current->next; current = current->next);
	current->next = student;
	return head;
}

struct Student *marks_add_end(struct Marks *head, struct Marks *node)
{
	if (!head)
		return node;
	struct Student *current = head;
	for (; current->next; current = current->next)
	{
		current->previous = current;
		struct Marks *peviuos = current;
	}
	current->next = node;
	return head;
}

struct Student *student_create(char *name, int age, struct Marks *head_marks)
{
	struct Student *student = malloc(sizeof(struct Student));
	if (student)
	{
		student->name = name;
		student->age = age;
		student->data = head_marks;
		student->next = NULL;
		student->previous = NULL;
	}
	return student;
}

void list_free_all(struct Student *head)
{
	for (struct Node *next; head; head = next)
	{
		next = head->next;
		free(head->data);
		free(head->name);
		free(head);
	}
}

char *input(FILE *file)
{
	int capacity = 1, size = 0;
	char *s = malloc(capacity * sizeof(char));
	for (char c = fgetc(file); c != '\n' && c != EOF; c = fgetc(file))
	{
		s[size++] = c;
		if (size >= capacity)
		{
			capacity *= 2;
			s = realloc(s, capacity * sizeof(char));
			if (!s)
				return NULL;
		}
	}
	s[size] = '\0';
	return s;
}

void print_students(struct Student *student_head, struct Marks *marks_head, int n)
{
	for (struct Student *current = student_head; current->next; current = current->next)
	{
		printf("Имя студента: %d;\nВозраст студента: %d;\n", current->name, current->age);
		for (struct Marks *current_marks = marks_head; current_marks->next; current_marks = current_marks->next)
			for (int i = 0; i < n; i++)
			{
				printf("%d ", current_marks->marks[i]);
				printf("\n");
			}
	}
}

int main(void)
{
	int choice = -1, error = 0;
	struct Student *student_head = NULL;
	struct Marks *marks_head = NULL;
	while (choice)
	{
		printf("Выберите дейтсвие:\n0) Выйти;\n1) Добавить элемент в конец;\n2) Сортировать список;\n3) Вывести список.\n");
		scanf("%d\n", &choice);
		switch (choice)
		{
			case 1:
				printf("Введите имя студента: ");
				char *name = input(stdin);
				printf("\nВведите возраст студента: ");
				int age = 0;
				scanf("%d", &age);
				int *marks;
				static int n = 0;
				printf("\nВведите количество оценок студента: ");
				scanf("%d", &n);
				printf("\nВведите оценки студента, каждую с новой строки: ");
				for (int i = 0; i < n; i++)
					scanf("%d", &marks[i]);
				struct Marks *node = marks_create(marks);
				struct Marks *marks_head = marks_add_end(marks_head, node);
				struct Student *student = student_create(name, age, marks_head);
				struct Student *student_head = student_add_end(student_head, student);
				break;
			case 3:
				print_students(student_head, marks_head, n);
				break;
			default:
				break;
		}
	}
	return error;
}