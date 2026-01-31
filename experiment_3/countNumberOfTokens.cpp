#include <bits/stdc++.h>

using namespace std;

set<string> keywords = {
    "int", "float", "double", "char", "if", "else", "while", "for",
    "return", "void", "break", "continue", "long", "short", "bool"};

set<char> delimiters = {';', ',', '(', ')', '{', '}', '[', ']'};

set<string> operators = {
    "+", "-", "*", "/", "%", "=", "==", "<=", ">=", "!=", "<", ">",
    "&&", "||", "++", "--"};

int main(int argc, char const *argv[])
{
    string filepath = "/workspaces/CD_LAB/experiment_3/in.c";
    ifstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open the file" << endl;
        return 1;
    }

    int kw = 0, id = 0, num = 0, lit = 0, op = 0, del = 0;
    string s((istreambuf_iterator<char>(file)), {});

    for (int i = 0; i < s.size();)
    {
        // skip preprocessor directives
        if (s[i] == '#') {
            while (i < s.size() && s[i] != '\n') i++;
        }
        // skip whitespaces
        else if (isspace(s[i]))
            i++;
        // skip comments
        else if (s[i] == '/' && s[i + 1] == '/')
        {
            while (i < s.size() && s[i] != '\n')
                i++;
        }
        else if (s[i] == '/' && s[i + 1] == '*')
        {
            i += 2;
            while (i < s.size() - 1 && !(s[i] == '*' && s[i + 1] == '/'))
                i++;
            i += 2;
        }
        // literals
        else if (s[i] == '"' || s[i] == '\'')
        {
            char q = s[i++];
            while (i < s.size() && s[i] != q)
                i++;
            i++;
            lit++;
        }
        // numbers
        else if (isdigit(s[i]))
        {
            while (i < s.size() && (isdigit(s[i]) || s[i] == '.'))
                i++;
            num++;
        }
        // identifiers / keywords
        else if (isalpha(s[i]) || s[i] == '_')
        {
            string t;
            while (i < s.size() && (isalnum(s[i]) || s[i] == '_'))
            {
                t += s[i++];
            }
            keywords.count(t) ? kw++ : id++;
        }
        // operators
        else if (i + 1 < s.size() && operators.count(s.substr(i, 2)))
        {
            op++;
            i += 2;
        }
        else if (operators.count(string(1, s[i])))
        {
            op++;
            i++;
        }
        // delimiters
        else if (delimiters.count(s[i]))
        {
            del++;
            i++;
        }
        else
            i++;
    }

    cout << "Keywords: " << kw << endl;
    cout << "Identifiers: " << id << endl;
    cout << "Numbers: " << num << endl;
    cout << "Literals: " << lit << endl;
    cout << "Operators: " << op << endl;
    cout << "Delimiters: " << del << endl;

    return 0;
}
