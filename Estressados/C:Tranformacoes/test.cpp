#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include "aux.hpp"
#include <bits/stdc++.h>
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
 
std::vector<int> reverse(std::vector<int> vet){

    int size = vet.size();
    vector<int> list;

    for(int i{1}; i<=size; i++){
        list.push_back(vet[size-i]);
    }

    return list;
}; // todo 

void reverse_inplace(std::vector<int> &vet){

    std::reverse(vet.begin(), vet.end());

}; // todo 

std::vector<int> unique(std::vector<int> vet){
    
    vector<int> vector; 
    int size = vet.size();

    sort(vet.begin(), vet.end(), greater<int>());
    vector = vet;
    int C{-1};

    for(int i{0}; i<size; i++){

        if(vet[i] == vet[i+1]){

            int x=i+1;
            int prox = vet[x];
            while(vet[x] == prox){
                x++;
            }
            vet[i+1] = vet[x];
            C++;
        }
    }

    vet.resize(std::distance(vector.begin(), (vector.end() - C)));

    return vet;
}; // todo 

std::vector<int> repeated(std::vector<int> vet){

    vector<int> vetor;
    int size = vet.size();

    for(int i{0}; i<size; i++){

        for(int Z{i+1}; Z<size; Z++)
        {
            if(vet[i] == vet[Z]){
                vetor.push_back(vet[i]);
            }
        }
    }


    return vetor;
}; // todo 

int main(){

    vector<int> myList{5,3,1,1,3,2};

    myList = repeated(myList); 

    for (auto i = myList.begin(); i != myList.end(); i++)
      cout << *i << " ";

    return 0;
}