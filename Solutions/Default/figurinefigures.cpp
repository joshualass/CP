// https://open.kattis.com/problems/figurinefigures
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(60000);
    ll sum = 0;
    int least = INT_MAX;
    int most = INT_MIN;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v[num-1] = 1;
        least = min(least, num);
        most = max(most, num);
        sum += num;
    }

    vector<int> ans = v;
    for(int i = 0; i < 3; i++) {
        ans = multiply(ans,v);
        for(auto &x: ans) {
            if(x) x = 1;
        }
    }
    int cnt = 0;
    for(int i = 0; i < ans.size(); i++) {
        if(ans[i] != 0) {
            cnt++;
        }
    }

    cout << most * 4 << " " << least * 4 << " " << cnt << " " << fixed << setprecision(10) << ((ld)sum) / n * 4 << "\n";

    return 0;
}