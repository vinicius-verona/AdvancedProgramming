# **Programming Contests Challenges**

## ![United Kingdom](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/gb.png "United Kingdom") - English

## **About**

- This repository contains the development for challenges proposed as part of the course `Advanced Programming and Algorithms`.
- Each algorithm is developed in `C/C++` language, and it is submitted to [OnlineJudge](https://onlinejudge.org/).
- Each challenge can also be found in the [Programming Challenges](https://www.amazon.com.br/dp/B008AFF2ZU/ref=dp-kindle-redirect?_encoding=UTF8&btkr=1) book, by Steven S. Skiena and Miguel A. Revilla.

## **Directory and Files**

- For each challenge proposed, there will be a specific directory, e.g. [`FileFragmentation`](./FileFragmentation/).
- Within the directory there will be available an `input` directory, an `output` directory and a `src` directory.
  - As the name proposes, the `input` directory contains each input file used to test the challenge.
  - The `output` directory contains each output file generated in each test for that specific challenge.
  - The `src` directory contains the solution to the challenge in either `C/C++` language.
- The directory `scripts` contains a _`.sh`_ script in order to execute the challenge. It must be executed with at least one parameter, the name of the challenge (same as the challenge directory). The second parameter is optional, and it is the input file to be executed. Some challanges require `-lm` flag in order to be properly compiled. To use the falg, add it after the desired input.
- The directory `bin` is used to store the binary files generated when the challenge is compiled.

## **Execution Example**
```
$ ./execute.sh ArcheologistDilemma 0 -lm
```  

## **Project Tree**

```
root
├─ 📁 .git
├─ 📄 .gitignore
├─ 📁 bin
├─ 📁 ArcheologistDilemma
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
├─ 📁 ContestScoreboard
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
├─ 📁 FileFragmentation
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
├─ 📁 Football
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
├─ 📄 LICENSE
├─ 📁 Minesweeper
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
├─ 📁 Monocycle
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
├─ 📄 README.md
├─ 📁 scripts
├─ 📁 Steps
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
├─ 📁 TollHighway
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
└─ 📁 Yahtzee
   ├─ 📁 input
   ├─ 📁 output
   └─ 📁 src
```
---
## ![Brazil](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/br.png) - Português

## **Sobre**

- Este repositório contém solução para desafios propostos como parte do curso `Programação Avançada e Algoritmos`.
- Todas as soluções propostas foram desenvolvidas em linguagem `C/C++` e retiradas do website [OnlineJudge](https://onlinejudge.org/).
- Os desafios estão presentes também no livro [Programming Challenges](https://www.amazon.com.br/dp/B008AFF2ZU/ref=dp-kindle-redirect?_encoding=UTF8&btkr=1), por Steven S. Skiena e Miguel A. Revilla.

## **Diretórios e Arquivos**

- Para cada desafio proposto, há um diretório específico, por exemplo, [`FileFragmentation`](./FileFragmentation/).
- No interior do diretório, encontra-se outros três diretórios: `input`, `output` e `src`.
  - Como proposto pelo nome, o diretório `input` contém arquivos de entrada utilizados para realizar testes dos desafios.
  - O diretório `output` contém os arquivos resultantes dos testes mencionados acima.
  - O diretório `src` contém a implementação da solução em linguagem `C/C++`.
- O diretório `scripts` contém um _`script`_ em _`.sh`_ que recebem como parâmetro de entrada o nome do desafio e o número do arquivo de entrada a ser usado na execução. Para a execução do script, é necessário fornecer o nome do desafio (mesmo nome dos diretórios). Por padrão o arquivo de entrada será o exemplo padrão do desafio. Alguns desafios necessitam do parâmetro `-lm` para serem compilados, neste caso, basta adicionar o argumento após o input.
- O diretório `bin` contém os arquivos binários gerados na compilação do desafio.

## **Árvore de diretórios**

```
root
├─ 📁 .git
├─ 📄 .gitignore
├─ 📁 bin
├─ 📁 ArcheologistDilemma
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
├─ 📁 ContestScoreboard
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
├─ 📁 FileFragmentation
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
├─ 📁 Football
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
├─ 📄 LICENSE
├─ 📁 Minesweeper
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
├─ 📁 Monocycle
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
├─ 📄 README.md
├─ 📁 scripts
├─ 📁 Steps
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
├─ 📁 TollHighway
│  ├─ 📁 input
│  ├─ 📁 output
│  └─ 📁 src
└─ 📁 Yahtzee
   ├─ 📁 input
   ├─ 📁 output
   └─ 📁 src
```
