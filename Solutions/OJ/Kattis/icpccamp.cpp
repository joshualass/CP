#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int n, p, q, s;
vector<ll> x, y;

//returns lowest index such that a[i] >= val
int lbound(vector<ll>& a, ll val) {
    int low = 0, high = a.size() - 1, ans = a.size();
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(a[mid] >= val) ans = mid, high = mid - 1;
        else low = mid + 1;
    }
    return ans;
}

bool is_valid(ll val) {
    // cout << "SOLVE : " << val << "\n";
    //make segment
    vector<pair<int, int>> seg; //interval in y
    for(int i = 0; i < p; i++){
        ll lval = x[i] - val, rval = x[i] + val;
        if(lval > s - x[i]) continue;
        lval = min(lval, s - x[i]);
        rval = min(rval, s - x[i]);
        int lind = lbound(y, lval), rind = lbound(y, rval + 1);
        seg.push_back({lind, rind});
        // cout << "SEG : " << lval << " " << rval << " " << lind << " " << rind << "\n";
    }
    //sort segment, make set
    sort(seg.begin(), seg.end(), [](pair<int, int>& a, pair<int, int>& b) -> bool {
        return a.second == b.second? a.first < b.first : a.second < b.second;
    });
    set<int> st;
    for(int i = 0; i < q; i++) st.insert(i);
    //do greedy matching
    int cnt = 0;
    for(int i = 0; i < seg.size(); i++){
        int l = seg[i].first, r = seg[i].second;
        auto ptr = st.lower_bound(l);
        if(ptr != st.end() && *ptr < r) {
            // cout << "MATCH : " << *ptr << " " << l << " " << r << "\n";
            cnt ++;
            st.erase(ptr);
        }
    }
    return cnt >= n;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> p >> q >> s;
    x = vector<ll>(p), y = vector<ll>(q);
    for(int i = 0; i < p; i++) cin >> x[i];
    for(int i = 0; i < q; i++) cin >> y[i];
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    ll low = 0, high = 1e10, ans = high;
    while(low <= high) {
        ll mid = low + (high - low) / 2;
        if(is_valid(mid)) ans = mid, high = mid - 1;
        else low = mid + 1;
    }
    cout << (ans == 1e10? -1 : ans) << "\n";

    return 0;
}
