import numpy as np
import os
import shutil

# Edite esses valores para determinar as propriedados dos teste
# é necessário executar o script novamente pra que as mudaças sejam efetivadas

quantidade_testes = 10
tamanho_max_sets = 100000
valor_max_item = 10000


def criar_diretorio_se_nao_existir(caminho):
    if not os.path.exists(caminho):
        os.makedirs(caminho)
        print(f"Diretório '{caminho}' criado com sucesso.")
    else:
        print(f"Diretório '{caminho}' já existe.")

def apagar_itens_pasta(caminho_pasta):
    try:
        shutil.rmtree(caminho_pasta)
        os.makedirs(caminho_pasta) 
    except Exception as e:
        print(f"Falha ao apagar itens da pasta {caminho_pasta}. Erro: {e}")

def criar_arquivo_com_string(nome_arquivo, conteudo_string):
    try:
        with open(nome_arquivo, 'w') as arquivo:
            arquivo.write(conteudo_string)
        print(f"Arquivo '{nome_arquivo}' criado com sucesso.")
    except Exception as e:
        print(f"Falha ao criar o arquivo. Erro: {e}")

def set_pertence(A, num):
    return num in A

def set_uniao(A, B):
    return np.union1d(A, B)

def set_interseccao(A, B):
    return np.intersect1d(A, B)

def set_remover(A, num):
    A = np.setdiff1d(A, [num])
    return A

def set_imprimir(A):
    print(A)

# Garante a existência dos diretórios de teste
criar_diretorio_se_nao_existir('test_in')
criar_diretorio_se_nao_existir('test_out')

# Limpa os casos testes criados anteriormente
apagar_itens_pasta('test_in')
apagar_itens_pasta('test_out')

entradas = []

for i in range(quantidade_testes):
    tamanho_set_1 = np.random.randint(0, tamanho_max_sets)
    tamanho_set_2 = np.random.randint(0, tamanho_set_1 + 1)

    set_1 = np.random.randint(0, valor_max_item, size=(tamanho_set_1))

    porcao_tamanho = np.random.randint(0, tamanho_set_2 + 1)
    porcao_aleatoria = np.random.choice(set_1, porcao_tamanho, replace=False)
    numeros_aleatorios_extra = np.random.randint(0, tamanho_max_sets, size= tamanho_set_2 - porcao_tamanho)  
    
    # print(porcao_tamanho)
    # print(np.size(porcao_aleatoria))
    # print(np.size(numeros_aleatorios_extra))
    # print(tamanho_set_1)
    set_2 = np.concatenate([porcao_aleatoria, numeros_aleatorios_extra])
    

    # print(len(set_2))
    operacao = np.random.randint(1, 5)

    extra = ''

    if operacao == 1 or operacao == 4:
        if np.size(set_2 != 0):
            extra = np.random.choice(set_2)
        else:
            extra = np.random.randint(0, valor_max_item)

    comando_final = str(tamanho_set_1) + ' ' + str(tamanho_set_2) + ' ' \
    + ' '.join(map(str, set_1)) + ' ' + ' '.join(map(str, set_2)) + ' ' \
    +  str(operacao) + ' ' + str(extra)

    saida = ''

    if operacao == 1:
        if set_pertence(set_1, extra):
            saida = 'Pertence.'
        else:
            saida = 'Não Pertence.'

    elif operacao == 2:
        C = set_uniao(set_1, set_2)
        saida = ' '.join(map(str, C))

    elif operacao == 3:
        C = set_interseccao(set_1, set_2)
        saida = ' '.join(map(str, C))

    elif operacao == 4:
        A = set_remover(set_1, extra)
        saida = ' '.join(map(str, A))
    
    if saida == '':
        saida = '\n'
    else:
        saida += ' \n'

    criar_arquivo_com_string(f'test_in/{i}.in', comando_final)
    criar_arquivo_com_string(f'test_out/{i}.out',saida)

quit()