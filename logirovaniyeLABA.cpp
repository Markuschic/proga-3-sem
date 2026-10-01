#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <ctime>
#include <algorithm>

struct Data
{
    int year;
    int day;
    int month;
    int hour;
    int second;
    int minute;
};

struct User
{
    std::string name;
    Data errorDate;
    std::string error;
};

static std::mt19937 gen((std::random_device{}()));

bool visokosnyYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

uint8_t getDay(int year, int month)
{
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return visokosnyYear(year) ? 29 : 28;
    default:
        return 30;
    }
}

Data randomdate(int minYear, int maxYear)
{
    Data date;
    std::uniform_int_distribution<int> yearDist(minYear, maxYear);
    date.year = yearDist(gen);
    date.month = 1 + rand() % 12;
    int max_day = getDay(date.year, date.month);
    date.day = 1 + rand() % max_day;
    date.hour = rand() % 24;
    date.minute = rand() % 60;
    date.second = rand() % 60;
    return date;
}

std::string randomName()
{
    static const std::string names[] = {"user1", "user2", "user3", "user4", "user52", "user666", "user67", "user678", "user789", "user999"};
    int i = rand() % (10);
    return names[i];
}

std::string randomError()
{
    static const std::string fails[] = {"Error301", "Error302", "Error303", "Error304", "Error305", "Error400", "Error401", "Error403", "Error404", "Error408", "Error500", "Error502", "Error503", "Error504", "Error505"};
    int i = rand() % (10);
    return fails[i];
}
User randomUser(int minYear, int maxYear)
{
    User newuser;
    newuser.name = randomName();
    newuser.errorDate = randomdate(minYear, maxYear);
    newuser.error = randomError();
    return newuser;
}

std::string MostActiveUser(User users[], int count)
{
    std::string mostFrequent = "";
    int Maxcount = 0;
    for (int i = 0; i < count; ++i)
    {
        std::string CurrentUser = users[i].name;
        int currentcount = 0;
        for (int j = 0; j < count; ++j)
        {
            if (users[j].name == CurrentUser)
            {
                ++currentcount;
            }
        }
        if (currentcount > Maxcount)
        {
            Maxcount = currentcount;
            mostFrequent = CurrentUser;
        }
    }
    return mostFrequent;
}

std::string MostProblemUser(User users[], int count)
{
    std::string mostProblem = "";
    int Maxcount = 0;
    for (int i = 0; i < count; ++i)
    {
        std::string CurrentUser = users[i].name;
        int currentcount = 0;
        for (int j = 0; j < count; ++j)
        {
            if (users[j].name == CurrentUser && (users[j].error[5] == '4' || users[j].error[5] == '5'))
            {
                ++currentcount;
            }
        }
        if (currentcount > Maxcount)
        {
            Maxcount = currentcount;
            mostProblem = CurrentUser;
        }
    }
    return mostProblem;
}

bool CompareTime(const User &user1, const User &user2)
{
    return user1.errorDate.year < user2.errorDate.year;
    return user1.errorDate.month < user2.errorDate.month;
    return user1.errorDate.day < user2.errorDate.day;
    return user1.errorDate.hour < user2.errorDate.hour;
    return user1.errorDate.minute < user2.errorDate.minute;
    return user1.errorDate.second < user2.errorDate.second;
}

void saveToFile(std::ofstream &fout, const User &user)
{
    fout << std::left << std::setw(7) << user.name << ":   "
         << std::right << std::setfill('0') << std::setw(2) << std::setfill('0') << user.errorDate.day << "."
         << std::setw(2) << std::setfill('0') << user.errorDate.month << "."
         << std::setw(4) << user.errorDate.year << " "
         << std::setw(2) << std::setfill('0') << user.errorDate.hour << ":"
         << std::setw(2) << std::setfill('0') << user.errorDate.minute << ":"
         << std::setw(2) << std::setfill('0') << user.errorDate.second
         << "   " << user.error << '\n';
}

int main()
{
    try
    {
        srand(time(0));
        std::ofstream ofs("output.txt");
        if (!ofs.is_open())
        {
            std::cout << " Error to open file " << '\n';
            return -1;
        }
        int minYear = 1970;
        int maxYear = 2026;
        const int count = 20;
        User randUsers[count];
        for (int i = 0; i < count; ++i)
        {
            randUsers[i] = randomUser(minYear, maxYear);
        }
        std::sort(randUsers, randUsers + count, CompareTime);
        for (int i = 0; i < count; ++i)
        {
            saveToFile(ofs, randUsers[i]);
        }
        ofs << "The most active user: " << MostActiveUser(randUsers, count) << '\n';
        ofs << "The most problem user: " << MostProblemUser(randUsers, count) << '\n';
        ofs.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}

// int compareYear(const Data &date1, const Data &date2)
// {
//     if (date1.year < date2.year)
//     {
//         return 1;
//     }
//     if (date1.year > date2.year)
//     {
//         return 2;
//     }
//     return 0;
// }
// void sortingData(User users[], int left, int right)
// {
//     if (left < right)
//     {
//         int halfindex = left + (right - left) / 2;
//         int halfYear = users[halfindex].errorDate.year;
//         std::swap(users[halfindex], users[right]);
//         int i = left;
//         for (int j = left; j < right; ++j)
//         {
//             if (users[j].errorDate.year < halfYear)
//             {
//                 std::swap(users[i], users[j]);
//                 ++i;
//             }
//         }
//         std::swap(users[i], users[right]);
//         sortingData(users, left, i - 1);
//         sortingData(users, i + 1, right);
//     }
// }
// for (int i = 0; i < 10; ++i)
// {
//     size_t amount_of_seconds = randtime(min, max);
//     ofs << " Your random data: " << amount_of_seconds << '\n';
//     // convertSec_to_Data(ofs, amount_of_seconds);
// }
// size_t randtime(size_t min, size_t max)
// {
//     return min + static_cast<size_t>(rand() % (max - min + 1));
// }

// // void convertSec_to_Data(std::ofstream &fout, size_t amount)
// // {
// //     std::time_t data = static_cast<std::time_t>(amount);
// //     fout << ctime(&data) << " ";
// // }