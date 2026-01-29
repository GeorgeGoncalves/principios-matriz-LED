#include <SPI.h>

#define CS_MAX D8  // Chip select do MAX7219

// ================================
// Envia um comando para o MAX7219
// reg  = registrador (1 a 8 = linhas)
// data = bits da linha
// ================================
void sendMAX(byte reg, byte data) {
  digitalWrite(CS_MAX, LOW);
  SPI.transfer(reg);
  SPI.transfer(data);
  digitalWrite(CS_MAX, HIGH);
}

// ================================
// Variavel que controla a direção da animação
// ================================
int direcao = 1;


// ================================
// Mostrar "quadrado 2x2" na matriz
// ================================
byte quadrado[8] = {
  0x00,
  0x00,
  0x18,
  0x18,
  0x00,
  0x00,
  0x00,
  0x00
};


// ================================
// Mostrar " "(espaço) na matriz
// ================================
const byte espaco[8] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};


// ================================
// Mostrar o número "1" na matriz
// ================================
const byte numero1[8] = {
  0x08,
  0x18,
  0x08,
  0x08,
  0x08,
  0x08,
  0x1C,
  0x00
};


// ================================
// Mostrar o número "2" na matriz
// ================================
const byte numero2[8] = {
  0x38,
  0x44,
  0x04,
  0x08,
  0x10,
  0x20,
  0x7C,
  0x00
};


// ================================
// Mostrar o número "3" na matriz
// ================================
const byte numero3[8] = {
  0x7C,
  0x08,
  0x10,
  0x08,
  0x04,
  0x44,
  0x38,
  0x00
};


// ================================
// Mostrar a letra "A" na matriz
// ================================
const byte letraA[8] = {
  0x3C,
  0x42,
  0x42,
  0x42,
  0x7E,
  0x42,
  0x42,
  0b00
};


// ================================
// Mostrar a letra "B" na matriz
// ================================
const byte letraB[8] = {
  0x7C,
  0x42,
  0x42,
  0x7C,
  0x42,
  0x42,
  0x7C,
  0x00
};


// ================================
// Mostrar a letra "C" na matriz
// ================================
const byte letraC[8] = {
  0x7E,
  0x80,
  0x80,
  0x80,
  0x80,
  0x80,
  0x7E,  //01111110
  0x00
};


// ================================
// Mostrar "smile" na matriz
// ================================
const byte smile[8] = {
  0x3C,
  0x42,
  0xA5,
  0x81,
  0xA5,
  0x99,
  0x42,
  0x3C
};


// ================================
// Mostrar "coração" na matriz
// ================================
const byte coracao[8] = {
  0xFF,
  0x99,
  0x00,
  0x00,
  0x81,
  0xC3,
  0xE7,
  0xFF
};

const byte coracao1[8] = {
  0x00,
  0x66,
  0xFF,
  0xFF,
  0x7E,
  0x3C,
  0x18,
  0x00
};


// ================================
// Vetor de letras que irão aparecer
// ================================
const byte* texto[] = {
  letraA,
  letraB,
  letraC,
  numero1,
  numero2,
  numero3
};


// ================================
// Buffer
// ================================
byte fb[8];

// ================================
// Envia o buffer para o MAX
// ================================
void drawFB() {
  for (byte i = 0; i < 8; i++) {
    sendMAX(i + 1, fb[i]);
  }
}

// ================================
// Carrega uma letra
// ================================
void loadLetter(const byte letter[8]) {
  for (byte i = 0; i < 8; i++) {
    fb[i] = letter[i];
  }
}

// ================================
// Limpa o buffer
// ================================
void clearFB() {
  for (byte i = 0; i < 8; i++) {
    fb[i] = 0;
  }
}

// ================================
// Faz a scroll para esquerda simples
// ================================
void scroll() {
  for (byte row = 0; row < 8; row++) {
    fb[row] <<= 1;
  }
}

// ================================
// Vai e volta do objeto na tela
// ================================
void roundTrip() {
  for (byte row = 0; row < 8; row++) {
    if (direcao == 1)
      fb[row] <<= 1;
    else
      fb[row] >>= 1;
  }
}

// ================================
// Verifica se o objeto tocou a borda
// ================================
void checkEdge() {
  for (byte row = 0; row < 8; row++) {
    if (fb[row] & 0b10000000) {
      direcao = -1;  // bateu à direita
    }
    if (fb[row] & 0b00000001) {
      direcao = 1;  // bateu à esquerda
    }
  }
}

// ================================
// Faz a letra entrar pela direita
// ================================
void scrollInLetter(const byte letter[8]) {
  for (int col = 7; col >= 0; col--) {
    for (byte row = 0; row < 8; row++) {
      fb[row] <<= 1;  // anda tudo para esquerda

      if (letter[row] & (1 << col)) {
        fb[row] |= 1;  // entra bit novo pela direita
      }
    }
    drawFB();
    delay(150);
  }
}

// ================================
// Limpa a matriz
// ================================
void clearMatriz() {
  for (byte i = 1; i <= 8; i++) {
    sendMAX(i, 0x00);
  }
}

// ================================
// SETUP
// ================================
void setup() {
  pinMode(CS_MAX, OUTPUT);
  digitalWrite(CS_MAX, HIGH);

  SPI.begin();
  SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE0));

  // Inicialização do MAX7219
  sendMAX(0x0C, 0x01);  // sai do shutdown
  sendMAX(0x09, 0x00);  // decode OFF (modo matriz)
  sendMAX(0x0B, 0x07);  // 8 linhas
  sendMAX(0x0A, 0x08);  // brilho médio
  sendMAX(0x0F, 0x00);  // display test OFF

  clearMatriz();
  loadLetter(quadrado);
}

// ================================
// LOOP
// ================================
void loop() {
  // for (byte i = 0; i < 6; i++) {
  //   scrollInLetter(texto[i]);
  // }
  // delay(1000);

  // for (int repeticao = 0; repeticao < 5; repeticao++) {
  //   loadLetter(coracao);
  //   drawFB();
  //   sendMAX(0x0A, 0x03);
  //   delay(500);

  //   loadLetter(coracao1);
  //   drawFB();
  //   sendMAX(0x0A, 0x0F);
  //   delay(500);
  // }

  drawFB();
  delay(200);
  checkEdge();  
  roundTrip();
}