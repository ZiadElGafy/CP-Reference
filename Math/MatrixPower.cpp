const int D = 100 + 1;
template<typename T>
struct Matrix {
/*
                     [ 0, 1 ]
    [ f(0), f(1) ] * [ 1, 1 ] = [ f(1), f(2) ]

    Transition: T[X][Y] = Z => newY += oldX * Z (from X to Y)
*/
    int r, c;
    T m[D][D] = {};

    Matrix() {}

    Matrix(int n) { // identity
        this->r = n;
        this->c = n;

        for (int i = 1; i <= n; i++)
            m[i][i] = 1;
    }

    Matrix(int r, int c) {
        this->r = r;
        this->c = c;
    }

    Matrix(int r, int c, T val) {
        this->r = r;
        this->c = c;

        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                m[i][j] = val;
    }

    void setRow(int row, T val) {
        for (int j = 1; j <= c; j++)
            m[row][j] = val;
    }

    void setColumn(int col, T val) {
        for (int i = 1; i <= r; i++)
            m[i][col] = val;
    }

    Matrix operator*(Matrix other) {
        if (c != other.r) {
            cout << "Invalid dimensions for multiplication" << endl;
            assert(0);
        }

        Matrix ret = Matrix(r, other.c);

        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                for (int k = 1; k <= other.c; k++) {
                    ret.m[i][k] += (1LL * m[i][j] * other.m[j][k]) % mod;

                    if (ret.m[i][k] >= mod)
                        ret.m[i][k] -= mod;
                }
            }
        }

        return ret;
    }

    friend Matrix<T> matPower(Matrix a, ll p) {
        Matrix<T> ret(a.r);

        while (p) {
            if (p & 1)
                ret = ret * a;

            p >>= 1;
            a = a * a;
        }

        return ret;
    }

    friend ostream &operator<<(ostream &out, const Matrix<T> &a){
        cout << "Matrix " << a.r << ' ' << a.c << el;
        for (int i = 1; i <= a.r; i++, cout << el)
            for (int j = 1; j <= a.c; j++)
                cout << a.m[i][j] << ' ';
        cout << "--------------" << el;
        return out;
    }
};
