#include <check.h>
#include "../inc/structure.h"
#include "../inc/inout.h"
#include "../inc/list.h"

START_TEST(test_val)
{
	struct node *head = node_create(4, 2);
	struct node *current = head;
	current = current->next = node_create(1, 0);
	int value = val(head, 7);
	list_free_all(head);
	ck_assert_int_eq(value, 197);
}
END_TEST

START_TEST(test_ddx)
{
	struct node *head = node_create(4, 2);
	struct node *current = head;
	current = current->next = node_create(12, 1);
	current = current->next = node_create(1, 0);
	struct node *result = NULL;
	dpdx(head, &result);
	current = result;
	ck_assert_int_eq(current->coefficient, 8);
	ck_assert_int_eq(current->degree, 1);
	current = current->next;
	ck_assert_int_eq(current->coefficient, 12);
	ck_assert_int_eq(current->degree, 0);
	list_free_all(head);
	list_free_all(result);
}
END_TEST

START_TEST(test_sum)
{
	struct node *head1 = node_create(4, 2);
	struct node *current = head1;
	current = current->next = node_create(12, 1);
	current = current->next = node_create(1, 0);
	struct node *head2 = node_create(8, 1);
	current = head2;
	current = current->next = node_create(12, 0);
	struct node *result = NULL;
	sum(head1, head2, &result);
	current = result;
	ck_assert_int_eq(current->coefficient, 4);
	ck_assert_int_eq(current->degree, 2);
	current = current->next;
	ck_assert_int_eq(current->coefficient, 20);
	ck_assert_int_eq(current->degree, 1);
	current = current->next;
	ck_assert_int_eq(current->coefficient, 13);
	ck_assert_int_eq(current->degree, 0);
	list_free_all(head1);
	list_free_all(head2);
	list_free_all(result);
}
END_TEST

START_TEST(test_dvd)
{
	struct node *head = node_create(4, 2);
	struct node *current = head;
	current = current->next = node_create(12, 1);
	current = current->next = node_create(1, 0);
	struct node *even_head = NULL, *odd_head = NULL;
	dvd(head, &even_head, &odd_head);
	current = even_head;
	ck_assert_int_eq(current->coefficient, 4);
	ck_assert_int_eq(current->degree, 2);
	current = current->next;
	ck_assert_int_eq(current->coefficient, 1);
	ck_assert_int_eq(current->degree, 0);
	current = odd_head;
	ck_assert_int_eq(current->coefficient, 12);
	ck_assert_int_eq(current->degree, 1);
	list_free_all(head);
	list_free_all(even_head);
	list_free_all(odd_head);
}
END_TEST

Suite *test_func_suite(void)
{
	Suite *s = suite_create("test_func");
	TCase *tc_val = tcase_create("val");
	tcase_add_test(tc_val, test_val);
	suite_add_tcase(s, tc_val);
	TCase *tc_ddx = tcase_create("ddx");
	tcase_add_test(tc_ddx, test_ddx);
	suite_add_tcase(s, tc_ddx);
	TCase *tc_sum = tcase_create("sum");
	tcase_add_test(tc_sum, test_sum);
	suite_add_tcase(s, tc_sum);
	TCase *tc_dvd = tcase_create("dvd");
	tcase_add_test(tc_dvd, test_dvd);
	suite_add_tcase(s, tc_dvd);
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