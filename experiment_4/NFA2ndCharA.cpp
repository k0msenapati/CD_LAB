#include <bits/stdc++.h>

using namespace std;

int main()
{
    unordered_map<int, unordered_map<char, set<int>>> t = {
        {0, {{'a', {1}}, {'b', {1}}}},
        {1, {{'a', {2}}}},
        {2, {{'a', {2}}, {'b', {2}}}}};
    set<int> final_states = {2};

    set<string> strings = {"aa", "bb", "bab", "aba"};

    for (const string &input : strings)
    {

        set<int> current_states = {0};

        for (char c : input)
        {
            set<int> next_states;

            for (int state : current_states)
            {
                if (t[state].count(c))
                {
                    for (int nxt : t[state][c])
                        next_states.insert(nxt);
                }
            }

            current_states = next_states;
        }

        bool accepted = false;
        for (int state : current_states)
            if (final_states.count(state))
                accepted = true;

        cout << input << " : "
             << (accepted ? "Accepted" : "Rejected") << endl;
    }
}

/*
Output:

aa : Accepted
aba : Rejected
bab : Accepted
bb : Rejected
*/