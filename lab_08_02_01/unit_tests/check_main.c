#include <check.h>
#include <math.h>
#include "../inc/task.h"
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
	free_matrix(a, 2);
	free_matrix(b, 2);
	ck_assert_ptr_null(result);
}
END_TEST
START_TEST(test_mult_ok)
{
	int **a = allocate_matrix(2, 3);
	a[0][0] = 2; a[0][1] = -3, a[0][2] = 1;
	a[1][0] = 5; a[1][1] = 4; a[1][2] = -2;
	int **b = allocate_matrix(3, 2);
	b[0][0] = -7; b[0][1] = 5;
	b[1][0] = 2; b[1][1] = -1;
	b[2][0] = 4; b[2][1] = 3;
	int **result = multiplication(a, 2, 3, b, 3, 2);
	int **true_result = allocate_matrix(2, 2);
	true_result[0][0] = -16; true_result[0][1] = 16;
	true_result[1][0] = -35; true_result[1][1] = 15;
	int error = compare_matrix(result, 2, 2, true_result, 2, 2);
	free_matrix(a, 2);
	free_matrix(b, 3);
	free_matrix(result, 2);
	free_matrix(true_result, 2);
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
Suite *test_func_suite(void)
{
	Suite *s = suite_create("test_func");
	TCase *tc_mult = tcase_create("mult");
	tcase_add_test(tc_mult, test_mult_not_compatible);
	tcase_add_test(tc_mult, test_mult_ok);
	tcase_add_test(tc_mult, test_mult_single_matrix);
	suite_add_tcase(s, tc_mult);
	/*TCase *tc_sort = tcase_create("sort");
	tcase_add_test(tc_sort, test_sort_void_base);
	suite_add_tcase(s, tc_sort);*/
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