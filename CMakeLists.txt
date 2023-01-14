project(RDMA_TEST)

cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

include_directories("include")

add_executable(opt src/option/opt.c)

# add_executable(rdma_cc_server src/rdma_cc/server.cc)
# target_link_libraries(rdma_cc_server ibverbs pthread)

# add_executable(rdma_cc_client src/rdma_cc/client.cc)
# target_link_libraries(rdma_cc_client ibverbs pthread)

# add_executable(cc_server src/tcp/server.cc)
# target_link_libraries(cc_server boost_system)

# add_executable(cc_client src/tcp/client.cc)
# target_link_libraries(cc_client boost_system)

# rdma_c
add_executable(rdma_c_server src/rdma_c/server.c)
target_link_libraries(rdma_c_server ibverbs)

add_executable(rdma_c_client src/rdma_c/client.c)
target_link_libraries(rdma_c_client ibverbs)
