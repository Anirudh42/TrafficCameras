#include "minisat/core/Solver.h"
#include "minisat/core/SolverTypes.h"
#include <iostream>
#include <vector>
#include "FindVertexCover.h"
#include <memory>
#include <algorithm>
#include<stdlib.h>
struct params{
  int fixedsize;
  std::vector<int> edges;
  std::vector<int> vertices;
};
void* MinVertexCover(void* parameters)
{
  struct params* p=(struct params*)parameters;
  using Minisat::lbool;
  std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
  //Minisat::Solver solver;
  std::vector<int> result;
  int lo=0;
  int hi=p->fixedsize;
  int k=(lo+hi)/2;
while(lo<=hi){
  //Minisat::Solver solver;
  //std::vector<std::vector<Minisat::Lit>> arr(p->fixedsize+1);
  Minisat::Lit arr[p->fixedsize+1][p->fixedsize+1];
  for(int i=0;i<p->fixedsize+1;i++){
    for(int j=0;j<p->fixedsize+1;j++){
      // Minisat::Lit a=Minisat::mkLit(solver->newVar());
      // arr[i].push_back(a);
      arr[i][j]=Minisat::mkLit(solver->newVar());
    }
  }
  for(int i=0;i<k;i++){
    Minisat::vec<Minisat::Lit> literals_vertex;
    for(int j=0;j<p->fixedsize;j++){
      literals_vertex.push(arr[j][i]);
    }
    solver->addClause(literals_vertex);
  }


  for(int m=0;m<p->fixedsize;m++){
    for(int p=0;p<k;p++){
      for(int q=p+1;q<k;q++){
        solver->addClause(~arr[m][p],~arr[m][q]);
      }
    }
  }


  for(int m=0;m<k;m++){
    for(int p1=0;p1<p->fixedsize;p1++){
      for(int q=p1+1;q<p->fixedsize;q++){
        solver->addClause(~arr[p1][m],~arr[q][m]);
      }
    }
  }

  for(unsigned int i=0;i<p->edges.size()-1;i=i+2){
    Minisat::vec<Minisat::Lit> literals;
    for(int j=0;j<k;j++){
      literals.push(arr[p->edges[i]][j]);
      literals.push(arr[p->edges[i+1]][j]);
    }
    solver->addClause(literals);
  }
  bool sat = solver->solve();
  if(sat){
    result.clear();
    for(int i=0;i<p->fixedsize;i++){
      for(int j=0;j<k;j++){
        if(solver->modelValue(arr[i][j])==Minisat::l_True){
          result.push_back(i);
        }
      }
    }
    hi=k-1;
  }
  else{
    lo=k+1;
    solver.reset(new Minisat::Solver());
    }
  //k++;
  k=(lo+hi)/2;

}
std::sort(result.begin(),result.end());
for(unsigned int i=0;i<result.size();i++){
  if(i==result.size()-1){
    std::cout<<result[i]<<"\n";
  }
  else{
  std::cout<<result[i]<<",";
}
}

return NULL;
}
