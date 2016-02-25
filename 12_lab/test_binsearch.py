from binsearch import binary_search
import unittest
import numpy as np

class BinarySearchTest(unittest.TestCase):
    def setUp(self):
        self.b = range(1000)
        self.infArray = [1,2,np.inf]

    def tearDown(self):
        del self.b

    def test_normal(self):
        self.assertEqual(binary_search(self.b,200), 200)
        self.assertEqual(binary_search(self.b,932), 932)

    def test_extremes(self):
        self.assertEqual(binary_search(self.b,0), 0)
        self.assertEqual(binary_search(self.b,999), 999)

    def test_missing(self):
        self.assertEqual(binary_search(self.b,-4),-1)
        self.assertEqual(binary_search(self.b,45.6),-1)
        self.assertEqual(binary_search(self.b,1000),-1)

    def test_infinity(self):
        self.assertEqual(binary_search(self.infArray,np.inf),2)

    def test_range(self):
        self.assertEqual(binary_search(self.b, 2, 1,3),2)
        self.assertEqual(binary_search(self.b, 2, 3,1),-1)
        self.assertEqual(binary_search(self.b, 3, 2,2),-1)
        self.assertEqual(binary_search(self.b, 5, 1,3),-1)

    def test_char(self):
        with self.assertRaises(TypeError):
            binary_search(self.b,'a')

    def test_nan(self):
        with self.assertRaises(TypeError):
            binary_search([np.NaN],4)

    def test_emptyArray(self):
        self.assertEqual(binary_search([],4),-1)

    def test_oneArray(self):
        self.assertEqual(binary_search([4],4),0)

    def test_twoArray(self):
        self.assertEqual(binary_search([2,4],4),1)
        self.assertEqual(binary_search([2,4],2),0)
