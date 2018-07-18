// https://open.kattis.com/problems/greetingcard

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>

#define sqr(x) ((x) * (x))

// note: this is a hack solution
//       larger MOD, more chance to AC
//       please see laurence's implementation
#define MOD 1725433

using namespace std;

int n;
uint64_t data[100000];
uint64_t data_hash[MOD + 3];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        uint64_t xx, yy;

        cin >> xx >> yy;
        ++xx; ++yy;

        data[i] = (xx << 32) + yy;

        uint64_t hash = data[i] % MOD;
        if (data_hash[hash]) ++hash;
        if (data_hash[hash]) ++hash;
        if (data_hash[hash]) ++hash;
        data_hash[hash] = data[i];
    }

    long count = 0;

    for (int i = 0; i < n; ++i) {
        uint64_t hash1 = (data[i] + (0ul << 32) + 2018ul);
        uint64_t hash2 = (data[i] + (2018ul << 32) + 0ul);
        uint64_t hash3 = (data[i] + (1680ul << 32) - 1118ul);
        uint64_t hash4 = (data[i] + (1680ul << 32) + 1118ul);
        uint64_t hash5 = (data[i] + (1118ul << 32) - 1680ul);
        uint64_t hash6 = (data[i] + (1118ul << 32) + 1680ul);

        count += data_hash[hash1 % MOD] == hash1;
        count += data_hash[hash1 % MOD + 1] == hash1;
        count += data_hash[hash1 % MOD + 2] == hash1;
        count += data_hash[hash1 % MOD + 3] == hash1;

        count += data_hash[hash2 % MOD] == hash2;
        count += data_hash[hash2 % MOD + 1] == hash2;
        count += data_hash[hash2 % MOD + 2] == hash2;
        count += data_hash[hash2 % MOD + 3] == hash2;

        count += data_hash[hash3 % MOD] == hash3;
        count += data_hash[hash3 % MOD + 1] == hash3;
        count += data_hash[hash3 % MOD + 2] == hash3;
        count += data_hash[hash3 % MOD + 3] == hash3;

        count += data_hash[hash4 % MOD] == hash4;
        count += data_hash[hash4 % MOD + 1] == hash4;
        count += data_hash[hash4 % MOD + 2] == hash4;
        count += data_hash[hash4 % MOD + 3] == hash4;

        count += data_hash[hash5 % MOD] == hash5;
        count += data_hash[hash5 % MOD + 1] == hash5;
        count += data_hash[hash5 % MOD + 2] == hash5;
        count += data_hash[hash5 % MOD + 3] == hash5;

        count += data_hash[hash6 % MOD] == hash6;
        count += data_hash[hash6 % MOD + 1] == hash6;
        count += data_hash[hash6 % MOD + 2] == hash6;
        count += data_hash[hash6 % MOD + 3] == hash6;
    }

    cout << count << endl;

    return 0;
}
