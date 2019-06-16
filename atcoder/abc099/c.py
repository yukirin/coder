import sys
import os
from sys import stdin
import math

stdin = open(os.path.dirname(__file__) + '/input.txt')  # local test
input = stdin.readline
sys.setrecursionlimit(20000000)


N = int(input())
i_6 = math.ceil(math.log(N, 6))
i_9 = math.ceil(math.log(N, 9))

dp = [9999999] * (N + 1)
dp[0] = 0

for i in range(N):
    for j in range(i_6 + 1):
        if (i + 6 ** j) > N:
            break
        dp[i + 6 ** j] = min(dp[i + 6 ** j], dp[i] + 1)

    for k in range(i_9 + 1):
        if (i + 9 ** k) > N:
            break
        dp[i + 9 ** k] = min(dp[i + 9 ** k], dp[i] + 1)

print(dp[N])
