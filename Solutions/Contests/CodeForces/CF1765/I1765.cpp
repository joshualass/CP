#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

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
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}



set<pii>::iterator addInterval(set<pii>& is, int L, int R) {
	if (L == R) return is.end();
	auto it = is.lower_bound({L, R}), before = it;
	while (it != is.end() && it->first <= R) {
		R = max(R, it->second);
		before = it = is.erase(it);
	}
	if (it != is.begin() && (--it)->second >= L) {
		L = min(L, it->first);
		R = max(R, it->second);
		is.erase(it);
	}
	return is.insert(before, {L,R});
}

void removeInterval(set<pii>& is, int L, int R) {
	if (L == R) return;
	auto it = addInterval(is, L, R);
	auto r2 = it->second;
	if (it->first == L) is.erase(it);
	else (int&)it->second = L;
	if (R != r2) is.emplace(R, r2);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int xs, ys, xt, yt; cin >> xs >> ys >> xt >> yt;
    int n; cin >> n;

    vector<pair<char,array<int,2>>> a(n);
    set<array<int,2>> s;
    set<array<int,2>> bad;
    vector<set<pii>> bad_rows(8);

    vector<set<int>> row_pieces(8);
    for(int i = 0; i < 8; i++) {
        row_pieces[i].insert(1e9);
        row_pieces[i].insert(-1e9);
    }

    for(int i = 0; i < n; i++) {
        cin >> a[i].first;
        for(auto &x : a[i].second) cin >> x;
        s.insert(a[i].second);
        row_pieces[a[i].second[1] - 1].insert(a[i].second[0]);
        bad.insert(a[i].second);
    }

    vector<int> kx = {1, 2, 2, 1, -1, -2, -2, -1};
    vector<int> ky = {2, 1, -1, -2, -2, -1, 1, 2};

    auto cover_knight = [&](array<int,2> coord) -> void {
        int x = coord[0], y = coord[1];
        for(int i = 0; i < 8; i++) {
            int nx = x + kx[i];
            int ny = y + ky[i];
            bad.insert({nx, ny});
        }
    };

    vector<int> dx = {1, 0, -1, 0};
    vector<int> dy = {0, 1, 0, -1};

    auto cover_rook = [&](array<int,2> coord) -> void {
        int x = coord[0], y = coord[1];
        for(int dir = 0; dir < 4; dir++) {
            for(int i = 1; i <= 8; i++) {
                int nx = x + dx[dir] * i;
                int ny = y + dy[dir] * i;
                if(s.count({nx, ny})) break;
                bad.insert({nx, ny});
            }
        }

        int nx = *row_pieces[coord[1] - 1].upper_bound(coord[0]);
        addInterval(bad_rows[coord[1] - 1], coord[0], nx);
        int prev = *--row_pieces[coord[1] - 1].lower_bound(coord[0]);
        addInterval(bad_rows[coord[1] - 1], prev + 1, coord[0]);
    };

    vector<int> bx = {1, 1, -1, -1};
    vector<int> by = {1, -1, 1, -1};

    auto cover_bishop = [&](array<int,2> coord) -> void {
        int x = coord[0], y = coord[1];
        for(int dir = 0; dir < 4; dir++) {
            for(int i = 1; i <= 8; i++) {
                int nx = x + bx[dir] * i;
                int ny = y + by[dir] * i;
                if(s.count({nx, ny})) break;
                bad.insert({nx, ny});
            }
        }
    };

    auto cover_king = [&](array<int,2> coord) -> void {
        int x = coord[0], y = coord[1];

        for(int dir = 0; dir < 4; dir++) {
            for(int i = 1; i <= 1; i++) {
                int nx = x + dx[dir] * i;
                int ny = y + dy[dir] * i;
                if(s.count({nx, ny})) break;
                bad.insert({nx, ny});
            }
        }

        for(int dir = 0; dir < 4; dir++) {
            for(int i = 1; i <= 1; i++) {
                int nx = x + bx[dir] * i;
                int ny = y + by[dir] * i;
                if(s.count({nx, ny})) break;
                bad.insert({nx, ny});
            }
        }
    };

    for(auto [type, coord] : a) {
        if(type == 'K') {
            cover_king(coord);
        } else if(type == 'Q') {
            cover_bishop(coord);
            cover_rook(coord);
        } else if(type == 'R') {
            cover_rook(coord);
        } else if(type == 'B') {
            cover_bishop(coord);
        } else if(type == 'N') {
            cover_knight(coord);
        } else {
            cout << "type : " << type << endl;
            assert(0);
        }
    }

    set<int> rwb; //also the relevant rows

    auto abr = [&](int row) -> void {
        for(int i = -10; i <= 10; i++) rwb.insert(row + i);
    };

    for(auto [r, c] : bad) {
        abr(r);
    }

    abr(xt);
    abr(xs);

    // cout << "rwb : " << rwb << endl;

    map<array<int,2>, int> dis;
    set<array<int,2>> vis;
    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> pq;

    auto pushq = [&](array<int,2> coord, int d) -> void {
        if(rwb.count(coord[0]) && bad.count(coord) == 0 && (dis.count(coord) == 0 || d < dis[coord]) && coord[1] >= 1 && coord[1] <= 8) {
            auto it = bad_rows[coord[1] - 1].upper_bound({coord[0], 1000000000});
            if(it != bad_rows[coord[1] - 1].begin()) {
                it--;
                if((*it).second > coord[0]) return;
            }

            // cout << "pq nx : " << coord << " nx d : " << d << endl;
            dis[coord] = d;
            pq.push({d, coord[0], coord[1]});
        }
    };

    pushq({xs, ys}, 0);

    while(!pq.empty()) {
        auto [d, x, y] = pq.top();
        pq.pop();

        if(vis.count({x, y})) continue;
        vis.insert({x, y});

        // cout << "x : " << x << " y : " << y << " d : " << d << endl;

        //try standard king moves first
        for(int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            pushq({nx, ny}, d + 1);
        }

        for(int dir = 0; dir < 4; dir++) {
            int nx = x + bx[dir];
            int ny = y + by[dir];
            pushq({nx, ny}, d + 1);
        }

        //try teleporting up
        auto next = rwb.upper_bound(x);
        if(next != rwb.end() && *next > x + 1) {
            int nx = *next, ny = y;
            pushq({nx, ny}, d + max(abs(nx - x), abs(ny - y)));
        }

        //try teleporting down
        next = rwb.lower_bound(x);
        if(next != rwb.begin()) {
            next--;
            if(*next < x - 1) {
                int nx = *next, ny = y;
                pushq({nx, ny}, d + max(abs(nx - x), abs(ny - y)));
            }
        }
    }

    if(dis.count({xt, yt}) == 0) {
        dis[{xt, yt}] = -1;
    }

    cout << dis[{xt, yt}] << '\n';

    // for(int i = 0; i < 8; i++) {
    //     cout << "i : " << i << " br[i] : " << bad_rows[i] << endl;
    // }

    return 0;
}
