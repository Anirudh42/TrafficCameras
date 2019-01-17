#include "ApproxVC2.h"
#include "AllEdges.h"
#include <iostream>
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
std::vector<int> minvc;
Adjacency** arr;
Vertex** vertexobjs;
void* getVertexCover2(void* parameters1){
  struct params* p1=(struct params*)parameters1;
  arr=new Adjacency*[p1->fixedsize+1];
  vertexobjs=new Vertex*[p1->fixedsize+1];
  calculateEdges(vertexobjs,arr,p1->vertices,p1->edges);
  std::vector<int>edges_temp;
  std::vector<int>vertices_temp;
  minvc.push_back(p1->edges[0]);
  minvc.push_back(p1->edges[1]);
  for(unsigned int i=0;i<p1->edges.size();i=i+2){
    if(p1->edges[i]!=p1->edges[0]&&p1->edges[i]!=p1->edges[1]){
      if(p1->edges[i+1]!=p1->edges[0]&&p1->edges[i+1]!=p1->edges[1]){
        edges_temp.push_back(p1->edges[i]);
        edges_temp.push_back(p1->edges[i+1]);
      }
    }
  }
  for(unsigned int i=0;i<p1->vertices.size();i++){
    delete vertexobjs[p1->vertices[i]];
    delete arr[p1->vertices[i]];
  }
  delete[] vertexobjs;
  delete[] arr;
  for(unsigned int i=0;i<edges_temp.size();i++){
      if(std::find(vertices_temp.begin(),vertices_temp.end(),edges_temp[i])!=vertices_temp.end()){
        continue;
      }else{
        vertices_temp.push_back(edges_temp[i]);
    }
     }
     std::sort(vertices_temp.begin(),vertices_temp.end());
    if(edges_temp.size()!=0){
      p1->vertices=vertices_temp;
      p1->edges=edges_temp;
    getVertexCover2(p1);
  }
  else if(edges_temp.size()==0){
    std::sort(minvc.begin(),minvc.end());
    for(unsigned int i=0;i<minvc.size();i++){
      if(i==minvc.size()-1){
        std::cout<<minvc[i];
      }
      else{
      std::cout<<minvc[i]<<",";
    }
    }
    std::cout<<"\n";
    minvc.clear();
    return NULL;
  }
  return NULL;
}
