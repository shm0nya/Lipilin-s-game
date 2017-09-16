#include <string>

using namespace std;

#include "algebra_string.h"


string_int::string_int(string str = "0")
{
	value = str;
}

string string_int::get_value()
{
	return value;
}

void string_int::set_value(string new_value)
{
	value = new_value;
}

void string_int::add(string summand)
{
	if (summand.size() > value.size())
	{
		/*
		Всегда к большему прибавляем меньшее
		(больше по количеству символов)
		*/
		string temp;
		temp = value;
		value = summand;
		summand = temp;
	}

	/*
	migrate - перенос ("1 в уме")
	*/
	int migrate = 0;
	int j = value.size() - 1;

	/*
	Сложили, посмотрели, что записываем, что "в уме"
	Перешли к следующим по разряду значениям
	*/
	for (int i = summand.size() - 1 /*компенсация границы*/; i >= 0; i--)
	{
		int temp = (value[j] - '0') + (summand[i] - '0') + migrate;
		value[j] = temp % 10 + '0';
		migrate = temp / 10;
		j--;
	}
	/*
	Если после сложения осталось "1 в уме"
	Самый наглядный пример 9999 + 1
	*/
	while (migrate != 0)
	{
		if (j != -1)
		{
			int temp = (value[j] - '0') + migrate;
			value[j] = temp % 10 + '0';
			migrate = temp / 10;
			j--;
		}
		else
		{
			char a = '0' + migrate;
			value = a + value;
			migrate = 0;
		}
	}
}
