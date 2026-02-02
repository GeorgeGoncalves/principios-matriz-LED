# 🟩 Matriz de LEDs com Scroll e Animações

• SPI • MAX7219 • Bitwise • Frame Buffer

## 📌 Descrição do Projeto

Este projeto tem como objetivo estudar, **na prática**, a comunicação entre um microcontrolador e hardware externo utilizando **registradores de deslocamento e matriz de LEDs 8x8.**

A ideia inicial era simples: acender LEDs.
Com o tempo, o projeto evoluiu para incluir **scroll de texto, animações, manipulação direta de bits** e a criação de uma **fonte própria (alfabeto e números).**

O foco principal **não é apenas o resultado visual,** mas o **processo de aprendizado,** entendendo como dados são manipulados em baixo nível e como o software cria abstrações que o hardware não “enxerga”.

---

## 🎯 Objetivos de Aprendizado

- Entender bits, bytes e operações bitwise

- Compreender como funciona um registrador de deslocamento

- Implementar comunicação SPI sem bibliotecas prontas de alto nível

- Criar um frame buffer para controle da matriz

- Desenvolver scroll de texto baseado em deslocamento de bits

- Criar animações simples sem múltiplos frames prontos

- Entender a diferença entre fonte (dados imutáveis) e buffer (estado atual)

---

## 🧠 Conceitos Abordados
### 🔌 Hardware

- Matriz de LEDs 8x8

- Registrador de deslocamento

- Driver de matriz MAX7219

- Sinais SPI (CS, Clock, Data)

### 💻 Software

- Comunicação SPI (SPI.transfer)

- Uso de const para dados imutáveis

- Manipulação de bits (<<, |, &)

- Frame Buffer (fb[])

- Scroll baseado em injeção de colunas

### 🧩 Conceitos Importantes

- Scroll ≠ mover desenho

- Scroll = deslocar bits + injetar nova coluna

- O hardware não “vê” colunas, apenas linhas

- A animação acontece totalmente no software

- Separação clara entre fonte e estado

---

## 🗂 Estrutura Lógica do Código
```
├── Fonte de dados (letras, números, desenhos)
│   └── const byte font[][8]
│
├── Frame Buffer
│   └── byte fb[8]
│
├── Funções principais
│   ├── drawFB()        -> envia o buffer para a matriz
│   ├── clearFB()       -> limpa o frame buffer
│   ├── scrollLeft()    -> desloca o buffer
│   └── scrollInColumn()-> injeta uma coluna no scroll
│
└── Loop principal
    └── controla tempo, animação e scroll
```

---

## 🖼 Como o Scroll Funciona (Resumo)

1. Todo o frame buffer é deslocado para a esquerda

2. Um novo bit é injetado na extremidade direita

3. Esse bit vem de uma fonte (letra, número ou desenho)

4. O processo se repete rapidamente, criando a animação

O scroll é uma **ilusão criada pelo software.**
O hardware apenas recebe novos valores de linhas.

---

## 🔤 Fonte de Caracteres

O projeto inclui uma fonte simples com:

- Letras de **A a Z**

- Números de **0 a 9**

Cada caractere é representado por um array de 8 bytes, onde cada bit representa um LED.

Exemplo:

```
const byte letraA[8] = {
  0b00111100,
  0b01000010,
  0b01000010,
  0b01111110,
  0b01000010,
  0b01000010,
  0b01000010,
  0b00000000
};
```

---

## 🎞 Animações

Além do texto em scroll, o projeto explora:

- Animações simples

- Desenhos em movimento

- “Boneco andando” usando apenas manipulação de bits

- Animação sem múltiplos frames prontos (procedural)

---

## 🚀 Possíveis Evoluções

- Criar um protocolo via Serial para controle do display

- Ajustar velocidade do scroll dinamicamente

- Suporte a múltiplas matrizes em cascata

- Criar uma biblioteca reutilizável

- Remover delays e usar temporização não bloqueante

---

## 📚 O Que Esse Projeto Ensina de Verdade

Mais do que LEDs, este projeto ensina:

- Como o software cria abstrações

- Como dados fluem do código para o hardware

- Como conceitos de baixo nível se conectam com ideias maiores

- Como engines gráficas simples funcionam internamente

---

## 👨‍💻 Desenvolvedor

- **George Gonçalves Miranda** — [georgeggmiranda@gmail.com](mailto:georgeggmiranda@gmail.com)  

---

## 📄 Licença

Projeto desenvolvido como estudo pessoal em sistemas embarcados, eletrônica e programação de baixo nível.

Este projeto não possui licença comercial. Uso livre para fins educacionais.
