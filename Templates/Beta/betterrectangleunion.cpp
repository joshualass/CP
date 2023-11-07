#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

typedef pair<ll,ll> T;
 pair<ll,ll> operator+(const  pair<ll,ll>& l, const  pair<ll,ll>& r) {
	return l.first != r.first ? min(l,r) :  pair<ll,ll>{l.first,l.second+r.second};     
}

const int MAXN = 2e6 + 1;
struct LazySeg { 

	const pair<ll,ll> ID = {MOD,0}; 

    pair<ll,ll> comb( pair<ll,ll> a,  pair<ll,ll> b) { 
        return a+b; 
    }

	// pair<ll,ll> seg[2 * MAXN]; 
    int lazy[2000001]; 


	// LazySeg() { 
    //     // for(int i = 0; i < 2 * MAXN; i++) {
    //     //     seg[i] = {0,0};
    //     //     lazy[i] = 0;
    //     // }
    
    // }
	// void push(int ind, int L, int R) { /// modify values for current node
	// 	if (L != R) {
    //         for(int i = 0; i < 2; i++) {
    //             lazy[2 * ind + i] += lazy[ind];
    //         }
    //     }

    //     seg[ind].first += lazy[ind]; // dependent on operation
	// 	lazy[ind] = 0; 
	// } 
    
    // // recalc values for current node
	// void pull(int ind) { 
    //     seg[ind] = comb(seg[2*ind],seg[2*ind+1]); 
    // }

	// void build() { 
    //     for(int i = MAXN - 1; i >= 1; i--) {
    //         pull(i);
    //     }
    // }

	// void upd(int lo, int hi, int inc, int ind=1, int L = 0, int R = MAXN-1) {
	// 	push(ind,L,R); 
        
    //     if (hi < L || R < lo) return;

	// 	if (lo <= L && R <= hi) { 
	// 		lazy[ind] = inc; push(ind,L,R); return; 
    //     }

	// 	int M = (L+R)/2; 
    //     upd(lo,hi,inc,2*ind,L,M); 
	// 	upd(lo,hi,inc,2*ind+1,M+1,R); 
    //     pull(ind);
	// }
};


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<array<ll,4>> events;
    for(int i = 0; i < n; i++) {
        ll x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
        x1 += 1e6;
        y1 += 1e6;
        x2 += 1e6;
        y2 += 1e6;
        y2--;
        events.push_back({x1,1,y1,y2});
        events.push_back({x2,-1,y1,y2});
    }
    sort(events.begin(),events.end());
    LazySeg lazy;
    // lazy.build();
    // ll ans = 0;
    // ll prev = 0;
    // for(int i = 0; i < events.size(); i++) {
    //     ans += (events[i][0] - prev) * lazy.seg[1].second;
    //     prev = events[i][0];
    //     lazy.upd(events[i][2], events[i][3], events[i][1]);
    //     // ans += query() * (events[i][0] - prev);
    //     // prev = events[i][0];
    //     // update(events[i][2],events[i][3],events[i][1]);
    // }

    // cout << ans << '\n';

    return 0;
}