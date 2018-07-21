#ifndef LOG2
#define LOG2(x) (log(x)/M_LN2)
#endif

#ifndef ULLI
#define ULLI unsigned long long int
#endif

#ifndef PRIMO
#define PRIMO

#include <math.h>

// LENGTH_PRIMOS == log2(x)
#define LENGTH_PRIMOS(x) LOG2(x)
#define LENGTH_DIVISORES(x) ( LENGTH_PRIMOS(x) * (LENGTH_PRIMOS(x) + 1) ) / 2

typedef struct primo{
    bool *vetor;
    int n;
}PRIMOS;

PRIMOS* criar_primo(int lim);
void destruir_primo(PRIMOS *P);
bool eh_primo_busca(PRIMOS *P, int x);

bool isprime(ULLI n);
bool eh_primo_rec(ULLI num);
static bool _eh_primo_rec(ULLI num, ULLI mod);
bool eh_primo(ULLI num);

#define IS_PRIME(x) eh_primo(x)

ULLI gen_primos_w(bool run);
ULLI gen_primos_2(bool run);

#define GEN_PRIMES(x) gen_primos_2(x)

int* fatores_primos_iter(int n);
int* fatores_primos_gen(int n);

#define FATORES_PRIMOS(x) fatores_primos_gen(x)

int* divisores_lazy(int num);
int* divisores_optm(int num);

#define DIVISORES(x) divisores_optm(x)

/* IMPLEMENTAÇÕES DAS FUNÇÕES */

/*  COM BUSCA  */
PRIMOS* criar_primo(int lim){
    lim++;
    PRIMOS *P = (PRIMOS*) malloc (sizeof(PRIMOS));
    P->vetor = (bool*) calloc (lim, sizeof(bool));
    P->n = lim;
    P->vetor[2] = true;
    for(int i = 3; i < P->n; i+=2) P->vetor[i] = IS_PRIME(i);
    return P;
}
void destruir_primo(PRIMOS *P){
    free(P->vetor);
    free(P);
}
bool eh_primo_busca(PRIMOS *P, int x){
    return P->vetor[x]; 
}
/* FIM */

bool isprime(ULLI n){
    if (n <= 3)
        return true;
    if (n%2 == 0)
        return false;
    if (n%3 == 0)
        return false;

    ULLI i = 5;
    int w = 2;

    while (i * i <= n){
        if (n%i == 0)
            return false;
        i += w;             
        w = 6 - w;          
    }
    return true;
}
bool eh_primo_rec(ULLI num){
    return _eh_primo_rec(num, 2);
}
static bool _eh_primo_rec(ULLI num, ULLI mod){
    if ( num < mod*mod ) return true;
    if ( num%mod == 0 ) return false;
    return mod == 2 ? _eh_primo_rec(num, 3) : _eh_primo_rec(num, mod+2);
}
bool eh_primo(ULLI num){
    if (num < 2)
        return false;
    if (num < 4)
        return true;
    if (num%2 == 0)
        return false;    
    if (num%3 == 0)
        return false;

    ULLI i = 5;
    int w = 2;

    while(i * i <= num){
        if (num % i == 0)
            return false;
        i += w;
        w = 6 - w;
    }
    return true;
}

/*
 * A variavel run mantem o gerador ligado enquanto true.
 * Se false, reinicia o gerador.
*/
ULLI gen_primos_2(bool run){
    static ULLI i = 2;
    ULLI r ;
    if(run){
        if(i == 2){
            r = i;
            i++;
            return r;
        }
        else{
            while(!IS_PRIME(i)){
                i += 2;
            }
            r = i;
            i += 2;
            return r;
        }
    }
    else{
        i = 2;
    }
}
ULLI gen_primos_w(bool run){
    static ULLI i = 2;
    static int w = 2;
    ULLI r ;
    if(run){
        if(i == 2){
            r = i;
            i++;
            return r;
        }
        if(i == 3){
            r = i;
            i += 2;
            return r;
        }
        if(i > 3){
            while(!IS_PRIME(i)){
                i += w;
                w = 6 - w;
            }
            r = i;
            i += w;
            w = 6 - w;
            return r;
        }
    }
    else{
        i = 2;
        w = 2;
    }
}

int* divisores_lazy(int num){
    // Identifica os divisores sem optimizações Ondem (n)
    int *divs = zeros_array(LENGTH_DIVISORES(num)) ;
    int k = 0;
    for(int i=2; i<=num/2; i++){
        if (num%i == 0){
            divs[k++] = i;
        }
    }
    divs[k++] = num;
    return divs;
}
int* divisores_optm(int num){
    // Encontra os divisores de um número com optimizações 
    int *divs = zeros_array(LENGTH_DIVISORES(num)) ; // MALLOC divs
    int lim = num;
    int k = 0;
    int i, j;
    if(!IS_PRIME(num)){
        for(i=2; i<lim; i++){
            if (num%i == 0){
                divs[k++] = i;
                divs[k++] = num/i;
                lim = num/i;
                if(IS_PRIME(lim)){ // Impede o pior caso Ordem(n)
                    divs[k++] = lim;
                    lim = 0;
                }
            }
        }
    }
    divs[k++] = num;
    unique_array(divs, k);
    return divs;
}

int* fatores_primos_iter(int n){
    // Nao é possível retornar o tamanho do vetor resultante
    // Porém, o tamanho do vetor resultante é dado pela expressão
    //              log(n)/log(2) == log(n)/M_LN2
    //                     log(2) == M_LN2
    int *primos = zeros_array(LENGTH_PRIMOS(n));
    int k = 0;
    int i = 2;
    while(n != 1){
        if(IS_PRIME(i)){
            while(n % i == 0){
                primos[k++] = i;
                n /= i;
            }
            if(IS_PRIME(n)){ // Evita o pior caso
                primos[k++] = n;
                n = 1;
            }
        }
        i++;
    }
    return primos;
}
int* fatores_primos_gen(int n){
    // Nao é possível retornar o tamanho do vetor resultante
    // Porém, o tamanho do vetor resultante é dado pela expressão
    //              log(n)/log(2) == log(n)/M_LN2
    //                     log(2) == M_LN2
    int *primos = zeros_array(LENGTH_PRIMOS(n));
    int k = 0;
    int primo;
    while(n != 1){
        primo = GEN_PRIMES(true);
        while(n % primo == 0){
            primos[k++] = primo;
            n /= primo;
        }
        if(IS_PRIME(n)){ // Evita o pior caso
            primos[k++] = n;
            n = 1;
        }
    }
    GEN_PRIMES(false);
    return primos;
}

#endif