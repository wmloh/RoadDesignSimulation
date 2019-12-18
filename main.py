import numpy as np
from configparser import ConfigParser
from utils.config_converter import convert_parameters
from interface.command_loop import CommandLoop
from interface.training_simulation import TrainingSimulation

if __name__ == '__main__':
    # reads config.ini
    config = ConfigParser()
    config.read('config.ini')
    config = convert_parameters(config)

    # sets random seed
    np.random.seed(int(config['SIMULATION_TYPE']['random_seed']))

    sim_type = config['SIMULATION_TYPE']['type']
    if sim_type == 'cmd':
        # command loop
        cmd = CommandLoop(**config['COMMAND_INIT_ARGS'])
        cmd.load_files(**config['COMMAND_LOAD_ARGS'])
        cmd.run()

    elif sim_type == 'train':
        # training simulation
        train_sim = TrainingSimulation(**config['TRAIN_INIT_ARGS'])

        if config['TRAIN_CONTROL_FLOW']['visualize']:
            train_sim.visualize_samples(**config['TRAIN_VISUALIZE'])

        if config['TRAIN_CONTROL_FLOW']['generate']:
            pass  # TODO: Incomplete
