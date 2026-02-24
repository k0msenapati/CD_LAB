#include <bits/stdc++.h>

using namespace std;

int main()
{
    unordered_map<int, unordered_map<char, int>> t = {
        {0, {{'a', 1}, {'b', 1}}},
        {1, {{'a', 2}, {'b', 3}}},
        {2, {{'a', 2}, {'b', 2}}},
        {3, {{'a', 3}, {'b', 3}}}};
    set<int> final_states = {2};

    set<string> strings = {"aa", "bb", "bab", "aba"};

    for (const string &input : strings)
    {
        int current_state = 0;

        for (char c : input)
        {
            int next_state = t[current_state][c];
            current_state = next_state;
        }

        bool accepted = final_states.count(current_state);

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