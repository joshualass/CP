#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int p, h; cin >> p >> h;
    vector<vector<ll>> holes(p, vector<ll>(h));
    for(auto &x: holes) {
        for(auto &y: x) cin >> y;
        x.push_back(1e9+5);
        sort(x.begin(), x.end());
    }

    for(int i = 0; i < p; i++) {
    // for(int i = 0; i < 1; i++) {
        vector<pair<int,int>> ranges(0);
        // cout << "i: " << i <<  " ";
        for(int j = 0; j < p; j++) {
            if(i == j) continue;
            ll l = 0;
            ll iptr = 0;
            ll jptr = 0;
            ll icnt = 0;
            ll jcnt = 0;
            while(l <= 1e9) {
                //update scores
                while(iptr < h && l >= holes[i][iptr]) {
                    icnt += holes[i][iptr++];
                }
                while(jptr < h && l >= holes[j][jptr]) {
                    jcnt += holes[j][jptr++];
                }

                ll iscore = icnt + (l * (h - iptr)); //current scores
                ll jscore = jcnt + (l * (h - jptr)); //current scores
                ll inext = iscore + (p - iptr); //scores of l + 1
                ll jnext = jscore + (p - jptr); //scores of l + 1
                // cout << "l: " << l << "\n";
                // cout << "iptr: " << iptr << " jptr: " << jptr << "\n";
                // cout << "iscore: " << iscore << " jscore: " << jscore << "\n";
                // cout << "inext: " << inext << " jnext: " << jnext << "\n";
                for(ll t = iptr; t < p; t++) {
                    if(holes[i][t] != l) {
                        break;
                    }
                    inext--;
                }
                for(ll t = jptr; t < p; t++) {
                    if(holes[j][t] != l) {
                        break;
                    }
                    jnext--;
                }

                if(iscore < jscore) { //currently winning 
                    if(jnext <= inext) { //next is losing, stopping point here [l,r]
                        // cout << "no longer win " << " l: " << l + 1 << " j: " << j << "\n";
                        ranges.push_back({l+1,-1});
                        l++;
                    } else {
                        ll next = max(l+1,min(holes[i][iptr]-1, holes[j][jptr]-1));
                        // cout << "next? " << next << "\n";
                        if(iptr < jptr) {
                            next = min(next, max(l+1,l + (jscore - iscore) / (jptr - iptr) - 1));
                        }
                        l = next;
                    }
                } else { //currently tied/losing (Ethan's team rn)
                    if(inext < jnext) {//l + 1 is winning
                        // cout << "start winning l: " << l + 1 << " j: " << j << "\n";
                        ranges.push_back({l+1,1});
                        l++;
                    } else {
                        ll next = max(l+1,min(holes[i][iptr]-1, holes[j][jptr]-1));
                        if(iptr > jptr) {
                            next = min(next, max(l+1,l + (iscore - jscore) / (iptr - jptr) - 1));
                        }
                        l = next;
                    }
                }
            }
        }

        for(auto x : ranges) {
            // cout << x.first << " " << x.second << " ";
        }
        sort(ranges.begin(), ranges.end());
        int best = p;
        int curr = 0;
        for(auto x : ranges) {
            curr += x.second;
            best = min(best, p - curr);
        // cout << "curr: " << curr << "\n";
        }
        cout << best << "\n";
        // break;
    }

    return 0;
}