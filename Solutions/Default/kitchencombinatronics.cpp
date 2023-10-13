//https://open.kattis.com/problems/kitchencombinatorics
//nothing very tricky about this problem
//just find the number of ways you can make every combination of dishes, since they are low in amount
//ingredients are also low enough so it can run in time
#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//O(25 * 25 * 25 * (20 * 3 + 1000))
const lll most = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    lll sum = 0;
    int r, s, m, d, n; cin >> r >> s >> m >> d >> n;
    vector<ll> ingredients(r);
    for(auto &x: ingredients) cin >> x;
    vector<vector<ll>> dishes(s + m + d);
    for(int i = 0; i < s + m + d; i++) {
        int k; cin >> k;
        for(int j = 0; j < k; j++) {
            int num; cin >> num;
            num--;
            dishes[i].push_back(num);
        }
    }
    set<pair<int,int>> invalids;
    for(int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        invalids.insert({--a,--b});
        invalids.insert({b,a});
    }
    bool toomany = false;
    for(int i = 0; i < s; i++) {
        for(int j = s; j < s + m; j++) {
            for(int k = s + m; k < s + m + d; k++) {
                // cout << i << " " << j << " " << k << "\n";
                if(invalids.find({i,j}) != invalids.end() || invalids.find({i,k}) != invalids.end() || invalids.find({k,j}) != invalids.end()) continue;
                vector<bool> used(r);
                for(int l = 0; l < dishes[i].size(); l++) {
                    used[dishes[i][l]] = true;
                }
                for(int l = 0; l < dishes[j].size(); l++) {
                    used[dishes[j][l]] = true;
                } 
                for(int l = 0; l < dishes[k].size(); l++) {
                    used[dishes[k][l]] = true;
                }   
                lll mult = 1;
                for(int l = 0; l < r; l++) {
                    if(used[l]) {
                        mult *= ingredients[l];
                    }
                    if(mult > most) toomany = true;
                }
                sum += mult;
                if(sum > most) toomany = true;
            }
        }
    }
    if(toomany) cout << "too many\n";
    else cout << (ll) sum << "\n";


    return 0;
}