#pragma once

#include <iostream>
using namespace std;

namespace Num
{

    int ReadPositiveNumber(string message)
    {
            int number = 0;
            cout << message;
            cin >> number;
            while (number <= 0 || cin.fail())
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                cout << "Invaild Number, Enter a valid one: ";
                cin >> number;
            }

        return number;
    }

    int ReadAnyNumber(string message)
    {
        int number = 0;
        cout << message;
        cin >> number;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Invaild Number, Enter a valid one: ";
            cin >> number;
        }
        return number;
    }

    int RandomNumber(int From, int To)
    {
        int randnum = rand() % (To - From + 1) + From;
        return randnum;
    }

    void SwapNumbers(int& num1, int& num2)
    {
        int  temp = num1;
        num1 = num2;
        num2 = temp;
    }

    int SumOfDigits(int number)
    {
        int remainder = 0, sum = 0;
        while (number > 0)
        {
            remainder = number % 10;
            number = number / 10;
            sum += remainder;
        }
        return sum;
    }

    int NumberReversed(int number)
    {
        int Number2 = 0, remainder = 0;

        while (number > 0) // 1234
        {
            remainder = number % 10;   //4
            number = number / 10;
            Number2 = Number2 * 10 + remainder;
        }
        return Number2;
    }

    float ReadFLoat(string message)
    {
        float number = 0;
        cout << message;
        cin >> number;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Invaild Number, Enter a valid one: ";
            cin >> number;
        }
        return number;
    }

}
