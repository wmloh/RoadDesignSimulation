from interface.command_loop import CommandLoop

if __name__ == '__main__':
    cmd = CommandLoop(guide_path='./datasets/guide.txt', legend_path='./datasets/legend.txt')
    cmd.load_files('./datasets/map1.txt', './datasets/profile1.txt', './datasets/order1.csv')
    cmd.run()
