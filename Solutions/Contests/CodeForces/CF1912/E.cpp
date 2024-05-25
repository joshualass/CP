#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

// ll next_lowest_palindrome(ll num) {

//     string str = to_string(num);
//     int n = str.size();

//     if(num == 1) {
//         return 1;
//     }

//     if(count(str.begin(), str.end(), '0') == n - 1 && count(str.begin(), str.end(), '1') == 1) {
//         string ans = "";
//         for(int i = 1; i < n; i++) {
//             ans.push_back('9');
//         }
//         return stoll(ans);
//     }
    
//     string ans = to_string(num);
    
//     bool needdecrease = 0;
//     for(int i = 0; i < n / 2; i++) {
//         if(str[i] <= str[n-i-1]) {
//             ans[n-i-1] = str[i];
//         } else {
//             int temp = i;
//             bool isnonzero = 0;
//             for(int j = i + 1; j < (n + 1) / 2; j++) {
//                 if(str[j] != '0') isnonzero = 1;
//             }
//             if(isnonzero) {
//                 ans[i] = str[i];
//                 ans[n-i-1] = str[i];
//                 needdecrease = 1;
//             } else {
//                 for(; i <= n / 2; i++) {
//                     ans[i] = '9';
//                     ans[n-i-1] = '9';
//                 }
//                 needdecrease = 0;
//                 ans[temp] = str[temp] - 1;
//                 ans[n-1-temp] = str[temp] - 1;                
//             }
//         }
//     }
//     if(needdecrease) {
//         ans[n/2] = str[n/2] - 1;
//         ans[n-1-n/2] = str[n/2] - 1;
//     }
//     // cout << "num : " << num << " ans : " << ans << '\n';
    
//     return stoll(ans);
// }

ll near_pal(ll num) {
    ll best = 0;
    for(int i = 1; i <= 9; i++) {
        ll curr = 0;
        for(int j = 0; j < 18; j++) {
            curr *= 10;
            curr += i;
            if(curr <= num) best = max(curr,best);
        }
    }
    return best; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll p, q; cin >> p >> q;

    string ans = "";

    ll diff = p - q;

    if(diff & 1) {
        ans = "0+21+0";
        p -= 21;
        q -= 12;
        diff = p - q;
    } else {
        ans = "0";
    }
    // cout << "diff : " << diff / 2 << '\n';
    diff /= 2;
    ll midpoint = (p + q) / 2;

    while(midpoint != 0) {
        ll pal = near_pal(abs(midpoint));
        if(midpoint < 0) {
            ans.push_back('-');
            ans.append(to_string(pal));
            ans.push_back('-');
            ans.push_back('0');
            midpoint += pal;
        } else {
            ans.push_back('+');
            ans.append(to_string(pal));
            ans.push_back('+');
            ans.push_back('0');
            midpoint -= pal;
        }
    }

    while(diff != 0) {
        ll pal = near_pal(abs(diff));
        // cout << "diff : " << diff << " pal : " << pal << '\n';
        if(diff < 0) {
            ans.push_back('-');
            ans.append(to_string(pal));
            ans.push_back('+');
            ans.push_back('0');
            diff += pal;
        } else {
            ans.push_back('+');
            ans.append(to_string(pal));
            ans.push_back('-');
            ans.push_back('0');
            diff -= pal; 
        }
        // diff = 0;
    }

    cout << ans << '\n';

    return 0;
}