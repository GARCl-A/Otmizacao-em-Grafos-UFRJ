import os
import subprocess
import numpy as np
import time

def run_instance(instance_path, executables, alphas=None, runs=5):
    results = []

    for executable in executables:
        profits = []
        times = []

        if 'tabu' in executable:
            alpha_values = [None]  # No alpha parameter needed for ./tabu/main
        else:
            alpha_values = alphas  # Use alphas for grasp and ils executables

        for alpha in alpha_values:
            alpha_str = str(alpha) if alpha is not None else None

            for _ in range(runs):
                start_time = time.time()
                if alpha is None:
                    result = subprocess.run([executable, instance_path], capture_output=True, text=True)
                else:
                    result = subprocess.run([executable, instance_path, alpha_str], capture_output=True, text=True)
                end_time = time.time()

                runtime = end_time - start_time
                output_lines = result.stdout.splitlines()
                print(instance_path, output_lines, executable)

                profit_line = next(line for line in output_lines if "Solution Profit: " in line)
                profit = int(profit_line.split(": ")[1])

                profits.append(profit)
                times.append(runtime)

            best_profit = max(profits)
            avg_profit = np.mean(profits)
            profit_cv = np.std(profits) / avg_profit if avg_profit != 0 else 0

            avg_time = np.mean(times)
            time_cv = np.std(times) / avg_time if avg_time != 0 else 0

            results.append((instance_path, executable, alpha, best_profit, avg_profit, profit_cv, avg_time, time_cv))

    return results

def main():
    instance_dir = 'dckp_instances'
    tabu_executables = ['./tabu/main']
    grasp_executables = ['./grasp/main']
    ils_executables = ['./ils/main']
    alphas = [0.5, 0.75, 1.0]  # Different values of alpha to test for grasp and ils
    executables = tabu_executables + grasp_executables + ils_executables
    output_file = 'results.csv'

    with open(output_file, 'w') as f_out:
        f_out.write("Instance,Executable,Alpha,Best Profit,Average Profit,Profit CV,Average Time,Time CV\n")

        for root, _, files in os.walk(instance_dir):
            for file in files:
                if file.endswith(".txt"):
                    instance_path = os.path.join(root, file)
                    results = run_instance(instance_path, executables, alphas=alphas if 'main' in executables[0] else None)

                    for result in results:
                        instance_path, executable, alpha, best_profit, avg_profit, profit_cv, avg_time, time_cv = result
                        f_out.write(f"{instance_path},{executable},{alpha},{best_profit},{avg_profit},{profit_cv},{avg_time},{time_cv}\n")
                        print(f"Processed {instance_path} with {executable} and alpha {alpha}")

if __name__ == "__main__":
    main()
