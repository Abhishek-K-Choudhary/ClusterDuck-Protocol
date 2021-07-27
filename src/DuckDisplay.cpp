#include "DuckDisplay.h"

#ifdef CDPCFG_OLED_CLASS
#include "include/DuckTypes.h"
#include "include/DuckEsp.h"
#include "include/DuckUtils.h"
#endif

#include <vector>

#ifdef CDPCFG_OLED_CLASS

#define CDPCFG_PIN_OLED_ROTATION U8G2_R0

CDPCFG_OLED_CLASS u8g2( CDPCFG_PIN_OLED_ROTATION,
                        /* clock=*/CDPCFG_PIN_OLED_CLOCK,
                       /* data=*/CDPCFG_PIN_OLED_DATA,
                       /* reset=*/CDPCFG_PIN_OLED_RESET);

static const unsigned char u8g_logo_bits[] U8X8_PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xF8, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x1F,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xFF, 0xFF, 0x1F, 0xC0, 0x63, 0x08, 0xE3, 0xF9, 0xFD, 0x7C, 0x3E,
    0x18, 0xE3, 0x33, 0x07, 0x80, 0xFF, 0xEF, 0x3F, 0xE0, 0x67, 0x1C, 0xF3,
    0xFD, 0xFD, 0xFE, 0xFC, 0x1C, 0xF3, 0xB3, 0x03, 0xC0, 0xFF, 0x83, 0x7F,
    0x70, 0x26, 0x18, 0x3B, 0x61, 0x0C, 0xC4, 0xCE, 0x1D, 0x3B, 0xB6, 0x01,
    0xC0, 0xFF, 0x81, 0x7F, 0x30, 0x70, 0x1C, 0x7B, 0x60, 0xDC, 0xCE, 0x84,
    0x19, 0x1B, 0xF0, 0x00, 0xC0, 0xFF, 0x21, 0x7E, 0x38, 0x60, 0x1C, 0xF3,
    0x63, 0xFC, 0xFE, 0x8E, 0x1D, 0x1B, 0xF0, 0x00, 0xE0, 0xFF, 0x01, 0xFE,
    0x30, 0x70, 0x18, 0x83, 0x63, 0x0C, 0x7C, 0x8C, 0x09, 0x3B, 0xF2, 0x01,
    0xE0, 0xEF, 0x83, 0xFF, 0x70, 0xE7, 0xB9, 0x1B, 0x63, 0x1C, 0x64, 0xEC,
    0xF9, 0x73, 0xB7, 0x03, 0xE0, 0xC7, 0x87, 0xFF, 0xE0, 0xE7, 0xF3, 0xF9,
    0x71, 0xFC, 0xCE, 0xFE, 0xF8, 0xF1, 0x33, 0x07, 0xE0, 0xC7, 0x03, 0xFF,
    0x80, 0x42, 0x61, 0xA0, 0x20, 0xA4, 0x84, 0x14, 0x60, 0x80, 0x20, 0x04,
    0xE0, 0x0F, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xE0, 0x07, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x0F, 0x00, 0xFE,
    0xF0, 0x7C, 0x38, 0x3F, 0x07, 0x87, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xC0, 0x0F, 0x00, 0x7E, 0xF0, 0xFD, 0x7E, 0x9D, 0xCF, 0xCF, 0x67, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xC0, 0x1F, 0x00, 0x7F, 0x10, 0xCB, 0xC6, 0xCC,
    0xD8, 0x60, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x7F, 0x80, 0x7F,
    0xF0, 0x5D, 0xC2, 0x4C, 0x70, 0x60, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0xFF, 0xF5, 0x3F, 0xF0, 0x7C, 0xC3, 0xCC, 0xD8, 0x20, 0x2C, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x1F, 0x30, 0x6C, 0x66, 0xCC,
    0xDC, 0x6D, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x0F,
    0x10, 0xCC, 0x7C, 0x8C, 0x8F, 0xC7, 0xE7, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xFC, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};

#endif // CDPCFG_OLED_CLASS

#define u8g_logo_width 128
#define u8g_logo_height 64

DuckDisplay* DuckDisplay::instance = NULL;

DuckDisplay::DuckDisplay() {}

DuckDisplay* DuckDisplay::getInstance() {
  if (!instance) {
    instance = new DuckDisplay;
  }
  return instance;
}

#ifndef CDPCFG_OLED_NONE

void DuckDisplay::setupDisplay(int duckType, std::vector<byte> name) {
  u8g2.begin();        // clear the internal memory
  u8g2.setFont(u8g2_font_synchronizer_nbp_tf); // choose a suitable font
  u8g2.clearBuffer();  
  u8g2.drawXBM( 0, 0, u8g_logo_width, u8g_logo_height, u8g_logo_bits);
  u8g2.sendBuffer(); 
  delay(1500);
  // TODO: Add U8g2 drawLog support
  width = u8g2.getCols();
  height = u8g2.getRows();


  std::string id(name.begin(), name.end());


  if (duckType >= DuckType::MAX_TYPE) {
    this->duckType = DuckType::UNKNOWN;
  } else {
    this->duckType = duckType;
  }
  this->duckName = id.c_str();
}


void DuckDisplay::powerSave(bool save) {
  if (save) {
    // TODO check what the power save mode is with the new driver
    u8g2.clear();
  } else {
    u8g2.initDisplay();
  }
}

void DuckDisplay::drawString(u8g2_uint_t x, u8g2_uint_t y, const char *s) {
  u8g2.drawStr(x, y, s);
}

void DuckDisplay::drawString(bool cls, u8g2_uint_t x, u8g2_uint_t y, const char *s) {
  if (cls) {
    clear();
  }
  drawString(x, y, s);
}

void DuckDisplay::clearLine(u8g2_uint_t x, u8g2_uint_t y) {
  u8g2.setDrawColor(0);
  u8g2.drawBox(x, y-10, 200, 10);
  sendBuffer();
  u8g2.setDrawColor(1);
}

void DuckDisplay::setCursor(u8g2_uint_t x, u8g2_uint_t y) { u8g2.setCursor(x, y); }

void DuckDisplay::print(String s) { u8g2.print(s); }

void DuckDisplay::clear(void) { u8g2.clear(); }

void DuckDisplay::sendBuffer(void){  u8g2.sendBuffer();}

#ifndef CDPCFG_OLED_NONE
String DuckDisplay::duckTypeToString(int duckType) {
  String duckTypeStr = "";
  switch (duckType) {
    case DuckType::PAPA:
      duckTypeStr = "Papa";
      break;
    case DuckType::LINK:
      duckTypeStr = "Link";
      break;
    case DuckType::DETECTOR:
      duckTypeStr = "Detector";
      break;
    case DuckType::MAMA:
      duckTypeStr = "Mama"; 
      break; 
    default:
      duckTypeStr = "Duck";
  }
  return duckTypeStr;
}
#endif // CDPCFG_OLED_NONE



void DuckDisplay::showDefaultScreen() {
#ifdef CDPCFG_OLED_64x32
  // small display 64x32
  setCursor(0, 2);
  print("CDP");
  setCursor(0, 4);
  print("DT: " + duckTypeToString(duckType));
  setCursor(0, 5);
  print("ID: " + duckName);
#else
  u8g2.clearBuffer();  
  // default display size 128x64
  drawString(0,10, "Clusterduck ");
  drawString(0,20, "Protocol ");
  setCursor(0, 40);
  print("DT: " + duckTypeToString(duckType));
  drawString(0,50,"v");
  setCursor(5, 50);
  print(duckutils::getCDPVersion().c_str());
  drawString(0,30, "----------------");
  setCursor(0, 60);
  print("ID: " + duckName);
  setCursor(0, 70);
  print("MC: " + duckesp::getDuckMacAddress(false));
  u8g2.sendBuffer(); 
#endif // CDPCFG_OLED_64x32
}
#endif // CDPCFG_OLED_NONE
