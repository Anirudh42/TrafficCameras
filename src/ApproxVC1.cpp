#include "ApproxVC1.h"
#include "AllEdges.h"
#include <iostream>
#include<vector>
#include<regex>
#include<sstream>
#include<string>
#include<stack>
#include<queue>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
struct params{
  int fixedsize;
  std::vector<int> edges;
  std::vector<int> vertices;
};
std::vector<int> minvc1;
Adjacency** arr1;
Vertex** vertexobjs1;
void* getVertexCover1(void* parameters2){
  struct params* p2=(struct params*) parameters2;
  int max_vertex=9999;
  int max_degree=-1;
  arr1=new Adjacency*[p2->fixedsize+1];
  vertexobjs1=new Vertex*[p2->fixedsize+1];
  calculateEdges(vertexobjs1,arr1,p2->vertices,p2->edges);
  std::vector<int>edges_temp;
  std::vector<int>vertices_temp;
  for(unsigned int i=0;i<p2->vertices.size();i++)
  {
    int temp=arr1[p2->vertices[i]]->getSize();
    if(temp>max_degree){
      max_degree=temp;
      max_vertex=arr1[p2->vertices[i]]->getVertex(p2->vertices[i])->getValue();
    }
  }
  minvc1.push_back(max_vertex);
  for(unsigned int i=0;i<p2->edges.size();i=i+2){
    if(p2->edges[i]!=max_vertex){
      if(p2->edges[i+1]!=max_vertex){
        edges_temp.push_back(p2->edges[i]);
        edges_temp.push_back(p2->edges[i+1]);
      }
    }
  }
  for(unsigned int i=0;i<p2->vertices.size();i++){
    delete vertexobjs1[p2->vertices[i]];
    delete arr1[p2->vertices[i]];
  }
  delete[] vertexobjs1;
  delete[] arr1;
  for(unsigned int i=0;i<edges_temp.size();i++){
      if(std::find(vertices_temp.begin(),vertices_temp.end(),edges_temp[i])!=vertices_temp.end()){
        continue;
      }else{
        vertices_temp.push_back(edges_temp[i]);
    }
     }
     std::sort(vertices_temp.begin(),vertices_temp.end());
    if(edges_temp.size()!=0){
      p2->vertices=vertices_temp;
      p2->edges=edges_temp;
      getVertexCover1(p2);
  }
  else if(edges_temp.size()==0){
    std::sort(minvc1.begin(),minvc1.end());
    for(unsigned int i=0;i<minvc1.size();i++){
      if(i==minvc1.size()-1){
        std::cout<<minvc1[i];
      }
      else{
      std::cout<<minvc1[i]<<",";
    }
    }
    std::cout<<"\n";
    minvc1.clear();
    return NULL;
  }
  return NULL;
}
