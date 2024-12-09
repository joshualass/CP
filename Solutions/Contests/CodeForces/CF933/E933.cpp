#include <bits/stdc++.h>
typedef int64_t banana;
typedef long double ld;
using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    banana n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (banana i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (banana i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

vector<banana> multiply(vector<banana> const& a, vector<banana> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    banana n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (banana i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<banana> result(n);
    for (banana i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // banana n, x; cin >> n >> x;
    // vector<banana> a(n+1);
    // a[0] = 1;
    // banana c = 0;
    // for(banana i = 0; i < n; i++) {
    //     banana b; cin >> b;
    //     if(b < x) c++;
    //     a[c]++;
    // }

    // vector<banana> b(c+1,1);
    // vector<banana> pm = multiply(a,b);

    // for(banana i = 0; i <= n; i++) {
    //     cout << pm[i+c] << " \n"[i == n];
    // }

    banana n, x; cin >> n >> x;
    vector<banana> a(n);
    for(banana &x : a) cin >> x;
    vector<banana> b(n+1), c(n+1);
    banana cu = 0;
    b[cu]++;
    for(banana i = 0; i < n; i++) {
        if(a[i] < x) cu++;
        b[cu]++;
    }
    cu = 0;
    c[cu]++;
    for(banana i = n - 1; i >= 0; i--) {
        if(a[i] < x) cu++;
        c[cu]++;
    }

    vector<banana> d = multiply(b,c);

    banana z = 0;
    for(banana i = 0; i < n;) {
        banana y = i;
        while(y < n && a[y] >= x) {
            y++;
        }
        z += (y-i)*(y-i+1)/2;
        i = y + 1;
    }

    for(banana i = 0; i <= n; i++) {
        if(i == 0) {
            cout << z << " \n"[i == n];
        } else if(cu - i >= 0) {
            cout << d[cu-i] << " \n"[i == n];
        } else {
            cout << '0' << " \n"[i == n];
        }
    }

    return 0;
}