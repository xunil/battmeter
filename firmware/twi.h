#ifndef __TWI_H__
#define __TWI_H__ 1

#define twi_wait_tx() while (!(TWCR & (1<<TWINT)))
#define twi_start() twi_change_condition(TWI_START)
#define twi_repeated_start() twi_change_condition(TWI_START)
#define twi_stop() twi_change_condition(TWI_STOP)
#define twi_data(c) twi_tx(c)

#define TWI_START 0
#define TWI_STOP 1

void twi_change_condition(int condition);
void twi_tx(char addr);

#endif
