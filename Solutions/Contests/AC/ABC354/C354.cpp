#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<array<int,3>> a(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i;
    }

    sort(a.begin(), a.end());

    int minx = a.back()[0];
    int miny = a.back()[1];
    vector<int> res;
    for(int i = n - 1; i >= 0; i--) {
        if(a[i][0] < minx && a[i][1] > miny) {

        } else {
            minx = min(minx,a[i][0]);
            miny = min(miny,a[i][1]);
            res.push_back(a[i][2]);
        }
    }

    sort(res.begin(), res.end());
    cout << res.size() << '\n';
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] + 1 << " \n"[i == res.size() - 1];
    }
    

    return 0;
}