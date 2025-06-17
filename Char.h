#pragma once

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


namespace Char
{
    char ReadChar(string message)
    {
        char character;
        cout << message;
        cin >> character;
        return character;
    }

    char InvertLetter(char letter)
    {
        return (isupper(letter)) ? tolower(letter) : toupper(letter);
    }

    int CountChar(char character, string text, bool Matchcase = true)
    {
        int counter = 0;

        for (char& letter : text)
        {
        if (Matchcase)                // count the character as its case
        {
            if (letter == character)
                ++counter;
        }
        else
        {
            if (tolower(letter) == tolower(character))
                ++counter;
        }
        }

        return counter;
    }

    bool isVowel(char character)
    {
        char vowels[6] = { 'a', 'e', 'i', 'o', 'y', 'u' };

        for (char& vowel : vowels)
        {
            if (vowel == tolower(character))
                return true;
        }
        return false;

    }

    int CountVowels(string text)
    {
        int counter = 0;
        for (char& letter : text)
        {
            if (Char::isVowel(letter))
            {
                ++counter;
            }
        }
        return counter;
    }

    void PrintVowels(string text)
    {
        for (char& letter : text)
        {
            if (Char::isVowel(letter))
                cout << letter << setw(3);
        }
    }


}
