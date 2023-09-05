#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

map<string, pair<ll, char>> table;

vector<map<char, ll>> merger(vector<map<char, ll>> parts, int size,
                             string line) {
    vector<map<char, ll>> result(0);
    for (int i = 0; i < parts.size() - 1; i++) {
        map<char, ll> temp;
        for (pair<char, ll> p : parts[i]) {
            string rec = string() + p.first + line[size - parts.size() + i + 1];
            ll time = p.second + table[rec].first;
//            cout << "rec: " << rec << '\n';
            char c = table[rec].second;
            if (temp.find(c) == temp.end()) {
//                cout << "inserting value1: " << c << " " << time << '\n';
                temp.insert({c, time});
            } else {
                temp[c] = min(temp[c], time);
            }
        }

        for (pair<char, ll> p : parts[i + 1]) {
            ll time = p.second + table[string() + line[i] + p.first].first;
            char c = table[string() + line[i] + p.first].second;
            if (temp.find(c) == temp.end()) {
//                cout << "inserting value2: " << c << " " << time << '\n';
                temp.insert({c, time});
            } else {
                temp[c] = min(temp[c], time);
            }
        }
        result.push_back(temp);
    }
    // cout << "result: " << '\n';
    // for (map<char, ll> p : result) {
    //     for (pair<char, ll> pp : p) {
    //         cout << "first: " << pp.first << " second: "
    //              << "p.second " << pp.second << '\n';
    //     }
    // }
    // cout << "MERGING new size - " << result.size() << '\n';

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k;
    cin >> k;
    vector<char> sequence(k);
    for (char &x : sequence) cin >> x;

    string order = "";
    for (char x : sequence) order += x;
    for (int r = 0; r < k; r++) {
        for (int c = 0; c < k; c++) {
            string line;
            cin >> line;
            table.insert({string() + sequence[r] + sequence[c],
                          {stoll(line.substr(0, line.size() - 2)),
                           line[line.size() - 1]}});
        }
    }

    // for(pair<string, pair<ll,char>> p : table) {
    //     cout << "string: " << p.first << " ll: " << p.second.first << " char: " << p.second.second << '\n';
    // }

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string line;
        cin >> line;
        if (line.size() == 1) {
            cout << "0-" << line[0] << '\n';
        } else {
            vector<map<char, ll>> parts(line.size() - 1);
            for (int t = 0; t < line.size() - 1;
                 t++) {  // do first operation already
                parts[t] = {{table[string() + line[t] + line[t + 1]].second, table[string() + line[t] + line[t + 1]].first}};
                // cout << "expr: " << table[string() + line[t] + line[t + 1]].second << " huh: " << table[string() + line[t] + line[t + 1]].first << '\n';
            }

            while (parts.size() != 1) {
                // cout << "starting position: " << '\n';
                // for (int i = 0; i < parts.size(); i++) {
                //     for (pair<char, ll> pp : parts[i]) {
                //         cout << "i: " << i << " first: " << pp.first
                //              << " second: " << pp.second << '\n';
                //     }
                // }
                // cout << '\n';
                parts = merger(parts, line.size(), line);
            }
            ll lowest = LLONG_MAX;
            ll index = -1;
            for (pair<char, ll> p : parts[0]) {
                // cout << "char: " << p.first << " time: " << p.second << '\n';
                if (p.second == lowest) {
                    index = min(index, (ll)order.find(p.first));
                }
                if (p.second < lowest) {
                    lowest = p.second;
                    index = (ll)order.find(p.first);
                }
            }

            cout << lowest << '-' << order[index] << '\n';
        }
    }
    int last;
    cin >> last;
    return 0;
}