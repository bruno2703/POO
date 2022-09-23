/*
1)
Fiz tudo só
2)
Não entendi direito como usa stringstream
3)
8 horas total dividida entre alguns dias
*/

#include <iostream>
#include <vector>
#include "aux.hpp" // https://raw.githubusercontent.com/senapk/cppaux/master/aux.hpp
using namespace aux;

using namespace std;

//As funções abaixo sao de busca

//Função pra encontrar um valor no array
bool in(vector<int> vet, int value){

    for(int i=0; i < vet.size(); i++){
        if(value == vet[i]){
            int achado = vet[i];
            return true;
        };
    }
    return false;
}

//Qual posicao aparece x pela primeira vez
int index_of(vector<int> vet, int value){

    for(int i=0; i < vet.size(); i++){
        if(value == vet[i]){
            int achado = vet[i];
            return i;
        };
    }
    return -1;
}

//Qual posicao do primeiro homem na fila
int find_if(vector<int> vet){

    for(int i=0; i < vet.size(); i++){
        if( 0 < vet[i] ){
            int achado = vet[i];
            return i;
        };
    }
    return -1;
}


//retorna a posicao do menor valor na lista
int min_element(vector<int> vet){

    if(vet.empty()){
        return -1;
    }
    else{
        int menor = vet[0];
        for(int i=0; i < vet.size(); i++){
            if(menor > vet[i]){
                menor = vet[i];
            };
    } 
    int result = index_of(vet,menor);
    return result;
    }
}


//retorna posicao do menor positivo
int find_min_if(vector<int> vet){

   int i{0}, mais{0};

    for( i; i < vet.size(); i++){
        if( (vet[i]>0) ){
            mais = vet[i];
        }
    }

    for( i=0; i < vet.size(); i++){
        if( (vet[i]>0) && (vet[i]<mais)){
            mais = vet[i];
        }
    }

    int resposta = index_of(vet, mais);
    return resposta;
}



//loop principal
int main(){
    Chain chain;
    Param ui;

    chain["in"]           = [&] { show <<          in(to_vet<int>(ui[1]), to<int>(ui[2])); };
    chain["index_of"]     = [&] { show <<    index_of(to_vet<int>(ui[1]), to<int>(ui[2])); };
    chain["find_if"]      = [&] { show <<     find_if(to_vet<int>(ui[1])                ); };
    chain["min_element"]  = [&] { show << min_element(to_vet<int>(ui[1])                ); };
    chain["find_min_if"]  = [&] { show << find_min_if(to_vet<int>(ui[1])                ); };

    execute(chain, ui);
}