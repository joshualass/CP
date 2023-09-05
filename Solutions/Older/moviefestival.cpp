#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct sort_second {
    bool operator()(const pair<int,int> &left, const pair<int,int> &right) {
        if(left.second == right.second) {
            return left.first < right.first;
        } else {
            return left.second < right.second;
        }
    }
};

void printV(const vector<pair<int,int>> &x) {
    cout << " --- vector --- \n";
    for(auto y : x) {
        cout << y.first <<" " << y.second << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<int,int>> v(n);
    for(auto &x: v) {
        cin >> x.first; 
        cin >> x.second;
    }
    sort(v.begin(), v.end(), sort_second());
    int latest = -1;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(v[i].first >= latest) {
            cnt++;
            latest = v[i].second;
        }
    }
    cout << cnt << "\n";
    return 0;
}