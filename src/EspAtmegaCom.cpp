#include "EspAtmegaCom.h"

EspAtmegaCom::EspAtmegaCom(HardwareSerial &serial) {
	this->_serial = &serial;
	setCallback(NULL);
}

EspAtmegaCom::EspAtmegaCom(HardwareSerial &serial, EAC_CALLBACK_SIGNATURE) {
	this->_serial = &serial;
	setCallback(callback);
}

String EspAtmegaCom::read() {
  if (_serial->available()) {
    String data = _serial->readStringUntil('\n');
    data.trim();
    int startTag = data.indexOf(EAC_START_TAG);
    int endTag = data.indexOf(EAC_END_TAG);
    if (startTag >= 0 && endTag >= 0) {
      data.remove(endTag);
      data.remove(0, startTag + 3);
      return data;
    }
    return "";
  }
  return "";
}

int EspAtmegaCom::available() {
	return _serial->available();
}

void EspAtmegaCom::begin() {
	begin(115200);
}

void EspAtmegaCom::begin(long baud) {
	_serial->begin(baud);
	while (!_serial) {
		// wait serial port initialization
	}
	_serial->setTimeout(100);
}

void EspAtmegaCom::send(String payload) {
	_serial->println(EAC_START_TAG + payload + EAC_END_TAG);
}

void EspAtmegaCom::loop() {
	String data = read();
	if (data.length() > 0 && callback) {
		callback(data);
	}
}

void EspAtmegaCom::setCallback(EAC_CALLBACK_SIGNATURE) {
	this->callback = callback;
}
