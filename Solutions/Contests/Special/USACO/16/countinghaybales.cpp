#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("haybales.in","r",stdin);
    freopen("haybales.out","w",stdout);

    int n, q; cin >> n >> q;
    
    vector<int> v(n);

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v[i] = num;
    }

    // for(int &x : v) {
    //     cin >> x;
    // }

    //2, 3, 5, 7

    sort(v.begin(), v.end());

    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;

        int left = -1, right = n - 1;
        
        while(left != right) {
            int midpoint = (left + right + 1) / 2; //finds midpoint in our range (left, right)

            //comparison check
            if(v[midpoint] < a) {
                left = midpoint;
            } else {
                right = midpoint - 1;
            }

        }

        //Now, left = right store the highest index in our list such that v[index] < a.

        int left2 = -1;
        int right2 = n - 1;

        while(left2 != right2) {
            int midpoint2 = (left2 + right2 + 1) / 2;

            //check condition
            if(v[midpoint2] <= b) {
                left2 = midpoint2;
            } else {
                right2 = midpoint2 - 1;
            }
        }


        //print differences between are binary searched indices. 

        cout << left2 - left << '\n';

    }

    return 0;
}