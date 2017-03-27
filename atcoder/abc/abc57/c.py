#!/usr/bin/env python
# -*- coding: utf-8 -*-

import math


def f(a, b):
    return max(len(str(a)), len(str(b)))


n = int(input())
r, cur = math.floor(math.sqrt(n)), 999999

for i in range(1, r + 1):
    if n % i != 0: continue

    ret = f(i, int(n / i))
    if ret < cur:
        cur = ret

print(cur)
