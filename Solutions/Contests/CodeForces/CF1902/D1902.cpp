#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    string str; cin >> str;

    map<pair<int,int>, set<int>> forward_positions;
    map<pair<int,int>, set<int>> reverse_positions;
    vector<pair<int,int>> forward_offsets;
    vector<pair<int,int>> reverse_offsets;

    forward_offsets.push_back({0,0});
    forward_positions[{0,0}] = {0};
    pair<int,int> curr_pos = {0,0};
    for(int i = 0; i < n; i++) {
        switch(str[i]) {
            case 'L' : curr_pos.first--; break;
            case 'U' : curr_pos.second++; break;
            case 'D' : curr_pos.second--; break;
            case 'R' : curr_pos.first++; break;
        }
        forward_offsets.push_back(curr_pos);
        if(forward_positions.find(curr_pos) == forward_positions.end()) {
            forward_positions[curr_pos] = {i+1};
        } else {
            forward_positions[curr_pos].insert(i+1);
        }
    }
    reverse(str.begin(), str.end());
    reverse_offsets.push_back({0,0});
    reverse_positions[{0,0}] = {0};
    curr_pos = {0,0};
    for(int i = 0; i < n; i++) {
        switch(str[i]) {
            case 'L' : curr_pos.first--; break;
            case 'U' : curr_pos.second++; break;
            case 'D' : curr_pos.second--; break;
            case 'R' : curr_pos.first++; break;
        }
        reverse_offsets.push_back(curr_pos);
        if(reverse_positions.find(curr_pos) == reverse_positions.end()) {
            reverse_positions[curr_pos] = {i+1};
        } else {
            reverse_positions[curr_pos].insert(i+1);
        }
    }    

    for(int i = 0; i < q; i++) {
        int x, y, l, r; cin >> x >> y >> l >> r;
        bool found = 0;
        pair<int,int> p = {x,y};
        //first try before the reverse string 
        //valid indexes are anything less than l
        if(forward_positions.find(p) != forward_positions.end()) {
            if((*forward_positions[p].begin()) < l) {
                // cout << "found 1 \n";
                found = 1;
            }
        }
        //second try after the reverse string
        //valid indexes are anything greater than or equal to r
        if(forward_positions.find(p) != forward_positions.end()) {
            if((*--forward_positions[p].end()) >= r) {
                // cout << "found 2 \n";
                found = 1;
            }
        }
        //third try if visited during the reverse string
        pair<int,int> curr_pos_before_reverse = forward_offsets[l-1];
        pair<int,int> reverse_start = reverse_offsets[n - r];     
        // pair<int,int> reverse_start = {0,0};             
        pair<int,int> starting_pos = {curr_pos_before_reverse.first - reverse_start.first, curr_pos_before_reverse.second - reverse_start.second};
        pair<int,int> upd_p = {p.first - starting_pos.first, p.second - starting_pos.second};
        // cout << "reverse l : " << l << " reverse r : " << r << " before_reverse : " << curr_pos_before_reverse << " rev start : " << reverse_start << " starting pos : " << starting_pos << " upd_p : " << upd_p << '\n';

        if(reverse_positions.find(upd_p) != reverse_positions.end()) {
            int lo = n - r;
            int hi = n - l;
            if(reverse_positions[upd_p].lower_bound(lo) != reverse_positions[upd_p].end() && (*reverse_positions[upd_p].lower_bound(lo)) <= hi) {
                // cout << "found 3\n";
                found = 1;
            }
        }
        cout << (found ? "YES" : "NO") << '\n';
    }

    return 0;
}