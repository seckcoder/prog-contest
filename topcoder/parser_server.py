import sys
sys.path.append('gen-py')

import json
from thrift.transport import TSocket, TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer
from thrift import Thrift

from json_parser.ttypes import Case
from json_parser import DataService


class JsonObject(dict):
    def __getattr__(self, attr):
        return self[attr]

    def __setattr__(self, attr, value):
        self[attr] = value


def obj_hook(pairs):
    o = JsonObject()
    for k, v in pairs.iteritems():
        o[str(k)] = v
    return o

def load_json(filename):
    with open(filename, 'r') as f:
        res = json.loads(f.read(), object_hook=obj_hook)
        return res
    
class Handler(object):
    def read(self, filename):
        json_obj = load_json(filename)
        cases = []
        for jcase in json_obj.cases:
            case = Case()
            for attr,value in jcase.iteritems():
                setattr(case, attr, value)
            cases.append(case)

        return cases

def main():
    handler = Handler()
    processor = DataService.Processor(handler)
    transport = TSocket.TServerSocket('localhost', 9090)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()

    server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

    print "started..."

    try:
        server.serve()
    except Thrift.TException, ex:
        print ex.message

    print "shut down"

def test():
    handler = Handler()
    print handler.read('test.json')

if __name__ == '__main__':
    main()
