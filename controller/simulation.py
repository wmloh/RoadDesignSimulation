import numpy as np

from tiles.traversable import Traversable
from tiles.home import Home
from tiles.hub import Hub
from tiles.road import Road
from tiles.obstacle import Obst
from tiles.empty import Empty
from controller.timestep import Timestep
from controller.waiting import Waiting
from utils.map_generator import generate_map
from utils.constants import HOME_VEC, HUB_VEC, OBST_VEC, ROAD_VEC, EMPTY_VEC
from agents.car import Car


class Simulation:
    __doc__ = '''
    A class that owns all the tiles in the simulation and controls the sequence of events along with the aid of
    trigger classes as in observer pattern paradigm.
    '''

    def __init__(self):
        '''
        Constructor for Simulation
        '''
        self.ground = None
        self.steps = 0
        self.num_roads = 0  # undefined
        self.road_cost = 0  # undefined
        self.timestep_trigger = Timestep(self)
        self.waiting_trigger = Waiting(self)

    def init(self):
        '''
        Iteratively calls Simulation.step_run until both the waiting and timestep trigger objects are empty.

        :return: None
        '''
        while self.step_run():
            pass

    def step_run(self):
        '''
        Runs one loop of calling the trigger notify_observer methods.

        :return: Boolean - return True if and only if at least of the trigger classes are non-empty
        '''
        self.waiting_trigger.notify_observer(self.timestep_trigger)
        self.timestep_trigger.notify_observer()
        self.steps += 1

        if self.waiting_trigger.get_size() or self.timestep_trigger.get_size():
            return True
        return False

    def load(self, map_fp, profile_fp, order_fp, sample=False, verbose=False):
        '''
        Generates all the tiles and fix_state for the waiting_trigger.

        :param map_fp: String - file path to the map file
        :param profile_fp: String - file path to profile file
        :param order_fp: String/None - file path to order file (None if sample=True)
        :param sample - Boolean - enable random sampling
        :param verbose: Boolean - if True, print out message when there are no paths for some cars
        :return: None/(Int) => None - returns sampling function if sample=True else None
        '''
        if sample:
            self.ground, sampling_func = generate_map(map_fp, profile_fp, order_fp, self.waiting_trigger, sample=True)

            return sampling_func
        else:
            self.ground = generate_map(map_fp, profile_fp, order_fp, self.waiting_trigger)
            self.waiting_trigger.fix_state(verbose=verbose)

    def calculate(self):
        '''
        Calculates the score based on the steps needed for cars to reach their respective destination

        Note: Lower score indicates better performance

        :return: float - score of all cars
        '''
        return 0  # TODO: Calculate score

    def get_matrix(self):
        '''
        Extracts a mathematical representation of the ground.

        :return: np.array - 3D array of np
        '''
        ground = self.ground
        if ground is not None:
            matrix = list()
            for col in ground:
                vector = list()
                for tile in col:
                    if isinstance(tile, Home):
                        vector.append(HOME_VEC)
                    elif isinstance(tile, Hub):
                        vector.append(HUB_VEC)
                    elif isinstance(tile, Obst):
                        vector.append(OBST_VEC)
                    elif isinstance(tile, Road):
                        vector.append(ROAD_VEC)
                    elif isinstance(tile, Empty):
                        vector.append(EMPTY_VEC)
                matrix.append(vector)

            return np.array(matrix, dtype=np.float16)

        raise ValueError('Simulation is not loaded')

    def reset(self):
        '''
        Removes all instances of car agents in the simulation

        :return: None
        '''
        Car.delete_all()
        self.waiting_trigger.reset()
        self.timestep_trigger.reset()
        self.steps = 0

    def __str__(self):
        '''
        String representation of object

        :return: String
        '''
        if self.ground is None:
            raise ValueError('Simulation files are not loaded. '
                             'Call the Simulation.load method with the appropriate file types')

        tiles_list = ['  '.join([str(tile) for tile in row]) for row in self.ground]
        return '\n'.join(tiles_list)

    def _get_capacities(self):
        '''
        Gets a string representation of the map showing the capacities of each tile, if available.

        :return: String - formatted string of capacities
        '''
        if self.ground is None:
            raise ValueError('Simulation files are not loaded. '
                             'Call the Simulation.load method with the appropriate file types')

        tiles_list = [
            ' '.join([f'{len(tile.cars)}/{tile.capacity}' if isinstance(tile, Traversable) else '---' for tile in row])
            for row in self.ground]

        return '\n'.join(tiles_list)
