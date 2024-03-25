// https://open.kattis.com/problems/solarly

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <unordered_map>
#include <iostream>

using namespace std;

long extgcd(long y, long x, long &s, long &t){
    long ss = 0;
    long tt = 1;

    s = 1;
    t = 0;

    while (x) {
        s -= y / x * ss;
        swap(s, ss);
        t -= y / x * tt;
        swap(t, tt);
        y %= x;
        swap(y, x);
    }

    return y;
}

int n, nx, ny, nz;
int mass[100];
int x[100];
int y[100];
int z[100];
int vx[100];
int vy[100];
int vz[100];

pair<long, long> solve(int i, int j) {
    long s, t;

    long gx = extgcd(2 * nx + vx[j] - vx[i], nx, s, t);
    long mod_x = nx / gx;
    if ((nx + x[i] - x[j]) % gx) return {0, 0};
    long rem_x = (nx + x[i] - x[j]) / gx * (nx + s) % mod_x;

    long gy = extgcd(2 * ny + vy[j] - vy[i], ny, s, t);
    long mod_y = ny / gy;
    if ((ny + y[i] - y[j]) % gy) return {0, 0};
    long rem_y = (ny + y[i] - y[j]) / gy * (ny + s) % mod_y;

    long gz = extgcd(2 * nz + vz[j] - vz[i], nz, s, t);
    long mod_z = nz / gz;
    if ((nz + z[i] - z[j]) % gz) return {0, 0};
    long rem_z = (nz + z[i] - z[j]) / gz * (nz + s) % mod_z;

    long gxy = extgcd(mod_x, mod_y, s, t);
    long mod_xy = mod_x * mod_y / gxy;
    long rem_xy = (mod_y / gxy * rem_x * (mod_x + t) + mod_x / gxy * rem_y * (mod_y + s)) % mod_xy;

    long gxyz = extgcd(mod_xy, mod_z, s, t);
    long mod_xyz = mod_xy * mod_z / gxyz;
    long rem_xyz = (mod_z / gxyz * rem_xy * (mod_xy + t) + mod_xy / gxyz * rem_z * (mod_z + s)) % mod_xyz;

    return {rem_xyz, mod_xyz};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    cin >> n >> nx >> ny >> nz;

    for (int i = 0; i < n; ++i) {
        cin >> mass[i] >> x[i] >> y[i] >> z[i] >> vx[i] >> vy[i] >> vz[i];
    }

    set<long> q;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            pair<long, long> cp = solve(i, j);

            if (cp.second) q.insert(cp.first);
        }
    }

    long t_last = 0;

    while (!q.empty()) {
        long t = *q.begin();
        q.erase(t);

        unordered_map<int, int> m;
        int nn[100];

        for (int i = 0; i < n; ++i) {
            if (mass[i]) {
                int xx = (x[i] + t * (nx + vx[i])) % nx;
                int yy = (y[i] + t * (ny + vy[i])) % ny;
                int zz = (z[i] + t * (nz + vz[i])) % nz;
                int pos = (xx << 20) + (yy << 10) + zz;

                if (m.find(pos) == m.end()) {
                    m[pos] = i;
                    nn[i] = 1;
                } else {
                    int j = m[pos];

                    mass[j] += mass[i];
                    x[j] = xx;
                    y[j] = yy;
                    z[j] = zz;
                    vx[j] += vx[i];
                    vy[j] += vy[i];
                    vz[j] += vz[i];
                    nn[j] += 1;

                    mass[i] = 0;
                }
            }
        }

        for (pair<int, int> p: m) {
            if (nn[p.second] > 1) {
                vx[p.second] /= nn[p.second];
                vy[p.second] /= nn[p.second];
                vz[p.second] /= nn[p.second];
                x[p.second] = (x[p.second] + t * (nx - vx[p.second])) % nx;
                y[p.second] = (y[p.second] + t * (ny - vy[p.second])) % ny;
                z[p.second] = (z[p.second] + t * (nz - vz[p.second])) % nz;
                t_last = t;

                // cerr << '@' << t << ' ' << mass[p.second] << endl;
                // cerr << x[p.second] << ' ' << y[p.second] << ' ' << z[p.second] << endl;
                // cerr << vx[p.second] << ' ' << vy[p.second] << ' ' << vz[p.second] << endl;
                // cerr << endl;

                for (int i = 0; i < n; ++i) {
                    if (i != p.second && mass[i]) {
                        pair<long, long> cp = solve(i, p.second);

                        if (cp.second) q.insert(t + 1 + ((cp.first - t - 1) % cp.second + cp.second) % cp.second);
                    }
                }
            }
        }
    }

    set<pair<long, int>> s;

    for (int i = 0; i < n; ++i) {
        if (mass[i]) {
            x[i] = (x[i] + t_last * (nx + vx[i])) % nx;
            y[i] = (y[i] + t_last * (ny + vy[i])) % ny;
            z[i] = (z[i] + t_last * (nz + vz[i])) % nz;

            long pos = -(long(mass[i]) << 30) + (x[i] << 20) + (y[i] << 10) + z[i];

            s.insert({pos, i});
        }
    }

    cout << s.size() << endl;

    int ii = 0;

    for (pair<long, int> p: s) {
        cout << 'P' << ii << ": " << mass[p.second] << ' ';
        cout << x[p.second] << ' ' << y[p.second] << ' ' << z[p.second] << ' ';
        cout << vx[p.second] << ' ' << vy[p.second] << ' ' << vz[p.second] << endl;
        ii += 1;
    }

    return 0;
}
