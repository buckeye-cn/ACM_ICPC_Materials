#include <bits/stdc++.h>

using namespace std;

typedef double T;
typedef vector<T> VT;
typedef vector<VT> VVT;

typedef vector<int> VI;
typedef vector<VI> VVI;

// This function runs the Floyd-Warshall algorithm for all-pairs
// shortest paths.  Also handles negative edge weights.  Returns true
// if a negative weight cycle is found.
//
// Running time: O(|V|^3)
//
//   INPUT:  w[i][j] = weight of edge from i to j
//   OUTPUT: w[i][j] = shortest path from i to j
//           prev[i][j] = node before j on the best path starting at i

bool FloydWarshall (VVT &w, VVI &prev){
    int n = w.size();
    prev = VVI (n, VI(n, -1));
  
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (w[i][j] > w[i][k] + w[k][j]){
                    w[i][j] = w[i][k] + w[k][j];
                    prev[i][j] = k;
                }
            }
        }
    }
 
    // check for negative weight cycles
    for(int i=0;i<n;i++)
        if (w[i][i] < 0) return false;
    return true;
}
