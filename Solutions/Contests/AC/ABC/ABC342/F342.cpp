#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(15);

    //try to solve better later
    

    // int n, l, d; cin >> n >> l >> d;

    // vector<ld> y(n+1);
    // vector<ld> subs(n+1);
    // subs[1] = 1;
    // ld active = 1;
    // for(int i = 0; i <= n; i++) {
    //     active -= subs[i];
    //     //force roll
    //     if(i < l) {
    //         ld avg = active / d;
    //         if(i + d + 1 <= n) {
    //             subs[i + d + 1] = avg;
    //         }
    //         active += avg;
    //     } else {
    //         y[i] = active;
    //     }
    // }

    // // cout << "y : " << y << '\n';

    // vector<ld> ypref(n+1); //ypref[0] = 0;
    // for(int i = 1; i <= n; i++) {
    //     ypref[i] = ypref[i-1];
    //     ypref[i] += y[i];
    // }

    // ld bust = 1 - ypref[n];

    // ld maxwin = bust;

    // // cout << "ypref : " << ypref << '\n';
    // // cout << "bust : " << bust << '\n';

    // // vector<ld> rolluntil(n+1); //if we roll up to and including this index, how will our odds change
    // ld ev = 0;

    // vector<ld> probs(n+1); //if you are at index i, stores the probability of reaching i
    // active = 1;
    // subs.assign(n+1,0);
    // subs[1] = 1;
    // for(int i = 0; i <= n; i++) {
    //     active -= subs[i];
    //     probs[i] = active;
    //     ld avg = active / d;
    //     if(i + d + 1 <= n) {
    //         subs[i + d + 1] = avg;
    //     }
    //     active += avg;
    // }
    
    // // cout << "probs : " << probs << '\n';

    // for(int i = 1; i <= n + d; i++) {
    //     //roll up to i - l
    //     //if we choose to roll at index i - l, we now have a probability to beat all values at i - 1 which is probabilty of (i - l) / l
    //     if(i - d < n) {
    //         // cout << "add i : " << i << " add val : " << ypref[min(i-1,n-1)] / d * probs[max(0,i-d)] << '\n';
    //         // cout << "v1 : " << ypref[min(i-1,n-1)] / d << " v2 : " << probs[max(0,i-d)] << '\n';
    //         ev += ypref[min(i-1,n-1)] / d * probs[max(0,i-d)];
    //     }
    //     //if we choose to roll at index i - l, we lose probability of winning at indexes i - l - 1
    //     if(i - d - 1 >= 0) {
    //         // cout << "sub i : " << i << " sub val : " << ypref[i-d-1] / d * probs[max(0,i-d-d)] << '\n';
    //         ev -= ypref[i-d-1] / d * probs[max(0,i-d-d)];
    //     }
    //     if(i - d >= 0) {
    //         maxwin = max(maxwin, ev + bust);
    //     }
    //     if(i - d >= 0) {
    //         // cout << "stop at : " << i - d << " ev : " << ev << '\n';
    //     }
    //     // cout << "i : " << i << " ev : " << ev << '\n';
    // }

    // cout << maxwin << '\n';

    return 0;
}