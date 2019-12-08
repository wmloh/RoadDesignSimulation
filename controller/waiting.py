import warnings
from search.path_finder import PathFinder
from utils.constants import cost_function

TIMESTEP = 0
HOME = 3
HUB = 4


class Waiting:
    __doc__ = '''
    Class that handles and organizes cars that are not actively moving in the simulation
    '''

    def __init__(self, simulation):
        '''
        Constructor for Waiting

        :param simulation: Simulation - reference to simulation object
        '''
        self.homes = list()
        self.backup = None
        self.simulation = simulation
        self.fixed = False
        self.pathfinder = PathFinder(simulation.ground, cost_function)

    def attach(self, ts, desX, desY, home, hub):
        '''
        Appends a predefined-structured tuple that represents data from the order text file
        which indicates the order and time to move each car.

        :param ts: Int - timestep to begin moving a car
        :param desX: Int - destination x-coordinate
        :param desY: Int - destination y-coordinate
        :param home: Home - reference to the starting Home of the car
        :param hub: Hub - reference to the destination Hub of the car
        :return: None
        '''
        if not self.fixed:
            self.homes.append((ts, desX, desY, home, hub))
        else:
            warnings.warn('Attempted to attach object to Waiting after fixing')

    def detach(self):
        '''
        Removes the last object in homes.

        :return: Home/None - Home object of tuple that is removed
        '''
        if self.fixed:
            return self.homes.pop()[3]  # TODO: Enable feature to safely remove objects
        return None

    def notify_observer(self, timestep):
        '''
        Attaches all car agents to the timestep object once the current timestep is reached for
        the car agents to start moving.

        :param timestep: Timestep - reference to Timestep object
        :return: None
        '''
        # attaches the car agent to Timestep object whenever it is time for the car to start moving
        #   as specified by order.txt
        # TODO: Consider using PriorityQueue
        while len(self.homes) and self.homes[-1][TIMESTEP] == self.simulation.steps:
            timestep.attach(self.homes[-1][HOME].cars[0])  # TODO: Avoid assuming only one Car agent in a Home
            self.homes.pop()

    def fix_state(self):
        '''
        Sorts all tuples in order and loads cars into Home objects.

        This should be called before the simulations starts.

        :return: None
        '''
        self.homes.sort(key=lambda x: x[0])  # TODO: potential error
        self.backup = self.homes
        self.fixed = True

        for home in self.homes:
            ts, desX, desY, h, hub = home
            h.load_car(desX, desY, self.pathfinder, hub)

    def reset(self):
        '''
        Resets the homes container to the original state.

        :return: None
        '''
        self.homes = self.backup
        for home in self.homes:
            h = home[3]
            h.clear_cars()

    def get_size(self):
        '''
        Gets the number of cars in waiting for convenience.

        :return: Int - number of cars waiting
        '''
        return len(self.homes)

    def __str__(self):
        homes_list = list()
        for home in self.homes:
            home_string = f'[{home[0]}]\nStarts at: {home[3].get_coord()} -> ({home[1]}, {home[2]})'
            homes_list.append(home_string)

        return '\n'.join(homes_list)
