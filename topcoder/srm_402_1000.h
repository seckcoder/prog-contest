#include <vector>
#include <string>
#include <iostream>
#include <memory.h>

using namespace std;

class BikeRiding {
 public:
  int countRoutes(vector<string> paths, vector<int> startPoints, int endPoint, int n) {
    int route_num = 0;
    int visited[50];
    for (int i = 0; i < startPoints.size(); ++i) {
      int num = 0;
      memset(visited, 0, 50*sizeof(int));
      if (!dfs(paths, num, visited, startPoints[i], endPoint, n, false)) return -1;
      else route_num += num;
      if (route_num > n) return -1;
    }
    return route_num;
  }

  bool dfs(const vector<string> &paths, int &num, int visited[], int startPoint, int endPoint, int n, bool loop) {
    //cout << startPoint << endl;
    if (startPoint == endPoint) {
      num += 1;
      if (loop) {
        return false;
      } else {
        return true;
      }
    }
    visited[startPoint] = 1;

    for (int i = 0; i < paths[startPoint].length(); ++i) {
      if (connected(paths[startPoint][i])) {
        if (visited[i]) {
          loop = true;
        } else {
          if (!dfs(paths, num, visited, i, endPoint, n, loop)) return false;
        }
      }
    }
    visited[startPoint] = 0;
    return true;
  }

  bool connected(char c) {
    if (c == '0') return false;
    return true;
  }
};
