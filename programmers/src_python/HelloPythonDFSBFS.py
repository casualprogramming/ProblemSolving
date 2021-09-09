from collections import deque,defaultdict

#pre-check visited version
def pre_bfs(vertex, graph, visited, OnVisited=lambda x:x):
    if vertex in visited:
        return
    queue = deque()
    #visite and append initial node
    visited.add(    vertex)
    OnVisited(      vertex)
    queue.append(   vertex)
    while queue:
        v = queue.popleft()
        for other in graph[v]:
            if other not in visited:
                #visite and append
                visited.add(    other)
                OnVisited(      other)
                queue.append(   other)
#post-check
def bfs(index, graph, visited, OnVisited=lambda x:x):
    queue = deque()
    queue.append(index)
    while queue:
        vertex = queue.popleft()
        if vertex not in visited:
            visited.add(vertex)
            OnVisited( vertex)
            queue.extend(graph[vertex])

#pre-check: visiting when appending node
def stack_dfs(vertex, graph, visited, OnVisited=lambda x:x):
    if vertex in visited:
        return
    stack = list()
    #visite and append initial node
    visited.add(    vertex)
    OnVisited(      vertex)
    stack.append(   vertex)

    while stack:
        v = stack.pop()
        for other in graph[v]:
            if other not in visited:
                #visite and append
                visited.add(    other)
                OnVisited(      other)
                stack.append(   other)

#post-check: visiting when pop()
def stack_dfs_post(index, graph, visited, OnVisited=lambda x:x):
    stack = list()
    stack.append(index)
    while stack:
        vertex = stack.pop()
        if vertex not in visited:
            visited.add(vertex)
            OnVisited(vertex)
            stack.extend(graph[vertex])

n=5
data = [["0", "1"], ["2", "3"], ["0", "4"]]
graph = defaultdict(set)
visited = set()
for d in data:
    graph[d[0]].add(d[1])
    graph[d[1]].add(d[0])
def func(vertex):
    print(vertex)

visited = set()
bfs("0",graph,visited,func)

visited = set()
pre_bfs("1",graph,visited,func)

visited = set()
stack_dfs("2",graph,visited,func)

visited = set()
stack_dfs_post("3",graph,visited,func)

visited = set()
stack_dfs_post("4",graph,visited)

