#pragma once
namespace Character
{
    bool isDigit(char c)
    {
        return c >= '0' && c <= '9';
    }

    int digit(char c, int radix)
    {
        if (radix == 10)
        {
            if (c >= '0' && c <= '9')
                return c - '0';
            else
                return -1;
        }
        else if (radix == 16)
        {
            if (c >= '0' && c <= '9')
                return c - '0';
            else if (c >= 'a' && c <= 'f')
                return c - 'a' + 10;
            else if (c >= 'A' && c <= 'F')
                return c - 'A' + 10;
            else
                return -1;
        }
        else if (radix == 2)
        {
            if (c == '0' || c == '1')
                return c - '0';
            else
                return -1;
        }
        else return -1;
    }

    bool isLetter(char c)
    {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    bool isLetterOrDigit(char c)
    {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    }
}
