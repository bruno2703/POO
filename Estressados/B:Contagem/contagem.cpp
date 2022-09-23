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
#include "aux.hpp" 
using namespace aux;



using namespace std;

//as funções abaixo sao de contagem

// essa funcao conta a quantidade de vezes q x apareceu
int count(vector<int> vet, int X){

    int box{0};

    for(int i{0}; i < vet.size(); i++){
        if(vet[i]==X) box++;
    }

    return box;
}

int sum(vector<int> vet){

    int result{0};

    for(int i{0}; i < vet.size(); i++){
        result += abs(vet[i]);
    }
    return result;
}

double average(vector<int> vet){

    double media{0};
    for(int i{0}; i < vet.size(); i++){
        media += abs(vet[i]);
    } 
    media = media/vet.size();
    return media;
}

string half_compare(vector<int> vet){

    size_t const half_size = (vet.size() / 2);
    int metade1{0}, metade2{0};

    int i;
    for(i=0; i < half_size; i++){
        metade1 += abs(vet[i]);
    }  

    for(i; i < vet.size(); i++){
        metade2 += abs(vet[i]);
    }  

    string resposta;
    if(metade1==metade2){
        resposta = "draw";
    }
    else if(metade1>metade2){
        resposta = "first";
    }
    else{
        resposta = "second";
    }

    return resposta;
}

string more_men(vector<int> vet){

    int women{0}, men{0};

    for(int i{0}; i< vet.size(); i++){

        if(vet[i]>0){
            men++;
        }
        else{
            women++;
        }
    }
    string result;
    if(men==women){
        result ="draw";
    }
    else if(men>women){
        result="men";
    }
    else{
        result="women";
    }
    return result;
}

string sex_battle(vector<int> vet){

    int men{0}, women{0};

    for(int i{0}; i< vet.size(); i++){

        if(vet[i]<0){
            women += abs(vet[i]);
        }
        else{
            men += vet[i];
        }
    }

    string resposta;
     if(men==women){
        resposta = "draw";
     }
     else if(men>women){
        resposta = "men";
     }
     else{
        resposta = "women";
     }

     return resposta;
}


//loop principal
int main(){
    Chain chain;
    Param ui;

    chain["count"]        = [&] { show <<        count(to_vet<int>(ui[1]), to<int>(ui[2])); };
    chain["sum"]          = [&] { show <<          sum(to_vet<int>(ui[1])                ); };
    chain["average"]      = [&] { show <<      average(to_vet<int>(ui[1])                ); };
    chain["more_men"]     = [&] { show <<     more_men(to_vet<int>(ui[1])                ); };
    chain["half_compare"] = [&] { show << half_compare(to_vet<int>(ui[1])                ); };
    chain["sex_battle"]   = [&] { show <<   sex_battle(to_vet<int>(ui[1])                ); };

    execute(chain, ui);
}