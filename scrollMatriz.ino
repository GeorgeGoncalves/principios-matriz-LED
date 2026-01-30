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
// Boneco corpo inteiro
// ================================
const byte boneco[8] = {
  0b00111000,
  0b00111000,
  0b00010000,
  0b00111000,
  0b01010000,
  0b00010000,
  0b00101000,
  0b01000100
};


const byte boneco1[8] = {
  0b00111000,
  0b00111000,
  0b00010000,
  0b00111000,
  0b00010100,
  0b00010000,
  0b01000100,
  0b00101000
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
// Minha biblioteca Alfabeto de A a Z e de 0 a 9
// ================================
const byte font[][8] = {
  //A index[0]
  {0x3C,0x42,0x42,0x42,0x7E,0x42,0x42,0x00},
  //B index[1]
  {0x7C,0x42,0x42,0x7C,0x42,0x42,0x7C,0x00},
  //C index[2]
  {0x7E,0x80,0x80,0x80,0x80,0x80,0x7E,0x00},
  // D index[3]
  {0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x00},
  // E index[4]
  {0x7E,0x40,0x40,0x7C,0x40,0x40,0x7E,0x00},
  // F index[5]
  {0x7E,0x40,0x40,0x7C,0x40,0x40,0x40,0x00},
  // G index[6]
  {0x3C,0x42,0x40,0x4E,0x42,0x42,0x3C,0x00},
  // H index[7]
  {0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x00},
  // I index[8]
  {0x3E,0x08,0x08,0x08,0x08,0x08,0x3E,0x00},
  // J index[9]
  {0x1E,0x04,0x04,0x04,0x44,0x44,0x38,0x00},
  // K index[10]
  {0x42,0x44,0x48,0x70,0x48,0x44,0x42,0x00},
  // L index[11]
  {0x40,0x40,0x40,0x40,0x40,0x40,0x7E,0x00},
  // Mindex[12]
  {0x42,0x66,0x5A,0x5A,0x42,0x42,0x42,0x00},
  // N index[13]
  {0x42,0x62,0x52,0x4A,0x46,0x42,0x42,0x00},
  // O index[14]
  {0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00},
  // P index[15]
  {0x7C,0x42,0x42,0x7C,0x40,0x40,0x40,0x00},
  // Q index[16]
  {0x3C,0x42,0x42,0x42,0x4A,0x44,0x3A,0x00},
  // R index[17]
  {0x7C,0x42,0x42,0x7C,0x48,0x44,0x42,0x00},
  // S index[18]
  {0x3C,0x42,0x40,0x3C,0x02,0x42,0x3C,0x00},
  // T index[19]
  {0x7F,0x08,0x08,0x08,0x08,0x08,0x08,0x00},
  // U index[20]
  {0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00},
  // V index[21]
  {0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00},
  // W index[22]
  {0x42,0x42,0x42,0x5A,0x5A,0x66,0x42,0x00},
  // X index[23]
  {0x42,0x24,0x18,0x18,0x18,0x24,0x42,0x00},
  // Y index[24]
  {0x42,0x24,0x18,0x08,0x08,0x08,0x08,0x00},
  // Z index[25]
  {0x7E,0x02,0x04,0x18,0x20,0x40,0x7E,0x00},
  
  
  // 0 index[26]
  {0x3C,0x42,0x46,0x4A,0x52,0x62,0x3C,0x00},
  // 1 index[27]
  {0x08,0x18,0x28,0x08,0x08,0x08,0x3E,0x00},
  // 2 index[28]
  {0x3C,0x42,0x02,0x0C,0x30,0x40,0x7E,0x00},
  // 3 index[29]
  {0x3C,0x42,0x02,0x1C,0x02,0x42,0x3C,0x00},
  // 4 index[30]
  {0x08,0x18,0x28,0x48,0x7E,0x08,0x08,0x00},
  // 5 index[31]
  {0x7E,0x40,0x40,0x7C,0x02,0x42,0x3C,0x00},
  // 6 index[32]
  {0x1C,0x20,0x40,0x7C,0x42,0x42,0x3C,0x00},
  // 7 index[33]
  {0x7E,0x02,0x04,0x08,0x10,0x10,0x10,0x00},
  // 8 index[34]
  {0x3C,0x42,0x42,0x3C,0x42,0x42,0x3C,0x00},
  // 9 index[35]
  {0x3C,0x42,0x42,0x3E,0x02,0x04,0x38,0x00}
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
  font[19],
  font[4],
  font[2],
  font[13],
  font[14],
  font[11],
  font[14],
  font[6],
  font[8],
  font[0]
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
}

// ================================
// LOOP
// ================================
void loop() {
  // Scroll da função texto
  for (byte i = 0; i < (sizeof(texto) / sizeof(texto[0])); i++) {
    scrollInLetter(texto[i]);
  }
  delay(1000);

  // Contagem dos números
  for (byte i = 0; i < 10; i++) {
    int num = 26 + i;
    loadLetter(font[num]);
    drawFB();
    delay(1000);
  }

  // Animação do coração
  for (int repeticao = 0; repeticao < 5; repeticao++) {
    loadLetter(coracao);
    drawFB();
    sendMAX(0x0A, 0x03);
    delay(500);

    loadLetter(coracao1);
    drawFB();
    sendMAX(0x0A, 0x0F);
    delay(500);
  }

  // Quadrado se movendo(vai e vem)
  loadLetter(quadrado);

  for (int i = 0; i < 20; i++) {
  drawFB();
  delay(200);
  checkEdge();
  roundTrip();
  }

  // Bonequinho andando
  for (int i = 0; i < 10; i++) {
    loadLetter(boneco);
    drawFB();
    delay(300);

    loadLetter(boneco1);
    drawFB();
    delay(300);
  }
}