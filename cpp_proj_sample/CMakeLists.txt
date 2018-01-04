CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(CPP_PROJ_SAMPLE)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(VERSION "v0.0.0")
SET(WORK_ROOT "../")
IF(debug)
    SET(CMAKE_CXX_FLAGS "-std=c++11 -g  -pthread")
ELSE()
    SET(CMAKE_CXX_FLAGS "-std=c++11 -O2  -pthread")
    ADD_DEFINITIONS(-DNO_DEBUG=1)
ENDIF()
IF(gprof)
    SET(CMAKE_CXX_FLAGS "-std=c++11 -pg -g  -pthread")
    ADD_DEFINITIONS(-DGPROF=1)
ENDIF()
IF(gcov)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC")
ENDIF()

AUX_SOURCE_DIRECTORY(src SRC)
AUX_SOURCE_DIRECTORY(proto_out PROTO)

INCLUDE_DIRECTORIES(
    "include"
    "proto_out"
    "/usr/local/include"
)

LINK_DIRECTORIES(
    "/usr/local/lib"
)

ADD_DEFINITIONS(
    -DCPP_PROJ_SAMPLE_VERSION="${VERSION}"
)

ADD_EXECUTABLE(cpp_proj_sample ${SRC} ${PROTO})

TARGET_LINK_LIBRARIES(
    cpp_proj_sample
    grpc
    protobuf
)

ADD_CUSTOM_COMMAND(
    TARGET cpp_proj_sample
    POST_BUILD
    COMMAND rm -rf ${CPP_PROJ_SAMPLE_BINARY_DIR}/output
    COMMAND mkdir -p ${CPP_PROJ_SAMPLE_BINARY_DIR}/output/bin
    COMMAND mkdir -p ${CPP_PROJ_SAMPLE_BINARY_DIR}/output/conf
    COMMAND mkdir -p ${CPP_PROJ_SAMPLE_BINARY_DIR}/output/log
    COMMAND cp -rf ${CPP_PROJ_SAMPLE_BINARY_DIR}/cpp_proj_sample ${CPP_PROJ_SAMPLE_BINARY_DIR}/output/bin
    COMMAND cp -rf ${CPP_PROJ_SAMPLE_SOURCE_DIR}/conf/*.conf ${CPP_PROJ_SAMPLE_BINARY_DIR}/output/conf/
)

