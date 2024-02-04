#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x; cin >> n >> x;
    vector<pair<int,int>> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i + 1;
    }   
    sort(v.begin(), v.end());
    int low = 0;
    int high = n - 1;
    bool flag = false;
    while(low != n && high != -1) {
        int sum = v[low].first + v[high].first;
        if(sum == x) {
            if(low == high) {
                break;
            }
            flag = true;
            break;
        } else if(sum > x) {
            high--;
        } else {
            low++;
        }
    }
    if(flag) {
        cout << v[low].second << " " << v[high].second << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}
