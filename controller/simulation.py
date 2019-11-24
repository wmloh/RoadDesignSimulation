from tiles.traversable import Traversable
from controller.timestep import Timestep
from controller.waiting import Waiting
from utils.map_generator import generate_map


class Simulation:

    def __init__(self):
        self.ground = None
        self.steps = 0
        self.num_roads = 0  # undefined
        self.road_cost = 0  # undefined
        self.timestep_trigger = Timestep(self)
        self.waiting_trigger = Waiting(self)

    def init(self):
        while self.step_run():
            pass

    def step_run(self):
        self.waiting_trigger.notify_observer(self.timestep_trigger)
        self.timestep_trigger.notify_observer()
        self.steps += 1

        if self.waiting_trigger.get_size() or self.timestep_trigger.get_size():
            return True
        return False

    def load(self, map_fp, profile_fp, order_fp):
        self.ground = generate_map(map_fp, profile_fp, order_fp, self.waiting_trigger)
        self.waiting_trigger.fix_state()

    def calculate(self):
        return 0

    def __str__(self):
        if self.ground is None:
            raise ValueError('Simulation files are not loaded. '
                             'Call the Simulation.load method with the appropriate file types')
        tiles_list = ['  '.join([str(tile) for tile in row]) for row in self.ground]
        return '\n'.join(tiles_list)

    def _get_capacities(self):
        if self.ground is None:
            raise ValueError('Simulation files are not loaded. '
                             'Call the Simulation.load method with the appropriate file types')
        tiles_list = [' '.join([f'{len(tile.cars)}/{tile.capacity}' if isinstance(tile, Traversable) else '---' for tile in row]) for row in self.ground]
        return '\n'.join(tiles_list)
