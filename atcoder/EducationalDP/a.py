import sys
import os
from sys import stdin

stdin = open(os.path.dirname(__file__) + '/input.txt')  # local test
input = stdin.readline
sys.setrecursionlimit(20000000)


n = int(input())
weights = list(map(int, input().split()))
weights += [0, 0, 0]

dp = [9999999999] * (n + 3)
dp[0] = 0

for i in range(n - 1):
    step1 = abs(weights[i] - weights[i + 1])
    step2 = abs(weights[i] - weights[i + 2])

    dp[i + 1] = min(dp[i + 1], dp[i] + step1)
    dp[i + 2] = min(dp[i + 2], dp[i] + step2)

print(dp[n - 1])
