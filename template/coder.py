import sys
import os
from sys import stdin


stdin = open(os.path.dirname(__file__) + '/input.txt')  # local test
input = stdin.readline
sys.setrecursionlimit(20000000)


nums = list(map(int, input().split()))
print(nums)
