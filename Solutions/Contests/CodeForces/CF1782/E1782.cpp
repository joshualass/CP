#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void filterOverlaps(vector<array<int,3>> &singles, vector<array<int,3>> &doubles, vector<array<int,3>> &oppositesingle, vector<array<int,3>> &newdoubles) {

    sort(singles.begin(), singles.end());
    sort(doubles.begin(), doubles.end());
    newdoubles.clear();

    int up = 0, dp = 0;
    int maxup = -1;
    for(int i = 0; i < doubles.size(); i++) {
        while(up != singles.size() && singles[up][0] <= doubles[i][0]) {//while the leftendpoint of current single is <= current double block
            maxup = max(maxup, singles[up++][1]);
        }
        if(doubles[i][1] > maxup) { //we do not like doubles. right endpoint must be strictly greater
            newdoubles.push_back(doubles[i]);
        } else {
            oppositesingle.push_back(doubles[i]);
        }
    }

    swap(doubles, newdoubles);

}

void fillMerge(vector<array<int,3>> &doubles, vector<array<int,2>> &doublesegs, vector<array<int,4>> &res, int &area) {

    sort(doubles.begin(), doubles.end());
    for(array<int,3> d : doubles) {
        if(doublesegs.empty() || d[0] >= doublesegs.back()[1]) {//see if this area has no overlap
            int l = d[0], r = d[1], i = d[2];
            res[i] = {0, l, 1, r};
            doublesegs.push_back({l, r});
            area += (r - l) * 2;
        } else if(doublesegs.back()[1] < d[1]) {//see if there is some overlap, but nonzero area
            int l = doublesegs.back()[1], r = d[1], i = d[2];
            res[i] = {0, l, 1, r};
            doublesegs.back()[1] = r;
            area += (r - l) * 2;
        }
    }

}

void fillFixed(vector<array<int,3>> &filler, vector<array<int,2>> &blockers, vector<array<int,4>> &res, int h, int &area) {

    sort(filler.begin(), filler.end());
    sort(blockers.begin(), blockers.end());

    int blp = -1, bhp = 0;
    int maxup = -1;
    for(int i = 0; i < filler.size(); i++) {
        while(blp + 1 != blockers.size() && blockers[blp + 1][0] <= filler[i][0]) {//if next lowerpoint is <= curr seg, adjust. 
            blp++;
        }
        while(bhp != blockers.size() && blockers[bhp][1] < filler[i][1]) {//if current upperpoint is < curr seg, adjust.
            bhp++;
        }

        int l = filler[i][0], r = filler[i][1];
        l = max(l, maxup);
        if(blp != -1) {
            l = max(l, blockers[blp][1]);
        }
        if(bhp != blockers.size()) {
            r = min(r, blockers[bhp][0]);
        }
        if(r > l) {
            res[filler[i][2]] = {h, l, h, r};
            maxup = r;
            area += r - l;
        }
    }

}

void solve() {
    int n; cin >> n;

    vector<array<int,3>> doubles;
    vector<array<int,3>> upper;
    vector<array<int,3>> lower;

    for(int i = 0; i < n; i++) {
        int u, l, d, r; cin >> u >> l >> d >> r;

        if(u == 1 && d == 1) {
            upper.push_back({l - 1, r, i});
        } else if(u == 1 && d == 2) {
            doubles.push_back({l - 1, r, i});
        } else {
            lower.push_back({l - 1, r, i});
        }
    }

    vector<array<int,3>> newdoubles;

    //first remove all doubles that have a complete overlap from upper
    filterOverlaps(upper, doubles, lower, newdoubles);
    //second remove all doubles that have a complete overlap from lower
    filterOverlaps(lower, doubles, upper, newdoubles);


    // cout << "upper : " << upper << '\n';
    // cout << "double : " << doubles << '\n';
    // cout << "lower : " << lower << '\n';

    int area = 0;
    vector<array<int,4>> res(n, {-1, -1, -1, 0});

    //third greedy the double rectangles
    vector<array<int,2>> doublesegs; //stores merged double segments
    fillMerge(doubles, doublesegs, res, area);

    //fourth, maximize upper segments around fixed double blocks
    fillFixed(upper, doublesegs, res, 0, area);

    //fourth, maximize lower segments around fixed double blocks
    fillFixed(lower, doublesegs, res, 1, area);

    cout << area << '\n';
    for(int i = 0; i < n; i++) {
        cout << res[i][0] + 1 << " " << res[i][1] + 1 << " " << res[i][2] + 1 << " " << res[i][3] << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// int getarea(vector<array<int,2>> &a) {
//     sort(a.begin(), a.end());

//     int prev = -1;
//     int cnt = 0;
//     int res = 0;

//     for(array<int,2> x : a) {
//         if(cnt) {
//             res += x[0] - prev;
//         }
//         cnt += x[1];
//         prev = x[0];
//     }

//     return res;

// }

// void solve() {
//     int n; cin >> n;
//     vector<vector<array<int,2>>> a(2);

//     for(int i = 0; i < n; i++) {
//         int u, l, d, r; cin >> u >> l >> d >> r;
//         a[u - 1].push_back({l - 1, 1});
//         a[u - 1].push_back({r, -1});
//         a[d - 1].push_back({l - 1, 1});
//         a[d - 1].push_back({r, -1});
//     }

//     int res = 0;
//     res += getarea(a[0]);
//     res += getarea(a[1]);

//     cout << res << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }