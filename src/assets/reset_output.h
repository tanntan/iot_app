#include <stdio.h>

static uint8_t reset_output[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x0F, 0x00, 0x00, 0x00, 
  0x00, 0xE0, 0x07, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 
  0x00, 0xF8, 0x01, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x55, 0x5A, 0x01, 0x00, 
  0x80, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 
  0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 
  0x00, 0x3E, 0x00, 0x00, 0xF0, 0x03, 0x00, 0xFE, 0x00, 0x00, 0xE0, 0x03, 
  0x00, 0xF8, 0x00, 0x00, 0xC0, 0x07, 0x00, 0xF8, 0x03, 0x00, 0xC0, 0x07, 
  0x00, 0xE0, 0x03, 0x00, 0x80, 0x07, 0x00, 0xE0, 0x0F, 0x00, 0x80, 0x07, 
  0x00, 0x80, 0x1F, 0x00, 0x80, 0x07, 0x00, 0x80, 0x1F, 0x00, 0x80, 0x07, 
  0x00, 0x00, 0x0E, 0x00, 0x80, 0x07, 0x00, 0x00, 0x06, 0x00, 0x80, 0x07, 
  0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 
  0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x3F, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0xFF, 0x00, 0x03, 0x00, 0x00, 0x00, 0xE7, 0x9C, 0x9F, 0xFD, 0x07, 
  0x00, 0xE3, 0xFE, 0x9F, 0xFF, 0x0F, 0x00, 0xFF, 0x77, 0xDF, 0xFD, 0x0D, 
  0x00, 0x7F, 0x7F, 0x9B, 0xCD, 0x0C, 0x00, 0xEB, 0x7F, 0xDF, 0xED, 0x0C, 
  0x00, 0xE3, 0x77, 0xDB, 0xCF, 0x0E, 0x00, 0xE3, 0x7E, 0xFF, 0xCD, 0x0C, 
  0x00, 0xC3, 0x3C, 0xFF, 0xCD, 0x0C, 0x00, 0x41, 0x00, 0x00, 0x08, 0x04, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
  };
