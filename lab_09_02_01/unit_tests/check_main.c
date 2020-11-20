#include <check.h>
#include <string.h>
#include "../inc/error_codes.h"
#include "../inc/functions.h"
START_TEST(test_sort_ok)
{
	struct information stuff[] =
	{
		{"box", 10, 2},
		{"can", 10, 5}
	};
	sort_stuff(stuff, 2);
	struct information result[] = 
	{
		{"can", 10.000000, 5.000000},
		{"box", 10.000000, 2.000000}
	};
	ck_assert_mem_eq(stuff, result, 2 * sizeof(struct information));
}
START_TEST(test_sort_single_structure)
{
	struct information stuff =
	{
		.name = "can",
		.weight = 44,
		.volume = 40
	};
	sort_stuff(&stuff, 1);
	struct information result =
	{
		.name = "can",
		.weight = 44,
		.volume = 40
	};
	ck_assert_mem_eq(&stuff, &result, sizeof(struct information));
}
END_TEST
START_TEST(test_sort_equal_records)
{
	struct information stuff[] =
	{
		{"box", 87, 45},
		{"box", 87, 45},
		{"box", 87, 45}
	};
	sort_stuff(stuff, 3);
	struct information result[] =
	{
		{"box", 87, 45},
		{"box", 87, 45},
		{"box", 87, 45}
	};
	ck_assert_mem_eq(stuff, result, sizeof(struct information));
}
END_TEST
Suite *test_func_suite(void)
{
	Suite *s = suite_create("test_func");
	TCase *tc_sort = tcase_create("sort");
	tcase_add_test(tc_sort, test_sort_ok);
	tcase_add_test(tc_sort, test_sort_single_structure);
	tcase_add_test(tc_sort, test_sort_equal_records);
	suite_add_tcase(s, tc_sort);
	/*TCase *tc_dynamic = tcase_create("find");
	tcase_add_test(tc_dynamic, test_remove_strings);
	tcase_add_test(tc_dynamic, test_remove_columns);
	tcase_add_test(tc_dynamic, test_add_str_stb);
	suite_add_tcase(s, tc_dynamic);
	TCase *tc_math = tcase_create("math");
	tcase_add_test(tc_math, test_low_average_ok);
	tcase_add_test(tc_math, test_low_average_zeroes_and_negatives);
	suite_add_tcase(s, tc_math);*/
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