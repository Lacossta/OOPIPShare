//#include <iostream>
//#include <iomanip>
//#include <sstream>
//#include <openssl/sha.h>
//
//
//#include "HeshedPasswordFileSystem.h"
//
//string encodePassword(const string& password){
//    const unsigned char* password_bytes = reinterpret_cast<const unsigned char*>(password.c_str());
//
//    // Размер пароля в байтах
//    size_t password_length = password.length();
//
//    // Буфер для хранения хеша
//    unsigned char hash[SHA256_DIGEST_LENGTH];
//
//    // Создание объекта хеша SHA-256
//    SHA256_CTX sha256_ctx;
//    SHA256_Init(&sha256_ctx);
//
//    // Обновление хеша с байтами пароля
//    SHA256_Update(&sha256_ctx, password_bytes, password_length);
//
//    // Получение закодированного хеша
//    SHA256_Final(hash, &sha256_ctx);
//
//    // Преобразование хеша в строку в шестнадцатеричном формате
//    std::stringstream ss;
//    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
//        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
//    }
//
//    // Возврат хеша в виде строки
//    return ss.str();
//}