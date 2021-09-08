from itertools import permutations, combinations, product, combinations_with_replacement
import sys       


def solution(clothes):
    cloth_dict = dict()
    for cloth in clothes:
        if cloth[1] in cloth_dict:
            cloth_dict[cloth[1]]+=1
        else:
            cloth_dict[cloth[1]]=1
    total=1
    for cloth in cloth_dict.values():
        total*=cloth+1
    return total-1

print(solution([["yellowhat", "headgear"], ["bluesunglasses", "eyewear"], ["green_turban", "headgear"]]))
print(solution([["crowmask", "face"], ["bluesunglasses", "face"], ["smoky_makeup", "face"]]))
