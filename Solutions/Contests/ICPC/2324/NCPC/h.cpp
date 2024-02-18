#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int calc_power(vector<string> &v, bool isCenter, map<string,int> &goon) {
    int power = 0;
    for(string x : v) {
        power += goon[x];
        if(x == "Thunderheart") {
            if(v.size() == 4) {
                power += goon[x];
            }
        }
        if(x == "Zenith" && isCenter) {
            power += 5;
        }
        if(x == "Seraphina") {
            power += v.size() - 1;
        }
    }
    return power;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    map<string,int> m = {
        {"Shadow", 6},
        {"Gale", 5},
        {"Ranger", 4},
        {"Anvil", 7},
        {"Vexia", 3},
        {"Guardian", 8},
        {"Thunderheart", 6},
        {"Frostwhisper", 2},
        {"Voidclaw", 3},
        {"Ironwood", 3},
        {"Zenith", 4},
        {"Seraphina", 1}
    };

    int p1tp = 0;
    int p2tp = 0;
    int p1loc = 0;
    int p2loc = 0;

    for(int i = 0; i < 3; i++) {
        int num1; cin >> num1;
        vector<string> v1(num1);
        for(auto &x : v1) cin >> x;
        int p1p = calc_power(v1,i== 1, m);
        int num2; cin >> num2;
        vector<string> v2(num2);
        for(auto &x : v2) cin >> x;
        int p2p = calc_power(v2, i == 1, m);
        p1tp += p1p;
        p2tp += p2p;
        // cout << "i : " << i << "p1p : " << p1p << " p2p : " << p2p << '\n';
        if(p1p > p2p) {
            p1loc++;
        }
        if(p2p > p1p) {
            p2loc++;
        }
    }

    if(p1loc == p2loc) {
        if(p1tp == p2tp) {
            cout << "Tie\n";
        } else if(p1tp > p2tp) {
            cout << "Player 1\n";
        } else {
            cout << "Player 2\n";
        }
    } else {
        if(p1loc > p2loc) {
            cout << "Player 1\n";
        } else {
            cout << "Player 2\n";
        }
    }

    return 0;
}