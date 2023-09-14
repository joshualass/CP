#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    while(t-->0) {
        int n, m; cin >> n >> m;
        vector<int> v(n);
        map<int, vector<int>> nums;
        for(int i = 0; i < n; i++) {
            int num; cin >> num;
            v[i] = num;
            vector<int> temp(1,-1);
            nums.insert({num, temp});
        }
        for(int i = 0; i < m; i++) {
            int num, index; cin >> index >> num;
            index--;
            if(nums.find(num) == nums.end()) {
                vector<int> temp(0);
                nums.insert({num, temp});
            }
            nums[num].push_back(i);
            nums[v[index]].push_back(i - 1);
            v[index] = num;
        }
        ll sum = 0;

        for(pair<int, vector<int>> p : nums) {
            int num = p.first;
            vector<int> v = p.second;
            if(v.size() % 2 == 1) {
                v.push_back(n - 1);
            }
            cout << "num: " << num << '\n';
            for(int x : v) {
                cout << x << ' ';
            }
            cout << '\n';

        }
        cout << '\n';
    }

    return 0;
}