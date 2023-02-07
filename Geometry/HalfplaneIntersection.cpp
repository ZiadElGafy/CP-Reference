struct HalfPlane{
    point pt, direction;
    ld angle;

    HalfPlane(){}

    HalfPlane(const point &a, const point &b){
        pt = a;
        direction = vec(a, b);
        angle = direction.angle;
    }

    bool out(const point &a){
        return cross(direction, vec(pt, a)) < -eps;
    }

    const bool operator<(HalfPlane &other) const {
        return angle < other.angle;
    }

    friend point intersection(const HalfPlane &s, const HalfPlane &t){ // assume they're not parallel
        ld alpha = cross(vec(s.pt, t.pt), t.direction) / cross(s.direction, t.direction);
        return s.pt + (s.direction * alpha);
    }
};

vector<point> HalfPlaneIntersection(vector<HalfPlane> H){
    point box[4] = {
        point(INF, INF),
        point(-INF, INF),
        point(-INF, -INF),
        point(INF, -INF)
    };

    for(int i = 0; i < 4; i++)
        H.push_back(HalfPlane(box[i], box[(i + 1) % 4]));

    // sorting step can be skipped if convex polygon is given in ccw making the algorithm O(n)
    sort(H.begin(), H.end());

    deque<HalfPlane> dq;
    int sz = 0;

    for(int i = 0; i < H.size(); i++){
        while(sz > 1 and H[i].out(intersection(dq[sz - 1], dq[sz - 2])))
            dq.pop_back(), sz--;

        while(sz > 1 and H[i].out(intersection(dq[0], dq[1])))
            dq.pop_front(), sz--;

        // Special case: parallel halfplanes
        if(sz > 0 and fabsl(cross(H[i].direction, dq[sz - 1].direction)) < eps){
            // Opposite halfplanes that are adjecent --> no intersection
            if(dot(H[i].direction, dq[sz - 1].direction) < eps)
                return {};

            // Same direction halfplanes --> keep only the leftmost
            if(H[i].out(dq[sz - 1].pt))
                dq.pop_back(), sz--;
            else
                continue;
        }

        // Add new halfplane
        dq.push_back(H[i]);
        sz++;
    }

    // Final cleanup: Check half-planes at the front against the back and vice-versa
    while (sz > 2 and dq[0].out(intersection(dq[sz - 1], dq[sz - 2])))
        dq.pop_back(), sz--;

    while (sz > 2 and dq[sz - 1].out(intersection(dq[0], dq[1])))
        dq.pop_front(), sz--;

    if(sz < 3)
        return {};

    vector<point> ret(sz);

    for(int i = 0; i + 1 < sz; i++)
        ret[i] = intersection(dq[i], dq[i + 1]);

    ret.back() = intersection(dq[0], dq[sz - 1]);

    return ret;

    // This can produce duplicate points if multiple halfplanes intersect at the same point
}
