pos = []
invalid = 0
for i in range(0,8):
    line = input()
    line = list(line)
    count = 0
    for j in range(0, 8):
        if line[j] == '*':
            pos.append([i,j])
if len(pos) != 8:
    invalid = 1
i = 0
while i < len(pos) and not invalid:
    j = i + 1
    while j < len(pos) and not invalid:
        invalid = pos[i][0] == pos[j][0] or pos[i][1] == pos[j][1] or pos[i][0]-pos[j][0] == pos[i][1]-pos[j][1] or pos[i][0]+pos[i][1] == pos[j][0]+pos[j][1]
        j += 1
    i += 1

if invalid:
    print("invalid")
else:
    print("valid")