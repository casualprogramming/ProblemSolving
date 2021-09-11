from itertools import permutations, combinations, product, combinations_with_replacement
from collections import deque,defaultdict
import sys       

def IsConvertable(str1,str2):
    if len(str1) != len(str2):
        return False
    count=0
    for c1,c2 in zip(str1,str2):
        if c1!=c2:
            count+=1
    if count==1:
        return True
    return False

#post-check
def bfs(begin_word, target_word, words):
    queue = deque()
    queue.append((begin_word,0))
    while queue:
        word, level = queue.popleft()
        if word == target_word:
            return level
        if level==len(words)-1:
            continue
        next_words = map(lambda x: (x,level+1),  filter(lambda x: IsConvertable(word,x),words))
        queue.extend(next_words)
    return 0

def solution(begin, target, words):
    answer = 0
    answer = bfs(begin, target, words)
    return answer

print(solution("hit","cog", ["hot", "dot", "dog", "lot", "log", "cog"]))
print(solution("hit","cog", ["hot", "dot", "dog", "lot", "log"]))
