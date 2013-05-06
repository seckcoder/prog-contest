#include <vector>
#include <string>
using std::vector;
using std::string;

class Trekking {
 public:
  int findCamps(string trail, vector<string> plans) {
    int invalid = trail.length()+1;
    int camps = invalid;
    for(int i = 0; i < plans.size(); i++) {
      camps = std::min(findCamp(trail, plans[i]), camps);
    }
    if (camps == invalid) {
      return -1;
    } else {
      return camps;
    }
  }

  int findCamp(string trail, string plan) {
    int invalid = trail.length()+1;
    int camps = 0;
    for(int i = 0; i < trail.length(); i++) {
      if (trail[i] == '^' && plan[i] == 'C') {
        return invalid;
      } else if (trail[i] == '.' && plan[i] == 'C') {
        camps += 1;
      }
    }
    return camps;
  }
};
