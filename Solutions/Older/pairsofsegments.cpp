#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printV(const vector<pair<int,int>> &x) {
    cout << " --- vector --- \n";
    for(pair<int,int> y : x) {
        cout << y.first << " " << y.second;
    }
    cout << "\n";
}

struct sort_second {
    bool operator()(const pair<int,int> &left, const pair<int,int> &right) {
        if(left.second == right.second) {
            return left.first < right.first;
        } else {
            return left.second < right.second;
        }
    }
};

void solve() {
    int n; cin >> n;
    vector<pair<int,int>> v(n);
    for(auto &x: v) {
        cin >> x.first;
        cin >> x.second;
    }

    vector<pair<int,int>> longersegments;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            //check if segments intersect
            if(max(v[i].first,v[j].first) <= min(v[i].second,v[j].second)) {
                longersegments.push_back({min(v[i].first,v[j].first),max(v[i].second,v[j].second)});
            }
        }
    }
    // sort(v.begin(), v.end(), sort_second());
    sort(longersegments.begin(),longersegments.end(), sort_second());
    
    int cnt = 0;
    int prev = -1;
    for(pair<int,int> x : longersegments) {
        if(x.first > prev) {
            cnt++;
            prev = x.second;
        }
    }
    cout << n - cnt * 2 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}