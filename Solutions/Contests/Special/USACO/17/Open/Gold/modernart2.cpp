#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//ezpz gold problem
//solved in linear using cool stack
//we only care about the first and last occurence of each element, and we maintiain the stack be monotonic and everything works bc i'm ok at this

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // freopen("art2.in","r",stdin);
    // freopen("art2.out","w",stdout);
    
    int n; cin >> n;
    vector<pair<int,int>> ranges(n,{INT_MAX,INT_MIN});
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v[i] = num;
        if(num != 0) {
            ranges[num-1].first = min(ranges[num-1].first, i);
            ranges[num-1].second = max(ranges[num-1].second, i);
        }
    }

    stack<int> ends;
    bool ok = 1;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        //only significant if it's the first or last occurance of the color
        if(v[i] == 0) {
            if(ends.size()) { //can't have an interval over a 0
                ok = 0;
                break;
            }
        } else {
            if(ranges[v[i]-1].first == i) {
                int end = ranges[v[i]-1].second;
                if(ends.size() && end > ends.top()) {
                    ok = 0;
                    break;
                }
                ends.push(end);
            }
            ans = max(ans, (int)ends.size());
            if(ranges[v[i]-1].second == i) {
                ends.pop();
            }
        }
    }
    cout << (ok ? ans : -1) << '\n';
    return 0;
}