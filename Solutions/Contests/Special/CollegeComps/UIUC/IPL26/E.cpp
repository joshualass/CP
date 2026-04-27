#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

ll calc_score(const string& s, ll x, ll y, ll z) {
    ll ans = 0;
    for(int i = 0; i < s.size(); i++) {
        if(i + 3 <= s.size() && s[i + 0] == 'I' && s[i + 1] == 'G' && s[i + 2] == 'M') {
            ans += x;
        }   
        if(i + 2 <= s.size() && s[i + 0] == 'G' && s[i + 1] == 'M') {
            ans += y;
        }
        if(i + 2 <= s.size() && s[i + 0] == 'I' && s[i + 1] == 'M') {
            ans += z;
        }
    }
    return ans;
}

void append_IGM(string& s, ll& a, ll& b, ll& c) {
    while(a != 0 && b != 0 && c != 0) {
        a --, b --, c --;
        s.push_back('I');
        s.push_back('G');
        s.push_back('M');
    }
}

void append_GM(string& s, ll& a, ll& b, ll& c) {
    while(b != 0 && c != 0) {
        b --, c --;
        s.push_back('G');
        s.push_back('M');
    }
}

void append_IM(string& s, ll& a, ll& b, ll& c) {
    while(a != 0 && c != 0) {
        a --, c --;
        s.push_back('I');
        s.push_back('M');
    }
}

void append_fill(string& s, ll& a, ll& b, ll& c) {
    while(c --) s.push_back('M');
    while(b --) s.push_back('G');
    while(a --) s.push_back('I');
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        ll a, b, c, x, y, z;
        cin >> a >> b >> c >> x >> y >> z;
        string best = "";
        ll res = LLONG_MIN;

        auto dfs = [&](auto self, vector<int> cur, vector<int> vis) -> void {
            
            ll ta = a, tb = b, tc = c;
            string s = "";
            for(int x : cur) {
                if(x == 0) {
                    append_IGM(s, ta, tb, tc);
                } else if(x == 1) {
                    append_GM(s, ta, tb, tc);
                } else if(x == 2) {
                    append_IM(s, ta, tb, tc);
                }
            }

            append_fill(s, ta, tb, tc);
            ll score = calc_score(s, x, y, z);
            if(score > res) {
                res = score;
                best = s;
            }

            if(sz(cur) == 3) return;

            for(int i = 0; i < 3; i++) {
                if(vis[i] == 0) {
                    cur.push_back(i);
                    vis[i] = 1;
                    self(self, cur, vis);
                    cur.pop_back();
                    vis[i] = 0;
                }
            }
        };

        vector<int> cur, vis(3);

        dfs(dfs, cur, vis);

        int best_igm_cnt = -1, gm_cnt = -1, im_cnt = -1;

        for(int i = 1; i <= min({a, b, c}); i++) {
            ll ta = a - i, tb = b - i, tc = c - i;
            ll im_use, gm_use;

            if(y > z) {
                gm_use = min(tb, tc);
                tb -= gm_use;
                tc -= gm_use;
                im_use = min(ta, tc);
            } else {
                im_use = min(ta, tc);
                ta -= im_use;
                tc -= im_use;
                gm_use = min(tb, tc);
            }

            // cout << "i : " << i << " im_use : " << im_use << " gm_use : " << gm_use << endl;

            ll score = i * (x + y) + gm_use * y + im_use * z;
            if(score > res) {
                res = score;
                best_igm_cnt = i;
                gm_cnt = gm_use;
                im_cnt = im_use;
            }
        }

        if(best_igm_cnt != -1) {
            best = "";
            for(int i = 0; i < best_igm_cnt; i++) {
                best.append("IGM");
                a--; b--; c--;
            }
            for(int i = 0; i < gm_cnt; i++) {
                best.append("GM");
                b--; c--;
            }
            for(int i = 0; i < im_cnt; i++) {
                best.append("IM");
                a--; c--;
            }
            append_fill(best, a, b, c);
        }

        cout << res << '\n';
        cout << best << '\n';

    }
    
    return 0;
}