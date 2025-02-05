#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    set<int> p_unused, i_unvis;

    for(int i = 0; i < n; i++) {
        p_unused.insert(i);
        i_unvis.insert(i);
    }
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(x != -1) x--;
        a[i] = x;
        if(x != -1) {
            p_unused.erase(x);
            i_unvis.erase(i);
        }
    }
    int i = 0;

    auto ok = [&](int idx) -> bool {
        if(idx > 0 && a[idx-1] != -1 && abs(a[idx] - a[idx-1]) == 1) return 0;
        if(idx < n - 1 && a[idx+1] != -1 && abs(a[idx] - a[idx+1]) == 1) return 0;
        return 1;
    };

    while(p_unused.size() > 6) {
        if(a[i] == -1) {
            int f = -1;
            for(int x : p_unused) {
                a[i] = x;
                if(ok(i)) {
                    f = x;
                    break;
                }
            }
            i_unvis.erase(i);
            a[i] = f;
            p_unused.erase(f);
        }
        i++;
    }

    vector<int> p(p_unused.size());
    iota(p.begin(),p.end(),0);
    vector<int> pu(p_unused.begin(),p_unused.end());
    vector<int> iu(i_unvis.begin(),i_unvis.end());
    int good = 0;

    // cout << "a : " << a << '\n';
    // cout << "pu : " << pu << '\n';
    // cout << "iu : " << iu << '\n';

    while(1) {
        for(int i = 0; i < p.size(); i++) {
            // a[iu[p[i]]] = pu[i];
            a[iu[i]] = pu[p[i]];
        }
        int f = 1;
        for(int i = 0; i < p.size(); i++) {
            if(!ok(iu[i])) f = 0;
        }
        if(f) {
            good = 1;
            break;
        }

        if(!next_permutation(p.begin(), p.end())) break;
    }

    if(good) {
        for(int i = 0; i < n; i++) {
            cout << a[i] + 1 << " \n"[i == n - 1];
        }
    } else {
        cout << "-1\n";
    }

    return 0;
}