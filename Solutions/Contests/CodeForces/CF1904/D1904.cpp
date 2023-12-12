#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
struct Tree {
    static constexpr T base = 0;
    T f(T a, T b) {
        return a + b; //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    Tree(int n = 0, T def = base) : s(n*2,def), n(n) {}
    void build() {
        for(int i = n - 1; i > 0; i--) s[i] = f(s[i*2],s[i*2+1]);
    }
    void update(int pos, T val) {
        for(s[pos += n] = val; pos /= 2;) s[pos] = f(s[pos*2],s[pos*2+1]);
    }
    T query(int l, int r) { //[l,r)
        T ans = base;
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) ans = f(ans, s[l++]);
            if(r & 1) ans = f(s[--r],ans);
        }
        return ans;
    }
};

void solve() {
    int n; cin >> n;
    
    vector<array<int,3>> order;
    Tree<int> locked(n,1); 
    vector<set<int>> indexes(n);

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        num--;
        order.push_back({num,0,i}); //value, a or b ,index
        indexes[num].insert(i);
    }

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        num--;
        order.push_back({num,1,i});
    }
    sort(order.begin(), order.end());
    bool ok = 1;
    int prev = -1;
    vector<int> tolock;
    for(int i = 0; i < order.size(); i++) {
        if(prev != order[i][0]) {
            while(tolock.size()) {
                locked.update(tolock.back(),1);
                tolock.pop_back();
            }
        }
        if(order[i][1] == 0) { //on a, just unlocking
            locked.update(order[i][2],0);
        } else {
            bool found = 0;
            int num = order[i][0];
            if(indexes[num].lower_bound(order[i][2]) != indexes[num].end()) {
                if(locked.query(order[i][2], (*indexes[num].lower_bound(order[i][2])) + 1) == 0) {
                    found = 1;
                }
            }
            if(indexes[num].lower_bound(order[i][2]) != indexes[num].begin()) {
                if(locked.query(*--indexes[num].lower_bound(order[i][2]), order[i][2] + 1) == 0) {
                    found = 1;
                }
            }
            if(!found) {
                // cout << "not possible : " << order[i][0] << " " << order[i][1] << " " << order[i][2] << '\n';
                ok = 0;
                break;
            }
            // locked.update(order[i][2],1);
            tolock.push_back(order[i][2]);
        }
        prev = order[i][0];
    }
    cout << (ok ? "YES" : "NO") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}