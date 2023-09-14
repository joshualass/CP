#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int l = 1, r = n;
    while(l != r) {
        int length = r + 1 - l;
        int quarter = length / 4;
        int remainder = length % 4;
        int segments[4] = {quarter,quarter,quarter,quarter};
        for(int i = 0; remainder > 0; i++) {
            segments[i]++;
            --remainder;
        }
        int applejack_lower = l;
        int applejack_upper = l + segments[0] + segments[1] - 1;
        int applebloom_lower = l + segments[0];
        int applebloom_upper = l + segments[0] + segments[1]+ segments[2] - 1;

        cout << "Q " << applejack_lower << " " << applejack_upper << " " << applebloom_lower << " " << applebloom_upper << endl;
        int w1, w2; cin >> w1 >> w2;
        if(r - l <= 3) {
            if(w1 && w2) {
                l = l + segments[0];
                r = l;
            } else if(w1 && !w2) {
                r = l;
            } else if(!w1 && w2) {
                l = l + segments[0] + segments[1];
                r = l;
            } else {
                l = l + segments[0] + segments[1] + segments[2];
                r = l;
            }
        } else {
            if(w1 && !w2) {
                r = l + segments[0];
                --l;
                l = max(l,1);
            } else if(w1 && w2) {
                r = l + segments[0] + segments[1];
                l = l + segments[0] - 1;
            } else if(!w1 && w2) {
                r = l + segments[0] + segments[1] + segments[2];
                l = l + segments[0] + segments[1] - 1;
            } else {
                r = l + segments[0] + segments[1] + segments[2] + segments[3];
                r = min(r,n);
                l = l + segments[0] + segments[1] + segments[2] - 1;
            }
        }

    }
    cout << "A " << l << endl;
    return 0;
}