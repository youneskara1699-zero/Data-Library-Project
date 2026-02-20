#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdio>  // Added for printf

using namespace std;

class clsString
{
public:
    static vector<string> Split(string s, string delimiter)
    {
        vector<string> v;
        size_t pos = 0;
        string token;
        while ((pos = s.find(delimiter)) != string::npos)
        {
            token = s.substr(0, pos);
            v.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        v.push_back(s);
        return v;
    }
};

class clsDate
{
private:
    short Day;
    short Month;
    short Year;

public:
    clsDate()
    {
        time_t t = time(0);
        tm* now = localtime(&t);
        Day = now->tm_mday;
        Month = now->tm_mon + 1;
        Year = now->tm_year + 1900;
    }

    clsDate(string sDate)
    {
        vector<string> vDate;
        vDate = clsString::Split(sDate, "/");
        Day = stoi(vDate[0]);
        Month = stoi(vDate[1]);
        Year = stoi(vDate[2]);
    }

    clsDate(short day, short month, short year)
    {
        Day = day;
        Month = month;
        Year = year;
    }

    clsDate(short DateOrderInYear, short year)
    {
        // This will construct a date by date order in year
        clsDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, year);
        Day = Date1.getDay();
        Month = Date1.getMonth();
        Year = Date1.getYear();
    }

    short getDay() { return Day; }
    void setDay(short day) { Day = day; }

    short getMonth() { return Month; }
    void setMonth(short month) { Month = month; }

    short getYear() { return Year; }
    void setYear(short year) { Year = year; }

    void Print()
    {
        cout << DateToString() << endl;
    }

    static clsDate GetSystemDate()
    {
        time_t t = time(0);
        tm* now = localtime(&t);
        short Day, Month, Year;
        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;
        return clsDate(Day, Month, Year);
    }

    static bool IsValidDate(clsDate Date)
    {
        if (Date.Day < 1 || Date.Day > 31)
            return false;
        if (Date.Month < 1 || Date.Month > 12)
            return false;
        if (Date.Month == 2)
        {
            if (isLeapYear(Date.Year))
            {
                if (Date.Day > 29)
                    return false;
            }
            else
            {
                if (Date.Day > 28)
                    return false;
            }
        }
        short DaysInMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
        if (Date.Day > DaysInMonth)
            return false;
        return true;
    }

    bool IsValid()
    {
        return IsValidDate(*this);
    }

    static string DateToString(clsDate Date)
    {
        return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
    }

    string DateToString()
    {
        return DateToString(*this);
    }

    static bool isLeapYear(short Year)
    {
        return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    }

    bool isLeapYear()
    {
        return isLeapYear(Year);
    }

    static short NumberOfDaysInAYear(short Year)
    {
        return isLeapYear(Year) ? 366 : 365;
    }

    short NumberOfDaysInAYear()
    {
        return NumberOfDaysInAYear(Year);
    }

    static short NumberOfHoursInAYear(short Year)
    {
        return NumberOfDaysInAYear(Year) * 24;
    }

    short NumberOfHoursInAYear()
    {
        return NumberOfHoursInAYear(Year);
    }

    static int NumberOfMinutesInAYear(short Year)
    {
        return NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfMinutesInAYear()
    {
        return NumberOfMinutesInAYear(Year);
    }

    static int NumberOfSecondsInAYear(short Year)
    {
        return NumberOfMinutesInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear()
    {
        return NumberOfSecondsInAYear(Year);
    }

    static short NumberOfDaysInAMonth(short Month, short Year)
    {
        if (Month < 1 || Month > 12)
            return 0;
        int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : days[Month - 1];
    }

    short NumberOfDaysInAMonth()
    {
        return NumberOfDaysInAMonth(Month, Year);
    }

    static short NumberOfHoursInAMonth(short Month, short Year)
    {
        return NumberOfDaysInAMonth(Month, Year) * 24;
    }

    short NumberOfHoursInAMonth()
    {
        return NumberOfHoursInAMonth(Month, Year);
    }

    static int NumberOfMinutesInAMonth(short Month, short Year)
    {
        return NumberOfHoursInAMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInAMonth()
    {
        return NumberOfMinutesInAMonth(Month, Year);
    }

    static int NumberOfSecondsInAMonth(short Month, short Year)
    {
        return NumberOfMinutesInAMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInAMonth()
    {
        return NumberOfSecondsInAMonth(Month, Year);
    }

    static short DayOfWeekOrder(short Day, short Month, short Year)
    {
        short a, y, m;
        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2;
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    short DayOfWeekOrder()
    {
        return DayOfWeekOrder(Day, Month, Year);
    }

    static string DayShortName(short DayOfWeekOrder)
    {
        string arrDayNames[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
        return arrDayNames[DayOfWeekOrder];
    }

    static string DayShortName(short Day, short Month, short Year)
    {
        return DayShortName(DayOfWeekOrder(Day, Month, Year));
    }

    string DayShortName()
    {
        return DayShortName(Day, Month, Year);
    }

    static string MonthShortName(short MonthNumber)
    {
        string Months[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
        return Months[MonthNumber - 1];
    }

    string MonthShortName()
    {
        return MonthShortName(Month);
    }

    static void PrintMonthCalendar(short Month, short Year)
    {
        int NumberOfDays;
        int current = DayOfWeekOrder(1, Month, Year);
        NumberOfDays = NumberOfDaysInAMonth(Month, Year);

        printf("\n  _______________%s_______________\n\n", MonthShortName(Month).c_str());
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        int i;
        for (i = 0; i < current; i++)
            printf("     ");

        for (int j = 1; j <= NumberOfDays; j++)
        {
            printf("%5d", j);
            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }
        printf("\n  _________________________________\n");
    }

    void PrintMonthCalendar()
    {
        PrintMonthCalendar(Month, Year);
    }

    static void PrintYearCalendar(int Year)
    {
        printf("\n  _________________________________\n\n");
        printf("           Calendar - %d\n", Year);
        printf("  _________________________________\n");
        for (int i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(i, Year);
        }
    }

    void PrintYearCalendar()
    {
        PrintYearCalendar(Year);
    }

    static short DaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
    {
        short TotalDays = 0;
        for (int i = 1; i <= Month - 1; i++)
        {
            TotalDays += NumberOfDaysInAMonth(i, Year);
        }
        TotalDays += Day;
        return TotalDays;
    }

    short DaysFromTheBeginingOfTheYear()
    {
        return DaysFromTheBeginingOfTheYear(Day, Month, Year);
    }

    static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
    {
        clsDate Date(1, 1, Year);
        short RemainingDays = DateOrderInYear;
        short MonthDays = 0;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date.Month, Year);
            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date.Month++;
            }
            else
            {
                Date.Day = RemainingDays;
                break;
            }
        }
        return Date;
    }

    void AddDays(short Days)
    {
        short RemainingDays = Days + DaysFromTheBeginingOfTheYear(Day, Month, Year);
        short MonthDays = 0;
        Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Month, Year);
            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Month++;
                if (Month > 12)
                {
                    Month = 1;
                    Year++;
                }
            }
            else
            {
                Day = RemainingDays;
                break;
            }
        }
    }

    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1.Year < Date2.Year) ? true :
               (Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true :
               (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false;
    }

    bool IsDate1BeforeDate2(clsDate Date2)
    {
        return IsDate1BeforeDate2(*this, Date2);
    }

    static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1.Year == Date2.Year) &&
               (Date1.Month == Date2.Month) &&
               (Date1.Day == Date2.Day);
    }

    bool IsDate1EqualDate2(clsDate Date2)
    {
        return IsDate1EqualDate2(*this, Date2);
    }

    static bool IsLastDayInMonth(clsDate Date)
    {
        return (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year));
    }

    bool IsLastDayInMonth()
    {
        return IsLastDayInMonth(*this);
    }

    static bool IsLastMonthInYear(short Month)
    {
        return (Month == 12);
    }

    static clsDate AddOneDay(clsDate Date)
    {
        if (IsLastDayInMonth(Date))
        {
            if (IsLastMonthInYear(Date.Month))
            {
                Date.Month = 1;
                Date.Day = 1;
                Date.Year++;
            }
            else
            {
                Date.Day = 1;
                Date.Month++;
            }
        }
        else
        {
            Date.Day++;
        }
        return Date;
    }

    void AddOneDay()
    {
        clsDate temp = AddOneDay(*this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static void SwapDates(clsDate& Date1, clsDate& Date2)
    {
        clsDate TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }

    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        short SwapFlagValue = 1;

        if (!IsDate1BeforeDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
            SwapFlagValue = -1;
        }

        while (IsDate1BeforeDate2(Date1, Date2))
        {
            Days++;
            Date1 = AddOneDay(Date1);
        }

        return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
    }

    int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
    {
        return GetDifferenceInDays(*this, Date2, IncludeEndDay);
    }

    static short CalculateMyAgeInDays(clsDate DateOfBirth)
    {
        return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
    }

    static clsDate IncreaseDateByOneWeek(clsDate Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = AddOneDay(Date);
        }
        return Date;
    }

    void IncreaseDateByOneWeek()
    {
        clsDate temp = IncreaseDateByOneWeek(*this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate IncreaseDateByXWeeks(short Weeks, clsDate Date)
    {
        for (short i = 1; i <= Weeks; i++)
        {
            Date = IncreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void IncreaseDateByXWeeks(short Weeks)
    {
        clsDate temp = IncreaseDateByXWeeks(Weeks, *this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate IncreaseDateByOneMonth(clsDate Date)
    {
        if (Date.Month == 12)
        {
            Date.Month = 1;
            Date.Year++;
        }
        else
        {
            Date.Month++;
        }

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }
        return Date;
    }

    void IncreaseDateByOneMonth()
    {
        clsDate temp = IncreaseDateByOneMonth(*this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate IncreaseDateByXDays(short Days, clsDate Date)
    {
        for (short i = 1; i <= Days; i++)
        {
            Date = AddOneDay(Date);
        }
        return Date;
    }

    void IncreaseDateByXDays(short Days)
    {
        clsDate temp = IncreaseDateByXDays(Days, *this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate IncreaseDateByXMonths(short Months, clsDate Date)
    {
        for (short i = 1; i <= Months; i++)
        {
            Date = IncreaseDateByOneMonth(Date);
        }
        return Date;
    }

    void IncreaseDateByXMonths(short Months)
    {
        clsDate temp = IncreaseDateByXMonths(Months, *this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate IncreaseDateByOneYear(clsDate Date)
    {
        Date.Year++;
        return Date;
    }

    void IncreaseDateByOneYear()
    {
        clsDate temp = IncreaseDateByOneYear(*this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate IncreaseDateByXYears(short Years, clsDate Date)
    {
        Date.Year += Years;
        return Date;
    }

    void IncreaseDateByXYears(short Years)
    {
        clsDate temp = IncreaseDateByXYears(Years, *this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate IncreaseDateByOneDecade(clsDate Date)
    {
        Date.Year += 10;
        return Date;
    }

    void IncreaseDateByOneDecade()
    {
        clsDate temp = IncreaseDateByOneDecade(*this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate IncreaseDateByXDecades(short Decade, clsDate Date)
    {
        Date.Year += Decade * 10;
        return Date;
    }

    void IncreaseDateByXDecades(short Decade)
    {
        clsDate temp = IncreaseDateByXDecades(Decade, *this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate IncreaseDateByOneCentury(clsDate Date)
    {
        Date.Year += 100;
        return Date;
    }

    void IncreaseDateByOneCentury()
    {
        clsDate temp = IncreaseDateByOneCentury(*this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate IncreaseDateByOneMillennium(clsDate Date)
    {
        Date.Year += 1000;
        return Date;
    }

    void IncreaseDateByOneMillennium()
    {
        clsDate temp = IncreaseDateByOneMillennium(*this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate DecreaseDateByOneDay(clsDate Date)
    {
        if (Date.Day == 1)
        {
            if (Date.Month == 1)
            {
                Date.Month = 12;
                Date.Day = 31;
                Date.Year--;
            }
            else
            {
                Date.Month--;
                Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
            }
        }
        else
        {
            Date.Day--;
        }
        return Date;
    }

    void DecreaseDateByOneDay()
    {
        clsDate temp = DecreaseDateByOneDay(*this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate DecreaseDateByOneWeek(clsDate Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }

    void DecreaseDateByOneWeek()
    {
        clsDate temp = DecreaseDateByOneWeek(*this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate DecreaseDateByXWeeks(short Weeks, clsDate Date)
    {
        for (short i = 1; i <= Weeks; i++)
        {
            Date = DecreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void DecreaseDateByXWeeks(short Weeks)
    {
        clsDate temp = DecreaseDateByXWeeks(Weeks, *this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate DecreaseDateByOneMonth(clsDate Date)
    {
        if (Date.Month == 1)
        {
            Date.Month = 12;
            Date.Year--;
        }
        else
            Date.Month--;

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }
        return Date;
    }

    void DecreaseDateByOneMonth()
    {
        clsDate temp = DecreaseDateByOneMonth(*this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate DecreaseDateByXDays(short Days, clsDate Date)
    {
        for (short i = 1; i <= Days; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }

    void DecreaseDateByXDays(short Days)
    {
        clsDate temp = DecreaseDateByXDays(Days, *this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate DecreaseDateByXMonths(short Months, clsDate Date)
    {
        for (short i = 1; i <= Months; i++)
        {
            Date = DecreaseDateByOneMonth(Date);
        }
        return Date;
    }

    void DecreaseDateByXMonths(short Months)
    {
        clsDate temp = DecreaseDateByXMonths(Months, *this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate DecreaseDateByOneYear(clsDate Date)
    {
        Date.Year--;
        return Date;
    }

    void DecreaseDateByOneYear()
    {
        clsDate temp = DecreaseDateByOneYear(*this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate DecreaseDateByXYears(short Years, clsDate Date)
    {
        Date.Year -= Years;
        return Date;
    }

    void DecreaseDateByXYears(short Years)
    {
        clsDate temp = DecreaseDateByXYears(Years, *this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate DecreaseDateByOneDecade(clsDate Date)
    {
        Date.Year -= 10;
        return Date;
    }

    void DecreaseDateByOneDecade()
    {
        clsDate temp = DecreaseDateByOneDecade(*this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate DecreaseDateByXDecades(short Decades, clsDate Date)
    {
        Date.Year -= Decades * 10;
        return Date;
    }

    void DecreaseDateByXDecades(short Decades)
    {
        clsDate temp = DecreaseDateByXDecades(Decades, *this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate DecreaseDateByOneCentury(clsDate Date)
    {
        Date.Year -= 100;
        return Date;
    }

    void DecreaseDateByOneCentury()
    {
        clsDate temp = DecreaseDateByOneCentury(*this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static clsDate DecreaseDateByOneMillennium(clsDate Date)
    {
        Date.Year -= 1000;
        return Date;
    }

    void DecreaseDateByOneMillennium()
    {
        clsDate temp = DecreaseDateByOneMillennium(*this);
        Day = temp.Day;
        Month = temp.Month;
        Year = temp.Year;
    }

    static short IsEndOfWeek(clsDate Date)
    {
        return DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
    }

    short IsEndOfWeek()
    {
        return IsEndOfWeek(*this);
    }

    static bool IsWeekEnd(clsDate Date)
    {
        short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
        return (DayIndex == 5 || DayIndex == 6);
    }

    bool IsWeekEnd()
    {
        return IsWeekEnd(*this);
    }

    static bool IsBusinessDay(clsDate Date)
    {
        return !IsWeekEnd(Date);
    }

    bool IsBusinessDay()
    {
        return IsBusinessDay(*this);
    }

    static short DaysUntilTheEndOfWeek(clsDate Date)
    {
        return 6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
    }

    short DaysUntilTheEndOfWeek()
    {
        return DaysUntilTheEndOfWeek(*this);
    }

    static short DaysUntilTheEndOfMonth(clsDate Date1)
    {
        clsDate EndOfMontDate;
        EndOfMontDate.Day = NumberOfDaysInAMonth(Date1.Month, Date1.Year);
        EndOfMontDate.Month = Date1.Month;
        EndOfMontDate.Year = Date1.Year;
        return GetDifferenceInDays(Date1, EndOfMontDate, true);
    }

    short DaysUntilTheEndOfMonth()
    {
        return DaysUntilTheEndOfMonth(*this);
    }

    static short DaysUntilTheEndOfYear(clsDate Date1)
    {
        clsDate EndOfYearDate;
        EndOfYearDate.Day = 31;
        EndOfYearDate.Month = 12;
        EndOfYearDate.Year = Date1.Year;
        return GetDifferenceInDays(Date1, EndOfYearDate, true);
    }

    short DaysUntilTheEndOfYear()
    {
        return DaysUntilTheEndOfYear(*this);
    }

    static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
    {
        short Days = 0;
        while (IsDate1BeforeDate2(DateFrom, DateTo))
        {
            if (IsBusinessDay(DateFrom))
                Days++;
            DateFrom = AddOneDay(DateFrom);
        }
        return Days;
    }

    static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
    {
        return CalculateBusinessDays(DateFrom, DateTo);
    }

    static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
    {
        short WeekEndCounter = 0;
        for (short i = 1; i <= VacationDays; i++)
        {
            if (IsWeekEnd(DateFrom))
                WeekEndCounter++;
            DateFrom = AddOneDay(DateFrom);
        }
        for (short i = 1; i <= WeekEndCounter; i++)
            DateFrom = AddOneDay(DateFrom);
        return DateFrom;
    }

    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
    }

    bool IsDate1AfterDate2(clsDate Date2)
    {
        return IsDate1AfterDate2(*this, Date2);
    }

    enum enDateCompare { Before = -1, Equal = 0, After = 1 };

    static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2))
            return enDateCompare::Before;
        if (IsDate1EqualDate2(Date1, Date2))
            return enDateCompare::Equal;
        return enDateCompare::After;
    }

    enDateCompare CompareDates(clsDate Date2)
    {
        return CompareDates(*this, Date2);
    }
};

int main()
{
    clsDate Date1;
    Date1.Print();

    clsDate Date2("31/1/2022");
    Date2.Print();

    clsDate Date3(20, 12, 2022);
    Date3.Print();

    clsDate Date4(250, 2022);
    Date4.Print();

    Date1.IncreaseDateByOneMonth();
    Date1.Print();

    Date3.PrintYearCalendar();
    cout << Date2.IsValid() << endl;

    cout << "My Age InDays: "
         << clsDate::CalculateMyAgeInDays(clsDate(6, 11, 1977)) << endl;

    system("pause>0");
    return 0;
}
