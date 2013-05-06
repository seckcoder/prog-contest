#include <cstdlib>

using namespace std;
class Pathfinding {
 public:
  int getDirections(int,int);
  int direct(int x, int y) {
    return abs(x) + abs(y);
  }

  bool even(int x) {
    return (x%2==0);
  }

  bool odd(int x) {
    return !even(x);
  }
};

int Pathfinding::getDirections(int x, int y) {
  int direct_dist = direct(x,y);
  if (x >= 0 && y == 0)
    return direct_dist;

  if (x > 0 && y > 0) {
    if (odd(x) && odd(y)) return direct_dist + 2;
    else
      return direct_dist;
  }

  if (x == 0 && y > 0) return direct_dist;

  if (x < 0 && y > 0) {
    if (odd(x) && odd(y)) return direct_dist+2;
    else
      return direct_dist;
  }

  if (x < 0 && y < 0) {
    if (even(x) && even(y)) return direct_dist + 4;
    else return direct_dist + 2;
  }

  if (x == 0 && y < 0) {
    if (odd(y)) return direct_dist + 2;
    else return direct_dist + 4;
  }

  if (x > 0 && y < 0) {
    if (odd(y)) return direct_dist + 2;
    else return direct_dist;
  }
  return direct_dist;
}
