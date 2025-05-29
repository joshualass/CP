#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
instead of trying dp on the smallest number to make each string, try doing some dp on the actual string themselves and see the 
smallest number to make these strings possible + count these strings. 

they are pretty similar. 

X 9's, Y 0's, assume there are later digits, denote as D, digit that increases is I. 
always need a digit that increases. 

D000I000
D000I999

below is better
D00009I0
D00009I9

when is I the first digit. 

I0
I9

I00
I99

I000
I999

observations
always have a digit that increases. 
always have a nonzero leading digit 
digit that increases is of the form
... ???I00000 ...
... ???I99999 ...
with no leading 0s. 



how to count all things correctly?
how to optimally place the 0's and 9's?

if given x 0's and y 9's, must also have a digit that increases. 
case - at least have an extra digit pair that is not 0/9
can greedily place all digits in ascending order, putting the smallest nonzero at front, it is 
allowed to have both an odd amt of 0 and 9, then we put this at the front. 

case - the only digits are 0's 9's and the increased value
if there are an equal # of 0's and 9's, then do I0000, I99999
else, have to do normal greedy starts. 

9001
9002

unique

901
902 

not unique

try inclusion/exclusion-like

*/

int bf (int n) {
    set<string> s;
    for(int i = 1; i <= n; i++) {
        string t = to_string(i) + to_string(i + 1);
        sort(t.begin(),t.end());
        s.insert(t);
    }
    return s.size();
}

void solve() {
    
    int n; cin >> n;



}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << bf(899) << '\n';
    cout << bf(999) << '\n';

    // int casi; cin >> casi;
    // while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// /*
// did not consider a case like 

// n = 199 
// 199200
// 001299
// n = 901
// 901902
// 001299

// 909 fails assert 

// gg

// */

// int bf (int n) {
//     set<string> s;
//     for(int i = 1; i <= n; i++) {
//         string t = to_string(i) + to_string(i + 1);
//         sort(t.begin(),t.end());
//         s.insert(t);
//     }
//     return s.size();
// }

// void solve() {
//     ll n; cin >> n;
//     string ns = to_string(n);
//     int nd = ns.size(); //num digits

//     vector<int> p10(10);
//     p10[0] = 1;
//     for(int i = 1; i < 10; i++) p10[i] = p10[i-1] * 10;

//     int res = 0;

//     for(int len = 1; len <= nd; len++) {
//         cout << "len : " << len << '\n';
//         vector dp(len, vector(10, vector<ll>(2))); //{len of pref, max digit used, 0 / 1 if tight on n}

//         //handle all but the first digit 9
//         for(int l = 1; l < 10; l++) {
//             int num = (l + 1) * p10[len - 1] - 1;
//             if(num <= n) {
//                 // cout << "add full l : " << l << '\n';
//                 res++;
//             }
//         }

//         //initialize first number + some amt of zeroes 
//         for(int i = 1; i <= 9; i++) { //first digit in num
//             for(int j = 1; j < len; j++) { //zc + 1
//                 int num = i * p10[j - 1];
//                 int tn = n / p10[len - j];
//                 if(num <= tn) {
//                     // cout << "i : " << i << " j : " << j << " num : " << num << " tn : " << tn << '\n';
//                     dp[j][i][num == tn] = 1;
//                 }
//             }   
//         }

//         for(int i = 1; i < len; i++) { //current digit
//             for(int j = 1; j < 10; j++) { //current max digit
//                 for(int k = 0; k < 2; k++) { //tight 0 / 1
//                     if(dp[i][j][k]) {
//                         if(k) { //tight here
//                             assert(dp[i][j][k] == 1);
//                             // cout << "reach tight i : " << i << " j : " << j << " k : " << k << '\n';
//                             for(int l = 0; l < 10; l++) { //try all possible next digits X9999 combos 
//                                 int num = (l + 1) * p10[len - i - 1] - 1;
//                                 int tn = n % p10[len - i];
//                                 // cout << "i : " << i << " j : " << j << " l : " << l << " num : " << num << " tn : " << tn << '\n';

//                                 if(num <= tn) res++;
//                             }
//                             if(i + 1 < len) { //push
//                                 int nxd = n / p10[len - i - 2] % 10; //next digit 
//                                 for(int l = j; l <= nxd; l++) {
//                                     dp[i+1][l][l == nxd] += dp[i][j][k];
//                                 }
//                             }
//                         } else {
//                             // cout << "add i : " << i << " j : " << j << " k : " << k << '\n';
//                             res += dp[i][j][k] * 9; //last digit can be 0 - 8. 
//                             if(i + 1 < len) {
//                                 for(int l = j; l <= 9; l++) {
//                                     dp[i+1][l][0] += dp[i][j][k];
//                                 }
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     cout << "solve ";
//     cout << res << '\n';
//     cout << "bf " << bf(n) << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     set<string> s;
//     for(int i = 1; i <= 10000; i++) {
//         string t = to_string(i) + to_string(i+1);
//         sort(t.begin(), t.end());
//         if(s.count(t) == 0) {
//             s.insert(t);
//         } else {
//             cout << i << '\n';
//         }
//     }

//     // int casi; cin >> casi;
//     // while(casi-->0) solve();

//     return 0;
// }