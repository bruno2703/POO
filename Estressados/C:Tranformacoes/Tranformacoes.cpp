#include <iostream>
#include <algorithm>
#include <vector>
#include "aux.hpp"
using namespace aux;
using namespace std;

std::vector<int> get_men(std::vector<int> vet){

    std::vector<int> mans;

    for(int i{0}; vet.size() > i; i++){
        if(vet[i]>0) mans.push_back(vet[i]);
    }

    return mans;
}; // todo 

std::vector<int> get_calm_women(std::vector<int> vet){

    std::vector<int> vetor;

    for(int i{0}; vet.size() > i; i++){
        if(vet[i]<0 && vet[i]>-10) vetor.push_back(vet[i]) ;
    }

    return vetor;
}; // todo 

std::vector<int> sort(std::vector<int> vet){

  int size = vet.size();

  for (int step = 0; step < size; ++step) {

    for (int i = 0; i < size - step; ++i) {

      if (vet[i] > vet[i + 1]) {
        int temp = vet[i];
        vet[i] = vet[i + 1];
        vet[i + 1] = temp;
      }
    }
  }
  return vet;
};


std::vector<int> sort_stress(std::vector<int> vet) { 
    
    int size = vet.size();
    size--;
    
    for(int element=0;element<size;++element){
        
        for(int i=0;i<size-element;++i){
            
            if(abs(vet[i]) > abs(vet[i+1])){
                int x = vet[i];
                vet[i] = vet[i+1];
                vet[i+1] = x;
            }
        }
    }
    return vet;
}
 

std::vector<int> reverse(std::vector<int> vet); // todo 

void reverse_inplace(std::vector<int> &vet); // todo 

std::vector<int> unique(std::vector<int> vet); // todo 

std::vector<int> repeated(std::vector<int> vet); // todo 



//loop principal
int main(){
    Chain chain;
    Param ui;

    chain["get_men"]         = [&] { show <<        get_men(to_vet<int>(ui[1])); };
    chain["get_calm_women"]  = [&] { show << get_calm_women(to_vet<int>(ui[1])); };
    chain["sort"]            = [&] { show <<           sort(to_vet<int>(ui[1])); };
    chain["sort_stress"]     = [&] { show <<    sort_stress(to_vet<int>(ui[1])); };
    chain["reverse"]         = [&] { show <<        reverse(to_vet<int>(ui[1])); };
    chain["reverse_inplace"] = [&] { 
        auto vet = to_vet<int>(ui[1]);
        reverse_inplace(vet);
        show << (vet);
    };
    chain["unique"]          = [&] { show <<         unique(to_vet<int>(ui[1])); };
    chain["repeated"]        = [&] { show <<       repeated(to_vet<int>(ui[1])); };

    execute(chain, ui);
}
