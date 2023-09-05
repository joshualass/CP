#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ld x_value(ld a, ld c) {
    return sqrt(c/a);
}

ld k_value(ld a, ld b, ld x) {
    return 2 * a * x + b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n, m; cin >> n >> m;
        set<ld> slopes;
        for(int i = 0; i < n; i++) {
            int num; cin >> num;
            slopes.insert(num);
        }
        for(int i = 0; i < m; i++) {
            ld a, b, c; cin >> a >> b >> c;
            if(c <= 0) {
                cout << "NO\n";
                continue;
            }
            ld upper_x = x_value(a,c);
            ld lower_x = x_value(a,c) * -1;
            ld upper_k = k_value(a,b,upper_x);
            ld lower_k = k_value(a,b,lower_x);
            bool has_element = slopes.upper_bound(lower_k) != slopes.lower_bound(upper_k);
            if(has_element) {
                cout << "YES\n" << ((int)(*(slopes.upper_bound(lower_k)))) << "\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}