// SET N TO THE SUM OF PATTERN SIZES
// MAKE SURE PATTERNS ARE UNIQUE (NO DUPLICATES)
namespace ACA {
    const int ALPHABET = 26;
    vector<int> endHere[N];
    int pi[N] = {-1};
    vector<vector<int>> trie(1, vector<int>(ALPHABET, -1));
 
    void insert(string &s, int idx) {
        int cur = 0;
        for (auto &i: s) {
            int rank = i - 'a';
            
            if (trie[cur][rank] == -1) {
                trie[cur][rank] = trie.size();
                pi[trie.size()] = -1;
                trie.push_back(vector<int>(ALPHABET, -1));
            }
 
            cur = trie[cur][rank];
        }
        endHere[cur].push_back(idx);
    }
 
    void build() {
        queue<int> q;
        
        for (int i = 0; i < ALPHABET; i++) {
            if (trie[0][i] != -1) {
                pi[trie[0][i]] = 0, q.push(trie[0][i]);
            }
            else {
                trie[0][i] = 0;
            }
        }
 
        
        while (q.size()) {
            int cur = q.front();
            q.pop();
 
            for (int i = 0; i < ALPHABET; i++) {
                if (trie[cur][i] == -1) {
                    continue;
                }
 
                int f = pi[cur];
                while (trie[f][i] == -1) {
                    f = pi[f];
                }
 
                f = trie[f][i];
                pi[trie[cur][i]] = f;
                endHere[trie[cur][i]].insert(endHere[trie[cur][i]].end(), endHere[f].begin(), endHere[f].end());
                q.push(trie[cur][i]);
            }
        }
    }
 
    void init(string patterns[], int n) {
        /*
         * MAKE SURE THAT THE STRINGS IN P ARE UNIQUE3
         * n is the number of patterns
         * m is the size of the alphabet
        */
 
        for (int i = 0; i < n; i++) {
            insert(patterns[i], i);
        }
 
        build();
    }
 
    int nextState(int trieNode, char nxt) {
        int rank = nxt - 'a', &ret = trie[trieNode][rank];
 
        if (~ret) {
            return ret;
        }
 
        int cur = trieNode;
 
        while (trie[cur][rank] == -1) {
            cur = pi[cur];
        }
 
        return ret = trie[cur][rank];
    }
 
    vector<vector<int>> search(string &s, string a[], int n) {
        vector<vector<int>> occ(n);
 
        int cur = 0;
 
        for (int i = 0; i < s.size(); i++) {
            cur = nextState(cur, s[i]);
 
            if (cur == 0 or endHere[cur].empty()) {
                continue;
            }
 
            for (auto &j: endHere[cur]) {
                occ[j].push_back(i - a[j].size() + 1);
            }
        }
 
        return occ;
    }
};
