class PriorityQueue:
    __doc__ = '''
    Class for a min priority queue (using heaps)
    
    Time complexity of methods:
    * push - O(log n)
    * pop - O(log n)
    
    Note: Does not have type-checking functionality
    '''

    def __init__(self, key=lambda x: x[0]):
        '''
        Constructor for PriorityQueue

        :param key: (tuple(...)) => Int - indexing function as key
        '''
        self.container = list()
        self.key = key

    def push(self, obj):
        '''
        Pushes an object with a priority field and organizes appropriates

        :param obj: tuple(...) - object to store with priority field
        :return: None
        '''
        container = self.container
        key = self.key

        container.append(obj)
        length = len(container)
        k = length - 1

        # performs fix up
        while (k - 1) // 2 >= 0 and key(container[(k - 1) // 2]) > key(container[k]):
            parent_idx = (k - 1) // 2
            container[k], container[parent_idx] = container[parent_idx], container[k]
            k = parent_idx

    def pop(self):
        '''
        Pops and returns the root of the priority queue which has the lowest priority value.

        :return: <OBJECT_TYPE> - object stored with lowest priority value
        '''
        container = self.container
        key = self.key

        # non-empty check
        if len(container) == 0:
            raise IndexError('Pop method called on empty PriorityQueue')

        container[0], container[-1] = container[-1], container[0]
        obj = container.pop()  # temporarily stores the object

        length = len(container)
        k = 0

        # performs fix down
        while 2 * k + 1 < length:
            j = 2 * k + 1

            if j + 1 < length and key(container[j + 1]) < key(container[j]):
                j += 1

            if key(container[j]) >= key(container[k]):
                # guaranteed that invariant is preserved
                break

            container[j], container[k] = container[k], container[j]
            k = j

        return obj

    def find(self, item, key=lambda x: x[1]):
        '''
        Searches for an item in the priority queue using the given key

        :param item: <FIND_OBJECT_TYPE> - object to find
        :param key: (<OBJECT_TYPE>) => <FIND_OBJECT_TYPE> - key to index
        :return: <FIND_OBJECT_TYPE>/None - returns the object if found otherwise None
        '''
        for ele in self.container:
            if key(ele) == item:
                return ele
        return None

    def top(self):
        '''
        Returns a reference to the object at the top of the heap (lowest key)

        :return: <OBJECT_TYPE> - object stored at the top
        '''
        return self.container[0]

    def empty(self):
        '''
        Function to check if empty for convenience

        :return: Boolean - returns True if and only if empty
        '''
        return len(self.container) == 0

    def clear(self):
        '''
        Clear the container

        :return: None
        '''
        self.container.clear()

    def __iter__(self):
        return self.container.__iter__()

    def __len__(self):
        return len(self.container)

    def __contains__(self, item):
        return item in self.container
