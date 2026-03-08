//-----------------------------------------------------------------
//
//  MAC Address(EUI-64)
//
//  Auther: Yusuke Shimizu - Workshpop Asahi
//  https://www.ws-asahi.net
//
//-----------------------------------------------------------------
#pragma once
#ifndef MAC_ADDRESS_EUII64_H
#define MAC_ADDRESS_EUII64_H
#include <Arduino.h>
#include "MACAddressEUI48.h"

#define MAC_EUI64_FORMAT_UPPER_COLON "%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X"
#define MAC_EUI64_FORMAT_LOWER_COLON "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x"
#define MAC_EUI64_FORMAT_UPPER_HYPHEN "%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X"
#define MAC_EUI64_FORMAT_LOWER_HYPHEN "%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x"
#define MAC_EUI64_FORMAT_UPPER_PERIOD "%04X.%04X.%04X.%04X"
#define MAC_EUI64_FORMAT_LOWER_PERIOD "%04x.%04x.%04x.%04x"

#define MAC_EUI64_BYTES_LENGTH 8
#define MAC_EUI64_WORDS_LENGTH 4
#define MAC_EUI64_STR_LENGTH 40


class MACAddressEUI64 : public Printable {
public:

private:
  union {
    uint8_t bytes[MAC_EUI64_BYTES_LENGTH];
    uint16_t words[MAC_EUI64_WORDS_LENGTH];
  } _address;

  static inline MacFormat _defaultFormat = MacFormat::UPPER_COLON;
  MacFormat _format;

public:
  MACAddressEUI64() {
    clear();
    _format = _defaultFormat;
  }
  MACAddressEUI64(const MacFormat format) {
    clear();
    _format = format;
  }
  MACAddressEUI64(const uint8_t firstOctet, const uint8_t secondOctet, const uint8_t thirdOctet, const uint8_t fourthOctet, const uint8_t fifthOctet, const uint8_t sixthOctet, const uint8_t seventhOctet, const uint8_t eighthOctet) {
    fromBytes(firstOctet, secondOctet, thirdOctet, fourthOctet, fifthOctet, sixthOctet, seventhOctet, eighthOctet);
    _format = _defaultFormat;
  }
  MACAddressEUI64(const uint8_t firstOctet, const uint8_t secondOctet, const uint8_t thirdOctet, const uint8_t fourthOctet, const uint8_t fifthOctet, const uint8_t sixthOctet,  const uint8_t seventhOctet, const uint8_t eighthOctet, const MacFormat format) {
    fromBytes(firstOctet, secondOctet, thirdOctet, fourthOctet, fifthOctet, sixthOctet, seventhOctet, eighthOctet);
    _format = format;
  }
  MACAddressEUI64(const uint16_t firstWord, const uint16_t secondWord, const uint16_t thirdWord, const uint16_t fourthWord) {
    fromWords(firstWord, secondWord, thirdWord, fourthWord);
    _format = _defaultFormat;
  }
  MACAddressEUI64(const uint16_t firstWord, const uint16_t secondWord, const uint16_t thirdWord, const uint16_t fourthWord, const MacFormat format) {
    fromWords(firstWord, secondWord, thirdWord, fourthWord);
    _format = format;
  }
  MACAddressEUI64(const uint8_t* bytes) {
    fromBytes(bytes);
    _format = _defaultFormat;
  }
  MACAddressEUI64(const uint8_t* bytes, const MacFormat format) {
    fromBytes(bytes);
    _format = format;
  }
  MACAddressEUI64(const uint16_t* words) {
    fromWords(words);
    _format = _defaultFormat;
  }
  MACAddressEUI64(const uint16_t* words, const MacFormat format) {
    fromWords(words);
    _format = format;
  }
  MACAddressEUI64(const MACAddressEUI64& addr) {
    fromBytes(addr._address.bytes);
    _format = _defaultFormat;
  }
  MACAddressEUI64(const MACAddressEUI64& addr, const MacFormat format) {
    fromBytes(addr._address.bytes);
    _format = format;
  }
  MACAddressEUI64(const char* addr) {
    fromString(addr);
    _format = _defaultFormat;
  }
  MACAddressEUI64(const char* addr, const MacFormat format) {
    fromString(addr);
    _format = format;
  }
  MACAddressEUI64(const String& addr) {
    fromString(addr);
    _format = _defaultFormat;
  }
  MACAddressEUI64(const String& addr, const MacFormat format) {
    fromString(addr);
    _format = format;
  }
  

  bool fromString(const String& addr) {
    return fromString(addr);
  }
  bool fromString(const String& addr, const MacFormat format) {
    char str[MAC_EUI64_STR_LENGTH];
    addr.toCharArray(str, MAC_EUI64_STR_LENGTH);
    return fromString(str, format);
  }

  static bool fromString(uint8_t* bytes, const String& addr) {
    return fromString(bytes, addr, _defaultFormat);
  }
  static bool fromString(uint8_t* bytes, const String& addr, const MacFormat format) {
    char str[MAC_EUI64_STR_LENGTH];
    addr.toCharArray(str, MAC_EUI64_STR_LENGTH);
    return fromString(bytes, str, format);
  }

  static bool fromString(uint16_t* words, const String& addr) {
    return fromString(words, addr, _defaultFormat);
  }
  static bool fromString(uint16_t* words, const String& addr, const MacFormat format) {
    char str[MAC_EUI64_STR_LENGTH];
    addr.toCharArray(str, MAC_EUI64_STR_LENGTH);
    return fromString(words, str, format);
  }

  bool fromString(const char* addr) {

    return fromString(_address.bytes, addr) || fromString(_address.words, addr);
  }
  bool fromString(const char* addr, const MacFormat format) {

    return fromString(_address.bytes, addr, format) || fromString(_address.words, addr, format);
  }

  static bool fromString(uint8_t* bytes, const char* addr) {
    uint8_t newBytes[MAC_EUI64_BYTES_LENGTH];

    int result = 0;
    result = sscanf(addr, MAC_EUI64_FORMAT_UPPER_COLON, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5], &newBytes[6], &newBytes[7]);
    if (result == MAC_EUI64_BYTES_LENGTH) {
      fromBytes(bytes, newBytes);
      return true;
    }
    result = sscanf(addr, MAC_EUI64_FORMAT_LOWER_COLON, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5], &newBytes[6], &newBytes[7]);
    if (result == MAC_EUI64_BYTES_LENGTH) {
      fromBytes(bytes, newBytes);
      return true;
    }

    result = sscanf(addr, MAC_EUI64_FORMAT_UPPER_HYPHEN, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5], &newBytes[6], &newBytes[7]);
    if (result == MAC_EUI64_BYTES_LENGTH) {
      fromBytes(bytes, newBytes);
      return true;
    }
    result = sscanf(addr, MAC_EUI64_FORMAT_LOWER_HYPHEN, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5], &newBytes[6], &newBytes[7]);
    if (result == MAC_EUI64_BYTES_LENGTH) {
      fromBytes(bytes, newBytes);
      return true;
    }

    return false;
  }
  static bool fromString(uint8_t* bytes, const char* addr, const MacFormat format) {
    uint8_t newBytes[MAC_EUI64_BYTES_LENGTH];

    int result = 0;
    switch (format) {
      case MacFormat::UPPER_COLON:
        result = sscanf(addr, MAC_EUI64_FORMAT_UPPER_COLON, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5], &newBytes[6], &newBytes[7]);
        if (result == MAC_EUI64_BYTES_LENGTH) {
          fromBytes(bytes, newBytes);
          return true;
        }
        break;

      case MacFormat::LOWER_COLON:
        result = sscanf(addr, MAC_EUI64_FORMAT_LOWER_COLON, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5], &newBytes[6], &newBytes[7]);
        if (result == MAC_EUI64_BYTES_LENGTH) {
          fromBytes(bytes, newBytes);
          return true;
        }
        break;

      case MacFormat::UPPER_HYPHEN:
        result = sscanf(addr, MAC_EUI64_FORMAT_UPPER_HYPHEN, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5], &newBytes[6], &newBytes[7]);
        if (result == MAC_EUI64_BYTES_LENGTH) {
          fromBytes(bytes, newBytes);
          return true;
        }
        break;

      case MacFormat::LOWER_HYPHEN:
        result = sscanf(addr, MAC_EUI64_FORMAT_LOWER_HYPHEN, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5], &newBytes[6], &newBytes[7]);
        if (result == MAC_EUI64_BYTES_LENGTH) {
          fromBytes(bytes, newBytes);
          return true;
        }
        break;
    }

    return false;
  }

  static bool fromString(uint16_t* words, const char* addr) {
    uint16_t newWords[MAC_EUI64_WORDS_LENGTH];

    int result = 0;
    result = sscanf(addr, MAC_EUI64_FORMAT_UPPER_PERIOD, &newWords[0], &newWords[1], &newWords[2], &newWords[3]);
    if (result == MAC_EUI64_WORDS_LENGTH) {
      fromWords(words, newWords);
      return true;
    }
    result = sscanf(addr, MAC_EUI64_FORMAT_LOWER_PERIOD, &newWords[0], &newWords[1], &newWords[2], &newWords[3]);
    if (result == MAC_EUI64_WORDS_LENGTH) {
      fromWords(words, newWords);
      return true;
    }
  }
  static bool fromString(uint16_t* words, const char* addr, const MacFormat format) {
    uint16_t newWords[MAC_EUI64_BYTES_LENGTH];

    int result = 0;
    switch (format) {
      case MacFormat::UPPER_PERIOD:
        result = sscanf(addr, MAC_EUI64_FORMAT_UPPER_PERIOD, &newWords[0], &newWords[1], &newWords[2], &newWords[3]);
        if (result == MAC_EUI64_WORDS_LENGTH) {
          fromWords(words, newWords);
          return true;
        }
        break;

      case MacFormat::LOWER_PERIOD:
        result = sscanf(addr, MAC_EUI64_FORMAT_LOWER_PERIOD, &newWords[0], &newWords[1], &newWords[2], &newWords[3]);
        if (result == MAC_EUI64_WORDS_LENGTH) {
          fromWords(words, newWords);
          return true;
        }
        break;
    }

    return false;
  }

  void fromBytes(const uint8_t firstOctet, const uint8_t secondOctet, const uint8_t thirdOctet, const uint8_t fourthOctet, const uint8_t fifthOctet, const uint8_t sixthOctet, const uint8_t seventhOctet, const uint8_t eighthOctet) {
    _address.bytes[0] = firstOctet;
    _address.bytes[1] = secondOctet;
    _address.bytes[2] = thirdOctet;
    _address.bytes[3] = fourthOctet;
    _address.bytes[4] = fifthOctet;
    _address.bytes[5] = sixthOctet;
    _address.bytes[6] = seventhOctet;
    _address.bytes[7] = eighthOctet;
  }
  void fromBytes(const uint8_t* bytes) {
    fromBytes(_address.bytes, bytes);
  }
  static void fromBytes(uint8_t* target, const uint8_t* source) {
    memcpy(target, source, MAC_EUI64_BYTES_LENGTH);
  }

  void fromWords(const uint16_t firstWord, const uint16_t secondWord, const uint16_t thirdWord, const uint16_t fourthWord) {
    _address.words[0] = firstWord;
    _address.words[1] = secondWord;
    _address.words[2] = thirdWord;
    _address.words[3] = fourthWord;
  }
  void fromWords(const uint16_t* words) {
    fromWords(_address.words, words);
  }
  static void fromWords(uint16_t* target, const uint16_t* source) {
    memcpy(target, source, MAC_EUI64_WORDS_LENGTH);
  }

  bool equals(const MACAddressEUI64& addr) const {
    return _address.bytes[0] == addr[0] && _address.bytes[1] == addr[1] && _address.bytes[2] == addr[2] && _address.bytes[3] == addr[3] && _address.bytes[4] == addr[4] && _address.bytes[5] == addr[5] && _address.bytes[6] == addr[6] && _address.bytes[7] == addr[7];
  }
  bool equals(const uint8_t* bytes) const {
    return equals(bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);
  }
  bool equals(const uint16_t* words) const {
    return equals(words[0], words[1], words[2], words[3]);
  }
  bool equals(const uint8_t firstOctet, const uint8_t secondOctet, const uint8_t thirdOctet, const uint8_t fourthOctet, const uint8_t fifthOctet, const uint8_t sixthOctet, const uint8_t seventhOctet, const uint8_t eighthOctet) const {
    return _address.bytes[0] == firstOctet && _address.bytes[1] == secondOctet && _address.bytes[2] == thirdOctet && _address.bytes[3] == fourthOctet && _address.bytes[4] == fifthOctet && _address.bytes[5] == sixthOctet && _address.bytes[6] == seventhOctet && _address.bytes[7] == eighthOctet;
  }
  bool equals(const uint16_t firstWord, const uint16_t secondWord, const uint16_t thirdWord, const uint16_t fourthWord) const {
    return _address.words[0] == firstWord && _address.words[1] == secondWord && _address.words[2] == thirdWord && _address.words[3] == fourthWord;
  }

  bool operator==(const MACAddressEUI64& addr) const {
    return equals(addr);
  }
  bool operator!=(const MACAddressEUI64& addr) const {
    return !equals(addr);
  }

  bool operator==(const uint8_t* bytes) const {
    return equals(bytes);
  }
  bool operator!=(const uint8_t* bytes) const {
    return !equals(bytes);
  }
  bool operator==(const uint16_t* words) const {
    return equals(words);
  }
  bool operator!=(const uint16_t* words) const {
    return !equals(words);
  }

  uint8_t operator[](int index) const {
    return _address.bytes[index];
  }
  uint8_t& operator[](int index) {
    return _address.bytes[index];
  }

  MACAddressEUI64& operator=(const uint8_t* bytes) {
    fromBytes(bytes);
    return *this;
  }
  MACAddressEUI64& operator=(const char* addr) {
    fromString(addr);
    return *this;
  }
  MACAddressEUI64& operator=(const String& addr) {
    fromString(addr);
    return *this;
  }

  operator uint8_t*() {
    return toBytes();
  }
  operator uint16_t*() {
    return toWords();
  }
  operator String() {
    return toString();
  }

  void setFormat(const MacFormat format) {
    _format = format;
  }
  static void setDefaultFormat(const MacFormat format) {
    _defaultFormat = format;
  }

  MacType getType(){
    return getType(_address.bytes[0]);
  }
  static MacType getType(const uint16_t firstWord){
    return getType((uint8_t)(firstWord & 0x000F));
  }
  static MacType getType(const uint8_t firstOctet){
    uint8_t id = firstOctet & 0x0F;
    switch(id){
      case 0x0:
      case 0x4:
      case 0x8:
      case 0xC:
        return MacType::GLOBAL_UNICAST;
        
      case 0x1:
      case 0x5:
      case 0x9:
      case 0xD:
        return MacType::GLOBAL_MULTICAST;

      case 0x2:
      case 0x6:
      case 0xA:
      case 0xE:
        return MacType::LOCAL_UNICAST;
        
      case 0x3:
      case 0x7:
      case 0xB:
      case 0xF:
        return MacType::LOCAL_MULTICAST;
    }
    return MacType::UNKNOWN;
  }

  uint8_t* toBytes() {
    return _address.bytes;
  }
  uint16_t* toWords() {
    return _address.words;
  }
  String toString() const {
    char str[MAC_EUI64_STR_LENGTH];
    toCharArray(str);
    return String(str);
  }
  String toString(const MacFormat format) const {
    char str[MAC_EUI64_STR_LENGTH];
    toCharArray(str, format);
    return String(str);
  }
  static String toString(const uint8_t* bytes) {
    char str[MAC_EUI64_STR_LENGTH];
    toCharArray(str, bytes);
    return String(str);
  }
  static String toString(const uint8_t* bytes, const MacFormat format) {
    char str[MAC_EUI64_STR_LENGTH];
    toCharArray(str, bytes, format);
    return String(str);
  }
  static String toString(const uint16_t* words) {
    char str[MAC_EUI64_STR_LENGTH];
    toCharArray(str, words);
    return String(str);
  }
  static String toString(const uint16_t* words, const MacFormat format) {
    char str[MAC_EUI64_STR_LENGTH];
    toCharArray(str, words, format);
    return String(str);
  }

  int toCharArray(char* c_array) const {
    return toCharArray(c_array, _format);
  }
  int toCharArray(char* c_array, const MacFormat format) const {
    switch(format){
      case MacFormat::UPPER_COLON:
      case MacFormat::LOWER_COLON:
      case MacFormat::UPPER_HYPHEN:
      case MacFormat::LOWER_HYPHEN:
        return toCharArray(c_array, _address.bytes, format);
        
      case MacFormat::UPPER_PERIOD:
      case MacFormat::LOWER_PERIOD:
        return toCharArray(c_array, _address.words, format);
    }

    return -1;
  }
  static int toCharArray(char* c_array, const uint8_t* bytes) {
    return toCharArray(c_array, bytes, _defaultFormat);
  }
  static int toCharArray(char* c_array, const uint8_t* bytes, const MacFormat format) {
    switch(format){
      case MacFormat::UPPER_COLON:
        return sprintf(c_array, MAC_EUI64_FORMAT_UPPER_COLON, bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);
        
      case MacFormat::LOWER_COLON:
        return sprintf(c_array, MAC_EUI64_FORMAT_LOWER_COLON, bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);
        
      case MacFormat::UPPER_HYPHEN:
        return sprintf(c_array, MAC_EUI64_FORMAT_UPPER_HYPHEN, bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);
        
      case MacFormat::LOWER_HYPHEN:
        return sprintf(c_array, MAC_EUI64_FORMAT_LOWER_HYPHEN, bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);
    }
    return -1;
  }
  static int toCharArray(char* c_array, const uint16_t* words) {
    return toCharArray(c_array, words, _defaultFormat);
  }
  static int toCharArray(char* c_array, const uint16_t* words, const MacFormat format) {
    switch(format){
      case MacFormat::UPPER_PERIOD:
        return sprintf(c_array, MAC_EUI64_FORMAT_UPPER_PERIOD, words[0], words[1], words[2], words[3]);
        
      case MacFormat::LOWER_PERIOD:
        return sprintf(c_array, MAC_EUI64_FORMAT_LOWER_PERIOD, words[0], words[1], words[2], words[3]);
    }
    return -1;
  }

  virtual size_t printTo(Print& p) const {
    char str[MAC_EUI64_STR_LENGTH];
    toCharArray(str);

    return p.print(str);
  }
private:
  void clear() {
    memset(_address.bytes, 0, sizeof(_address.bytes));
  }
};


#endif