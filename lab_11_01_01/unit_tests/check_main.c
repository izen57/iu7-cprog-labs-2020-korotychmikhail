#include <check.h>
#include <stdio.h>
#include <stdint.h>
#include "../inc/my_snprintf.h"

START_TEST(test_text_buffer_more_n)
{
	char buffer1[13], buffer2[13];
	ck_assert_int_eq(my_snprintf(buffer1, 10, "I'm coding..."), snprintf(buffer2, 10, "I'm coding..."));
}
END_TEST

START_TEST(test_void_text)
{
	char buffer1[13], buffer2[13],  string1[2] = "", string2[2] = "";
	ck_assert_int_eq(my_snprintf(buffer1, 0, string1), snprintf(buffer2, 0, string2));
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

START_TEST(test_i_specfiers_without_spaces)
{
	int a = 3, b = 56, c = -8, d = 3, e = 56, f = -8;
	char buffer1[3], buffer2[3];
	ck_assert_int_eq(my_snprintf(buffer1, 3, "%i%i%i", a, b, c), snprintf(buffer2, 3, "%i%i%i", d, e, f));
}
END_TEST

START_TEST(test_i_wrong_specifiers)
{
	int a = 3, b = 56.2, c = -8, d = 3, e = 56.2, f = -8;
	char buffer1[3], buffer2[3];
	ck_assert_int_eq(my_snprintf(buffer1, 3, "%i%i%i", a, b, c), snprintf(buffer2, 3, "%i%i%i", d, e, f));
}
END_TEST

START_TEST(test_i_with_spaces)
{
	int a = 3, b = 6, c = 8, d = 3, e = 5, f = 8;
	char buffer1[3], buffer2[3];
	ck_assert_int_eq(my_snprintf(buffer1, 3, "% i% i% i", a, b, c), snprintf(buffer2, 3, "% i% i% i", d, e, f));
}
END_TEST

START_TEST(test_li_min)
{
	char buffer1[2], buffer2[2];
	ck_assert_int_eq(my_snprintf(buffer1, 2, "%lli", INTMAX_MIN), snprintf(buffer2, 2, "%lli", INTMAX_MIN));
}
END_TEST

START_TEST(test_li_max)
{
	char buffer1[2], buffer2[2];
	ck_assert_int_eq(my_snprintf(buffer1, 2, "%lli", INTMAX_MAX), snprintf(buffer2, 2, "%lli", INTMAX_MAX));
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
	TCase *tc_i = tcase_create("i");
	tcase_add_test(tc_i, test_i_specfiers_without_spaces);
	tcase_add_test(tc_i, test_i_wrong_specifiers);
	tcase_add_test(tc_i, test_i_with_spaces);
	TCase *tc_li = tcase_create("li");
	tcase_add_test(tc_li, test_li_min);
	tcase_add_test(tc_li, test_li_max);
	suite_add_tcase(s, tc_li);
	
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