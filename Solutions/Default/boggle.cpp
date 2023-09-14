#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

vector<pair<int,int>> directions = {{1,0}, {1,1}, {0,1}, {-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};

const int SIZE = 26;
vector<vector<char>> board(4,vector<char>(4));
int cnt;
ll score;
string best_word;
unordered_set<string> found;

string vToS(vector<char> &v) {
    string x{};
    for(char y : v) {
        x.push_back(y);
    }
    return x;
}

struct Trie {
    struct Trie* arr[SIZE];
    bool end;
};

struct Trie* getNode() {
    struct Trie* node = new Trie;
    node->end = false;
    for(int i = 0; i < SIZE; i++) {
        node->arr[i] = NULL;
    }
    return node;
}

void insert(struct Trie* root, string add) {
    struct Trie* curr = root;
    for(int i = 0; i < add.size(); i++) {
        if(!curr->arr[add[i] - 'A']) {
            curr->arr[add[i] - 'A'] = getNode();
        }
        curr = curr->arr[add[i] - 'A'];
    }
    curr->end = true;
}

void search(struct Trie* node, vector<char>& str, vector<vector<bool>>& visited, int R, int C) {
    if(str.size() == 8) {
        string word = vToS(str);
        if(found.find(word) == found.end()) {
            found.insert(word);
            // cout << "mo fluffer | " << word << "\n";
            cnt++;
            score += 11;
            if(str.size() > best_word.size()) {
                best_word = word;
            } else if(str.size() == best_word.size() && word.compare(best_word) < 0) {
                best_word = word;
            }
            return;
        }
    }
    if(node->end) {
        string word = vToS(str);
        if(found.find(word) == found.end()) {
            found.insert(word);
            // cout << "how? " << word << "\n";
            switch(str.size()) {
                case 3 :
                case 4 : score += 1; break;
                case 5 : score += 2; break;
                case 6 : score += 3; break;
                case 7 : score += 5; break;
            }
            cnt++;
            if(str.size() > best_word.size()) {
                best_word = word;
            } else if(str.size() == best_word.size() && word.compare(best_word) < 0) {
                best_word = word;
            }
        }
    }
    visited[R][C] = true;
    for(int i = 0; i < directions.size(); i++) {
        int r = directions[i].first + R;
        int c = directions[i].second + C;
        if(r < 0 || r > 3 || c < 0 || c > 3) {
            continue;
        }
        if(node->arr[board[r][c] - 'A'] && !visited[r][c]) {
            str.push_back(board[r][c]);
            search(node->arr[board[r][c] - 'A'], str, visited, r, c);
            str.pop_back();
        }
    }
    visited[R][C] = false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int w; cin >> w;
    Trie* root = getNode();
    for(int i = 0; i < w; i++) {
        string word; cin >> word;
        insert(root, word);
    }
    int b; cin >> b;
    while(b-->0) {
        vector<vector<bool>> visited(4,vector<bool>(4,false));
        cnt = 0; score = 0;
        best_word = "";
        for(int i = 0; i < 4; i++) {
            string word; cin >> word;
            for(int t = 0; t < 4; t++) {
                board[i][t] = word[t];
            }
        }
        vector<char> str(0);
        found = {};
        for(int i = 0; i < 4; i++) {
            for(int t = 0; t < 4; t++) {
                if(root->arr[board[i][t] - 'A']) {
                    str.push_back(board[i][t]);
                    visited[i][t] = true;
                    search(root->arr[board[i][t] - 'A'], str, visited, i, t);
                    str.pop_back();
                    visited[i][t] = false;
                }
            }
        }
        cout << score << " " << best_word << " " << cnt << "\n";
    }

    return 0;
}