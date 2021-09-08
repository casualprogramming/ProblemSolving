#reference: https://velog.io/@koyo/python-docs-6
result = eval("(2 + 4) * 6")
print(result)

result = sorted([9, 3, 2, 7, 4]) # 오름차순으로 정렬
print(result)

result = sorted([9, 3, 2, 7, 4], reverse = True) # 내림차순으로 정렬
print(result)

#x[1] 두번째 원소
result = sorted([('banana', 27), ('can', 33), ('apple', 42)], key = lambda x: x[1], reverse = True)
print(result)

#x[1] 첫번째 원소
result = sorted([('banana', 27), ('can', 33), ('apple', 42)], key = lambda x: x[0], reverse = True)
print(result)

data = [9 ,3, 2, 5, 6]
data.sort()
print(data)

from itertools import permutations, combinations, product, combinations_with_replacement

data = ['A', 'B', 'C'] # 데이터 준비
result = list(permutations(data, 3)) # 모든 순열 구하기
print(result)

result = list(combinations(data, 2)) #2개를 뽑는 모든 조합 구하기
print(result)

result = list(product(data, repeat=2)) # 2개를 뽑는 모든 순열 구하기(중복 허용)
print(result)

#result = list(combinations_with_replacement(data, repeat=2)) # 2개를 뽑는 모든 조합 구하기(중복 허용)
result = list(combinations_with_replacement(data, 2)) # 2개를 뽑는 모든 조합 구하기(중복 허용)
print(result)

from bisect import bisect_left, bisect_right

nums = [4, 5, 5, 5, 5, 5, 5, 5, 5]
n = 5 
print(nums[bisect_left(nums, n)]) 
print(nums[bisect_right(nums, n)])


def IsMagicSqure(data):
    for x in range(3):
        sum = 0
        for y in range(3):
            sum += data[x*3+y]
        if sum!=15:
            return False
    for y in range(3):
        sum = 0
        for x in range(3):
            sum += data[x*3+y]
        if sum!=15:
            return False
    if (data[0]+data[4]+data[8]) !=15:
        return False
    elif (data[0]+data[4]+data[8]) !=15:
        return False    
    else:
        return True
        
        
numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9] #
permutation = list(permutations(numbers, 9)) #
def IsMagicSqure(data):
    for x in range(3):
        sum = 0
        for y in range(3):
            sum += data[x*3+y]
        if sum!=15:
            return False
    for y in range(3):
        sum = 0
        for x in range(3):
            sum += data[x*3+y]
        if sum!=15:
            return False
    if (data[0]+data[4]+data[8]) !=15:
        return False
    elif (data[0]+data[4]+data[8]) !=15:
        return False    
    else:
        return True

def GetCost(permutation, array):
    cost = 0;
    for x in range(3):
        for y in range(3):
            cost+=abs(permutation[x*3+y]-array[x][y])
    return cost    
import sys       
def formingMagicSquare(s):
    # Write your code here
    data = [1, 2, 3, 4, 5, 6, 7, 8, 9] #
    permutation = list(permutations(data, 9)) #
    minimalCost = sys.maxsize
    for data in permutation:
        if IsMagicSqure(data):
            minimalCost = min(minimalCost, GetCost(data,s))
    return minimalCost

s = [[5, 3, 4], [1, 5, 8], [6, 4, 2]]
print(formingMagicSquare(s))    