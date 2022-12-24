void
event_handler(int signum){
    printf("\e[?25h");
    exit(0);
}

