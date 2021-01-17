#include <check.h>
#include <math.h>
#include <stdlib.h>
#include "../inc/task.h"
#include "../inc/inout.h"

int compare_matrix(int **matrix1, int rows1, int cols1, int **matrix2, int rows2, int cols2)
{
	if (rows1 != rows2 || cols1 != cols2)
		return 2;
	for (int i = 0; i < rows1; i++)
		for (int j = 0; j < cols1; j++)
			if (matrix1[i][j] != matrix2[i][j])
				return 1;
	return 0;
}

START_TEST(test_mult_not_compatible)
{
	FILE *file1 = fopen("func_tests\\in_1.txt", "r"), *file2 = fopen("func_tests\\in_2.txt", "r");
	int n, m, p, q;
	int **a = input(file1, &n, &m);
	int **b = input(file2, &p, &q);
	int **result = multiplication(a, n, m, b, p, q);
	fclose(file1);
	fclose(file2);
	ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_mult_ok)
{
	FILE *file1 = fopen("func_tests\\in_3.txt", "r"), *file2 = fopen("func_tests/in_4.txt", "r"), *file3 = fopen("func_tests\\in_5.txt", "r");
	int n, m, p, q, x, y;
	int **a = input(file1, &n, &m);
	int **b = input(file2, &p, &q);
	int **result = multiplication(a, n, m, b, p, q);
	int **true_result = input(file3, &x, &y);
	int error = compare_matrix(result, n, q, true_result, x, y);
	free_matrix(a, n);
	free_matrix(b, p);
	free_matrix(result, n);
	free_matrix(true_result, x);
	fclose(file1);
	fclose(file2);
	fclose(file3);
	ck_assert_int_eq(error, 0);
}

START_TEST(test_mult_single_matrix)
{
	FILE *file1 = fopen("func_tests\\in_6.txt", "r"), *file2 = fopen("func_tests\\in_7.txt", "r"), *file3 = fopen("func_tests\\in_8.txt", "r");
	int n, m, p, q, x, y;
	int **a = input(file1, &n, &m);
	int **b = input(file2, &p, &q);
	int **result = multiplication(a, n, m, b, p, q);
	int **true_result = input(file3, &x, &y);
	int error = compare_matrix(result, n, q, true_result, x, y);
	free_matrix(a, n);
	free_matrix(b, p);
	free_matrix(result, n);
	free_matrix(true_result, x);
	fclose(file1);
	fclose(file2);
	fclose(file3);
	ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_remove_columns)
{
	FILE *file1 = fopen("func_tests\\in_9.txt", "r"), *file2 = fopen("func_tests\\in_10.txt", "r");
	int n, m, p, q;
	int **a = input(file1, &n, &m);
	a = remove_by_number(a, &n, &m, 2);
	int **true_result = input(file2, &p, &q);
	int error = compare_matrix(a, n, m, true_result, p, q);
	free_matrix(a, n);
	free_matrix(true_result, p);
	fclose(file1);
	fclose(file2);
	ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_remove_strings)
{
	FILE *file1 = fopen("func_tests\\in_11.txt", "r"), *file2 = fopen("func_tests\\in_12.txt", "r");
	int n, m, p, q;
	int **a = input(file1, &n, &m);
	a = remove_by_number(a, &n, &m, 3);
	int **true_result = input(file2, &p, &q);
	int error = compare_matrix(a, n, m, true_result, p, q);
	free_matrix(a, n);
	free_matrix(true_result, p);
	fclose(file1);
	fclose(file2);
	ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_low_average_ok)
{
	FILE *file1 = fopen("func_tests\\in_6.txt", "r");
	int n, m;
	int **a = input(file1, &n, &m);
	int result1 = counting_low_average(a, 2, 0);
	if (result1 != 3)
	{
		free_matrix(a, n);
		ck_assert_int_eq(3, result1);
	}
	int result2 = counting_low_average(a, 2, 1);
	if (result2)
	{
		free_matrix(a, n);
		ck_assert_int_eq(0, result2);
	}
	free_matrix(a, n);
	return;
}
END_TEST

START_TEST(test_low_average_zeroes_and_negatives)
{
	FILE *file1 = fopen("func_tests\\in_13.txt", "r");
	int n, m;
	int **a = input(file1, &n, &m);
	int result1 = counting_low_average(a, 2, 0);
	if (result1)
	{
		free_matrix(a, n);
		ck_assert_int_eq(0, result1);
	}
	int result2 = counting_low_average(a, 2, 1);
	if (result2 != -4)
	{
		free_matrix(a, n);
		ck_assert_int_eq(-4, result2);
	}
	free_matrix(a, n);
	return;
}
END_TEST

START_TEST(test_add_str_stb)
{
	FILE *file1 = fopen("func_tests\\in_14.txt", "r"), *file2 = fopen("func_tests\\in_15.txt", "r");
	int n, m, p, q;
	int **a = input(file1, &n, &m);
	a = add_by_number(a, &n, &m, 3);
	int **true_result = input(file2, &p, &q);
	int error = compare_matrix(a, n, m, true_result, p, q);
	free_matrix(a, n);
	free_matrix(true_result, p);
	ck_assert_int_eq(error, 0);
}
END_TEST

Suite *test_func_suite(void)
{
	Suite *s = suite_create("test_func");
	TCase *tc_mult = tcase_create("mult");
	tcase_add_test(tc_mult, test_mult_not_compatible);
	tcase_add_test(tc_mult, test_mult_ok);
	tcase_add_test(tc_mult, test_mult_single_matrix);
	suite_add_tcase(s, tc_mult);
	TCase *tc_dynamic = tcase_create("dynamic");
	tcase_add_test(tc_dynamic, test_remove_strings);
	tcase_add_test(tc_dynamic, test_remove_columns);
	tcase_add_test(tc_dynamic, test_add_str_stb);
	suite_add_tcase(s, tc_dynamic);
	TCase *tc_math = tcase_create("math");
	tcase_add_test(tc_math, test_low_average_ok);
	tcase_add_test(tc_math, test_low_average_zeroes_and_negatives);
	suite_add_tcase(s, tc_math);
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