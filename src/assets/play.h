#include <stdio.h>
static uint8_t playicon[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 
  0x00, 0x80, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x0F, 0x00, 
  0x00, 0xF0, 0x0F, 0xE0, 0x1F, 0x00, 0x00, 0xF8, 0x01, 0x00, 0x3F, 0x00, 
  0x00, 0x7C, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x3E, 0x00, 0x00, 0xF8, 0x00, 
  0x00, 0x1F, 0x00, 0x00, 0xF0, 0x01, 0x80, 0x0F, 0x00, 0x00, 0xE0, 0x03, 
  0x80, 0x07, 0x00, 0x00, 0xC0, 0x03, 0xC0, 0x03, 0x00, 0x00, 0x80, 0x07, 
  0xC0, 0x03, 0x18, 0x00, 0x80, 0x07, 0xE0, 0x01, 0x78, 0x00, 0x00, 0x0F, 
  0xE0, 0x01, 0xF8, 0x00, 0x00, 0x0F, 0xE0, 0x01, 0xF8, 0x03, 0x00, 0x0F, 
  0xE0, 0x00, 0xF8, 0x07, 0x00, 0x0E, 0xF0, 0x00, 0xF8, 0x1F, 0x00, 0x1E, 
  0xF0, 0x00, 0xF8, 0x7F, 0x00, 0x1E, 0xF0, 0x00, 0xF8, 0xFF, 0x00, 0x1E, 
  0xF0, 0x00, 0xF8, 0xFF, 0x01, 0x1E, 0xF0, 0x00, 0xF8, 0xFF, 0x00, 0x1E, 
  0xF0, 0x00, 0xF8, 0x7F, 0x00, 0x1E, 0xF0, 0x00, 0xF8, 0x1F, 0x00, 0x1E, 
  0xE0, 0x00, 0xF8, 0x07, 0x00, 0x1E, 0xE0, 0x01, 0xF8, 0x03, 0x00, 0x0F, 
  0xE0, 0x01, 0xF8, 0x00, 0x00, 0x0F, 0xE0, 0x01, 0x78, 0x00, 0x00, 0x0F, 
  0xC0, 0x03, 0x18, 0x00, 0x80, 0x07, 0xC0, 0x07, 0x00, 0x00, 0xC0, 0x07, 
  0x80, 0x07, 0x00, 0x00, 0xC0, 0x03, 0x80, 0x0F, 0x00, 0x00, 0xE0, 0x03, 
  0x00, 0x1F, 0x00, 0x00, 0xF0, 0x01, 0x00, 0x3E, 0x00, 0x00, 0xF8, 0x00, 
  0x00, 0xFC, 0x00, 0x00, 0x7C, 0x00, 0x00, 0xF8, 0x01, 0x00, 0x3F, 0x00, 
  0x00, 0xF0, 0x0F, 0xE0, 0x1F, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x0F, 0x00, 
  0x00, 0x80, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 
  0x00, 0x00, 0xE0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };
