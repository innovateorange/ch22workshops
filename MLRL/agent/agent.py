from universe.universe import universe
import random


class agent:
    def __init__(self, **kwargs):
        self.QValues = {}
        try:
            self.epsilon = kwargs["epsilon"]
        except KeyError:
            self.epsilon = 1.0
        try:
            self.gamma = kwargs["gamma"]
        except KeyError:
            self.gamma = 1.0
        
        try:
            self.world_seed = kwargs["world_seed"]
            if(self.world_seed != "gridWorld"):
                raise(KeyError)
        except KeyError:
            self.world_seed = "gridWorld"
        self.universe = universe("Universe A", world_seed="gridWorld")
        
        for state, resList in self.universe.world.actions.items():
            for action, newState in resList:
                self.QValues[(state,action)] = 0
        
        self.currentState = self.universe.world.domain[0]
        self.iterateQValues()
        print(self.gamma)
        print(self.epsilon)

    def iterateQValues(self):
        
        for i in range(10000):
            
            self.currentState = self.universe.world.domain[0]
            while self.currentState != "EXIT_GOOD" and self.currentState != "EXIT_BAD":
                qNew = []
                newAction, newState = (None, None)
                if(random.random() < self.epsilon):

                    bestQ = -100
                    
                    for action, nextState in self.universe.world.actions[self.currentState]:
                        if self.QValues[(self.currentState, action)] > bestQ or newAction == None:
                            newAction = action
                            newState = nextState
                            bestQ = self.QValues[(self.currentState, action)]
                    
                else:
                    newAction, newState = random.choice(self.universe.world.actions[self.currentState])
                for action, unUsedState in self.universe.world.actions[newState]:
                    qNew.append(self.QValues[(newState, action)])
                
                if(qNew):
                    self.QValues[(self.currentState, newAction)] += self.universe.world.rewardFunction(newState) +  self.gamma * (max(qNew) - self.QValues[(self.currentState,newAction)])
                    self.currentState = newState
                else:
                    self.QValues[(self.currentState, newAction)] += self.universe.world.rewardFunction(newState) - self.gamma * self.QValues[(self.currentState, newAction)]
                    self.currentState = newState
            self.printQValues()
    
    def printQValues(self):
        
        for state, optionsResults in self.universe.world.actions.items():
            for action, newState in optionsResults:
                print("The Q Value at ", state, " with action ", action, "is ", self.QValues[(state, action)])
        

                    
            

