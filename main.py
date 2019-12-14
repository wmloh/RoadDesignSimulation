import numpy as np
from configparser import ConfigParser
from interface.command_loop import CommandLoop
from interface.training_simulation import TrainingSimulation

if __name__ == '__main__':
    config = ConfigParser()
    config.read('config.ini')

    np.random.seed(int(config['SIMULATION_TYPE']['random_seed']))
    sim_type = config['SIMULATION_TYPE']['type']

    if sim_type == 'cmd':
        cmd = CommandLoop(**config['COMMAND_INIT_ARGS'])
        cmd.load_files(**config['COMMAND_LOAD_ARGS'])
        cmd.run()

    elif sim_type == 'train':
        train_sim = TrainingSimulation(**config['TRAIN_INIT_ARGS'])
        train_sim.visualize_samples(3)
