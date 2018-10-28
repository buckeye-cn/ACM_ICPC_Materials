if __name__ == '__main__':
    state = [0 for i in range(50)]
    max = 0
    for i in range(3):
        strs = input().split(" ")
        for j in range(1, len(strs)):
            num = int(strs[j]) - 1
            state[num] = i + 1
            if num > max:
                max = num
    step_sum = 0
    bool = True
    pair = [1, 3]
    for i in range(max + 1):
        complement = [item for item in [1, 2, 3] if item not in pair]
        complement = complement[0]
        if state[max - i] == pair[0]:
            step_sum += 2 ** (max - i)
            pair[1] = complement
        elif state[max - i] == pair[1]:
            pair[0] = complement
        else:
            bool = False
            break
    if bool:
        print(step_sum)
    else:
        print("No")
        