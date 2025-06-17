#pragma once

#include <iostream>
#include <string>
#include "Char.h"
#include <vector>
using namespace std;



enum enWhattoCount { SmallLetter = 1, CapitalLetters = 2, Allletters = 3 };

namespace str {

    string Readtext(string message)
    {
        string text;
        cout << message;
        getline(cin, text);
        return text;
    }

    string UpperText(string& text)
    {
        for (char& letter : text)
        {
            if (letter != ' ')
            {
                letter = toupper(letter);
            }

        }
        return text;
    }

    string LowerText(string text)
    {
        for (char& letter : text)
        {
            if (letter != ' ')
            {
                letter = tolower(letter);
            }

        }
        return text;
    }

    string LowerFirstLetters(string text)
    {
        bool isFirstLetter = true;
        for (char& letter : text)
        {
            if (letter != ' ' && isFirstLetter)
            {
                letter = tolower(letter);
            }
            isFirstLetter = (letter == ' ') ? true : false;
        }
        return text;

    }

    string UpperFirstLetters(string text)
    {
        bool isFirstLetter = true;
        for (char& letter : text)
        {
            if (letter != ' ' && isFirstLetter)
            {
                letter = toupper(letter);
            }
            isFirstLetter = (letter == ' ') ? true : false;
        }
        return text;

    }

    string InvertString(string text)
    {
        for (char& letter : text)
        {
            letter = Char::InvertLetter(letter);
        }
        return text;
    }

    int CountCapitalLetters(string text)
    {
        int count = 0;
        for (char& letter : text)
        {
            if (letter != ' ')
            {
                if (isupper(letter))
                    ++count;
            }
        }
        return count;
    }

    int CountSmallLetters(string text)
    {
        int count = 0;
        for (char& letter : text)
        {
            if (letter != ' ')
            {
                if (islower(letter))
                    ++count;
            }
        }
        return count;
    }

    int Countstring(string text, enWhattoCount what = enWhattoCount::Allletters)
    {
        int count = 0;
        if (what == enWhattoCount::Allletters)
            return text.length();

        if (what == enWhattoCount::CapitalLetters)
            count = CountCapitalLetters(text);
        else
            count = CountSmallLetters(text);

        return count;
    }

    void PrintWordsfromText(string text)
    {
        string delimeter = " ";
        string word;
        int pos = 0;

        while ((pos = text.find(delimeter)) != string::npos) // while there are spaces inside the text
        {
            word = text.substr(0, pos);

            if (word != "")
            {
                cout << word << endl;
            }

            text.erase(0, pos + delimeter.length()); // adding delimeter length to pos is important to remove spaces
        }

        if (text != "")
        {
            cout << text << endl;  //printing last word, because if there's no space after it, it will not enter while loop
        }
    }

    short CountWordsInstring(string text) // "Mohammed Abu-Hadhoud @ProgrammingAdvices"
    {
        short count = 0;
        string delimeter = " ";
        int pos = 0;
        while ((pos = text.find(delimeter)) != string::npos)
        {
            string word = text.substr(0, pos); // Mohammed

            if (word != "")
            {
                ++count;
            }
            text.erase(0, pos + delimeter.length());

        }
        if (text != "")
        {
            ++count;
        }
        return count;
    }

    vector <string> SplitString(string& text, string delimeter)
    {
        vector <string> vWords;
        short pos = 0;

        while ((pos = text.find(delimeter)) != string::npos)
        {
            string word = text.substr(0, pos);

            if (word != "")
            {
                vWords.push_back(word);

            }
            text.erase(0, pos + delimeter.length());
        }
        if (text != "")
        {
            vWords.push_back(text);
        }
        return vWords;

    }

    string TrimLeft(string text)
    {

        for (short i = 0; i < text.length(); ++i)
        {
            if (text.at(i) != ' ')
            {
                return (text.substr(i));
            }

        }
        return "";
    }

    string TrimRight(string text)
    {
        for (short i = text.length() - 1; i >= 0; --i)
        {
            if (text.at(i) != ' ')
            {
                return (text.substr(0, i + 1));
            }

        }
        return "";
    }

    string Trim(string text)
    {
        return TrimRight(TrimLeft(text));
    }

    string JoinWithSeparator(string Names[100], short length, string seperator)
    {
        string result;
        for (short i = 0; i < length; ++i)
        {
            result += Names[i] + seperator;
        }

        return result.substr(0, result.length() - seperator.length());
    }

    string JoinWithSeparator(vector <string> vNames, string seperator)
    {
        string result;

        for (string& name : vNames)
        {
            result += name + seperator;
        }
        return result.substr(0, result.length() - seperator.length());
    }

    string RemovePunctiation(string text)
    {
        string textwithoutpunct;
        for (int i = 0; i < text.length(); ++i)
        {
            if (!ispunct(text.at(i)))
            {
                textwithoutpunct += text.at(i);

            }
        }
        return textwithoutpunct;
    }





}
