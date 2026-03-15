#include <bits/stdc++.h>

using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> FIRST;

set<char> findFirst(char symbol)
{
    if (symbol < 'A' || symbol > 'Z')
        return {symbol};

    if (!FIRST[symbol].empty())
        return FIRST[symbol];

    set<char> result;

    for (string prod : grammar[symbol])
    {
        for (int i = 0; i < prod.size(); i++)
        {
            char c = prod[i];

            set<char> temp = findFirst(c);

            for (char x : temp)
            {
                if (x != '#')
                    result.insert(x);
            }

            if (temp.find('#') == temp.end())
                break;

            if (i == prod.size() - 1)
                result.insert('#');
        }
    }

    FIRST[symbol] = result;
    return result;
}

int main()
{
    string g =
        "E->TX\n"
        "X->+TX|#\n"
        "T->FY\n"
        "Y->*FY|#\n"
        "F->(E)|i";

    stringstream ss(g);
    string line;

    while (getline(ss, line))
    {
        char lhs = line[0];
        string rhs = line.substr(3);

        string temp = "";

        for (char c : rhs)
        {
            if (c == '|')
            {
                grammar[lhs].push_back(temp);
                temp = "";
            }
            else
                temp += c;
        }
        grammar[lhs].push_back(temp);
    }

    for (auto &p : grammar)
        findFirst(p.first);

    for (auto &p : grammar)
    {
        for (string prod : p.second)
        {
            for (char c : prod)
            {
                if (c < 'A' || c > 'Z')
                    FIRST[c] = {c};
            }
        }
    }

    for (auto &p : FIRST)
    {
        cout << "FIRST(" << p.first << ") = { ";
        for (char c : p.second)
            cout << c << " ";
        cout << "}" << endl;
    }
}

/*
Output:

FIRST(#) = { # }
FIRST(() = { ( }
FIRST()) = { ) }
FIRST(*) = { * }
FIRST(+) = { + }
FIRST(E) = { ( i }
FIRST(F) = { ( i }
FIRST(T) = { ( i }
FIRST(X) = { # + }
FIRST(Y) = { # * }
FIRST(i) = { i }
*/