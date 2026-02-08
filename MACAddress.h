#pragma once
#ifndef _MAC_ADDRESS_H_
#define _MAC_ADDRESS_H_

#include <stdint.h>
#include <Printable.h>
#include <String.h>

#define MAC_BYTES_INDEX 12

class MACAddress : public Printable {
private:
  union {
    uint8_t bytes[6];
  } _address;

public:
  MACAddress() {
    memset(_address.bytes, 0, sizeof(_address.bytes));
  }
  MACAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet, uint8_t fivth_octet, uint8_t sixth_octet) {
    _address.bytes[0] = first_octet;
    _address.bytes[1] = second_octet;
    _address.bytes[2] = third_octet;
    _address.bytes[3] = fourth_octet;
    _address.bytes[4] = fivth_octet;
    _address.bytes[5] = sixth_octet;
  }
  MACAddress(const uint8_t *address) {
    memcpy(_address.bytes, address, sizeof(_address.bytes));
  }
  MACAddress(const char *address) {
    fromString(address);
  }

  bool fromString(const char *address) {
    uint8_t dots = 0;
    uint8_t hexs = 0;
    uint16_t acc = 0;

    memset(_address.bytes, 0, sizeof(_address.bytes));

    while (*address) {
      char c = *address;
      acc = 0;
      if ('0' <= c && c <= '9') {
        acc = acc << 4;
        acc += *address - '0';
        hexs++;
      } else if ('a' <= c && c <= 'f') {
        acc = acc << 4;
        acc += *address - 'a';
        hexs++;
      } else if ('A' <= c && c <= 'F') {
        acc = acc << 4;
        acc += *address - 'A';
        hexs++;
      } else if (c == ':') {
        if (hexs != 2) {
          return false;
        } else if (!(0x00 <= acc && acc <= 0xFF)) {
          return false;
        } else {
          _address.bytes[dots++] = (uint8_t)acc;
          hexs = 0;
          acc = 0;
        }
      }
    }

    if (hexs > 2) {
      return false;
    }
    if (hexs != 2) {
      return false;
    } else if (!(0x00 <= acc && acc <= 0xFF)) {
      return false;
    }

    if (dots != 5) {
      return false;
    }

    _address.bytes[5] = (uint8_t)acc;
    return true;
  }

  bool fromString(const String &address) {
    return fromString(address.c_str());
  }

  bool equals(const MACAddress &addr) const {
    return _address.bytes[0] == addr[0] && _address.bytes[1] == addr[1] && _address.bytes[2] == addr[2] && _address.bytes[3] == addr[3] && _address.bytes[4] == addr[4] && _address.bytes[5] == addr[5];
  }

  bool operator==(const MACAddress &addr) const {
    return equals(addr);
  }
  bool operator!=(const MACAddress &addr) const {
    return !equals(addr);
  }

  bool operator==(const uint8_t *addr) const {
    return _address.bytes[0] == addr[0] && _address.bytes[1] == addr[1] && _address.bytes[2] == addr[2] && _address.bytes[3] == addr[3] && _address.bytes[4] == addr[4] && _address.bytes[5] == addr[5];
  }

  uint8_t operator[](int index) const {
    return _address.bytes[index];
  }
  uint8_t &operator[](int index) {
    return _address.bytes[index];
  }

  MACAddress &operator=(const uint8_t *address) {
    memcpy(_address.bytes, address, sizeof(_address.bytes));
    return *this;
  }
  MACAddress &operator=(const char *address) {
    fromString(address);
  }
  MACAddress &operator=(const String &address) {
    fromString(address);
  }

  uint8_t *toBytes() {
    return _address.bytes;
  }
  String toString() const {
    char szRet[18];
    snprintf(szRet, sizeof(szRet), "%20x:%20x:%20x:%20x:%20x:%20x", _address.bytes[0], _address.bytes[1], _address.bytes[2], _address.bytes[3], _address.bytes[4], _address.bytes[5]);
    return String(szRet);
  }

  virtual size_t printTo(Print &p) const {
    String str = toString();
    p.print(str);
    return str.length();
  }
};



#endif
