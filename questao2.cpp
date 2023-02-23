#include <iostream>
#include <immintrin.h>
#include <stdio.h>

using namespace std;

int main() {

    int escalar;
    cout << "Digite o valor do escalar: ";
    cin >> escalar;

    alignas(32) float vetorX[8] = {1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1};
    alignas(32) float vetorY[8] = {4.1, 3.1, 5.1, 1.1, 0.1, 6.1, 2.1, 7.1};

    __m256 X = _mm256_load_ps(vetorX);
    __m256 Y = _mm256_load_ps(vetorY);
    __m256 a = _mm256_set1_ps(escalar);

    __m256 resultado = _mm256_fmadd_ps(a, X, Y);

    alignas(32) float res[8];
    _mm256_store_ps(res, resultado);

    cout << "Resultado: ";
    for(int i = 0; i < 8; i++){
        cout << res[i] << " ";
    }
    cout << endl;



    

    // float* res = (float*)&X;

    // cout << "Imprimindo X: ";
    // for(int i = 0; i < 8; i++){
    //     cout << res[i] << " ";
    // }
    // cout << endl;

    // res = (float*)&Y;
    // cout << "Imprimindo Y: ";
    // for(int i = 0; i < 8; i++){
    //     cout << res[i] << " ";
    // }
    // cout << endl;

    // res = (float*)&a;
    // cout << "Imprimindo a: ";
    // for(int i = 0; i < 8; i++){
    //     cout << res[i] << " ";
    // }
    // cout << endl;


    // __m256d vec1 = _mm256_setr_pd(4.0, 5.0, 13.0, 6.0);
    // __m256d vec2 = _mm256_setr_pd(9.0, 3.0, 6.0, 7.0);
    // __m256d neg = _mm256_setr_pd(1.0, -1.0, 1.0, -1.0);
    
    // /* Step 1: Multiply vec1 and vec2 */
    // __m256d vec3 = _mm256_mul_pd(vec1, vec2);

    // /* Step 2: Switch the real and imaginary elements of vec2 */
    // vec2 = _mm256_permute_pd(vec2, 0x5);
    
    // /* Step 3: Negate the imaginary elements of vec2 */
    // vec2 = _mm256_mul_pd(vec2, neg);  
    
    // /* Step 4: Multiply vec1 and the modified vec2 */
    // __m256d vec4 = _mm256_mul_pd(vec1, vec2);

    // /* Horizontally subtract the elements in vec3 and vec4 */
    // vec1 = _mm256_hsub_pd(vec3, vec4);
    
    // /* Display the elements of the result vector */
    // double* res = (double*)&vec1;
    // printf("%lf %lf %lf %lf\n", res[0], res[1], res[2], res[3]);
    
    return 0;
}