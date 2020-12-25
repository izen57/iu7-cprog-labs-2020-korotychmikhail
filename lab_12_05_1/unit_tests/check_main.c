#include <check.h>
#include <stdlib.h>
#include "../inc/key.h"
#include "../inc/mysort.h"

int compare_arrs(int *arr1, int len1, int *arr2, int len2)
{
	if (len1 != len2)
		return 1;
	for (int i = 0; i < len1; i++)
		if (arr1[i] != arr2[i])
			return 1;
	return 0;
}

START_TEST(test_key_four_null_pointers)
{
	int rc = key(NULL, NULL, NULL, NULL);
	ck_assert_int_eq(rc, 4);
}
END_TEST

START_TEST(test_key_three_null_pointers)
{
	int *arr = calloc(5, sizeof(int));
	int rc = key(arr, NULL, NULL, NULL);
	free(arr);
	ck_assert_int_eq(rc, 4);
}
END_TEST

START_TEST(test_key_two_null_pointers)
{
	int *arr = calloc(5, sizeof(int));
	int *end = arr + 5;
	int rc = key(arr, end, NULL, NULL);
	free(arr);
	ck_assert_int_eq(rc, 4);
}
END_TEST

START_TEST(test_key_one_null_pointer)
{
	int *arr = calloc(5, sizeof(int));
	int *end = arr + 5;
	int *newarr;
	int rc = key(arr, end, &newarr, NULL);
	free(arr);
	ck_assert_int_eq(rc, 4);
}
END_TEST

START_TEST(test_key_all_pointers)
{
	int arr[] = {89, 5, 7, 9, 7};
	int *end = arr + 5;
	int *newarr = end + 1, *endnewarr = newarr;
	int count = counting_elems(arr, end);
	create_arr(&newarr, count);
	key(arr, end, &newarr, &endnewarr);
	int len = endnewarr - newarr;
	int arr1[] = {89, 9};
	int rc = compare_arrs(newarr, len, arr1, 2);
	free(newarr);
	ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_key_old_equal_pointers)
{
	int *arr = calloc(5, sizeof(int));
	int *end = arr;
	int *newarr;
	int rc = key(arr, end, &newarr, &newarr);
	free(arr);
	ck_assert_int_eq(rc, 4);
}
END_TEST

START_TEST(test_key_empty_result)
{
	int arr[] = {1, 5, 7, 9, 11, 457};
	int *end = arr + 6;
	int *newarr;
	int count = counting_elems(arr, end);
	create_arr(&newarr, count);
	int rc = key(arr, end, &newarr, &newarr);
	ck_assert_int_eq(rc, 5);
}
END_TEST

START_TEST(test_sort_void_base)
{
	int rc = mysort(NULL, 7, sizeof(int), &compare);
	ck_assert_int_eq(rc, 5);
}
END_TEST

START_TEST(test_sort_void_num)
{
	int *arr = calloc(4, sizeof(int));
	int rc = mysort(arr, 0, sizeof(int), &compare);
	free(arr);
	ck_assert_int_eq(rc, 5);
}
END_TEST

START_TEST(test_sort_ok)
{
	int arr[] = {3, 58, 1098, 32, 1, 11, 90};
	mysort(arr, 7, sizeof(int), &compare);
	int newarr[] = {1, 3, 11, 32, 58, 90, 1098};
	int rc = compare_arrs(arr, 7, newarr, 7);
	ck_assert_int_eq(rc, 0);
}
END_TEST

Suite *test_func_suite(void)
{
	Suite *s = suite_create("test_func");
	TCase *tc_key = tcase_create("key");
	tcase_add_test(tc_key, test_key_four_null_pointers);
	tcase_add_test(tc_key, test_key_three_null_pointers);
	tcase_add_test(tc_key, test_key_two_null_pointers);
	tcase_add_test(tc_key, test_key_one_null_pointer);
	tcase_add_test(tc_key, test_key_all_pointers);
	tcase_add_test(tc_key, test_key_empty_result);
	tcase_add_test(tc_key, test_key_old_equal_pointers);
	suite_add_tcase(s, tc_key);
	TCase *tc_sort = tcase_create("sort");
	tcase_add_test(tc_sort, test_sort_void_base);
	tcase_add_test(tc_sort, test_sort_void_num);
	tcase_add_test(tc_sort, test_sort_ok);
	suite_add_tcase(s, tc_sort);
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