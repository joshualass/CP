#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

int getnext(int num, vector<int> &b, int sum) {
    int start = sum - num;
    for(int i = 0; i <= 9; i++) {
        if(b[(start + i) % 10]) {
            return (start + i) % 10;
        }
    }
    return -1; //this shouldn't happen 
}

int sum_digits(string &a, string &b) {
    int sum = 0;
    bool carry = false;

    for(int i = 0; i < max(a.size(),b.size()); i++) {
        int digit = carry;
        if(i < a.size()) {
            digit += a[i] - '0';
        }
        if(i < b.size()) {
            digit += b[i] - '0';
        }
        sum += digit % 10;
        carry = digit / 10;
    }
    return sum;
}

pair<pair<string,string>,int> solve(vector<int> a, vector<int> b, int start, int asize) {
    // cout << "prebegin: " << a << " " << b << '\n';
    // cout << "hey\n";
    string stra = "";
    string strb = "";
    stra.push_back('0' + start);
    int next = getnext(start, b,10);
    // cout << "start: " << start << " next: " << next << '\n';
    strb.push_back('0' + next);
    a[start]--;
    b[next]--;

    // cout << "begin: " << a << " " << b << '\n';

    int perfect_found = 0;
    int carry_found = 0;

    for(int i = 1; i < asize; i++) {
        while(perfect_found < 10) {
            if(a[perfect_found] == 0 || b[9-perfect_found] == 0) {
                perfect_found++;
            } else {
                break;
            }
        }
        if(perfect_found < 10) { //we can make a sum to 9 here
            // cout << "use perfect: " << perfect_found << " i: " << i << '\n';
            stra.push_back('0' + perfect_found);
            strb.push_back('0' + (9 - perfect_found));
            a[perfect_found]--;
            b[9-perfect_found]--;
            continue;
        }
        while(carry_found < 10) {
            if(a[carry_found] == 0 || getnext(carry_found,b,9) + carry_found < 10) {
                carry_found++;
            } else {
                break;
            }
        }
        if(carry_found < 10) {
            // cout << "use carry: " << carry_found << " i: " << i << '\n';
            int bnum = getnext(carry_found,b,9);
            stra.push_back('0' + carry_found);
            strb.push_back('0' + bnum);
            a[carry_found]--;
            b[bnum]--;
            continue;
        }
    }

    // cout << "a: " << a << '\n';
    // cout << "b: " << b << '\n';

    for(int i = 0; i < 10; i++) {
        if(a[i] != 0) {
            stra.push_back(i + '0');
            a[i]--;
            i--;
        }
    }

    for(int i = 9; i >= 0; i--) {
        if(b[i] != 0) {
            strb.push_back(i + '0');
            b[i]--;
            i++;
        }
    }
    return {{stra,strb},sum_digits(stra,strb)};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string a, b; cin >> a >> b;
    bool useswap = false;
    if(a.size() > b.size()) {
        useswap = true;
        swap(a,b);
    }

    vector<int> acnts(10);
    vector<int> bcnts(10);

    for(int i = 0; i < a.size(); i++) {
        acnts[a[i] - '0']++;
    }

    for(int i = 0; i < b.size(); i++) {
        bcnts[b[i] - '0']++;
    }
    pair<pair<string,string>,int> ans = {{"",""},INT_MAX};
    for(int i = 1; i <= 9; i++) {
        if(acnts[i] == 0) continue;
        // cout << "pass : " << acnts << " " << bcnts << '\n';
        pair<pair<string,string>,int> p = solve(acnts,bcnts,i, a.size());
        if(p.second < ans.second) {
            ans = p;
        }
    }

    reverse(ans.first.first.begin(), ans.first.first.end());
    reverse(ans.first.second.begin(), ans.first.second.end());

    if(useswap) {
        cout << ans.first.second << "\n" << ans.first.first << '\n';
    } else {
        cout << ans.first.first << "\n" << ans.first.second << '\n';
    }

    return 0;
}