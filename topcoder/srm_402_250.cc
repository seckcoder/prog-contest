#include <iostream>
#include <vector>
#include <string>
#include <cstdarg>
#include <stdio.h>
#include "srm_402_250.h"

using namespace std;

struct TestCase {
  string trail;
  vector<string> plan;
};

TestCase makeTestCase(char *trail, ...) {

  TestCase one;
  va_list vl;
  va_start(vl, trail);
  one.trail = string(trail);

  char * str = trail;

  str = va_arg(vl, char*);
  while (str != NULL) {
    one.plan.push_back(string(str));
    str = va_arg(vl, char*);
  }

  va_end(vl);

  return one;
}

void makeTestCases(vector<TestCase> &cases) {
  cases.push_back(makeTestCase("^^....^^^...",
                               "CwwCwwCwwCww",
                               "wwwCwCwwwCww",
                               "wwwwCwwwwCww",
                               NULL));

  cases.push_back(makeTestCase("^^^^",
                            "wwww",
                            "wwwC",
                            NULL));
  cases.push_back(makeTestCase("^^.^^^^",
                            "wwCwwwC",
                            "wwwCwww",
                            "wCwwwCw",
                            NULL));
  cases.push_back(makeTestCase("^^^^....^.^.^.",
                            "wwwwCwwwwCwCwC",
                            "wwwwCwwCwCwwwC",
                            "wwwCwwwCwwwCww",
                            "wwwwwCwwwCwwwC",
                            NULL));

  cases.push_back(makeTestCase("..............",
                            "CwCwCwCwCwCwCw",
                            "CwwCwwCwwCwwCw",
                            NULL));

}
int main(int argc, const char *argv[]) {
  Trekking trek = Trekking();
  vector<TestCase> cases;
  makeTestCases(cases);

  for (int i = 0; i < cases.size(); ++i) {
    cout << trek.findCamps(cases[i].trail, cases[i].plan) << endl; 
  }
  return 0;
}
