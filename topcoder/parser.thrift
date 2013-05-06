namespace cpp json_parser
namespace py json_parser

struct Case {
  1:list<string> paths;
  2:list<i32> startPoints;
  3:i32 endPoint;
  4:i32 n;
}

service DataService {
  list<Case> read(1:string filename);
}
