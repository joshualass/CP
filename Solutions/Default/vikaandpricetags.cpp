#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    for(int &x: a) cin >> x;
    for(int &x: b) cin >> x;

    vector<int> c(n);

    for(int i = 0; i < n; i++) {
        int A = a[i];
        int B = b[i];
        int cnt = 0;
        while(A != 0) {
            if(B == 0) {
                cnt++;
                break;
            }
            if(B > A) {
                cnt++;
                int temp = B - A;
                A = B;
                B = temp;
            } else if(A >= B * 2) {
                A -= A / (B * 2) * (B * 2);
            } else {
                int temp = A - B;
                A = B;
                B = temp;
                cnt++;
            }
            // cout << "looppp";
        }
        c[i] = cnt % 3;
    }
    int val = -1;
    bool flag = true;
    for(int i = 0; i < n; i++) {
        if(a[i] != 0 || b[i] != 0) {
            if(val == -1) {
                val = c[i];
            } else if(c[i] != val) {
                flag = false;
            }
        }
    }
    cout << (flag ? "YES" : "NO") << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}