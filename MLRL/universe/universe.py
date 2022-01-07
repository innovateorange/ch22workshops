from world.world import world

class universe:

    def __init__(self, name, world_seed):
        self.name = name
        

        self.world = world(world_seed)



