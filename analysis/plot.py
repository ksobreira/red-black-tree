import csv
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

# Lê o CSV
tamanhos, insercao, busca, remocao = [], [], [], []

with open('../output/results.csv', newline='') as f:
    reader = csv.DictReader(f)
    for row in reader:
        tamanhos.append(int(row['tamanho']))
        insercao.append(float(row['insercao']))
        busca.append(float(row['busca']))
        remocao.append(float(row['remocao']))

# Tabela 
fig, ax = plt.subplots(figsize=(14, 10))
ax.axis('off')

headers = ['Tamanho (n)', 'Inserção (s)', 'Busca (s)', 'Remoção (s)']
rows = [
    [f'{t:,}', f'{i:.9f}', f'{b:.9f}', f'{r:.9f}']
    for t, i, b, r in zip(tamanhos, insercao, busca, remocao)
]

table = ax.table(cellText=rows, colLabels=headers, loc='center', cellLoc='center')
table.auto_set_font_size(False)
table.set_fontsize(8)
table.scale(1, 1.5)

for j in range(len(headers)):
    table[0, j].set_facecolor('#8B0000')
    table[0, j].set_text_props(color='white', fontweight='bold')

for i in range(1, len(rows) + 1):
    cor = '#f5f5f5' if i % 2 == 0 else 'white'
    for j in range(len(headers)):
        table[i, j].set_facecolor(cor)

ax.set_title(
    'Tabela: Tempo de Execução Red-Black Tree\n'
    'Média de 35 execuções com entradas aleatórias entre 1 e 100.000',
    fontsize=12, fontweight='bold', pad=20
)

plt.savefig('../output/tabela.png', bbox_inches='tight', dpi=150)
plt.close()
print("tabela.png gerado")

# Gráfico 
fig, ax = plt.subplots(figsize=(14, 8))

ax.plot(tamanhos, insercao, 'o-', color='#C0392B', linewidth=2, markersize=4, label='Inserção')
ax.plot(tamanhos, busca,    's-', color='#2980B9', linewidth=2, markersize=4, label='Busca')
ax.plot(tamanhos, remocao,  '^-', color='#27AE60', linewidth=2, markersize=4, label='Remoção')

ax.set_xlabel('Tamanho da Entrada (n)', fontsize=12)
ax.set_ylabel('Tempo Médio (segundos)', fontsize=12)
ax.set_title(
    'Análise Empírica de Complexidade da Red-Black Tree\n'
    'Escala Linear | Média de 35 execuções',
    fontsize=13, fontweight='bold'
)
ax.legend(fontsize=11)
ax.grid(True, linestyle='--', alpha=0.5)
ax.xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: f'{int(x):,}'))
plt.xticks(rotation=45, ha='right')
plt.tight_layout()

plt.savefig('../output/grafico.png', bbox_inches='tight', dpi=150)
plt.close()
print("grafico.png gerado")