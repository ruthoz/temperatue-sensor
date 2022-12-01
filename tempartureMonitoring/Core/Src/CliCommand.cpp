#include <CliCommand.h>


extern Led ledB;
extern Buzzer buzzer;
extern Rtc rtc;
extern Flash flash;
extern thresholdTemp Temprature;
extern CliContainer CliContainer;
extern DateTime dateTime;
extern File logFile;
extern File warningFile;

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
		const char s[2] = ":";
		char* date= (char*) param;
		//day:month:year:hours:min:sec
		//"01:01:22:12:12:12"
		dateTime.day = atoi(strtok(date, s));
		dateTime.month = atoi(strtok(NULL, s));
		dateTime.year = atoi(strtok(NULL, s));
		dateTime.hours = atoi(strtok(NULL, s));
		dateTime.min = atoi(strtok(NULL, s));
		dateTime.sec = atoi(strtok(NULL, s));
		_rtc->setTime(&dateTime);
	}
};

class setCriticalTempCmd : public CliCommand {
	Flash* _flash;

public:
	setCriticalTempCmd (const char * name, Flash* flash) : CliCommand(name), _flash(flash) {}
	void doCommand(const char* param) override {
		uint16_t val;
		val = atoi(param);
		if(Temprature.warningTemp > val){
			printf("A critical temperature cannot be more then warning temperature\r\n");
			return;
		}
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
		if(Temprature.criticalTemp < val){
			printf("A warning temperature cannot be less then warning temperature\r\n");
			return;
		}
		Temprature.warningTemp = val;
		_flash->writh(&Temprature);
	}
};

class getCriticalTempCmd : public CliCommand {
	Flash* _flash;

public:
	getCriticalTempCmd (const char * name, Flash* flash) : CliCommand(name), _flash(flash) {}
	void doCommand(const char* param) override
	{
		_flash->read();
		printf("Critical temperature = %d\r\nWarning temperature = %d\r\n" ,Temprature.criticalTemp , Temprature.warningTemp);
	}
};

class clearFileCmd : public CliCommand {
	File* _file;

public:
	clearFileCmd (const char * name, File* file) : CliCommand(name), _file(file) {}
	void doCommand(const char* param) override
	{
		_file->clear();
	}
};

class printFileCmd : public CliCommand {
	File* _file;

public:
	printFileCmd (const char * name, File* file) : CliCommand(name), _file(file) {}
	void doCommand(const char* param) override
	{
		_file->read();
	}
};

class helpCmd : public CliCommand {

public:
	helpCmd (const char * name) : CliCommand(name) {}
	void doCommand(const char* param) override
	{
		printf("1. help\r\n"
				"2. getTime\r\n"
				"3.setTime day:month:year:hours:min:sec\r\n"
				"4.setCritical param\r\n"
				"5.setWarning param\r\n"
		        "6.clearLog\r\n"
				"7.printLog\r\n"
				"8.printLog\r\n");
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

	/////////////////////RTC//////////////////////////
	CliContainer.add (new getDataTimeCmd("getTime", &rtc));
	CliContainer.add (new setDataTimeCmd("setTime", &rtc));

	////////////////////flash/////////////////////////
	CliContainer.add (new setCriticalTempCmd("setCritical", &flash));
	CliContainer.add (new setWarningTempCmd("setWarning", &flash));

	CliContainer.add (new getCriticalTempCmd("getCritical", &flash));

	/////////////////file///////////////////////////////////////////
	CliContainer.add (new clearFileCmd("clearLog", &logFile));
	CliContainer.add (new printFileCmd("printLog", &warningFile));

	////////////////help/////////////////////////////////////////
	CliContainer.add (new helpCmd("help"));


}

