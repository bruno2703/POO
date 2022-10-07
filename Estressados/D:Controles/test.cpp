#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "aux.hpp"
using namespace aux;
using namespace std;

std::vector<int> sort_stress(std::vector<int> vet)
{ 
    int size = vet.size();
    size--;
    for(int element=0;element<size;++element)
    {    
        for(int i=0;i<size-element;++i)
        {    
            if(abs(vet[i]) > abs(vet[i+1]))
            {
                int x = vet[i];
                vet[i] = vet[i+1];
                vet[i+1] = x;
            }
        }
    }
    return vet;
}

std::vector<std::pair<int, int>> occurr(std::vector<int> vet) {

    vector<int> lista;
    vet = sort_stress(vet);

    for(int i{0}; vet.size() > i; i++){
        ;
    }
    
    return {}; // todo
}

std::vector<std::pair<int, int>> teams(std::vector<int> vet) {
    return {}; // todo
}

std::vector<int> mnext(std::vector<int> vet) {
    return {}; // todo
}

std::vector<int> alone(std::vector<int> vet) {
    return {}; // todo
}

int couple(std::vector<int> vet) {
    return {}; // todo
}

bool has_subseq(std::vector<int> vet, std::vector<int> seq, int pos) {
    return {}; // todo
}

int subseq(std::vector<int> vet, std::vector<int> seq) {
    return {}; // todo
}

std::vector<int> erase(std::vector<int> vet, std::vector<int> pos_list) {
    return {}; // todo
}

std::vector<int> clear(std::vector<int> vet, int value) {
    return {}; // todo
}

int main(){

    vector<pair<int, int>>MM{2,5}:{3,7};

    cout << MM[0] <<"\n";

    return 0;
}