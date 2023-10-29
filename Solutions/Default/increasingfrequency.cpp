// https://codeforces.com/problemset/problem/1082/E
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const int N = 5e5;

int arr[N];
vector<int> poss[N+1];
int pref[N+1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;
    pref[0] = 0;
    int kcnt = 0;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        poss[num].push_back(i);
        arr[i] = num;
        pref[i+1] = pref[i];
        if(num == k) {
            pref[i+1]++;
            kcnt++;
        }
    }
    int bestval = 0;
    for(int i = 1; i <= N; i++) {
        int previdx = 0;
        int currval = 0;
        if(i == k) continue;
        for(auto x : poss[i]) {
            currval -= pref[x+1] - pref[previdx];
            currval = max(0,currval);
            currval++;
            bestval = max(bestval, currval);
            previdx = x;
        }
    }
    cout << bestval + kcnt << '\n';

    return 0;
}