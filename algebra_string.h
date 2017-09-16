#ifndef MODULE3_H
#define MODULE3_H

class string_int
{
	/*
	Столкнулся с проблемой, что при шифровании RSA не хватает памяти.
	Дабы исключить возможность того, что будет переполнение предлагаю использовать строки
	Ну или тестируйте c long long
	Не включена поддержка отрицательных значений
	*/
private:
	string value;
public:
	string_int(string str);
	string get_value();
	void set_value(string new_value);
	void add(string summand);
};

#endif