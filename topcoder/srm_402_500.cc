#include <iostream>
#include <vector>
#include "srm_402_500.h"

using namespace std;

struct TestCase {
  int x, y;
  TestCase(int _x, int _y) {
    x = _x;
    y = _y;
  }
};

int main(int argc, const char *argv[]) {
  Pathfinding path;
  vector<TestCase> cases;
  cases.push_back(TestCase(0, -4));
  cases.push_back(TestCase(5, -4));
  cases.push_back(TestCase(5,4));
  cases.push_back(TestCase(-1,-4));
  cases.push_back(TestCase(0,0));

  for (int i = 0; i < cases.size(); ++i) {
    cout << path.getDirections(cases[i].x, cases[i].y) << endl;
  }
  return 0;
}
