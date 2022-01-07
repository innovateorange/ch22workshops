from typing import TypeVar
from world.action import Action, LEFT, RIGHT, DOWN, UP, EXIT


                          

class world:
   
    def __init__(self, preDefinedName, rewardFunction=lambda s: 10 if (s=="EXIT_GOOD") else (-10 if (s=="EXIT_BAD") else -1)):
        self.name = preDefinedName
        self.actions, self.domain = self.getDomainAndActions(preDefinedName)
        self.rewardFunction = rewardFunction
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