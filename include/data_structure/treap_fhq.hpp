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
    int l, r, u;
    split(root, k, l, r);
    split(r, k + 1, u, r);
    root = merge(merge(l, u), r);
    return u;
  }

  int insert(int k) {
    int l, r, u = node(k);
    split(root, k, l, r);
    root = merge(merge(l, u), r);
    return u;
  }

  int erase(int k) {
    int l, r, u;
    split(root, k, l, r);
    split(r, k + 1, u, r);
    root = merge(merge(l, merge(ch[u][0], ch[u][1])), r);
    return u;
  }

  int order_of_key(int k) {
    int l, r;
    split(root, k, l, r);
    int ret = sz[l];
    root = merge(l, r);
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

  void split(int u, int k, int &l, int &r) {
    if (!u) {
      l = r = 0;
      return;
    }
    if (k > key[u]) {
      l = u, split(ch[u][1], k, ch[u][1], r);
    } else {
      split(ch[u][0], k, l, ch[u][0]), r = u;
    }
    maintain(u);
  }

  int merge(int u, int v) {
    if (!u || !v) return u ^ v;
    if (pri[u] > pri[v]) {
      ch[u][1] = merge(ch[u][1], v), maintain(u);
      return u;
    } else {
      ch[v][0] = merge(u, ch[v][0]), maintain(v);
      return v;
    }
  }
};
