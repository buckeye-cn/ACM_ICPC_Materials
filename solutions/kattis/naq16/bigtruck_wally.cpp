#include <iostream>
#include <set>
#include <algorithm>

#define MAX 1000

// #define DEBUG

using namespace std;

int index_of_min(set<int> s, int a[]) {
    set<int>::const_iterator it = s.cbegin();
    int ret = *it;
    int min = a[ret];
    for (auto i : s) {
        if (min > a[i]) {
            ret = i;
            min = a[i];
        }
    }
    return ret;
}

int min(int a, int b) {
    return a < b? a: b;
}

int main() {
    int n_locations;
    cin >> n_locations;

    int pick_ups[n_locations+1];
    int count[n_locations+1];
    for (auto i = 0; i < n_locations; ++i) {
        count[i] = 0;
    }
    for (auto i = 1; i <= n_locations; ++i) {
        cin >> pick_ups[i];
    }

    int n_roads;
    cin >> n_roads;

    int roads[n_locations+1][n_locations+1];
    for (auto i = 0; i < n_locations + 1; ++i) {
        for (auto j = 0; j < n_locations + 1; ++j) {
            if (i == j) {
                roads[i][j] = 0;
            } else {
                roads[i][j] = MAX;
            }
        }
    }
    for (auto i = 0; i < n_roads; ++i) {
        int a, b, d;
        cin >> a >> b >> d;
        roads[a][b] = d;
        roads[b][a] = d;
    }

    int dist[n_roads+1];
    for (auto i = 0; i < n_locations + 1; ++i) {
        dist[i] = roads[1][i];
    }

    set<int> visited = { 1 };
    set<int> unvisited;
    for (auto i = 2; i < n_locations + 1; ++i) {
        unvisited.insert(i);
    }
    count[1] = pick_ups[1];

    while (unvisited.size() > 0) {
        int nearest = index_of_min(unvisited, dist);
        int distance = dist[nearest];

        int new_dist[n_roads+1];
        for (auto i = 0; i < n_locations + 1; ++i) {
            new_dist[i] = distance + roads[nearest][i];
            // count[i] = pick_ups[nearest] + 
        }

        for (auto i = 0; i < n_locations + 1; ++i) {
            dist[i] = min(dist[i], new_dist[i]);
        }

        unvisited.erase(nearest);
        visited.insert(nearest);
    }

    if (dist[n_locations] == MAX) {
        cout << "impossible" << endl;
    } else {
        cout << dist[n_locations] << endl;
    }
}
