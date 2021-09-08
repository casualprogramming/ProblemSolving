from itertools import permutations, combinations, product, combinations_with_replacement
import sys       
import math
from collections import defaultdict, deque, OrderedDict
from enum import Enum
from pprint import pprint
from bisect import bisect_left, bisect_right
from functools import cmp_to_key

def compare(a, b):
    if a+b<b+a:
        return 1
    else:
        return -1

def solution(numbers: list):
    answer = ''
    numbersStr = [str(number) for number in numbers]
    numbersStr.sort(key=cmp_to_key(compare))
    for number in numbersStr:
        answer+=number
    #check 0
    answer = '0' if answer.count('0')==len(answer) else answer
    return answer

print(solution([6, 10, 2]))
print(solution([3, 30, 34, 5, 9]))
