import os
import sys


def extract_swf_data(input_file, output_dir, m_count, start_index):
    n_machines = 4096

    output_filename = f"tasks_{m_count}_x_{n_machines}.txt"
    output_path = os.path.join(output_dir, output_filename)

    tasks = []

    try:
        with open(input_file, 'r') as f:
            current_task_num = 0
            for line in f:
                line = line.strip()
                if not line or line.startswith(';'):
                    continue

                current_task_num += 1

                if current_task_num < start_index:
                    continue

                parts = line.split()
                if len(parts) >= 5:
                    t_j = int(parts[3])
                    r_j = int(parts[4])

                    if t_j > 0 and r_j > 0:
                        tasks.append(f"{t_j} {r_j}")

                if len(tasks) >= m_count:
                    break

        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        with open(output_path, 'w') as out:
            out.write("\n".join(tasks))

        print(f"Write {len(tasks)} tasks to '{output_path}' starts from {start_index}")

    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    if len(sys.argv) < 5:
        print(f"Usage: python {sys.argv[0]} <input.swf> <output_dir> <count> <start_from>")
    else:
        extract_swf_data(sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4]))
