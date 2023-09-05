#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int t; cin >> t;
    while(t-->0) {
 
        int n, k, d, w; cin >> n >> k >> d >> w;
        vector<int> v(n);
        int packs = 0;
        int left = 0;
        int open_time = 0;
 
        for(int i = 0; i < n; i++) {
            int num; cin >> num;
            if(left == 0 || num > open_time + d) { //check if need to open
                packs++;
                open_time = num + w;
                left = k - 1;
            } else {
                left--;
            }
        }
        cout << packs << '\n';
 
    }
 
    return 0;
}