#ifndef EspAtmegaCom_h
#define EspAtmegaCom_h

#include <WString.h>
#include <HardwareSerial.h>

#define EAC_START_TAG "+S+"
#define EAC_END_TAG "-E-"

#ifdef ESP8266
#include <functional>
#define EAC_CALLBACK_SIGNATURE std::function<void(String)> callback
#else
#define EAC_CALLBACK_SIGNATURE void (*callback)(String)
#endif

class EspAtmegaCom {
  private:
	HardwareSerial *_serial;
	EAC_CALLBACK_SIGNATURE;
	String read();
	int available();
  public:
	EspAtmegaCom(HardwareSerial&);
	EspAtmegaCom(HardwareSerial&,EAC_CALLBACK_SIGNATURE);
	void begin();
	void begin(long);
	void send(String);
	void loop();
	void setCallback(EAC_CALLBACK_SIGNATURE);
};

#endif

