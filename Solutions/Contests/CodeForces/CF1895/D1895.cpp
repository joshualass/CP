#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int depth = 31;

struct TrieNode {
    int value;
    TrieNode *arr[2];
};

TrieNode *newNode() {
    TrieNode *temp = new TrieNode;
    temp->value = 0;
    temp->arr[0] = nullptr;
    temp->arr[1] = nullptr;
    return temp;
}

void insertNode(int num, TrieNode* root) {
    TrieNode* curr = root;
    for(int i = 0; i < depth; i++) {
        int idx = (num >> (depth - i - 1)) & 1;
        if(curr->arr[idx]) {
            curr = curr->arr[idx];
        } else {
            curr->arr[idx] = newNode();
            curr = curr->arr[idx];
        }
    }
    curr->value = num;
}

int findMax(int num, TrieNode* root) {
    int ans = 0;
    TrieNode* curr = root;
    for(int i = 0; i < depth; i++) {
        int idx = (num >> (depth - i - 1)) & 1;
        if(idx) {
            if(curr->arr[0] != nullptr) {
                ans += (1 << (depth - i - 1));
                curr = curr->arr[0];
            } else {
                curr = curr->arr[1];
            }
        } else {
            if(curr->arr[1] != nullptr) {
                ans += (1 << (depth - i - 1));
                curr = curr->arr[1];
            } else {
                curr = curr->arr[0];
            }
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    TrieNode* root = newNode();
    vector<int> a(n-1);

    int curr = 0;
    insertNode(0, root);
    for(int i = 0; i < n - 1; i++) {
        int num; cin >> num;
        curr ^= num;
        insertNode(curr, root);
        a[i] = num;
    }
    int start = -1;
    for(int i = 0; i < n; i++) {

        int most = findMax(i, root);
        // cout << "i: " << i << " max: " << most << '\n';
        if(most < n) {
            start = i;
            break;
        }

    }

    cout << start << " ";
    for(int i = 0; i < n - 1; i++) {
        start ^= a[i];
        cout << start << " ";
    }

    return 0;
}