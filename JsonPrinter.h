// ----------------------------------------------------------------------------
// JsonPrinter.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _JSON_PRINTER_H_
#define _JSON_PRINTER_H_
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Streaming.h"
#include "Array.h"
#include "ConstantVariable.h"
#include "GenericSerial.h"


class JsonDepthTracker
{
public:
  JsonDepthTracker();
  JsonDepthTracker(bool first_item, bool inside_object);
  bool first_item_;
  bool inside_object_;
};

class JsonPrinter
{
public:
  enum ResponseCodes
    {
      ERROR=0,
      SUCCESS=1,
    };
  static const uint8_t STRING_LENGTH_DOUBLE=36;
  static const uint8_t DOUBLE_DIGITS=4;

  JsonPrinter(GenericSerial &serial);
  void setSerial(GenericSerial &serial);
  void startObject();
  void stopObject();
  void startArray();
  void stopArray();
  void setCompactPrint();
  void setPrettyPrint();
  void addKey(const char *key);
  void addKey(const String key);
  void addKey(const ConstantString key);
  template<typename T>
  void add(T value);
  template<typename T>
  void add(const char *key, T value)
  {
    addKey(key);
    add(value);
  }
  template<typename T>
  void add(const String key, T value)
  {
    addKey(key);
    add(value);
  }
  template<typename T>
  void add(const ConstantString key, T value)
  {
    addKey(key);
    add(value);
  }
  void addNull(const char *key)
  {
    addKey(key);
    addNull();
  }
  void addNull(const String key)
  {
    addKey(key);
    addNull();
  }
  void addNull(const ConstantString key)
  {
    addKey(key);
    addNull();
  }
  void addNull();
private:
  static const uint8_t RESPONSE_DEPTH_MAX=8;
  static const uint8_t RESPONSE_INDENT=2;
  GenericSerial generic_serial_;
  bool pretty_print_;
  int indent_level_;
  Array<JsonDepthTracker,RESPONSE_DEPTH_MAX> jdt_array_;
  void indent();
  void stopItem();
  void stopArrayItem();
};
#endif
