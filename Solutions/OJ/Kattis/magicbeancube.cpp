#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    array<string,3> a = {}; //o, g, r
    for(auto &x : a) cin >> x;

    vector<string> res;
    auto move = [&](int idx, int dist) -> void {
        for(int i = 1; i <= dist; i++) {
            if(idx <= 2) {
               rotate(a[idx].begin(), a[idx].begin() + 9, a[idx].end());
            } else {
                for(int j = 0; j < 3; j++) {
                    swap(a[0][j], a[2][j]);
                    swap(a[0][j], a[1][j]);
                }
            }
        }
        string c = "";
        if(idx == 0) {
            c = "o";
        } else if(idx == 1) {
            c = "g";
        } else if(idx == 2) {
            c = "r";
        } else {
            c = "c";
        }
        res.push_back(c + to_string(dist));
    };

    auto move_pos = [&](int wheel_idx, int s, int t) -> void {
        int dist = (t - s + 10) % 10;
        if(dist) move(wheel_idx, dist);
    };

    auto print = [&]() -> void {
        vector<string> wheels = {"o","g","r"};
        for(int i = 0; i < 3; i++) {
            cout << wheels[i] << " wheel ";
            cout << a[i] << '\n';
        }
    };

    for(int i = 1; i < 3; i++) {
        while(count(a[i].begin(), a[i].end(), 'o')) {
            // cout << "start op\n";
            // print();
            int st = 0;
            while(a[i][st] != 'o') st++;
            int ost = 0;
            while(a[0][ost] == 'o') ost++;
            // cout << "put non-o in first position o\n";
            move_pos(0, ost, 0);
            // print();
            // cout << "put o in fourth position of idx i : " << i << '\n';
            move_pos(i, st, 3);
            // print();
            move(3, 3 - i);
            move(i, 9);
            move(3, i);
            // cout << "end op\n";
            // print();
        }
    }

    // print();

    while(count(a[1].begin(), a[1].end(), 'r')) {
        int gst = 0;
        while(a[1][gst] != 'r') gst++;
        int rst = 0;
        while(a[2][rst] != 'g') rst++;
        move_pos(1, gst, 2);
        move_pos(2, rst, 9);
        move(3, 2);
        move(2, 1);
        move(3,1);
    }

    // print();

    cout << res.size() << '\n';
    for(auto x : res) cout << x << '\n';

    return 0;
}