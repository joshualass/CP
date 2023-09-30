#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template <typename T>
void printV(const vector<T> &x) {
    cout << "v: ";
    for(auto &y : x) {
        cout << y << " ";
    }
    cout << "\n";
}

void solve() {
    int k, n; cin >> k >> n;
    string str; cin >> str;
    vector<pair<int,int>> ranges(n);
    vector<int> reverse(k);
    for(auto &x : ranges) cin >> x.first;
    for(auto &x: ranges) cin >> x.second;
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int x; cin >> x;
        int l = 0;
        int r = n - 1;
        while(l < r) {
            int m = (l + r)/2;
            if(x < ranges[m].first) {
                r = m - 1;
            } else if(x > ranges[m].second) {
                l = m + 1;
            } else {
                l = r = m;
            }
        }
        reverse[min(x, ranges[l].first + ranges[l].second - x) - 1] ^= 1;
    }
    // printV(reverse);
    int range = 0;
    bool yes = false;
    for(int i = 0; i < k; i++) {
        if(ranges[range].second < i + 1) {
            range++;
            yes = false;
        }
        // cout << "i: " << i << " range: " << range << "\n";
        yes ^= reverse[i];
        if(yes && i < (ranges[range].first + ranges[range].second) / 2) {
            // cout << "swap: " << i << " " << ranges[range].second - 1 - (i - ranges[range].first + 1) << "\n";
            swap(str[i],str[ranges[range].second - 1 - (i - ranges[range].first + 1)]);
        }
        cout << str[i];
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}