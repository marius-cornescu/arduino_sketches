//= CONSTANTS ======================================================================================
//= VARIABLES ======================================================================================
//==================================================================================================
static const char* bin2tristate(const char* bin);
static char * dec2binWzerofill(unsigned long Dec, unsigned int bitLength);
//==================================================================================================
void printRxToSerial(unsigned long decimal, unsigned int length, unsigned int delay, unsigned int* raw, unsigned int protocol) {
#ifdef RfLogsToSerial
  const char* b = dec2binWzerofill(decimal, length);

  char buffer[200];
  sprintf(buffer, "Decimal: %d (%dBit) Binary: %d Tri-State: %d PulseLength: %d microseconds Protocol: %d",
          decimal, length, b, bin2tristate(b), delay, protocol);
  Serial.println(buffer);

  Serial.print("Raw data: ");
  for (unsigned int i = 0; i <= length * 2; i++) {
    Serial.print(raw[i]);
    Serial.print(",");
  }
  Serial.println();
  Serial.println();
#endif
}
//==================================================================================================
#ifdef RfLogsToSerial
//==================================================================================================
static const char* bin2tristate(const char* bin) {
  static char returnValue[50];
  int pos = 0;
  int pos2 = 0;
  while (bin[pos] != '\0' && bin[pos + 1] != '\0') {
    if (bin[pos] == '0' && bin[pos + 1] == '0') {
      returnValue[pos2] = '0';
    } else if (bin[pos] == '1' && bin[pos + 1] == '1') {
      returnValue[pos2] = '1';
    } else if (bin[pos] == '0' && bin[pos + 1] == '1') {
      returnValue[pos2] = 'F';
    } else {
      return "not applicable";
    }
    pos = pos + 2;
    pos2++;
  }
  returnValue[pos2] = '\0';
  return returnValue;
}
//==================================================================================================
static char* dec2binWzerofill(unsigned long decimal, unsigned int bitLength) {
  static char bin[64];
  unsigned int i = 0;

  while (decimal > 0) {
    bin[32 + i++] = ((decimal & 1) > 0) ? '1' : '0';
    decimal = decimal >> 1;
  }

  for (unsigned int j = 0; j < bitLength; j++) {
    if (j >= bitLength - i) {
      bin[j] = bin[ 31 + i - (j - (bitLength - i)) ];
    } else {
      bin[j] = '0';
    }
  }
  bin[bitLength] = '\0';

  return bin;
}
//==================================================================================================
#endif
