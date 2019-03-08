#include "hashfunctions.h"

int hashdiv(std::string str, int m ) {

    
    int soma = 0; // valor total da 'soma' da string
    int p = 0; // valor da tabela ascii do caractere
    int posicao = 0; // Posição da string no vetor de listas ligadas de strings

    for (char c : str){
        p = c;
        soma = soma + p;
    }
    
    posicao = soma%(m);


    return posicao;
    
    
    
}//hashdiv

// convenience function to fix the size to 29
int hashdiv29(std::string str) {
    return hashdiv(str,29);
}


