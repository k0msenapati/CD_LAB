#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
    string filepath = "/workspaces/CD_LAB/experiment_2/in.c";
    ifstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open the file" << endl;
        return 1;
    }

    int comments = 0;
    bool inBlock = false;
    char prev = 0, cur;

    while (file.get(cur))
    {
        if (!inBlock && prev == '/' && cur == '/')
        {
            comments++;
            while (file.get(cur) && cur != '\n')
                ;
            prev = 0;
            continue;
        }

        if (!inBlock && prev == '/' && cur == '*')
        {
            comments++;
            inBlock = true;
            prev = 0;
            continue;
        }

        if (inBlock && prev == '*' && cur == '/')
        {
            inBlock = false;
            prev = 0;
            continue;
        }

        prev = cur;
    }

    cout << "Number of comments: " << comments << endl;

    return 0;
}

/*
Output:

Number of comments: 3
*/