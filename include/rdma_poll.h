//
// Created by wangxinshuo on 2020/11/7.
//

#ifndef RDMA_TEST_INCLUDE_RDMA_POLL_H_
#define RDMA_TEST_INCLUDE_RDMA_POLL_H_

#include "rdma_predefine.h"
#include "rdma_structure.h"

<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
=======
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <cstdint>
#include <cinttypes>
>>>>>>> 0e0992a012c0911bb5008d41f572f1ab49323ebd

#include <sys/time.h>
#include <arpa/inet.h>
#include <infiniband/verbs.h>
#include <sys/socket.h>
#include <netdb.h>

/******************************************************************************
* Function: poll_completion
*
* Input
* res pointer to resources structure
*
* Output
* none
*
* Returns
* 0 on success, 1 on failure
*
* Description
* Poll the completion queue for a single event. This function will continue to
* poll the queue until MAX_POLL_CQ_TIMEOUT milliseconds have passed.
*
******************************************************************************/
static int poll_completion(struct resources *res) {
<<<<<<< HEAD
  struct ibv_wc wc;
  unsigned long start_time_msec;
  unsigned long cur_time_msec;
  struct timeval cur_time;
=======
  ibv_wc wc{};
  unsigned long start_time_msec;
  unsigned long cur_time_msec;
  timeval cur_time{};
>>>>>>> 0e0992a012c0911bb5008d41f572f1ab49323ebd
  int poll_result;
  int rc = 0;


  /* poll the completion for a while before giving up of doing it .. */
<<<<<<< HEAD
  gettimeofday(&cur_time, NULL);
  start_time_msec = (cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000);
  do {
    poll_result = ibv_poll_cq(res->cq, 1, &wc);
    gettimeofday(&cur_time, NULL);
=======
  gettimeofday(&cur_time, nullptr);
  start_time_msec = (cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000);
  do {
    poll_result = ibv_poll_cq(res->cq, 1, &wc);
    gettimeofday(&cur_time, nullptr);
>>>>>>> 0e0992a012c0911bb5008d41f572f1ab49323ebd
    cur_time_msec = (cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000);
  } while ((poll_result == 0) && ((cur_time_msec - start_time_msec) < kMaxPollCqTimeout));


  if (poll_result < 0) {
    /* poll CQ failed */
    fprintf(stderr, "poll CQ failed\n");
    rc = 1;
  } else if (poll_result == 0) { /* the CQ is empty */
    fprintf(stderr, "completion wasn't found in the CQ after timeout\n");
    rc = 1;
  } else {
    /* CQE found */
    fprintf(stdout, "completion was found in CQ with status 0x%x\n", wc.status);
    /* check the completion status (here we don't care about the completion opcode */
    if (wc.status != IBV_WC_SUCCESS) {
      fprintf(stderr,
              "got bad completion with status: 0x%x, vendor syndrome: 0x%x\n", wc.status,
              wc.vendor_err);
      rc = 1;
    }
  }
  return rc;
}

/******************************************************************************
* Function: post_send
*
* Input
* res pointer to resources structure
* opcode IBV_WR_SEND, IBV_WR_RDMA_READ or IBV_WR_RDMA_WRITE
*
* Output
* none
*
* Returns
* 0 on success, error code on failure
*
* Description
* This function will create and post a send work request
******************************************************************************/
static int post_send(struct resources *res, int opcode) {
  struct ibv_send_wr sr;
  struct ibv_sge sge;
  struct ibv_send_wr *bad_wr = NULL;
  int rc;


  /* prepare the scatter/gather entry */
  memset(&sge, 0, sizeof(sge));
  sge.addr = (uintptr_t) res->buf;
  sge.length = kMemSize;
  sge.lkey = res->mr->lkey;


  /* prepare the send work request */
  memset(&sr, 0, sizeof(sr));
<<<<<<< HEAD
  sr.next = NULL;
  sr.wr_id = 0;
  sr.sg_list = &sge;
  sr.num_sge = 1;
  sr.opcode = opcode;
=======
  sr.next = nullptr;
  sr.wr_id = 0;
  sr.sg_list = &sge;
  sr.num_sge = 1;
  sr.opcode = static_cast<ibv_wr_opcode>(opcode);
>>>>>>> 0e0992a012c0911bb5008d41f572f1ab49323ebd
  sr.send_flags = IBV_SEND_SIGNALED;
  if (opcode != IBV_WR_SEND) {
    sr.wr.rdma.remote_addr = res->remote_props.addr;
    sr.wr.rdma.rkey = res->remote_props.rkey;
  }


<<<<<<< HEAD
  /* there is a Send Request in the responder side,
=======
  /* there is a Receive Request in the responder side,
>>>>>>> 0e0992a012c0911bb5008d41f572f1ab49323ebd
   * so we won't get any into RNR flow */
  rc = ibv_post_send(res->qp, &sr, &bad_wr);
  if (rc)
    fprintf(stderr, "failed to post SR\n");
  else {
    switch (opcode) {
      case IBV_WR_SEND:
        fprintf(stdout, "Send Request was posted\n");
        break;
      case IBV_WR_RDMA_READ:
        fprintf(stdout, "RDMA Read Request was posted\n");
        break;
      case IBV_WR_RDMA_WRITE:
        fprintf(stdout, "RDMA Write Request was posted\n");
        break;
      default:
        fprintf(stdout, "Unknown Request was posted\n");
        break;
    }
  }
  return rc;
}

/******************************************************************************
* Function: post_receive
*
* Input
* res pointer to resources structure
*
* Output
* none
*
* Returns
* 0 on success, error code on failure
*
* Description
*
******************************************************************************/
static int post_receive(struct resources *res) {
<<<<<<< HEAD
  struct ibv_recv_wr rr;
  struct ibv_sge sge;
=======
  ibv_recv_wr rr{};
  ibv_sge sge{};
>>>>>>> 0e0992a012c0911bb5008d41f572f1ab49323ebd
  struct ibv_recv_wr *bad_wr;
  int rc;

  /* prepare the scatter/gather entry */
  memset(&sge, 0, sizeof(sge));
  sge.addr = (uintptr_t) res->buf;
  sge.length = kMemSize;
  sge.lkey = res->mr->lkey;

  /* prepare the receive work request */
  memset(&rr, 0, sizeof(rr));
<<<<<<< HEAD
  rr.next = NULL;
=======
  rr.next = nullptr;
>>>>>>> 0e0992a012c0911bb5008d41f572f1ab49323ebd
  rr.wr_id = 0;
  rr.sg_list = &sge;
  rr.num_sge = 1;

  /* post the Receive Request to the RQ */
  rc = ibv_post_recv(res->qp, &rr, &bad_wr);
  if (rc)
    fprintf(stderr, "failed to post RR\n");
  else
    fprintf(stdout, "Receive Request was posted\n");
  return rc;
}

#endif //RDMA_TEST_INCLUDE_RDMA_POLL_H_
