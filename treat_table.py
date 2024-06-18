import pandas as pd
import matplotlib.pyplot as plt
import re

# Leitura do arquivo .xlsx
file_path = 'otm grafos.csv'  # Caminho para o arquivo .xlsx
df = pd.read_csv(file_path)

def convert_instance(instance):
    match = re.search(r'dckp_instances/(\d+)/dckp_(\d+)_sum.txt', instance)
    if match:
        items = match.group(1)
        instance_num = match.group(2)
        return f"{items} Itens - Instancia {instance_num}"
    return instance

# Função para simplificar o valor de 'Executable'
def simplify_executable(executable):
    return executable.split('/')[1]

# Aplicando a conversão de 'Instance'
df["Instance"] = df["Instance"].apply(convert_instance)

df["Executable"] = df["Executable"].apply(simplify_executable)

output_file_path = 'tabela_processada.csv'
df.to_csv(output_file_path, index=False)

