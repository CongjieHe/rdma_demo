//
// Created by wangxinshuo on 2020/11/2.
//

#include <stdio.h>
#include <unistd.h>
<<<<<<< HEAD
#include <infiniband/verbs.h>

int main(int argc, char *argv[]) {
  // int opt;
  // char *string = "a::b:c:d";
  // while ((opt = getopt(argc, argv, string)) != -1) {
  //   printf("opt = %c\t\t", opt);
  //   printf("optarg = %s\t\t", optarg);
  //   printf("optind = %d\t\t", optind);
  //   printf("argv[optind] = %s\n", argv[optind]);
  // }
  // return 0;

  struct ibv_recv_wr *rr;
  printf("%ld", sizeof(rr));
=======

int main(int argc, char *argv[]) {
  int opt;
  char *string = "a::b:c:d";
  while ((opt = getopt(argc, argv, string)) != -1) {
    printf("opt = %c\t\t", opt);
    printf("optarg = %s\t\t", optarg);
    printf("optind = %d\t\t", optind);
    printf("argv[optind] = %s\n", argv[optind]);
  }
  return 0;
>>>>>>> 0e0992a012c0911bb5008d41f572f1ab49323ebd
}