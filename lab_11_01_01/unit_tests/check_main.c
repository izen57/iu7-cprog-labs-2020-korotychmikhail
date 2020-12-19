#include <check.h>
#include <stdio.h>
#include "../inc/my_snprintf.h"

START_TEST(test_text)
{
	char buffer1[13], buffer2[13];
	ck_assert_int_eq(my_snprintf(buffer1, 13, "I'm coding..."), snprintf(buffer2, 13, "I'm coding..."));
}
END_TEST

START_TEST(test_void_text)
{
	char buffer1[13], buffer2[13];
	ck_assert_int_eq(my_snprintf(buffer1, 0, ""), snprintf(buffer2, 0, ""));
}
END_TEST

Suite *test_func_suite(void)
{
	Suite *s = suite_create("test_func");
	TCase *tc_text = tcase_create("text");
	tcase_add_test(tc_text, test_text);
	tcase_add_test(tc_text, test_void_text);
	suite_add_tcase(s, tc_text);
	/*TCase *tc_ddx = tcase_create("ddx");
	tcase_add_test(tc_ddx, test_ddx);
	suite_add_tcase(s, tc_ddx);
	TCase *tc_sum = tcase_create("sum");
	tcase_add_test(tc_sum, test_sum);
	suite_add_tcase(s, tc_sum);
	TCase *tc_dvd = tcase_create("dvd");
	tcase_add_test(tc_dvd, test_dvd);
	suite_add_tcase(s, tc_dvd);*/
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