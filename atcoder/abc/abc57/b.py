#!/usr/bin/env python
# -*- coding: utf-8 -*-


def distance(p1, p2):
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])


n, m = map(int, input().split())
st = [[int(a) for a in input().split()] for _ in range(n)]
cp = [[int(a) for a in input().split()] for _ in range(m)]

for s in st:
    index, dist = 0, 9999999999999999999999
    for i, c in enumerate(cp):
        if distance(s, c) < dist:
            index, dist = i, distance(s, c)
    print(index + 1)
