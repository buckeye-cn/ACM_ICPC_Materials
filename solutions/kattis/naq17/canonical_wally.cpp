#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int n;
    scanf("%d", &n);

    int coins[n];
    for (auto i = 0; i < n; ++i) {
        scanf("%d", &coins[i]);
    }

    int upper = coins[n-2] + coins[n-1];
    int optimal[upper];
    // int greedy[upper];
    optimal[0] = 0;

    bool canonical = true;
    for (auto i = 1; i < upper && canonical; ++i) {
        // cout << i << " ";
        optimal[i] = numeric_limits<int>::max();
        // cerr << i << '\t' << n  << '\n';
        for (auto coin : coins) {
            if (i - coin >= 0 && optimal[i-coin]+1 < optimal[i]) {
                optimal[i] = optimal[i-coin] + 1;
            }
        }
        // cout << "optimal: " << optimal[i];

        int greedy_count = 0;
        int sum = i;
        int index = n - 1;
        while (sum > 0) {
            while (index > 0 && coins[index] > sum) index--;
            // (greedy[i])++;
            if (index == 0) {
                greedy_count += sum;
                sum = 0;
            } else {
                sum -= coins[index];
                greedy_count++;
            }

            if (greedy_count > optimal[i]) {
                canonical = false;
                break;
            }
        }
        // cout << "; greedy: " << greedy_count << endl;
    }

    if (canonical) printf("canonical\n");
    else printf("non-canonical\n");

    return 0;
}
