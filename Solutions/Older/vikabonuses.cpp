#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll additional(ll digit, ll sales) {
    if(digit == 0) {
        return 0;
    }
    if(digit == 5) {
        return (sales > 0 ? 5 : 0);
    }
    ll add = 0;
    while(sales > 0 && digit != 2) {
        // cout << "inf1";
        add += digit;
        sales--;
        digit *= 2;
        digit %= 10;
    }
    if(digit == 2) {
        int cycles = sales/4;
        add += cycles * 20;
        sales -= cycles * 4;
    }
    while(sales > 0) {
        // cout << "inf2";
        sales--;
        add += digit;
        digit *= 2;
        digit %= 10;
    }
    return add;
}

ll calcTotal(ll bonus, ll sales, ll saves) {
    bonus += additional(bonus % 10, saves);
    return bonus * (sales - saves);
}

void solve() {
    ll s, k; cin >> s >> k;

    //value store show many days you accumulate the bonus before buying out
    int l = 0;
    int r = k - 1;


    //ternary serach :)
    while(r - l > 100) {
        // cout << "inftern";
        if(r - l < 3) {
            ll L = calcTotal(s, k, l);
            ll R = calcTotal(s, k, r);
            ll M = calcTotal(s, k, (l + r) / 2);
            if(L >= R && L >= M) {
                r = l;
            } else if(M >= R && M >= L) {
                l = (l + r) / 2;
                r = (l + r) / 2;
            } else {
                l = r;
            }
        } else {
            ll M1 = calcTotal(s, k, l + (r - l) / 3);
            ll M2 = calcTotal(s, k, l + (r - l) / 3 * 2);
            if(M1 >= M2) {
                r = l + (r - l) / 3 * 2;
            } else {
                l = l + (r - l) / 3;
            }
        }
    }

    ll most = calcTotal(s, k, l);
    for(int i = 1; i <= 10000; i++) {
        if(l - i >= 0) {
            most = max(most, calcTotal(s, k, l - i));
        } else {
            break;
        }
    }
    for(int i = 1; i <= 10000; i++) {
        if(l + i < k) {
            most = max(most, calcTotal(s, k, l + i));
        } else {
            break;
        }
    }
    cout << most << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}