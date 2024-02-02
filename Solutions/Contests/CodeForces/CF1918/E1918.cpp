#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

bool ok = 1;
int n,q;

void genvals(vector<int > &v, int l, int r) {
    if(r - l < 0) return;
    int m = l + (r - l) / 2;
    v.push_back(m);
    genvals(v,l,m-1);
    genvals(v,m+1,r);
}

//finds target value, then does queries on all elements that have unknowns that could be fixed
void findval(vector<pair<int,int>> &bounds, int &x, int target, int minidx, int maxidx) {
    if(target == 1 || target == bounds.size()) return; //already computed
    //calibrate x to target.
    while(x != target) {
        if(x > target) {
            cout << "? " << minidx + 1 << endl; q++;
            string s; cin >> s;
            if(s == "-1" || q > n * 40) {
                ok = 0;
                return;
            }
            x--;
        }
        if(x < target) {
            cout << "? " << maxidx + 1 << endl; q++;
            string s; cin >> s;
            if(s == "-1" || q > n * 40) {
                ok = 0;
                return;
            }
            x++;
        }
    }
    int n = bounds.size();

    for(int i = 0; i < n; i++) {
        if(bounds[i].first <= x && bounds[i].second >= x) {
            cout << "? " << i + 1 << endl; q++;
            string s; cin >> s;
            if(s == "-1" || q > n * 40) {
                ok = 0;
                return;
            }
            if(s == ">") {
                bounds[i].first = x + 1;
                cout << "? " << minidx + 1 << endl; q++;
                string s; cin >> s;
                if(s == "-1" || q > n * 40) {
                    ok = 0;
                    return;
                }
            } else if(s == "<") {
                bounds[i].second = x - 1;
                cout << "? " << maxidx + 1 << endl; q++;
                string s; cin >> s;
                if(s == "-1" || q > n * 40) {
                    ok = 0;
                    return;
                }
            } else if(s == "=") {
                bounds[i] = {x,x};
            }
        }
    }
}

void setmin(vector<pair<int,int>> &bounds, int n, int &minidx) {
    minidx = 0;
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            string s = "\0"; 
            while(s != "=") {
                cout << "? " << i + 1 << endl; q++;
                cin >> s;
                if(s == "-1" || q > n * 40) {
                    ok = 0;
                    return;
                }
            }
        } else {
            string s = "\0";
            cout << "? " << i + 1 << endl; q++;
            cin >> s;
            if(s == "-1" || q > n * 40) {
                ok = 0;
                return;
            }
            if(s == "<") {
                minidx = i;
                while(s != "=") {
                    cout << "? " << i + 1 << endl; q++;
                    cin >> s;
                    if(s == "-1" || q > n * 40) {
                        ok = 0;
                        return;
                    }
                }
            } else {
                cout << "? " << minidx + 1 << endl; q++;
                cin >> s;
                if(s == "-1" || q > n * 40) {
                    ok = 0;
                    return;
                }
            }
        }
    }
    //maxidx points to highest number in pertmuation, and x is currently set to n
    bounds[minidx] = {1,1};
}

void setmax(vector<pair<int,int>> &bounds, int n, int &maxidx) {
    maxidx = 0;
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            string s = "\0"; 
            while(s != "=") {
                cout << "? " << i + 1 << endl; q++;
                cin >> s;
                if(s == "-1" || q > n * 40) {
                    ok = 0;
                    return;
                }
            }
        } else {
            string s = "\0";
            cout << "? " << i + 1 << endl; q++;
            cin >> s;
            if(s == "-1" || q > n * 40) {
                ok = 0;
                return;
            }
            if(s == ">") {
                maxidx = i;
                while(s != "=") {
                    cout << "? " << i + 1 << endl; q++;
                    cin >> s;
                    if(s == "-1" || q > n * 40) {
                        ok = 0;
                        return;
                    }
                }
            } else {
                cout << "? " << maxidx + 1 << endl; q++;
                cin >> s;
                if(s == "-1" || q > n * 40) {
                    ok = 0;
                    return;
                }
            }
        }
    }
    //minidx points to highest number in pertmuation, and x is currently set to n
    bounds[maxidx] = {n,n};
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}
void solve() {
    cin >> n;
    q = 0;
    if(n == -1) {
        ok = 0;
        return;
    }
    vector<pair<int,int>> bounds(n,{1,n});
    int maxidx = -1;
    int minidx = -1;
    if(ok) {
        setmin(bounds, n, minidx);
    }
    if(ok) {
        setmax(bounds, n, maxidx);
    }
    int x = n;
    // cout << "minidx : " << minidx << " maxidx : " << maxidx << " x : " << x << '\n';
    vector<int> findvals;
    genvals(findvals,1,n);
    // cout << "findvals : " << findvals << '\n';
    for(int val : findvals) {
        if(ok) {
            findval(bounds, x, val, minidx, maxidx);
        }
    }
    if(ok) {
        cout << "!";
        for(auto b : bounds) {
            cout << " " << b.first;
        }
        cout << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0 && ok) solve();

    return 0;
}