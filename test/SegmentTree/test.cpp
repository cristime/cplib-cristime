#include <fstream>

#include "../../lib/SegmentTree/Segtree_sum.h"

#ifdef DEBUG
#include <iostream>
#endif

using namespace std;

int n, m;
SegTree::T origin[SegTree::maxn];

#ifdef DEBUG
int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  // ifstream fin( argv[ 1 ] );
  // ofstream fout( argv[ 2 ] );

  cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> origin[i];

  SegTree::build(origin, 1, 1, n);

  for (int i = 1; i <= m; ++i) {
    int op, left, right, addnum;
    cin >> op >> left >> right;
    if (op == 1) {
      cin >> addnum;
      SegTree::update(left, right, addnum, 1, 1, n);
    } else {
      cout << SegTree::query(left, right, 1, 1, n) << endl;
    }
  }
  return 0;
}
#endif

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  ifstream fin(argv[1]);
  ofstream fout(argv[2]);

  fin >> n >> m;
  for (int i = 1; i <= n; ++i) fin >> origin[i];

  SegTree::build(origin, 1, 1, n);

  for (int i = 1; i <= m; ++i) {
    int op, left, right;
    SegTree::T addnum;
    fin >> op >> left >> right;
    if (op == 1) {
      fin >> addnum;
      SegTree::update(left, right, addnum, 1, 1, n);
    } else {
      fout << SegTree::query(left, right, 1, 1, n) << endl;
    }
  }

  fin.close();
  fout.close();

  return 0;
}