//
// Created by wangxinshuo on 2020/11/7.
//

<<<<<<< HEAD
#include "rdma_predefine.hpp"
#include "rdma_structure.hpp"
#include "rdma_resource.hpp"
#include "rdma_poll.hpp"
#include "rdma_connect.hpp"
=======
#include "rdma_predefine.h"
#include "rdma_structure.h"
#include "rdma_resource.h"
#include "rdma_poll.h"
#include "rdma_connect.h"
>>>>>>> 0e0992a012c0911bb5008d41f572f1ab49323ebd

#include <string>

class RdmaClient {
 private:
  resources resources_{};
  config_t config_{
      nullptr,  /* dev_name */
      nullptr,  /* server_name */
      19875, /* tcp_port */
      1,       /* ib_port */
      -1 /* gid_idx */
  };
 public:
  explicit RdmaClient(const std::string &ip) {
    // set ip
    config_.server_name = const_cast<char *>(ip.c_str());
    // init
    char temp_char;
    resources_init(&resources_);
    // 1 - 4， 7
    resources_create(&resources_, &config_);
    // 5 - 6
    connect_qp(&resources_, &config_);
    // waiting for complete
    poll_completion(&resources_);
    sock_sync_data(resources_.sock, 1, "R", &temp_char);
    // 8
    post_send(&resources_, IBV_WR_RDMA_READ);
    poll_completion(&resources_);
  }

  void copy(uint64_t pos, const char *data, uint64_t size) const {
    memcpy(resources_.buf + pos, data, size);
  }

  ~RdmaClient() {
//    char temp_char;
//    post_send(&resources_, IBV_WR_RDMA_WRITE);
//    poll_completion(&resources_);
//    sock_sync_data(resources_.sock, 1, "W", &temp_char);
    resources_destroy(&resources_);
    if (config_.dev_name)
      free((char *) config_.dev_name);
  }
};

int main() {
  std::string ip = "10.11.6.132";
  RdmaClient client(ip);
  std::string data = "123543252345342523454325234543252345325";
  client.copy(0, data.c_str(), data.size());
  client.copy( data.size(), data.c_str(), data.size());
}