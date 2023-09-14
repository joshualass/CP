#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 5e5 + 1;

int cnts[N];
int prefix[N+1];

void solve() {
    int n; cin >> n;
    string str; cin >> str;
    fill(begin(cnts), begin(cnts) + n + 1, 0);
    //need the ratios instead of equivalence
    for(int i = 0; i < n; i++) {
        prefix[i+1] = prefix[i] + (str[i] == 'D');
    }

    //will this run in time??
    for(int i = 1; i <= min(N/2, n); i++) {
        int curr = prefix[i] - prefix[0]; //i think we are close to solution here
        for(int j = 2; j * i <= n; j++) {
            if(curr == prefix[i * j] - prefix[i * (j - 1)]) {
                cnts[i * j - 1]++;
            } else {
                break;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        cout << cnts[i] + 1 << " ";
    }
    cout << "\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //14

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}