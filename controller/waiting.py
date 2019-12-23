import warnings
from search.pathFinder import PathFinder
from utils.constants import cost_function
from utils.priority_queue import PriorityQueue
from agents.car import Car
from tiles.home import Home
from tiles.hub import Hub

# Indices for the tuple
TIMESTEP = 0
HOME = 3
HUB = 4
CAR = 5


class Waiting:
    __doc__ = '''
    Class that handles and organizes cars that are not actively moving in the simulation
    '''

    def __init__(self, simulation):
        '''
        Constructor for Waiting

        :param simulation: Simulation - reference to simulation object
        '''
        self.homes = PriorityQueue(key=lambda x: x[0])
        self.simulation = simulation
        self.fixed = False
        self.pathfinder = PathFinder(simulation.ground, cost_function)

    def attach(self, ts, desX, desY, home, hub):
        '''
        Appends a predefined-structured tuple that represents data from the order text file
        which indicates the order and time to move each car.

        Constructs a Car agent object.

        Will raise a non-fatal alert if attempted to attach after being fixed

        :param ts: Int - timestep to begin moving a car
        :param desX: Int - destination x-coordinate
        :param desY: Int - destination y-coordinate
        :param home: Home - reference to the starting Home of the car
        :param hub: Hub - reference to the destination Hub of the car
        :return: None
        '''
        if not self.fixed:
            if not isinstance(home, Home):
                raise ValueError(f'Expected Home tile but given {type(home)}')
            elif not isinstance(hub, Hub):
                raise ValueError(f'Expected Hub tile but given {type(hub)}')

            car = Car(home.x, home.y, desX, desY, hub, home)
            self.homes.push((ts, desX, desY, home, hub, car))
        else:
            warnings.warn('Attempted to attach object to Waiting after fixing')

    def detach(self):
        '''
        Removes the object with the most recent initialization timestep in homes.

        :return: Home/None - Home object of tuple that is removed (None if not fixed)
        '''
        if self.fixed and len(self.homes):
            return self.homes.pop()[HOME]
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
        while len(self.homes) and self.homes.top()[TIMESTEP] == self.simulation.steps:
            timestep.attach(self.homes.pop()[CAR])

    def fix_state(self, verbose=False):
        '''
        Sorts all tuples in order and loads cars into Home objects.

        This should be called before the simulations starts.

        :param verbose: Boolean - if True, print out message when there are no paths for some cars
        :return: None
        '''
        self.fixed = True

        for home in self.homes:
            ts, desX, desY, h, hub, car = home
            if not h.load_car(car, self.pathfinder) and verbose:
                print(f'Car at {h.get_coord()} does not have a valid path')

    def reset(self):
        '''
        Empties the homes container

        :return: None
        '''
        self.homes.clear()
        self.fixed = False

    def get_size(self):
        '''
        Gets the number of cars in waiting for convenience.

        :return: Int - number of cars waiting
        '''
        return len(self.homes)

    def __str__(self):
        homes_list = list()
        for home in sorted(self.homes.container, key=lambda x: x[0]):
            home_string = f'[{home[TIMESTEP]}] Car ({home[CAR].id}) starts at: {home[HOME].get_coord()} -> {home[HUB].get_coord()}'
            homes_list.append(home_string)

        return '\n'.join(homes_list)
