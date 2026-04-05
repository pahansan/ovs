import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("data/table.csv", sep=";")

theta_vectors = []
t_vectors = []
n_values_list = []

for idx, row in df.iterrows():
    theta_vec = [float(x) for x in row["theta"].split(",")]
    t_vec = [float(x) for x in row["t"].split(",")]

    n_start = int(row["n"])
    n_vals = list(range(n_start, n_start + len(theta_vec)))

    theta_vectors.append(theta_vec)
    t_vectors.append(t_vec)
    n_values_list.append(n_vals)

df["theta_list"] = theta_vectors
df["t_list"] = t_vectors
df["n_vals"] = n_values_list

plt.rcParams["font.size"] = 11
plt.rcParams["axes.labelsize"] = 12
plt.rcParams["axes.titlesize"] = 13
plt.rcParams["legend.fontsize"] = 10
plt.rcParams["figure.facecolor"] = "white"
plt.rcParams["axes.facecolor"] = "white"
plt.rcParams["grid.color"] = "black"
plt.rcParams["grid.linewidth"] = 0.5
plt.rcParams["grid.linestyle"] = "-"
plt.rcParams["axes.edgecolor"] = "black"
plt.rcParams["axes.linewidth"] = 1

fig, axes = plt.subplots(2, 3, figsize=(16, 10))
fig.suptitle(
    "Зависимость θ(n) и T(n) для живучей распределенной вычислительной системы\nN = 65536, n ∈ [65527, 65536]",
    fontsize=14,
    fontweight="bold",
)
fig.patch.set_facecolor("white")

ax1 = axes[0, 0]
lambda_val = 1e-5
m_val = 1
mu_values = [1, 10, 100, 1000]

for mu in mu_values:
    subset = df[(df["lambda"] == lambda_val) & (df["mu"] == mu) & (df["m"] == m_val)]
    if not subset.empty:
        row = subset.iloc[0]
        n_vals = row["n_vals"]
        theta_vals = row["theta_list"]
        ax1.plot(n_vals, theta_vals, "o-", label=f"μ = {mu}", linewidth=2, markersize=4)

ax1.set_xlabel("n (минимальное число работоспособных ЭМ)")
ax1.set_ylabel("θ(n) (среднее время безотказной работы, ч)")
ax1.set_title("θ(n) при различных μ\nλ = 1e-5, m = 1")
ax1.set_yscale("log")
ax1.legend()
ax1.grid(True, alpha=0.3, color="black")
ax1.set_xlim(65525, 65537)
ax1.set_facecolor("white")

ax2 = axes[0, 1]
mu_val = 1
m_val = 1
lambda_values = [1e-7, 1e-6, 1e-5]

for lam in lambda_values:
    subset = df[(df["lambda"] == lam) & (df["mu"] == mu_val) & (df["m"] == m_val)]
    if not subset.empty:
        row = subset.iloc[0]
        n_vals = row["n_vals"]
        theta_vals = row["theta_list"]
        ax2.plot(
            n_vals, theta_vals, "o-", label=f"λ = {lam:.0e}", linewidth=2, markersize=4
        )

ax2.set_xlabel("n (минимальное число работоспособных ЭМ)")
ax2.set_ylabel("θ(n) (среднее время безотказной работы, ч)")
ax2.set_title("θ(n) при различных λ\nμ = 1, m = 1")
ax2.set_yscale("log")
ax2.legend()
ax2.grid(True, alpha=0.3, color="black")
ax2.set_xlim(65525, 65537)
ax2.set_facecolor("white")

ax3 = axes[0, 2]
lambda_val = 1e-5
mu_val = 1
m_values = [1, 2, 3]

for m_val_plot in m_values:
    subset = df[
        (df["lambda"] == lambda_val) & (df["mu"] == mu_val) & (df["m"] == m_val_plot)
    ]
    if not subset.empty:
        row = subset.iloc[0]
        n_vals = row["n_vals"]
        theta_vals = row["theta_list"]
        ax3.plot(
            n_vals,
            theta_vals,
            "o-",
            label=f"m = {m_val_plot}",
            linewidth=2,
            markersize=4,
        )

ax3.set_xlabel("n (минимальное число работоспособных ЭМ)")
ax3.set_ylabel("θ(n) (среднее время безотказной работы, ч)")
ax3.set_title("θ(n) при различных m\nλ = 1e-5, μ = 1")
ax3.set_yscale("log")
ax3.legend()
ax3.grid(True, alpha=0.3, color="black")
ax3.set_xlim(65525, 65537)
ax3.set_facecolor("white")

ax4 = axes[1, 0]
lambda_val = 1e-5
m_val = 1
mu_values = [1, 10, 100, 1000]

for mu in mu_values:
    subset = df[(df["lambda"] == lambda_val) & (df["mu"] == mu) & (df["m"] == m_val)]
    if not subset.empty:
        row = subset.iloc[0]
        n_vals = row["n_vals"]
        t_vals = row["t_list"]
        ax4.plot(n_vals, t_vals, "o-", label=f"μ = {mu}", linewidth=2, markersize=4)

ax4.set_xlabel("n (минимальное число работоспособных ЭМ)")
ax4.set_ylabel("T(n) (среднее время восстановления, ч)")
ax4.set_title("T(n) при различных μ\nλ = 1e-5, m = 1")
ax4.set_yscale("log")
ax4.legend()
ax4.grid(True, alpha=0.3, color="black")
ax4.set_xlim(65525, 65537)
ax4.set_facecolor("white")

ax5 = axes[1, 1]
mu_val = 1
m_val = 1
lambda_values = [1e-7, 1e-6, 1e-5]

for lam in lambda_values:
    subset = df[(df["lambda"] == lam) & (df["mu"] == mu_val) & (df["m"] == m_val)]
    if not subset.empty:
        row = subset.iloc[0]
        n_vals = row["n_vals"]
        t_vals = row["t_list"]
        ax5.plot(
            n_vals, t_vals, "o-", label=f"λ = {lam:.0e}", linewidth=2, markersize=4
        )

ax5.set_xlabel("n (минимальное число работоспособных ЭМ)")
ax5.set_ylabel("T(n) (среднее время восстановления, ч)")
ax5.set_title("T(n) при различных λ\nμ = 1, m = 1")
ax5.set_yscale("log")
ax5.legend()
ax5.grid(True, alpha=0.3, color="black")
ax5.set_xlim(65525, 65537)
ax5.set_facecolor("white")

ax6 = axes[1, 2]
lambda_val = 1e-5
mu_val = 1
m_values = [1, 2, 3]

for m_val_plot in m_values:
    subset = df[
        (df["lambda"] == lambda_val) & (df["mu"] == mu_val) & (df["m"] == m_val_plot)
    ]
    if not subset.empty:
        row = subset.iloc[0]
        n_vals = row["n_vals"]
        t_vals = row["t_list"]
        ax6.plot(
            n_vals, t_vals, "o-", label=f"m = {m_val_plot}", linewidth=2, markersize=4
        )

ax6.set_xlabel("n (минимальное число работоспособных ЭМ)")
ax6.set_ylabel("T(n) (среднее время восстановления, ч)")
ax6.set_title("T(n) при различных m\nλ = 1e-5, μ = 1")
ax6.set_yscale("log")
ax6.legend()
ax6.grid(True, alpha=0.3, color="black")
ax6.set_xlim(65525, 65537)
ax6.set_facecolor("white")

fig1, ax1_ind = plt.subplots(figsize=(10, 6))
fig1.patch.set_facecolor("white")
lambda_val = 1e-5
for mu in [1, 10, 100, 1000]:
    subset = df[(df["lambda"] == lambda_val) & (df["mu"] == mu) & (df["m"] == 1)]
    if not subset.empty:
        row = subset.iloc[0]
        ax1_ind.plot(
            row["n_vals"],
            row["theta_list"],
            "o-",
            label=f"μ = {mu}",
            linewidth=2,
            markersize=6,
        )
ax1_ind.set_xlabel("n (минимальное число работоспособных ЭМ)", fontsize=12)
ax1_ind.set_ylabel("θ(n) (среднее время безотказной работы, ч)", fontsize=12)
ax1_ind.set_title("Зависимость θ(n) от μ\nλ = 1e-5, m = 1", fontsize=14)
ax1_ind.set_yscale("log")
ax1_ind.legend()
ax1_ind.grid(True, alpha=0.3, color="black")
ax1_ind.set_facecolor("white")
plt.tight_layout()
plt.savefig(
    "png_plots/plot1_theta_vs_mu.png", dpi=150, bbox_inches="tight", facecolor="white"
)

fig2, ax2_ind = plt.subplots(figsize=(10, 6))
fig2.patch.set_facecolor("white")
mu_val = 1
for lam in [1e-7, 1e-6, 1e-5]:
    subset = df[(df["lambda"] == lam) & (df["mu"] == mu_val) & (df["m"] == 1)]
    if not subset.empty:
        row = subset.iloc[0]
        ax2_ind.plot(
            row["n_vals"],
            row["theta_list"],
            "o-",
            label=f"λ = {lam:.0e}",
            linewidth=2,
            markersize=6,
        )
ax2_ind.set_xlabel("n (минимальное число работоспособных ЭМ)", fontsize=12)
ax2_ind.set_ylabel("θ(n) (среднее время безотказной работы, ч)", fontsize=12)
ax2_ind.set_title("Зависимость θ(n) от λ\nμ = 1, m = 1", fontsize=14)
ax2_ind.set_yscale("log")
ax2_ind.legend()
ax2_ind.grid(True, alpha=0.3, color="black")
ax2_ind.set_facecolor("white")
plt.tight_layout()
plt.savefig(
    "png_plots/plot2_theta_vs_lambda.png",
    dpi=150,
    bbox_inches="tight",
    facecolor="white",
)

fig3, ax3_ind = plt.subplots(figsize=(10, 6))
fig3.patch.set_facecolor("white")
lambda_val = 1e-5
mu_val = 1
for m_val_plot in [1, 2, 3]:
    subset = df[
        (df["lambda"] == lambda_val) & (df["mu"] == mu_val) & (df["m"] == m_val_plot)
    ]
    if not subset.empty:
        row = subset.iloc[0]
        ax3_ind.plot(
            row["n_vals"],
            row["theta_list"],
            "o-",
            label=f"m = {m_val_plot}",
            linewidth=2,
            markersize=6,
        )
ax3_ind.set_xlabel("n (минимальное число работоспособных ЭМ)", fontsize=12)
ax3_ind.set_ylabel("θ(n) (среднее время безотказной работы, ч)", fontsize=12)
ax3_ind.set_title("Зависимость θ(n) от m\nλ = 1e-5, μ = 1", fontsize=14)
ax3_ind.set_yscale("log")
ax3_ind.legend()
ax3_ind.grid(True, alpha=0.3, color="black")
ax3_ind.set_facecolor("white")
plt.tight_layout()
plt.savefig(
    "png_plots/plot3_theta_vs_m.png", dpi=150, bbox_inches="tight", facecolor="white"
)

fig4, ax4_ind = plt.subplots(figsize=(10, 6))
fig4.patch.set_facecolor("white")
lambda_val = 1e-5
for mu in [1, 10, 100, 1000]:
    subset = df[(df["lambda"] == lambda_val) & (df["mu"] == mu) & (df["m"] == 1)]
    if not subset.empty:
        row = subset.iloc[0]
        ax4_ind.plot(
            row["n_vals"],
            row["t_list"],
            "o-",
            label=f"μ = {mu}",
            linewidth=2,
            markersize=6,
        )
ax4_ind.set_xlabel("n (минимальное число работоспособных ЭМ)", fontsize=12)
ax4_ind.set_ylabel("T(n) (среднее время восстановления, ч)", fontsize=12)
ax4_ind.set_title("Зависимость T(n) от μ\nλ = 1e-5, m = 1", fontsize=14)
ax4_ind.set_yscale("log")
ax4_ind.legend()
ax4_ind.grid(True, alpha=0.3, color="black")
ax4_ind.set_facecolor("white")
plt.tight_layout()
plt.savefig(
    "png_plots/plot4_T_vs_mu.png", dpi=150, bbox_inches="tight", facecolor="white"
)

fig5, ax5_ind = plt.subplots(figsize=(10, 6))
fig5.patch.set_facecolor("white")
mu_val = 1
for lam in [1e-7, 1e-6, 1e-5]:
    subset = df[(df["lambda"] == lam) & (df["mu"] == mu_val) & (df["m"] == 1)]
    if not subset.empty:
        row = subset.iloc[0]
        ax5_ind.plot(
            row["n_vals"],
            row["t_list"],
            "o-",
            label=f"λ = {lam:.0e}",
            linewidth=2,
            markersize=6,
        )
ax5_ind.set_xlabel("n (минимальное число работоспособных ЭМ)", fontsize=12)
ax5_ind.set_ylabel("T(n) (среднее время восстановления, ч)", fontsize=12)
ax5_ind.set_title("Зависимость T(n) от λ\nμ = 1, m = 1", fontsize=14)
ax5_ind.set_yscale("log")
ax5_ind.legend()
ax5_ind.grid(True, alpha=0.3, color="black")
ax5_ind.set_facecolor("white")
plt.tight_layout()
plt.savefig(
    "png_plots/plot5_T_vs_lambda.png", dpi=150, bbox_inches="tight", facecolor="white"
)

fig6, ax6_ind = plt.subplots(figsize=(10, 6))
fig6.patch.set_facecolor("white")
lambda_val = 1e-5
mu_val = 1
for m_val_plot in [1, 2, 3]:
    subset = df[
        (df["lambda"] == lambda_val) & (df["mu"] == mu_val) & (df["m"] == m_val_plot)
    ]
    if not subset.empty:
        row = subset.iloc[0]
        ax6_ind.plot(
            row["n_vals"],
            row["t_list"],
            "o-",
            label=f"m = {m_val_plot}",
            linewidth=2,
            markersize=6,
        )
ax6_ind.set_xlabel("n (минимальное число работоспособных ЭМ)", fontsize=12)
ax6_ind.set_ylabel("T(n) (среднее время восстановления, ч)", fontsize=12)
ax6_ind.set_title("Зависимость T(n) от m\nλ = 1e-5, μ = 1", fontsize=14)
ax6_ind.set_yscale("log")
ax6_ind.legend()
ax6_ind.grid(True, alpha=0.3, color="black")
ax6_ind.set_facecolor("white")
plt.tight_layout()
plt.savefig(
    "png_plots/plot6_T_vs_m.png", dpi=150, bbox_inches="tight", facecolor="white"
)
