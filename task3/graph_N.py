import matplotlib.pyplot as plt
import numpy as np

# Функция для чтения данных из файла
def read_data_from_file(filename):
    unsort_deg = []
    size       = []
    time1      = []
    time2      = []
    time3      = []

    with open(filename, 'r') as file:
        for line in file:
            data = line.split()
            if len(data) == 5:  # Проверяем, что строка содержит 4 значения
                size.append(int(data[0]))
                unsort_deg.append(float(data[1]))
                time1.append(float(data[2]))
                time2.append(float(data[3]))
                time3.append(float(data[4]))

    return np.array(size), np.array(unsort_deg), np.array(time1), np.array(time2), np.array(time3)

# Функция для построения графика
def plot_graph_deg(unsort_deg, time1, time2, time3):
    plt.figure(figsize=(10, 6))

    plt.plot(unsort_deg, time1, label="Sort2", marker='o')
    plt.plot(unsort_deg, time2, label="Shaker Sort", marker='s')
    plt.plot(unsort_deg, time3, label="Comb Sort", marker='^')

    plt.title("Time Dependency on Unsorted Degree")
    plt.xlabel("Unsorted Degree (%)")
    plt.ylabel("Time (seconds)")
    plt.legend()
    plt.grid(True)
    plt.show()

def plot_graph_size(size, time1, time2, time3):
    plt.figure(figsize=(10, 6))

    plt.plot(size, time1, label="Sort2", marker='o')
    plt.plot(size, time2, label="Shaker Sort", marker='s')
    plt.plot(size, time3, label="Comb Sort", marker='^')

    plt.title("Time Dependency on Array Size (Log Scale)")
    plt.xlabel("Array Size")
    plt.ylabel("Time (seconds)")
    
    # Установка логарифмического масштаба по оси X
    plt.xscale("log")
    
    # Добавление сетки для логарифмического масштаба
    plt.grid(which="both", linestyle='--', linewidth=0.5)
    
    plt.legend()
    plt.show()




# Главная функция
if __name__ == "__main__":
    filename_deg  = "time_deg.txt"
    filename_size = "time_size.txt"
    size, unsort_deg, time1, time2, time3 = read_data_from_file(filename_deg)
    plot_graph_deg (unsort_deg, time1, time2, time3)

    size_2, unsort_deg_2, time1_2, time2_2, time3_2 = read_data_from_file(filename_size)
    plot_graph_size(      size_2, time1_2, time2_2, time3_2)