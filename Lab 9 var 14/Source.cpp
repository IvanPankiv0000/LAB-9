#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>

using namespace std;

//структура данных;
struct Time
{
	int hour;
	int minute;
	int second;
	bool isCorrect();
};

//проверка корректности;
bool Time::isCorrect()
{
	if (hour <= 23 && hour >= 0)
	{
		if (minute <= 59 && minute >= 0)
		{
			if (second <= 59 && second >= 0)
			{
				return true;
			}
		}
	}

	return false;
}

void easy()
{
	//определяем нынешнее время;
	Time input_time;
	struct tm* entered, start_time;
	double seconds;
	char formatted[80];
	time_t entered_time = time(NULL);
	entered = localtime(&entered_time);

	do
	{
		cout << "Введите часы, минуты и секунды для форматирования: ";
		cin >> input_time.hour >> input_time.minute >> input_time.second;
		cout << endl;
	} while (!input_time.isCorrect());

	//после ввода значений записываем их в спец. структуру tm;
	entered->tm_hour = input_time.hour;
	entered->tm_min = input_time.minute;
	entered->tm_sec = input_time.second;

	//выводим время в нужном формате;
	strftime(formatted, sizeof(formatted), "%H %M %S", entered);
	cout << "Введенное время: " << formatted << endl << endl;

	//вводим время для нахождения разницы;
	cout << "Теперь введите время для отталкивания(год, месяц, число, день недели, часы, минуты, секунды): ";
	cin >> start_time.tm_year >> start_time.tm_mon >> start_time.tm_mday >> start_time.tm_wday >> start_time.tm_hour >> start_time.tm_min >> start_time.tm_sec;

	start_time.tm_mon -= 1;
	start_time.tm_wday -= 1;
	start_time.tm_year -= 1900;

	cout << endl;

	//находим разницу;
	seconds = difftime(mktime(entered), start_time.tm_year + start_time.tm_mon + start_time.tm_mday + start_time.tm_wday + start_time.tm_hour + start_time.tm_min + start_time.tm_sec);
	seconds = abs(seconds / 86400);

	cout << seconds << " дней осталось до дня голосования" << endl;
	cout << seconds - 1 << " дней до конца агитации" << endl << endl;
}

int main()
{
	setlocale(LC_ALL, "RU");

	int count, b;

	easy();

	do
	{
		count = 0;

		cout << "Продолжить ввод? Да - 1, Нет - 2: ";

		cin >> b;

		cout << endl;

		if (b == 1)
		{
			count++;
			main();
		}

		if (b == 2)
		{
			cout << "Вы решили не продолжать";
			count++;
			break;
		}

	} while (count == 0);
}