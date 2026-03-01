#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int w, h;
    // cin >> w >> h;
    // int v = h;
    // bool valid = 1;
    // for(int i = 0; i < w; i++) {
    //     int x;
    //     cin >> x;
    //     if(h - x < 0) {
    //         valid = 0;
    //         break;
    //     }
    //     if((h - x) % 2) v --;
    //     else v = min(h, v + 1);
    // }
    // if(v != h) valid = 0;
    // cout << (valid? "possible" : "impossible") << "\n";

    int w, h; cin >> w >> h;

    int ok = 1;
    vector<int> a;
    
    auto _work = [&]() -> void {
        // cout << "a : " << a << '\n';
        int prev = 0;
        int po = 0, pe = 0;
        for(int i = 0; i < a.size(); i++) {
            int x = h - a[i];
            int ne = x / 2, no = x/ 2;
            if(x & 1) {
                if(i % 2 == 0) {
                    no++;
                } else {
                    ne++;
                } 
            }
            // cout << "i : " << i << " po : " << po << " pe : " << pe << " ne : " << ne << " no : " << no << '\n';
            if(ne < po) ok = 0;
            ne -= po;
            if(no < pe) ok = 0;
            no -= pe;
            int sub = min(ne, no);
            po = no - sub;
            pe = ne - sub;
        }
        // cout << "po : " << po << " pe : " << pe << '\n';
        if(po || pe) ok = 0;
    };

    for(int i = 0; i < w; i++) {
        int x; cin >> x;
        if(x == h) {
            _work();
            a.clear();
        }
        a.push_back(x);
    }

    _work();

    cout << (ok ? "possible" : "impossible") << '\n';

    return 0;
}
