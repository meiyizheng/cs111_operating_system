#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

int main(int argc, char * argv[]) {
  int opt = 0;
  int option_index = 0;
  char *string = "c:";
  
  static struct option long_options[] = {
					
       
					 {"command", required_argument, NULL, 'c'},
					 {0, 0, 0,  0}
  };

  while(1) {
    opt = getopt_long(argc, argv, string, long_options, &option_index);
