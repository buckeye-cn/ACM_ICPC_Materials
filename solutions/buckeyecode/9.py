n = int(input())
lines = [
    input().split(' ')
    for i in range(n)
]
words = {
    line[0]
    for line in lines
}
print(len(set(
    word
    for line in lines
    for word in line
) - words))
