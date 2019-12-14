import os
import re
from controller.simulation import Simulation
from agents.car import Car


class TrainingSimulation:
    __doc__ = '''
    A class that sets up a simulation for training and refining of a reinforcement learning agent
    '''

    def __init__(self, map_dir, profile_dir, map_regex=r'map\d+\.txt', profile_regex=r'profile\d+\.txt'):
        self.sim = Simulation()

        map_files = list()
        profile_files = list()

        # recursively searches for all files
        for root, subdirs, files in os.walk(map_dir):
            map_files.extend([os.path.join(root, file) for file in files])
        for root, subdirs, files in os.walk(profile_dir):
            profile_files.extend([os.path.join(root, file) for file in files])

        self.map_files = re.findall(map_regex, ' '.join(map_files))
        self.profile_files = re.findall(profile_regex, ' '.join(profile_files))

    def visualize_samples(self, num_sample):

        for map_fp, profile_fp in zip(self.map_files, self.profile_files):

            sampling_func = self.sim.load(map_fp, profile_fp, None, sample=True)

            print(f'\nOriginal map of {map_fp}')
            print(self.sim)

            for sample in range(num_sample):
                print(f'\n> Beginning Simulation {sample} of {map_fp}')

                sampling_func(beta=2)

                self.sim.waiting_trigger.fix_state(verbose=True)
                Car._debug_check_route_all_cas()

                print('Initial loaded simulation map')
                print(self.sim)
                print('Ordering of car movements')
                print(self.sim.waiting_trigger)

                while self.sim.step_run():
                    print(f'[{self.sim.steps}]')
                    print(self.sim)

                print(f'Score: {self.sim.calculate()}')

                self.sim.reset()
