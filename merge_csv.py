import pandas as pd

# Caminhos dos arquivos CSV
file1_path = 'otm grafos.csv'
file2_path = 'results_part1.csv'
file3_path = 'results.csv'

# Leitura dos arquivos CSV, ignorando a primeira linha em file2_path e file3_path
df1 = pd.read_csv(file1_path)
df2 = pd.read_csv(file2_path, skiprows=1)
df3 = pd.read_csv(file3_path, skiprows=1)

# Juntando os DataFrames em um único DataFrame
merged_df = pd.concat([df1, df2, df3], ignore_index=True)

# Salvando o DataFrame mesclado em um novo arquivo CSV
output_file_path = 'merged_file.csv'
merged_df.to_csv(output_file_path, index=False)

print(f'Os arquivos foram mesclados com sucesso em {output_file_path}.')
