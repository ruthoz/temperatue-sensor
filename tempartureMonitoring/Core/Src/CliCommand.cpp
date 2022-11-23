#include <CliCommand.h>


extern Led ledB;
extern Buzzer buzzer;
extern Rtc rtc;
extern Flash flash;
extern thresholdTemp Temprature;
extern CliContainer CliContainer;

class LedOnCmd : public CliCommand {
	Led *_led;
public:
	LedOnCmd (const char * name, Led * led) : CliCommand(name), _led(led) {}
	void doCommand(const char* param) override {
		_led->on();
	}
};

class LedOffCmd : public CliCommand {
	Led *_led;
public:
	LedOffCmd (const char * name, Led * led) : CliCommand(name), _led(led) {}
	void doCommand(const char* param) override {
		_led->off();
	}
};

class LedBlinkCmd : public CliCommand {
	Led *_led;
public:
	LedBlinkCmd (const char * name, Led * led) : CliCommand(name), _led(led) {}
	void doCommand(const char* param) override {
		_led->blink();
	}
};

class BuzzerOnCmd : public CliCommand {
	Buzzer *_buzzer;
public:
	BuzzerOnCmd (const char * name, Buzzer* buzzer) : CliCommand(name), _buzzer(buzzer) {}
	void doCommand(const char* param) override {
		_buzzer->on();
	}
};

class BuzzerOffCmd : public CliCommand {
	Buzzer *_buzzer;
public:
	BuzzerOffCmd (const char * name, Buzzer* buzzer) : CliCommand(name), _buzzer(buzzer) {}
	void doCommand(const char* param) override {
		_buzzer->off();
	}
};

class getDataTimeCmd : public CliCommand {
	Rtc *_rtc;
public:
	getDataTimeCmd (const char * name, Rtc* rtc) : CliCommand(name), _rtc(rtc) {}
	void doCommand(const char* param) override {
		DateTime dateTime;
		_rtc->getTime(&dateTime);
		printf("%02d:%02d:%02d-%d-%02d/%02d/%02d\r\n",
						dateTime.hours, dateTime.min, dateTime.sec,
						dateTime.weekDay,
						dateTime.day, dateTime.month, dateTime.year);
	}
};

class setDataTimeCmd : public CliCommand {
	Rtc *_rtc;
public:
	setDataTimeCmd (const char * name, Rtc* rtc) : CliCommand(name), _rtc(rtc) {}
	void doCommand(const char* param) override {
		//DateTime dateTime;
	}
};

class setCriticalTempCmd : public CliCommand {
	Flash* _flash;

public:
	setCriticalTempCmd (const char * name, Flash* flash) : CliCommand(name), _flash(flash) {}
	void doCommand(const char* param) override {
		uint16_t val;
		val = atoi(param);
		Temprature.criticalTemp = val;
		_flash->writh(&Temprature);
	}
};

class setWarningTempCmd : public CliCommand {
	Flash* _flash;

public:
	setWarningTempCmd (const char * name, Flash* flash) : CliCommand(name), _flash(flash) {}
	void doCommand(const char* param) override {
		uint16_t val;
		val = atoi(param);
		Temprature.warningTemp = val;
		_flash->writh(&Temprature);
	}
};


void CliInit()
{
	//////////////////ledB//////////////////////////////
	CliContainer.add (new LedOnCmd("ledOn", &ledB));
	CliContainer.add (new LedOffCmd("ledOff", &ledB));
	CliContainer.add (new LedBlinkCmd("ledBlink", &ledB));
	////////////////////buzzer///////////////////////////
	CliContainer.add (new BuzzerOnCmd("BOn", &buzzer));
	CliContainer.add (new BuzzerOffCmd("BOff", &buzzer));
	/////////////////////////////////////////////////////
	CliContainer.add (new getDataTimeCmd("getTime", &rtc));
	CliContainer.add (new setDataTimeCmd("setTime", &rtc));
	//////////////////////////////////////////////////////
	CliContainer.add (new setCriticalTempCmd("setCritical", &flash));
	CliContainer.add (new setWarningTempCmd("setWarning", &flash));
}

