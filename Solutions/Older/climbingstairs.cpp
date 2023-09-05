#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int step, r, office;
    cin >> step >> r >> office;
    int steps = 0;
    if (office > r) {
        steps = max(step, office + office - r);
        if (steps % 2 != r % 2) {
            steps++;
        }
        steps += r;
        cout << steps;
    } else {
        steps = max(r, step);
        if (steps % 2 != r % 2) {
            steps++;
        }
        steps += r;
        cout << steps;
    }

    return 0;
}