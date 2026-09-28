#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void tripleshift(int index, vector<int> &v) {
    swap(v[index], v[index+1]);
    swap(v[index], v[index+2]);
}

void rightshift(int index, vector<int> &v) {
    tripleshift(index, v);
    tripleshift(index, v);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

bool samenums(vector<int> a, vector<int> b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for(int i = 0; i < a.size(); i++) {
        if(a[i] != b[i]) return false;
    }
    return true;
}

bool dupes(vector<int> a) {
    set<int> s(a.begin(), a.end());
    return s.size() != a.size();
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<int> a(n);
    vector<int> b(n);

    for(auto &x : a) cin >> x;
    for(auto &y: b) cin >> y;

    //don't contain same nums
    if(!samenums(a,b)) {
        cout << "No\n";
        return 0;
    }

    //have a duplicate, then always possible
    if(dupes(a)) {
        cout << "Yes\n";
        return 0;
    }

    //greedily simulate to see if it works
    for(int i = 0; i < n - 2; i ++) {

        int idx = -1;
        for(int j = i; j < n; j++) {

            if(a[j] == b[i]) {
                idx = j;
                break;
            }

        }

        if(idx == n - 1) {
            tripleshift(idx - 2, a);
            idx -= 2;
        } else if(idx == n - 2) {
            rightshift(idx - 1, a);
            idx--;
        }
        for(int j = idx - 1; j >= i; j--) {
            rightshift(j,a);
        }
    }

    bool flag = true;
    for(int i = 0; i < a.size(); i++) {
        if(a[i] != b[i]) flag = false;
    }
    
    cout << (flag ? "Yes" : "No") << '\n';

    return 0;
}