#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
this doesn't work. had to read editorial. 
try to avoid comparing pokemon's, but rather focus on the attributes
before doing anything, for each of the n pokemon, insert their m attributes into a map

maintain that when we are inserting elements into the map, that element is done optimally, so any of the pokemon with higher of the attribute can be immediately added to the priority queue. 
for all the pokemon with a lower attribute 

new idea/easier to implement - for each attribute, have and maintain the minimum attribute encountered and its cost

*/

void solve() {
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}