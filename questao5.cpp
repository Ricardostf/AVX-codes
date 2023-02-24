#include <iostream>
#include <fstream>
#include <immintrin.h>
#include <stdio.h>

using namespace std;

void encriptar(){
    ifstream entrada("entrada.txt");
    remove("encriptado.txt");
    ofstream encript("encriptado.txt", ios::app);
    string linha;

    entrada>>linha;
    cout << "Texto Base:\t\t" << linha << endl;
    cout << "Texto encriptado:\t";

    alignas(32) int charParaInt[8];
    int tamVetor = 0;
    int aux;

    __m256i vetorInt;
    __m256i vetorSoma;
    __m256i padraoPermuta = _mm256_setr_epi32(1, 3, 2, 0, 5, 7, 6, 4);

    vetorSoma = _mm256_set1_epi32(123);


    for (int i = 0; i < linha.length(); i++){
        aux = linha[i];
        charParaInt[tamVetor] = aux;
        tamVetor++;

        if (tamVetor == 8){
            tamVetor = 0;
            vetorInt = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(charParaInt));
            vetorInt = _mm256_add_epi32(vetorInt, vetorSoma);
            vetorInt = _mm256_permutevar8x32_epi32(vetorInt, padraoPermuta);

            _mm256_store_si256(reinterpret_cast<__m256i*>(charParaInt), vetorInt);

            for (int j = 0; j < 8; j++){
                cout << charParaInt[j];
                encript << charParaInt[j];
            }
        }
    }
}

void desencriptar(){
    ifstream entrada("encriptado.txt");
    remove("desencriptado.txt");
    ofstream desencript("desencriptado.txt", ios::app);
    string linha;

    entrada>>linha;
    cout << "Texto Desencriptado:\t";

    alignas(32) int charEncriptado[8];
    int tamVetor = 0;
    string aux;

    __m256i vetorInt;
    __m256i vetorSub;
    __m256i padraoPermuta = _mm256_setr_epi32(3, 0, 2, 1, 7, 4, 6, 5);

    vetorSub = _mm256_set1_epi32(123);

    int i;
    for (i = 0; i < linha.length(); i++){
        aux = "";
        aux.append(1,linha[i]);
        aux.append(1,linha[i+1]);
        aux.append(1,linha[i+2]);
        charEncriptado[tamVetor] = stoi(aux);
        tamVetor++;
        i=i+2;

        if (tamVetor == 8){
            tamVetor = 0;
            vetorInt = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(charEncriptado));
            vetorInt = _mm256_sub_epi32(vetorInt, vetorSub);
            vetorInt = _mm256_permutevar8x32_epi32(vetorInt, padraoPermuta);

            _mm256_store_si256(reinterpret_cast<__m256i*>(charEncriptado), vetorInt);

            for (int j = 0; j < 8; j++){
                cout << char(charEncriptado[j]);
                desencript << char(charEncriptado[j]);
            }
        }
    }
}

int main (){

    encriptar();
    cout << endl;
    desencriptar();
    cout << endl;

    return 0;
}