#include <tchar.h>
#include "pch.h"
#include <cstring>
#include <iostream>
class Big_Decimal {
private:
	static const int N = 60; // max size
	bool sign;//знак числа
	char value[N];
public:
	Big_Decimal(); // конструктор по умолчанию
	Big_Decimal& String_To_Big_Decimal(char*, bool&); // возможно переполнение и исключение, если строка некорректная
	// \0 добавлять видимо самой
	bool Get_Sign() const { return sign; }
	char Get_Value(int i) const { return value[i]; }
	Big_Decimal Complement_Code(Big_Decimal&);
	Big_Decimal Addition(Big_Decimal&, Big_Decimal&, bool&);
	Big_Decimal& Subtraction(const Big_Decimal&, const Big_Decimal&, bool&);
	Big_Decimal& Increase(Big_Decimal&, bool&);
	Big_Decimal& Decrease(Big_Decimal&);
	// в конструкторы записывать с конца
};

Big_Decimal::Big_Decimal() {
	sign = 0;
	for (int i = 0; i < 51; i++) value[i] = 0;
	int j = 1;
	for (int i = 51; i < 60; i++) {
		value[i] = j; //0...0123456789
		j++;
	}
}
Big_Decimal Big_Decimal::Complement_Code(Big_Decimal& bd) {
	Big_Decimal tmp = bd; // мб без этого?
	if (tmp.sign == 0) return tmp;
	if (tmp.sign == 1) {
		Big_Decimal res;
		res.sign = tmp.sign; //=1
		for (int i = 0; i < N; i++) {
			res.value[i] = 9 - tmp.value[i];
		}
		(res.value[N - 1])++;
		int j = N - 1;
		while ((res.value[j] == 10) && (j > 0)) {
			res.value[j] = 0;
			(res.value[j - 1])++;
			j--;
		}
		if (res.value[0] == 10) {
			res.value[0] = 0;
			res.sign = 0; // -0 переводится в 0 
		}
		return res;
	}
}
Big_Decimal Big_Decimal::Addition(Big_Decimal& bd1, Big_Decimal& bd2, bool& overflow) {
	//Big_Decimal tmp3 = bd1, tmp4 = bd2;
	Big_Decimal tmp1 = Complement_Code(bd1);
	Big_Decimal tmp2 = Complement_Code(bd2);
	Big_Decimal res;
	bool k = 0;
	for (int j = N - 1; j >= 0; j--) {
		res.value[j] = tmp1.value[j] + tmp2.value[j] + k;
		if (res.value[j] > 9) {
			res.value[j] = res.value[j] % 10;
			k = 1;
		}
		else k = 0;
	}
	if ((tmp1.sign == tmp2.sign) && (tmp1.sign == k)) res.sign = k;
	if (tmp1.sign != tmp2.sign) res.sign = !k;
	if ((tmp1.sign == tmp2.sign) && (tmp1.sign != k)) {
		res.sign = tmp1.sign;
		overflow = true; // переполнение!!!!!
	}// после каждого раза в мэйне обнулять этот overflow что ли
	return res;
}
Big_Decimal& Big_Decimal::Subtraction(const Big_Decimal& bd1, const Big_Decimal& bd2, bool& overflow) {
	Big_Decimal tmp1 = bd1, tmp2 = bd2, res;
	tmp2.sign = !tmp2.sign;
	res = Addition(tmp1, tmp2, overflow);
	return res;
}
Big_Decimal& Big_Decimal::Increase(Big_Decimal& bd, bool& overflow) {
	int i;
	for (i = 0; ((i < N) && (bd.value[i] == 0)); i++);// находим индекс первого ненулевого (типа чтоб нули не двигать)
	// а кстати если идут подряд несколько одинаковых цифр то их как будто тоже можно не двигать
	// но вдруг операция сравнения вот этого постоянного еще больше времени занимает и
	// вообще все эти оптимизации не имеют смысла ))
	if (i == N) return bd; // нет ненулевых цифр
	if (i == 0) {
		i = 1;
		overflow = true; // переполнение!!!!! 
	}
	for (int j = i; j < N; j++) {
		bd.value[j - 1] = bd.value[j];
	}
	bd.value[N - 1] = 0;
	return bd;
}
Big_Decimal& Big_Decimal::Decrease(Big_Decimal& bd) {
	int i;
	for (i = 0; ((i < N) && (bd.value[i] == 0)); i++);// находим индекс первого ненулевого (типа чтоб нули не двигать)
	if (i == N) return bd; // нет ненулевых цифр
	if (i == 0) i = 1;
	for (int j = N - 1; j >= i; j--) {
		bd.value[j] = bd.value[j - 1];
	}
	bd.value[0] = 0;
	return bd;
}
Big_Decimal& Big_Decimal::String_To_Big_Decimal(char* str, bool& overflow) {
	int n = strlen(str);
	if (n == 0) throw std::exception("incorrect string"); // empty
	// ecли n > N не факт, что переполнение, надо еще проверить впереди стоящие нули
	Big_Decimal res;
	if ((str[0] != '+') && (str[0] != '-') && (str[0] != 0) && (str[0] != 1) && (str[0] != 2)
		&& (str[0] != 3) && (str[0] != 4) && (str[0] != 5) && (str[0] != 6) && (str[0] != 7) &&
		(str[0] != 8) && (str[0] != 9))
		throw std::exception("incorrect string");
	else {
		for (int i = 1; i < n; i++)
			if ((str[i] != 0) && (str[i] != 1) && (str[i] != 2)
				&& (str[i] != 3) && (str[i] != 4) && (str[i] != 5) && (str[i] != 6) && (str[i] != 7) &&
				(str[i] != 8) && (str[i] != 9))
				throw std::exception("incorrect string");
			else {
				int j, k, b = 0;
				if (str[0] == '-') {
					res.sign = 1;
					b = 1;
				}
				else res.sign = 0;
				if (str[0] == '+') b = 1;
				/*for (j = N - 1; j >= 0; j--) {
					for (k = n - 1; k >= 0; k--) {
						res.value[j] = str[k];
					}
				} */
				j = N - 1;
				k = n - 1;
				while ((k >= b) && (j >= 0)) {
					res.value[j] = str[k];
					k--;
					j--;
				}
				// сравнить k и j и исходя из этого определить переполнение или дохерачить нули до конца
				if (j > k) {
					for (int c = 0; c <= j; c++) res.value[c] = 0;
				}
				if (j < k) {
					for (int c = b; c <= k; c++) {
						if (str[c] != 0) {
							overflow = true;
							break;
						}
					}
				}
				return res;
			}
	}
}

TEST(Constructor, Default) {
	Big_Decimal bd;
	ASSERT_EQ(0, bd.Get_Sign());
	ASSERT_EQ(9, bd.Get_Value(59));
	ASSERT_EQ(8, bd.Get_Value(58));
	ASSERT_EQ(0, bd.Get_Value(0));
}
TEST(Complement_Code, Default) {
	Big_Decimal bd;
	Big_Decimal tmp = bd.Complement_Code(bd);
	ASSERT_EQ(0, tmp.Get_Sign());
	ASSERT_EQ(9, tmp.Get_Value(59));
	ASSERT_EQ(8, tmp.Get_Value(58));
	ASSERT_EQ(0, tmp.Get_Value(0));
}
int main(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}