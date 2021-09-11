from itertools import permutations, combinations, product, combinations_with_replacement
from collections import deque,defaultdict
import sys       
#https://programmers.co.kr/learn/courses/30/lessons/12952
#solution1: check the queen can be placed when place queen
#solution2: Update position (can not be placed) to the array when place queen
def boundary_check(board,c,r):
    if r>=0 and c>=0 and r<len(board[0]) and c<len(board):
        return True
    else:
        return False

#solution1
def CanPlaced(board,c,r):
    #check coloum
    for col in range(len(board)):
        if board[col][r]==True:
            return False
    #check row
    for row in range(len(board[0])):
        if board[c][row]==True:
            return False
    directions = [[-1,-1],[-1,1],[1,-1],[1,1]]

    #self
    if board[c][r] == True:
        return False

    #diagonal
    for dir in directions:
        for i in range(len(board[0])):
            c_diag=c + dir[0]*i
            r_diag=r + dir[1]*i
            if not boundary_check(board,c_diag,r_diag):
                break
            else:
                if board[c_diag][r_diag] == True:
                    return False
    return True

solution_set = list()
#backtracking
def dfs(board, row, queen_set):
    global solution_set, queen_count
    if len(queen_set) == len(board):
        solution_set.add(tuple(queen_set))
        return 
    for c in range(len(board)):
        if CanPlaced(board,c,row):
            board[c][row] = True
            queen_set.append((c,row))
            dfs(board, row+1, queen_set)
            queen_set.pop()
            board[c][row] = False

def solution(n):
    board = [[0 for r in range(n)]for c in range(n)]
    global solution_count
    dfs(board,0, list())
    print(solution_set)
    return len(solution_set)

print(solution(4))


#worng: iterate all path that places a queen
#[(0, 2), (1, 0), (2, 3), (3, 1)] , [(2, 3), (3, 1), (0, 2), (1, 0)] .... 
           
# solution_set = set()
# #backtracking
# def dfs(board, queen_set):
#     global solution_set, queen_count
#     if len(queen_set) == len(board):
#         solution_set.add(tuple(sorted(queen_set)))
#         return 
#     for c in range(len(board)):
#         for r in range(len(board[0])):
#             if CanPlaced(board,c,r):
#                 board[c][r] = True
#                 queen_set.append((c,r))
#                 dfs(board, queen_set)
#                 queen_set.pop()
#                 board[c][r] = False

# def solution(n):
#     board = [[0 for r in range(n)]for c in range(n)]
#     global solution_count
#     dfs(board, list())
#     return len(solution_set)
