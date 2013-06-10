#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <vector>
#include <iostream>

using std::priority_queue;
using std::vector;
using std::cout;
using std::endl;

#define M 50010

typedef long long uint64;

// cost value and index
struct CostIndex {
  int value, index;
};

bool operator< (CostIndex const &left, CostIndex const &right) {
  return left.value < right.value;
}

int main(int argc, const char *argv[]) {
  char brackets[M];
  scanf("%s", brackets);
  uint64 total_cost = 0;
  priority_queue<CostIndex> cost_queue;
  int balance = 0;
  bool failed = false;
  int brackets_len = strlen(brackets);
  for (int i = 0; i < brackets_len; ++i) {
    if (brackets[i] == '(') {
      balance += 1;
    } else if (brackets[i] == ')') {
      balance -= 1;
    } else {
      int left_cost, right_cost;
      scanf("%d %d", &left_cost, &right_cost);
      brackets[i] = ')';
      balance -= 1;
      total_cost += right_cost;
      CostIndex cost_index;
      int adjust_cost = right_cost - left_cost;
      cost_index.value = adjust_cost;
      cost_index.index = i;
      cost_queue.push(cost_index);
    }

    if (balance < 0) {
      if (cost_queue.empty()) {
        failed = true;
        break;
      } else {
        CostIndex cheapest = cost_queue.top();
        cost_queue.pop();
        // transform from "(" to ")"
        brackets[cheapest.index] = '(';
        // cout << cheapest.index << " " << cheapest.value << endl;
        total_cost -= cheapest.value;
        balance += 2;
      }
    }
  }
  if (balance != 0) failed = true;
  if (failed) printf("-1\n");
  else {
    cout << total_cost << endl;
    cout << brackets << endl;
    return 0;
  }
}
