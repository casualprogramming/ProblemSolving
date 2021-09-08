from itertools import permutations, combinations, product, combinations_with_replacement
import sys       
import math
from collections import defaultdict, deque, OrderedDict
from enum import Enum
from pprint import pprint
from bisect import bisect_left, bisect_right
from functools import cmp_to_key
import itertools 

def compare(a, b):
    if a+b<b+a:
        return 1
    else:
        return -1
from functools import reduce

ID=0
PLAYS=1


def solution(genres, plays):
    answer = []
    best_album = defaultdict(list)

    for i, (genre , play) in enumerate(zip(genres, plays)):
        best_album[genre].append((i,play))
    best_genre = list()
    for genre, album in best_album.items():
        album.sort(key=lambda x : x[PLAYS], reverse=True)
        #counting play count
        play_count = reduce(lambda x, y:x+y,list(map(lambda x : x[PLAYS], album)))
        best_genre.append((play_count,genre))
    best_genre.sort(key=lambda x : x[0], reverse=True)
    select=2
    for play, genre in best_genre:
        for i, (id, p) in enumerate(best_album[genre]):
            if i==select: break
            answer.append(id)

    return answer



print(solution(["classic", "pop", "classic", "classic", "pop"], [500, 600, 150, 800, 2500]))

