TABLE = [ 0 ]
r = 1
for n in range(1, 5000*2 + 1):
    r *= n
    TABLE.append(r)
n = int(input())
for i in range(n):
    x = int(input())
    print(TABLE[2 * x] // TABLE[x + 1] // TABLE[x])
