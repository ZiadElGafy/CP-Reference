struct FenwickTree {
    int a[N], b[N];

    int sum(int arr[], int r) {
        int ret = 0;

        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += arr[r];

        return ret;
    }

    int solve(int i) {
        return sum(a, i) * i - sum(b, i);
    }

    int query(int l, int r) {
        return solve(r) - solve(l - 1);
    }

    void set(int arr[], int i, int d) {
        for (; i < N; i = i | (i + 1))
            arr[i] += d;
    }

    void add(int l, int r, int d) {
        set(a, l, d);
        set(a, r + 1, -d);

        set(b, l, d * (l - 1));
        set(b, r + 1, -d * r);
    }
};
