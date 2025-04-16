import matplotlib.pyplot as plt
import numpy as np

def read_data(filename):
    with open(filename, 'r') as f:
        data = np.array([list(map(float, line.strip().split())) for line in f])
    return data[:, 0], data[:, 1]

# Чтение всех необходимых данных
x_size, y_c_size = read_data('text_data/c_size.txt')
_, y_std_size = read_data('text_data/std_sort_size.txt')

x_unsort, y_c_unsort = read_data('text_data/c_unsort.txt')
_, y_std_unsort = read_data('text_data/std_sort_unsort.txt')

x_radix, y_c_radix = read_data('text_data/c_radix.txt')
_, y_std_radix = read_data('text_data/std_sort_radix.txt')

# 1. Основной график сравнения по размеру
plt.figure(figsize=(10, 6))
plt.plot(x_size, y_c_size, 'b-o', label='Radix Sort (C)')
plt.plot(x_size, y_std_size, 'r--s', label='std::sort (C++)')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Размер массива')
plt.ylabel('Время сортировки (сек)')
plt.title('Сравнение времени сортировки по размеру массива')
plt.grid(True, which="both", ls="-")
plt.legend()
plt.savefig('size_comparison.png', dpi=300, bbox_inches='tight')
plt.close()

# 2. График сравнения по степени упорядоченности (два подграфика)
plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
plt.plot(x_unsort, y_c_unsort, 'g-^', label='Radix Sort')
plt.xlabel('Степень упорядоченности')
plt.ylabel('Время (сек)')
plt.title('Radix Sort: зависимость от упорядоченности')
plt.grid(True)
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(x_unsort, y_std_unsort, 'm-*', label='std::sort')
plt.xlabel('Степень упорядоченности')
plt.ylabel('Время (сек)')
plt.title('std::sort: зависимость от упорядоченности')
plt.grid(True)
plt.legend()

plt.suptitle('Сравнение зависимости от степени упорядоченности')
plt.tight_layout()
plt.savefig('unsort_comparison.png', dpi=300, bbox_inches='tight')
plt.close()

# 3. График сравнения по количеству разрядов (два подграфика)
plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
plt.plot(x_radix, y_c_radix, 'c-D', label='Radix Sort')
plt.xlabel('Количество разрядов')
plt.ylabel('Время (сек)')
plt.title('Radix Sort: зависимость от разрядов')
plt.grid(True)
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(x_radix, y_std_radix, 'y-p', label='std::sort')
plt.xlabel('Количество разрядов')
plt.ylabel('Время (сек)')
plt.title('std::sort: зависимость от разрядов')
plt.grid(True)
plt.legend()

plt.suptitle('Сравнение зависимости от количества разрядов')
plt.tight_layout()
plt.savefig('radix_comparison.png', dpi=300, bbox_inches='tight')
plt.close()