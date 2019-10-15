import numpy as np
import math
import queue

class Node:
    def __init__(self,s, p, fn, gn, hn):
        self.state = s
        self.parent = p
        self.fn = fn
        self.gn = gn
        self.hn = hn
class Problem:
    def __init__(self, start, goal):
        self.start = start
        self.goal = goal
        self.maxState = (4,4,2)  # fixed..
        


class Astar:
    def __init__(self,prob):
        self.numberGeneratedNodes=0
        self.state = dict()
        self.opened =  dict()
        self.prob = prob # fixed..

        self.priorityQueue = queue.PriorityQueue()
        self.directions = np.array([[1,0],[0,1],[1,1],[2,0],[0,2]])
    def solution(self,start,goal):
        hn = Astar.H(start,goal)
        gn = 0
        fn= hn+gn
        self.state[start]=(fn,gn,hn)
        self.priorityQueue.put((fn,start))
        while not self.priorityQueue.empty():
            #print("queue",self.priorityQueue.queue)
            fn,(missionary,wolve,boat)= self.priorityQueue.get()
            state = (missionary,wolve,boat)
            if not(self.isOpened(state)):
                self.opened[state]=1
                self.openNode(state,goal)
                if state==goal:
                    return True
        return False
    def openNode(self,state,goal):
        print("open: ",state,self.state[state])
        #missionary,wolf,boat = state
        #directionSign=-1 if Astar.isLeft(boat) else 1
        nextStates = self.generateNextStates(state)
        for nextState in nextStates:
            if not (self.isOpened(nextState)):
                fn,gn,hn=self.state[state]
                print("iter: ",fn,gn,hn)
                
                gn+=1
                hn=Astar.H(nextState,goal)
                fn=gn+hn
                #find better path
                if (not ( nextState in self.state )) or self.state[nextState][0]>fn:
                        self.numberGeneratedNodes+=1
                        self.state[nextState]=fn,gn,hn
                        self.priorityQueue.put((fn,nextState))
    def isOpened(self,state):
        return True if (state in self.opened) else False
    
    def isValid(self,state):
        missionary,wolf,boat=state
        rightMissionary=self.prob.maxState[0]-1-missionary
        rightWolf = self.prob.maxState[1]-1-wolf
        if not (missionary< self.prob.maxState[0] and wolf < self.prob.maxState[1] and 0<=missionary and 0<=wolf ):
            return False
        elif missionary !=0 and missionary<wolf:
            return False
        elif rightMissionary!=0 and rightMissionary<rightWolf:
            return False  
        else:
            return True
    @staticmethod
    def H(state,goal):
        m,w,b=np.array(state)-np.array(goal)
        h=0
        counts=m+w
        if counts==0:
            return 0 if not (Astar.isLeft(b)) else 1
        
        # if boat is left, then move back to right side and count increase at least 1
        if not (Astar.isLeft(b)):
            h+=1
            counts+=1
        # caculate boat's move counts, 
        # The boat must move at least twice to get rid of 1 (move 2 to right side and 1 back to left side 2 -1) except the last two or one.
        if counts>2:
            h+=(counts-2)*2
        #last two or one
        h+=1
        return h
    @staticmethod
    def isLeft(boat):
        return True if boat==1 else False
    
    def solutionPath(self,start,goal):
        path=[]
        curState = goal
        while True:
            curFn,curGn,curHn = self.state[curState]
            path.append((curState,(curFn,curGn,curHn)))
            if curState == start:
                break
            nextStates = self.generateNextStates(curState)
            for state in nextStates:
                fn,gn,hn=self.state[state]
                if gn<self.state[curState][1]:
                    curState=state
                    break
        return path
    
    def generateNextStates(self,state):
        missionary,wolf,boat = state
        directionSign=-1 if Astar.isLeft(boat) else 1
        states = []
        for direction in self.directions:
            next_miss,next_wolf =  (missionary,wolf) + (direction *(directionSign))
            next_boat= 0 if Astar.isLeft(boat) else 1
            next_state= (next_miss,next_wolf,next_boat)
            if self.isValid(next_state):
                states.append(next_state)
        return states

prob=Problem((3,3,1),(0,0,0))
astar = Astar(prob)
astar.solution((3,3,1),(0,0,0))
path=astar.solutionPath((3,3,1),(0,0,0))
for state in path:
    print(state)
print(astar.numberGeneratedNodes)
print(astar.numberGeneratedNodes)