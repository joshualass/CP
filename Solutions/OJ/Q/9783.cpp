#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n, 0);
    a[0] = 1;

    //bm vector
    auto ask = [&](vector<int> o) -> int {
        cout << "? ";
        for(int x : o) cout << x;
        cout << endl;
        int res; cin >> res;
        return res;
    };

    //vector that includes the elements. 
    auto ask1 = [&](vector<int> b) -> int {
        vector<int> o(n);
        for(int x : b) o[x] = 1;
        return ask(o);
    };

    auto get_both = [&](vector<int> b, vector<int> c) -> vector<int> {
        for(int x : c) b[x] = 1;
        return b;
    };

    for(int i = 1; i < n; i++) {

        vector<int> out;
        for(int j = 0; j < n; j++) {
            if(a[j] == 0) out.push_back(j);
        }

        int s = ask(a);

        while(out.size() > 1) {
            int m = out.size() / 2;
            vector<int> t(out.begin(), out.begin() + m);
            int g = ask1(t);
            int gp = ask(get_both(a, t));
            if(s + g == gp) { //no match with this group
                out = vector<int>(out.begin() + m, out.end());
            } else {
                out = vector<int>(out.begin(), out.begin() + m);
            }
        }

        int g = ask1(out);
        int gp = ask(get_both(a, out));
        if(s + g == gp) {
            cout << "! 0" << endl;
            return 0;
        }

        a[out[0]] = 1;

    }

    cout << "! 1" << endl;


    return 0;
}
