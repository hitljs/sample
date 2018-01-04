#include <iostream>
#include <libconfig.h++>
#include "greeter_service_impl.hpp"

int main(int argc, const char* argv[]) {
    libconfig::Config config;
    config.readFile("conf/greeter.cfg");
    
    hl::GreeterServer greeterServer;
    if (greeterServer.Init(config.lookup("greeter")) != 0) {
        std::cout << "init failed" << std::endl;
    }
    if (greeterServer.Run() != 0) {
        std::cout << "run failed." << std::endl;
    }
}
