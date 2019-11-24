from utils.constants import *
from collections import deque
from utils.priority_queue import PriorityQueue

FSCORE = 0
GSCORE = 1
CUR_TILE = 2
PREV_TUP = 3
DIR = 4


class PathFinder:

    def __init__(self, ground, heuristic):
        self.ground = ground
        self.heuristic = heuristic

    def find_path(self, x, y, desX, desY, car):
        heuristic = self.heuristic

        # format:             fScore,          gScore, current tile, previous tuple, direction
        #                       0                 1          2              3            4
        first_node = (heuristic(x, y, desX, desY), 0, car.cur_road, None, DEFAULT)
        open = PriorityQueue()
        open.push(first_node)
        closed = set()

        while not open.empty():
            node = open.pop()
            fScore, gScore, tile, prev, dir = node
            closed.add(tile)

            curX, curY = tile.get_coord()
            if curX == desX and curY == desY:
                return self.backtrack(node)

            neighbours = tile.neighbours
            for i in range(9):
                tile_neighbour = neighbours[i]

                if not tile_neighbour: continue
                if tile_neighbour in closed: continue

                childX, childY = tile_neighbour.get_coord()
                if not tile_neighbour.traversable() and not (childX == desX and childY == desY): continue

                if i > 3: i -= 1

                gScore_child = gScore + self.get_cost(i)
                child_relX, child_relY = KEYMAPPING[i]
                fScore_child = gScore_child + heuristic(child_relX + curX, child_relY + curY, desX, desY)

                find_result = open.find(tile_neighbour, key=lambda t: t[CUR_TILE])
                if find_result and gScore_child >= find_result[GSCORE]:
                    continue

                open.push((fScore_child, gScore_child, tile_neighbour, node, i))

    def get_cost(self, i):
        if i == NW or i == NE or i == SW or i == SE:
            return DIAG_COST
        return ORTHO_COST

    def backtrack(self, node):
        directions = deque()

        directions.append(node[PREV_TUP])
        while node[PREV_TUP]:
            directions.append(node[DIR])
            node = node[PREV_TUP]

        directions.reverse()
        directions.pop()

        return directions
