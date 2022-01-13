import random
from world.action import UP, DOWN, LEFT, RIGHT, EXIT
import numpy as np
"""
    Q-Learning Agent class:
        Reinforcement learning demonstration - CuseHacks 2022
        Author: Matthew Cufari
        Date Created: Jan 7 2022

    Methods - 
        constructor (__init__):
            args: 
                self, 
                kwargs (key-word args)
            usage: create an agent to play a Q-learning session on world world_seed.

            key-words: epsilon -> double: [0.0, 1.0], gamma -> double: [0.0, 1.0], world_seed -> String : "gridWorld"

        iterateQValues():
            args: 
                self,
                None
            usage: Perform the online Q-learning updates
        
        printQValues():
            args:
                self,
                None
            usage: Print the Contents of the self.QValues Dict
    
    Properties-
        QValues -> Dict containing the Q-values for each associated (state, action) pair
        Gamma -> The discount factor for the Reinforcement learning process
        Epsilon -> The epsilon value for the epsilon greedy variant of the learning algorithm
        currentState -> A tuple encoding the current state of the agent 
        universe -> The universe in which this agent exists
"""

class agent:
    def __init__(self, domain, actions, reward_function, **kwargs):
        self.QValues = {} #init the QValues dict
        self.domain = domain
        self.actions = actions
        self.rewardFunction = reward_function
        try:
            self.epsilon = kwargs["epsilon"] #Set epsilon
        except KeyError:
            self.epsilon = 0.0 #Default epsilon -> Small epsilon means less exploration
        try:
            self.gamma = kwargs["gamma"] #Set discount factor gamma
        except KeyError:
            self.gamma = 1.0 #Default gamma
        
        try:
            self.world_seed = kwargs["world_seed"]
            if(self.world_seed != "gridWorld"): #Grid world is the only problem supported right now
                raise(KeyError)
        except KeyError:
            self.world_seed = "gridWorld"
        
        
        for state in  self.domain: #init the Q-values over the domain of states and action pairs to 0
            for action in [UP, DOWN, LEFT, RIGHT, EXIT]:
                self.QValues[(state,action)] = 0
        
        self.currentState = self.domain[0] #Set initial state
        self.iters = 0
       

    def iterateQValues(self):
        
        self.iters += 1
        if(self.currentState == "EXIT_GOOD" or self.currentState == "EXIT_BAD"): #Reset when reaching either point
            self.currentState = self.domain[0] #reset to initial state
            self.iters = 0
            return
        qNew = []
        newAction, newState = (None, None)
        r = random.random()
        if(r > self.epsilon): #Decrease epsilon to 0 as i increases

            bestQ = -1e10
            newActionList = []
            for action, nextState in self.actions[self.currentState]:
                QVal = self.QValues[(self.currentState, action)]
               
                if QVal > bestQ or not newActionList: #pick the best Q-value from the available options
                    newActionList = [(action,nextState)]
                    bestQ = QVal

                elif abs(QVal - bestQ) < 1e-6:
                    newActionList.append((action,nextState))
                
            
            newAction, newState = random.choice(newActionList)
        else:
            newAction, newState = random.choice(self.actions[self.currentState]) #randomly choose an action
        for action, unUsedState in self.actions[newState]:
            qNew.append(self.QValues[(newState, action)]) 
        
        #Q-learning update equation
        if(qNew):
            self.QValues[(self.currentState, newAction)] = 0.9 * self.QValues[(self.currentState, newAction)] + \
                                                        0.1*(self.rewardFunction(newState) +  self.gamma * (max(qNew) - self.QValues[(self.currentState,newAction)])) 
            
        else:
            self.QValues[(self.currentState, newAction)] = self.rewardFunction(newState) 
        
        
        r = random.random()

        if(r < 0.2):
            newStatesList = []
            for action, randState in self.actions[self.currentState]:
                
                if randState == newState:
                    continue
                else:
                    newStatesList.append(randState)
            if newStatesList:
                newState = random.choice(newStatesList)
                
        self.currentState = newState

       
    def printQValues(self):
        for state, optionsResults in self.actions.items():
            for action, newState in optionsResults:
                print("The Q Value at ", state, " with action ", action.__name__, "is ", self.QValues[(state, action)])
    

