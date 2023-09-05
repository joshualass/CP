#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    while(n != 0) {
        int L = 1;
        int H = INT_MAX;
        vector<int> divs(0);
        for(int i = 0; i < n; i++) {
            string first, second; cin >> first >> second;
            int num; cin >> num;
            if(first == "less") {
                H = min(num -1,H);
            } else if(first == "divisible") {
                if(num != 1) {
                    divs.push_back(num);
                }
            } else if(first == "greater") {
                L = max(num + 1,L);
            }
        }
        // if(divs.size()) {
        //     int gg = divs[0];
        //     for(int i = 1; i < divs.size(); i++) {
        //         gg = gcd(gg,divs[i]);
        //     }
        //     if(gg == 1) {
        //     cout << "none\n";
        //     cin >> n;
        //     continue;
        // }
        // }

        if(H == INT_MAX) {
            cout << "infinite\n";
            cin >> n;
            continue;
        }
        sort(divs.begin(),divs.end());
        string out = "";
        for(int i = L; i <= H; i++) {
            bool poss = true;
            for(int x : divs) {
                if(i % x != 0) {
                    poss = false;
                    break;
                }
            }
            if(poss) {
                out += to_string(i) + " ";
            }
        }
        if(out == "") {
            cout << "none\n";
        } else {
            cout << out << "\n";
        }

        cin >> n;
    }

    return 0;
}