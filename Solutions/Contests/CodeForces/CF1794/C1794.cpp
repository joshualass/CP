#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        vector<int> v(n);
        for(int &x: v) cin >> x;

        int pivot = 0;

        for(int i = 0; i < n; i++) {
            while(v[pivot] < i + 1 - pivot) {
                pivot++;
            }
            cout << (i + 1) - pivot << ' ';
        }
        cout << '\n';
    }

    return 0;
}