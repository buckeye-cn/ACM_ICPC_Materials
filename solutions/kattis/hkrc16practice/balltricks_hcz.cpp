// https://open.kattis.com/problems/balltricks

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#include <emmintrin.h>

#define MSIZE (4 * 4 * 16)
#define MOD 1000000007l
#define ACCESS(a, b, s) \
    [((a) * 4 + (b)) * 16 + (s)]
#define REQUIRE(cond) \
    if (!(cond)) continue

using namespace std;

uint64_t s_seq[16]  {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 2, 9};
uint64_t s_rseq[16] {1, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 0, 0, 0, 9};
uint64_t s_r[16]    {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 9, 9, 9, 9};

uint64_t trans[64][MSIZE][MSIZE];
uint64_t cases[64][MSIZE];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint64_t player[4];
    uint64_t n;
    cin >> player[0] >> player[1] >> player[2] >> player[3] >> n;

    n -= 1;

    for (uint64_t a = 0; a < 4; ++a)
    for (uint64_t b = 0; b < 4; ++b)
    for (uint64_t s = 0; s < 15; ++s) {
        uint64_t seq = s_seq[s];
        uint64_t rseq = s_rseq[s];
        uint64_t r = s_r[s];

        for (uint64_t na = 0; na < 4; ++na)
        for (uint64_t nb = 0; nb < 4; ++nb)
        for (uint64_t ns = 0; ns < 15; ++ns) {
            uint64_t nseq = s_seq[ns];
            uint64_t nrseq = s_rseq[ns];
            uint64_t nr = s_r[ns];

            uint64_t count;

            if (((a >> 1) & 1) == (b & 1)) {
                // attack fails

                REQUIRE(na == b);
                count = player[nb] - uint64_t(nb == a) - uint64_t(nb == b) - uint64_t(rseq == 1 && nb == r);
                REQUIRE(count > 0);
                REQUIRE(nseq == 0);

                switch (rseq) {
                    case 0:
                        REQUIRE(nrseq == 0);
                        REQUIRE(nr == 9);
                        break;
                    case 1:
                        REQUIRE(nrseq == 2);
                        REQUIRE(nr == r);
                        break;
                    case 2:
                        REQUIRE(nrseq == 0);
                        REQUIRE(nr == 9);
                        break;
                }
            } else if (seq == 2) {
                count = (player[na] - uint64_t(na == a) - uint64_t(na == b) - uint64_t(rseq == 1 && na == r));
                REQUIRE(count > 0);
                count *= (player[nb] - uint64_t(nb == a) - uint64_t(nb == b) - uint64_t(nb == na) - uint64_t(rseq == 1 && nb == r));
                REQUIRE(count > 0);
                REQUIRE(nseq == 0);

                switch (rseq) {
                    case 0:
                        REQUIRE(nrseq == 1);
                        REQUIRE(nr == a);
                        break;
                    case 1:
                        REQUIRE(false);
                        break;
                    case 2:
                        REQUIRE(false);
                        break;
                }
            } else {
                REQUIRE(na == a);
                count = player[nb] - uint64_t(nb == a) - uint64_t(nb == b) - uint64_t(rseq == 1 && nb == r);
                REQUIRE(count > 0);
                REQUIRE(nseq == seq + 1);

                switch (rseq) {
                    case 0:
                        REQUIRE(nrseq == 0);
                        REQUIRE(nr == 9);
                        break;
                    case 1:
                        REQUIRE(nrseq == 2);
                        REQUIRE(nr == r);
                        break;
                    case 2:
                        REQUIRE(nrseq == 0);
                        REQUIRE(nr == 9);
                        break;
                }
            }

            trans[0]ACCESS(a, b, s)ACCESS(na, nb, ns) = count;
        }
    }

    for (uint64_t a = 0; a < 4; ++a)
    for (uint64_t b = 0; b < 4; ++b)
    for (uint64_t s = 0; s < 15; ++s) {
        uint64_t seq = s_seq[s];
        uint64_t rseq = s_rseq[s];
        uint64_t r = s_r[s];

        uint64_t count;

        count = player[a];
        REQUIRE(count > 0);
        count *= (player[b] - uint64_t(b == a));
        REQUIRE(count > 0);
        REQUIRE(seq == 0);
        REQUIRE(rseq == 0);
        REQUIRE(r == 9);

        cases[0]ACCESS(a, b, s) = count;
    }

    uint64_t level;

    for (level = 1; (1ul << level) <= n; ++level) {
        for (uint64_t i = 0; i < MSIZE; ++i) {
            uint64_t buf[MSIZE];
            memset(buf, 0, sizeof(buf));

            for (uint64_t jbase = 0; jbase < MSIZE; jbase += 32) {
                for (uint64_t j = jbase; j < jbase + 32; ++j) {
                    if (!trans[level - 1][i][j]) continue;

                    __m128i *src = (__m128i *) trans[level - 1][j];
                    __m128i *dst = (__m128i *) buf;
                    __m128i m = _mm_set1_epi64x(trans[level - 1][i][j]);

                    for (uint64_t kbase = 0; kbase < MSIZE; kbase += 32) {
                        _mm_store_si128(&dst[0], _mm_add_epi64(dst[0], _mm_mul_epu32(m, src[0])));
                        _mm_store_si128(&dst[1], _mm_add_epi64(dst[1], _mm_mul_epu32(m, src[1])));
                        _mm_store_si128(&dst[2], _mm_add_epi64(dst[2], _mm_mul_epu32(m, src[2])));
                        _mm_store_si128(&dst[3], _mm_add_epi64(dst[3], _mm_mul_epu32(m, src[3])));
                        _mm_store_si128(&dst[4], _mm_add_epi64(dst[4], _mm_mul_epu32(m, src[4])));
                        _mm_store_si128(&dst[5], _mm_add_epi64(dst[5], _mm_mul_epu32(m, src[5])));
                        _mm_store_si128(&dst[6], _mm_add_epi64(dst[6], _mm_mul_epu32(m, src[6])));
                        _mm_store_si128(&dst[7], _mm_add_epi64(dst[7], _mm_mul_epu32(m, src[7])));
                        _mm_store_si128(&dst[8], _mm_add_epi64(dst[8], _mm_mul_epu32(m, src[8])));
                        _mm_store_si128(&dst[9], _mm_add_epi64(dst[9], _mm_mul_epu32(m, src[9])));
                        _mm_store_si128(&dst[10], _mm_add_epi64(dst[10], _mm_mul_epu32(m, src[10])));
                        _mm_store_si128(&dst[11], _mm_add_epi64(dst[11], _mm_mul_epu32(m, src[11])));
                        _mm_store_si128(&dst[12], _mm_add_epi64(dst[12], _mm_mul_epu32(m, src[12])));
                        _mm_store_si128(&dst[13], _mm_add_epi64(dst[13], _mm_mul_epu32(m, src[13])));
                        _mm_store_si128(&dst[14], _mm_add_epi64(dst[14], _mm_mul_epu32(m, src[14])));
                        _mm_store_si128(&dst[15], _mm_add_epi64(dst[15], _mm_mul_epu32(m, src[15])));

                        src += 16;
                        dst += 16;
                    }
                }

                for (uint64_t kbase = 0; kbase < MSIZE; kbase += 16) {
                    if (buf[kbase + 0]) buf[kbase + 0] %= MOD;
                    if (buf[kbase + 1]) buf[kbase + 1] %= MOD;
                    if (buf[kbase + 2]) buf[kbase + 2] %= MOD;
                    if (buf[kbase + 3]) buf[kbase + 3] %= MOD;
                    if (buf[kbase + 4]) buf[kbase + 4] %= MOD;
                    if (buf[kbase + 5]) buf[kbase + 5] %= MOD;
                    if (buf[kbase + 6]) buf[kbase + 6] %= MOD;
                    if (buf[kbase + 7]) buf[kbase + 7] %= MOD;
                    if (buf[kbase + 8]) buf[kbase + 8] %= MOD;
                    if (buf[kbase + 9]) buf[kbase + 9] %= MOD;
                    if (buf[kbase + 10]) buf[kbase + 10] %= MOD;
                    if (buf[kbase + 11]) buf[kbase + 11] %= MOD;
                    if (buf[kbase + 12]) buf[kbase + 12] %= MOD;
                    if (buf[kbase + 13]) buf[kbase + 13] %= MOD;
                    if (buf[kbase + 14]) buf[kbase + 14] %= MOD;
                    if (buf[kbase + 15]) buf[kbase + 15] %= MOD;
                }
            }

            for (uint64_t j = 0; j < MSIZE; ++j) {
                trans[level][i][j] = buf[j];
            }
        }
    }

    for (level = 1; (1ul << (level - 1)) <= n; ++level) {
        if (n & (1ul << (level - 1))) {
            uint64_t buf[MSIZE];
            memset(buf, 0, sizeof(buf));

            for (uint64_t ibase = 0; ibase < MSIZE; ibase += 32) {
                for (uint64_t i = ibase; i < ibase + 32; ++i) {
                    if (!cases[level - 1][i]) continue;

                    __m128i *src = (__m128i *) trans[level - 1][i];
                    __m128i *dst = (__m128i *) buf;
                    __m128i m = _mm_set1_epi64x(cases[level - 1][i]);

                    for (uint64_t jbase = 0; jbase < MSIZE; jbase += 32) {
                        _mm_store_si128(&dst[0], _mm_add_epi64(dst[0], _mm_mul_epu32(m, src[0])));
                        _mm_store_si128(&dst[1], _mm_add_epi64(dst[1], _mm_mul_epu32(m, src[1])));
                        _mm_store_si128(&dst[2], _mm_add_epi64(dst[2], _mm_mul_epu32(m, src[2])));
                        _mm_store_si128(&dst[3], _mm_add_epi64(dst[3], _mm_mul_epu32(m, src[3])));
                        _mm_store_si128(&dst[4], _mm_add_epi64(dst[4], _mm_mul_epu32(m, src[4])));
                        _mm_store_si128(&dst[5], _mm_add_epi64(dst[5], _mm_mul_epu32(m, src[5])));
                        _mm_store_si128(&dst[6], _mm_add_epi64(dst[6], _mm_mul_epu32(m, src[6])));
                        _mm_store_si128(&dst[7], _mm_add_epi64(dst[7], _mm_mul_epu32(m, src[7])));
                        _mm_store_si128(&dst[8], _mm_add_epi64(dst[8], _mm_mul_epu32(m, src[8])));
                        _mm_store_si128(&dst[9], _mm_add_epi64(dst[9], _mm_mul_epu32(m, src[9])));
                        _mm_store_si128(&dst[10], _mm_add_epi64(dst[10], _mm_mul_epu32(m, src[10])));
                        _mm_store_si128(&dst[11], _mm_add_epi64(dst[11], _mm_mul_epu32(m, src[11])));
                        _mm_store_si128(&dst[12], _mm_add_epi64(dst[12], _mm_mul_epu32(m, src[12])));
                        _mm_store_si128(&dst[13], _mm_add_epi64(dst[13], _mm_mul_epu32(m, src[13])));
                        _mm_store_si128(&dst[14], _mm_add_epi64(dst[14], _mm_mul_epu32(m, src[14])));
                        _mm_store_si128(&dst[15], _mm_add_epi64(dst[15], _mm_mul_epu32(m, src[15])));

                        src += 16;
                        dst += 16;
                    }
                }

                for (uint64_t jbase = 0; jbase < MSIZE; jbase += 16) {
                    if (buf[jbase + 0]) buf[jbase + 0] %= MOD;
                    if (buf[jbase + 1]) buf[jbase + 1] %= MOD;
                    if (buf[jbase + 2]) buf[jbase + 2] %= MOD;
                    if (buf[jbase + 3]) buf[jbase + 3] %= MOD;
                    if (buf[jbase + 4]) buf[jbase + 4] %= MOD;
                    if (buf[jbase + 5]) buf[jbase + 5] %= MOD;
                    if (buf[jbase + 6]) buf[jbase + 6] %= MOD;
                    if (buf[jbase + 7]) buf[jbase + 7] %= MOD;
                    if (buf[jbase + 8]) buf[jbase + 8] %= MOD;
                    if (buf[jbase + 9]) buf[jbase + 9] %= MOD;
                    if (buf[jbase + 10]) buf[jbase + 10] %= MOD;
                    if (buf[jbase + 11]) buf[jbase + 11] %= MOD;
                    if (buf[jbase + 12]) buf[jbase + 12] %= MOD;
                    if (buf[jbase + 13]) buf[jbase + 13] %= MOD;
                    if (buf[jbase + 14]) buf[jbase + 14] %= MOD;
                    if (buf[jbase + 15]) buf[jbase + 15] %= MOD;
                }
            }

            for (uint64_t i = 0; i < MSIZE; ++i) {
                cases[level][i] = buf[i];
            }
        } else {
            for (uint64_t i = 0; i < MSIZE; ++i) {
                cases[level][i] = cases[level - 1][i];
            }
        }
    }

    // for (uint64_t i = 0; i < level; ++i) {
    //     cerr << i << endl;

    //     for (uint64_t a = 0; a < 4; ++a)
    //     for (uint64_t b = 0; b < 4; ++b)
    //     for (uint64_t s = 0; s < 15; ++s) {
    //         uint64_t seq = s_seq[s];
    //         uint64_t rseq = s_rseq[s];
    //         uint64_t r = s_r[s];

    //         uint64_t count = cases[i]ACCESS(a, b, s);

    //         if (count) {
    //             cerr << a << ' ' << b << ' ' << seq << ' ' << rseq << ' ' << r << " = "
    //                  << count << endl;
    //         }
    //     }
    // }

    uint64_t sum = 0;

    for (uint64_t i = 0; i < MSIZE; ++i) {
        sum += cases[level - 1][i];
    }

    cout << sum % MOD << endl;

    return 0;
}
