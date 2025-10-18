#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 4e6 + 1;
int truePrefix[N];
int falsePrefix[N];

bool poss(int start, int n) {
    int falses = falsePrefix[start + n/2] - falsePrefix[start];
    int trues = truePrefix[start + n] - truePrefix[start + (n+1)/2];
    return falses == n/2 && trues == n /2;
}   

bool poss2(int start, int n) { //need to add n operations
    int trues = truePrefix[start + n/2] - truePrefix[start];
    int falses = falsePrefix[start + n] - falsePrefix[start + (n+1)/2];
    return falses == n/2 && trues == n /2;    
}

bool checkRev(int start, int n, vector<int> &a, vector<int> &b) {

    for(int i = start; i < n + start; i++) {
        int lo, hi;
        lo = a[i];
        hi = b[start * 2 + n - i - 1];
        if(lo != hi) {
            // cout << "fail rev i: " << i << " lo: " << lo << " hi: " << hi << "\n";
            return false;
        }
    }

    return true;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n*2);
    vector<int> b(n*2);
    // for(auto &x: a) cin >> x;
    // for(auto &y: b) cin >> y;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a[i] = num;
        b[i+n] = num;
    }
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        b[i] = num;
        a[i+n] = num;
    }

    int equals = 0;
    int equalidx = -1;
    truePrefix[0] = 0;
    falsePrefix[0] = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] > b[i]) {
            truePrefix[i+1] = truePrefix[i] + 1;
            falsePrefix[i+1] = falsePrefix[i];
        } else if(b[i] > a[i]) {
            truePrefix[i+1] = truePrefix[i];
            falsePrefix[i+1] = falsePrefix[i] + 1;            
        } else {
            equals++;
            equalidx = i - n /2;
        }
    }
    for(int i = n; i < n * 2; i++) {
        if(a[i-n] > b[i-n]) {
            truePrefix[i+1] = truePrefix[i];
            falsePrefix[i+1] = falsePrefix[i] + 1;            
        } else if(b[i-n] > a[i-n]) {
            truePrefix[i+1] = truePrefix[i] + 1;
            falsePrefix[i+1] = falsePrefix[i];
        }    
    }

    if(equals) {
        if((n & 1) == 0 || equals > 1) {
            // cout << "FAIL EQUALS\n";
            cout << "-1\n";
            return;
        }
    }
    // for(int i = 0; i < 13; i++) {
    //     cout << truePrefix[i] << " ";
    // }
    // cout << "\n";
    // for(int i = 0; i < 13; i++) {
    //     cout << falsePrefix[i] << " ";
    // }
    // cout << "\n";

    for(int i = 0; i < n * 2; i++) {
        if(equals) {
            if(i != equalidx && i != equalidx + n) continue;
        }
        if(i < n) {
            // cout << "i: " << i << " " << "poss? " << poss(i,n) << ' ' << "rev? " << checkRev(i,n,a,b) << "\n";
            if(poss(i,n) && checkRev(i,n,a,b)) {
                cout << i << "\n";
                return;
            }
        } else {
            // cout << "i: " << i << " " << "poss2? " << poss2(i-n,n) << ' ' << "rev? " << checkRev(i-n,n,a,b) << "\n";
            // cout << i << "\n";
            if(poss2(i-n,n) && checkRev(i-n,n,a,b)) {
                cout << i << "\n";
                return;
            }
        }
    }

    // cout << "end fail ...\n";
    cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    freopen("B2.in","r",stdin);
    freopen("B2.txt","w",stdout);
    
    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}