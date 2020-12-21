#include <check.h>
#include <stdio.h>
#include "../inc/my_snprintf.h"

START_TEST(test_text_buffer_more_n)
{
	char buffer1[13], buffer2[13];
	ck_assert_int_eq(my_snprintf(buffer1, 10, "I'm coding..."), snprintf(buffer2, 10, "I'm coding..."));
}
END_TEST

START_TEST(test_void_text)
{
	char buffer1[13], buffer2[13];
	ck_assert_int_eq(my_snprintf(buffer1, 0, ""), snprintf(buffer2, 0, ""));
}
END_TEST

START_TEST(test_text_buffer_less_n)
{
	char buffer1[10], buffer2[10];
	ck_assert_int_eq(my_snprintf(buffer1, 13, "I'm coding..."), snprintf(buffer2, 13, "I'm coding..."));
}
END_TEST

START_TEST(test_text_with_percent)
{
	char buffer1[14], buffer2[14];
	ck_assert_int_eq(my_snprintf(buffer1, 14, "I'm coding%%..."), snprintf(buffer2, 14, "I'm coding%%..."));
}
END_TEST

Suite *test_func_suite(void)
{
	Suite *s = suite_create("test_func");
	TCase *tc_text = tcase_create("text");
	tcase_add_test(tc_text, test_text_buffer_less_n);
	tcase_add_test(tc_text, test_text_buffer_more_n);
	tcase_add_test(tc_text, test_void_text);
	tcase_add_test(tc_text, test_text_with_percent);
	suite_add_tcase(s, tc_text);
	
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