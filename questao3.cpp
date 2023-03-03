#include <iostream>
#include <immintrin.h>

using namespace std;

void FMAS_int(int v1[], int v2[], int v3[], int res[]){
    cout << "Primeiro Vetor:\t";
    for (int i = 0; i < 8; i++)
        cin >> v1[i];
    cout << "Segundo Vetor:\t";
    for (int i = 0; i < 8; i++)
        cin >> v2[i];
    cout << "Terceiro Vetor:\t";
    for (int i = 0; i < 8; i++)
        cin >> v3[i];
    
    __m256i vI1,vI2,vI3, vIMult, vIResAdd, vIResSub;

    __m256i maskStoreAdd = _mm256_setr_epi32(1, -1, 1, -1, 1, -1, 1, -1);
    __m256i maskStoreSub = _mm256_setr_epi32(-1, 1, -1, 1, -1, 1, -1, 1);

    vI1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(v1));
    vI2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(v2));
    vI3 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(v3));

    vIMult = _mm256_mullo_epi32(vI1, vI2);
    vIResAdd = _mm256_add_epi32(vIMult, vI3);
    vIResSub = _mm256_sub_epi32(vIMult, vI3);

    _mm256_maskstore_epi32(res, maskStoreAdd, vIResAdd);
    _mm256_maskstore_epi32(res, maskStoreSub, vIResSub);
}

void FMAS_float(float v1[], float v2[], float v3[], float res[]){
    cout << "Primeiro Vetor:\t";
    for (int i = 0; i < 8; i++)
        cin >> v1[i];
    cout << "Segundo Vetor:\t";
    for (int i = 0; i < 8; i++)
        cin >> v2[i];
    cout << "Terceiro Vetor:\t";
    for (int i = 0; i < 8; i++)
        cin >> v3[i];

    __m256 vF1,vF2,vF3, vFRes;

    vF1 = _mm256_load_ps(v1);
    vF2 = _mm256_load_ps(v2);
    vF3 = _mm256_load_ps(v3);

    vFRes = _mm256_fmaddsub_ps(vF1,vF2,vF3);

    _mm256_store_ps(res, vFRes);

}

void FMAS_double(double v1[], double v2[], double v3[], double res[]){
    cout << "Primeiro Vetor:\t";
    for (int i = 0; i < 4; i++)
        cin >> v1[i];
    cout << "Segundo Vetor:\t";
    for (int i = 0; i < 4; i++)
        cin >> v2[i];
    cout << "Terceiro Vetor:\t";
    for (int i = 0; i < 4; i++)
        cin >> v3[i];

    __m256d vD1,vD2,vD3, vDRes;

    vD1 = _mm256_load_pd(v1);
    vD2 = _mm256_load_pd(v2);
    vD3 = _mm256_load_pd(v3);

    vDRes = _mm256_fmaddsub_pd(vD1,vD2,vD3);

    _mm256_store_pd(res, vDRes);
}

int main() {
    alignas(32) int vInt1[8], vInt2[8], vInt3[8], vIntRes[8];
    alignas(32) float vFloat1[8], vFloat2[8], vFloat3[8], vFloatRes[8];
    alignas(64) double vDouble1[4], vDouble2[4], vDouble3[4], vDoubleRes[4];
    int opcao;

    cout << "Qual será o tipo de entrada?\n1- Inteiro\n2- Float\n3- Double\nDigite um número: ";
    cin >> opcao;

    switch(opcao){
        case 1:
            FMAS_int(vInt1, vInt2, vInt3, vIntRes);
            for (int i = 0; i < 8; i++)
                cout << vIntRes[i] << " ";
            break;
        case 2:
            FMAS_float(vFloat1, vFloat2, vFloat3, vFloatRes);
            for (int i = 0; i < 8; i++)
                cout << vFloatRes[i] << " ";
            break;
        case 3:
            FMAS_double(vDouble1, vDouble2, vDouble3, vDoubleRes);
            for (int i = 0; i < 4; i++)
                cout << vDoubleRes[i] << " ";
            break;
        default:
            cout << "Opção Inválida";
    }


    cout << endl;
    return 0;
}