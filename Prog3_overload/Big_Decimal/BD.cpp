#include "stdafx.h"
#include "BD.h"

Big_Decimal::Big_Decimal() {
	for (int i = 0; i < N; i++) {
		value[i] = '0';
	}
	overflow = false;
}

Big_Decimal Big_Decimal::Complement_Code(Big_Decimal& bd) {
	Big_Decimal tmp = bd; // мб без этого?
	if (tmp.value[0] == '0') return tmp;
	if (tmp.value[0] == '9') {
		Big_Decimal res;
		res.overflow = bd.overflow;
		res.value[0] = '9';
		for (int i = 1; i < N; i++) {
			res.value[i] = 48 + '9' - tmp.value[i]; // 48 потому что таблица 
		}
		(res.value[N - 1])++;
		int j = N - 1;
		while ((res.value[j] == 48 + 10) && (j > 0)) {
			res.value[j] = '0';
			(res.value[j - 1])++;
			j--;
		}
		if (res.value[0] == 48 + 10) res.value[0] = '0'; // -0 переводится в +0 
		return res;
	}
}
Big_Decimal operator + (Big_Decimal &bd1, Big_Decimal &bd2) {
	Big_Decimal tmp1 = bd1.Complement_Code(bd1);
	Big_Decimal tmp2 = bd2.Complement_Code(bd2);
	Big_Decimal res;
	bool k = 0;
	for (int j = N - 1; j >= 0; j--) {// откидывание единицы кажется тут же происходит
		res.value[j] = tmp1.value[j] + tmp2.value[j] - 48 + k;
		if (res.value[j] > '0' + 9) {
			res.value[j] = (res.value[j] - 48) % 10 + 48;
			k = 1;
		}
		else k = 0;
	}
	if (res.value[0] == '8') {
		res.overflow = true; // переполнение!!!!!
		res.value[0] = '9';
	}
	if (res.value[0] == '1') {
		res.overflow = true; // переполнение!!!!!
		res.value[0] = '0';
	}
	// после каждого раза в мэйне обнулять этот overflow что ли
	res = res.Complement_Code(res);
	return res;
}

Big_Decimal operator - (Big_Decimal &bd1, Big_Decimal &bd2) {
	Big_Decimal tmp1 = bd1, tmp2 = bd2, res;
	tmp2.value[0] = 48 + '9' - tmp2.value[0]; // знак меняется
	res = tmp1 + tmp2;
	return res;
}

Big_Decimal Big_Decimal::operator()(bool tm) {
	int i;
	for (i = 1; ((i < N) && (value[i] == '0')); i++);// находим индекс первого ненулевого (типа чтоб нули не двигать)
	if (i == N) return *this; // нет ненулевых цифр
	if (tm == ten_times) {
		if (i == 1) {
			i = 2;
			overflow = true; // переполнение!!!!! 
		}
		for (int j = i; j < N; j++) {
			value[j - 1] = value[j];
		}
		value[N - 1] = '0';
	}
	if (tm == minus_ten_times) {
		if (i == 1) i = 2;
		for (int j = N - 1; j >= i; j--) {
			value[j] = value[j - 1];
		}
		value[1] = '0';
	}
	return *this;
}

Big_Decimal Big_Decimal::String_To_Big_Decimal(char* str) {
	int n = strlen(str);
	if (n == 0) throw std::exception("incorrect string"); // empty
	// ecли n > N не факт, что переполнение, надо еще проверить впереди стоящие нули
	if (n == 1) {
		if ((str[0] != '0') && (str[0] != '1') && (str[0] != '2')
			&& (str[0] != '3') && (str[0] != '4') && (str[0] != '5') && (str[0] != '6') && (str[0] != '7') &&
			(str[0] != '8') && (str[0] != '9'))
			throw std::exception("incorrect string");
		else {
			Big_Decimal res;
			res.value[0] = '0';
			res.value[N - 1] = str[0];
			return res;
		}
	}
	Big_Decimal res;
	if ((str[0] != '+') && (str[0] != '-') && (str[0] != '0') && (str[0] != '1') && (str[0] != '2')
		&& (str[0] != '3') && (str[0] != '4') && (str[0] != '5') && (str[0] != '6') && (str[0] != '7') &&
		(str[0] != '8') && (str[0] != '9'))
		throw std::exception("incorrect string");
	else {
		for (int i = 1; i < n; i++)
			if ((str[i] != '0') && (str[i] != '1') && (str[i] != '2')
				&& (str[i] != '3') && (str[i] != '4') && (str[i] != '5') && (str[i] != '6') && (str[i] != '7') &&
				(str[i] != '8') && (str[i] != '9'))
				throw std::exception("incorrect string");
			else {
				int j, k, b = 0;
				if (str[0] == '-') {
					res.value[0] = '9';
					b = 1;
				}
				else res.value[0] = '0'; // оно вроде и так
				if (str[0] == '+') b = 1;
				/*for (j = N - 1; j >= 0; j--) {
					for (k = n - 1; k >= 0; k--) {
						res.value[j] = str[k];
					}
				} */
				j = N - 1;
				k = n - 1;
				while ((k >= b) && (j >= 1)) {
					res.value[j] = str[k];
					k--;
					j--;
				}
				if (j < k) {
					for (int c = b; c <= k; c++) {
						if (str[c] != 0) {
							res.overflow = true;
							break;
						}
					}
				}
				return res;
			}
	}
}
Big_Decimal Big_Decimal::Long_To_Big_Decimal(long int l) {
	long int tmp = l;
	if (l < 0) {
		value[0] = '9'; // по умолчанию sign = 0
		tmp = -tmp;
	}
	int i = N - 1;
	while ((tmp != 0) && (i >= 1)) {
		value[i] = (tmp % 10) + 48;
		tmp = tmp / 10;
		i--;
	}
	if (tmp != 0) {
		overflow = true; // не уместилось
	}
	return *this;
}

char* getstr(std::istream& s)
{
	char* ptr = (char*)malloc(1);
	char buf[500];
	int len = 0;
	*ptr = '\0';
	s >> buf;
	len += strlen(buf);
	ptr = (char*)realloc(ptr, len + 1);
	strcat(ptr, buf);
	return ptr;
}
unsigned GetNum(const char* msg) {
	unsigned n;
	const char* errmsg = "";
	do {
		std::cout << errmsg << std::endl;
		std::cout << msg;
		std::cin >> n;
		if (!(std::cin.good())) {
			errmsg = "Invalid value, try again\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else return n;
	} while (true);
}

unsigned GetNum(const char* msg, std::istream& i) {
	unsigned n;
	const char* errmsg = "";
	do {
		std::cout << errmsg << std::endl;
		std::cout << msg;
		i >> n;
		if (!(std::cin.good())) {
			errmsg = "Invalid value, try again\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else return n;
	} while (true);
}
std::istream& operator >> (std::istream& s, Big_Decimal& bd) {
	char* str = getstr(s);
	bd = bd.String_To_Big_Decimal(str);
	return s;
}

std::ostream& operator << (std::ostream& s, Big_Decimal& bd) {
	if (bd.value[0] == '9') s << "-";
	int i;
	for (i = 1; ((i < N) && (bd.value[i] == '0')); i++); // индекс первого ненулевого
	if (i == N) { s << '0'; }
	for (int j = i; j < N; j++) {
		s << bd.value[j];
	}
	/*for (int b = 1; b < N; b++) {
		s << value[b];
	} */
	s << std::endl;
	return s;
}