#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x; cin >> n >> x;
    vector<int> v(n);
    for(int &x: v) cin >> x;
    sort(v.begin(),v.end());
    int left = 0;
    int right = n - 1;
    int cnt = 0;
    while(right >= left) {
        cnt++;
        if(v[left] + v[right] <= x) {
            left++;
            right--;
        } else {
            right--;
        }
    }
    cout << cnt << "\n";
    return 0;
}
