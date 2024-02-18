#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

map<int, int> find_seg(vector<bool>& a, int max_miss, int l, int r) {
    vector<bool> good(r - l - 3, false);
    for(int i = l; i < r - 3; i++){
        int cnt = a[i] + a[i + 1] + a[i + 2] + a[i + 3];
        good[i - l] = 4 - cnt <= max_miss;
    }
    vector<pair<int, int>> seg(0);
    for(int i = 0; i < good.size();){
        if(!good[i]) {
            i ++;
            continue;
        }
        int rptr = i;
        while(rptr != good.size() && good[rptr]) {
            rptr ++;
        }
        seg.push_back({i, rptr + 4});
        i = rptr + 1;
    }
    for(int i = 0; i < seg.size(); i++){
        seg[i].first += l;
        seg[i].second += l;
    }
    map<int, int> ans;
    for(int i = 0; i < seg.size(); i++){
        ans.insert({seg[i].first, seg[i].second});
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;  //10^5
    cin >> n;
    string line;
    cin >> line;
    vector<bool> a(n);
    for(int i = 0; i < n; i++){
        a[i] = line[i] == 'b';
    }
    for(int i = 0; i < 3; i++){
        // cout << "NOW ONTO " << i << endl;
        map<int, int> seg = find_seg(a, i, 0, n);
        int max_moves = 0;
        set<int> breaks, g_breaks, n_breaks;
        for(auto j = seg.begin(); j != seg.end(); j++){
            int l = j -> first;
            int r = j -> second;
            int len = r - l;
            max_moves += len / 4;
            if(len / 4 == 2 && len != 11){
                breaks.insert(l);
            }
            else if(len / 4 >= 2){
                g_breaks.insert(l);
            }
            else {
                n_breaks.insert(l);
            }
        }
        while(seg.size() != 0){
            // for(int j = 0; j < n; j++){
            //     cout << a[j] << " \n"[j == n - 1];
            // }
            int g_move;
            cin >> g_move;
            g_move --;
            {
                auto ptr = seg.upper_bound(g_move);
                ptr --;
                int l = ptr -> first;
                int r = ptr -> second;
                int len = r - l;
                max_moves -= len / 4;
                if(len / 4 == 2 && len != 11){
                    breaks.erase(l);
                }
                else if(len / 4 >= 2){
                    g_breaks.erase(l);
                }
                else {
                    n_breaks.erase(l);
                }
                for(int j = 0; j < 4; j++){
                    a[g_move + j] = false;
                }
                seg.erase(l);
                map<int, int> n_seg = find_seg(a, i, l, r);
                for(auto j = n_seg.begin(); j != n_seg.end(); j++){
                    int nl = j -> first;
                    int nr = j -> second;
                    int nlen = nr - nl;
                    max_moves += nlen / 4;
                    if(nlen / 4 == 2 && len != 11){
                        breaks.insert(nl);
                    }
                    else if(nlen / 4 >= 2){
                        g_breaks.insert(nl);
                    }
                    else {
                        n_breaks.insert(nl);
                    }
                    seg.insert({nl, nr});
                }
            }
            //ok, what move are we going to make?
            {   
                int l, r, move;
                //if there still exists a g_break, create a new break
                if(g_breaks.size() != 0){
                    l = *g_breaks.begin();
                    r = seg[l];
                    move = l + 8;
                }
                //if the amount of breaks > 2
                else if(breaks.size() > 2){
                    //idc about parity
                    l = *breaks.begin();
                    r = seg[l];
                    move = l;
                }
                //if there is only 1 break left, fix the parity
                else if(breaks.size() == 1){
                    l = *breaks.begin();
                    r = seg[l];
                    if(max_moves % 2 == 0){
                        //create extra move
                        move = l;
                    }
                    else {
                        //erase extra move
                        move = l + 3;
                    }
                }
                //otherwise, just take a non-break
                else {
                    l = *n_breaks.begin();
                    r = seg[l];
                    move = l;
                }
                cout << move + 1 << endl;
                int len = r - l;
                max_moves -= len / 4;
                if(len / 4 == 2 && len != 11){
                    breaks.erase(l);
                }
                else if(len / 4 >= 2){
                    g_breaks.erase(l);
                }
                else {
                    n_breaks.erase(l);
                }
                for(int j = 0; j < 4; j++){
                    a[move + j] = false;
                }
                seg.erase(l);
                map<int, int> n_seg = find_seg(a, i, l, r);
                for(auto j = n_seg.begin(); j != n_seg.end(); j++){
                    int nl = j -> first;
                    int nr = j -> second;
                    int nlen = nr - nl;
                    max_moves += nlen / 4;
                    if(nlen / 4 == 2 && len != 11){
                        breaks.insert(nl);
                    }
                    else if(nlen / 4 >= 2){
                        g_breaks.insert(nl);
                    }
                    else {
                        n_breaks.insert(nl);
                    }
                    seg.insert({nl, nr});
                }
            }
        }
    }
    //just ones remaining
    set<int> berries;
    for(int i = 0; i < n; i++){
        if(a[i]){
            berries.insert(i);
        }
    }
    while(berries.size() != 0){
        int g_move;
        cin >> g_move;
        g_move --;
        for(int i = 0; i < 4; i++){
            if(a[g_move + i] == true){
                a[g_move + i] = false;
                berries.erase(g_move + i);
            }
        }
        int move = *berries.begin();
        berries.erase(move);
        cout << move + 1 << endl;
    }

    return 0;
}