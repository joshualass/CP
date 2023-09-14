#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//had to read tutorial to solve this one ._.

map<char,int> m = {
    {'A',1},
    {'B',10},
    {'C', 100},
    {'D', 1000},
    {'E', 10000}
};

int calculate(string num) {
    int maxval = -1;
    int total = 0;
    for(int i = num.size() - 1; i >= 0; i--) {

        int val = m[num[i]];
        if(val < maxval) {
            total -= val;
        } else {
            total += val;
        }
        maxval = max(maxval,val);
    }
    return total;
}

void solve() {
    string num; cin >> num;
    int best = calculate(num);
    unordered_set<char> s;
    int i = 0;
    while(s.size() != 5 && i < num.size()) {
        if(s.find(num[i]) == s.end()) {
            char hold = num[i];
            for(int t = 0; t < 5; t++) {
                num[i] = ((char) 'A' + t);
                best = max(best, calculate(num));
            }
            num[i] = hold;
        }
        s.insert(num[i]);
        i++;
    }
    unordered_set<char> ss;
    i = num.size() - 1;
    while(ss.size() != 5 && i >= 0) {
        if(ss.find(num[i]) == ss.end()) {
            char hold = num[i];
            for(int t = 0; t < 5; t++) {
                num[i] = ((char) 'A' + t);
                best = max(best, calculate(num));
            }
            num[i] = hold;
        }
        ss.insert(num[i]);
        i--;
    }
    cout << best << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}