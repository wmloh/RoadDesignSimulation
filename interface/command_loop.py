from controller.simulation import Simulation


class CommandLoop:
    __doc__ = '''
    Command line interface for initiating and managing simulations.
    '''

    def __init__(self, guide_path=None, legend_path=None):
        '''
        Constructor for CommandLoop

        :param guide_path: String - path to guide(help) text file
        :param legend_path: String - path to legend text file
        '''
        self.sim = Simulation()
        self.guide_path = guide_path
        self.legend_path = legend_path

    def run(self):
        '''
        Runs a command loop with command line inputs.

        :return: None
        '''
        while True:
            command = input('Enter command: ')

            if command == 'help':
                print(self.help())
            elif command == 'legend':
                print(self.legend())
            elif command == 'init':
                self.sim.init()
            elif command == 'dev':
                self.dev_mode()
            elif command == 'show':
                print(self.sim)
            elif command == 'quit' or command == 'q':
                break
            else:
                print('Invalid command; enter "help" for more information')

    def dev_mode(self):
        print('### DEVELOPMENT MODE ACTIVATED ###')

        while True:
            command = input('Enter command: ')

            if command == 'help':
                print(self.help())
            elif command == 'legend':
                print(self.legend())
            elif command == 'init':
                self.sim.init()
            elif command == 'dev':
                pass
            elif command == 'show':
                print(self.sim)
            elif command == 'step':
                secondary = input()
                while secondary != 'stop':
                    if not self.sim.step_run():
                        break
                    print(self.sim)
                    secondary = input()
            elif command == 'cap':
                print(self.sim._get_capacities())
            elif command == 'quit' or command == 'q':
                break
            else:
                print('Invalid command; enter "help" for more information')

    def load_files(self, map_fp, profile_fp, order_fp):
        self.sim.load(map_fp, profile_fp, order_fp)

    def help(self):
        '''
        Reads the guide text file.

        :return: String - guide text
        '''
        if not self.guide_path:
            raise ValueError('Guide text is not loaded')

        with open(self.guide_path, 'r') as f:
            help_text = f.read()
        return help_text

    def legend(self):
        '''
        Reads the legend text file.

        :return: String - legend text
        '''
        if not self.legend_path:
            raise ValueError('Legend text is not loaded')

        with open(self.legend_path, 'r') as f:
            legend_text = f.read()
        return legend_text
