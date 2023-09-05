#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n, w, L; cin >> n >> w >> L;
        vector<int> v(w);
        for(int i = 0; i < w; i++) {
            int num; cin >> num;
            v[i] = num;
        }
        int l = 1;
        int r = 1000000000;
        while(l < r) {
            int m = (l + r + 1) / 2;
            int index = 0;
            int trains = 0;
            for(int i = 1; i <= n;) {
                if(index == w) {
                    trains++;
                    break;
                }
                if(v[index] - i - 1> m) {
                    i = v[index] + 1;
                } else {
                    i += m;
                    while(index != w && i > v[index]) {
                        index++;
                    }
                }
                trains++;
            }
            // cout << l << " " << r << " " << trains << '\n';
            if(r-l == 1) {
                if(trains <= L) {
                    l = r;
                } else {
                    r = l;
                }
            } else if(trains <= L) {
                r = m;
            } else {
                l = m;
            }
        }
        cout << r << '\n';
    }

    return 0;
}