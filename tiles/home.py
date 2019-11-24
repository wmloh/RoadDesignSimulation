from tiles.traversable import Traversable
from agents.car import Car


class Home(Traversable):
    __doc__ = '''
    Class that can initially contain car(s) at the start of the simulation and is 
    the starting point for car agents 
    '''

    def __init__(self, x, y, capacity):
        '''
        Constructor for a Home

        :param x: Int - x-coordinate of the tile
        :param y: Int - y-coordinate of the tile
        :param capacity: Int - maximum number of cars the Home can support
        '''
        super(Home, self).__init__(x, y, capacity)

    def load_car(self, desX, desY, pathfinder, hub):
        '''
        Determines a route for the car using the pathfinder reference and loads
        the car into the container of this object.

        This is the point that constructs a Car agent.

        :param desX: Int - x-coordinate of destination
        :param desY: Int - y-coordinate of destination
        :param pathfinder: PathFinder - pathfinder reference
        :param hub: Hub - reference for destination hub
        :return: None
        '''
        car = Car(self.x, self.y, desX, desY, hub, self)
        car.get_route(pathfinder)
        self.cars.append(car)

    def __str__(self):
        if len(self.cars) == 0:
            return 'H'
        else:
            return '@'

    def traversable(self):
        '''
        Return whether cars can drive to this tile
        :return: Boolean
        '''
        return False
