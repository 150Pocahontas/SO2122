//client
#include "include/sdstore.h"

int main(int argc, char** argv){
  int pid, res, fd_write_cs, fd_read_sc;
  char buf[MAX_LINE_SIZE];

  bzero(buf, MAX_LINE_SIZE * sizeof(char));

  if((pid = fork()) == 0){

    if((fd_write_cs = open("fifo_cs",O_WRONLY)) == -1){
      perror("open");
      return -1;
    }

    if(argc == 1){
      write(fd_write_cs,"info",strlen("info"));
    }else if(argc == 2){
      write(fd_write_cs,argv[1],strlen(argv[1]));
    }else if(argc > 2){
      for (int i = 1; i<argc;i++){
        write(fd_write_cs,argv[i],strlen(argv[i]));
        write(fd_write_cs," ",strlen(" "));
      }
    }
    close(fd_write_cs);
    _exit(0);
  }else{
    if((fd_read_sc = open("fifo_sc",O_RDONLY)) == -1){
      perror("open");
      return -1;
    }
    while((res = readln(fd_read_sc,buf,MAX_LINE_SIZE)) > 0){
      if(strcmp(buf,EXIT) == 0) {
        if(argc > 2) if(read(fd_read_sc,buf,MAX_LINE_SIZE));

        close(fd_read_sc);
        return 1;
      }else{
        write(1,buf,res);
        bzero(buf, MAX_LINE_SIZE * sizeof(char));
      }
    }
  }
  return 0;
}
