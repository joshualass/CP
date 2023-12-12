#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    map<int,int> a;
    map<int,int> b;

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a[num]++;
    }

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        b[num]++;
    }

    set<int> intersection;

    for(auto x : a) {
        set<int> temp;
        for(auto y : b) {
            if(x.second == y.second) {
                temp.insert(x.first ^ y.first);
            }
        }
        if(x.first == (*a.begin()).first) {
            intersection = temp;
        } else {
            // set_intersection(intersection.begin(), intersection.end(), temp.begin(), temp.end(), intersection.begin());
            set<int> upd;
            for(auto x : intersection) {
                if(temp.find(x) != temp.end()) {
                    upd.insert(x);
                }
            }
            swap(intersection, upd);
        }
    }

    cout << intersection.size() << '\n';
    for(auto x : intersection) {
        cout << x << '\n';
    }

    return 0;
}

/*
00000110011010001111110110111011
00000111101101100001111111001001
00001000010011000001101001010001
00001001100100101111100000100011
00010010100111011101101000111111
00010011010000110011100001001101
00011100101110010011110111010101
00011101011001111101111110100111
*/