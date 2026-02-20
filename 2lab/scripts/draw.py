import os
import sys

import matplotlib.pyplot as plt


def build_runtime_plots(input_dir, output_file):
    # Проверка существования директории
    if not os.path.isdir(input_dir):
        print(f"Ошибка: Директория {input_dir} не найдена.")
        return

    plt.figure(figsize=(10, 7))

    # Получаем список файлов и сортируем их
    files = sorted([f for f in os.listdir(input_dir) if f.endswith('.txt')])

    if not files:
        print("В директории нет .txt файлов.")
        return

    for filename in files:
        m_tasks = []
        runtime = []

        file_path = os.path.join(input_dir, filename)
        with open(file_path, 'r') as f:
            for line in f:
                parts = line.split()
                if len(parts) >= 2:
                    try:
                        m_tasks.append(int(parts[0]))
                        runtime.append(float(parts[1]))
                    except ValueError:
                        continue

        # Сортируем данные по количеству задач, чтобы линия на графике не "прыгала"
        data = sorted(zip(m_tasks, runtime))
        x_vals, y_vals = zip(*data)

        # Имя файла для легенды
        label_name = os.path.splitext(filename)[0]
        plt.plot(x_vals, y_vals, marker='s', markersize=4, label=label_name)

    # Оформление
    plt.title('Зависимость времени выполнения от количества задач', fontsize=14)
    plt.xlabel('Количество задач (m)', fontsize=12)
    plt.ylabel('Время выполнения (сек)', fontsize=12)

    plt.grid(True, which='both', linestyle='--', alpha=0.5)
    plt.legend(title="Алгоритм и параметры")

    # Улучшаем компоновку, чтобы подписи не обрезались
    plt.tight_layout()

    # Сохранение
    plt.savefig(output_file, dpi=300)
    print(f"График зависимости времени сохранен в: {output_file}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Использование: python build_plots.py <input_dir> <output_png_name>")
    else:
        build_runtime_plots(sys.argv[1], sys.argv[2])
