from itertools import permutations, combinations, product, combinations_with_replacement
from collections import deque,defaultdict
import sys       

ticket_size = 0
FIND = False
def dfs(begin, graph:dict, route:list):
    global ticket_size, FIND
    if len(route) == ticket_size+1:
        FIND = True
        return;
    if begin not in graph:
        return
    for order, departure in enumerate(graph[begin]):
        graph[begin].pop(order)
        route.append(departure)
        dfs(departure,graph, route)
        if FIND == True:
            return
        route.pop()
        graph[begin].insert(order,departure)
        #graph[begin].append(departure)# worng: order is changed, c++ multiset or using index and swap

def solution(tickets):
    answer = []
    global ticket_size, FIND
    graph = dict()
    for ticket in tickets:
        if ticket[0] not in graph:
            graph[ticket[0]] = list()
        graph[ticket[0]].append(ticket[1])
    for adj in graph.values():
        adj.sort()
    ticket_size=len(tickets)
    answer.append("ICN")
    dfs("ICN", graph, answer)
    return answer

print(solution([["ICN", "JFK"], ["HND", "IAD"], ["JFK", "HND"]]))
print(solution([["ICN", "BOO"], ["ICN", "COO"], ["COO", "DOO"], ["DOO", "COO"], ["BOO", "DOO"], ["DOO", "BOO"], ["BOO", "ICN"], ["COO", "BOO"]]))


