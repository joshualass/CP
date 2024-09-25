// //TBD upload from laptop
// const int SIZE = 26;

// struct Trie {
//     struct Trie *arr[SIZE];
//     int words;
// };

// struct Trie* getNode() {
//     struct Trie* node = new Trie;
//     node->words = 0;
//     for(int i = 0; i < SIZE; i++) {
//         node->arr[i] = NULL;
//     }
//     return node;
// }

// void insert(struct Trie* root, string add) {
//     struct Trie* curr = root;
//     for(int i = 0; i < add.size(); i++) {
//         if(!curr->arr[add[i] - 'a']) {
//             curr->arr[add[i] - 'a'] = getNode();
//         }
//         curr = curr->arr[add[i] - 'a'];
//         curr->words++;
//     }
// }

// int previous(struct Trie* root, string word) {
//     struct Trie* curr = root;
//     for(int i = 0; i < word.size(); i++) {
//         if(!curr->arr[word[i] - 'a']) {
//             return 0;
//         }
//         curr = curr->arr[word[i] - 'a'];
//     }
//     return curr->words;
// }

const int SIZE = 26;

struct Trie {
    struct Trie* arr[SIZE];
    int cnt;
};

struct Trie* getNode() {
    struct Trie* node = new Trie;
    node->cnt = false;
    for(int i = 0; i < SIZE; i++) {
        node->arr[i] = NULL;
    }
    return node;
}

void insert(struct Trie* root, string add) {
    struct Trie* curr = root;
    for(int i = 0; i < add.size(); i++) {
        if(!curr->arr[add[i] - 'a']) {
            curr->arr[add[i] - 'a'] = getNode();
        }
        curr = curr->arr[add[i] - 'a'];
        curr->cnt++;
    }
    // curr->cnt++;
}

ll query(struct Trie* root, string str) {
    struct Trie* curr = root;
    ll score = 0;
    for(int i = 0; i < str.size(); i++) {
        if(curr != nullptr) {
            curr = curr->arr[str[i] - 'a'];
        }
        if(curr != nullptr) {
            score += curr->cnt;
        }
    }
    return score;
}