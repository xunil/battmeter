#include <avr/io.h>
#include <util/twi.h>
#include "twi.h"

void twi_change_condition(int condition) {
  TWCR = (1<<TWINT)|(1<<TWEN) | (condition == TWI_START ? (1<<TWSTA) : (1<<TWSTO));
  twi_wait_tx();
}

void twi_tx(char addr) {
  TWDR = addr;
  TWCR = (1<<TWINT)|(1<<TWEN);
  twi_wait_tx();
}
