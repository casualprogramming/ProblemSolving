from itertools import permutations, combinations, product, combinations_with_replacement
import sys       
def IsMagicSqure(data: list):
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
    elif (data[2]+data[4]+data[6]) !=15:
        return False    
    else:
        return True
def GetCost(data: list, array: list):
    cost = 0
    for x in range(3):
        for y in range(3):
            cost+=abs(data[x*3+y]-array[x][y])
    return cost
    
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