#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> v(n);

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v[i] = num;
    }

    //IMPORTANT - NEED SORTED DATA
    sort(v.begin(), v.end());

    int q; cin >> q;
    for(int i = 0; i < q; i++) {

        int query; cin >> query;

        int left = -1;
        int right = n - 1;

        //goal : find the highest index such that a[index] <= query

        while(left != right) {
            //calculate midpoint. include the + 1 because we are trying to find the highest index 
            int midpoint = (left + right + 1) / 2;
            if(v[midpoint] <= query) {
                left = midpoint;
            } else {
                right = midpoint - 1;
            }

        }

        cout << left + 1 << '\n';

    }

    return 0;
}