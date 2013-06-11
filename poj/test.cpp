#include "interval_tree.h"
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
class MyTreeNode: public TreeNode<int> {
 public:
  static const int LOWER_LIMIT = -1;
  static const int UPPER_LIMIT= 1000001;
  int tmin;
  int tmax;
  MyTreeNode() : TreeNode<int>(){
    tmin = LOWER_LIMIT;
    tmax = UPPER_LIMIT;
  }
  static MyTreeNode bad() {
    return MyTreeNode(-1, -1, UPPER_LIMIT, LOWER_LIMIT);
  }
  MyTreeNode(int _l, int _r, int _tmin, int _tmax) : TreeNode<int>(_l, _r){
    tmin = _tmin;
    tmax = _tmax;
  }
  bool operator==(const MyTreeNode &node) const {
    return (l == node.l && r == node.r && tmin == node.tmin && tmax == node.tmax);
  }
  void fill(int _l, int _r, const MyTreeNode *lc, const MyTreeNode *rc) {
    TreeNode<int>::fill(_l, _r, lc, rc);
    if (_l == _r) {
      tmin = (*orig_vec)[_l];
      tmax = (*orig_vec)[_l];
    } else {
      tmin = (std::min)(lc->tmin, rc->tmin);
      tmax = (std::max)(lc->tmax, rc->tmax);
    }
  }
  friend ostream& operator<<(ostream &os, const MyTreeNode &node);
};

ostream &operator<<(ostream &os, const MyTreeNode &node) {
  os << node.l << " " << node.r << " " << node.tmin << " " << node.tmax;
  return os;
}

int main(int argc, const char *argv[]) {
  int n, q;
  scanf("%d %d", &n, &q);
  vector<int> orig(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &orig[i]);
  }
  IntervalTree<MyTreeNode, int> intv_tree;
  intv_tree.build(orig);
  for (int i = 0; i < q; ++i) {
    int l, r;
    scanf("%d %d", &l, &r);
    MyTreeNode res = intv_tree.search(0, l - 1, r - 1);
    printf("%d\n", res.tmax - res.tmin);
  }
  return 0;
}
