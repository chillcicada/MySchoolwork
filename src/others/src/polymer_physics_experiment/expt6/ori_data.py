import os


def subLine(start, end):
    tmp = ''
    for i in range(start, end):
        tmp += ',' + str(i) + '-' + str(i + 1)
    return tmp


length = 141
topo = '0-1'

points = [
    (0, 36),
    (0, 66),
    (0, 111),
    (15, 21),
    (15, 26),
    (50, 56),
    (50, 61),
    (125, 131),
    (125, 136),
    (95, 101),
    (95, 106),
]
sublines = [
    (21, 25),
    (26, 35),
    (56, 60),
    (61, 65),
    (136, 140),
    (131, 135),
    (101, 105),
    (106, 110),
    (1, 20),
    (36, 55),
    (66, 100),
    (111, 140),
]

for sl in sublines:
    s, e = sl
    topo += subLine(s, e)

for p in points:
    p1, p2 = p
    topo += ',' + str(p1) + '-' + str(p2)

current_dir = os.path.dirname(os.path.abspath(__file__))

with open(os.path.join(current_dir, 'topo.txt'), 'w') as f:
    print(topo, file=f)
