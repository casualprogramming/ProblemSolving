import math
import os
import random
import re
import sys

#
# Complete the 'extraLongFactorials' function below.
#
# The function accepts INTEGER n as parameter.
#

max_int_len=len(str(sys.maxsize))
chunk_len = 0

def extraLongFactorials(n):
    global chunk_len
    chunk_len = max_int_len-NumberOfDigit(n)-1
    BigInteger = [1]
    for i in range(2,n+1):
        BigIntegerMul(BigInteger, i)
    #print
    txt="";
    for i in reversed(range(len(BigInteger))):
        if i==len(BigInteger)-1:
            txt +=str(BigInteger[i])
        else:
            txt += str(BigInteger[i]).zfill(chunk_len)
    print(txt)

def NumberOfDigit(number):
    return len(str(number))

def SplitInteger(number):
    str_number = str(number)
    chunk0 = int(str_number[-chunk_len:])
    chunk1 = int(str_number[:-chunk_len])
    return [chunk0, chunk1]

def IsOutOfChunk(number):
    return True if NumberOfDigit(number)>chunk_len else False

def ResolveChunk(BigInteger, i):
    if IsOutOfChunk(BigInteger[i]):
        integers = SplitInteger(BigInteger[i])
        if i==len(BigInteger)-1:
            BigInteger.insert(len(BigInteger),0)
        print("chunk" + str(integers))
        BigInteger[i] = integers[0]
        BigInteger[i+1] += integers[1]
        ResolveChunk(BigInteger, i+1)

def BigIntegerMul(BigInteger, mul):
    for i in range(len(BigInteger)):
        BigInteger[i]*=mul
    i=0
    while True:
        ResolveChunk(BigInteger, i)
        i+=1
        if i==len(BigInteger):
            break;
    
extraLongFactorials(70) 

    
#def extraLongFactorials(n):
    # Write your code here


#print(NumberOfDigit(10))

#print(BigIntegerMul(20101))