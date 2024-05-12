#include "aes.h"

AES::AES(KeyLength key_length, uint8_t* key) : key_length_{key_length} {
  switch (key_length_) {
    case AES_128:
      rounds_ = 10;
      break;
    case AES_192:
      rounds_ = 12;
      break;
    case AES_256:
      rounds_ = 14;
      break;
  }

  if (key != nullptr) {
    set_key(key, key_length);
    std::cout << "La cambia llave\n";
  } else {
    expanded_key_.resize((rounds_ + 1) * 16);
    memcpy(expanded_key_.data(), key_.data(), key_length_);
    ExpandKey();
  }
}

size_t AES::EncryptedLength(int length) {
  return (length / 16) * 16 + (length % 16 > 0) * 16;
}

void AES::Encrypt(const uint8_t* texto_original, int length, uint8_t* salida) {
  int pos = 0;
  // llamar bloque encriptado 16 veces
  while (pos + 16 <= length) {
    EncryptBlock(texto_original + pos, salida + pos);
    pos += 16;
  }

  if (pos < length) {
    int size = (length - pos);
    // copia el texto original al estado
    memcpy(salida + pos, texto_original + pos, size);
    salida[pos + size] = 0;
    EncryptBlock(salida + pos, salida + pos);
  }
}


void AES::set_key(uint8_t* key, KeyLength key_length) {
  key_length_ = key_length;
  if (key_length != key_.size()) {
    key_.resize(key_length);
    expanded_key_.resize((rounds_ + 1) * 16);
    std::cout << "La cambia llave2\n";
    for (size_t i = 0; i < expanded_key_.size(); i++) {
      expanded_key_[i] = key[i];
    }
  };
  memcpy(key_.data(), key, key_length);
  ExpandKey();
}

inline void AES::AddRoundKey(int iteration) {
  std::cout << "AddRoundKey:\n";
  Xor(state_.data(), state_.data(), expanded_key_.data() + iteration * 16, 16);
  for(int k = 0; k < 16; k++){
    std::cout << std::hex << (int)state_[k];
  }
  std::cout << "\n";
}

void AES::EncryptBlock(const uint8_t input[16], uint8_t salida[16]) {
  // copia de memoria el input al estado
  memcpy(state_.data(), input, 16);
  // Ronda inicio
  AddRoundKey(0);
  std::cout << "R" << 0 << "(subclave = ";
    for(int k = 0; k < 16; k++){
      std::cout << std::hex << (int)expanded_key_[0*16 + k];
    }
    std::cout << ") = ";
    for(int k = 0; k < 16; k++){
      std::cout << std::hex << (int)state_[k];
    }
    std::cout << "\n";

    // 9 rondas
  for (int i = 1; i < rounds_; i++) {
    for (int j = 0; j < 16; j++) {
      state_[j] = GetSubByte(state_[j]);
    }
    std::cout << "SubBytes:\n";
    for(int k = 0; k < 16; k++){
      std::cout << std::hex << (int)state_[k];
    } 
    std::cout << "\n";
    ShiftRows();
    MixColumns();
    AddRoundKey(i);
    std::cout << "R" << i << "(subclave = ";
    for(int k = 0; k < 16; k++){
      std::cout << std::hex << (int)expanded_key_[i*16 + k];
    }
    std::cout << ") = ";
    for(int k = 0; k < 16; k++){
      std::cout << std::hex << (int)state_[k];
    }
    std::cout << "\n";
  }

  for (int j = 0; j < 16; j++) {
    state_[j] = GetSubByte(state_[j]);
  }

  ShiftRows();
  AddRoundKey(rounds_);
  std::cout << "R10 (subclave = ";
  for(int k = 0; k < 16; k++){
    std::cout << std::hex << (int)expanded_key_[9*16 + k];
  }
  std::cout << ") = ";
  for(int k = 0; k < 16; k++){
    std::cout << std::hex << (int)state_[k];
  }
  std::cout << "\n";
  memcpy(salida, state_.data(), 16);
}


void AES::ExpandKey() {
  for (int i = key_length_; i < (rounds_ + 1) * 16; i += key_length_) {
    uint8_t* position = expanded_key_.data() + i;
    // Se copia la última columna.
    memcpy(position, position - 4, 4);

    // Realmente actua sobre una columna, pero el funcionamiento es el mismo.
    ShiftRow(position, 1);

    for (int i = 0; i < 4; i++) {
      position[i] = GetSubByte(position[i]);
    }

    Xor(position, position, position - key_length_);
    Xor(position, position, rcon_.data());

    rcon_[0] = dbl(rcon_[0]);

    for (int j = 4; j < key_length_ && i + j < (rounds_ + 1) * 16; j += 4) {
      memcpy(position + j, position + j - 4, 4);
      for (int k = 0; k < 4 && j == 16 && key_length_ == AES_256; k++) {
        position[j + k] = GetSubByte(position[j + k]);
      }
      Xor(position + j, position + j, position + j - key_length_);
    }
  }
}


inline void AES::MixColumns() {
  std::cout << "MixColumns:\n";
  MixColumn(state_.data());
   for(int k = 0; k < 16; k++){
    std::cout << std::hex << (int)state_[k];
  }
  std::cout << "\n";
  MixColumn(state_.data() + 4);
  for(int k = 0; k < 16; k++){
    std::cout << std::hex << (int)state_[k];
  }
  std::cout << "\n";
  MixColumn(state_.data() + 8);
  for(int k = 0; k < 16; k++){
    std::cout << std::hex << (int)state_[k];
  }
  std::cout << "\n";
  MixColumn(state_.data() + 12);
  for(int k = 0; k < 16; k++){
    std::cout << std::hex << (int)state_[k];
  }
  std::cout << "\n";
}


void AES::ShiftRows() {
  std::cout << "ShiftRows:\n";
  std::array<uint8_t, 16> temp;
  RotateMatrix(state_.data(), temp.data());
  std::cout << "\t1. RotateMatrix:\n";
  for(int k = 0; k < 16; k++){
    std::cout << std::hex << (int)temp[k];
  }
  std::cout << "\n\t2. ShiftRow:\n";
  ShiftRow(temp.data() + 4, 1);
    for(int k = 0; k < 16; k++){
    std::cout << std::hex << (int)temp[k];
  }
  std::cout << "\n\t3. ShiftRow:\n";
  ShiftRow(temp.data() + 8, 2);
  for(int k = 0; k < 16; k++){
    std::cout << std::hex << (int)temp[k];
  }
  std::cout << "\n\t4. ShiftRow:\n";
  ShiftRow(temp.data() + 12, 3);
  for(int k = 0; k < 16; k++){
    std::cout << std::hex << (int)temp[k];
  }
  RotateMatrix(temp.data(), state_.data());
  std::cout << "\n\t5. RotateMatrix:\n";
  for(int k = 0; k < 16; k++){
    std::cout << std::hex << (int)state_[k];
  }
}

void AES::Xor(uint8_t* a, const uint8_t* b, const uint8_t* c, int size) const {
  for (int i = 0; i < size; i++) {
    a[i] = b[i] ^ c[i];
  }
}

/**
 * @brief  se utiliza para realizar la sustitución de bytes (S-Box) en el proceso de cifrado AES.
*/
inline uint8_t AES::GetSubByte(uint8_t index) const { return s_box_[index]; }



void AES::ShiftRow(uint8_t* row, int offset) const {
  std::array<uint8_t, 4> temp;
  memcpy(temp.data(), row, 4);

  for (int i = 0; i < 4; i++) {
    row[i] = temp[(i + offset) % 4];
  }
}

void AES::MixColumn(uint8_t* column) const {
  auto c_0 = column[0], c_1 = column[1], c_2 = column[2], c_3 = column[3];

  column[0] = dbl(c_0 ^ c_1) ^ c_1 ^ c_2 ^ c_3;
  column[1] = dbl(c_1 ^ c_2) ^ c_2 ^ c_3 ^ c_0;
  column[2] = dbl(c_2 ^ c_3) ^ c_3 ^ c_0 ^ c_1;
  column[3] = dbl(c_3 ^ c_0) ^ c_0 ^ c_1 ^ c_2;
}



inline uint8_t AES::dbl(uint8_t a) const {
  return (a << 1) ^ (0x11b & -(a >> 7));
}

void AES::RotateMatrix(const uint8_t* input, uint8_t* salida) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      salida[(i * 4) + j] = input[(j * 4) + i];
    }
  };
}