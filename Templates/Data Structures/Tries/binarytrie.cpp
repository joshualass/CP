/*
binary trie which stores bits
useful for solving maximum xor problems
*/
const int depth = 64;

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
