#include <iostream>
#include <compare>

// Месяц
enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

// День недели
enum class WeekDay
{
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

struct DateData
{
	unsigned day;
	Month month;
	unsigned year;
};

// Дата в формате день-месяц-год. Год в диапазоне от 1970 до 9999
class Date
{
public:
	// инициализируем дату заданными днем, месяцем и годом.
	// примечание: год >= 1970
	Date(unsigned day, Month month, unsigned year);

	// инициализируем дату количеством дней, прошедших после 1 января 1970 года
	// например, 2 = 3 января 1970, 32 = 2 февраля 1970 года и т.д.
	explicit Date(unsigned timestamp);

	// Конструктор по умолчанию. Создаёт дату, равную 1 января 1970.
	Date();

	// возвращает день месяца (от 1 до 31)
	unsigned GetDay() const;

	// возвращает месяц
	Month GetMonth() const;

	// возвращает год
	unsigned GetYear() const;

	// возвращает день недели
	WeekDay GetWeekDay() const;

	// возвращает информацию о корректности хранимой даты.
	// Например, после вызова CDate date(99, static_cast<Month>(99), 10983);
	// или после:
	// CDate date(1, January, 1970); --date;
	// метод date.IsValid() должен вернуть false;
	bool IsValid() const; // См. примечание

	std::strong_ordering operator<=>(const Date& other) const = default;
	// bool operator==(const Date& other) const;

	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);

	Date operator+(int days) const;
	int operator+(const Date& other) const;
	Date operator-(int days) const;
	int operator-(const Date& other) const;
	Date& operator+=(int days);
	Date& operator-=(int days);

	friend std::ostream& operator<<(std::ostream& os, const Date& date);
	friend std::istream& operator>>(std::istream& is, Date& date);
	// std::os
private:
	int m_days;

	static bool IsLeapYear(int year);
	static int DaysInMonth(Month month, int year);
	static int DateToTimestamp(unsigned day, Month month, unsigned year);
	static DateData TimestampToDate(int timestamp);
};
