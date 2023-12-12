#!/bin/bash

# Diretórios de entrada e saída
input_directory="./test_in"
output_directory="./test_out"
binary="./bin/projeto"  # Substitua pelo caminho do seu binário

make clean
make all

# Define códigos de escape ANSI para cores e formatações
vermelho="\033[1;31m"
verde="\033[1;32m"
amarelo="\033[1;33m"
reset="\033[0m"

# Verificar se o binário existe
if [ ! -x "$binary" ]; then
    echo "Erro: O binário não foi encontrado ou não é executável."
    exit 1
fi

# Verificar se os diretórios de entrada e saída existem
if [ ! -d "$input_directory" ] || [ ! -d "$output_directory" ]; then
    echo "Erro: Os diretórios de entrada ou saída não existem."
    exit 1
fi

# Iterar sobre os arquivos de entrada
for input_file in $(ls "$input_directory"/*.in | sort -V); do
    # Extrair o número do caso de teste do nome do arquivo
    test_number=$(basename "$input_file" .in)

    # Construir os caminhos para o arquivo de saída esperado e para a saída gerada
    expected_output_file="$output_directory/$test_number.out"
    generated_output_file="/tmp/$test_number.out"  # Arquivo temporário

    # Executar o binário com a entrada e salvar a saída gerada
    "$binary" < "$input_file" > "$generated_output_file"

    # Comparar a saída gerada com a saída esperada
    diff_result=$(diff -u "$expected_output_file" "$generated_output_file")

    if [ $? -eq 0 ]; then
        echo -e "Teste $test_number: ${verde}PASSOU${reset}"
    else
        echo -e "Teste $test_number: ${vermelho}FALHOU${reset}"
        # echo "Diferenças:"
        echo "$diff_result"
    fi

    # Remover o arquivo temporário
    rm -f "$generated_output_file"
done

# echo "Conclusão dos testes."
