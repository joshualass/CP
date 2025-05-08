#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = 0; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int ans = 1e9;
    int n;
    cin >> n;
    vi a(n), b(n), k(n);
    int d = 0;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        int scnt = 0, tcnt = 0;
        for(int j = 0; j < s.size() - 1; j++) scnt += s[j] == 's', tcnt += s[j] == 't';
        if(s[s.size() - 1] == '}') d--;
        a[i] = scnt, b[i] = tcnt, k[i] = d;
        // cout << "ABK : " << a[i] << " " << b[i] << " " << k[i] << "\n";
        if(s[s.size() - 1] == '{') d ++;
    }
    int I = 1e9;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(j == i) continue;
            int num = a[j] * b[i] - a[i] * b[j];
            int denom = k[j] * b[i] - k[i] * b[j];
            // cout << "ND : " << num << " " << denom << " " << i << " " << j << "\n";
            // cout << a[i] << " " << b[i] << " " << k[i] << "\n";
            // cout << a[j] << " " << b[j] << " " << k[j] << "\n";
            // cout << a[i] * b[j] << " " << -a[j] * b[i] << " " << k[i] * b[j] << " " << -k[j] * b[i] << "\n";
            if(num == 0 && denom == 0) {
                //indeterminate
                continue;
            }
            else if(denom == 0) {
                //impossible
                I = -1;
                goto outer;
            }
            else {
                if(abs(num) % abs(denom) != 0) {
                    //answer is not an integer
                    I = -1;
                    goto outer;
                }
                if(num / denom <= 0) {
                    //bad ans
                    I = -1;
                    goto outer;
                }
                
                I = num / denom;
                if(b[i] != 0) {
                    ans = min(ans, (I * k[i] - a[i]) / b[i]);
                }
                
                // cout << "FOUND ANS : " << num / denom << " " << (I * k[i] - a[i]) / b[i] << "\n";
            }
        }
    }
    outer: {}
    if(I == 1e9) {
        //have to decide on I, just choose the smallest one that works; all equations are identical. 
        for(int i = 0; i < n; i++){
            if(b[i] != 0) {
                //t = (kI - s) / b
                if(a[i] != 0 && a[i] % gcd(k[i], b[i]) != 0){
                    //impossible to choose I here
                    continue;
                }
                for(int j = 1; ; j++){
                    int num = k[i] * j - a[i];
                    if(num % b[i] == 0){
                        I = j;
                        ans = num / b[i];
                        break;
                    }
                }
                break;
            }
        }
        if(I == 1e9) {
            //there doesn't exist t anywhere. 
            ans = 1;
            for(int i = 0; i < n; i++) {
                if(k[i] != 0) {
                    I = a[i] / k[i];
                }
            }
        }
    }
    if(I == -1) {
        cout << "-1\n";
        return 0;
    }
    // cout << "I : " << I << " " << ans << "\n";
    bool is_valid = true;
    //consistency check
    for(int i = 0; i < n; i++){
        if(a[i] + b[i] * ans != k[i] * I) {
            // cout << "INCONSISTENT : " << i << "\n";
            is_valid = false;
        }
        // cout << a[i] << " " << b[i] << " " << k[i] << "\n";
    }
    if(!is_valid){
        cout << "-1\n";
        return 0;
    }
    cout << ans << "\n";

    return 0;
}