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

bool ask(int i, int j) {
    cout << "? " << i + 1 << " " << j + 1 << endl;
    int b; cin >> b;
    return b;
}

int add(int i, int j) {
    cout << "+ " << i + 1 << " " << j + 1 << endl;
    int p; cin >> p;
    return p;
}

void done() {
    cout << "!" << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    //maintain order
    vector<int> order;
    for(int i = 0; i < n; i++) {
        int l = 0, r = order.size();
        while(l != r) {
            int m = (l + r) / 2;
            int b = ask(order[m], i);
            if(b == 1) {
                l = m + 1;
            } else if(b == 0) {
                r = m;
            } else {
                return 69;
            }
        }
        order.insert(order.begin() + l, i);
        // cout << "i : " << i << "order : " << order << '\n';
    }

    while(order.size() != 1) {
        int p = add(order[0], order[order.size() - 1]);
        order.pop_back();
        order.erase(order.begin(), order.begin() + 1);
        p--;
        int l = 0, r = order.size();
        while(l != r) {
            int m = (l + r) / 2;
            int b = ask(order[m], p);
            if(b == 1) {
                l = m + 1;
            } else if(b == 0) {
                r = m;
            } else {
                return 69;
            }
        }
        order.insert(order.begin() + l, p);
    }

    done();

    return 0;
}