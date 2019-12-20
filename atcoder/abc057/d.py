#!/usr/bin/env python
# -*- coding: utf-8 -*-

from math import factorial


def comb(n, r):
    nf = factorial(n)
    rf = factorial(r)
    nrf = factorial(n - r)
    return int(nf / (rf * nrf))


n, a, b = map(int, input().split())
goods = list(reversed(sorted([int(x) for x in input().split()])))

avg, total = sum(goods[:a]) / a, 0

lastcount, lastindex = 0, 0
for i, val in enumerate(goods):
    if val == goods[a - 1]:
        lastcount += 1
        if i < a:
            lastindex += 1

if goods[0] != goods[a - 1]:
    total += comb(lastcount, lastindex)
else:
    for i in range(a - 1, b):
        if goods[a - 1] != goods[i]: break
        total += comb(lastcount, i + 1)

print("{}\n{}".format(avg, total))
