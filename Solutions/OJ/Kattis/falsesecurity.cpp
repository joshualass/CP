#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

map<char,string> m = {
    {'A',".-"},
    {'B',"-..."},
    {'C',"-.-."},
    {'D',"-.."},
    {'E',"."},
    {'F', "..-."},
    {'G',"--."},
    {'H',"...."},
    {'I',".."},
    {'J',".---"},
    {'K',"-.-"},
    {'L',".-.."},
    {'M',"--"},
    {'N',"-."},
    {'O',"---"},
    {'P',".--."},
    {'Q',"--.-"},
    {'R',".-."},
    {'S',"..."},
    {'T',"-"},
    {'U',"..-"},
    {'V',"...-"},
    {'W',".--"},
    {'X',"-..-"},
    {'Y',"-.--"},
    {'Z',"--.."},
    {'_',"..--"},
    {'.',"---."},
    {',',".-.-"},
    {'?',"----"}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    while(1) {
        getline(cin,line);
        if(line.empty()) break;

        string b = "";
        vector<int> a;
        for(char c : line) {
            string s = m[c];
            b.append(s);
            a.push_back(s.size());
        }

        // cout << "a : " << a << '\n';

        reverse(a.begin(),a.end());

        int p = 0;

        for(int i = 0; i < a.size(); i++) {
            int len = a[i];
            string s = b.substr(p,len);
            for(auto [c, bm] : m) {
                if(bm == s) {
                    cout << c;
                }
            }
            p += len;
        }
        cout << '\n';
    }

    return 0;
}