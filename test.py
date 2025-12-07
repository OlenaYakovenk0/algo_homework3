import os, subprocess, numpy as np, matplotlib.pyplot as plt, time
from scipy.optimize import linear_sum_assignment

def run_cpp(matrix):
    exe = "./build/Release/hungarian_cli.exe"
    if not os.path.exists(exe):
        exe = "./build/Debug/hungarian_cli.exe"

    n = matrix.shape[0]
    mat = matrix.astype(np.int64, copy=False)
    input_str = f"{n}\n" + "\n".join(" ".join(map(str, row)) for row in mat)

    res = subprocess.run([exe], input=input_str.encode(),
                         stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if res.returncode != 0:
        raise RuntimeError(res.stderr.decode())
    return float(res.stdout.decode().strip())

def run_scipy(matrix):
    cost = matrix.astype(np.float64, copy=False)
    t0 = time.perf_counter()
    linear_sum_assignment(cost)
    t1 = time.perf_counter()
    return t1 - t0

sizes = [10, 20, 40, 60, 80, 100, 150, 200, 250, 300]
repeats, warmup = 5, True
cpp_times, scipy_times = [], []
rng = np.random.default_rng(12345)

for n in sizes:
    base = rng.integers(1, 1000, size=(n, n), dtype=np.int64)
    if warmup:
        _ = run_cpp(base)
        _ = run_scipy(base)

    t_cpp = sum(run_cpp(base.copy()) for _ in range(repeats)) / repeats
    t_sci = sum(run_scipy(base.copy()) for _ in range(repeats)) / repeats

    cpp_times.append(t_cpp)
    scipy_times.append(t_sci)
    print(f"n={n}: C++ {t_cpp:.6f}s  |  SciPy {t_sci:.6f}s")

plt.figure(figsize=(10,6))
plt.plot(sizes, cpp_times, marker='o', label="Ваш C++ (Release/Debug авто)")
plt.plot(sizes, scipy_times, marker='s', label="SciPy (Hungarian)")
plt.xlabel("Розмір матриці n"); plt.ylabel("Час виконання (сек)")
plt.title("Порівняння швидкодії угорського алгоритму")
plt.grid(True); plt.legend(); plt.tight_layout(); plt.show()
