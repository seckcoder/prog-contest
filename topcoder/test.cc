#include <vector>

#include "data.h"
#include "gen-cpp/parser_types.h"

using json_parser::Case;
using namespace std;


void testDataReader() {
  vector<Case> cases;
  read(cases, "test.json");
  for (int i = 0; i < cases.size(); ++i) {
    cout << cases[i].n << endl;
  }
}

int main(int argc, const char *argv[]) {
}
