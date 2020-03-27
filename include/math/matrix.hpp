#include <cstring>

const int mod = 1000000007;
const int maxn = 10000 + 5;

struct Matrix {
  int n, m;
  int a[maxn];

  Matrix(int n, int m) : n(n), m(m) { memset(a, 0, sizeof(int) * n * m); }

  int* operator[](int i) { return a + i * m; }

  const int* operator[](int i) const { return a + i * m; }

  Matrix operator+(const Matrix& b) const {
    Matrix ret(n, m);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) ret[i][j] = (a[i * m + j] + b[i][j]) % mod;
    return ret;
  }

  Matrix operator*(const Matrix& b) const {
    Matrix ret(n, b.m);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < b.m; ++j)
        for (int k = 0; k < m; ++k)
          ret[i][j] = (ret[i][j] + (long long)a[i * m + k] * b[k][j]) % mod;
    return ret;
  }

  Matrix pow(long long b) const {
    Matrix a = *this, ret(n, n);
    for (int i = 0; i < n; ++i) ret[i][i] = 1;
    for (; b; a = a * a, b >>= 1)
      if (b & 1) ret = ret * a;
    return ret;
  }
};
