#include <cstdlib>

const int maxn = 1000000 + 5;

int psz;
int key[maxn], pri[maxn];
int sz[maxn], ch[maxn][2];

int node(int k) {
  int u = ++psz;
  key[u] = k, pri[u] = rand(), sz[u] = 1, ch[u][0] = ch[u][1] = 0;
  return u;
}

void maintain(int u) { sz[u] = sz[ch[u][0]] + sz[ch[u][1]] + 1; }

class Treap {
 public:
  Treap() : root(0) {}

  bool empty() { return root == 0; }

  int size() { return sz[root]; }

  void clear() { root = 0; }

  int find(int k) {
    int u = root;
    while (u) {
      if (k == key[u]) return u;
      u = ch[u][k > key[u]];
    }
    return 0;
  }

  int insert(int k) { return insert(root, k); }

  int erase(int k) { return erase(root, k); }

  int order_of_key(int k) {
    int u = root, ret = 0;
    while (u) {
      if (k > key[u]) ret += sz[ch[u][0]] + 1;
      u = ch[u][k > key[u]];
    }
    return ret;
  }

  int find_by_order(int i) {
    int u = root;
    while (u) {
      int k = sz[ch[u][0]];
      if (i == k) return u;
      u = ch[u][i > k];
      if (i > k) i -= k + 1;
    }
    return 0;
  }

 private:
  int root;

  void rotate(int &u, int d) {
    int v = ch[u][d];
    ch[u][d] = ch[v][d ^ 1], maintain(u);
    ch[v][d ^ 1] = u, maintain(v), u = v;
  }

  int insert(int &u, int k) {
    if (u == 0) return u = node(k);
    int d = (k > key[u]), ret = insert(ch[u][d], k);
    pri[ch[u][d]] > pri[u] ? rotate(u, d) : maintain(u);
    return ret;
  }

  int erase(int &u, int k) {
    if (u == 0) return 0;
    if (k == key[u]) {
      int ret = u;
      if (!ch[u][0] || !ch[u][1]) {
        u = ch[u][0] ^ ch[u][1];
      } else {
        int d = (pri[ch[u][1]] > pri[ch[u][0]]);
        rotate(u, d), erase(ch[u][d ^ 1], k), maintain(u);
      }
      return ret;
    }
    int ret = erase(ch[u][k > key[u]], k);
    if (ret) maintain(u);
    return ret;
  }
};
