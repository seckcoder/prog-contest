/*
 * Not passed; 2012-09-26
 */
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
template<class OrigDataType>
class TreeNode {
public:
  int l, r;
  TreeNode() {
    l = r = -1;
    orig_vec = NULL;
  }
  TreeNode(int _l, int _r) {
    l = _l;
    r = _r;
  }
  void set_orig_vec(const vector<OrigDataType> *_orig) {
    orig_vec = _orig;
  }
  void fill(int _l, int _r) {
    l = _l;
    r = _r;
  }
  void fill(int _l, int _r, const TreeNode *lc, const TreeNode *rc) {
    fill(_l, _r);
  }
  void print() {
    cout << l << " " << r << endl;
  }
  //virtual bool is_bad(const TreeNode *node) = 0;
protected:
  const vector<OrigDataType> *orig_vec;
};


template<class TheTreeNode, class OrigDataType>
class IntervalTree {
 public:
  IntervalTree() {
    tree = NULL;
    orig_vec = NULL;
  } 
  ~IntervalTree() {
    delete [] tree;
  }

  void build(const vector<OrigDataType> &_orig) {
    tree = new TheTreeNode[2 * _orig.size() + 3];
    orig_vec = &_orig;
    build(0, 0, _orig.size() - 1);
  }

  TheTreeNode *build(int node_idx, int l, int r) {
    TheTreeNode &node = tree[node_idx];
    node.fill(-1, -1);
    node.set_orig_vec(orig_vec);
    if (l ==r)  {
      node.fill(l, r, NULL, NULL);
      //cout << node_idx << ":";
      //cout << node << endl;
      return &node;
    }
    int mid = ceil((l + r) * 0.5);
    TheTreeNode *lc = build(left_child(node_idx), l, mid - 1);
    TheTreeNode *rc = build(right_child(node_idx), mid, r);
    node.fill(l, r, lc, rc);
    //cout << node_idx << ":";
    //cout << node << endl;
    return &node;
  }

  TheTreeNode search(int node_idx, int l, int r) {
    TheTreeNode cur_node = tree[node_idx];
    //cout << node_idx << " " << l << " " << r << endl;
    if (l > r) return TheTreeNode::bad();
    if (cur_node.r < l || cur_node.l > r) return TheTreeNode::bad();
    if (cur_node.r == r && cur_node.l == l) return cur_node;
    TheTreeNode lc = tree[left_child(node_idx)];
    TheTreeNode rc = tree[right_child(node_idx)];
    TheTreeNode lret = search(left_child(node_idx),
                              (std::max)(l, lc.l),
                              (std::min)(r, lc.r));
    //cout << lret << endl;
    TheTreeNode rret = search(right_child(node_idx),
                              (std::max)(l, rc.l),
                              (std::min)(r, rc.r));
    //cout << rret <<endl;
    return TheTreeNode(l, r,
                       (std::min)(lret.tmin, rret.tmin),
                       (std::max)(lret.tmax, rret.tmax));
  }
  int left_child(int root) { return 2*root + 1; }
  int right_child(int root) { return 2*root + 2; }

  void print(int root) {
    TheTreeNode node = tree[root];
    cout << node << endl;
    if (node.l != -1) { cout << node.l << endl;print(node.l); }
    //if (node.r != -1) print(node.r);
  }
  private:
   TheTreeNode *tree;  // tree root
   const vector<OrigDataType> *orig_vec;

  //friend ostream &operator<<(ostream &os, const IntervalTree &intv_tree);
};



class MyTreeNode: public TreeNode<int> {
 public:
  static const int LOWER_LIMIT = 0;
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
  void fill(int _l, int _r) {
    TreeNode<int>::fill(_l, _r);
    tmin = LOWER_LIMIT;
    tmax = UPPER_LIMIT;
  }
  void fill(int _l, int _r, const MyTreeNode *lc, const MyTreeNode *rc) {
    TreeNode<int>::fill(_l, _r, lc, rc);
    if (_l == _r) {
      tmin = (*orig_vec)[_l];
      tmax = (*orig_vec)[_l];
      //cout << _l << ":" << orig_vec << ":" << tmin << " : " << tmax << endl;
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

void test_from_stdin() {
  int n, q;
  scanf("%d%d", &n, &q);
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

}
void test_from_file() {
  int n, q;
  FILE* f = fopen("poj_3264.in", "r");
  FILE* out = fopen("poj_3264.out", "w");
  int t;
  fscanf(f, "%d", &t);
  for (int i = 0; i < t; ++i) {
    fscanf(f, "%d %d", &n, &q);
    vector<int> orig(n);
    for (int j = 0; j < n; ++j) {
      fscanf(f, "%d", &orig[j]);
    }
    IntervalTree<MyTreeNode, int> intv_tree;
    intv_tree.build(orig);
    //intv_tree.print(0);
    for (int k = 0; k < q; ++k) {
      int l, r;
      fscanf(f, "%d %d", &l, &r);
      MyTreeNode res = intv_tree.search(0, l - 1, r - 1);
      fprintf(out, "%d\n", res.tmax - res.tmin);
    }
  }
  fclose(out);
  fclose(f);
}
int main(int argc, const char *argv[]) {
  //test_from_file();
  test_from_stdin();
  return 0;
}
