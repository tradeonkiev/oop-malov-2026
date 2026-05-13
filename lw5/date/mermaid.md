classDiagram
    class Date {
        + Date()
        + Date(day, month, year)
        + Date(timestamp)

        + GetDay() unsigned
        + GetMonth() Month
        + GetYear() unsigned
        + GetWeekDay() WeekDay
        + IsValid() bool

        + operator++()
        + operator--()
        + operator+(days) Date
        + operator-(days) Date
        + operator-(Date) int

        + operator==() bool
        + operator!=() bool
        + operator<() bool
        + operator>() bool
        + operator<=() bool
        + operator>=() bool

        + operator<<()
        + operator>>()

        - int m_days
        - IsLeapYear(year) bool
        - DaysInMonth(month, year) int
        - DateToTimestamp(day, month, year) int
        - TimestampToDate(timestamp) DateData
    }

    class DateData {
        + unsigned day
        + Month month
        + unsigned year
    }

    class Month {
        <<enumeration>>
        JANUARY
        FEBRUARY
        MARCH
        APRIL
        MAY
        JUNE
        JULY
        AUGUST
        SEPTEMBER
        OCTOBER
        NOVEMBER
        DECEMBER
    }

    class WeekDay {
        <<enumeration>>
        SUNDAY
        MONDAY
        TUESDAY
        WEDNESDAY
        THURSDAY
        FRIDAY
        SATURDAY
    }

    Date --> DateData
    Date --> Month
    Date --> WeekDay
