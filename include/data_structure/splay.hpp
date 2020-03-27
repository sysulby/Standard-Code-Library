const int maxn = 1000000 + 5;

int psz;
int key[maxn], tag[maxn];
int sz[maxn], fa[maxn], ch[maxn][2];

int node(int k) {
  int u = ++psz;
  key[u] = k, tag[u] = 0, sz[u] = 1, fa[u] = ch[u][0] = ch[u][1] = 0;
  return u;
}

void maintain(int u) { sz[u] = sz[ch[u][0]] + sz[ch[u][1]] + 1; }

void pushdown(int u) {
  if (tag[u]) {
    // apply change
    tag[u] = 0;
  }
}

class Splay {
 public:
  Splay() : root(0) {}

  bool empty() { return root == 0; }

  int size() { return sz[root]; }

  void clear() { root = 0; }

  int find(int k) {
    int u = root, p = 0;
    while (u) {
      pushdown(u);
      if (k == key[u]) return splay(u);
      p = u, u = ch[u][k > key[u]];
    }
    splay(p);
    return 0;
  }

  int insert(int k) {
    int u = root, p = 0;
    while (u) {
      pushdown(u);
      p = u, u = ch[u][k > key[u]];
    }
    u = node(k), fa[u] = p;
    if (p) ch[p][k > key[p]] = u;
    return splay(u);
  }

  int erase(int k) {
    int u = find(k);
    if (!u) return 0;
    if (!ch[u][0] || !ch[u][1]) {
      root = ch[u][0] ^ ch[u][1];
    } else {
      int d = (sz[ch[u][0]] > sz[ch[u][1]]), v = ch[u][d ^ 1];
      while (ch[v][d]) {
        pushdown(v);
        v = ch[v][d];
      }
      splay(v, u);
      fa[ch[u][d]] = v, ch[v][d] = ch[u][d], maintain(v);
      root = v;
    }
    fa[root] = 0;
    return u;
  }

  int order_of_key(int k) {
    int u = root, p = 0, ret = 0;
    while (u) {
      pushdown(u);
      if (k > key[u]) ret += sz[ch[u][0]] + 1;
      p = u, u = ch[u][k > key[u]];
    }
    splay(p);
    return ret;
  }

  int find_by_order(int i) {
    int u = root, p = 0;
    while (u) {
      pushdown(u);
      int l = sz[ch[u][0]];
      if (i == l) return splay(u);
      u = ch[u][i > l];
      if (i > l) i -= l + 1;
    }
    splay(p);
    return 0;
  }

 private:
  int root;

  void rotate(int u) {
    int p = fa[u], g = fa[p], d = (u == ch[p][1]);
    fa[ch[u][d ^ 1]] = p, ch[p][d] = ch[u][d ^ 1], maintain(p);
    fa[p] = u, ch[u][d ^ 1] = p, maintain(u);
    fa[u] = g;
    if (g) ch[g][p == ch[g][1]] = u, maintain(g);
  }

  int splay(int u, int top = 0) {
    while (fa[u] != top) {
      int p = fa[u], g = fa[p];
      if (g != top) rotate((u == ch[p][1]) ^ (p == ch[g][1]) ? u : p);
      rotate(u);
    }
    if (!top) root = u;
    return u;
  }
};
