def left_move(map):
    for i in range(4):
        j = 0
        while j < 4:
            if map[i][j] == 0:
                map[i].pop(j)
                map[i].append(0)
                if j < 3 and map[i][j + 1] > 0:
                    j -= 1
            j += 1
    return map
                    
def right_move(map):
    for i in range(4):
        j = 0
        while j < 4:
            if map[i][3 - j] == 0:
                map[i].pop(3 - j)
                map[i].insert(0, 0)
                if j < 3 and map[i][3 - j - 1] > 0:
                    j -= 1
            j += 1
    return map
                
def up_move(map):
    mirror_map = [[0 for j in range(4)] for i in range(4)]
    for i in range(4):
        for j in range(4):
            mirror_map[i][j] = map[j][i]
    mirror_map = left_move(mirror_map);
    for i in range(4):
        for j in range(4):
            map[i][j] = mirror_map[j][i]
    return map

def down_move(map):
    mirror_map = [[0 for j in range(4)] for i in range(4)]
    for i in range(4):
        for j in range(4):
            mirror_map[i][j] = map[j][i]
    mirror_map = right_move(mirror_map);
    for i in range(4):
        for j in range(4):
            map[i][j] = mirror_map[j][i]
    return map

if __name__ == "__main__":
    map = [[] for i in range(4)]
    for i in range(4):
        line = input().split(" ")
        for j in range(4):
            map[i].append(int(line[j]))
    op = input()
    
    if (op == '0'):
        map = left_move(map)
    elif (op == '1'):
        map = up_move(map)
    elif (op == '2'):
        map = right_move(map)
    elif (op == '3'):
        map = down_move(map)
    
    for i in range(4):
        for j in range(3):
            if op == '0':
                if map[i][j] != 0 and map[i][j] == map[i][j + 1]:
                    map[i][j] += map[i][j + 1]
                    map[i][j + 1] = 0
            elif op == '1':
                if map[j][i] != 0 and map[j][i] == map[j + 1][i]:
                    map[j][i] += map[j + 1][i]
                    map[j + 1][i] = 0
            if op == '2':
                if map[i][3 - j] != 0 and map[i][3 - j] == map[i][3 - j - 1]:
                    map[i][3 - j] += map[i][3 - j - 1]
                    map[i][3 - j - 1] = 0
            elif op == '3':
                if map[3 - j][i] != 0 and map[3 - j][i] == map[3 - j - 1][i]:
                    map[3 - j][i] += map[3 - j - 1][i]
                    map[3 - j - 1][i] = 0
    
    if (op == '0'):
        map = left_move(map)
    elif (op == '1'):
        map = up_move(map)
    elif (op == '2'):
        map = right_move(map)
    elif (op == '3'):
        map = down_move(map)
    
    for i in range(4):
        for j in range(4):
            print(map[i][j], end = ' ')
        print()