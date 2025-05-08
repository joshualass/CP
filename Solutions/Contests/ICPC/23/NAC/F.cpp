#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = 0; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    vector<pii> a(4);
    for (auto& p : a) {
        cin >> p.first >> p.second;
    }

    int area = 0;
    for (auto p : a)
        area += p.first * p.second;

    int sq = sqrt(area);

    if (sq * sq != area) {
        cout << 0 << endl;
        return 0;
    }

    bool works = false;

    auto case1 = [&](vector<pii> b) -> void {
        if (b[3].first == sq - b[0].first) {
            // cerr << "HEY" << endl;
            bool h = (b[1].second + b[3].second == sq) && (b[1].second == b[2].second);
            bool w = (b[1].first + b[2].first) == b[3].first;
            if (h && w)
                works = true;

            bool h2 = (b[1].second + b[2].second + b[3].second == sq);
            bool w2 = (b[1].first == b[3].first) && (b[1].first == b[2].first);

            if (h2 && w2)
                works = true;
        } else if (b[3].second == sq) {
            // cerr << "HEY!" << endl;
            bool h = (b[1].second + b[2].second) == sq;
            bool w = (b[0].first + b[1].first + b[3].first == sq) && (b[1].first == b[2].first);

            bool h2 = (b[1].second == sq) && (b[2].second == sq);
            bool w2 = (b[1].first + b[2].first + b[0].first + b[3].first == sq);
            if (h && w)
                works = true;
            if (h2 && w2)
                works = true;
        }
    };

    auto check = [&](vector<pii> b) -> void {
        // cerr << "TRY.\n";
        // for (auto p : b)
        //     cerr << p.first << " " << p.second << endl;
        // cerr << endl;
        
        // panes are w*h
        if (b[0].second == sq) {
            case1(b);
        } else if (b[3].second == sq)
            return;
        else {
            bool wa = (b[0].first + b[3].first) == sq;
            bool ha = (b[0].second + b[3].second) == sq;

            if (wa || ha) {
                bool two = ((b[0].first + b[1].first) == sq) && ((b[1].second + b[3].second) == sq);
                bool three = ((b[3].first + b[2].first) == sq) && ((b[2].second + b[0].second) == sq);
                if (two && three)
                    works = true;
            }
        }
        
    };

    sort(a.begin(), a.end());

    do {

        for (int i = 0; i < 16; ++i) {
            vector<pii> b = a;

            for (int j = 0; j < 4; ++j) {
                if (i & (1 << j)) {
                    swap(b[j].first, b[j].second);
                }
            }
            check(b);
        }
        
    } while (next_permutation(a.begin(), a.end()));


    cout << works << endl;

    return 0;
}