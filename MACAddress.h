//-----------------------------------------------------------------
//
//  MAC Address(EUI-48)
//
//  Auther: Yusuke Shimizu - Workshpop Asahi
//  https://www.ws-asahi.net
//
//-----------------------------------------------------------------
#pragma once
#ifndef MAC_ADDRESS_H
#define MAC_ADDRESS_H
#include <Arduino.h>

#define MAC_FORMAT_UPPER_COLON "%02X:%02X:%02X:%02X:%02X:%02X"
#define MAC_FORMAT_LOWER_COLON "%02x:%02x:%02x:%02x:%02x:%02x"
#define MAC_FORMAT_UPPER_HYPHEN "%02X-%02X-%02X-%02X-%02X-%02X"
#define MAC_FORMAT_LOWER_HYPHEN "%02x-%02x-%02x-%02x-%02x-%02x"
#define MAC_FORMAT_UPPER_PERIOD "%04X.%04X.%04X"
#define MAC_FORMAT_LOWER_PERIOD "%04x.%04x.%04x"

#define MAC_BYTES_LENGTH 6
#define MAC_WORDS_LENGTH 3
#define MAC_STR_LENGTH 32

class MACAddress : public Printable {
public:
  enum MacFormat {
    UPPER_COLON,  // default setting
    LOWER_COLON,
    UPPER_HYPHEN,
    LOWER_HYPHEN,
    UPPER_PERIOD,
    LOWER_PERIOD,
  };

private:
  union {
    uint8_t bytes[MAC_BYTES_LENGTH];
    uint16_t words[MAC_WORDS_LENGTH];
  } _address;

  static inline MacFormat _defaultFormat = MacFormat::UPPER_COLON;
  MacFormat _format;

public:
  MACAddress() {
    clear();
    _format = _defaultFormat;
  }
  MACAddress(const MacFormat format) {
    clear();
    _format = format;
  }
  MACAddress(const uint8_t firstOctet, const uint8_t secondOctet, const uint8_t thirdOctet, const uint8_t fourthOctet, const uint8_t fifthOctet, const uint8_t sixthOctet) {
    fromBytes(firstOctet, secondOctet, thirdOctet, fourthOctet, fifthOctet, sixthOctet);
    _format = _defaultFormat;
  }
  MACAddress(const uint8_t firstOctet, const uint8_t secondOctet, const uint8_t thirdOctet, const uint8_t fourthOctet, const uint8_t fifthOctet, const uint8_t sixthOctet, const MacFormat format) {
    fromBytes(firstOctet, secondOctet, thirdOctet, fourthOctet, fifthOctet, sixthOctet);
    _format = format;
  }
  MACAddress(const uint16_t firstWord, const uint16_t secondWord, const uint16_t thirdWord) {
    fromWords(firstWord, secondWord, thirdWord);
    _format = _defaultFormat;
  }
  MACAddress(const uint16_t firstWord, const uint16_t secondWord, const uint16_t thirdWord, const MacFormat format) {
    fromWords(firstWord, secondWord, thirdWord);
    _format = format;
  }
  MACAddress(const uint8_t* addr) {
    fromBytes(addr);
    _format = _defaultFormat;
  }
  MACAddress(const uint8_t* addr, const MacFormat format) {
    fromBytes(addr);
    _format = format;
  }
  MACAddress(const uint16_t* addr) {
    fromWords(addr);
    _format = _defaultFormat;
  }
  MACAddress(const uint16_t* addr, const MacFormat format) {
    fromWords(addr);
    _format = format;
  }
  MACAddress(const MACAddress& addr) {
    fromBytes(addr._address.bytes);
    _format = _defaultFormat;
  }
  MACAddress(const MACAddress& addr, const MacFormat format) {
    fromBytes(addr._address.bytes);
    _format = format;
  }
  MACAddress(const char* addr) {
    fromString(addr);
    _format = _defaultFormat;
  }
  MACAddress(const char* addr, const MacFormat format) {
    fromString(addr);
    _format = format;
  }
  MACAddress(const String& addr) {
    fromString(addr);
    _format = _defaultFormat;
  }
  MACAddress(const String& addr, const MacFormat format) {
    fromString(addr);
    _format = format;
  }

  bool fromString(const char* addr) {
    uint8_t newBytes[MAC_BYTES_LENGTH];
    uint16_t newWords[MAC_WORDS_LENGTH];

    int result = 0;
    result = sscanf(addr, MAC_FORMAT_UPPER_COLON, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5]);
    if (result == MAC_BYTES_LENGTH) {
      fromBytes(newBytes);
      return true;
    }
    result = sscanf(addr, MAC_FORMAT_LOWER_COLON, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5]);
    if (result == MAC_BYTES_LENGTH) {
      fromBytes(newBytes);
      return true;
    }

    result = sscanf(addr, MAC_FORMAT_UPPER_HYPHEN, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5]);
    if (result == MAC_BYTES_LENGTH) {
      fromBytes(newBytes);
      return true;
    }
    result = sscanf(addr, MAC_FORMAT_LOWER_HYPHEN, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5]);
    if (result == MAC_BYTES_LENGTH) {
      fromBytes(newBytes);
      return true;
    }

    result = sscanf(addr, MAC_FORMAT_UPPER_PERIOD, &newWords[0], &newWords[1], &newWords[2]);
    if (result == MAC_WORDS_LENGTH) {
      fromWords(newWords);
      return true;
    }
    result = sscanf(addr, MAC_FORMAT_LOWER_PERIOD, &newWords[0], &newWords[1], &newWords[2]);
    if (result == MAC_WORDS_LENGTH) {
      fromWords(newWords);
      return true;
    }

    return false;
  }
  bool fromString(const char* addr, const MacFormat format) {
    uint8_t newBytes[MAC_BYTES_LENGTH];
    uint16_t newWords[MAC_WORDS_LENGTH];

    int result = 0;
    switch (format) {
      case MacFormat::UPPER_COLON:
        result = sscanf(addr, MAC_FORMAT_UPPER_COLON, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5]);
        if (result == MAC_BYTES_LENGTH) {
          fromBytes(newBytes);
          return true;
        }
        break;

      case MacFormat::LOWER_COLON:
        result = sscanf(addr, MAC_FORMAT_LOWER_COLON, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5]);
        if (result == MAC_BYTES_LENGTH) {
          fromBytes(newBytes);
          return true;
        }
        break;

      case MacFormat::UPPER_HYPHEN:
        result = sscanf(addr, MAC_FORMAT_UPPER_HYPHEN, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5]);
        if (result == MAC_BYTES_LENGTH) {
          fromBytes(newBytes);
          return true;
        }
        break;

      case MacFormat::LOWER_HYPHEN:
        result = sscanf(addr, MAC_FORMAT_LOWER_HYPHEN, &newBytes[0], &newBytes[1], &newBytes[2], &newBytes[3], &newBytes[4], &newBytes[5]);
        if (result == MAC_BYTES_LENGTH) {
          fromBytes(newBytes);
          return true;
        }
        break;

      case MacFormat::UPPER_PERIOD:
        result = sscanf(addr, MAC_FORMAT_UPPER_PERIOD, &newWords[0], &newWords[1], &newWords[2]);
        if (result == MAC_WORDS_LENGTH) {
          fromWords(newWords);
          return true;
        }
        break;

      case MacFormat::LOWER_PERIOD:
        result = sscanf(addr, MAC_FORMAT_LOWER_PERIOD, &newWords[0], &newWords[1], &newWords[2]);
        if (result == MAC_WORDS_LENGTH) {
          fromWords(newWords);
          return true;
        }
        break;
    }

    return false;
  }

  bool fromString(const String& addr) {
    char str[MAC_STR_LENGTH];
    addr.toCharArray(str, MAC_STR_LENGTH);
    return fromString(str);
  }
  bool fromString(const String& addr, const MacFormat format) {
    char str[MAC_STR_LENGTH];
    addr.toCharArray(str, MAC_STR_LENGTH);
    return fromString(str, format);
  }

  void fromBytes(const uint8_t firstOctet, const uint8_t secondOctet, const uint8_t thirdOctet, const uint8_t fourthOctet, const uint8_t fifthOctet, const uint8_t sixthOctet) {
    _address.bytes[0] = firstOctet;
    _address.bytes[1] = secondOctet;
    _address.bytes[2] = thirdOctet;
    _address.bytes[3] = fourthOctet;
    _address.bytes[4] = fifthOctet;
    _address.bytes[5] = sixthOctet;
  }
  void fromBytes(const uint8_t* addr) {
    memcpy(_address.bytes, addr, MAC_BYTES_LENGTH);
  }
  void fromWords(const uint16_t firstWord, const uint16_t secondWord, const uint16_t thirdWord) {
    _address.words[0] = firstWord;
    _address.words[1] = secondWord;
    _address.words[2] = thirdWord;
  }
  void fromWords(const uint16_t* addr) {
    memcpy(_address.words, addr, MAC_WORDS_LENGTH);
  }

  bool equals(const MACAddress& addr) const {
    return _address.bytes[0] == addr[0] && _address.bytes[1] == addr[1] && _address.bytes[2] == addr[2] && _address.bytes[3] == addr[3] && _address.bytes[4] == addr[4] && _address.bytes[5] == addr[5];
  }
  bool equals(const uint8_t* addr) const {
    return equals(addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
  }
  bool equals(const uint16_t* addr) const {
    return equals(addr[0], addr[1], addr[2]);
  }
  bool equals(const uint8_t firstOctet, const uint8_t secondOctet, const uint8_t thirdOctet, const uint8_t fourthOctet, const uint8_t fifthOctet, const uint8_t sixthOctet) const {
    return _address.bytes[0] == firstOctet && _address.bytes[1] == secondOctet && _address.bytes[2] == thirdOctet && _address.bytes[3] == fourthOctet && _address.bytes[4] == fifthOctet && _address.bytes[5] == sixthOctet;
  }
  bool equals(const uint16_t firstWord, const uint16_t secondWord, const uint16_t thirdWord) const {
    return _address.words[0] == firstWord && _address.words[1] == secondWord && _address.words[2] == thirdWord;
  }

  bool operator==(const MACAddress& addr) const {
    return equals(addr);
  }
  bool operator!=(const MACAddress& addr) const {
    return !equals(addr);
  }

  bool operator==(const uint8_t* addr) const {
    return equals(addr);
  }
  bool operator!=(const uint8_t* addr) const {
    return !equals(addr);
  }
  bool operator==(const uint16_t* addr) const {
    return equals(addr);
  }
  bool operator!=(const uint16_t* addr) const {
    return !equals(addr);
  }

  uint8_t operator[](int index) const {
    return _address.bytes[index];
  }
  uint8_t& operator[](int index) {
    return _address.bytes[index];
  }

  MACAddress& operator=(const uint8_t* addr) {
    fromBytes(addr);
    return *this;
  }
  MACAddress& operator=(const char* addr) {
    fromString(addr);
    return *this;
  }
  MACAddress& operator=(const String& addr) {
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

  uint8_t* toBytes() {
    return _address.bytes;
  }
  uint16_t* toWords() {
    return _address.words;
  }
  String toString() const {
    char str[MAC_STR_LENGTH];
    toCharArray(str);
    return String(str);
  }
  int toCharArray(char* c_array) const {
    switch(_format){
      case MacFormat::UPPER_COLON:
        return sprintf(c_array, MAC_FORMAT_UPPER_COLON, _address.bytes[0], _address.bytes[1], _address.bytes[2], _address.bytes[3], _address.bytes[4], _address.bytes[5]);
        
      case MacFormat::LOWER_COLON:
        return sprintf(c_array, MAC_FORMAT_LOWER_COLON, _address.bytes[0], _address.bytes[1], _address.bytes[2], _address.bytes[3], _address.bytes[4], _address.bytes[5]);
        
      case MacFormat::UPPER_HYPHEN:
        return sprintf(c_array, MAC_FORMAT_UPPER_HYPHEN, _address.bytes[0], _address.bytes[1], _address.bytes[2], _address.bytes[3], _address.bytes[4], _address.bytes[5]);
        
      case MacFormat::LOWER_HYPHEN:
        return sprintf(c_array, MAC_FORMAT_LOWER_HYPHEN, _address.bytes[0], _address.bytes[1], _address.bytes[2], _address.bytes[3], _address.bytes[4], _address.bytes[5]);
        
      case MacFormat::UPPER_PERIOD:
        return sprintf(c_array, MAC_FORMAT_UPPER_PERIOD, _address.words[0], _address.words[1], _address.words[2]);
        
      case MacFormat::LOWER_PERIOD:
        return sprintf(c_array, MAC_FORMAT_LOWER_PERIOD, _address.words[0], _address.words[1], _address.words[2]);
    }

    return -1;
  }

  virtual size_t printTo(Print& p) const {
    char str[MAC_STR_LENGTH];
    toCharArray(str);

    return p.print(str);
  }
private:
  void clear() {
    memset(_address.bytes, 0, sizeof(_address.bytes));
  }
};


#endif