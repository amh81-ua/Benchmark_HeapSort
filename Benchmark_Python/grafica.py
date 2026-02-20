import subprocess
import matplotlib.pyplot as plt
import os
import sys

# Carpeta donde está grafica.py
base_dir = os.path.dirname(os.path.abspath(__file__))

# Subimos un nivel si grafica.py está dentro de Benchmark_Python
base_dir = os.path.abspath(os.path.join(base_dir, ".."))

# Ruta a la carpeta Release
release_dir = os.path.join(base_dir, "Release")

exe_cpp = os.path.join(release_dir, "BenchmarkComparation.exe")
exe_asm = os.path.join(release_dir, "Benchmark_ASM.exe")

print("Ejecutando version C++...")
resultado_cpp = subprocess.run(exe_cpp, capture_output=True, text=True)
tiempo_cpp = float(resultado_cpp.stdout.strip())

print("Ejecutando version ASM...")
resultado_asm = subprocess.run(exe_asm, capture_output=True, text=True)
tiempo_asm = float(resultado_asm.stdout.strip())

print(f"Tiempo C++: {tiempo_cpp} segundos")
print(f"Tiempo ASM: {tiempo_asm} segundos")

labels = ["C++", "ASM (x86 SSE)"]
tiempos = [tiempo_cpp, tiempo_asm]

plt.bar(labels, tiempos)
plt.ylabel("Tiempo (segundos)")
plt.title("Comparacion HeapSort C++ vs ASM")
plt.grid(axis="y", linestyle="--", alpha=0.7)

plt.show()