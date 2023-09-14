#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll nums[5] = {1000000007, 1000000207, 1000000409, 1000000531, 1000000829};
ll counts[5] = {1,1,1,1,1};
ll expected[5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // nums = ll {1000000007, 1000000207, 1000000409, 1000000531, , 1000000829};
    string num; cin >> num;
    for(int i = 0; i < num.size(); i++) {
        int digit = num[i] - '0';
        for(int t = 0; t < 5; t++) {
            expected[t] *= 10;
            expected[t] += digit;
            expected[t] %= nums[t];
            // cout << "dig: " << digit << " " << expected[t] << "\n";
        }
    }
    for(int i = 0; i < 5; i++) {
        // cout << expected[i] << " ";
    }
    int index = 1;
    while(true) {
        // cout << "inf: " << index << "\n";
        bool flag = true;
        for(int t = 0; t < 5; t++) {
            counts[t] *= index;
            counts[t] %= nums[t];
            if(counts[t] != expected[t]) {
                flag = false;
            }
        }
        if(flag) {
            break;
        }
        index++;
    }
    cout << index << "\n";
    return 0;
}