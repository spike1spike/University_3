import unittest

from PythonApplication1 import append_func

class TestAppend(unittest.TestCase):

    def test_empty_list(self):
        self.assertEqual(append_func([], 1), [1], 'Должно возвращать список с 1 элементом для пустого списка')

    def test_single_element(self):
        self.assertEqual(append_func([5], 1), [5, 1], 'Должно возвращать список с \"1\" в конце для списка с 1 элементом')

    def test_multiple_elemets(self):
        self.assertEqual(append_func([2, 6, 7, 8, 0], 1), [2, 6, 7, 8, 0, 1], 'Должно возвращать список с \"1\" в конце для списка с несколькими элементами')


if __name__ == '__main__':
    unittest.main()
