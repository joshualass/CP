#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int c;
    cin >> c;
    while (c-- > 0) {
        ll l, m;
        cin >> l >> m;
        l *= 100;
        map<ll, ll> lefts;
        map<ll, ll> rights;
        for (int i = 0; i < m; i++) {
            ll length;
            string side;
            cin >> length >> side;
            if (side == "left") {
                if (lefts.find(length) == lefts.end()) {
                    lefts.insert({length, 1});
                } else {
                    lefts[length]++;
                }
            } else {
                if (rights.find(length) == rights.end()) {
                    rights.insert({length, 1});
                } else {
                    rights[length]++;
                }
            }
        }
        int leftcount = 0;
        while (lefts.size() != 0) {
            ll remaining = l;
            leftcount++;
            while (lefts.size() != 0 && (*(lefts.begin())).first <= remaining) {
                pair<ll, ll> minus;
                if (lefts.size() == 1) {
                    minus = *(lefts.begin());
                } else {
                    minus = (*(--lefts.upper_bound(remaining)));
                }
                remaining -= minus.first;
                lefts[minus.first]--;
                if (lefts[minus.first] <= 0) {
                    lefts.erase(minus.first);
                }
            }
        }
        int rightcount = 0;
        while (rights.size() != 0) {
            ll remaining = l;
            rightcount++;
            while (rights.size() != 0 &&
                   (*(rights.begin())).first <= remaining) {
                pair<ll, ll> minus;
                if (rights.size() == 1) {
                    minus = *(rights.begin());
                } else {
                    minus = (*(--rights.upper_bound(remaining)));
                }
                remaining -= minus.first;
                rights[minus.first]--;
                if (rights[minus.first] <= 0) {
                    rights.erase(minus.first);
                }
            }
        }
        cout << max(leftcount * 2 - 1, rightcount * 2) << '\n';
    }

    return 0;
}