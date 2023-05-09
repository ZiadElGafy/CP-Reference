struct FenwickTree {
    vector<int> a, b;

    FenwickTree(int n) {
        a.assign(n, 0);
        b.assign(n, 0);
    }

    int sum(vector<int> &v, int r) {
        int ret = 0;

        for (; r >= 0; r = (r & (r + 1)) - 1) {
            ret += v[r];
        }

        return ret;
    }

    int solve(int i) {
        return sum(a, i) * i - sum(b, i);
    }

    int query(int l, int r) {
        return solve(r) - solve(l - 1);
    }

    void set(vector<int> &v, int i, int d) {
        for (; i < v.size(); i = i | (i + 1)) {
            v[i] += d;
        }
    }

    void add(int l, int r, int d) {
        set(a, l, d);
        set(a, r + 1, -d);

        set(b, l, d * (l - 1));
        set(b, r + 1, -d * r);
    }
};
