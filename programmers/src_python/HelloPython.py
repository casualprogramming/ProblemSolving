#reference: https://velog.io/@koyo/python-docs-6
result = eval("(2 + 4) * 6")
print(result)

#************************ sort ************************
print("\n************************ sort ************************\n")

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

data = [9, 3, 2, 7, 4]
data.sort()
print(data)

from functools import cmp_to_key
def CompareDescending(a, b):
    if a>b:
        return 1
    else:
        return -1

data=[9, 3, 2, 7, 4]
data.sort(key=cmp_to_key(CompareDescending))
print(data)

#**************** bisect_left, bisect_right, binary search ****************

from bisect import bisect_left, bisect_right
print("\n**************** bisect_left, bisect_right, binary search ****************\n")

nums = [4, 5, 5, 5, 5, 5, 5, 5, 5]
print(nums[bisect_left(nums, 5)]) 
print(nums[bisect_right(nums, 5)-1])

#**************** permutations, combinations, product ****************
print("\n**************** permutations, combinations, product ****************\n")

from collections import defaultdict, deque
from itertools import permutations, combinations, product, combinations_with_replacement
from typing import DefaultDict
from functools import reduce

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

result = list(permutations([0,1], 3)) #2P3 result: empty
print(result)

result = list(combinations([0,1], 3)) #2C3 result: empty
print(result)#empty

result = list(product([0,1], repeat=3)) # 3
print(result)

result = list(combinations_with_replacement([0,1], 3)) # 3개를 뽑는 모든 조합 구하기(중복 허용)
print(result)



#**************** list, dictionary, set, enumerate, zip, reduce ****************
print("\n**************** list ****************\n")
#--list
data = ["Bob", "Alice", "Dave"]
age_str = ["17", "15", "20"]
age_int = [int(age) for age in age_str]
print(dict(zip(data,age_int)))

for i, (first, second) in enumerate(zip(data,age_int)):
    print(i, first, second)

n=3
m=4
Nx2_List = [ [[],[]] for i in range(n)]
NxM_int = [[0 for j in range(m)] for i in range(n)]
NxM_list = [[[] for j in range(m)] for i in range(n)]
NxM_int[n-1][m-1] = 1
print(Nx2_List)
print(NxM_int)
print(NxM_list)

print("\n**************** dictionary ****************\n")
#--dictionary
data = [["key1", "value0"], ["key1", "value1"], ["key0", "value2"]]
data2 = [["key1", "value3"], ["key1", "value4"], ["key0", "value5"]]
dictionary = dict(data)
print(dictionary)

#for key in dictionary: 

for i, (key,value) in enumerate(dictionary.items()):
    print(i, key,value)

print(list(map(lambda x : x[0], dictionary.items())))

dictionary.update([["key1", "new_value0"], ["key0", "new_value1"]])#multiple insert
print(dictionary)


data = defaultdict(set)

#--set

print("\n**************** reduce, map ****************\n")

#--reduce, map
data = [[16,"Alice"],[16,"Dave"],[16,"Bob"]]
print(reduce(lambda x, y:x+y,list(map(lambda x : x[0], data))))
print("filter (Alice):", list(filter(lambda x: ("a" in x[1] or "A" in x[1]), data)))

mapping = list(map(lambda x: (x,1),  filter(lambda x: ("a" in x[1] or "A" in x[1]), data)))
print(mapping)

#**************** string ****************
print("\n**************** string ****************\n")
s = "07:05:45PM"
print(s[-2:])
print(s[:-2])

print(s.replace("PM", "AM"))

val = "77".rjust(5, "0")#right align, padding left
print(val)

val = "77".ljust(5, "0")#left align, padding right
print(val)

#****************** math ******************
print("\n**************** math ****************\n")

import math
print(math.ceil(2.0))
print(math.ceil(2.1))
print(abs(-2.1))

import sys
print("max integer", sys.maxsize)



#****************** etc. ******************
print("\n**************** etc ****************\n")
global_value = 0
def IncreaseGlobalValue():
    global global_value
    global_value+=1
IncreaseGlobalValue()
print(global_value)




#****************** dfs, bfs. ******************


#****************** bit ******************
print("\n**************** bit ****************\n")
print(1, bin(1))
n=5
print(1<<2, bin(1<<2))