import os
import re
from controller.simulation import Simulation
from agents.car import Car


class TrainingSimulation:
    __doc__ = '''
    A class that sets up a simulation for training and refining of a reinforcement learning agent
    '''

    def __init__(self, map_dir, profile_dir, map_regex=r'\.\S*?map\d+\.txt', profile_regex=r'\.\S*?profile\d+\.txt'):
        '''
        Constructor for TrainingSimulation

        :param map_dir: String - relative path to directory of maps
        :param profile_dir: String - relative path to directory of profiles
        :param map_regex: String - regex pattern to search for maps
        :param profile_regex: String - regex pattern to search for profile
        '''
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

    def visualize_samples(self, num_sample, beta=2, blocking=False, debug=False):
        '''
        Runs multiple samples of each map file while printing significant details

        :param num_sample: Int - number of samples for each map
        :param beta: float - scale parameter for exponential distribution to get timestep
        :param blocking: Boolean - if True, requires user input at every simulation loop
        :param debug: Boolean - if True, verifies that cars have a correct route
        :return: None
        '''

        for map_fp, profile_fp in zip(self.map_files, self.profile_files):

            # loads simulation and obtain sampling function
            sampling_func = self.sim.load(map_fp, profile_fp, None, sample=True)

            print(f'\nOriginal map of {map_fp}')
            print(self.sim)

            # sampling loop
            for sample in range(num_sample):
                print(f'\n> Beginning Simulation {sample} of {map_fp}')

                # sampling car origin-destination pairs
                sampling_func(beta=beta)
                self.sim.waiting_trigger.fix_state(verbose=True)

                if debug:  # verify correct routes
                    Car._debug_check_route_all_cars()

                print('Initial loaded simulation map')
                print(self.sim)
                print('Ordering of car movements')
                print(self.sim.waiting_trigger)

                # runs loop
                while self.sim.step_run():
                    print(f'[{self.sim.steps}]')
                    print(self.sim)
                    if blocking:
                        input()

                print(f'Score: {self.sim.calculate()}')

                self.sim.reset()  # resets the simulation parameters
