#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    freopen("shuffle.in","r",stdin);
    freopen("shuffle.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int B;
    cin >> B;
    const int N = B;
    vector<int> order{};
    vector<string> names(N);
    for(int i = 0; i < N; i++) {
        string in;
        cin >> in;
        order.push_back(stoi(in) - 1);
    }
    vector<int> better (N);
    for(int i = 0; i < N; i++) {
        better[i] = order[order[order[order[i]]]];
    }
    for(int i = 0; i < N; i++) {
        string in;
        cin >> in;
        names[order[i]] = in;
    }
    for(int i = 0; i < N; i++) {

        cout << names[better[i]] << "\n";

    }
    return 0;
}