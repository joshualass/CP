/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

// #include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    // cout<<"Hello World";
    string str; cin >> str;
    char prev = '0';
    int cnt = 0;
    int curr = 0;
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == prev) {
            curr++;
        } else {
            prev = str[i];
            curr = 1;    
        }
        cnt = max(curr, cnt);
    }
    cout << cnt << "\n";
    return 0;
}
