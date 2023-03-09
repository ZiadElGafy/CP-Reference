template<typename T>
struct Matrix {
/*
                  [ 0, 1 ]
 [ f(0), f(1) ] * [ 1, 1 ] = [ f(1), f(2) ]

 Transition: T[X][Y] = Z => newY += oldX * Z
*/
    int r, c;
    vector<vector<T>> m;

    Matrix() {}

    Matrix(int n) { // identity
        this->r = n;
        this->c = n;
        m.assign(n + 1, vector<T>(n + 1));

        for(int i = 1; i <= n; i++)
            m[i][i] = 1;
    }

    Matrix(int r, int c) {
        this->r = r;
        this->c = c;
        m.assign(r + 1, vector<T>(c + 1));
    }

    Matrix(int r, int c, T val) {
        this->r = r;
        this->c = c;
        m.assign(r + 1, vector<T>(c + 1, val));
    }

    void setRow(int row, T val) {
        for(int j = 1; j <= c; j++)
            m[row][j] = val;
    }

    void setColumn(int col, T val) {
        for(int i = 1; i <= r; i++)
            m[i][col] = val;
    }

    Matrix operator *(Matrix other) {
        if(c != other.r) {
            cout << "Invalid dimensions for multiplication" << endl;
            assert(0);
        }

        Matrix ret = Matrix(r, other.c);

        for(int i = 1; i <= r; i++)
            for(int j = 1; j <= other.c; j++)
                for(int k = 1; k <= c; k++)
                    ret.m[i][j] = (ret.m[i][j] + (1LL * m[i][k] * other.m[k][j]) % mod) % mod;

        return ret;
    }

    friend Matrix<T> matPower(Matrix a, ll p) {
        Matrix<T> ret(a.r);

        while(p){
            if(p & 1)
                ret = ret * a;

            p >>= 1;
            a = a * a;
        }

        return ret;
    }

    void print() {
        cout << "Matrix: " << r << ' ' << c << el << "-------" << el;
        for(int i = 1; i <= r; i++, cout << el)
            for(int j = 1; j <= c; j++)
                cout << m[i][j] << ' ';
        cout << el;
    }
};
