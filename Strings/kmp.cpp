/*
Classic problem: given a string t and a pattern p, find all occurrences of p in t

0 1 2 3 4 5 6 7 8 9
a b d a b c a b c a
         a b c a (index 3)
                  a b c a (index 6)

Brute: O(n * m)

KMP: O(n + m)

Prefix function: the length of the longest proper prefix which is also a suffix of a string

lps[N]: an array where lps[i] = the prefix function of substring(0, i)

Idx:	0 1 2 3 4 5 6 7 8 9
string: 	a b d a b c a b c a
lps: 	0 0 0 1 2 0 1 2 0 1

Idx:	0 1 2 3 4 5 6 7 8 9
string: 	a b c a b c a b c a
lps: 	0 0 0 1 2 3 4 5 6 7

lps[0] = 0 because there is no proper prefix of a string of 1 character

lps[i + 1] <= lps[i] + 1
*/

vector<int> prefixFunction(string &pattern) {
    int n = pattern.size();
    vector<int> lps(n);
    lps[0] = 0;
    
    for (int i = 1; i < n; i++) {
        lps[i] = 0;
        int j = lps[i - 1];

        while (j > 0 and pattern[j] != pattern[i]) {
            j = lps[j - 1];
        }

        if (pattern[j] == pattern[i]) {
            lps[i] = j + 1;
        }
    }

    return lps;
}

/*
Application 1 - pattern matching in a string:

Find places where pattern p occurs in string t

string s = p + ‘#’ + t

Get prefix function of s (lps[i] <= p.size() because of the separator)

If (lps[i] == p.size()) then we’ve found a match that ends at index i (starts at i - p.size() + 1)\

Because the suffix [i - p.size() + 1, i] == prefix (which is p)

Application 2 - counting number of occurrences of each prefix in a string:

Counting the number of occurrences of each prefix s[0…i] in string s:

lps[i] is the length of the longest proper prefix which is a suffix that ends at position i, shorter prefixes can end at the same position too.

So at position i, prefixes of the following sizes end: lps[i], lps[lps[i] - 1], lps[lps[lps[i] - 1] - 1] and so on until the index becomes zero

vector<int> ans(n + 1);

// count the longest prefixes at each position (lps[i])
for (int i = 0; i < n; i++) {
    ans[lps[i]]++;
}

// accumulate smaller prefixes ending at the same position
for (int i = n - 1; i > 0; i--) {
    ans[lps[i - 1]] += lps[i];
}

// count the suffixes themselves (each suffix occurs once at the start)
for (int i = 0; i <= n; i++) {
    ans[i]++;
}

Counting the number of occurrences of each prefix s[0…i] in string t:
Get the string s + ‘#’ + t and do the same but ignore the first s.size() + 1 indices the final loop only goes on for the lcp of s and t (i <= lcp(s, t))

Application 3 - finding the number of different substrings in a string:

We will solve this problem iteratively, meaning if you know the answer for a string s, what happens if you add a character c at the end of s (some new substrings ending in c will appear, we want to count the ones that didn’t appear before)

string t = s + c, reverse t, now the task is to count the number of prefixes of t which don’t appear again

The total number of prefixes is |s| + 1.

If we find the max value in the lps array of t (the longest prefix which appears as a substring in t) we know that all prefixes smaller that max(lps[i]) also appear so answer = |s| + 1 - max(lps[i])

O(n2)

Application 4 - compressing a string s (finding shortest t where t * n = s)

k = n - lps[n - 1]

If (n % k == 0) {
    ans = k;
}
else {
    ans = n;
}
*/
