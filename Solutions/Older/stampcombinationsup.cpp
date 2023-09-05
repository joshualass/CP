#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n; cin >> m >> n;
    unordered_set<int> us;
    us.insert(0);
    vector<int> v(m + 1);
    int total = 0;
    for(int i = 1; i <= m; i++) {
        cin >> v[i];
        total += v[i];
    }
    v.push_back(0);
    int sum =0;
    for(int i = v.size()-1; i >= 0; i--) {
        sum += v[i];
        us.insert(sum);
    }
    for(int i = 0; i < n; i++) {
        sum = 0;
        int num; cin >> num;
        if(num > total) {
            cout << "No\n";
            continue;
        }
        bool flag = false;
        for(int t = 0; t <= m; t++) {
            sum += v[t];
            if(us.find(num - sum) != us.end()) {
                flag = true;
                break;
            }
        }
        if(us.find(num) != us.end()) {
            flag = true;
        }
        cout << (flag ? "Yes" : "No") << "\n";
    }

    return 0;
}