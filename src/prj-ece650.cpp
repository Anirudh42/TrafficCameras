
#include "InputOutput.h"
#include<pthread.h>
#include<iterator>
#include<stdio.h>
#include<errno.h>
#include<time.h>
#include<iostream>
#include<vector>
#include<regex>
#include<sstream>
#include<string>
#include<stack>
#include<queue>
#include<stdlib.h>
#include<unistd.h>
#include<ctime>
int main(void) {
    pthread_t thread_io;
    pthread_create(&thread_io,NULL,&getInput,NULL);
    pthread_join(thread_io,NULL);


    return 0;
}
