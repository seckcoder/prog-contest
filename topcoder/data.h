#ifndef DATA_93GGWE9K

#define DATA_93GGWE9K


#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include "gen-cpp/DataService.h"

using boost::shared_ptr;
using json_parser::Case;
using json_parser::DataServiceClient;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

void read(std::vector<Case> &_return, const std::string &filename) {
  shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

  DataServiceClient client(protocol);

  try {
    transport->open();
    client.read(_return, filename);
    transport->close();
  } catch (TException &tx) {
    printf("ERROR: %s\n", tx.what());
  }
}

#endif /* end of include guard: DATA_93GGWE9K */
