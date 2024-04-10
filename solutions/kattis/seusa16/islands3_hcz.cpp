# https://open.kattis.com/problems/islands3

r, c = input().split()
r = int(r)
c = int(c)

grid = [
    list(input())
    for i in range(r)
]

def dfs(i, j):
    grid[i][j] = 'x'

    if i > 0 and grid[i - 1][j] in 'LC':
        dfs(i - 1, j)
    if i < r - 1 and grid[i + 1][j] in 'LC':
        dfs(i + 1, j)
    if j > 0 and grid[i][j - 1] in 'LC':
        dfs(i, j - 1)
    if j < c - 1 and grid[i][j + 1] in 'LC':
        dfs(i, j + 1)

    return 1

print(sum(
    dfs(i, j)
    for i in range(r)
    for j in range(c)
    if grid[i][j] == 'L'
))
