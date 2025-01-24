#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

struct TrieNode {
    char c;
    bool end;
    map<char,int> m; //the children
};

vector<TrieNode> trie; //array that can add elements

void insert_to_trie(string str) {
    int current_trie_idx = 0;
    //want to add the strings in reverse
    for(int i = str.size() - 1; i >= 0; i--) {
        // TrieNode current_node = trie[current_trie_idx];
        char next_to_insert = str[i];
        //create child node if not present
        if(trie[current_trie_idx].m.count(next_to_insert) == 0) { //see if this child is not present
            trie.push_back(TrieNode());
            trie[current_trie_idx].m[next_to_insert] = trie.size() - 1;
        }
        //we always go down
        current_trie_idx = trie[current_trie_idx].m[next_to_insert];
        trie[current_trie_idx].c = next_to_insert;
    }
    trie[current_trie_idx].end = true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  

    //add the root node
    trie.push_back(TrieNode());

    string word; cin >> word;
    int word_size = word.size();
    int dict_size; cin >> dict_size;

    for(int i = 0; i < dict_size; i++) {
        string dictionary_word; cin >> dictionary_word;
        insert_to_trie(dictionary_word);
    }

    vector<long long> dp(word_size + 1);
    dp[0] = 1;

    for(int i = 1; i <= word_size; i++) {
        int current_trie_idx = 0;
        for(int j = i - 1; j >= 0; j--) {
            char next_char = word[j];
            //check if this next_char is in the trie
            if(trie[current_trie_idx].m.count(next_char) == 1) {
                current_trie_idx = trie[current_trie_idx].m[next_char];
                if(trie[current_trie_idx].end == true) {
                    dp[i] = (dp[i] + dp[j]) % MOD;
                }
            } else { //once this trienode has no children that match the next_char, there are no words in the dictionary that match
                break; //leave for loop
            }
        }
    }

    cout << dp[word_size] << '\n';

    //969356451

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     string word; cin >> word;
//     int length_of_word = word.size();

//     int n; cin >> n;
//     vector<string> dictionary(n);

//     for(int i = 0; i < n; i++) {
//         string str; cin >> str;
//         dictionary[i] = str;
//     }

//     vector<long long> dp(length_of_word + 1);
//     dp[0] = 1;

//     for(int i = 1; i <= length_of_word; i++) {
//         //iterate over our words in the dictionary and try to match the words in the dictionary 
//         //with the last characters of are string prefix up to length i
//         for(string dictionary_word : dictionary) {
//             int length_of_string = dictionary_word.size();
//             if(i >= length_of_string) { //ensure the string we compare is smaller than the current string
//                 string comp = word.substr(i - length_of_string, length_of_string);
//                 if(dictionary_word == comp) {
//                     // dp[i] += dp[i-length_of_string];
//                     dp[i] = (dp[i] + dp[i-length_of_string]) % MOD;
//                 }
//             }
//         }
//     }

//     cout << dp[length_of_word] << '\n';

//     return 0;
// }