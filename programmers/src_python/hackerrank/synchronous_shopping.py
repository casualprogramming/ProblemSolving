from collections import defaultdict, OrderedDict
from itertools import permutations, combinations, product, combinations_with_replacement
import sys
from typing import DefaultDict       
from pprint import pprint
from queue import PriorityQueue
import heapq

#[worng] Dijkstra: adjacent node length (timeout)
#[better] Dijkstra: select node cost cost[node][fish_state]
#그래도 시간초과난다 14번부터..... (미해결) c++ set으로 node를 compact하게 바꿔보자 https://www.youtube.com/watch?v=610JNkzxIEI&ab_channel=HackerRankSolution
#state 마다 visited 체크 해도 시간초과.. c++써야할듯?

#https://www.hackerrank.com/challenges/synchronous-shopping/problem
def dij(initial_vertex,costs,    fishes,edges):
    pqueue = PriorityQueue()
    costs[initial_vertex][fishes[initial_vertex]]=0
    pqueue.put((0, initial_vertex,fishes[initial_vertex]))
    
    while pqueue.empty()!=True:
        state_cost,u,u_state = pqueue.get()
        for (edge_cost, v) in edges[u]:
            v_next_cost = state_cost + edge_cost
            v_next_state = u_state|fishes[v]
            if v_next_cost < costs[v][v_next_state]:
                costs[v][v_next_state] = v_next_cost
                pqueue.put((v_next_cost,v,v_next_state))
                
        
def shop(n, k, centers, roads):
    # Write your code here
    goal_mask = (1<<k) -1

    fishes = defaultdict(int)
    edges = defaultdict(list)#[vertex][vertex]:cost
    costs = dict()#[vertex][fish_state]:dijkstra cost
    for vertex, center in enumerate(centers):
        fish_types = center.split()[1:]
        fish = 0
        for fish_type in fish_types:
            fish|=1<<(int(fish_type)-1)
        fishes[vertex]=fish

    #initial costs map
    costs[vertex] = dict()
    for vertex, fish in fishes.items():
        if vertex not in costs:
            costs[vertex] = dict()
        for i in range(goal_mask+1):
            costs[vertex][i] = sys.maxsize

    for road in roads:
        v1 = road[0]-1
        v2 = road[1]-1
        cost = road[2]
        edges[v1].append((cost, v2))
        edges[v2].append((cost, v1))
    for adjacent in edges.values():
        adjacent.sort(key=lambda x: x[0])


    dij(0,costs, fishes,edges)
    v = len(centers)-1
    answer = costs[v][goal_mask];
    for i in range(0, goal_mask+1):
        for j in range(0, goal_mask+1):
            if (i|j)==goal_mask:
                answer = min(answer,max(costs[v][i],costs[v][j]))
    return answer

print(shop(5, 5, ['1 1', '1 2', '1 3', '1 4', '1 5'] , [[1, 2, 10], [1, 3, 10], [2, 4, 10], [3, 5, 10], [4, 5, 10]]))
#print(shop(10,3,['2 1 2', '1 3', '0', '2 1 3', '1 2', '1 3'],[[1, 2, 572], [4, 2, 913], [2, 6, 220], [1, 3, 579], [2, 3, 808], [5, 3, 298], [6, 1, 927], [4, 5, 171], [1, 5, 671], [2, 5, 463]]))
# print(shop(20 ,2,['0', '1 1', '0', '1 1', '0', '0', '0', '2 1 2'],
# [
#     [3, 2, 762],
#     [7, 4, 727],
#     [8, 7, 322],
#     [8, 1, 207],
#     [1, 5, 687],
#     [2, 6, 556],
#     [1, 6, 103],
#     [6, 8, 237],
#     [3, 6, 777],
#     [5, 6, 698],
#     [3, 7, 584],
#     [6, 4, 25],
#     [2, 5, 734],
#     [3, 5, 667],
#     [7, 2, 208],
#     [7, 5, 669],
#     [4, 8, 775],
#     [8, 3, 229],
#     [1, 2, 462],
#     [4, 2, 562]]))


def CountSetBits(n:int):
    count = 0
    while (n):
        count += n & 1
        n >>= 1
    return count