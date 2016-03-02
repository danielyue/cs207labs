from array import array
import reprlib
import math
import numbers
import functools
import operator
import itertools

class Vector:
    """
    Class that implements vector operations

    >>> v1 = Vector([3, 4])
    >>> v1
    Vector([3.0, 4.0])
    >>> v1 + [1,2]
    Vector([4.0, 6.0])
    >>> [1,2] + v1
    Vector([4.0, 6.0])
    >>> v1 + 3
    Vector([6.0, 7.0])
    >>> 3 + v1
    Vector([6.0, 7.0])
    >>> 3 + v1 == v1 + 3
    True
    >>> v1 - [1,2]
    Vector([2.0, 2.0])
    >>> v1 - 3
    Vector([0.0, 1.0])
    >>> v1 = Vector([3, 4])
    >>> 3 - v1
    Vector([-0.0, -1.0])
    >>> [5,5] - v1
    Vector([2.0, 1.0])
    >>> v1 = Vector([3, 4])
    >>> 3 * v1
    Vector([9.0, 12.0])
    >>> [5,5] * v1
    Vector([15.0, 20.0])
    """
    typecode = 'd'

    def __init__(self, components):
        """
        """
        self._components = array(self.typecode, components)

    def __iter__(self):
        return iter(self._components)

    def __repr__(self):
        components = reprlib.repr(self._components)
        components = components[components.find('['):-1]
        return 'Vector({})'.format(components)

    def __eq__(self, other):
        if isinstance(other, Vector):
            return (len(self) == len(other) and
                all(a == b for a, b in zip(self, other)))
        else:
            return NotImplemented

    def __abs__(self):
        return math.sqrt(sum(x * x for x in self))

    def __bool__(self):
        return bool(abs(self))

    def __len__(self):
        return len(self._components)

    def __getitem__(self, index):
        cls = type(self)

        if isinstance(index, slice):
            return cls(self._components[index])
        elif isinstance(index, numbers.Integral):
            return self._components[index]
        else:
            msg = '{.__name__} indices must be integers'
            raise TypeError(msg.format(cls))

    def __neg__(self):
        return Vector(-x for x in self)

    def __pos__(self):
        return Vector(self)

    def _check_length_helper(self , rhs):
        if not len(self)==len(rhs):
            raise ValueError(str(self)+' and '+str(rhs)+' must have the same length')

    def __add__(self, rhs):
        """
        """
        try:
            if isinstance(rhs, numbers.Real):
                return Vector(a + rhs for a in self)
            else: #
                self._check_length_helper(rhs)
                pairs = zip(self, rhs)
                return Vector(a + b for a, b in pairs)
        except TypeError:
            raise NotImplemented

    def __radd__(self, other): # other + self delegates to __add__
        """
        """
        return self + other

    def __sub__(self, rhs):
        """
        """
        try:
            if isinstance(rhs, numbers.Real):
                return Vector(a - rhs for a in self)
            else: #
                self._check_length_helper(rhs)
                pairs = zip(self, rhs)
                return Vector(a - b for a, b in pairs)
        except TypeError:
            raise NotImplemented

    def __rsub__(self, other): # other + self delegates to __add__
        """
        """
        return -(self - other)

    def __mul__(self, rhs):
        """
        """
        try:
            if isinstance(rhs, numbers.Real):
                return Vector(a * rhs for a in self)
            else: #
                self._check_length_helper(rhs)
                pairs = zip(self, rhs)
                return Vector(a * b for a, b in pairs)
        except TypeError:
            raise NotImplemented

    def __rmul__(self, other):
        return self * other
#### To run doctest:
from doctest import run_docstring_examples as dtest
dtest(Vector, globals(), verbose = True)
