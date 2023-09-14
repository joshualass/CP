#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<pair<int,int>> v(n);
    int most = 0;
    int total = 0;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v[i] = {num,i};
        total += num;
        most = max(most,num);
    }
    if(most * 2 > total) {
        cout << "impossible" << "\n";
        return 0;
    }
    sort(v.begin(),v.end());
    for(int i = n - 1; i >= 0; i--) {
        cout << v[i].second +
         1 << " ";
    }
    return 0;
}