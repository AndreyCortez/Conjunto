# Projeto Conjunto em C

Este é um projeto em C que implementa uma estrutura de dados de conjunto com uma AVL.

Uma estrutura de dados conjunto é uma coleção não ordenada de elementos distintos, onde a principal propriedade é que cada elemento é único no conjunto. Os conjuntos são fundamentais em ciência da computação e matemática, sendo frequentemente utilizados para representar relações de pertinência entre objetos.

Uma Árvore AVL (Adelson-Velsky e Landis) é uma árvore de busca binária balanceada, na qual a diferença entre as alturas das subárvores esquerda e direita de qualquer nó (chamada de fator de balanceamento) é mantida dentro do intervalo {-1, 0, 1}. Isso garante que a árvore permaneça relativamente balanceada, o que resulta em operações de busca, inserção e remoção eficientes com complexidade de tempo logarítmica.

A escolha de implementar um conjunto usando uma árvore AVL oferece várias vantagens:

Busca Eficiente: A árvore AVL mantém uma estrutura de busca binária balanceada, o que garante que as operações de busca em um conjunto (verificar a existência de um elemento) sejam realizadas em tempo logarítmico, proporcionando eficiência na recuperação de elementos.

Inserção e Remoção Eficientes: As operações de inserção e remoção em uma árvore AVL também têm complexidade de tempo logarítmica, garantindo que a estrutura do conjunto seja mantida de maneira eficiente após essas operações.

Manutenção do Conjunto Ordenado: Embora a ordenação não seja um requisito fundamental para conjuntos, a estrutura de uma árvore AVL fornece naturalmente uma ordenação, o que pode ser útil em certos casos.

Adaptabilidade a Mudanças Dinâmicas: A árvore AVL é adaptável a mudanças dinâmicas na coleção. À medida que os elementos são inseridos ou removidos, a árvore é automaticamente reequilibrada para garantir uma estrutura balanceada.

## Como Usar

### Compilação do Projeto

Para compilar o projeto, basta executar o comando `make all` no terminal. Isso criará um executável chamado `conjunto` no diretório atual.

```bash
make all
```

### Execução

Para executar os arquivos, basta executar o comando `make run` no terminal.

```bash
make run
```

### Limpeza

Para remover os arquivos de objeto e o executável gerados durante a compilação, use o comando `make clean`.

```bash
make clean
```

### Criação do Arquivo ZIP

Para criar um arquivo `.zip` contendo todos os arquivos relevantes do projeto, execute o seguinte comando:

```bash
make zip
```

O arquivo ZIP será gerado com o nome `conjunto.zip` e conterá os diretórios `src`, `inc` e o arquivo `Makefile`.

## Dependências

Certifique-se de ter o utilitário `zip` instalado no seu sistema para usar a funcionalidade de criação do arquivo ZIP.

```bash
sudo apt-get install zip   # Para sistemas baseados em Debian/Ubuntu
# ou
sudo yum install zip       # Para sistemas baseados em Red Hat/Fedora
```

Isso completa a documentação básica para compilar e usar este projeto em C.
