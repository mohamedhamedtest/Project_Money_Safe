/*
 * Money_Safe.h
 *
 *  Created on: Aug 23, 2023
 *      Author: user
 */

#ifndef MONEY_SAFE_MONEY_SAFE_H_
#define MONEY_SAFE_MONEY_SAFE_H_

#include"../LCD/LCD.h"
#include"../STD_TYPES.h"

typedef enum{
	Correct_password = -1,
	wrong_password = -2
}state;

//password
#define Saved_password 123
#define input_attempts 3

//prototypes
state Check_Password(u32 password);
void Show_Balance(void);
void Inset_Money(u32 money);
void Withdraw(u32 money);


#endif /* MONEY_SAFE_MONEY_SAFE_H_ */
