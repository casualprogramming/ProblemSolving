from itertools import permutations, combinations, product, combinations_with_replacement
from collections import deque,defaultdict
import sys       



#post-check: visiting when pop()
def dfs(index, graph, remains:set):
    stack = list()
    stack.append(index)
    while stack:
        vertex = stack.pop()
        if vertex in remains:
            remains.remove(vertex)
            #OnVisited(vertex)
            stack.extend(graph[vertex])

def solution(n, computers):
    answer = 0
    graph = defaultdict(list)
    for i in range(n):
        for adj in range(n):
            if computers[i][adj]==1:
                graph[i].append(adj)
                graph[adj].append(i)

    remains = set([v for v in range(n)])
    for v in range(n):
        if v in remains:
            dfs(v,graph,remains)
            answer+=1
    return answer



print(solution(3, [[1, 1, 0], [1, 1, 0], [0, 0, 1]]))
print(solution(3, [[1, 1, 0], [1, 1, 1], [0, 1, 1]]))
