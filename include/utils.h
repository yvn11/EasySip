/*
 * include/utils.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <iostream>

namespace EasySip
{
    #define CASE_UPPER_ALPHA \
                case 'A': \
                case 'B': \
                case 'C': \
                case 'D': \
                case 'E': \
                case 'F': \
                case 'G': \
                case 'H': \
                case 'I': \
                case 'J': \
                case 'K': \
                case 'L': \
                case 'M': \
                case 'N': \
                case 'O': \
                case 'P': \
                case 'Q': \
                case 'R': \
                case 'S': \
                case 'T': \
                case 'U': \
                case 'V': \
                case 'W': \
                case 'X': \
                case 'Y': \
                case 'Z':
    #define CASE_LOWER_ALPHA \
                case 'a': \
                case 'b': \
                case 'c': \
                case 'd': \
                case 'e': \
                case 'f': \
                case 'g': \
                case 'h': \
                case 'i': \
                case 'j': \
                case 'k': \
                case 'l': \
                case 'm': \
                case 'n': \
                case 'o': \
                case 'p': \
                case 'q': \
                case 'r': \
                case 's': \
                case 't': \
                case 'u': \
                case 'v': \
                case 'w': \
                case 'x': \
                case 'y': \
                case 'z':

    #define CASE_ALPHA \
            CASE_UPPER_ALPHA \
            CASE_LOWER_ALPHA 

    #define CASE_DIGIT \
                case '1': \
                case '2': \
                case '3': \
                case '4': \
                case '5': \
                case '6': \
                case '7': \
                case '8': \
                case '9': \
                case '0': 

    #define CASE_ALPHA_NUM \
            CASE_ALPHA \
            CASE_DIGIT 

    #define CASE_TOKEN \
                CASE_ALPHA_NUM \
                case '-': \
                case '.': \
                case '!': \
                case '%': \
                case '*': \
                case '_': \
                case '+': \
                case 39: \
                case '~':

    #define CASE_WORD \
                CASE_TOKEN \
                case '(': \
                case ')': \
                case '<': \
                case '>': \
                case ':': \
                case 92: \
                case 34: \
                case '/': \
                case '[': \
                case ']': \
                case '?': \
                case '{': \
                case '}': 

    #define do_if_is_alpha(c, f)     \
    {                                \
        std::locale loc;            \
        if (std::isalpha(c, loc)) { f; }    \
    }

    enum
    {
        PROCEDURE_OK,        // everything's normal
        MESSAGE_PROCESSED,    // message issue, but handled
        PROCEDURE_ERROR,    // something wrong, unhandled
    };

    #define PROGRESS_WITH_FEEDBACK(opr, cond, p)\
    {                                    \
        std::cout << opr;                \
        while (cond)                    \
        {                                \
            std::cout << " ..."; p;        \
        }                                \
        std::cout << "\n";                \
    }

    template<typename T>
    T& RefOf(T& t) { return t; }

    template<typename T>
    class PtsOf : public std::vector<T*>
    {
    public:
        PtsOf()
        {
        }

        void append_item()
        {
            this->push_back(new T);
        }

        void append_item(T &it)
        {
            this->push_back(new T(it));
        }

        T* first()
        {
            return this->at(0);
        }

        T* last()
        {
            return this->at(this->size()-1);
        }

        friend std::ostream& operator<< (std::ostream &o, PtsOf<T> &pts)
        {
            for (auto &it : pts)
            {
                o << *it;
            }

            return o;
        }
    };

    class CodeMap : public std::pair<int, std::string>
    {
    public:

        void Code(int c)
        {
            first = c;
        }

        void name(std::string n)
        {
            second = n;
        }

    public:

        int code() const
        {
            return first;
        }

        std::string name() const
        {
            return second;
        }

        CodeMap()
        {
        }

        CodeMap(int c)
        {
            first = c;
        }
    
        CodeMap(std::string n)
        {
            second = n;
        }

        CodeMap(int c, std::string n)
        {
            first = c;
            second = n;
        }

        std::string CodeStr() const
        {
            std::ostringstream o;
            o << first;
            return o.str();
        }

        bool operator< (CodeMap cm)
        {
            return (first < cm.first);
        }
    
        bool operator== (const CodeMap &cm)
        {
            return ((first == cm.first ) && (second == cm.second));
        }

        friend std::ostream& operator<< (std::ostream &o, CodeMap cm)
        {
            o << cm.first << " " << cm.second;
            return o;
        }

        std::string operator() ()
        {
            std::ostringstream o;
            o << first << " " << second << '\n';
            return o.str();
        }

        void operator() (CodeMap &cm)
        {
            *this = cm;
        }
    };

} // namespace EasiSip
