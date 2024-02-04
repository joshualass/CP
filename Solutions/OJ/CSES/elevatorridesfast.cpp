#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,fma,bmi,bmi2")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
ll n, x, w[20];
 
int bound;
int ans = 20;
 
int k = 0; // how many elevator rides are currently being used.
ll s[21] = {0}; // s[j-1] the sum of weights of people in the j'th elevator ride.
void search(int i)
{
    if (k >= ans || ans == bound)
        return;
 
    if (i == n)
    {
        ans = min(ans, k);
        return;
    }
 
    // for each previous elevator ride, try adding i.
    for (int j = k - 1; j >= 0; j--)
    {
        if (s[j] + w[i] > x) continue;
 
        s[j] += w[i];
        search(i + 1);
        s[j] -= w[i];
 
        // if we found a solution <= k, then there is no point looking for any solutions >= k.
        if (k >= ans || ans == bound)
            return;
    }
 
    // add i to their own lonely elevator ride
    s[k++] += w[i];
    search(i + 1);
    s[--k] -= w[i];
}
 
int main()
{
    cin.tie(0)->sync_with_stdio(0);
 
    cin >> n >> x;
    int S = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> w[i];
        S += w[i];
    }
    sort(w, w + n, [] (int a, int b) {return a > b;});
 
    ll t = 0, c = 0;
    for (int i = n - 1; t + w[i] <= x && i >= 0; i--)
        t += w[i], c++;
 
    ll T = w[0], C = 1;
    for (int i = n - 1; T + w[i] <= x && i >= 0; i--)
        T += w[i], C++;
 
    bound = max((S + x - 1) / x, (n - C + c - 1) / c + 1); // find a lower bound.
    ans = n; // answer is at most n.
    search(0);
    cout << ans << '\n';
 
    return 0;
}