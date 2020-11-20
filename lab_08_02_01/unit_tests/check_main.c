#include <check.h>
#include <math.h>
#include <stdlib.h>
#include "../inc/task.h"
#include "../inc/inout.h"
void fill(int **matrix, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix[i][j] = i + j;
}
int compare_matrix(int **matrix1, int rows1, int cols1, int **matrix2, int rows2, int cols2)
{
	if (rows1 != rows2 || cols1 != cols2)
		return 1;
	for (int i = 0; i < rows1; i++)
		for (int j = 0; j < cols1; j++)
			if (matrix1[i][j] != matrix2[i][j])
				return 1;
	return 0;
}
START_TEST(test_mult_not_compatible)
{
	int **a = allocate_matrix(2, 3);
	fill(a, 2, 3);
	int **b = allocate_matrix(2, 4);
	fill(b, 2, 4);
	int **result = multiplication(a, 2, 3, b, 2, 4);
	ck_assert_ptr_null(result);
}
END_TEST
START_TEST(test_mult_ok)
{
	int **a = allocate_matrix(3, 3);
	a[0][0] = -4; a[0][1] = 0, a[0][2] = -4;
	a[1][0] = 7; a[1][1] = 3; a[1][2] = 3;
	a[2][0] = 1; a[2][1] = 1; a[2][2] = 1;
	int **b = allocate_matrix(3, 3);
	b[0][0] = 4; b[0][1] = 7; b[0][2] = 4;
	b[1][0] = 3; b[1][1] = 5; b[1][2] = 0;
	b[2][0] = 1; b[2][1] = 1; b[2][2] = 1;
	int **result = multiplication(a, 3, 3, b, 3, 3);
	int **true_result = allocate_matrix(3, 3);
	true_result[0][0] = -20; true_result[0][1] = -32; true_result[0][2] = -20;
	true_result[1][0] = 40; true_result[1][1] = 67; true_result[1][2] = 31;
	true_result[2][0] = 8; true_result[2][1] = 13; true_result[2][2] = 5;
	int error = compare_matrix(result, 3, 3, true_result, 3, 3);
	free_matrix(a, 3);
	free_matrix(b, 3);
	free_matrix(result, 3);
	free_matrix(true_result, 3);
	ck_assert_int_eq(error, 0);
}
START_TEST(test_mult_single_matrix)
{
	int **a = allocate_matrix(2, 2);
	a[0][0] = 2; a[0][1] = -3;
	a[1][0] = 5; a[1][1] = 4;
	int **b = allocate_matrix(2, 2);
	b[0][0] = 1; b[0][1] = 0;
	b[1][0] = 0; b[1][1] = 1;
	int **result = multiplication(a, 2, 2, b, 2, 2);
	int **true_result = allocate_matrix(2, 2);
	true_result[0][0] = 2; true_result[0][1] = -3;
	true_result[1][0] = 5; true_result[1][1] = 4;
	int error = compare_matrix(result, 2, 2, true_result, 2, 2);
	free_matrix(a, 2);
	free_matrix(b, 2);
	free_matrix(result, 2);
	free_matrix(true_result, 2);
	ck_assert_int_eq(error, 0);
}
END_TEST
START_TEST(test_remove_columns)
{
	int n = 2, m = 3;
	int **a = allocate_matrix(n, m);
	a[0][0] = 4; a[0][1] = 7; a[0][2] = 1;
	a[1][0] = 3; a[1][1] = 2; a[1][2] = 7;
	a = remove_by_number(a, &n, &m, 2);
	int **true_result = allocate_matrix(2, 2);
	true_result[0][0] = 4; true_result[0][1] = 7;
	true_result[1][0] = 3; true_result[1][1] = 2;
	int error = compare_matrix(a, n, m, true_result, 2, 2);
	free_matrix(a, n);
	free_matrix(true_result, 2);
	ck_assert_int_eq(error, 0);
}
END_TEST
/*int **allocate_matrix_dop(int str, int stb)
{
	int **matrix = calloc(str, sizeof(int *));
	if (!matrix)
		return NULL;
	matrix[0] = calloc(stb, sizeof(int));
	matrix[1] = calloc(stb, sizeof(int));
	matrix[2] = calloc(stb, sizeof(int));
	matrix[3] = calloc(stb, sizeof(int));
	matrix[4] = calloc(stb, sizeof(int));
	return matrix;
}*/
START_TEST(test_remove_strings)
{
	int n = 5, m = 3;
	int **a = allocate_matrix(n, m);
	a[0][0] = 0; a[0][1] = 2; a[0][2] = 9;
	a[1][0] = 1; a[1][1] = 2; a[1][2] = 2;
	a[2][0] = 3; a[2][1] = 3; a[2][2] = 3;
	a[3][0] = 8; a[3][1] = 8; a[3][2] = 2;
	a[4][0] = 1; a[4][1] = 8; a[4][2] = 3;
	a = remove_by_number(a, &n, &m, 3);
	int **true_result = allocate_matrix(3, 3);
	true_result[0][0] = 1; true_result[0][1] = 2; true_result[0][2] = 2;
	true_result[1][0] = 3; true_result[1][1] = 3; true_result[1][2] = 3;
	true_result[2][0] = 8; true_result[2][1] = 8; true_result[2][2] = 2;
	int error = compare_matrix(a, n, m, true_result, 3, 3);
	free_matrix(a, n);
	free_matrix(true_result, 3);
	ck_assert_int_eq(error, 0);
}
END_TEST
START_TEST(test_low_average_ok)
{
	int **a = allocate_matrix(3, 2);
	a[0][0] = 2; a[0][1] = -3;
	a[1][0] = 5; a[1][1] = 4;
	int result1 = counting_low_average(a, 3, 0);
	if (result1 != 3)
	{
		free_matrix(a, 3);
		ck_assert_int_eq(3, result1);
	}
	int result2 = counting_low_average(a, 3, 1);
	if (result2)
	{
		free_matrix(a, 3);
		ck_assert_int_eq(0, result2);
	}
	free_matrix(a, 3);
	return;
}
END_TEST
START_TEST(test_low_average_zeroes_and_negatives)
{
	int **a = allocate_matrix(3, 2);
	a[0][0] = 0; a[0][1] = -3;
	a[1][0] = 0; a[1][1] = -4;
	int result1 = counting_low_average(a, 3, 0);
	if (result1)
	{
		free_matrix(a, 3);
		ck_assert_int_eq(0, result1);
	}
	int result2 = counting_low_average(a, 3, 1);
	if (result2 != -4)
	{
		free_matrix(a, 3);
		ck_assert_int_eq(-4, result2);
	}
	free_matrix(a, 3);
	return;
}
END_TEST
START_TEST(test_add_str_stb)
{
	int n = 2, m = 2;
	int **a = allocate_matrix(n, m);
	a[0][0] = 4; a[0][1] = 1;
	a[1][0] = 3; a[1][1] = 7;
	a = add_by_number(a, &n, &m, 3);
	int **true_result = allocate_matrix(3, 3);
	true_result[0][0] = 4; true_result[0][1] = 1; true_result[0][2] = 1;
	true_result[1][0] = 3; true_result[1][1] = 7; true_result[1][2] = 3;
	true_result[2][0] = 3; true_result[2][1] = 4; true_result[2][2] = 3;
	int error = compare_matrix(a, n, m, true_result, 3, 3);
	free_matrix(a, n);
	free_matrix(true_result, 3);
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