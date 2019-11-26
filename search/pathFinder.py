from utils.constants import *
from collections import deque
from utils.priority_queue import PriorityQueue

FSCORE = 0
GSCORE = 1
CUR_TILE = 2
PREV_TUP = 3
DIR = 4


class PathFinder:
    __doc__ = '''
    Class that implements the A* search algorithm that integrates with the simulation mechanics
    '''

    def __init__(self, ground, heuristic):
        '''
        Constructor for PathFinder

        :param ground: np.ndarray - 2D array of tiles
        :param heuristic: (Int, Int, Int, Int) => Int - cost function as a heuristic function to be minimized
        '''
        self.ground = ground
        self.heuristic = heuristic

    def find_path(self, x, y, desX, desY, car):
        '''
        Runs the A* search algorithm using the heuristic function.

        :param x: Int - current x-coordinate
        :param y: Int - current y-coordinate
        :param desX: Int - destination x-coordinate
        :param desY: Int - destination y-coordinate
        :param car: Car - reference to Car object
        :return: deque/None - return a deque object containing directions in order if a
                              route exists, otherwise None
        '''
        heuristic = self.heuristic

        # format:             fScore,          gScore, current tile, previous tuple, direction
        #                       0                 1          2              3            4
        first_node = (heuristic(x, y, desX, desY), 0, car.cur_road, None, DEFAULT)
        open = PriorityQueue()
        open.push(first_node)  # begins with the original node
        closed = set()

        while not open.empty():
            node = open.pop()
            fScore, gScore, tile, prev, dir = node
            closed.add(tile)

            curX, curY = tile.get_coord()
            if curX == desX and curY == desY:  # destination reached!
                return self.backtrack(node)

            neighbours = tile.neighbours
            for i in range(9):
                tile_neighbour = neighbours[i]

                # skip None
                if not tile_neighbour: continue
                # skip tiles already considered
                if tile_neighbour in closed: continue

                childX, childY = tile_neighbour.get_coord()
                # skip if tile is not traversable (and not the destination)
                if not tile_neighbour.traversable() and not (childX == desX and childY == desY): continue

                if i > 3: i -= 1  # calibration due to discrepancy

                # builds upon the cost from the original tile
                gScore_child = gScore + self.get_cost(i)
                # gets relative direction from the original tile
                child_relX, child_relY = KEYMAPPING[i]
                fScore_child = gScore_child + heuristic(child_relX + curX, child_relY + curY, desX, desY)

                # finds results if exists
                find_result = open.find(tile_neighbour, key=lambda t: t[CUR_TILE])
                if find_result and gScore_child >= find_result[GSCORE]:
                    # skips if results exists and has a higher g-score
                    continue

                # push into priority queue
                open.push((fScore_child, gScore_child, tile_neighbour, node, i))

        return None  # no route can be found

    def get_cost(self, i):
        '''
        Performs a mapping of direction to costs

        :param i: Int - direction
        :return: Int - cost for the direction
        '''
        if i == NW or i == NE or i == SW or i == SE:
            return DIAG_COST
        return ORTHO_COST

    def backtrack(self, node):
        '''
        Recursively traces back starting from the initial end node that reached the destination
        to obtain a linear forward order of directions to take.

        :param node: tuple(Int, Int, Traversable, tuple(node)/None, Int) - final node containing all previous nodes
        :return: deque - ordered queue of directions to take
        '''
        directions = deque()

        directions.append(node[PREV_TUP])
        while node[PREV_TUP]:
            directions.append(node[DIR])
            node = node[PREV_TUP]

        directions.reverse()
        directions.pop()  # removes the base case recursion

        return directions
