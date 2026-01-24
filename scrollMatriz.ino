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
  0x3C,
  0x42,
  0x42,
  0x42,
  0x7E,
  0x42,
  0x42,
  0b00
};

byte colunaA = 0; 

void drawA() {
  for (byte i = 0; i < 8; i++) {
    sendMAX(i + 1, letraA[i]);
  }
}


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

byte colunaSmile = 0;

void drawSmile() {
  for (byte i = 0; i < 8; i++) {
    sendMAX(i + 1, smile[i]);
  }
}


// ================================
// Mostrar "smile1" na matriz
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

byte colunaCoracao = 0;

void drawCoracao() {
  for (byte i = 0; i < 8; i++) {
    sendMAX(i + 1, coracao[i]);
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
  // Mostrando a letra "A" com um delay de 1000 milessegundos
  drawA();
  delay(1000);

  //Mostrando o "smile" com delay de 1000 milessegundos
  drawSmile();
  delay(1000);

  // Mostrando o "coração" com delay de 1000 milessegundos
  drawCoracao();
  delay(10000);

  // Acende todos os LEDs e faz parecido com uma respiração
  for (int i = 1; i < 8 ; i++) {
    sendMAX(i, 0xFF);
  }  

  for (int i = 0; i < 15; i++) {
    sendMAX(0X0A, i);
    delay(100);
  }
}