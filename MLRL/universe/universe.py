from world.world import world

"""
A small universe class defining the properties of each universe a world may belong to
    
    Reinforcement learning demonstration - CuseHacks 2022
    Author: Matthew Cufari
    Date Created: Jan 7 2022


"""

class universe:

    def __init__(self, name, world_seed):
        self.name = name
        self.world = world(world_seed)



