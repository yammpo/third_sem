#include "stdafx.h"
#include "BD.h"

char* Realloc(char* old_el, unsigned old_size, unsigned new_size, bool flag) {
	if (old_size != new_size) {
		char* new_el;
		try {
			new_el = new char[new_size];
		}
		catch (std::bad_alloc &ex) {
			throw std::exception(ex);
		}
		unsigned n = (old_size < new_size) ? old_size : new_size;
		if (flag == end) {
			int j = new_size - 1;
			for (unsigned i = n - 1; i >= 1; i--) {// c конца
				new_el[j] = old_el[i];
				j--;
			}
			for (unsigned i = 1; i < new_size - (old_size - 1); i++) {
				new_el[i] = '0';
			}
		}
		if (flag == begin) {
			for (unsigned i = 1; i < n; i++)// c начала
				new_el[i] = old_el[i];
		}
		delete[] old_el;
		old_el = new_el;
		new_el = nullptr;
	}
	return old_el;
}
Big_Decimal::Big_Decimal() {
	value = new char[2];
	value[0] = '0'; // знак
	value[1] = '0';
	overflow = false;
	n = 2;
}
Big_Decimal::Big_Decimal(const Big_Decimal& bd) : n(bd.n), overflow(bd.overflow) {
	value = new char[n];
	for (int i = 0; i < n; i++)
		value[i] = bd.value[i];
}
Big_Decimal::Big_Decimal(Big_Decimal&& bd) : n(bd.n), overflow(bd.overflow), value(bd.value) {
	bd.value = nullptr;
}
Big_Decimal& Big_Decimal::operator = (const Big_Decimal& bd) { // было Big_Decimal Big_Decimal::operator = (Big_Decimal bd) и без второй перегрузки равно
	if (this != &bd) {
		n = bd.n;
		overflow = bd.overflow;
		delete[] value;
		value = new char[n];
		for (int i = 0; i < n; i++)
			value[i] = bd.value[i];
	}
	//std::cout << "ravno" << std::endl;
	return *this;
}
Big_Decimal& Big_Decimal::operator = (Big_Decimal&& bd) {
	int tmp = n;
	n = bd.n;
	bd.n = tmp;
	bool temp = overflow;
	overflow = bd.overflow;
	bd.overflow = temp;
	char *ptr = value;
	value = bd.value;
	bd.value = ptr;
	return *this;
}

Big_Decimal Big_Decimal::Complement_Code(Big_Decimal& bd) { 
	Big_Decimal tmp = bd; // мб без этого?
	if (tmp.value[0] == '0') return tmp;
	if (tmp.value[0] == '9') {
		Big_Decimal res;
		delete[] res.value;
		res.value = new char[bd.n];
		res.n = bd.n;
		res.overflow = bd.overflow;
		res.value[0] = '9';
		for (int i = 1; i < n; i++) {
			res.value[i] = 48 + '9' - tmp.value[i]; // 48 потому что таблица 
		}
		(res.value[n - 1])++;
		int j = n - 1;
		while ((res.value[j] == 48 + 10) && (j > 0)) {
			res.value[j] = '0';
			(res.value[j - 1])++;
			j--;
		}
		if (res.value[0] == 48 + 10) res.value[0] = '0'; // -0 переводится в +0 
		return res;
	}
}
Big_Decimal operator + (Big_Decimal &bd1, Big_Decimal &bd2) {// расширять до сетки бОльшего
	int nn = bd1.n;
	if (bd1.n < bd2.n) {
		int sign1 = bd1.value[0];
		bd1.value = Realloc(bd1.value, bd1.n, bd2.n, end);
		bd1.value[0] = sign1;
		bd1.n = bd2.n;
		nn = bd2.n;
	}
	if (bd2.n < bd1.n) {
		int sign2 = bd2.value[0];
		bd2.value = Realloc(bd2.value, bd2.n, bd1.n, end);
		bd2.value[0] = sign2;
		bd2.n = bd1.n;
	}
	Big_Decimal tmp1 = bd1.Complement_Code(bd1);
	Big_Decimal tmp2 = bd2.Complement_Code(bd2);
	Big_Decimal res;
	delete[] res.value;
	res.value = new char[nn];
	res.n = nn;
	bool k = 0;
	for (int j = nn - 1; j >= 0; j--) {// откидывание единицы кажется тут же происходит
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
	//res = res.Complement_Code(res);
	return res.Complement_Code(res);
}

Big_Decimal operator - (Big_Decimal &bd1, Big_Decimal &bd2) {
	Big_Decimal tmp1 = bd1, tmp2 = bd2, res;
	tmp2.value[0] = 48 + '9' - tmp2.value[0]; // знак меняется
	res = tmp1 + tmp2;
	return res;
}

Big_Decimal Big_Decimal::operator()(bool tm) {
	//int i;
	//for (i = 1; ((i < n) && (value[i] == '0')); i++);// находим индекс первого ненулевого (типа чтоб нули не двигать)
	//if (i == n) return *this; // нет ненулевых цифр
	int sign = value[0];
	if (tm == ten_times) {
		if (n == N) {
			for (int j = 1; j < N; j++) {
				value[j - 1] = value[j];
			}
			value[N - 1] = '0';
			value[0] = sign;
			overflow = true; // переполнение!!!!! 
		}
		else {
			value = Realloc(value, n, n + 1, begin);
			n++;
			value[n - 1] = '0';
			value[0] = sign;
		}
	}
	if (tm == minus_ten_times) {
		if (n == 1) return *this; 
		else {
		value = Realloc(value, n, n - 1, begin);
		n--;
		value[0] = sign;
		}
	}
	return *this;
}

Big_Decimal Big_Decimal::String_To_Big_Decimal(char* str) {// под незначащие нули не выделять
	int ln = strlen(str);
	if (ln == 0) throw std::exception("incorrect string"); // empty
	// ecли ln > N не факт, что переполнение, надо еще проверить впереди стоящие нули
	if (ln == 1) {
		if ((str[0] != '0') && (str[0] != '1') && (str[0] != '2')
			&& (str[0] != '3') && (str[0] != '4') && (str[0] != '5') && (str[0] != '6') && (str[0] != '7') &&
			(str[0] != '8') && (str[0] != '9'))
			throw std::exception("incorrect string");
		else {
			value = new char[2];
			n = 2;
			overflow = false;
			value[0] = '0';
			value[1] = str[0];
			return *this;
		}
	}
	if ((str[0] != '+') && (str[0] != '-') && (str[0] != '0') && (str[0] != '1') && (str[0] != '2')
		&& (str[0] != '3') && (str[0] != '4') && (str[0] != '5') && (str[0] != '6') && (str[0] != '7') &&
		(str[0] != '8') && (str[0] != '9'))
		throw std::exception("incorrect string");
	else {
		for (int i = 1; i < ln; i++)
			if ((str[i] != '0') && (str[i] != '1') && (str[i] != '2')
				&& (str[i] != '3') && (str[i] != '4') && (str[i] != '5') && (str[i] != '6') && (str[i] != '7') &&
				(str[i] != '8') && (str[i] != '9'))
				throw std::exception("incorrect string");
			else {
				int t = 0;
				if ((str[0] == '+') || (str[0] == '-')) t = 1;
				for (; ((t < ln) && (str[t] == '0')); t++); // индекс первого ненулевого
				if ((ln - t + 1) > N) {
					value = new char[N];
					n = N;
					overflow = true;
				}
				else {
					value = new char[ln - t + 1];
					n = ln - t + 1;
					overflow = false; // вроде и так
				}
				int j, k, b = 0;
				if (str[0] == '-') {
					value[0] = '9';
					b = 1;
				}
				else value[0] = '0';
				if (str[0] == '+') b = 1;
				j = n - 1;
				k = ln - 1;
				while ((k >= b) && (j >= 1)) {
					value[j] = str[k];
					k--;
					j--;
				}
				return *this;
			}
	}
}
Big_Decimal Big_Decimal::Long_To_Big_Decimal(long int l) {// сначала найти длину числа чтоб узнать сколько памяти выделить?
	int i;
	long int tmp = l;
	if (l < 0) tmp = -tmp;
	long int tmp2 = tmp;
	for (i = 0; tmp2 > 0; i++) {tmp2 = tmp2 / 10;}
	if (i + 1 > N) {
		value = new char[N];
		n = N;
		overflow = true;
	}
	else {
		value = new char[i + 1];
		n = i + 1;
		overflow = false;
	}
	if (l < 0) value[0] = '9'; 
	else value[0] = '0';
	int j = n - 1;
	while ((tmp != 0) && (j >= 1)) {
		value[j] = (tmp % 10) + '0';
		tmp = tmp / 10;
		j--;
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
	for (i = 1; ((i < bd.n) && (bd.value[i] == '0')); i++); // индекс первого ненулевого, 
	//хоть незначащие нули при вводе и не записываются, но на всякий случай
	if (i == bd.n) { s << '0'; }
	for (int j = i; j < bd.n; j++) {
		s << bd.value[j];
	}
	/*for (int b = 1; b < N; b++) {
		s << value[b];
	} */
	s << std::endl;
	return s;
}