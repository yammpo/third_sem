#include "pch.h"
#include "gtest\gtest.h"
#include "BD.h"

TEST(Constructor, Default) {
	Big_Decimal bd;
	ASSERT_EQ(bd.Get_n(), 2);
	ASSERT_EQ(bd.Get_Overflow(), false);
	ASSERT_EQ(bd.Get_Value(0), '0');
	ASSERT_EQ(bd.Get_Value(1), '0');
}
TEST(Long_To_Big_Decimal, Test_1) {
	Big_Decimal bd;
	long int l = -123456789;
	bd = bd.Long_To_Big_Decimal(l);
	ASSERT_EQ(bd.Get_n(), 10);
	ASSERT_EQ(bd.Get_Overflow(), false);
	ASSERT_EQ('9', bd.Get_Value(0));
	ASSERT_EQ('9', bd.Get_Value(9));
	ASSERT_EQ('8', bd.Get_Value(8));
	ASSERT_EQ('7', bd.Get_Value(7));
	ASSERT_EQ('6', bd.Get_Value(6));
	ASSERT_EQ('5', bd.Get_Value(5));
	ASSERT_EQ('4', bd.Get_Value(4));
	ASSERT_EQ('3', bd.Get_Value(3));
	ASSERT_EQ('2', bd.Get_Value(2));
	ASSERT_EQ('1', bd.Get_Value(1));
}
TEST(Long_To_Big_Decimal, Test_2) {
	Big_Decimal bd;
	long int l = 123456789;
	bd = bd.Long_To_Big_Decimal(l);
	ASSERT_EQ(bd.Get_n(), 10);
	ASSERT_EQ(bd.Get_Overflow(), false);
	ASSERT_EQ('0', bd.Get_Value(0));
	ASSERT_EQ('9', bd.Get_Value(9));
	ASSERT_EQ('8', bd.Get_Value(8));
	ASSERT_EQ('7', bd.Get_Value(7));
	ASSERT_EQ('6', bd.Get_Value(6));
	ASSERT_EQ('5', bd.Get_Value(5));
	ASSERT_EQ('4', bd.Get_Value(4));
	ASSERT_EQ('3', bd.Get_Value(3));
	ASSERT_EQ('2', bd.Get_Value(2));
	ASSERT_EQ('1', bd.Get_Value(1));
}
TEST(String_To_Big_Decimal, Test_1) {
	Big_Decimal bd;
	char buf[] = "12345";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	Big_Decimal tmp = bd.String_To_Big_Decimal(s);
	ASSERT_EQ(tmp.Get_n(), 6);
	ASSERT_EQ(tmp.Get_Overflow(), false);
	ASSERT_EQ('0', tmp.Get_Value(0));
	ASSERT_EQ('5', tmp.Get_Value(5));
	ASSERT_EQ('4', tmp.Get_Value(4));
	ASSERT_EQ('3', tmp.Get_Value(3));
	ASSERT_EQ('2', tmp.Get_Value(2));
	ASSERT_EQ('1', tmp.Get_Value(1));
}
TEST(String_To_Big_Decimal, Test_2) {
	Big_Decimal bd;
	char buf[] = "-12345";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	Big_Decimal tmp = bd.String_To_Big_Decimal(s);
	ASSERT_EQ(tmp.Get_n(), 6);
	ASSERT_EQ(tmp.Get_Overflow(), false);
	ASSERT_EQ('9', tmp.Get_Value(0));
	ASSERT_EQ('5', tmp.Get_Value(5));
	ASSERT_EQ('4', tmp.Get_Value(4));
	ASSERT_EQ('3', tmp.Get_Value(3));
	ASSERT_EQ('2', tmp.Get_Value(2));
	ASSERT_EQ('1', tmp.Get_Value(1));
}
TEST(String_To_Big_Decimal, Test_3) {
	Big_Decimal bd;
	char buf[] = "mephi";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	ASSERT_ANY_THROW(bd.String_To_Big_Decimal(s));
}
TEST(String_To_Big_Decimal, Test_4) {
	Big_Decimal bd;
	char buf[] = "111111111111111111111111111111111111111111111111111111111111111111111111111";
	char *s = (char*)malloc(76);
	*s = '\0';
	strcat(s, buf);
	Big_Decimal tmp = bd.String_To_Big_Decimal(s);
	ASSERT_EQ('0', tmp.Get_Value(0));
	for (int i = 1; i < N; i++) {
		ASSERT_EQ('1', tmp.Get_Value(i));
	}
	ASSERT_EQ(true, tmp.Get_Overflow());
}
TEST(Complement_Code, Test_1) {
	Big_Decimal bd;
	Big_Decimal tmp2;
	char buf[] = "-2345";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	Big_Decimal tmp = bd.String_To_Big_Decimal(s);
	tmp2 = tmp.Complement_Code(tmp);
	ASSERT_EQ(tmp2.Get_n(), 5);
	ASSERT_EQ(tmp2.Get_Overflow(), false);
	ASSERT_EQ('5', tmp2.Get_Value(4));
	ASSERT_EQ('5', tmp2.Get_Value(3));
	ASSERT_EQ('6', tmp2.Get_Value(2));
	ASSERT_EQ('7', tmp2.Get_Value(1));
	ASSERT_EQ('9', tmp2.Get_Value(0));
}
TEST(Complement_Code, Test_2) {
	Big_Decimal bd;
	Big_Decimal tmp2;
	char buf[] = "12345";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	Big_Decimal tmp = bd.String_To_Big_Decimal(s);
	tmp2 = tmp.Complement_Code(tmp);
	ASSERT_EQ('0', tmp2.Get_Value(0));
	ASSERT_EQ(tmp2.Get_n(), 6);
	ASSERT_EQ(tmp2.Get_Overflow(), false);
	ASSERT_EQ('5', tmp.Get_Value(5));
	ASSERT_EQ('4', tmp.Get_Value(4));
	ASSERT_EQ('3', tmp.Get_Value(3));
	ASSERT_EQ('2', tmp.Get_Value(2));
	ASSERT_EQ('1', tmp.Get_Value(1));
}
TEST(Addition, Test_1) {
	Big_Decimal bd;
	char buf[] = "12345";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	char buf1[] = "6789";
	char *t = (char*)malloc(5);
	*t = '\0';
	strcat(t, buf1);
	Big_Decimal tmp1 = bd.String_To_Big_Decimal(s);
	Big_Decimal tmp2 = bd.String_To_Big_Decimal(t);
	Big_Decimal res = tmp1 + tmp2;
	ASSERT_EQ(res.Get_n(), 6);
	ASSERT_EQ(res.Get_Overflow(), false);
	ASSERT_EQ('4', res.Get_Value(5));
	ASSERT_EQ('3', res.Get_Value(4));
	ASSERT_EQ('1', res.Get_Value(3));
	ASSERT_EQ('9', res.Get_Value(2));
	ASSERT_EQ('1', res.Get_Value(1));
	ASSERT_EQ('0', res.Get_Value(0));
}
TEST(Addition, Test_2) {
	Big_Decimal bd;
	char buf[] = "99999999999999999999999999999999999999999999999999999999999";
	char *s = (char*)malloc(60);
	*s = '\0';
	strcat(s, buf);
	char buf1[] = "2";
	char *t = (char*)malloc(2);
	*t = '\0';
	strcat(t, buf1);
	Big_Decimal tmp1 = bd.String_To_Big_Decimal(s);
	Big_Decimal tmp2 = bd.String_To_Big_Decimal(t);
	Big_Decimal res = tmp1 + tmp2;
	ASSERT_EQ(true, res.Get_Overflow());
	ASSERT_EQ(res.Get_n(), N);
	ASSERT_EQ('1', res.Get_Value(N-1));
	for (int i = 0; i < N - 1; i++) {
		ASSERT_EQ('0', res.Get_Value(i));
	}
}
TEST(Addition, Test_3) {
	Big_Decimal bd;
	char buf[] = "-12345";
	char *s = (char*)malloc(7);
	*s = '\0';
	strcat(s, buf);
	char buf1[] = "6789";
	char *t = (char*)malloc(5);
	*t = '\0';
	strcat(t, buf1);
	Big_Decimal tmp1 = bd.String_To_Big_Decimal(s);
	Big_Decimal tmp2 = bd.String_To_Big_Decimal(t);
	Big_Decimal res = tmp1 + tmp2;
	ASSERT_EQ(false, res.Get_Overflow());
	ASSERT_EQ(res.Get_n(), 6);
	ASSERT_EQ('6', res.Get_Value(5));
	ASSERT_EQ('5', res.Get_Value(4));
	ASSERT_EQ('5', res.Get_Value(3));
	ASSERT_EQ('5', res.Get_Value(2));
	ASSERT_EQ('0', res.Get_Value(1));
	ASSERT_EQ('9', res.Get_Value(0));
}
TEST(Addition, Test_4) {
	Big_Decimal bd;
	char buf[] = "12345";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	char buf1[] = "-6789";
	char *t = (char*)malloc(6);
	*t = '\0';
	strcat(t, buf1);
	Big_Decimal tmp1 = bd.String_To_Big_Decimal(s);
	Big_Decimal tmp2 = bd.String_To_Big_Decimal(t);
	Big_Decimal res = tmp1 + tmp2;
	ASSERT_EQ(false, res.Get_Overflow());
	ASSERT_EQ(res.Get_n(), 6);
	ASSERT_EQ('6', res.Get_Value(5));
	ASSERT_EQ('5', res.Get_Value(4));
	ASSERT_EQ('5', res.Get_Value(3));
	ASSERT_EQ('5', res.Get_Value(2));
	ASSERT_EQ('0', res.Get_Value(1));
	ASSERT_EQ('0', res.Get_Value(0));
}
TEST(Subtraction, Test_1) {
	Big_Decimal bd;
	char buf[] = "56789";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	char buf1[] = "4321";
	char *t = (char*)malloc(5);
	*t = '\0';
	strcat(t, buf1);
	Big_Decimal tmp1 = bd.String_To_Big_Decimal(s);
	Big_Decimal tmp2 = bd.String_To_Big_Decimal(t);
	Big_Decimal res = tmp1 - tmp2;
	ASSERT_EQ(false, res.Get_Overflow());
	ASSERT_EQ(res.Get_n(), 6);
	ASSERT_EQ('8', res.Get_Value(5));
	ASSERT_EQ('6', res.Get_Value(4));
	ASSERT_EQ('4', res.Get_Value(3));
	ASSERT_EQ('2', res.Get_Value(2));
	ASSERT_EQ('5', res.Get_Value(1));
	ASSERT_EQ('0', res.Get_Value(0));
}
TEST(Subtraction, Test_2) {
	Big_Decimal bd;
	char buf[] = "-99999999999999999999999999999999999999999999999999999999999";
	char *s = (char*)malloc(61);
	*s = '\0';
	strcat(s, buf);
	char buf1[] = "2";
	char *t = (char*)malloc(2);
	*t = '\0';
	strcat(t, buf1);
	Big_Decimal tmp1 = bd.String_To_Big_Decimal(s);
	Big_Decimal tmp2 = bd.String_To_Big_Decimal(t);
	Big_Decimal res = tmp1 - tmp2;
	ASSERT_EQ(res.Get_Overflow(), true);
	ASSERT_EQ(res.Get_n(), N);
	ASSERT_EQ('1', res.Get_Value(59));
	for (int i = 1; i < N - 1; i++) {
		ASSERT_EQ('0', res.Get_Value(i));
	}
	ASSERT_EQ('9', res.Get_Value(0));
}
TEST(Increase, Test_1) {
	Big_Decimal bd;
	char buf[] = "-12345";
	char *s = (char*)malloc(7);
	*s = '\0';
	strcat(s, buf);
	Big_Decimal tmp = bd.String_To_Big_Decimal(s);
	Big_Decimal res = tmp(ten_times);
	ASSERT_EQ(false, res.Get_Overflow());
	ASSERT_EQ(res.Get_n(), 7);
	ASSERT_EQ('0', res.Get_Value(6));
	ASSERT_EQ('5', res.Get_Value(5));
	ASSERT_EQ('4', res.Get_Value(4));
	ASSERT_EQ('3', res.Get_Value(3));
	ASSERT_EQ('2', res.Get_Value(2));
	ASSERT_EQ('1', res.Get_Value(1));
	ASSERT_EQ('9', res.Get_Value(0));
}
TEST(Increase, Test_2) {
	Big_Decimal bd;
	char buf[] = "12345";
	char *s = (char*)malloc(7);
	*s = '\0';
	strcat(s, buf);
	Big_Decimal tmp = bd.String_To_Big_Decimal(s);
	Big_Decimal res = tmp(ten_times);
	ASSERT_EQ(false, res.Get_Overflow());
	ASSERT_EQ(res.Get_n(), 7);
	ASSERT_EQ('0', res.Get_Value(6));
	ASSERT_EQ('5', res.Get_Value(5));
	ASSERT_EQ('4', res.Get_Value(4));
	ASSERT_EQ('3', res.Get_Value(3));
	ASSERT_EQ('2', res.Get_Value(2));
	ASSERT_EQ('1', res.Get_Value(1));
	ASSERT_EQ('0', res.Get_Value(0));
}
TEST(Increase, Test_3) {
	Big_Decimal bd;
	char buf[] = "0";
	char *s = (char*)malloc(2);
	*s = '\0';
	strcat(s, buf);
	Big_Decimal tmp = bd.String_To_Big_Decimal(s);
	Big_Decimal res = tmp(ten_times);
	ASSERT_EQ(res.Get_n(), 3);
	ASSERT_EQ('0', res.Get_Value(2));
	ASSERT_EQ('0', res.Get_Value(1));
	ASSERT_EQ('0', res.Get_Value(0));
}
TEST(Increase, Test_4) {
	Big_Decimal bd;
	char buf[] = "99999999999999999999999999999999999999999999999999999999999";
	char *s = (char*)malloc(60);
	*s = '\0';
	strcat(s, buf);
	Big_Decimal tmp = bd.String_To_Big_Decimal(s);
	Big_Decimal res = tmp(ten_times);
	ASSERT_EQ(res.Get_n(), N);
	ASSERT_EQ('0', res.Get_Value(0));
	for (int i = 1; i < N - 1; i++) {
		ASSERT_EQ('9', res.Get_Value(i));
	}
	ASSERT_EQ('0', res.Get_Value(59));
	ASSERT_EQ(true, res.Get_Overflow());
}
TEST(Decrease, Test_1) {
	Big_Decimal bd;
	char buf[] = "-1234";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	Big_Decimal tmp = bd.String_To_Big_Decimal(s);
	Big_Decimal res = tmp(minus_ten_times);
	ASSERT_EQ(res.Get_n(), 4);
	ASSERT_EQ('9', res.Get_Value(0));
	ASSERT_EQ('3', res.Get_Value(3));
	ASSERT_EQ('2', res.Get_Value(2));
	ASSERT_EQ('1', res.Get_Value(1));
}
TEST(Decrease, Test_2) {
	Big_Decimal bd;
	char buf[] = "1";
	char *s = (char*)malloc(2);
	*s = '\0';
	strcat(s, buf);
	Big_Decimal tmp = bd.String_To_Big_Decimal(s);
	Big_Decimal res = tmp(minus_ten_times);
	ASSERT_EQ(res.Get_n(), 1);
	ASSERT_EQ(res.Get_Value(0), '0');
} 
