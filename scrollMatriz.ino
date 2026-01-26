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
}

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
// Scroll para a esquerda
// ================================
void scrollLeft() {
  for (byte i = 0; i < 8; i++) {
    fb[i] <<= 1;
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
// Limpa a matriz
// ================================
void clearMatriz() {
  for (byte i = 1; i <= 8; i++) {
    sendMAX(i, 0x00);
  }
};

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
  // Mostra o smile na matriz
  loadLetter(smile);
  drawFB();
  scrollLeft();
  delay(1000);

  

  // Mostra o coração na matriz
  loadLetter(coracao);
  drawFB();
  scrollLeft();
  delay(2500);
}