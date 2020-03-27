namespace merge_sort {

const int maxn = 1000000 + 5;

int b[maxn];

void merge(int a[], int l, int m, int r) {
  int i = l, j = m, p = l;
  while (p < r) {
    if (i < m && (j >= r || a[i] <= a[j])) {
      b[p++] = a[i++];
    } else {
      b[p++] = a[j++];
      // inv += m - i;
    }
  }
  for (int i = l; i < r; ++i) a[i] = b[i];
}

void sort(int a[], int l, int r) {
  if (r - l <= 1) return;
  int mid = (l + r) / 2;
  sort(a, l, mid);
  sort(a, mid, r);
  merge(a, l, mid, r);
}

}  // namespace merge_sort
