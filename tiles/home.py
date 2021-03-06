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
        :param capacity: Int - number of inhabitants in the house
        '''
        super(Home, self).__init__(x, y, capacity)

    def load_car(self, car, pathfinder):
        '''
        Determines a route for the car using the pathfinder reference and loads
        the car into the container of this object.

        This is the point that constructs a Car agent.

        :param car: Car - reference to car object to be loaded
        :param pathfinder: PathFinder - pathfinder reference
        :return: Boolean - returns True if and only if there exists a route
        '''
        if car.get_route(pathfinder):  # append only if a route exists
            self.cars.append(car)
            return True

        return False  # no route found

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
