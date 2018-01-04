#pragma once

#include "greeter.grpc.pb.h"
#include <grpc++/grpc++.h>

namespace hl {
    class GreeterServiceImpl final : public Greeter::Service
}
