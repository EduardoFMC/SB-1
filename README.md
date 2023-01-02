# Projeto 1 (SB - 2022.2): Montador
Projeto 1 de Software Básico, disciplina ofertada na Universidade de Brasília (UnB) no semestre 2022.2. Desenvolvido por <a href="https://github.com/EduardoFMC">Eduardo Ferreira Marques Cavalcante</a> e <a href="https://github.com/ciriatico">Gabriel Mendes Ciriatico Guimarães</a>.

## Descrição ##
O trabalho implementa um montador em C++ da linguagem Assembly hipotética vista em aula. O processo de tradução é feito em 4 etapas: duas passagens de pré-processamento (uma para comandos IF e EQU e outra para MACROs); e duas passagens de montagem (seguindo o algoritmo de duas passagens).

## Especificações ##
O sistema operacional utilizado no desenvolvimento do projeto foi Ubuntu 22.04.1 LTS. Para compilar o arquivo, é necessário executar o comando:

<code>g++ -std=c++17 -o montador main.cpp</code>

## Execução ##
Para executar o montador compilado, é necessário utilizar flags que especificam em qual parte do processo se está.

### Pré-processamento ###
Aceita qualquer tipo de arquivo sem nenhum tipo de pré-processamento, escrito no Assembly hipotético.

<code>./montador -p ../tests/bin.asm</code>

Necessita da flag -p antes do caminho do arquivo, resultando em arquivo com pré-processamento de comandos IF e EQU e com extensão .PRE.

### Processamento de MACROs ###
Aceita arquivos com extensão .PRE, que já tenham passado pelo pré-processamento da etapa anterior.

<code>./montador -m ../tests/bin.PRE</code>

Necessita da flag -m antes do caminho do arquivo, resultando em arquivo com MACROs processadas e com extensão .MCR.

### Geração de código-objeto ###
Aceita arquivos com extensão .MCR, que já tenham passado pelos pré-processamentos das etapas anteriores.

<code>./montador -o ../tests/bin.MCR</code>

Necessita da flag -o antes do caminho do arquivo, resultando em arquivo-objeto composto de uma única linha, com extensão .OBJ.
