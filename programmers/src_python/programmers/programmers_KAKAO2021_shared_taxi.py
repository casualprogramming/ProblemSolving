import sys
from queue import PriorityQueue
#https://programmers.co.kr/learn/courses/30/lessons/72413

def floyd(n, inputs):
    costs = [[sys.maxsize for j in range(n)] for i in range(n)]

    for input in inputs:
        costs[input[0]-1][input[1]-1] = input[2]
        costs[input[1]-1][input[0]-1] = input[2]

    for v in range(n):
        costs[v][v] = 0
    
    #floyd
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if costs[i][k] + costs[k][j] < costs[i][j]:
                    costs[i][j] = costs[i][k] + costs[k][j]
    return costs    

def dijk(begin, graph):
    pqueue = PriorityQueue()
    costs = [sys.maxsize for v in range(len(graph))]
    costs[begin]=0
    pqueue.put((0,begin))
    while not pqueue.empty():
        cost, v = pqueue.get()
        for adj, adj_cost in graph[v]:
            if cost + adj_cost <costs[adj]:
                costs[adj] = cost + adj_cost
                pqueue.put((cost + adj_cost, adj))
    return costs

#two dimentioanl dijk algorithm times out at test7, test8
#costs[v_A][v_B]: Costs by location of A and B
def dijk_two_dimentional(s, graph):
    costs = [[sys.maxsize for v_B in range(len(graph))] for v_A in range(len(graph))]
    costs[s][s] = 0
    pqueue = PriorityQueue()
    pqueue.put((0,s,s))
    while not pqueue.empty():
        cost,v_A,v_B = pqueue.get()
        #move AB
        if v_A==v_B:
            for adj, adj_cost in graph[v_A]:
                next_cost = cost+adj_cost
                if next_cost < costs[adj][adj]:
                    costs[adj][adj] = next_cost
                    pqueue.put((next_cost,adj,adj))
        #move A
        for adj, adj_cost in graph[v_A]:
            next_cost = cost+adj_cost
            if next_cost < costs[adj][v_B]:
                costs[adj][v_B] = next_cost
                pqueue.put((next_cost,adj,v_B))
        #move B
        for adj, adj_cost in graph[v_B]:
            next_cost = cost+adj_cost
            if next_cost < costs[v_A][adj]:
                costs[v_A][adj] = next_cost
                pqueue.put((next_cost,v_A,adj))
    return costs

def solution(n, s, a, b, fares):
    # 1. dijstra
    answer = sys.maxsize
    graph = [[] for v in range(n)]
    for fare in fares:
        graph[fare[0]-1].append((fare[1]-1,fare[2]))
        graph[fare[1]-1].append((fare[0]-1,fare[2]))
    #p: where shared taxi stopped
    for p in range(n):
        costs = dijk(p,graph)#get costs to p from all vertex
        answer = min(answer , costs[s-1] + costs[a-1] + costs[b-1])

    # 2. Floyd
    # costs = floyd(n,fares)
    # for p in range(n):
    #     answer = min(answer , costs[s-1][p] + costs[p][a-1] + costs[p][b-1])

    # 3. dijkstra 2 dimentional
    #costs = dijk_two_dimentional(s-1, graph)
    #answer = costs[a-1][b-1]

    return answer

print(solution
(
    6,4,6,2,
    [[4, 1, 10], [3, 5, 24], [5, 6, 2], [3, 1, 41], [5, 1, 24], [4, 6, 50], [2, 4, 66], [2, 3, 22], [1, 6, 25]]
))

print(solution
(
    7,3,4,1,
    [[5, 7, 9], [4, 6, 4], [3, 6, 1], [3, 2, 3], [2, 1, 6]]
))

print(solution
(
    6,4,5,6,
    [[2,6,6], [6,3,7], [4,6,7], [6,5,11], [2,5,12], [5,3,20], [2,4,8], [4,3,9]]
))


