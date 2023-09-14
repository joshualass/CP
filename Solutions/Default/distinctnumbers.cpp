#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> v(n);
    for(int &x: v) cin >> x;
    sort(v.begin(),v.end());
    int counter = 0;
    int prev = -1;
    for(int i = 0; i < n ;i++) {
        if(v[i] != prev) {
            counter++;
        }
        prev = v[i];
    }
    cout << counter << "\n";
    return 0;
}