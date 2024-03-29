# https://open.kattis.com/problems/vedurvindhradi

x = float(input())

if x <= 0.2:
    print('Logn')
elif x <= 1.5:
    print('Andvari')
elif x <= 3.3:
    print('Kul')
elif x <= 5.4:
    print('Gola')
elif x <= 7.9:
    print('Stinningsgola')
elif x <= 10.7:
    print('Kaldi')
elif x <= 13.8:
    print('Stinningskaldi')
elif x <= 17.1:
    print('Allhvass vindur')
elif x <= 20.7:
    print('Hvassvidri')
elif x <= 24.4:
    print('Stormur')
elif x <= 28.4:
    print('Rok')
elif x <= 32.6:
    print('Ofsavedur')
else:
    print('Farvidri')
