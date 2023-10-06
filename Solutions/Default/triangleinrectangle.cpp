//https://atcoder.jp/contests/abc292/tasks/abc292_f?lang=en
//binary search the sidelength of triangle, it is trivial to determine if a side length works given a rectangle width and height

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << p.first << " " << p.second << " ";
    return os;
}

bool calc_poss(ld side_length, int sideA, int sideB) {
    if(side_length <= sideA) return true;
    pair<ld,ld> one = {0,0};
    pair<ld,ld> two = {sqrt(side_length * side_length - sideA * sideA), sideA};
    pair<ld,ld> midpoint = {two.first / 2, two.second/2};
    // ld slope = (two.second) / (two.first);
    // ld slope_perp = -1 / slope;
    ld distance = sqrt(((ld) 3) / 4) * side_length; //failed bc sqrt was doing integer division and distance as always 0
    ld unit_x = two.first / side_length;
    ld unit_y = two.second / side_length;
    pair<ld,ld> three = {midpoint.first + distance * unit_y, midpoint.second + distance * -unit_x};
    // cout << "side_length: " << side_length << " one: " << one << " two: " << two << " three: " << three << "\n";
    // cout << "midpoint: " << midpoint << " distance: " << distance << " unitx: " << unit_x << " unity: " << unit_y << "\n";
    if(two.first > sideB || three.second < 0 || three.first > sideB) return false;

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(15);
    int a, b; cin >> a >> b;
    if(a > b) swap(a,b); //a <= b
    ld l = 1, r = 10000;
    while(r - l > 1e-12) {
        ld m = (l + r) / 2;
        bool poss = calc_poss(m, a, b);
        if(poss) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l << "\n";

    return 0;
}