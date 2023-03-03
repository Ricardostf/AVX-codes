#include <iostream>
#include <immintrin.h>

using namespace std;

int main() {
    int linha1, coluna1, linha2, coluna2;
    cout << "Quantidade de linhas da primeira matriz (max 4): ";
    cin >> linha1;
    cout << "Quantidade de colunas da primeira matriz (max 4): ";
    cin >> coluna1;

    cout << "Quantidade de linhas da segunda matriz (max 4): ";
    cin >> linha2;
    cout << "Quantidade de colunas da segunda matriz (max 4): ";
    cin >> coluna2;

    if (linha1 > 4 or coluna1 > 4 or linha2 > 4 or coluna2 > 4) {
        cout << "Foi inserido um valor maior que 4";
    }

    else if (linha1 != linha2 or coluna1 != coluna2) {
        cout << "Não é possível fazer a soma" << endl;
    }

    else {
        /*
        
         Todas tiveram que ser 4x4, pois o _mm256_load_pd pega os 256 bit sequenciais da memória.
         Com matrizes de tamanhos multiplos de 2, seria simples resolver, mas do contrário, eu não tenho nem ideia,
         pois acessaria posições inválidas da memória na primeira iteração da matriz 1x1 ou na terceira da 3x3.
        
        */
        alignas(64) double matriz1[4][4];
        alignas(64) double matriz2[4][4];
        alignas(64) double resultado[4][4];

        cout << "Insira os elementos da primeira matriz:" << endl;
        for (int i = 0; i < linha1; i++) {
            for (int j = 0; j < coluna1; j++) {
                cin >> matriz1[i][j];
            }
        }

        cout << "Insira os elementos da segunda matriz:" << endl;
        for (int i = 0; i < linha1; i++) {
            for (int j = 0; j < coluna1; j++) {
                cin >> matriz2[i][j];
            }
        }

        __m256d linhaM1, linhaM2, soma;
    
        for (int i = 0; i < linha1; i++) {

            linhaM1 = _mm256_load_pd(&matriz1[i][0]);
            linhaM2 = _mm256_load_pd(&matriz2[i][0]);
            soma = _mm256_add_pd(linhaM1, linhaM2);
            _mm256_store_pd(&resultado[i][0], soma);

        }

        cout << "Resultado da soma: \n";
        for (int i = 0; i < linha1; i++) {
            for (int j = 0; j < coluna1; j++) {
                cout << resultado[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}