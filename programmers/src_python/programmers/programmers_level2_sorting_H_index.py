from itertools import permutations, combinations, product, combinations_with_replacement
import sys       
import math
from collections import defaultdict, deque, OrderedDict
from enum import Enum
from pprint import pprint
from bisect import bisect_left, bisect_right

def solution(citations):
    answer = 0
    citations.sort()
    Min = 0
    Max = citations[len(citations)-1]
    for h in range(Min, Max+1):
        h_more_papers = len(citations) - bisect_left(citations, h)
        if h_more_papers>=h:
            answer = max(answer, h)
    return answer


print(solution([3, 0, 6, 1, 5]))
print(solution([12,11,10,9,8,1]))
print(solution([6,6,6,6,6,1]))
