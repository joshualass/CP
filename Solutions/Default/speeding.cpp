#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    freopen("speeding.in","r",stdin);
    freopen("speeding.out","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N, M;
    cin >> N >> M;

    array<int,100> difference {};
    int index {0};
    int high = INT_MIN;
    while(N-->0) {
        int length, limit;
        cin >> length >> limit;
        for(int i = 0; i < length; i++) {
            difference[i + index] = limit;
        }
        index += length;
    }
    index = 0;
    while(M-->0) {
        int length, speed;
        cin >> length >> speed;
        for(int i = 0; i < length; i++) {
            high = max(high, speed - difference[i+index]);
        }
        index += length;
    }
    if(high < 0) {
        high = 0;
    }
    cout << high << "\n";
    return 0;
}