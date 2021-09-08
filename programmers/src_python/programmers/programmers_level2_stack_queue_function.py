from itertools import permutations, combinations, product, combinations_with_replacement
import sys       
import math
from collections import deque

def solution(progresses, speeds):
    answer = []
    remains = deque()
    for i in range(len(progresses)):
        remains.append(int(math.ceil((100 - progresses[i]) / speeds[i])))
    while remains:
        remain = remains.popleft();
        count=1
        while remains and (remain>=remains[0]):
            remains.popleft()
            count+=1
        answer.append(count)

    return answer

print(solution([93, 30, 55],[1, 30, 5]))
print(solution([95, 90, 99, 99, 80, 99], [1, 1, 1, 1, 1, 1]))
