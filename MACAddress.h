//-----------------------------------------------------------------
//
//  MAC Address
//
//  Auther: Yusuke Shimizu - Workshpop Asahi
//  https://www.ws-asahi.net
//
//-----------------------------------------------------------------
//
// class MACAddressEUI48
//   IEEE 802 EUI-48 format
//   6 byte address
//   For Ethernet / Wi-Fi / Bluetooth
//  
// class MACAddressEUI64
//   IEEE 802 EUI-64 format
//   8 byte address
//   For ZiegBee / FireWire
//
//-----------------------------------------------------------------
#pragma once
#ifndef MAC_ADDRESS_H
#define MAC_ADDRESS_H

enum MacFormat {
  UPPER_COLON,
  LOWER_COLON,
  UPPER_HYPHEN,
  LOWER_HYPHEN,
  UPPER_PERIOD,
  LOWER_PERIOD,
};

enum MacType{
  UNKNOWN,
  GLOBAL_UNICAST,
  GLOBAL_MULTICAST,
  LOCAL_UNICAST,
  LOCAL_MULTICAST,
};

#ifndef MAC_ONLY_EUI64
  #include "MACAddressEUI48.h"
#endif

#ifndef MAC_ONLY_EUI48
  #include "MACAddressEUI64.h"
#endif


#if !defined(MAC_ONLY_EUI48) && !defined(MAC_ONLY_EUI64)
void EUI48toEUI64(MACAddressEUI64& target, const MACAddressEUI48& source){
  target[0] = source[0] ^ 0x02;
  target[1] = source[1];
  target[2] = source[2];
  target[3] = 0xFF;
  target[4] = 0xFE;
  target[5] = source[3];
  target[6] = source[4];
  target[7] = source[5];
}

void EUI64toEUI48(MACAddressEUI48& target, const MACAddressEUI64& source){
    target[0] = source[0] ^ 0x02;
    target[1] = source[1];
    target[2] = source[2];
    target[3] = source[5];
    target[4] = source[6];
    target[5] = source[7];
}
#endif



#endif