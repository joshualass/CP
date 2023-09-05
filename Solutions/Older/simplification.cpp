#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct Point {
    ld x;
    ld y;
};

ld calcTriangleArea(Point a, Point b, Point c) {
    return abs((ld)0.5 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    

    return 0;
}