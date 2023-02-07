struct SegmentTree{
    vector<ll> tree, lazy;
    ll neutral;
 
    SegmentTree(int sz){
        tree.assign(4 * sz, 0);
        lazy.assign(4 * sz, 0);
        neutral = 0;
    }
 
    ll merge(ll &u, ll &v){
        return u + v;
    }

    void build(int node, int start, int end, int a[]){
        if(start == end)
            return tree[node] = a[start], void();

        int m = (start + end) >> 1;

        build(2 * node, start, m, a);
        build(2 * node + 1, m + 1, end, a);

        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void set(int node, int start, int end, int idx, ll val){
        if(start == end)
            return tree[node] = val, void();

        int m = (start + end) >> 1;

        if(idx <= m)
            set(2 * node, start, m, idx, val);
        else
            set(2 * node + 1, m + 1, end, idx, val);

        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
 
    void propagate(int &node, int &start, int &end){
        if(lazy[node]){
            tree[node] += lazy[node] * (end - start + 1);
 
            if(start < end){
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
 
            lazy[node] = 0;
        }
    }
 
    // lazy = 0
    // lazy[child] += lazy[node]
    // tree[node] += lazy[node] * range
    void addToRange(int node, int start, int end, int left, int right, ll val){
        propagate(node, start, end);
 
        if(end < left or start > right)
            return;
 
        if(left <= start and end <= right){
            tree[node] += val * (end - start + 1);
 
            if(start < end){
                lazy[2 * node] += val;
                lazy[2 * node + 1] += val;
            }
 
            return;
        }
 
        int m = (start + end) >> 1;
        addToRange(2 * node, start, m, left, right, val);
        addToRange(2 * node + 1, m + 1, end, left, right, val);
 
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    // lazy = -1
    // lazy[child] = lazy[node]
    // tree[node] = lazy[node]
    void setRange(int node, int start, int end, int left, int right, int val){
        propagate(node, start, end);
 
        if(end < left or start > right)
            return;
 
        if(left <= start and end <= right){
            tree[node] = val;
 
            if(start < end){
                lazy[2 * node] = val;
                lazy[2 * node + 1] = val;
            }
 
            return;
        }
 
        int m = (start + end) >> 1;
        setRange(2 * node, start, m, left, right, val);
        setRange(2 * node + 1, m + 1, end, left, right, val);
 
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
 
    ll query(int node, int start, int end, int left, int right){
        if(end < left or start > right)
            return neutral;
 
        propagate(node, start, end);
 
        if(left <= start and end <= right)
            return tree[node];
 
        int m = (start + end) >> 1;
        ll l = query(2 * node, start, m, left, right);
        ll r = query(2 * node + 1, m + 1, end, left, right);
        return merge(l, r);
    }
};
