import matplotlib.pyplot as plt
import numpy as np

clusters = {
    "oak": {
        # "numa_mem": "results/oak/local_mem.txt",
        # "qpi_mem": "results/oak/qpi_mem.txt",
        "network": "results/oak/network.txt"
    },
    "pine": {
        # "numa_mem": "results/pine/local_mem.txt",
        # "qpi_mem": "results/pine/qpi_mem.txt",
        "network": "results/pine/network.txt"
    }
}

def load_data(filename):
    """Загружает два столбца: размер и среднее время."""
    sizes, times = [], []
    with open(filename) as f:
        for line in f:
            if line.startswith("#") or not line.strip():
                continue
            try:
                size, t = map(float, line.strip().split())
                sizes.append(size)
                times.append(t)
            except ValueError:
                continue
    return np.array(sizes), np.array(times)

colors = {
    # "numa_mem": "tab:blue",
    # "qpi_mem": "tab:orange",
    "network": "tab:green"
}

fig, axes = plt.subplots(1, 2, figsize=(14, 6))
fig.suptitle("Графики зависимости t(m) времени передачи сообщений: oak vs pine", fontsize=14, y=1.02)

for idx, (cluster_name, files) in enumerate(clusters.items()):
    ax = axes[idx]

    for test_name, path in files.items():
        sizes, times = load_data(path)
        if len(sizes) == 0:
            print(f"⚠️ Warning: no data in {path}")
            continue

        ax.plot(
            sizes / (1024 * 1024),
            times,
            label=test_name.replace("_", " "),
            color=colors[test_name],
            marker="o",
            markersize=4,
            linewidth=2
        )

    ax.set_xlabel("Размер сообщения (MB)")
    ax.set_ylabel("Среднее время передачи t(m) (сек)")
    ax.set_title(f"Кластер: {cluster_name}")
    ax.legend()
    ax.grid(True, linestyle="--", linewidth=0.5, alpha=0.7)

all_times = []
for cluster_files in clusters.values():
    for test_path in cluster_files.values():
        sizes, times = load_data(test_path)
        if len(times) > 0:
            all_times.extend(times)

if all_times:
    max_time = max(all_times) * 1.1
    for ax in axes:
        ax.set_ylim(bottom=0, top=max_time)

plt.tight_layout()
plt.savefig("results/network.png", dpi=300, bbox_inches='tight')
print("График сохранён в results/compare_oak_pine.png")
