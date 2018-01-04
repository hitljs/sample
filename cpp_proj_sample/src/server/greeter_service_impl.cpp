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

    int GreeterServer::Init(const libconfig::Setting& setting) {
        _address = setting.lookup("address").c_str();
        return 0;
    }

    int GreeterServer::Run() {
        std::string serverAddress(_address);
        GreeterServiceImpl service;
        
        grpc::ServerBuilder builder;
        builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
        std::cout << "Server listening on " << serverAddress << std::endl;
        
        server->Wait();
        
        return 0;
    }
}
