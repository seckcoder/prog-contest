#include <iostream>
#include "srm_402_1000.h"
#include "data.h"
#include "gen-cpp/parser_types.h"

using json_parser::Case;
using namespace std;


int main(int argc, const char *argv[]) {
  BikeRiding rider = BikeRiding();

  vector<Case> cases;
  read(cases, "test.json");
  for (int i = 0; i < cases.size(); ++i) {
    cout << rider.countRoutes(cases[i].paths, cases[i].startPoints,
                      cases[i].endPoint,
                      cases[i].n) << endl;
  }
  return 0;
}
