import warnings
from search.pathFinder import PathFinder
from utils.constants import cost_function


class Waiting:

    def __init__(self, simulation):
        self.homes = list()
        self.backup = None
        self.simulation = simulation
        self.fixed = False
        self.pathfinder = PathFinder(simulation.ground, cost_function)

    def attach(self, ts, desX, desY, home, hub):
        if not self.fixed:
            self.homes.append((ts, desX, desY, home, hub))
        else:
            warnings.warn('Attempted to attach object to Waiting after fixing')

    def detach(self):
        if self.fixed:
            return self.homes.pop()[3]
        return None

    def notify_observer(self, timestep):
        while len(self.homes) and self.homes[-1][0] == self.simulation.steps:
            timestep.attach(self.homes[-1][3].cars[0])
            self.homes.pop()

    def fix_state(self):
        self.homes.sort(key=lambda x: x[0])
        self.backup = self.homes
        self.fixed = True

        for home in self.homes:
            ts, desX, desY, h, hub = home
            h.load_car(desX, desY, self.pathfinder, hub)

    def reset(self):
        self.homes = self.backup
        for home in self.homes:
            h = home[3]
            h.clear_cars()

    def get_size(self):
        return len(self.homes)

    def __str__(self):
        homes_list = list()
        for home in self.homes:
            home_string = f'[{home[0]}]\nStarts at: {home[3].get_coord()} -> ({home[1]}, {home[2]})'
            homes_list.append(home_string)

        return '\n'.join(homes_list)



