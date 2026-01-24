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
// Mostrando a letra "A" na matriz
// ================================
const byte letraA[8] = {
  0x3c,
  0x42,
  0x42,
  0x42,
  0x7e,
  0x42,
  0x42,
  0b00
};

byte colunaA = 0; 

// ================================
// Desenhar a letra "A" linha por linha
// ================================
void drawA() {
  for (byte i = 0; i < 8; i++) {
    sendMAX(i + 1, letraA[i]);
  }
}

// ================================
// Mostrar "smile" na matriz
// ================================
const byte smile[8] = {
  0b00111100,
  0b01000010,
  0b10100101,
  0b10000001,
  0b10100101,
  0b10011001,
  0b01000010,
  0b00111100
};

byte colunaSmile = 0;

void drawSmile() {
  for (byte i = 0; i < 8; i++) {
    sendMAX(i + 1, smile[i]);
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
  pinMode (CS_MAX, OUTPUT);
  digitalWrite(CS_MAX, HIGH);

  SPI.begin();
  SPI.beginTransaction(SPISettings(100000, MSBFIRST,SPI_MODE0));

  // Inicialização do MAX7219
  sendMAX(0x0C, 0x01); // sai do shutdown
  sendMAX(0x09, 0x00); // decode OFF (modo matriz)
  sendMAX(0x0B, 0x07); // 8 linhas
  sendMAX(0x0A, 0x08); // brilho médio
  sendMAX(0x0F, 0x00); // display test OFF

  clearMatriz();
}

// ================================
// LOOP
// ================================
void loop() {
  drawSmile();
}