#include <algorithm>

using namespace std;

namespace quickselect {

int partition(int a[], int l, int r) {
  int pivot = a[l], p = r;
  for (int i = r - 1; i > l; --i)
    if (a[i] >= pivot) swap(a[i], a[--p]);
  swap(a[l], a[--p]);
  return p;
}

void kth(int a[], int l, int k, int r) {
  if (r - l <= 1) return;
  int p = partition(a, l, r);
  if (k < p) kth(a, l, k, p);
  if (k > p) kth(a, p + 1, k, r);
}

}  // namespace quickselect
