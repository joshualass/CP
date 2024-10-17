#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string firstline;
    getline(cin, firstline);

    stringstream ss(firstline);
    string firsttext; ss >> firsttext;
    char firstchar; ss >> firstchar;

    int score = 0;
    for(int i = 0; i < firsttext.size(); i++) {
        score += firsttext[i] - 32;
        // cout << (int) firsttext[i] << '\n';  
    }

    int shift = (52 + (score - 1) - (firstchar - 'a')) % 26;
    // cout << "score : " << score << '\n';
    // cout << "shift : " << shift << '\n';

    while(getline(cin,firstline)) {
        stringstream ss2(firstline);
        while(!ss2.eof()) {
            string s; ss2 >> s;
            if(s == "0") {
                cout << ' ';
            } else if(s == "<") {
                cout << ',';
            } else if(s == ">") {
                cout << ".";
            } else {
                int score = 0;
                for(char c : s) {
                    score += c - 32;
                }
                cout << (char) (((char) + 'a' + (score - 1 - shift + 26) % 26));
            }
        }
        cout << '\n';
    }

    return 0;
}