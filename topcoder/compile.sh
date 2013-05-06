# script to compile 
filename=${1-test.cc}
g++ -DHAVE_NETINET_IN_H -I /usr/local/boost/include -I/usr/local/thrift/include -L/usr/local/thrift/lib $filename gen-cpp/DataService.cpp gen-cpp/parser_types.cpp -o test -lthrift
