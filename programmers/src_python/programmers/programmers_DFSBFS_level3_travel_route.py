from itertools import permutations, combinations, product, combinations_with_replacement
from collections import deque,defaultdict
import sys       

def IsConvertable(str1,str2):
    if len(str1) != len(str2):
        return False
    count=0
    for c1,c2 in zip(str1,str2):
        if c1!=c2:
            count+=1
    if count==1:
        return True
    return False

#post-check
def bfs(begin_word, target_word, words):
    queue = deque()
    queue.append((begin_word,0))
    while queue:
        word, level = queue.popleft()
        if word == target_word:
            return level
        if level==len(words)-1:
            continue
        next_words = map(lambda x: (x,level+1),  filter(lambda x: IsConvertable(word,x),words))
        queue.extend(next_words)
    return 0

#
def dfs(index, graph, remains:set):
    stack = list()
    stack.append(index)
    dfs()
    while stack:
        vertex = stack.pop()
        if vertex in remains:
            remains.remove(vertex)
            #OnVisited(vertex)
            stack.extend(graph[vertex])


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


