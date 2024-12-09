#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
set<int> counterfeit = {1,5,12,13,23,24,33,34,43,44};

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int ask(int a, int b) {
    assert(a + 1 >= 1 && a + 1 <= 1000 && b + 1 >= 1 && b + 1 <= 1000);
    assert(a != b);
    cout << "? " << a + 1 << " " << b + 1 << endl;
    int res; cin >> res;
    // int res = counterfeit.count(a+1) != counterfeit.count(b+1);
    // cout << res << endl;
    if(res == -1) {
        exit(1);
    }
    return !res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q; cin >> n >> m >> q;
    vector<array<int,10>> queries(90);
    int good = -1;


    // for(int i = 0; i < 1000; i += 11) {
    for(int i = 0; i < 90; i++) {
        int ok = 1;
        for(int j = 0; j < 10; j++) {
            queries[i][j] = ask(i*11,i*11+j+1);
            if(queries[i][j] == 0) {
                ok = 0;
            }
        }
        if(ok) {
            good = i*11;
        }
    }

    vector<int> bad;
    for(int i = 0; i < 90; i++) {
        array<int,10> a = queries[i];
        int hasbad = 0;
        for(int x : a) {
            if(x == 0) {
                hasbad = 1;
            }
        }
        if(hasbad) {
            int logood = ask(good, i * 11);
            if(!logood) {
                bad.push_back(i*11);
            }
            for(int j = 0; j < 10; j++) {
                if((logood ^ a[j]) == 1) {
                    bad.push_back(i*11+j+1);
                }
            }
        }
    }

    for(int i = 990; i < 1000; i++) {
        if(ask(good,i) == 0) {
            bad.push_back(i);
        }
    }

    // cout << "bad : " << bad << '\n';

    assert(bad.size() == 10);
    cout << "! ";
    for(int i = 0; i < bad.size(); i++) {
        cout << bad[i] + 1;
        if(i == bad.size() - 1) {
            cout << endl;
        } else {
            cout << " ";
        }
    }

    return 0;
}