#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    priority_queue<pair<int, int>> o;
    priority_queue<pair<int, int>> l;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (a < 0) {
            l.push({-a, b});
        } else {
            o.push({a, b});
        }
    }

    ll total = 0;
    while (o.size()) {
        int remaining = k;
        int distance = 0;
        bool first = true;
        while (o.size() && remaining > 0) {
            pair<int, int> p = o.top();
            if (first) {
                distance = p.first;
                first = false;
            }
            o.pop();
            if (remaining >= p.second) {
                remaining -= p.second;
            } else {
                o.push({p.first, p.second - remaining});
                remaining = 0;
            }
        }
        total += distance * 2;
    }

    while (l.size()) {
        int remaining = k;
        int distance = 0;
        bool first = true;
        while (l.size() && remaining > 0) {
            pair<int, int> p = l.top();
            if (first) {
                distance = p.first;
                first = false;
            }
            l.pop();
            if (remaining >= p.second) {
                remaining -= p.second;
            } else {
                l.push({p.first, p.second - remaining});
                remaining = 0;
            }
        }
        total += distance * 2;
    }

    cout << total;

    return 0;
}