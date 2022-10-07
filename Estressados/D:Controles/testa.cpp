#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "aux.hpp"
using namespace aux;
using namespace std;

int mais_ocorrencias(const std::vector<int>& vet) {
    int maior_ocorrencia{0};

    for (size_t i{0}; i < vet.size(); i++) {
        int elem = (vet[i] < 0) ? -vet[i] : vet[i];
        int occur{1};

        for (size_t j{i+1}; j < vet.size(); j++) {
            int elem2 = (vet[j] < 0) ? -vet[j] : vet[j];
            if (elem == elem2) {
                occur += 1;
            }
        }
        if (occur > maior_ocorrencia) {
            maior_ocorrencia = occur;
        }
    }
    return maior_ocorrencia;
}

std::vector<int> mais_recorrentes(const std::vector<int>& vet) {
    int maior_ocorrencia{mais_ocorrencias(vet)};
    std::vector<int> recorrentes;
    for (size_t i{0}; i < vet.size(); i++) {
        int elem = (vet[i] < 0) ? -vet[i] : vet[i];
        int occur{1};
        for (size_t j{i+1}; j < vet.size(); j++) {
            int elem2 = (vet[j] < 0) ? -vet[j] : vet[j];
            if (elem == elem2) {
                occur += 1;
            }
        }
        if (occur == maior_ocorrencia) {
            recorrentes.push_back(elem);
        }
    }
    return recorrentes;
}

int main(){

    vector<int> vetor{2, 39, -1, -19, 2, 2, -1};
    vector<int> VV{2, 39, -1, -19, 2, 2, -1};

    int V = mais_ocorrencias(vetor);
    vector<int> X = mais_recorrentes(VV);

    for(size_t i{0}; i < X.size(); i++)
     {
        cout<< X[i] << " ";
     }
     
    return 0;
}