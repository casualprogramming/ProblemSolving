from collections import deque
from itertools import permutations, combinations, product, combinations_with_replacement
import sys      


global_count =0
#pre-check visited version
def bfs(index, graph, visited):
    global global_count
    if visited[index]==True:
        return
    queue = deque()
    #visite and append initial node
    global_count+=1
    visited[index]=True
    queue.append(index)

    while queue:
        vertex = queue.popleft()
        for other in graph[vertex]:
            if visited[other]==False:
                #visite and append
                global_count+=1
                visited[other]=True
                queue.append(other)
#post-check
def post_bfs(index, graph, visited):
    global global_count
    queue = deque()
    queue.append(index)
    while queue:
        vertex = queue.popleft()
        if visited[vertex]==False:
            global_count+=1
            visited[vertex]=True
            queue.extend(graph[vertex])

#pre-check: visiting when appending node
def stack_dfs(index, graph, visited):
    global global_count
    if visited[index]==True:
        return
    stack = list()
    #visite and append initial node
    global_count+=1
    visited[index]=True
    stack.append(index)

    while stack:
        vertex = stack.popleft()
        for other in graph[vertex]:
            if visited[other]==False:
                #visite and append
                global_count+=1
                visited[other]=True
                stack.append(other)

#post-check: visiting when pop()
def stack_dfs_post(index, graph, visited):
    global global_count
    stack = list()
    stack.append(index)
    while stack:
        vertex = stack.pop()
        if visited[vertex]==False:
            global_count+=1
            visited[vertex]=True
            stack.extend(graph[vertex])

def journeyToMoon(n, astronaut):
    # Write your code here
    visited =[False for _ in range(n)]
    graph = [[] for _ in range(n)]
    for a in astronaut:
        graph[a[0]].append(a[1])
        graph[a[1]].append(a[0])
    groups = []
    for index in range(n):
        global global_count
        global_count=0
        post_bfs(index, graph, visited)
        if global_count!=0:
            groups.append(global_count)

    if len(groups)<=1:
       return 0
    
    answer=0
    prefix_sums = [0 for _ in range(len(groups))]
    prefix_sums[-1] = groups[-1]
    for i in reversed(range(0,len(groups)-1)):
        prefix_sums[i] = prefix_sums[i+1] + groups[i]
    for prefix_sum, group in zip(prefix_sums,groups):
        answer+=(prefix_sum-group)*group
    return answer


#combination: runtime error
#dfs: runtime error

#def dfs(Self, graph, visited):
#    global global_count
#    if visited[Self]==True:
#        return
#    visited[Self]=True
#    global_count+=1
#    for other in graph[Self]:
#        dfs(other,graph,visited)

print(journeyToMoon(5,[[0, 1], [2, 3], [0, 4]]))
print(journeyToMoon(5,[[0, 1],[0, 2],[0, 3],[0, 4]]))
