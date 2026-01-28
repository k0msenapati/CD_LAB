#include <bits/stdc++.h>

using namespace std;

int precedence(char op)
{
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return -1;
}

bool isRightAssociative(char op)
{
    return op == '^';
}

bool isOperator(char ch)
{
    return (ch == '^') || (ch == '*') || (ch == '/') || (ch == '+') || (ch == '-');
}

string infixToPrefix(string s)
{
    stack<char> st;
    string result;

    reverse(s.begin(), s.end());
    for (char ch : s)
    {
        if (isalnum(ch))
            result += ch;
        else if (ch == ')')
            st.push(ch);
        else if (ch == '(')
        {
            while (
                !st.empty() && st.top() != ')')
            {
                result += st.top();
                st.pop();
            }

            if (!st.empty())
                st.pop();
        }
        else if (isOperator(ch))
        {
            while (
                !st.empty() && isOperator(st.top()) && ((precedence(st.top()) > precedence(ch)) || (precedence(st.top()) == precedence(ch) && isRightAssociative(ch))))
            {
                result += st.top();
                st.pop();
            }

            st.push(ch);
        }
    }

    while (!st.empty())
    {
        result += st.top();
        st.pop();
    }

    reverse(result.begin(), result.end());
    return result;
}

int main(int argc, char const *argv[])
{
    string s = "a+(b-c)*(d^e)/f";
    cout << infixToPrefix(s) << endl;

    return 0;
}
