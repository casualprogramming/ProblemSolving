#2019710740 석예찬
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
    
    def solutionPath(self):
        path=str()
        curNode=self
        while curNode.parent!=0:
            path+=(str(curNode))+'\n'
            curNode = curNode.parent
        return path
    def __str__(self):
        return  "{state} ({fn} = {gn} + {hn})".format(state=list(self.state),fn=self.fn,gn=self.gn,hn=self.hn)



class Problem:
    def __init__(self, start, goal):
        self.start = start
        self.goal = goal
        self.maxState = (4,4,2)  # fixed..
        


class Astar:
    def __init__(self,prob):
        self.numberGeneratedNodes=0
        self.states = dict() # (state,node)
        self.closed =  set() #(state)
        self.prob = prob # fixed..

        self.openlist = dict() #(state,fn)
    
    def solution(self):
        #initialize
        hn = Astar.H(prob.start,prob.goal)
        gn = 0
        fn= hn+gn
        self.states[prob.start]= Node(prob.start,Node(0,0,0,0,0),fn,gn,hn)
        self.openlist[prob.start] = fn
        self.numberGeneratedNodes=1
        #find solution
        while self.openlist:
            state = min(self.openlist.keys(),key=(lambda k: self.openlist[k]))
            fn = self.openlist[state]
            self.openlist.pop(state)
            if not(self.isClosed(state)):
                self.closed.add(state)
                self.openNode(state,prob.goal)
                if state==prob.goal:
                    return self.states[state]
        return Node(0,0,0,0,0)
    def openNode(self,state,goal):
        nextStates = self.generateNextStates(state)
        for nextState in nextStates:
            if not (self.isClosed(nextState)):
                curNode = self.states[state]
                gn = curNode.gn + 1
                hn=Astar.H(nextState,goal)
                fn=gn+hn
                #find better path at nextState
                if (not ( nextState in self.states )) or self.states[nextState].fn>fn:
                        #open & update states
                        self.states[nextState]=Node(nextState,self.states[state],fn,gn,hn)
                        self.openlist[nextState]=fn
                        self.numberGeneratedNodes+=1
    def isClosed(self,state):
        return True if (state in self.closed) else False
    
    def isValid(self,state):
        missionary,wolf,boat=state
        rightMissionary=self.prob.maxState[0]-1-missionary
        rightWolf = self.prob.maxState[1]-1-wolf
        if not (missionary< self.prob.maxState[0] and wolf < self.prob.maxState[1] and 0<=missionary and 0<=wolf ):
            return False
        #get eaten
        elif Astar.isEatable(missionary,wolf):
            return False
        elif Astar.isEatable(rightMissionary,rightWolf):
            return False  
        else:
            return True
    @staticmethod
    def isEatable(missionary,wolf):
        return True if missionary!=0 and missionary<wolf else False
    @staticmethod
    def H(state,goal):
        m,w,b=np.array(state)-np.array(goal)
        h=0
        counts=m+w
        
        #case : goal
        if counts==0 and not(Astar.isLeft(b)):
            return 0
        
        #1: if boat is right, then move back to left side and remaining count of left is increased at least 1
        if not (Astar.isLeft(b)):
            h+=1
            counts+=1

        #2: caculate boat's move counts, 
        #2-1: Except the last two or one, The boat must move at least twice to get rid of 1 (move 2 to right side and 1 back to left side -> 2 -1 = 1)
        if counts>2:
            h+=(counts-2)*2
        #2-2: last two or one
        h+=1
        return h
    @staticmethod
    def isLeft(boat):
        return True if boat==1 else False

    
    def generateNextStates(self,state):
        directions = np.array([[1,0],[0,1],[1,1],[2,0],[0,2]])
        missionary,wolf,boat = state
        directionSign=-1 if Astar.isLeft(boat) else 1
        availableStates = []
        for direction in directions:
            next_miss,next_wolf =  (missionary,wolf) + (direction *(directionSign))
            next_boat= 0 if Astar.isLeft(boat) else 1
            next_state= (next_miss,next_wolf,next_boat)
            if self.isValid(next_state):
                availableStates.append(next_state)
        return availableStates

prob=Problem((3,3,1),(0,0,0))
astar = Astar(prob)
goalNode=astar.solution()
print('Nodes Generated',astar.numberGeneratedNodes)
print(goalNode.solutionPath())
