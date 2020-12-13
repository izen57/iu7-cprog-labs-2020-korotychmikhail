#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "../inc/error_codes.h"
#include "../inc/inout.h"
#include "../inc/list.h"
#include "../inc/structure.h"

int compare_lists(node_t *head1, node_t *head2)
{
	int error = SUCCESS;
	for (node_t *current1 = head1, *current2 = head2; current1 && current2; current1 = current1->next, current2 = current2->next)
		if (comparator(current1->data, current2->data))
		{
			error = NO_RESULT;
			break;
		}
	return error;
}

START_TEST(test_pop_front)
{
	node_t *head1 = NULL, *head2 = NULL;
	FILE *in_file = fopen("..\\func_tests\\in.txt", "r");
	int error = read_file(in_file, &head1);
	void *data = pop_front(&head1);
	FILE *out_file = fopen("..\\func_tests\\pop_front_out.txt", "r");
	error = read_file(out_file, &head2);
	error = compare_lists(head1, head2);
	list_free_all(head1);
	list_free_all(head2);
	ck_assert_mem_eq(data, (void *) "Moscow", strlen("Moscow"));
	ck_assert_int_eq(error, SUCCESS);
}
END_TEST

START_TEST(test_find_null)
{
	node_t *head = NULL;
	FILE *in_file = fopen("..\\func_tests\\in.txt", "r");
	int error = read_file(in_file, &head);
	void *data = "Rostov";
	node_t *result = find(head, data, comparator);
	list_free_all(head);
	ck_assert_int_eq(error, SUCCESS);
	ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_find_ok)
{
	node_t *head = NULL;
	FILE *in_file = fopen("..\\func_tests\\in.txt", "r");
	int error = read_file(in_file, &head);
	node_t *result = find(head, "Moscow", comparator);
	list_free_all(head);
	ck_assert_int_eq(error, SUCCESS);
	ck_assert_mem_eq(result, "Moscow", strlen("Moscow"));
}
END_TEST

START_TEST(test_copy_ok)
{
	node_t *head1 = NULL, *head2 = NULL;
	FILE *in_file = fopen("..\\func_tests\\in.txt", "r");
	int error = read_file(in_file, &head1);
	error = copy(head1, &head2);
	error = compare_lists(head1, head2);
	list_free_all(head1);
	list_free_all(head2);
	ck_assert_int_eq(error, SUCCESS);
}
END_TEST

Suite *test_func_suite(void)
{
	Suite *s = suite_create("test_func");
	TCase *tc_pop_front = tcase_create("pop_front");
	tcase_add_test(tc_pop_front, test_pop_front);
	suite_add_tcase(s, tc_pop_front);
	TCase *tc_find = tcase_create("find");
	tcase_add_test(tc_find, test_find_null);
	tcase_add_test(tc_find, test_find_ok);
	suite_add_tcase(s, tc_find);
	TCase *tc_copy = tcase_create("copy");
	tcase_add_test(tc_copy, test_copy_ok);
	suite_add_tcase(s, tc_copy);
	return s;
}

int main(void)
{
	int no_failed = 0;
	Suite *s = test_func_suite();
	SRunner *runner = srunner_create(s);
	srunner_run_all(runner, CK_VERBOSE);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);
	return !no_failed? 0 : 1;
}