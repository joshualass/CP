#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void find_chain(int shijak, vector<ll> &v, vector<ll> &A) {
    int n = v.size();
    ll curr = 0;
    ll curr_min = 0;
    ll min_idx = shijak;
    for(int i = shijak; i + 1 < n; i += 3) {
        ll diff = v[i+1] - v[i];
        curr += diff;
        if(curr < curr_min) {
            curr_min = curr;
            min_idx = i + 3;
        }
    }
    curr = -curr_min;
    A[shijak] = curr;
    for(int i = shijak; i + 1 < n; i += 3) {
        curr += v[i+1] - v[i];
        A[i+3] = curr;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<ll> v(n);
    vector<ll> A(n+2);
    for(auto &x : v) cin >> x;

    find_chain(0,v,A);
    // cout << "A1: " << A << '\n';
    find_chain(1,v,A);
    // cout << "A2: " << A << '\n';
    find_chain(2,v,A);
    // cout << "A3: " << A << '\n';

    ll diff = v[0] - (A[0] + A[1] + A[2]);
    for(int i = 0; i < n + 2; i += 3) {
        A[i] += diff;
    }

    bool ok = 1;
    for(int i = 0; i < n; i++) {
        ll sum = 0;
        for(int j = 0; j < 3; j++) {
            if(A[j + i] < 0) ok = 0;
            sum += A[j + i];
        }
        if(sum != v[i]) ok = 0;
    }

    if(ok) {
        cout << "Yes\n";
        for(auto x : A) cout << x << " ";
        cout << '\n';
    } else {
        cout << "No\n";
    }

    return 0;
}