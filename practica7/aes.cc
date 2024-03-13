#include "aes.h"

AES::AES(KeyLength key_length, uint8_t* key, uint8_t* IV) : key_length_(key_length), prev_ciphertext_(16), IV_{0} {
  switch (key_length_) {
    case AES_128:
      rounds_ = 10;
      std::cout << "AES_128" << std::endl;
      break;
    case AES_192:
      rounds_ = 12;
      break;
    case AES_256:
      rounds_ = 14;
      break;
  }
  rounds_ = 10;
  if (key != nullptr) {
    set_key(key, key_length);
  } else {
    expanded_key_.resize((rounds_ + 1) * 16);
    memcpy(expanded_key_.data(), key_.data(), key_length_);
    ExpandKey();
  }

  if(IV != nullptr){
    memcpy(&IV_, IV, 16);
  }
  else{
    memset(&IV_, 0, 16);
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
    
    for (size_t i = 0; i < expanded_key_.size(); i++) {
      expanded_key_[i] = key[i];
    }
  };
  memcpy(key_.data(), key, key_length);
  ExpandKey();
}

inline void AES::AddRoundKey(int iteration) {
  Xor(state_.data(), state_.data(), expanded_key_.data() + iteration * 16, 16);
}

// Definición de la función privada UpdatePrevCiphertext
void AES::UpdatePrevCiphertext(const uint8_t* new_ciphertext) {
    memcpy(prev_ciphertext_.data(), new_ciphertext, key_length_);
}

void AES::EncryptCBC(const uint8_t* plaintext,const uint8_t* iv,uint8_t* ciphertext) {
  // if (prev_ciphertext_.size() == key_length_) {
  //  prev_ciphertext_.resize(key_length_);
   
  // }
  std::vector<uint8_t> plaintext_buffer(key_length_); // Nuevo búfer para el texto en claro
  memcpy(plaintext_buffer.data(), plaintext, key_length_); // Copia los datos de plaintext a plaintext_buffer

  memcpy(prev_ciphertext_.data(), iv, key_length_);
  // Combina el bloque de texto en claro con el bloque previamente cifrado
  for (size_t j = 0; j < key_length_; ++j) {
    plaintext_buffer[j] ^= prev_ciphertext_[j];
  }

  std::cout << "IV=";
  for(int k = 0; k < 16; k++){
    std::cout << std::hex << (int)prev_ciphertext_[k];
  }
  std::cout << "\n";
  std::cout << "lo que pasa=";
  for(int k = 0; k < 16; k++){
    std::cout << std::hex << (int)prev_ciphertext_[k];
  }
  std::cout << "\n";

  // Cifra el bloque modificado
  EncryptBlock(plaintext_buffer.data(), ciphertext);

  // Actualiza el bloque previamente cifrado
  UpdatePrevCiphertext(ciphertext);
    
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
    rounds_ =10;
    std::cout << "ROUNDS = " << rounds_ << "\n";
    // 9 rondas
  for (int i = 1; i < rounds_; i++) {
    for (int j = 0; j < 16; j++) {
      state_[j] = GetSubByte(state_[j]);
    }

    ShiftRows();
    MixColumns();
    AddRoundKey(i);
    // std::cout << "R" << i << "(subclave = ";
    // for(int k = 0; k < 16; k++){
    //   std::cout << std::hex << (int)expanded_key_[i*16 + k];
    // }
    // std::cout << ") = ";
    // for(int k = 0; k < 16; k++){
    //   std::cout << std::hex << (int)state_[k];
    // }
    // std::cout << "\n";
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
  MixColumn(state_.data());
  MixColumn(state_.data() + 4);
  MixColumn(state_.data() + 8);
  MixColumn(state_.data() + 12);
}


void AES::ShiftRows() {
  std::array<uint8_t, 16> temp;
  RotateMatrix(state_.data(), temp.data());

  ShiftRow(temp.data() + 4, 1);
  ShiftRow(temp.data() + 8, 2);
  ShiftRow(temp.data() + 12, 3);

  RotateMatrix(temp.data(), state_.data());
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