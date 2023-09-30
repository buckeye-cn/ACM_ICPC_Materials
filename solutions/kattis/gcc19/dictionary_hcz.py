# https://open.kattis.com/problems/dictionary
# with data file

import bz2

words = ['']

for i in bz2.decompress(open('data.bz2', 'rb').read()):
    if i < 64:
        words[-1] += "123ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'"[i]
    else:
        words.append(words[-1][:len(words[-1]) - i + 64])

for word in sorted(
    word
        .replace('1', '\'s')
        .replace('2', 'ion')
        .replace('3', 'ing')
    for word in words[1:]
):
    print(word)
