from itertools import permutations, combinations, product, combinations_with_replacement
import sys       

def solution(numbers:list, target):
    plus_minus_pack =[-1,1]
    answer = 0
    for signs in list(product(plus_minus_pack, repeat=len(numbers))):
        sum = 0
        for i in range(len(numbers)):
            sum += numbers[i] *signs[i]
        if sum==target:
            answer+=1
    return answer

def dfs(numbers, target):
    goal =0
    stack = [(numbers[0],0),(-numbers[0],0)]
    while stack:
        n, level = stack.pop()#n:number,level
        if level == len(numbers)-1:
            if n==target:
                goal+=1
            continue
        else:
            stack.append((n + numbers[level+1]*1,level+1))
            stack.append((n + numbers[level+1]*-1,level+1))
    return goal

def solution2(numbers:list, target):
    return dfs(numbers,target)

print(solution([1, 1, 1, 1, 1], 3))
print(solution2([1, 1, 1, 1, 1], 3))