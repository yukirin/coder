#!/usr/bin/env python
# -*- coding: utf-8 -*-

n, k = map(int, input().split())
cards = list(map(int, input().split()))

needs = 0
dp = [[False for _ in range(k)] for _ in range(n + 1)]
dp2 = [[False for _ in range(k)] for _ in range(n + 1)]

for l in range(n + 1):
    dp[l][0], dp2[l][0] = True, True

for i in range(1, n + 1):
    for j in range(1, k):
        prev = False if j - cards[i - 1] < 0 else dp[i - 1][j - cards[i - 1]]
        if dp[i - 1][j] or prev:
            dp[i][j] = True

        prev2 = False if j - cards[n - i] < 0 else dp2[i - 1][j - cards[n - i]]
        if dp2[i - 1][j] or prev2:
            dp2[i][j] = True

for i, val in enumerate(cards):
    if val >= k:
        needs += 1
        continue

    b = False
    for nv in range(k - val, k):
        if i == 0:
            if dp2[n - 1][nv]:
                needs += 1
                b = True
                break
            continue

        if i == n - 1:
            if dp[n - 1][nv]:
                needs += 1
                b = True
                break
            continue

        for nv2 in range(nv + 1):
            if dp[i][nv2] and dp2[n - i - 1][nv - nv2]:
                b = True
                needs += 1
                break
        if b: break

print(n - needs)
