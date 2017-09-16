#include <string>
#include <vector>
#include <cmath>

using namespace std;

#include "algebra_string.h"

string int_into_string(int value)
{
	/*
	Перевод Ineger в строку
	*/
	if (value == 0)
		return "0";

	string unswer = "";
	while (value > 0)
	{
		int temp = value % 10;
		char a = temp + '0';
		unswer = a + unswer;
		value = value / 10;
	}
	return unswer;
}

string compare(string a, string b)
{
	if (a.size() > b.size())
		return "more";
	else
		if (a.size() < b.size())
			return "less";

	for (int i = a.size() - 1; i >= 0; i--)
	{
		if ((a[i] - '0') > (b[i] - '0'))
			return "more";
		else
			if ((a[i] - '0') > (b[i] - '0'))
				return "less";
	}

	return "same";
}

//////////////////////////////Class metods///////////////////////////

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

void string_int::multiplicate(string mult)
{
	/*
	Проверка на 0
	*/
	if (mult == "0" || value == "0")
	{
		value = "0";
		return;
	}

	if (mult.size() > value.size())
	{
		/*
		Всегда множитель по количеству разрядом меньше или равен умножаемомоу
		13 * 900 = 900 * 13
		(удобнее с точки зрения построения алгоритма
		*/
		string temp;
		temp = value;
		value = mult;
		mult = temp;
	}
	/*
	Разобьем умножение чисел на две операции:1) умножение "а" на одноразрядное число
											 2) сложение чисел
	Что это значит:
	613*32 = 613*2 + 613*30
	Отсюда необходимо:
						1) 613 - умножаемое, 32 - множитель
						2) 32 разобьем по цифрам: [3, 2]
						3) будем обходить с конца данное множиство цифр [умножение столбиком]
						4) 613 * 2 *(10^n), где n - разряд числа 2
						5) 613 * 3 * (10^1)
						6) сложить все полученные "умножения"
	*/

int migrate = 0;				// Перенос в следующий разряд
int temp;						//
vector<string> adding_values;	// Хранятся "умножения"
string temp_value;				// Необходимо, чтобы каждый раз умножать value, не изменяя исходное значение value

for (int i = mult.size() - 1; i >= 0; i--)
{
	/* Обход множителя */
	temp_value = value;
	for (int j = temp_value.size() - 1; j >= 0; j--)
	{
		/*
		Обход умножаемого
						1) умножили значения и прибавили то, что перенеслось из предыдущего разряда (в начале 0)
						2) записали значение
						3) запомнили, что "в уме" (перенесется в следующий разряд)
		*/
		temp = (temp_value[j] - '0') * (mult[i] - '0') + migrate;
		temp_value[j] = temp % 10 + '0';
		migrate = temp / 10;
	}

	if (migrate != 0)
	{
		/*
		Проверка: вышли мы за пределы исходных разрядов или нет: (6*3) = 18
		Начальный разряд = 0 (6), после умножения он станет равен (8),
		перенесется (1) в следующий разряд !# проверяет перенос
		*/
		char a = migrate + '0';
		temp_value = a + temp_value;
	}
	/*
	Проверка смещения разрядов.
	613 * 32...
	По алгоритму представится как: 1) 613 * 2 * 10^0
								   2) 613 * 3 * 10^1
	Добавляет умножение на 10^n - по сути смещение
	*/
	string offset = "";
	for (int k = 0; k < mult.size() - i - 1; k++)
		offset = offset + '0';

	temp_value = temp_value + offset;
	adding_values.push_back(temp_value);
	migrate = 0;
}
/*
Сложение всех "умножений"
*/
value = "0";
for (int i = 0; i < adding_values.size(); i++)
	this->add(adding_values[i]);
}

void string_int::power(int range)
{
	/*
	Возведение в степень - умножение value n раз
	В начале сохраняется множитель затем поднимается до n-ой степени.
	Первоначальная степень = 1
	*/
	if (range == 0)
	{
		value = "1";
		return;
	}
	string mult = value;
	for (int i = 1; i < range; i++)
		this->multiplicate(mult);
}

int string_int::value_into_int()
{
	/*
	Перевод из string в integer
	*/
	int unswer = 0;
	for (int i = value.size() - 1; i >= 0; i--)
	{
		int temp = value[i] - '0';
		unswer = unswer + temp * pow(10, i);
	}
	return unswer;
}

void string_int::subtract(string subtr)
{
	if (compare(value, subtr) == "less") // Не поддерживает отрицательные значения
		return;
	/*
	Алгоритм вычитания столбиком:
	Необходим указатель на конец строки value и конец строки subtr
	В случае 100002 - 2 будут вчитаться value[0] и subtr[0]
	*/
	int j = value.size() - 1;
	for (int i = subtr.size() - 1; i >= 0; i--)
	{
		/*
		10003 - 41 = 10003 - 1 - 40 = 10002 - 40
		Во втором разряде с конца: 0 < 4
		*/
		int a = value[j] - '0';
		int b = subtr[i] - '0';
		if (a >= b)
			value[j] = a - b + '0';
		else
		{
			/*
			Раз 0<4, то нужно занять
			Заем из следующего разряда (i-1) -> (i-offset)
			Если занять из разряда нельзя, т.е. там 0, то ищем не "нулевой разряд",
			при этом преобразум остальные нули в '9'
			(1)0003 ->
			*/
			int offset = 1;

			while (value[j - offset] == '0')
			{
				value[j - offset] = '9';
				offset++;
			}
			value[j - offset]--; // Заем из первого ненулевого разряда
			value[j] = a - b + 10 + '0';
		}
		j--;
	}
	/*
	Проверка на наличие ситуаций: 000.001 (1.000.000-999.999)
	*/
	int zero_offset = 0;
	while (value[zero_offset] == '0')
		zero_offset++;

	string uns = "";
	for (int i = zero_offset; i < value.size(); i++)
		uns = uns + value[i];
	value = uns;
}

void divide(string divider)
{

}