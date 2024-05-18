#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p);

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v);

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<ll> teachers(n);
    for(ll &x : teachers) cin >> x;
    sort(teachers.rbegin(), teachers.rend());
    while(n != m) {
        teachers.pop_back();
        n--;
    }
    reverse(teachers.begin(), teachers.end());
    vector<pair<ll,vector<pair<ll,ll>>>> groups(m); // {sum, {student age, student id}}
    int gc = 0;
    for(int i = 0; i < m; i++) {
        int cnt; cin >> cnt;
        groups[i].second.resize(cnt);
        ll sum = 0;
        for(int j = 0; j < cnt; j++) {
            cin >> groups[i].second[j].first;
            groups[i].second[j].second = gc++;
            sum += groups[i].second[j].first;
        }
        groups[i].first = sum;
    }
    sort(groups.begin(), groups.end(), [] (auto &lhs, auto &rhs) -> bool {
        return lhs.first * rhs.second.size() < rhs.first * lhs.second.size();
    });

    // cout << "teachers : " << teachers << '\n';
    // cout << "groups : " << groups << '\n';

    //all 1-indexed
    vector<int> noshift(n+1); //at index i, is it satisfied with no shift
    vector<int> leftshift(n+1); //is the teacher at index i still satisfied after left shift
    vector<int> rightshift(n+1); //is the teacher at index i still satisfied after right shift

    for(int i = 0; i < n; i++) {
        if(i != 0 && teachers[i-1]     * groups[i].second.size() >= groups[i].first) {
            leftshift[i] = 1;
        }
        if(teachers[i]                 * groups[i].second.size() >= groups[i].first) {
            noshift[i+1] = 1;
        }
        if(i != n - 1 && teachers[i+1] * groups[i].second.size() >= groups[i].first) {
            rightshift[i+2] = 1;
        }
    }

    for(int i = 0; i < n; i++) {
        noshift[i+1] += noshift[i];
        leftshift[i+1] += leftshift[i];
        rightshift[i+1] += rightshift[i];
    }

    // cout << "no : " << noshift << '\n';

    vector<bool> ans(gc);

    for(int i = 0; i < n; i++) {
        for(pair<ll,ll> student : groups[i].second) {
            int lo = 0, hi = n - 1;
            ll newsum = groups[i].first - student.first;
            ll newcnt = groups[i].second.size() - 1;
            while(lo != hi) {
                int m = (lo + hi) / 2;
                if(teachers[m] * newcnt >= newsum) {
                    hi = m;
                } else {
                    lo = m + 1;
                }
            }
            bool ok = teachers[lo] * newcnt >= newsum;
            // cout << "id : " << student.second << " start ok : " << ok << '\n';
            if(lo < i) {
                //teachers 0 - (lo - 1) unchanged, teacher lo has i, teachers (lo + 1) - i right shift, teachers (i + 1) - (n - 1) unchanged
                ok &= noshift[lo] == lo;
                ok &= rightshift[i+1] - rightshift[lo+1] == i - lo;
                ok &= noshift[n] - noshift[i+1] == n - (i + 1);
                // cout << "student id : " << student.second << " ok : " << ok << " lo < i\n";
            } else if(lo > i) {
                //teachers 0 - (i - 1) unchanged, teachers i - (lo - 1) left shift, teacher lo has i, teachers (lo + 1) - (n - 1) unchanged
                ok &= noshift[i] == i;
                ok &= leftshift[lo] - leftshift[i] == lo - i;
                ok &= noshift[n] - noshift[lo+1] == n - (lo + 1);
                // cout << "student id : " << student.second << " ok : " << ok << " lo > i\n";
            } else {
                // ok &= noshift[n] == n;
                ok &= noshift[lo] == lo;
                ok &= noshift[n] - noshift[i+1] == n - (lo + 1);
                // cout << "student id : " << student.second << " ok : " << ok << " lo == i\n";
            }      

            ans[student.second] = ok;
        }
    }
    for(bool x : ans) cout << x;
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}