#!/usr/bin/env python
# -*- coding: utf-8 -*-

x = int(input())


total = 0
for i in range(x + 1):
    total += i
    if total >= x:
        print(i)
        break
