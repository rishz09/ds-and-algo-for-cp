#include<string>
#include<stdio.h>
#include<iostream>
#include<stack>
#include<algorithm>

using namespace std;

int precedence(char c)
{
    if(c == '+' || c == '-')
    return 1;

    if(c == '*' || c == '/')
    return 2;

    if(c == '^')
    return 3;

    return -1;
}

string infixToPrefix(string s)
{
    reverse(s.begin(), s.end());

    int l = s.length();

    for(int i=0; i<l; i++)
    {
        if(s[i] == ')')
        s[i] = '(';

        if(s[i] == '(')
        s[i] = ')';
    }

    stack<char> st;
    string ans = "";

    for(int i=0; i<l; i++)
    {
        if(isalpha(s[i]) || isdigit(s[i]))
        ans += s[i];

        else if(s[i] == '(')
        st.push(s[i]);

        else if(s[i] == ')')
        {
            while((st.size() != 0) && (st.top() != '('))
            {
                ans += st.top();
                st.pop();
            }
        }

        else
        {
            if(s[i] == '^')
            {
                while((st.size() != 0) && (precedence(s[i]) <= precedence(st.top())))
                {
                    ans += st.top();
                    st.pop();
                }
            }

            else
            {
                while((st.size() != 0) && (precedence(s[i]) < precedence(st.top())))
                {
                    ans += st.top();
                    st.pop();
                }
            }

            st.push(s[i]);
        }
    }

    while(st.size() != 0)
    {
        ans += st.top();
        st.pop();
    }

    reverse(ans.begin(), ans.end());

    return ans;
}

int main()
{
    string s;
    cin >> s;

    cout << infixToPrefix(s) << endl;
}