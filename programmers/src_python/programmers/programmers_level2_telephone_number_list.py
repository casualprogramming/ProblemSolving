from itertools import permutations, combinations, product, combinations_with_replacement
import sys       

def solution(phone_book):
    answer = True
    prefix_dict = set()
    for phone_number in phone_book:
        for i in range(1, len(phone_number)):
            prefix_dict.add(phone_number[:i])
    print(prefix_dict)
    for phone_number in phone_book:
        if phone_number in prefix_dict:
            return False
    return True

print(solution(["119", "97674223", "1195524421"]))
print(solution(["123","456","789"]))
print(solution(["12","123","1235","567","88"]))
