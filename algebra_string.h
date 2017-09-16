#ifndef MODULE3_H
#define MODULE3_H

class string_int
{
	/*
	Столкнулся с проблемой, что при шифровании RSA не хватает памяти.
	Дабы исключить возможность того, что будет переполнение предлагаю использовать строки
	Ну или тестируйте c long long
	Не включена поддержка отрицательных значений
	Не включена поддержка проверки "влезает значение в int или нет"
	*/
private:
	string value;
public:
	string_int(string str);
	string get_value();
	void set_value(string new_value);
	void add(string summand);
	void multiplicate(string mult);
	void power(int range); // Надеюсь не надо будет возводить в 2^32 степень
	int value_into_int();
};

string int_into_string(int value);
string compare(string a, string b);

#endif