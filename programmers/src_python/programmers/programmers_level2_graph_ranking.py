from itertools import permutations, combinations, product, combinations_with_replacement
import sys       
import math
from collections import defaultdict, deque
from enum import Enum
from pprint import pprint

W = 1
L = 0
GLobalCount = 0
def FindCount(p, winAndLoseList, WinOrLose):
    global GLobalCount
    visited = [ False for _ in range(len(winAndLoseList))]
    GLobalCount = 0
    FindCountInternal(p, winAndLoseList, visited, WinOrLose)
    return GLobalCount

def FindCountInternal(p, winAndLoseList, visited, WinOrLose):
    global GLobalCount
    visited[p] = True
    for other in winAndLoseList[p][WinOrLose]:
        if visited[other] is False:
            GLobalCount+=1
            FindCountInternal(other, winAndLoseList, visited,WinOrLose)
    return GLobalCount

def solution(n, results):
    winAndLoseList = [ [[],[]] for p in range(n)]
    visited = [ False for _ in range(n)]
    for result in results:
        p = result[0]-1
        other = result[1]-1
        winAndLoseList[p][W].append(other)
        winAndLoseList[other][L].append(p)
    answer = 0
    for p in range(n):
        WinCount = FindCount(p, winAndLoseList, W)
        LoseCount = FindCount(p, winAndLoseList, L)
        if (WinCount + LoseCount) == len(winAndLoseList)-1:
            answer+=1
    return answer

def solution2(n, results):
    winners = defaultdict(set)
    losers = defaultdict(set)
    answer=0
    for result in results:
        winners[result[0]-1].add(result[1]-1)
        losers[result[1]-1].add(result[0]-1)
    
    #similar to floyd
    for Self in range(n):
        for winner in winners[Self]:
            losers[winner].update(losers[Self])
        for loser in losers[Self]:
            winners[loser].update(winners[Self])

    for Self in range(n):
        if len(winners[Self]) + len(losers[Self]) == n-1:
            answer+=1
    return answer
    





print(solution(5, [[4, 3], [4, 2], [3, 2], [1, 2], [2, 5]]))
print(solution2(5, [[4, 3], [4, 2], [3, 2], [1, 2], [2, 5]]))
