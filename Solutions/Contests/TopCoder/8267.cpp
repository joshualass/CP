#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
class DateFieldCorrection {
public:
    string correctDate(string input) {
        vector<string> keyboard = {
            "1234567890",
            "qwertyuiop",
            "asdfghjkl",
            "zxcvbnm",
        };
        map<char, vector<pair<char,int>>> adj;

        auto addEdge = [&](char a, char b, int w) -> void {
            adj[a].push_back({b,w});
            adj[b].push_back({a,w});
        };
        
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < keyboard[i].size(); j++) {
                char a = keyboard[i][j];
                if(j != keyboard[i].size() - 1) {
                    char b = keyboard[i][j+1];
                    addEdge(a,b,1);
                }
                if(i == 3) {
                    if(j >= 1 && j <= 6) {
                        char b = ' ';
                        addEdge(a,b,3);
                    }
                } else {
                    if(keyboard[i+1].size() > j) {
                        char b = keyboard[i+1][j];
                        addEdge(a,b,1);
                    }
                    if(j && keyboard[i+1].size() > j - 1) {
                        char b = keyboard[i+1][j-1];
                        addEdge(a,b,1);
                    }
                }
            }
        }

        map<char,map<char,int>> dists;

        for(auto [c, edges] : adj) {
            priority_queue<pair<int,char>, vector<pair<int,char>>, greater<pair<int,char>>> pq;
            pq.push({0,c});
            while(pq.size()) {
                auto [d,ch] = pq.top();
                pq.pop();
                if(dists[c].count(ch)) continue;
                dists[c][ch] = d;
                for(auto [nei, w] : adj[ch]) {
                    pq.push({d+w,nei});
                }
            }
        }

        vector<string> months = {
            "January", 
            "February", 
            "March",
            "April", 
            "May", 
            "June", 
            "July", 
            "August", 
            "September", 
            "October", 
            "November", 
            "December"
        };

        vector<int> days = {
            31,
            29,
            31,
            30,
            31,
            30,
            31,
            31,
            30,
            31,
            30,
            31
        };

        auto tolower = [](string s) -> string {
            for(int i = 0; i < s.size(); i++) {
                if(s[i] >= 'A' && s[i] <= 'Z') {
                    s[i] = s[i] - 'A' + 'a';
                }
            }
            return s;
        };

        int res = INT_MAX;
        string best = "";

        input = tolower(input);
        for(int i = 0; i < 12; i++) {
            for(int j = 1; j <= days[i]; j++) {
                string test = tolower(months[i] + " " + to_string(j));
                if(test.size() == input.size()) {
                    int cnt = 0;
                    for(int k = 0; k < input.size(); k++) {
                        cnt += dists[input[k]][test[k]];
                    }
                    if(cnt < res) {
                        res = cnt;
                        best = test;
                    }
                }
            }
        }
        best[0] = best[0] - 'a' + 'A';
        return best;
    }
};
// SOLUTION_END

int main() {
  string arg0;
  getline(cin, arg0);
  auto c = DateFieldCorrection();
  string ret = c.correctDate(arg0);
  cout << ret;
}