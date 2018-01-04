//
//  greeter_service_imp.cpp
//  cpp_proj_sample
//
//  Created by hatlonely on 2018/1/4.
//

#include "greeter_service_impl.hpp"
#include <grpc++/grpc++.h>

namespace hl {
    
    grpc::Status GreeterServiceImpl::SayHello(grpc::ServerContext* context, const HelloRequest* request, HelloReply* response) {
        std::string prefix("Hello ");
        response->set_message(prefix + request->name());
        return grpc::Status::OK;
    }
    
    void RunServer() {
        std::string server_address("0.0.0.0:50051");
        GreeterServiceImpl service;
        
        grpc::ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
        std::cout << "Server listening on " << server_address << std::endl;
        
        server->Wait();
    }
    
}
