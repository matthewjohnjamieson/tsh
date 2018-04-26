void terminate(pid_t pid){
    int ret;
    if (ret = kill(pid, SIGINT) == 0) {
          deleteNodePid(pid);
    }
     else{
       //kill() has returned -1
       fprintf(stderr,"kill() failed.\n");
     }
}
