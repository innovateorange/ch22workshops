from typing import TypeVar
from world.action import Action, LEFT, RIGHT, DOWN, UP, EXIT

"""
A world class which describes the contents of each world (read problem environment) used in the Q-learning demo

    Reinforcement learning demonstration - CuseHacks 2022
    Author: Matthew Cufari
    Date Created: Jan 7 2022

"""

"""
World class:
    noteworthy properties include - 
        The reward function (note this is abstracted from the agent definition without good reason)
        The domain of states
        The state -> [action, resulting state] pairs 
        The reward function need-not be a lambda but need follow the form
            f(d) -> REAL where d is in the domain of states

"""                          

class world:
   
    def __init__(self, preDefinedName, rewardFunction=lambda s: 10 if (s=="EXIT_GOOD") else (-10 if (s=="EXIT_BAD") else -1)):
        self.name = preDefinedName
        self.actions, self.domain = self.getDomainAndActions(preDefinedName)
        self.rewardFunction = rewardFunction
        
        """
        Add visualization code here
        #self.initializeWindow()
        """
        
        

    def getDomainAndActions(self, preDefinedName):
        if(preDefinedName=="gridWorld"):
            print("Making Grid World...")
            
            domain = [(0,0), (0,1), (0,2), (0,3), (0,4),
                      (1,0), (1,1),        (1,3), (1,4),
                      (2,0),  (2,1), (2,2), (2,3), (2,4), "EXIT_GOOD", "EXIT_BAD"]
            actions = {(0,0):[(RIGHT, (0,1)), (DOWN, (1,0))], (0,1):[(LEFT,(0,0)), (DOWN, (1,1)), (RIGHT,(0,2))], (0,2):[(RIGHT, (0,3)), (LEFT,(0,1))], 
                       (0,3):[(RIGHT,(0,4)), (LEFT, (0,2)), (DOWN, (1,3))], (0,4):[(EXIT, "EXIT_BAD"), (LEFT, (0,3)), (DOWN, (1,4))],
                       (1,0):[(UP, (0,1)), (RIGHT, (1,1)),(DOWN, (2,0))], (1,1):[(LEFT, (1,0)), (UP, (0,1)), (DOWN,(2,1))], (1,3):[(UP,(0,3)), (RIGHT, (1,4)), (DOWN,(2,3))],
                       (1,4):[(UP,(0,4)), (LEFT, (1,3)),(DOWN, (2,4))],
                       (2,0):[(UP, (1,0)), (RIGHT, (2,1))], (2,1):[(LEFT,(2,0)), (UP, (1,1)), (RIGHT, (2,2))], (2,2):[(RIGHT, (2,3)), (LEFT, (2,1))], 
                       (2,3):[(UP,(1,3)),(LEFT,(2,2)),(RIGHT,(2,4))], (2,4):[(UP,(1,4)),(LEFT,(2,3)), (EXIT,"EXIT_GOOD")], "EXIT_GOOD":[], "EXIT_BAD":[]}
            return actions, domain
        
    def initializeWindow(self):
        return True
        """
            Implement a method which initializes a window for the game to take place. The window should be empty and all grey
        """
    def draw(self, qValues, activeState): 
        return True

        """
            Implement a drawing solution which upon pressing the space bar returns control to the agent but does not close the window
            A sequence of actions which solves the problem would go something like this

                1: agent performs q-value update
                2: agent calls self.universe.world.draw()
                3: world.draw() updates the contents of the current window
                4: world.draw() returns a boolean True if the user presses space or left-click
                5: world.draw() returns a boolean False if the user presses back-space or delete
            Pseudo code solution:

                #self.window() is an abstract window object that is assumed to exist from the call to self.initializeWindow()
                window <- add grid-world grid with white lines
                
                window <- [draw triangle with label qValues[(state, action)] for (state,action) pair in world.actions]
                window <- draw orange disk at location of activeState
                window <- wait for input (space-bar, left-click, delete, back-space)

                $user input

                return False if delete or backspace
                return true otherwise


        """
