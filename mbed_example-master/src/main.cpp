#include <mbed.h>
#include <MMA7455.h>
#include <LM75B.h>
#include <display.h>

bool accInit(MMA7455& acc);
Display *d = Display::theDisplay();

int main() {
  DigitalOut led1(LED1);
	AnalogIn pot(p15);
	MMA7455 acc(P0_27, P0_28);
  LM75B lm75b(P0_27, P0_28, LM75B::ADDRESS_1);
	float potVal = 0.0;
	float tempVal = 0.0;
	int32_t accVal[3];
	
	/* Initialise the display */	
	d->fillScreen(WHITE);
	d->setTextColor(BLACK, WHITE);

	/* Initialise accelerometer and temperature sensor */
	accInit(acc);
	lm75b.open();
	while (true) {
		potVal = pot.read();
		tempVal = lm75b.temp();
		acc.read(accVal[0], accVal[1], accVal[2]);
		d->setCursor(2,2);
		d->printf("Pot  : %1.2f\n", potVal);
		d->setCursor(2,12);
		d->printf("Temp : %03.1f\n", tempVal);
		d->setCursor(2,22);
		d->printf("Acc  : %05d, %05d, %05d\n", accVal[0], accVal[1], accVal[2]); 
		led1 = !led1;
		wait(0.5);
	}
}

bool accInit(MMA7455& acc) {
	bool result = true;
  if (!acc.setMode(MMA7455::ModeMeasurement)) {
    // d->printf("Unable to set mode for MMA7455!\n");
    result = false;
  }
	if (!acc.calibrate()) {
    // d->printf("Failed to calibrate MMA7455!\n");
    result = false;
  }
	// d->printf("MMA7455 initialised\n");
  return result;
}

