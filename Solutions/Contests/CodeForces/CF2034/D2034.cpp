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

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int zc = count(a.begin(),a.end(),0), oc = count(a.begin(),a.end(), 1), tc = count(a.begin(),a.end(),2);

    set<int> underzero, underone, overone, overtwo, ones, iwanttwo, iwantzero;
    auto addstatus = [&](int i) {
        int req = 0;
        if(i >= zc) req++;
        if(i >= zc + oc) req++;
        ones.erase(i);
        underzero.erase(i);
        underone.erase(i);
        overone.erase(i);
        overtwo.erase(i);
        iwanttwo.erase(i);
        iwantzero.erase(i);
        // cout << "i : " << i << " req : " << req << '\n';
        if(a[i] == 0 && req == 1) {
            underzero.insert(i);
        }
        if(a[i] == 1 && req == 2) {
            underone.insert(i);
        }
        if(a[i] == 2 && req == 1) {
            overtwo.insert(i);
        }
        if(a[i] == 1 && req == 0) {
            overone.insert(i);
        }
        if(a[i] == 1) ones.insert(i);
        if(req == 2 && a[i] == 0) {
            iwanttwo.insert(i);
        }
        if(req == 0 && a[i] == 2) {
            iwantzero.insert(i);
        }
    };
    for(int i = 0; i < n; i++) {
        addstatus(i);
    }
    // cout << "uz : " << underzero << '\n';
    // cout << "uo : " << underone << '\n';
    // cout << "oo : " << overone << '\n';
    // cout << "ot : " << overtwo << '\n';
    // cout << "ones : " << ones << '\n';
    // cout << "iwt : " << iwanttwo << '\n';
    // cout << "iwz : " << iwantzero << '\n';
    vector<array<int,2>> ops;
    // cout << "a : " << a << '\n';

    while(1) {
        // cout << "a : " << a << endl;
        if((underzero.size() || iwanttwo.size()) && overone.size()) {
            int x = -1, y = *overone.begin();
            if(iwanttwo.size()) {
                x = *iwanttwo.begin();
            } else {
                x = *underzero.begin();
            }
            // cout << "x1 : " << x << " y1 : " << y << endl;
            swap(a[x],a[y]);
            addstatus(x);
            addstatus(y);
            ops.push_back({x,y});
            continue;
        }

        if((overtwo.size() || iwantzero.size()) && underone.size()) {
            int x = -1, y = *underone.begin();
            if(iwantzero.size()) {
                x = *iwantzero.begin();
            } else {
                x = *overtwo.begin();
            }
            // cout << "x2 : " << x << " y2 : " << y << endl;
            swap(a[x],a[y]);
            addstatus(x);
            addstatus(y);
            ops.push_back({x,y});
            continue;
        }

        if((overtwo.size() || iwantzero.size()) && (underzero.size() || iwanttwo.size())) {
            int x = *ones.begin();
            int y = -1;
            if(iwantzero.size()) {
                y = *iwantzero.begin();
            } else if(iwanttwo.size()) {
                y = *iwanttwo.begin();
            } else {
                y = *underzero.begin();
            }
            // cout << "x3 : " << x << " y3 : " << y << endl;
            swap(a[x],a[y]);
            addstatus(x);
            addstatus(y);
            ops.push_back({x,y});
            continue;
        }
        // if(!f) break;
        break;
    }

    cout << ops.size() << '\n';
    for(auto op : ops) {
        cout << op[0] + 1 << " " << op[1] + 1 << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}