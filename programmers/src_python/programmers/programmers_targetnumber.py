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

print(solution([1, 1, 1, 1, 1], 3))