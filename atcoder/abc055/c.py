#!/usr/bin/env python
# -*- coding: utf-8 -*-

n, m = map(int, input().split())

if m < n * 2:
    print(m // 2)
elif m == n * 2:
    print(n)
else:
    t, m = n, m - n * 2
    t += m // 4
    print(t)
