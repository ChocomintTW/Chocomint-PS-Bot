#ifndef _STRING_EX_
#define _STRING_EX_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <bitset>
#include <map>

namespace std
{
    string base64_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    class stringEX : public string
    {
    public:
        stringEX() : string(){};
        stringEX(const char *val) : string(val){};
        stringEX(const string val) : string(val){};

        vector<stringEX> split(const stringEX &ref);
        vector<stringEX> splitByLength(const int &len);
        void replaceAll(const stringEX &rep, const stringEX &ref);
        stringEX toHex(bool BIG);
        vector<int> toCharVector();
        stringEX toUpper();
        stringEX toLower();
        stringEX toURI(const stringEX &uri);
        void insertEX(int pos, stringEX &ref);

        friend char list(int &ref);
        friend stringEX base64_encode(string &ref);
        friend stringEX base64_encode(const char *ref);
        friend stringEX base64_decode(stringEX &ref);
        friend stringEX base64_encode(stringEX &ref, int times);
        friend stringEX base64_decode(stringEX &ref, int times);

        friend stringEX Str_merge(const stringEX &separator, vector<string> string_list);
        friend stringEX Str_merge(const stringEX &separator, vector<stringEX> string_list);

        friend stringEX operator""_utf8(const char *ref, size_t size);
    };

    vector<stringEX> stringEX::split(const stringEX &ref)
    {
        vector<stringEX> tmp;
        stringEX th = *this;
        while (th.find(ref) != string::npos)
        {
            int found = th.find(ref);
            tmp.push_back(th.substr(0, found));
            th.erase(0, found + ref.size());
        }
        tmp.push_back(th);
        return tmp;
    }

    vector<stringEX> stringEX::splitByLength(const int &len)
    {
        vector<stringEX> tmp;
        stringEX th = *this;
        while (th.size() > len)
        {
            tmp.push_back(th.substr(0, len));
            th.erase(0, len);
        }
        tmp.push_back(th);
        return tmp;
    }

    void stringEX::replaceAll(const stringEX &rep, const stringEX &ref)
    {
        while (this->find(rep) != string::npos)
        {
            int found = this->find(rep);
            this->erase(found, rep.size());
            this->insert(found, ref);
        }
    }

    stringEX stringEX::toHex(bool BIG = true)
    {
        ostringstream os;
        for (unsigned char const &c : *this)
        {
            os << hex << setprecision(2) << setw(2)
               << setfill('0') << static_cast<int>(c);
        }
        return BIG ? stringEX(os.str()).toUpper() : os.str();
    }

    vector<int> stringEX::toCharVector()
    {
        vector<int> tmp;
        for (unsigned char const &c : *this)
            tmp.push_back(static_cast<int>(c));
        return tmp;
    }

    stringEX stringEX::toUpper()
    {
        stringEX tmp = *this, container = "";
        for (char i : tmp)
            container += ((i >= 'a' && i <= 'z') ? (char)(i - 'a' + 'A') : i);
        return container;
    }
    stringEX stringEX::toLower()
    {
        stringEX tmp = *this, container = "";
        for (char i : tmp)
            container += ((i >= 'A' && i <= 'Z') ? (char)(i - 'A' + 'a') : i);
        return container;
    }

    stringEX Str_merge(const stringEX &separator, vector<stringEX> string_list)
    {
        stringEX tmp;
        int size = string_list.size();
        for (int i = 0; i < size; i++)
            tmp += string_list[i] + ((i == size - 1) ? "\0" : separator);
        return tmp;
    }
    stringEX Str_merge(const stringEX &separator, vector<string> string_list)
    {
        stringEX tmp;
        int size = string_list.size();
        for (int i = 0; i < size; i++)
            tmp += string_list[i] + ((i == size - 1) ? "\0" : separator);
        return tmp;
    }

    stringEX stringEX::toURI(const stringEX &uri = "")
    {
        return uri + "%" + Str_merge("%", stringEX(*this).toHex().splitByLength(2));
    }

    void stringEX::insertEX(int pos, stringEX &ref)
    {
        stringEX tmp = "\0";
        tmp += this->substr(0, pos - 1) + ref + this->substr(pos - 1);
        *this = tmp;
    }

    char list(int &ref)
    {
        if (ref == 62)
            return '+';
        else if (ref == 63)
            return '/';
        else
            return static_cast<char>((ref <= 25) ? (ref + 'A') : ((ref >= 52) ? (ref - 52 + '0') : (ref - 26 + 'a')));
    }

    stringEX base64_encode(stringEX &ref) // import general string | output base64
    {
        string c, tmp;
        vector<int> v(0);
        for (auto i : ref)
        {
            auto x = bitset<8>(i);
            for (int j = x.size() - 1; j >= 0; j--)
                v.push_back(x[j]);
        }
        for (int j = 0; j < v.size(); j++)
        {
            c += to_string(v[j]);
            if ((j + 1) % 6 == 0)
            {
                int ctmp = stoi(c, 0, 2);
                tmp += base64_list[ctmp];
                c.clear();
            }
        }
        if (c.size() != 0)
        {
            while (c.size() < 6)
                c += '0';
            int ctmp1 = stoi(c, 0, 2);
            tmp += base64_list[ctmp1];
        }
        tmp += (ref.size() % 3 == 1) ? "==" : ((ref.size() % 3 == 2) ? "=" : "\0");
        return tmp;
    }
    stringEX base64_encode(const char *ref)
    {
        stringEX tmp = ref;
        return base64_encode(tmp);
    }

    stringEX base64_decode(stringEX &ref) // import base64 | output string
    {
        string c, tmp;
        vector<int> v(0);
        for (auto i : ref)
        {
            if (i == '=')
                break;
            else
            {
                auto x = bitset<6>(base64_list.find(i));
                for (int j = x.size() - 1; j >= 0; j--)
                    v.push_back(x[j]);
            }
        }
        for (int j = 0; j < v.size(); j++)
        {
            c += to_string(v[j]);
            if ((j + 1) % 8 == 0)
            {
                int ctmp = stoi(c, 0, 2);
                tmp += (char)ctmp;
                c.clear();
            }
        }
        return tmp;
    }

    stringEX base64_encode(stringEX &ref, int times)
    {
        stringEX t = ref;
        for (int i = 0; i < times; i++)
            t = base64_encode(t);
        return t;
    }

    stringEX base64_decode(stringEX &ref, int times)
    {
        stringEX t = ref;
        for (int i = 0; i < times; i++)
            t = base64_decode(t);
        return t;
    }

    stringEX operator""_utf8(const char *ref, size_t size)
    {
        stringEX s(ref);
        return s.toHex();
    }
}

#endif