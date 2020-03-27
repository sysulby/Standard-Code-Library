#include <algorithm>

using namespace std;

namespace quicksort {

int partition(int a[], int l, int r) {
  int pivot = a[l], p = r;
  for (int i = r - 1; i > l; --i)
    if (a[i] >= pivot) swap(a[i], a[--p]);
  swap(a[l], a[--p]);
  return p;
}

void sort(int a[], int l, int r) {
  if (r - l <= 1) return;
  int p = partition(a, l, r);
  sort(a, l, p);
  sort(a, p + 1, r);
}

}  // namespace quicksort
