#!/usr/bin/env python
# -*- coding: utf-8 -*-

import array


n, k = map(int, input().split())
cards = list(map(int, input().split()))

needs = 0
for i, val in enumerate(cards):
    if val >= k:
        needs += 1
        continue

    c_without_i = cards[:i] + cards[i + 1:]

    dp = array.array('b', [0] * k)
    dp2 = array.array('b', [0] * k)
    b = False
    for m in c_without_i:
        if m >= k: continue
        for j, v in enumerate(dp):
            dp2[j] = v or dp2[j]
            if v is 1 and (j + m) < k:
                if k - val <= j + m:
                    needs += 1
                    b = True
                    break
                dp2[j + m] = 1

        if b:
            break

        dp2[m] = 1
        dp, dp2 = dp2, dp

print(n - needs)
