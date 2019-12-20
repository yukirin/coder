#!/usr/bin/env python
# -*- coding: utf-8 -*-

a, b = input().split()

if a is "H":
    print(b)
else:
    if b is "H":
        print("D")
    else:
        print("H")
