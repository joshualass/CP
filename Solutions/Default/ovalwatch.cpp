#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    for(int i = 0; i < n ;i++) {
        v[i] = i;
    }

    vector<pair<int,int>> p(k);
    for(int i = 0; i < k; i++) {
        int f, s;
        cin >> f >> s;
        p[i] = make_pair(-s,f);
    }
    sort(p.begin(), p.end());

    for(int i = 0; i < k; i++) {
        int temp = v[p[i].second];
        v[p[i].second] = v[p[i].second + 1];
        v[p[i].second + 1] = temp;
    }
    for(int x : v) {
        cout << x << ' ';
    }
    cout << '\n';
    return 0;
}