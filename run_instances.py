import os
import subprocess
import numpy as np
import time

def run_instance(instance_path, executables, alpha=0.75, runs=5):
    results = []

    for executable in executables:
        profits = []
        times = []

        for _ in range(runs):
            start_time = time.time()
            result = subprocess.run([executable, instance_path, str(alpha)], capture_output=True, text=True)
            end_time = time.time()

            runtime = end_time - start_time
            output_lines = result.stdout.splitlines()

            profit_line = next(line for line in output_lines if "Solution Profit:" in line)
            profit = int(profit_line.split(": ")[1])

            profits.append(profit)
            times.append(runtime)

        best_profit = max(profits)
        avg_profit = np.mean(profits)
        profit_cv = np.std(profits) / avg_profit if avg_profit != 0 else 0

        avg_time = np.mean(times)
        time_cv = np.std(times) / avg_time if avg_time != 0 else 0

        results.append((executable, best_profit, avg_profit, profit_cv, avg_time, time_cv))

    return results

def main():
    instance_dir = 'dckp_instances'
    executables = ['./tabu/main', './grasp/main', './ils/main']  # List of paths to the compiled C++ executables
    output_file = 'results.txt'

    with open(output_file, 'w') as f_out:
        f_out.write("Instance,Executable,Best Profit,Average Profit,Profit CV,Average Time,Time CV\n")

        for root, _, files in os.walk(instance_dir):
            for file in files:
                if file.endswith(".txt"):
                    instance_path = os.path.join(root, file)
                    results = run_instance(instance_path, executables)

                    for result in results:
                        executable, best_profit, avg_profit, profit_cv, avg_time, time_cv = result
                        f_out.write(f"{instance_path},{executable},{best_profit},{avg_profit},{profit_cv},{avg_time},{time_cv}\n")
                        print(f"Processed {instance_path} with {executable}")

if __name__ == "__main__":
    main()
