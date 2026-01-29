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
  0b0001000,
  0b0011000,
  0b0001000,
  0b0001000,
  0b0001000,
  0b0001000,
  0b0011100,
  0b0000000
};


// ================================
// Mostrar o número "2" na matriz
// ================================
const byte numero2[8] = {
  B00111000,
  B01000100,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01111100,
  B00000000
};


// ================================
// Mostrar o número "3" na matriz
// ================================
const byte numero3[8] = {
  0b01111100,
  0b00001000,
  0b00010000,
  0b00001000,
  0b00000100,
  0b01000100,
  0b00111000,
  0b00000000
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
  0x7E, //01111110
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
  0x93,
  0x6D,
  0x7D,
  0xBB,
  0xD7,
  0xEF,
  0xFF
};

const byte coracao1[8] = {
  0b00000000,
  0b01100110,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00011000,
  0b00000000
};

const byte coracao2[8] = {
  0b00000000,
  0b01100110,
  0b11111111,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00000000
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
// LOOP
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
}

// ================================
// LOOP
// ================================
 void loop() {
//   for (byte i = 0; i < 6; i++) {
//     scrollInLetter(texto[i]);
//   }
//   delay(1000);

  loadLetter(coracao1);
  drawFB();
  sendMAX(0x0A, 0x07);
  delay(500);
  
  loadLetter(coracao2);
  drawFB();
  sendMAX(0x0A, 0x0F);
  delay(500);
  
}