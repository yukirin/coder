#!/usr/bin/env python
# -*- coding: utf-8 -*-


n = int(input())

power = 1
for i in range(1, n + 1):
    power = (power * i) % (1e9 + 7)
print(int(power))
