#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

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
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const int N = 2e5;
int dsu[N];
int sizes[N];

void dsubuild(int n) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    dsu[y] = x;
    sizes[x] += sizes[y];
}

vector<vector<double>> gen_rand_pts(int n, int d, double r) {
    uniform_real_distribution<double> uf(0, r);
    vector res(n, vector<double>(d));
    for(auto &x : res) for(auto &y : x) y = uf(rng);
    return res;
}

double dist(vector<double> a, vector<double> b) {
    double s = 0;
    assert(a.size() == b.size());
    for(int i = 0; i < a.size(); i++) s += (a[i]-b[i]) * (a[i]-b[i]);
    return sqrt(s);
}

vector<double> get_avg(vector<vector<double>> &pts, int l, int r) {
    vector<double> avg(pts[0].size());
    for(int i = l; i < r; i++) for(int j = 0; j < pts[0].size(); j++) avg[j] += pts[i][j];
    for(int i = 0; i < pts[0].size(); i++) avg[i] /= r - l;
    return avg;
}

int get_nearest_idx(vector<vector<double>> &pts, vector<double> pt) {
    int res = 0;
    for(int i = 1; i < pts.size(); i++) {
        if(dist(pts[i], pt) < dist(pts[res], pt)) res = i;
    }
    return res;
}

vector<int> k_means(vector<vector<double>> &pts, int ng) {
    vector<vector<double>> centroids(pts.begin(), pts.begin() + ng);
    for(int i = 0; i < ng; i++) centroids[i] = pts[i];

    int it = 0;
    vector<vector<double>> nx_avg(ng);
    vector<int> nx_cnts(ng);
    while(1) {
        nx_avg.assign(ng, vector<double>(pts[0].size()));
        nx_cnts.assign(ng, 0);
        for(auto pt : pts) {
            int closest_idx = get_nearest_idx(centroids, pt);
            for(int i = 0; i < pts[0].size(); i++) nx_avg[closest_idx][i] += pt[i];
            nx_cnts[closest_idx]++;
        }
        for(int i = 0; i < ng; i++) for(int j = 0; j < pts[0].size(); j++) if(nx_cnts[i]) nx_avg[i][j] /= nx_cnts[i];
        int ok = 1;
        for(int i = 0; i < ng; i++) {
            for(int j = 0; j < pts[0].size(); j++) {
                if(abs(centroids[i][j] - nx_avg[i][j]) > 1e-4) ok = 0;
            }
        }
        centroids = nx_avg;
        if(ok || it++ >= 1000000) break;
    }
    vector<vector<vector<double>>> nx(ng);
    for(auto pt : pts) {
        nx[get_nearest_idx(centroids, pt)].push_back(pt);
    }
    vector<vector<double>> res_pts;
    vector<int> part;
    int p = 0;
    for(auto nx_part : nx) {
        for(auto pt : nx_part) res_pts.push_back(pt);
        p += nx_part.size();
        part.push_back(p);
    }
    pts = res_pts;
    return part;
}

//recursively chop the dataset into two partitions until each partition has size no larger than sqrt(n)
void _bi_means(vector<vector<double>> &pts, vector<int> &parts, int l, int r) {
    if(r - l <= sqrt(pts.size())) {
        parts.push_back(r);
        return;
    }

    vector<double> avg = get_avg(pts, l, r);
    // cout << "avg : " << avg << '\n';
    //find nearest point to average
    int o = l;
    for(int i = l + 1; i < r; i++) {
        if(dist(avg, pts[i]) < dist(avg, pts[o])) o = i;
    }
    // cout << "o : " << pts[o] << '\n';
    //find farthest point from o
    int p = l;
    for(int i = l + 1; i < r; i++) {
        if(dist(pts[i], pts[o]) > dist(pts[o], pts[p])) p = i;
    }
    // cout << "p : " << pts[p] << '\n';
    //find farthest point from q
    int q = l;
    for(int i = l + 1; i < r; i++) {
        if(dist(pts[i], pts[p]) > dist(pts[q], pts[p])) q = i;
    }
    // cout << "q : " << pts[q] << '\n';
    vector<double> pp = pts[p], qq = pts[q];
    //chop into two groups depending on if point i is closer to p or q
    int hi = r - 1;
    int lo = l;
    for(; lo <= hi;) {
        if(dist(pts[lo],pp) < dist(pts[lo],qq)) { //closer to p which is lo
            // cout << "pt : " << pts[lo] << " is closer to p than q\n";
            lo++;
        } else {
            // cout << "pt : " << pts[lo] << " is closer to q than p\n";
            swap(pts[lo], pts[hi--]);
        }
    }
    // for(; lo <= hi; lo++) {
    //     while(lo <= hi && dist(pts[lo],pts[p]) < dist(pts[lo],pts[q])) {
    //         cout << "pt : " << pts[lo] << " is closer to p than q\n";
    //         swap(pts[lo],pts[hi--]);
    //     }
    //     if(lo <= hi) cout << "pt : " << pts[lo] << " is closer to q than p\n";
    // }
    _bi_means(pts, parts, l, lo);
    _bi_means(pts, parts, lo, r);
}

vector<int> bi_means(vector<vector<double>> &pts) {
    vector<int> parts;
    _bi_means(pts, parts, 0, pts.size());
    return parts;
}

vector<vector<double>> get_centers(vector<vector<double>> &pts, vector<int> &part) {
    int prev = 0;
    vector<vector<double>> centers;
    for(int x : part) {
        vector<double> avg = get_avg(pts, prev, x);
        centers.push_back(avg);
        prev = x;
    }
    return centers;
}

//adds an edge between all pairs of nodes on the interval [l, r)
void add_complete_edges(vector<vector<double>> &pts, vector<vector<pair<int,double>>> &adj, int l, int r) {
    for(int i = l; i < r; i++) {
        for(int j = i + 1; j < r; j++) {
            adj[i].push_back({j, dist(pts[i],pts[j])});
            adj[j].push_back({i, dist(pts[i],pts[j])});
        }
    }
}

pair<double, vector<vector<int>>> MST_Kruskal(vector<vector<pair<int,double>>> &adj) {
    int n = adj.size();
    // cout << "kruskal adj\n";
    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " adj[i] : " << adj[i] << '\n';
    // }
    vector<pair<double, array<int,2>>> edges;
    for(int i = 0; i < n; i++) {
        for(auto edge : adj[i]) {
            edges.push_back({edge.second, {i, edge.first}});
        }
    }
    sort(edges.begin(), edges.end());
    dsubuild(n);
    double res = 0;
    vector<vector<int>> mst_adj(n);
    for(auto edge : edges) {
        auto [w, p] = edge;
        auto [i, j] = p;
        if(find(i) != find(j)) {
            merge(i,j);
            mst_adj[i].push_back(j);
            mst_adj[j].push_back(i);
            res += w;
        }
    }
    return {res, mst_adj};
}

pair<double, vector<set<int>>> MST_Kruskal_Max(vector<vector<pair<int,double>>> &adj) {
    vector<pair<double, array<int,2>>> edges;
    int n = adj.size();
    for(int i = 0; i < n; i++) {
        for(auto edge : adj[i]) {
            edges.push_back({edge.second, {i, edge.first}});
        }
    }
    sort(edges.begin(), edges.end());
    dsubuild(n);
    double res = 0;
    vector<set<int>> mst_adj(n);
    for(auto edge : edges) {
        auto [w, p] = edge;
        auto [i, j] = p;
        if(find(i) != find(j)) {
            merge(i,j);
            mst_adj[i].insert(j);
            mst_adj[j].insert(i);
            res = max(res, w);
        }
    }
    return {res, mst_adj};
}

pair<double, vector<vector<int>>> MST_Prim(vector<vector<pair<int,double>>> &adj) {
    int n = adj.size();
    // cout << "prim adj\n";
    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " adj[i] : " << adj[i] << '\n';
    // }

    vector<bool> vis(n);
    priority_queue<pair<double, array<int,2>>, vector<pair<double, array<int,2>>>, greater<pair<double, array<int,2>>>> pq;
    auto add = [&](int x) {
        vis[x] = 1;
        for(auto edge : adj[x]) if(vis[edge.first] == 0) pq.push({edge.second, {edge.first, x}});
    };
    add(0);

    double res = 0;
    vector<vector<int>> mst_adj(n);
    while(pq.size()) {
        auto [w, info] = pq.top();
        auto [i, j] = info;
        pq.pop();
        if(vis[i]) continue;
        // cout << "vis i : " << i << '\n';
        res += w;
        mst_adj[i].push_back(j);
        mst_adj[j].push_back(i);
        add(i);
    }
    return {res, mst_adj};
}

//Partition Nearest Neighbor Graph Algorithm
vector<vector<pair<int,double>>> PNNG(vector<vector<double>> &pts, vector<int> &part) {
    // cout << "pts : " << pts << " part : " << part << '\n';
    int n = pts.size();
    auto centers = get_centers(pts, part);
    vector<vector<pair<int,double>>> T_adj(part.size());
    add_complete_edges(centers, T_adj, 0, part.size());
    auto [T_max, T_mst] = MST_Kruskal_Max(T_adj);

    vector<vector<pair<int,double>>> adj(n);
    for(int i = 0; i < part.size(); i++) {
        int l = i ? part[i-1] : 0;
        add_complete_edges(pts, adj, l, part[i]);
        for(int j = i + 1; j < part.size(); j++) {
            for(int k = l; k < part[i]; k++) {
                for(int m = part[j-1]; m < part[j]; m++) {
                    if(T_mst[i].count(j)) { //add all interpartition edges if they are neighboring partitions; this ensures things are connected. 
                        adj[k].push_back({m, dist(pts[k], pts[m])});
                        adj[m].push_back({k, dist(pts[k], pts[m])});
                    } else {
                        if(dist(centers[i], centers[j]) <= T_max) {
                            double dii = dist(centers[i], pts[k]);
                            double dij = dist(centers[j], pts[k]);
                            double dji = dist(centers[i], pts[j]);
                            double djj = dist(centers[j], pts[j]);
                            if(dij <= dii * 2 || dji <= djj * 2) {
                                adj[k].push_back({m, dist(pts[k], pts[m])});
                                adj[m].push_back({k, dist(pts[k], pts[m])});
                            }
                        }
                    }
                }
            }
        }
    }
    return adj;
}

vector<vector<pair<int,double>>> BNNG_to_LNG(vector<vector<double>> &pts) {
    auto part = bi_means(pts);
    return PNNG(pts, part);
}

vector<vector<pair<int,double>>> KNNG_to_LNG(vector<vector<double>> &pts) {
    // cout << "pts ? : " << pts << '\n';
    // auto start = std::chrono::high_resolution_clock::now();
    auto part = k_means(pts, sqrt(pts.size()));
    // auto end = std::chrono::high_resolution_clock::now();

    // cout << "k_means times : " << std::chrono::duration<double, std::milli>(end - start).count() << '\n';
    
    return PNNG(pts, part);
}

void update_ec(vector<vector<pair<int,double>>> &adj, int &ec) {
    for(int i = 0; i < adj.size(); i++) ec += adj[i].size();
    ec /= 2;
}

pair<double, vector<vector<int>>> BNNG_Kruskal(vector<vector<double>> &pts, int &ec) {
    // cout << "start BNNG_Kruskal\n";
    auto adj = BNNG_to_LNG(pts);
    update_ec(adj, ec);
    auto [res, mst] = MST_Kruskal(adj);
    return {res, mst};
}

pair<double, vector<vector<int>>> BNNG_Prim(vector<vector<double>> &pts, int &ec) {
    auto adj = BNNG_to_LNG(pts);
    update_ec(adj, ec);
    auto [res, mst] = MST_Prim(adj);
    return {res, mst};
}

pair<double, vector<vector<int>>> KNNG_Kruskal(vector<vector<double>> &pts, int &ec) {
    auto adj = KNNG_to_LNG(pts);
    update_ec(adj, ec);
    auto [res, mst] = MST_Kruskal(adj);
    return {res, mst};
}

pair<double, vector<vector<int>>> KNNG_Prim(vector<vector<double>> &pts, int &ec) {
    auto adj = KNNG_to_LNG(pts);
    update_ec(adj, ec);
    auto [res, mst] = MST_Prim(adj);
    return {res, mst};
}

void print_mst(vector<vector<double>> &pts, double res, vector<vector<int>> &mst, int n, int d) {
    cout << "res : " << res << '\n';
    for(int i = 0; i < n; i++) {
        cout << i << " - (";
        for(int j = 0; j < d; j++) {
            cout << pts[i][j];
            if(j != d - 1) cout << ",";
        }
        cout << ")\n";
    }
    cout << "edges\n";
    for(int i = 0; i < n; i++) {
        cout << i << " - ";
        for(int j = 0; j < mst[i].size(); j++) {
            cout << mst[i][j] << ",\n"[j == mst[i].size() - 1];
        }
    }
}

void pnice(vector<vector<double>> &pts, vector<int> &part) {
    cout << "pts = [\n";
    for(int i = 0; i < pts.size(); i++) {
        cout << "\t";
        for(int j = 0; j < 2; j++) {
            cout << pts[i][j] << ", ";
        }
        cout << '\n';
    }
    cout << "]\n";
    cout << "part = [0, ";
    for(int x : part) cout << x << ", ";
    cout << "]\n";
}

array<array<double,3>,5> test(vector<vector<double>> &_pts) {
    array<array<double,3>,5> res = {};

    //complete graph
    {
        auto pts = _pts;
        auto start = std::chrono::high_resolution_clock::now();
        vector<vector<pair<int,double>>> adj(pts.size());
        add_complete_edges(pts, adj, 0, pts.size());
        auto [complete_res, complete_adj] = MST_Prim(adj);
        auto end = std::chrono::high_resolution_clock::now();
        res[0][0] = complete_res;
        res[0][1] = std::chrono::duration<double, std::milli>(end - start).count();
        res[0][2] = 1LL * pts.size() * (pts.size() - 1) / 2;
    }

    //KNNG Kruskal
    {
        auto pts = _pts;
        auto start = std::chrono::high_resolution_clock::now();
        int ec = 0;
        auto [KNNG_Kruskal_res, KNNG_Kruskal_adj] = KNNG_Kruskal(pts, ec);
        auto end = std::chrono::high_resolution_clock::now();
        res[1][0] = KNNG_Kruskal_res;
        res[1][1] = std::chrono::duration<double, std::milli>(end - start).count();
        res[1][2] = ec;
    }

    //KNNG Prim
    {
        auto pts = _pts;
        auto start = std::chrono::high_resolution_clock::now();
        int ec = 0;
        auto [KNNG_Prim_res, KNNG_Prim_adj] = KNNG_Prim(pts, ec);
        auto end = std::chrono::high_resolution_clock::now();
        res[2][0] = KNNG_Prim_res;
        res[2][1] = std::chrono::duration<double, std::milli>(end - start).count();
        res[2][2] = ec;
    }

    //BNNG Kruskal
    {
        auto pts = _pts;
        auto start = std::chrono::high_resolution_clock::now();
        int ec = 0;
        auto [BNNG_Kruskal_res, BNNG_Kruskal_adj] = BNNG_Kruskal(pts, ec);
        auto end = std::chrono::high_resolution_clock::now();
        res[3][0] = BNNG_Kruskal_res;
        res[3][1] = std::chrono::duration<double, std::milli>(end - start).count();
        res[3][2] = ec;
    }

    //BNNG Prim
    {
        auto pts = _pts;
        auto start = std::chrono::high_resolution_clock::now();
        int ec = 0;
        auto [BNNG_Prim_res, BNNG_Prim_adj] = BNNG_Prim(pts, ec);
        auto end = std::chrono::high_resolution_clock::now();
        res[4][0] = BNNG_Prim_res;
        res[4][1] = std::chrono::duration<double, std::milli>(end - start).count();
        res[4][2] = ec;
    }

    return res;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int n = 3000, d = 2;
    // vector pts = gen_rand_pts(n, d, 10);

    // auto res = test(pts);
    // for(int i = 0; i < res.size(); i++) {
    //     cout << "i : " << i << " res[i] : " << res[i] << '\n';
    // }

    //FIRST TEST
    /*
    int n = 5000;

    cout << "Using n = " << n << " and trying several d\n";
    cout << "MST w, time taken, # edges of graph\n";

    for(int d = 2; d <= 256; d *= 2) {
        cout << "d : " << d << '\n';
        auto pts = gen_rand_pts(n, d, 10);
        auto res = test(pts);
        cout << "Complete Graph : " << res[0] << '\n';
        cout << "KNNG Kruskal : " << res[1] << '\n';
        cout << "KNNG Prim : " << res[2] << '\n';
        cout << "BNNG Kruskal : " << res[3] << '\n';
        cout << "BNNG Prim : " << res[4] << '\n';
    }
    */

    //SECOND TEST
    int d = 20;
    cout << "Using d = " << d << " and trying several n\n";
    cout << "MST w, time taken, # edges of graph\n";
    for(int n = 1000; n <= 10000; n += 1000) {
        cout << "n : " << n << '\n';
        auto pts = gen_rand_pts(n, d, 10);
        auto res = test(pts);
        cout << "Complete Graph : " << res[0] << '\n';
        cout << "KNNG Kruskal : " << res[1] << '\n';
        cout << "KNNG Prim : " << res[2] << '\n';
        cout << "BNNG Kruskal : " << res[3] << '\n';
        cout << "BNNG Prim : " << res[4] << '\n';
    }


    // cout << "res : " << res << '\n';
    // vector<vector<double>> pts = {
    //     {0.156284,8.23871},
    //     {7.82192,1.92364},
    //     {0.987821,1.6248},
    //     {3.76146,3.72461},
    //     {6.75499,0.976975},
    //     {9.4827,6.06199},
    //     {9.90717,6.11535},
    //     {6.51607,7.47325},
    //     {8.0892,8.20846},
    //     {8.12619,8.37216}
    // };

    // auto part = bi_means(pts);
    // cout << "pts : " << pts << '\n';
    // cout << "pnice\n";
    // pnice(pts, part);

    // auto [res_bnng_kruskal, mst_bnng_kruskal] = BNNG_Kruskal(pts);
    // cout << "res_bnng_kruskal : " << res_bnng_kruskal << '\n';
    // cout << "kruskal mst\n";
    // print_mst(pts, res_bnng_kruskal, mst_bnng_kruskal, n, d);

    // auto [res_bnng_prim, mst_bnng_prim] = BNNG_Prim(pts);
    // cout << "res_bnng_prim : " << res_bnng_prim << "\n";
    // cout << "prim mst\n";
    // print_mst(pts, res_bnng_prim, mst_bnng_prim, n, d);



    // vector<vector<pair<int,double>>> adj(n);
    // add_complete_edges(pts, adj, 0, n);
    // auto [res, mst] = MST_Kruskal(adj);
    // cout << "mst mst\n";
    // print_mst(pts, res, mst, n, d);

    // auto [res_pts, mst] = info;


    // for(int n = 1000; n <= 10000; n += 5000) {
        // for(int d = 2; d <= 128; d *= 2) {
        // int d = 2;
            // vector pts = gen_rand_pts(n, d, 1e9);
            // cout << "pts : " << pts << '\n';
            // cout << "n : " << n << '\n';
            // auto [res_bnng_kruskal, mst_bnng_kruskal] = BNNG_Kruskal(pts);
            

        // }
    // }



    return 0;
}
