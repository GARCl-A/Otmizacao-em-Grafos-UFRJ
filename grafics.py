import pandas as pd
import matplotlib.pyplot as plt

# Leitura do arquivo .csv processado
file_path = 'tabela_processada.csv'  # Caminho para o arquivo processado
df = pd.read_csv(file_path)

# Função para extrair número de itens e número da instância
def extrair_numeros(instancia):
    # Extrai o número de itens e o número da instância convertendo os valores após os últimos espaços
    partes = instancia.split()
    numero_itens = int(partes[0])
    numero_instancia = int(partes[-1])
    return numero_itens, numero_instancia

# Função para plotar gráfico comparando valores de Alpha para um dado Executable
def plot_comparison(df, executable, output_image_path):
    # Filtrando os dados para incluir apenas os registros do Executable especificado
    df_exec = df[df["Executable"] == executable]

    # Verificando se há dados suficientes para plotar
    if df_exec.empty:
        print(f"Não há dados suficientes para o '{executable}'. Verifique o arquivo processado.")
    else:
        # Convertendo 'Alpha' para string para garantir que todos os valores sejam tratados corretamente
        df_exec['Alpha'] = df_exec['Alpha'].astype(str)

        # Aplicando a função para extrair número de itens e número da instância
        df_exec[['Numero Itens', 'Numero Instancia']] = pd.DataFrame(df_exec['Instance'].apply(extrair_numeros).tolist(), index=df_exec.index)

        # Ordenando primeiro pelo número de itens e dentro de cada número de itens pelo número da instância
        df_exec = df_exec.sort_values(['Numero Itens', 'Numero Instancia'])

        # Plotando os dados
        plt.figure(figsize=(12, 8))

        for alpha in df_exec['Alpha'].unique():
            subset = df_exec[df_exec['Alpha'] == alpha]
            plt.plot(subset['Instance'], subset['Average Profit'], marker='o', label=f'Alpha {alpha}')

        plt.xlabel("Instance")
        plt.ylabel("Average Profit")
        plt.title(f"Comparação dos Valores de Alpha para o Executable '{executable}'")
        plt.legend()
        plt.xticks(rotation=45)
        plt.grid(True)
        plt.tight_layout()

        # Salvando o gráfico em um arquivo de imagem
        plt.savefig(output_image_path)

        # Exibindo o gráfico
        plt.show()

        print(f"Gráfico salvo em: {output_image_path}")

# Plotando comparações para 'grasp'
plot_comparison(df, "grasp", "comparacao_grasp_alphas.png")

# Plotando comparações para 'ils'
plot_comparison(df, "ils", "comparacao_ils_alphas.png")
