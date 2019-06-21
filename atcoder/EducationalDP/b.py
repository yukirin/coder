import sys
import os
from sys import stdin

stdin = open(os.path.dirname(__file__) + '/input.txt')  # local test
input = stdin.readline
sys.setrecursionlimit(20000000)


n, k = list(map(int, input().split()))
weights = list(map(int, input().split()))
weights += [0] * (k + 3)

dp = [9999999999] * (n + k + 3)
dp[0] = 0

for i in range(n - 1):
    current = weights[i]
    for step in range(1, k + 1):
        cost = abs(current - weights[i + step])
        dp[i + step] = min(dp[i + step], dp[i] + cost)

print(dp[n - 1])
