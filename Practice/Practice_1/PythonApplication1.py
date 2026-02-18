import time

def append_func(array, elem):
    array.append(elem)
    return array

def measure_execution_time(func, *args, **kw):
    start_time = time.time()
    result = func(*args, **kw)
    end_time = time.time()
    execution_time = (end_time - start_time) * 1000
    return result, execution_time

def main():
    arr_len = (10, 100, 1_000, 10_000, 100_000, 1_000_000, 10_000_000, 100_000_000, 250_000_000, 500_000_000)
    for ln in arr_len:
        arr = [0]*ln
        res, exec_time = measure_execution_time(append_func, arr, 1)
        print(f'Длина массива: {ln}; Время выполнения: {exec_time}')


main()
