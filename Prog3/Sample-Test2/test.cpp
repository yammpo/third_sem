#include "pch.h"
#include "gtest\gtest.h"
#include "BD.h"
TEST(Constructor, Default) {
	Big_Decimal bd;
	for (int i = 0; i < N; i++) {
		ASSERT_EQ('0', bd.Get_Value(i));
	}
}
TEST(Long_To_Big_Decimal, Test_1) {
	Big_Decimal bd;
	bool fl = false;
	long int l = -123456789;
	bd = bd.Long_To_Big_Decimal(l, fl);
	ASSERT_EQ('9', bd.Get_Value(0));
	ASSERT_EQ('9', bd.Get_Value(59));
	ASSERT_EQ('8', bd.Get_Value(58));
	ASSERT_EQ('7', bd.Get_Value(57));
	ASSERT_EQ('6', bd.Get_Value(56));
	ASSERT_EQ('5', bd.Get_Value(55));
	ASSERT_EQ('4', bd.Get_Value(54));
	ASSERT_EQ('3', bd.Get_Value(53));
	ASSERT_EQ('2', bd.Get_Value(52));
	ASSERT_EQ('1', bd.Get_Value(51));
	ASSERT_EQ('0', bd.Get_Value(50));
}
TEST(Long_To_Big_Decimal, Test_2) {
	Big_Decimal bd;
	bool fl = false;
	long int l = 123456789;
	bd = bd.Long_To_Big_Decimal(l, fl);
	ASSERT_EQ('0', bd.Get_Value(0));
	ASSERT_EQ('9', bd.Get_Value(59));
	ASSERT_EQ('8', bd.Get_Value(58));
	ASSERT_EQ('7', bd.Get_Value(57));
	ASSERT_EQ('6', bd.Get_Value(56));
	ASSERT_EQ('5', bd.Get_Value(55));
	ASSERT_EQ('4', bd.Get_Value(54));
	ASSERT_EQ('3', bd.Get_Value(53));
	ASSERT_EQ('2', bd.Get_Value(52));
	ASSERT_EQ('1', bd.Get_Value(51));
	ASSERT_EQ('0', bd.Get_Value(50));
}
TEST(String_To_Big_Decimal, Test_1) {
	Big_Decimal bd;
	bool fl = false;
	char buf[] = "12345";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	Big_Decimal tmp = bd.String_To_Big_Decimal(s, fl);
	ASSERT_EQ('5', tmp.Get_Value(59));
	ASSERT_EQ('4', tmp.Get_Value(58));
	ASSERT_EQ('3', tmp.Get_Value(57));
	ASSERT_EQ('2', tmp.Get_Value(56));
	ASSERT_EQ('1', tmp.Get_Value(55));
	ASSERT_EQ('0', tmp.Get_Value(0));
}
TEST(String_To_Big_Decimal, Test_2) {
	Big_Decimal bd;
	bool fl = false;
	char buf[] = "-12345";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	Big_Decimal tmp = bd.String_To_Big_Decimal(s, fl);
	ASSERT_EQ('5', tmp.Get_Value(59));
	ASSERT_EQ('4', tmp.Get_Value(58));
	ASSERT_EQ('3', tmp.Get_Value(57));
	ASSERT_EQ('2', tmp.Get_Value(56));
	ASSERT_EQ('1', tmp.Get_Value(55));
	ASSERT_EQ('9', tmp.Get_Value(0));
}
TEST(String_To_Big_Decimal, Test_3) {
	Big_Decimal bd;
	bool fl = false;
	char buf[] = "mephi";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	ASSERT_ANY_THROW(bd.String_To_Big_Decimal(s, fl));
}
TEST(String_To_Big_Decimal, Test_4) {
	Big_Decimal bd;
	bool fl = false;
	char buf[] = "111111111111111111111111111111111111111111111111111111111111111111111111111";
	char *s = (char*)malloc(76);
	*s = '\0';
	strcat(s, buf);
	Big_Decimal tmp = bd.String_To_Big_Decimal(s, fl);
	ASSERT_EQ('0', tmp.Get_Value(0));
	for (int i = 1; i < N; i++) {
		ASSERT_EQ('1', tmp.Get_Value(i));
	}
	ASSERT_EQ(true, fl);
}
TEST(Complement_Code, Test_1) {
	Big_Decimal bd;
	Big_Decimal tmp2;
	char buf[] = "-2345";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	bool fl = false;
	Big_Decimal tmp = bd.String_To_Big_Decimal(s, fl);
	tmp2 = tmp.Complement_Code(tmp);
	ASSERT_EQ('5', tmp2.Get_Value(59));
	ASSERT_EQ('5', tmp2.Get_Value(58));
	ASSERT_EQ('6', tmp2.Get_Value(57));
	ASSERT_EQ('7', tmp2.Get_Value(56));
	ASSERT_EQ('9', tmp2.Get_Value(0));
}
TEST(Complement_Code, Test_2) {
	Big_Decimal bd;
	Big_Decimal tmp2;
	char buf[] = "12345";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	bool fl = false;
	Big_Decimal tmp = bd.String_To_Big_Decimal(s, fl);
	tmp2 = tmp.Complement_Code(tmp);
	ASSERT_EQ('5', tmp2.Get_Value(59));
	ASSERT_EQ('4', tmp2.Get_Value(58));
	ASSERT_EQ('3', tmp2.Get_Value(57));
	ASSERT_EQ('2', tmp2.Get_Value(56));
	ASSERT_EQ('1', tmp2.Get_Value(55));
	ASSERT_EQ('0', tmp2.Get_Value(0));
}
TEST(Complement_Code, Test_3) {
	Big_Decimal bd;
	Big_Decimal tmp2;
	char buf[] = "-0";
	char *s = (char*)malloc(3);
	*s = '\0';
	strcat(s, buf);
	bool fl = false;
	Big_Decimal tmp = bd.String_To_Big_Decimal(s, fl);
	tmp2 = tmp.Complement_Code(tmp);
	for (int i = 0; i < N; i++) {
		ASSERT_EQ('0', tmp2.Get_Value(i));
	}
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
	bool fl = false;
	Big_Decimal tmp1 = bd.String_To_Big_Decimal(s, fl);
	Big_Decimal tmp2 = bd.String_To_Big_Decimal(t, fl);
	Big_Decimal res = tmp1.Addition(tmp1, tmp2, fl);
	ASSERT_EQ('4', res.Get_Value(59));
	ASSERT_EQ('3', res.Get_Value(58));
	ASSERT_EQ('1', res.Get_Value(57));
	ASSERT_EQ('9', res.Get_Value(56));
	ASSERT_EQ('1', res.Get_Value(55));
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
	bool fl = false;
	Big_Decimal tmp1 = bd.String_To_Big_Decimal(s, fl);
	Big_Decimal tmp2 = bd.String_To_Big_Decimal(t, fl);
	Big_Decimal res = tmp1.Addition(tmp1, tmp2, fl);
	ASSERT_EQ(fl, true);
	ASSERT_EQ('1', res.Get_Value(59));
	for (int i = 0; i < N-1; i++) {
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
	bool fl = false;
	Big_Decimal tmp1 = bd.String_To_Big_Decimal(s, fl);
	Big_Decimal tmp2 = bd.String_To_Big_Decimal(t, fl);
	Big_Decimal res = tmp1.Addition(tmp1, tmp2, fl);
	ASSERT_EQ('6', res.Get_Value(59));
	ASSERT_EQ('5', res.Get_Value(58));
	ASSERT_EQ('5', res.Get_Value(57));
	ASSERT_EQ('5', res.Get_Value(56));
	ASSERT_EQ('0', res.Get_Value(55));
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
	bool fl = false;
	Big_Decimal tmp1 = bd.String_To_Big_Decimal(s, fl);
	Big_Decimal tmp2 = bd.String_To_Big_Decimal(t, fl);
	Big_Decimal res = tmp1.Addition(tmp1, tmp2, fl);
	ASSERT_EQ('6', res.Get_Value(59));
	ASSERT_EQ('5', res.Get_Value(58));
	ASSERT_EQ('5', res.Get_Value(57));
	ASSERT_EQ('5', res.Get_Value(56));
	ASSERT_EQ('0', res.Get_Value(55));
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
	bool fl = false;
	Big_Decimal tmp1 = bd.String_To_Big_Decimal(s, fl);
	Big_Decimal tmp2 = bd.String_To_Big_Decimal(t, fl);
	Big_Decimal res = tmp1.Subtraction(tmp1, tmp2, fl);
	ASSERT_EQ('8', res.Get_Value(59));
	ASSERT_EQ('6', res.Get_Value(58));
	ASSERT_EQ('4', res.Get_Value(57));
	ASSERT_EQ('2', res.Get_Value(56));
	ASSERT_EQ('5', res.Get_Value(55));
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
	bool fl = false;
	Big_Decimal tmp1 = bd.String_To_Big_Decimal(s, fl);
	Big_Decimal tmp2 = bd.String_To_Big_Decimal(t, fl);
	Big_Decimal res = tmp1.Subtraction(tmp1, tmp2, fl);
	ASSERT_EQ(fl, true);
	ASSERT_EQ('1', res.Get_Value(59));
	for (int i = 1; i < N - 1; i++) {
		ASSERT_EQ('0', bd.Get_Value(i));
	}
	ASSERT_EQ('9', res.Get_Value(0));
}
TEST(Increase, Test_1) {
	Big_Decimal bd;
	char buf[] = "-12345";
	char *s = (char*)malloc(7);
	*s = '\0';
	strcat(s, buf);
	bool fl = false;
	Big_Decimal tmp = bd.String_To_Big_Decimal(s, fl);
	Big_Decimal res = tmp.Increase(tmp, fl);
	ASSERT_EQ('0', res.Get_Value(59));
	ASSERT_EQ('5', res.Get_Value(58));
	ASSERT_EQ('4', res.Get_Value(57));
	ASSERT_EQ('3', res.Get_Value(56));
	ASSERT_EQ('2', res.Get_Value(55));
	ASSERT_EQ('1', res.Get_Value(54));
	ASSERT_EQ('9', res.Get_Value(0));
}
TEST(Increase, Test_2) {
	Big_Decimal bd;
	char buf[] = "12345";
	char *s = (char*)malloc(7);
	*s = '\0';
	strcat(s, buf);
	bool fl = false;
	Big_Decimal tmp = bd.String_To_Big_Decimal(s, fl);
	Big_Decimal res = tmp.Increase(tmp, fl);
	ASSERT_EQ('0', res.Get_Value(59));
	ASSERT_EQ('5', res.Get_Value(58));
	ASSERT_EQ('4', res.Get_Value(57));
	ASSERT_EQ('3', res.Get_Value(56));
	ASSERT_EQ('2', res.Get_Value(55));
	ASSERT_EQ('1', res.Get_Value(54));
	ASSERT_EQ('0', res.Get_Value(0));
}
TEST(Increase, Test_3) {
	Big_Decimal bd;
	char buf[] = "0";
	char *s = (char*)malloc(2);
	*s = '\0';
	strcat(s, buf);
	bool fl = false;
	Big_Decimal tmp = bd.String_To_Big_Decimal(s, fl);
	Big_Decimal res = tmp.Increase(tmp, fl);
	for (int i = 0; i < N; i++) {
		ASSERT_EQ('0', res.Get_Value(i));
	}
}
TEST(Increase, Test_4) {
	Big_Decimal bd;
	char buf[] = "99999999999999999999999999999999999999999999999999999999999";
	char *s = (char*)malloc(60);
	*s = '\0';
	strcat(s, buf);
	bool fl = false;
	Big_Decimal tmp = bd.String_To_Big_Decimal(s, fl);
	Big_Decimal res = tmp.Increase(tmp, fl);
	ASSERT_EQ('0', res.Get_Value(0));
	for (int i = 1; i < N - 1; i++) {
		ASSERT_EQ('9', res.Get_Value(i));
	}
	ASSERT_EQ('0', res.Get_Value(59));
	ASSERT_EQ(true, fl);
}
TEST(Decrease, Test_1) {
	Big_Decimal bd;
	char buf[] = "-1234";
	char *s = (char*)malloc(6);
	*s = '\0';
	strcat(s, buf);
	bool fl = false;
	Big_Decimal tmp = bd.String_To_Big_Decimal(s, fl);
	Big_Decimal res = tmp.Decrease(tmp);
	ASSERT_EQ('9', res.Get_Value(0));
	ASSERT_EQ('3', res.Get_Value(59));
	ASSERT_EQ('2', res.Get_Value(58));
	ASSERT_EQ('1', res.Get_Value(57));
}
TEST(Decrease, Test_2) {
	Big_Decimal bd;
	char buf[] = "1";
	char *s = (char*)malloc(2);
	*s = '\0';
	strcat(s, buf);
	bool fl = false;
	Big_Decimal tmp = bd.String_To_Big_Decimal(s, fl);
	Big_Decimal res = tmp.Decrease(tmp);
	for (int i = 0; i < N; i++) {
		ASSERT_EQ('0', res.Get_Value(i));
	}
}
