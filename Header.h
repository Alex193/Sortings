#pragma once
#include <iostream>// библиотека ввода-вывода
#include <fstream>// библиотека для работы с файлами
#include <string>// библиотека для работы со строками
#include <time.h>// библиотека для работы со временем
#include <vector>// библиотека для создания вектора
#include <cstdlib>// библиотека для работы с функцией srand
using namespace std;
class wed 
{
public:
	string male_name;// фио жениха
	string female_name;// фио невесты
	string marrige_date;
	int male_year;// год рождения жениха
	int female_year;// год рождения невесты
	/*констуктор класса*/
	wed(string _male_name = "None", int _male_year = 0, string _female_name = "None", \
		int _female_year = 0, string _marrige_date = "None")
	{
		male_name = _male_name;
		male_year = _male_year;
		female_name = _female_name;
		female_year = _female_year;
		marrige_date = _marrige_date;
	}
	//wed(string& s);
	/*дружественные функции операторов сравнения*/
	friend bool operator== (wed b1, wed b2);
	friend bool operator< (wed b1, wed b2);
	friend bool operator> (wed b1, wed b2);
	friend bool operator<= (wed b1, wed b2);
	friend bool operator>= (wed b1, wed b2);
};
/*прототипы некоых */
void generate_database(int number, string path = "database.csv");// генерациая полной базы данных
void menu();// функция меню
