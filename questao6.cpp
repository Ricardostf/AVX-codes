#include <iostream>
#include <immintrin.h>

using namespace std;

int main() {


    int8_t resultado1_8b[32];
    int8_t resultado2_8b[32];
    int16_t resultado1_16b[16];
    int16_t resultado2_16b[16];


    __m256i X8b = _mm256_setr_epi8(100, 100, -30, -40, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1);
    __m256i Y8b = _mm256_setr_epi8(100, 20, -100, 20, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1);
    
    __m256i X16b = _mm256_setr_epi16(-15000, 120, -12769, 20, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1);
    __m256i Y16b = _mm256_setr_epi16(20000, 1020, 20000, 20, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1);

    __m256i res1_8b = _mm256_add_epi8(X8b, Y8b);
    __m256i res2_8b = _mm256_adds_epi8(X8b, Y8b);
    __m256i res1_16b = _mm256_sub_epi16(X16b, Y16b);
    __m256i res2_16b = _mm256_subs_epi16(X16b, Y16b);

    _mm256_storeu_si256((__m256i*)resultado1_8b, res1_8b);
    _mm256_storeu_si256((__m256i*)resultado2_8b, res2_8b);
    _mm256_storeu_si256((__m256i*)resultado1_16b, res1_16b);
    _mm256_storeu_si256((__m256i*)resultado2_16b, res2_16b);

    cout << "Usando _mm256_add_epi8:  ";
    for (int i = 0; i < 4; ++i) {
        cout << static_cast<int>(resultado1_8b[i]) << ' ';
    }
    cout << endl;

    cout << "Usando _mm256_adds_epi8: ";
    for (int i = 0; i < 4; ++i) {
        cout << static_cast<int>(resultado2_8b[i]) << ' ';
    }
    cout << endl << endl;

    cout << "Usando _mm256_sub_epi16:  ";
    for (int i = 0; i < 4; ++i) {
        cout << static_cast<int>(resultado1_16b[i]) << ' ';
    }
    cout << endl;

    cout << "Usando _mm256_subs_epi16: ";
    for (int i = 0; i < 4; ++i) {
        cout << static_cast<int>(resultado2_16b[i]) << ' ';
    }
    cout << endl;

    return 0;
    }
