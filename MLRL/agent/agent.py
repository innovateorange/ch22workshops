from universe.universe import universe
import random


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
    def __init__(self, **kwargs):
        self.QValues = {} #init the QValues dict
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
        self.universe = universe("Universe A", world_seed="gridWorld") #Create the new universe (which establishes the grid_world world)
        
        for state, resList in self.universe.world.actions.items(): #init the Q-values over the domain of states and action pairs to 0
            for action, newState in resList:
                self.QValues[(state,action)] = 0
        
        self.currentState = self.universe.world.domain[0] #Set initial state
        
        k = self.universe.world.draw(self.QValues, self.currentState) #draw initial q-values
        self.iterateQValues() #wait for control to return before beginning drawing

    def iterateQValues(self):
        controlFlag = True
        while(controlFlag):
            if(self.currentState == "EXIT_GOOD" or self.currentState == "EXIT_BAD"): #Reset when reaching either point
                self.currentState = self.universe.world.domain[0] #reset to initial state

            qNew = []
            newAction, newState = (None, None)
            if(random.random() > self.epsilon): #Decrease epsilon to 0 as i increases

                bestQ = -1e10
                
                for action, nextState in self.universe.world.actions[self.currentState]:
                    if self.QValues[(self.currentState, action)] > bestQ or newAction == None: #pick the best Q-value from the available options
                        newAction = action
                        newState = nextState
                        bestQ = self.QValues[(self.currentState, action)]
                
            else:
                newAction, newState = random.choice(self.universe.world.actions[self.currentState]) #randomly choose an action
            for action, unUsedState in self.universe.world.actions[newState]:
                qNew.append(self.QValues[(newState, action)]) 
            
            #Q-learning update equation
            if(qNew):
                self.QValues[(self.currentState, newAction)] += self.universe.world.rewardFunction(newState) +  self.gamma * (max(qNew) - self.QValues[(self.currentState,newAction)]) 
                self.currentState = newState
            else:
                self.QValues[(self.currentState, newAction)] = self.universe.world.rewardFunction(newState) 
                self.currentState = newState
            
            controlFlag = self.universe.world.draw(self.QValues, self.currentState) 
            
    def printQValues(self):
        for state, optionsResults in self.universe.world.actions.items():
            for action, newState in optionsResults:
                print("The Q Value at ", state, " with action ", action.__name__, "is ", self.QValues[(state, action)])
        

                    
            

