#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;

    vector<int> a(n);
    for(int& x : a) cin >> x; //dhruv cool way of reading into a vector
    int count = 0;

    for(int i = 0; i < pow(2, n); i++) {
        int sum = 0;
        for(int t = 0;t < n; t++) {
            if(i & 1 << t) {
                sum = (sum + 360 + a[t]) % 360;
            } else {
                sum = (sum + 360 - a[t]) %360;
            }
        }
        if(sum == 0) {
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    
    // vector<int> v(1,0);

    // int n;
    // cin >> n;
    // while(n-->0) {
    //     int num;
    //     cin >> num;
    //     int size = v.size(); 
    //     for(int i = 0; i < size; i++) {
    //         int value = v[i];
    //         v[i] = (360 + value - num) % 360;
    //         v.push_back((360 + value + num) % 360);
    //     }
    // }
    // sort(v.begin(), v.end());
    // cout << (v[0] == 0 ? "YES" : "NO");

    return 0;
}