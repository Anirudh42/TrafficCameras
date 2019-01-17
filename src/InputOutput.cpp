
#include "InputOutput.h"
#include<pthread.h>
#include<time.h>
#include<iterator>
#include<iostream>
#include<vector>
#include<regex>
#include<sstream>
#include<string>
#include<stack>
#include<queue>
#include<stdlib.h>

struct params{
  int fixedsize;
  std::vector<int> edges;
  std::vector<int> vertices;
};
void* getInput(void* parameters3){
std::string s;
pthread_t thread_cnfsat;
pthread_t thread_avc1;
pthread_t thread_avc2;
struct params thread_args;
struct params thread_args_avc1;
struct params thread_args_avc2;
while(std::getline(std::cin,s)){

  std::regex reg ("[-]?[0-9][^$]?");
  std::regex regstring("[a-zA-Z]+");
  std::sregex_iterator stringmatch(s.begin(),s.end(),regstring);
  std::smatch matchstring=*stringmatch;
  std::sregex_iterator currentMatch(s.begin(),s.end(),reg);

  std::sregex_iterator lastMatch;

  if(matchstring.str()=="V"){

    int input=0;
    std::stringstream ss((*currentMatch).str());
    ss>>input;
    thread_args.fixedsize=input;

}
  else if(matchstring.str()=="E"){
    int flag=0;
    int input=0;
    thread_args.edges.clear();
    thread_args.vertices.clear();
    while(currentMatch!=lastMatch){
      std::smatch match=*currentMatch;
      std::stringstream ss(match.str());
      ss>>input;
      if(input<thread_args.fixedsize){
        thread_args.edges.push_back(input);
        currentMatch++;
      }
      else{
        std::cerr<<"Error: Enter Vertex ID only upto "<<(thread_args.fixedsize)-1<<std::endl;
        flag=1;
        break;
      }

    }
    if(flag==0){
      for(unsigned int i=0;i<thread_args.edges.size();i++){
          if(std::find(thread_args.vertices.begin(),thread_args.vertices.end(),thread_args.edges[i])!=thread_args.vertices.end()){
            continue;
          }else{
            thread_args.vertices.push_back(thread_args.edges[i]);
        }
        }
        thread_args_avc1=(struct params)thread_args;
        thread_args_avc2=(struct params)thread_args;
    std::sort(thread_args.vertices.begin(),thread_args.vertices.end());
    std::cout<<"CNF-SAT-VC: ";
    pthread_create(&thread_cnfsat,NULL,&MinVertexCover,&thread_args);
    pthread_join(thread_cnfsat,NULL);
    std::cout<<"APPROX-VC-1: ";
    pthread_create(&thread_avc1,NULL,&getVertexCover1,&thread_args_avc1);
    pthread_join(thread_avc1,NULL);
    std::cout<<"APPROX-VC-2: ";
    pthread_create(&thread_avc2,NULL,&getVertexCover2,&thread_args_avc2);
    pthread_join(thread_avc2,NULL);

}
}}
return NULL;
}
