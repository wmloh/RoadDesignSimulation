from abc import ABC, abstractmethod


class Tile(ABC):
    __doc__ = '''
    Abstract class for a generic Tile that provides some methods and enforces implementation
    of certain methods
    '''

    def __init__(self, x, y):
        '''
        Abstract constructor for a Tile

        :param x: Int - x-coordinate of the tile
        :param y: Int - y-coordinate of the tile
        '''
        self.x = x
        self.y = y
        self.neighbours = list()

    def add_neighbours(self, tile):
        '''
        Appends neighbours into the Tile

        :param tile: Tile - reference to a neighbouring tile
        :return: None
        '''
        self.neighbours.append(tile)

    def convert_tile(self, constructor, ground):
        '''
        Converts this tile to another type while preserving invariants that are
        independent of the tile type

        :param constructor: (Int, Int, Int) => Traversable - constructor for a Traversable tile
        :param ground: np.ndarray - reference to the simulation ground
        :return: None
        '''
        constructed_tile = constructor(self.x, self.y, 1)
        constructed_tile.neighbours = self.neighbours  # preserve neighbours

        max_idx = len(self.neighbours) - 1
        # updates affected neighbours
        for idx, neighbour in enumerate(self.neighbours):
            if neighbour:
                neighbour.neighbours[max_idx - idx] = constructed_tile

        # replaces current tile with the constructed tile
        ground[self.y][self.x] = constructed_tile

    def get_coord(self):
        '''
        Returns the coordinates

        :return: tuple - x,y-coordinates of the Tile
        '''
        return (self.x, self.y)

    @abstractmethod
    def to_vector(self):
        '''
        Returns a vector representation of this tile
        :return: list(Int) - vector of 5 dimensions
        '''
        raise NotImplementedError()

    @abstractmethod
    def traversable(self):
        '''
        Return whether cars can drive to this tile
        :return: Boolean
        '''
        raise NotImplementedError()

    @abstractmethod
    def __str__(self):
        raise NotImplementedError()
