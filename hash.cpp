#include "hash.h"
#include "hashfunctions.h"


// LOOK FOR THE COMMENTS IN THE .H 
// TO UNDERSTAND WHAT EACH FUNCTION MUST DO

Hash::Hash(int tablesize, int (*hf) (std::string) ) {
 // CONSTRUTOR 
    _hash_func = hf;
    _table.resize(tablesize);
}

int Hash::add(std::string str) { 
    int contem, ncol;
    contem = this->contains(str, ncol);
    if(contem){
        return ncol;
    }else{
        _table[this->hash(str)].push_front(str);
        return ncol;
    }
    
}//add


int Hash::hash(std::string str) {
    int result =  (*_hash_func)(str);
    return result;
}//hash
    
int Hash::contains(std::string str, int &collisions) { 
    //Acessar a posição equivalente da string no vetor de listas ligadas
    int posic = 0;
    int ncol = 0; // numero de colisões
    posic = this->hash(str);
    collisions = 0;

    if(_table[posic].empty()){
        collisions = 0;
        return 0;
    }else{
        for(std::string test : _table[posic]){
            collisions++;
            if(str.compare(test)==0){
                return 1;
            }
        }
    }  
}//contains


int Hash::worst_case(){
    int tam = this->_table.size();
    int maior = 0;
    int cont = 0;
    for(int x=0; x<tam; x++){
        cont = 0;
        if(!this->_table[x].empty()){
            for(std::string x: this->_table[x]){
                cont++;
            }
        }
        if(cont > maior){
            maior = cont;
        }
    }
    return maior;
    
}//worst_case