import argparse
import sys

import matplotlib.pyplot as plt


def main():
    parser = argparse.ArgumentParser(
        description="Построение графика зависимости времени обмена от размера сообщения"
    )
    parser.add_argument(
        "input_file",
        help="Путь к файлу с данными"
    )
    parser.add_argument(
        "output_file",
        help="Путь для сохранения графика"
    )
    args = parser.parse_args()

    sizes = []
    times = []
    try:
        with open(args.input_file, 'r') as f:
            for line_num, line in enumerate(f, start=1):
                line = line.strip()
                if not line or line.startswith('#'):
                    continue
                parts = line.split()
                if len(parts) != 2:
                    raise ValueError(
                        f"Строка {line_num}: ожидается 2 столбца, получено {len(parts)}"
                    )
                try:
                    size = float(parts[0])
                    time = float(parts[1])
                except ValueError as e:
                    raise ValueError(
                        f"Строка {line_num}: ошибка преобразования в число: {e}"
                    )
                sizes.append(size)
                times.append(time)
    except FileNotFoundError:
        sys.stderr.write(f"Ошибка: файл не найден '{args.input_file}'\n")
        sys.exit(1)
    except Exception as e:
        sys.stderr.write(f"Ошибка при чтении файла: {e}\n")
        sys.exit(1)

    if not sizes:
        sys.stderr.write("Ошибка: файл не содержит валидных данных для построения графика.\n")
        sys.exit(1)

    plt.figure(figsize=(10, 6))
    plt.plot(sizes, times, marker='o', linestyle='-', linewidth=2, markersize=6, color='blue')
    plt.xlabel('Размер сообщения m, байт', fontsize=12)
    plt.ylabel('Время обмена t, с', fontsize=12)
    plt.title('Зависимость t(m) времени обмена от размера сообщения', fontsize=14, fontweight='bold')
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.tight_layout()

    try:
        plt.savefig(args.output_file, dpi=300, bbox_inches='tight')
        print(f"График успешно сохранён в файл: {args.output_file}")
    except Exception as e:
        sys.stderr.write(f"Ошибка при сохранении графика: {e}\n")
        sys.exit(1)
    finally:
        plt.close()


if __name__ == "__main__":
    main()
