#include "Header.h"// подключение заголовочного файла
/*Перегрузка операторов сравнения*/
bool operator== (wed w1, wed w2)
{
    return w1.male_name == w2.male_name and w1.marrige_date == w2.marrige_date;
}
bool operator!= (wed w1, wed w2)
{
    return (w1 != w2);
}
bool operator<= (wed w1, wed w2)
{
    return ((w1 < w2) || (w1 == w2));
}
bool operator>= (wed w1, wed w2)
{
    return ((w1 > w2) || (w1 == w2));
}
bool operator< (wed w1, wed w2)
{
    return((w1.male_name < w2.male_name) && (stoi(w1.marrige_date) < stoi(w2.marrige_date) || \
        (w1.marrige_date == w2.marrige_date)));// stoi переводит string в integer
}
bool operator> (wed w1, wed w2)
{
    return((w1.male_name > w2.male_name) && (stoi(w1.marrige_date) > stoi(w2.marrige_date) || \
        (w1.marrige_date == w2.marrige_date)));// stoi переводит string в integer
}
/*функция генерации полных женских имен*/
void female_names_generator(int number)
{
    /*генерация женских имен*/
    ofstream name_base("female_name_base.csv");// таблица с полными женскими ФИО
    ifstream name_1("Female_names_1.txt");// текстовый файл с женскими именами
    ifstream name_2("Female_names_2.txt");// текстовый файл с женскими фамилиями
    ifstream name_3("Female_names_3.txt");// текстовый файл с женскими отчествами
    /*создание нулевых векторов (имени, фамилии и отчества) для дальнейшего их заполнения*/
    /*Всего в файлах лежит по 100 имен, 100 фамилий и 100 отчеств*/
    vector<string> names_1(0);// вектор со всеми именами
    vector<string> names_2(0);// вектор со всеми фамилиями
    vector<string> names_3(0);// вектор со всеми отчествами
    /*Заполняем вектора*/
    for (int i = 0; i < 100; i++)
    {
        string buf;
        name_1 >> buf;
        names_1.push_back(buf);
        name_2 >> buf;
        names_2.push_back(buf);
        name_3 >> buf;
        names_3.push_back(buf);
    }
    /*В цикле рандомно из полученных векторов составляем фио количеством number*/
    for (int i = 0; i < number; i++)
    {
        name_base << names_1[rand() % 100] << ' ' << names_2[rand() % 100] \
            << ' ' << names_3[rand() % 100] << '\n';
    }
    /*закрыеваем файлы*/
    name_base.close();
    name_1.close();
    name_2.close();
    name_3.close();
}
/*заполнение базы данных*/
void generate_database(int number, string path)
{
    /*формируем и сразу записываем полные мужские имена в базу данных,
    фомирование происходит также, как и для женских имен*/
    ofstream database(path);// наша база данных
    ifstream name_1("Male_names_1.txt");// текстовый файл с мужскими именами
    ifstream name_2("Male_names_2.txt");// текстовый файл с мужскими фамилиями
    ifstream name_3("Male_names_3.txt");// текстовый файл с мужскими отчествами
    ifstream female_names("female_name_base.csv");// открыли таблицу с полными женскими именами
    /*создание нулевых векторов (имени, фамилии и отчества) для дальнейшего их заполнения*/
    /*Всего в файлах лежит по 100 имен, 100 фамилий и 100 отчеств*/
    vector<string> names_1(0);// вектор со всеми именами
    vector<string> names_2(0);// вектор со всеми фамилиями
    vector<string> names_3(0);// вектор со всеми отчествами
    /*Заполняем вектора*/
    for (int i = 0; i < 100; i++)
    {
        string buf;
        name_1 >> buf;
        names_1.push_back(buf);
        name_2 >> buf;
        names_2.push_back(buf);
        name_3 >> buf;
        names_3.push_back(buf);
    }
    /*генеиуем рандомную дату бракосочестания*/
    int month = 1 + (rand() % 12);
    int days = 31;
    int year = 2006 + (rand() % 13);
    if (month == 4 || month == 6 || month == 9 || month == 11)
        days = 30;
    else if (month == 2) //провека года на високосность, чтобы сделать в феврале 28 дней
    {
        if (year % 4 != 0)
            days = 28;
        else if (year % 100 != 0)
            days = 29;
        else if (year % 400 == 0)
            days = 29;
        else days = 28;
    }
    /*формируем и записываем окончательную строку (ФИО жениха, год рождения жениха,
    ФИО невесты, год рождения невесты, дата бакосочетания)*/

    for (int i = 0; i < number; i++)
    {
        string buf;// сюда будем записывать считанное уже сфомиованное полное имя невесты
        getline(female_names, buf);// считали полное женское имя
        database << names_1[rand() % 100] + ' ' + names_2[rand() % 100] \
            + ' ' + names_3[rand() % 100] + ';' + to_string(1970 + rand() % 30) + ';' + buf + ';' \
            + to_string(1970 + rand() % 30) + ';' + to_string(1 + rand() % days) + '.' + \
            to_string(month) + '.' + to_string(year) + '\n';
    }
    /*закрыеваем файлы*/
    database.close();
    name_1.close();
    name_2.close();
    name_3.close();
    female_names.close();
}
/*функция извлечения выгрузки базы данных в вектор*/
vector<wed> make_vector(string path)
{
    string buf;
    ifstream data(path);// откываем файл с базой данных
    vector<wed> record(0);// создаем пустой вектор
    while (getline(data, buf, ';'))// считываем из файла по разделителю пока не закончится файл 
    {
        int groom_birth, bride_birth;
        string groom_name, bride_name, wed_date;
        groom_name = buf;
        getline(data, buf, ';');
        groom_birth = stoi(buf);// переводим int в string
        getline(data, buf, ';');
        bride_name = buf;
        getline(data, buf, ';');
        bride_birth = stoi(buf);// переводим int в string
        getline(data, buf);
        wed_date = buf;
        record.push_back(wed(groom_name, groom_birth, bride_name, bride_birth, wed_date));
    }
    data.close();// закываем файл
    return record;
}
/*функция сотировки выбором*/
void selection_sorting(vector<wed>& num)
{
    int size = num.size();
    wed temp;// буфеная переменная для 
    int min; // индекс минимального элемента
    for (int i = 0; i < size; i++)
    {
        min = i; //индекс текущего элемента принимаем за минимальный
        /*поиск минимального элемента начиная с i + 1 - ого места*/
        for (int j = i + 1; j < size; j++)  // поход по всем элементам, начиная с i + 1 - ого
        {
            if (num[j] < num[min]) // если текущий элемент меньше минимального
                min = j;// запоминаем его индекс в min
        }
        temp = num[i];// меняем местами i-ый элемент и минимальный через буфеную переменную
        num[i] = num[min];
        num[min] = temp;
    }
}
/*функция шейкер-сортровки*/
void shaker_sorting(vector<wed>& num)
{
    int left = 0;// левая граница сортиуемой части массива
    int count = num.size();
    int right = count - 1;// правая граница сортиуемой части массива
    /*идем с обоих сторон справа и слева пока данные границы не сомкнуться и пока есть перемещения*/
    while ((left < right))
    {
        for (int i = left; i < right; i++)// проход слева на право
        {
            if (num[i] > num[i + 1])// если следующий меньше текущего, то меняем местами
            {
                wed t = num[i];// создаем времнную переменную
                num[i] = num[i + 1];
                num[i + 1] = t;
            }
        }
        right--;// сдвигаем правую границу на предыдущий элемент
        for (int i = right; i > left; i--)// проход справа налево
        {
            if (num[i - 1] > num[i]) // если предыдущий больше текущего, то меняем местами
            {
                wed t = num[i];// создаем времнную переменную
                num[i] = num[i - 1];
                num[i - 1] = t;
            }
        }
        left++;// сдвигаем левую границу на следующий элемент
    }
}
/*сама сотировка базы данных нужным способом*/
void sorting(void(*function)(vector<wed>&), string path_old, string path_new)
{
    vector<wed> a = make_vector(path_old);//записываем базу данных в вектор
    function(a);// сотируем данные
    ofstream data;
    data.open(path_new);// открываем базу данных для перезаписи
    for (int i = 0; i < a.size(); i++)
    {
        data << a[i].male_name + ";" + to_string(a[i].male_year) + ";" + a[i].female_name \
            + ";" + to_string(a[i].female_year) + ";" + a[i].marrige_date + "\n";
    }
    data.close();// закрываем файл
}
/*сортировка уже отсортированной базы данных*/
void time_of_sorting_unsorted_data(int n, void (*function)(vector<wed>&))
{
    unsigned int start_time = clock();// засекаем время выполнения сортировки
    sorting(function, "database.csv", "database(sorted).csv"); //сортировка данных
    unsigned int end_time = clock();
    cout << " время сортировки " << n << " элементов: " << (end_time - start_time) * 1.0 / 1000 \
        << ' c' << endl;
}
/*сортировка неотсортированных данных*/
void time_of_sorting_already_sorted_data(int n, void (*function)(vector<wed>&))
{
    unsigned int start_time = clock();// засекаем время выполнения сортировки
    sorting(function, "database(sorted).csv", "database.csv"); //сортировка данных
    unsigned int end_time = clock();
    cout << " время сортировки " << n << " элементов: " << (end_time - start_time) * 1.0 / 1000 \
        << ' c' << endl;
}
void menu()
{
    /*пользователь говоит сколько элементов отсотировать*/
    int b = 0;
    cout << "Press 1 to sort 100 items" << endl;
    cout << "Press 2 to sort 200 items" << endl;
    cout << "Press 3 to sort 400 items" << endl;
    cout << "Press 4 to sort 600 items" << endl;
    cout << "Press 5 to sort 800 items" << endl;
    cout << "Press 6 to sort 1000 items" << endl;
    cout << "Input the number: ";
    while (b < 1 || b > 6) // пока не ввели корректное значение повторяем ввод
    {
        cin >> b;
        if ((b < 1) || (b > 6))
        {
            cout << "WRONG INPUT!" << endl;
            cout << "Enter a number from 1 to 6" << endl;
            cin.clear();// очищаем поток ввода, если был введен символ типа, отличного от int 
            /*сдвигаемся максимально вправо, чтобы точно дойти до конца строки и перейти на новую*/
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    switch (b)
    {
    case 1:
    {
        
        female_names_generator(100);
        generate_database(100);
        cout << "Неотсотированные данные: " << endl;
        cout << "Shaker_sort:";
        time_of_sorting_unsorted_data(100, shaker_sorting);
        cout << "Selection_sort:";
        time_of_sorting_unsorted_data(100, selection_sorting);
        cout << "Заранее отсотированные данные: " << endl;
        cout << "Shaker_sort:";
        time_of_sorting_already_sorted_data(100, shaker_sorting);
        cout << "Selection_sort:";
        time_of_sorting_already_sorted_data(100, selection_sorting);
        break;
    }
    case 2:
    {
        female_names_generator(200);
        generate_database(200);
        cout << "Неотсотированные данные: " << endl;
        cout << "Shaker_sort:";
        time_of_sorting_unsorted_data(200, shaker_sorting);
        cout << "Selection_sort:";
        time_of_sorting_unsorted_data(200, selection_sorting);
        cout << "Заранее отсотированные данные: " << endl;
        cout << "Shaker_sort:";
        time_of_sorting_already_sorted_data(200, shaker_sorting);
        cout << "Selection_sort:";
        time_of_sorting_already_sorted_data(200, selection_sorting);
        break;
    }
    case 3:
    {
        female_names_generator(400);
        generate_database(400);
        cout << "Неотсотированные данные: " << endl;
        cout << "Shaker_sort:";
        time_of_sorting_unsorted_data(400, shaker_sorting);
        cout << "Selection_sort:";
        time_of_sorting_unsorted_data(400, selection_sorting);
        cout << "Заранее отсотированные данные: " << endl;
        cout << "Shaker_sort:";
        time_of_sorting_already_sorted_data(400, shaker_sorting);
        cout << "Selection_sort:";
        time_of_sorting_already_sorted_data(400, selection_sorting);
        break;
    }
    case 4:
    {
        
        female_names_generator(600);
        generate_database(600);
        cout << "Неотсотированные данные: " << endl;
        cout << "Shaker_sort:";
        time_of_sorting_unsorted_data(600, shaker_sorting);
        cout << "Selection_sort:";
        time_of_sorting_unsorted_data(600, selection_sorting);
        cout << "Заранее отсотированные данные: " << endl;
        cout << "Shaker_sort:";
        time_of_sorting_already_sorted_data(600, shaker_sorting);
        cout << "Selection_sort:";
        time_of_sorting_already_sorted_data(600, selection_sorting);
        break;
    }
    case 5:
    {
        female_names_generator(800);
        generate_database(800);
        cout << "Неотсотированные данные: " << endl;
        cout << "Shaker_sort:";
        time_of_sorting_unsorted_data(800, shaker_sorting);
        cout << "Selection_sort:";
        time_of_sorting_unsorted_data(800, selection_sorting);
        cout << "Заранее отсотированные данные: " << endl;
        cout << "Shaker_sort:";
        time_of_sorting_already_sorted_data(800, shaker_sorting);
        cout << "Selection_sort:";
        time_of_sorting_already_sorted_data(800, selection_sorting);
        break;
    }
    case 6:
    {
        for (int i = 0; i < 5; i++) {
            female_names_generator(1000);
            generate_database(1000);
            cout << "Неотсотированные данные: " << endl;
            cout << "Shaker_sort:";
            time_of_sorting_unsorted_data(1000, shaker_sorting);
            cout << "Selection_sort:";
            time_of_sorting_unsorted_data(1000, selection_sorting);
            cout << "Заранее отсотированные данные:" << endl;
            cout << "Shaker_sort:";
            time_of_sorting_already_sorted_data(1000, shaker_sorting);
            cout << "Selection_sort:";
            time_of_sorting_already_sorted_data(1000, selection_sorting);
        }
        break;
    }
    }
}
