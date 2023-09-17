/*
 * main.c
 *
 *  Created on: Aug 23, 2023
 *      Author: user
 */

#define F_CPU 8000000UL
#include"money_con/Money_Safe.h"
#include"util.h"
#include"KEYPAD/keypad.h"
#include "LCD/LCD.h"
#include<avr/io.h>
#include<util/delay.h>
void Welcome_User(void) //to show user a welcome screen when opens the program
{
	LCD_CLEAR_ALL_SCREEN();
	LCD_GOTO_XY(0,0);
	SEND_A_STRING("Welcome...");
	LCD_GOTO_XY(1,0);
	SEND_A_STRING(" Enter password");
	LCD_CLEAR_ALL_SCREEN();
}

u8 Get_Number(u8 num) //to convert characters to integer numbers
{
	switch(num)
	{
	case '0': return 0; break;
	case '1': return 1; break;
	case '2': return 2; break;
	case '3': return 3; break;
	case '4': return 4; break;
	case '5': return 5; break;
	case '6': return 6; break;
	case '7': return 7; break;
	case '8': return 8; break;
	case '9': return 9; break;
	default: break;
	}
	return 0;
}


void Choose_Operation(void) //all operation (like show balance) are done here
{
	u8 keyy_pressed, num_pressed;
	u32 money = 0;
	LCD_CLEAR_ALL_SCREEN();
	back: SEND_A_STRING("1-Show balance  2-insert money  3-withdraw"); //allowed features
	LCD_CLEAR_ALL_SCREEN();
	stay:keyy_pressed = KPD_GETKEY();
	switch(keyy_pressed)
	{
	case KPD_NOT_PRESSED:
		goto stay;
	case '1': //show balance case
		LCD_CLEAR_ALL_SCREEN();
		Show_Balance();
		_delay_ms(3000);
		LCD_CLEAR_ALL_SCREEN();
		goto back;
	case '2': //Insert money case
		LCD_CLEAR_ALL_SCREEN();
		SEND_A_STRING("Enter money: ");
		LCD_GOTO_XY(1,0);
		stay2: keyy_pressed = KPD_GETKEY();
		switch(keyy_pressed) //switch case to get inserted money
		{
		case KPD_NOT_PRESSED: //no key pressed
			goto stay2;
		case 'C': //clear screen
			break;
		case '=': //insert money function is done here
			LCD_CLEAR_ALL_SCREEN();
			Inset_Money(money);
			_delay_ms(3000);
			LCD_CLEAR_ALL_SCREEN();
			LCD_GOTO_XY(0,0);
			num_pressed= 0;
			money = 0;
			goto back;
		default: //store entered numbers as money to be inserted
			SEND_A_CHAR(keyy_pressed);
			num_pressed = Get_Number(keyy_pressed);
			money = money*10 + num_pressed;
			goto stay2;
		}

		break;
	case '3': //withdraw money case
		LCD_CLEAR_ALL_SCREEN();
		SEND_A_STRING("Enter amount: ");
		LCD_GOTO_XY(1,0);
		stay3: keyy_pressed = KPD_GETKEY();
		switch(keyy_pressed)
		{
		case KPD_NOT_PRESSED: //no key pressed
			goto stay3;
		case 'C': //clear screen
			break;
		case '=':
			LCD_CLEAR_ALL_SCREEN();
			Withdraw(money);
			_delay_ms(3000);
			LCD_CLEAR_ALL_SCREEN();
			LCD_GOTO_XY(0,0);
			num_pressed= 0;
			money = 0;
			goto back;
		default:
			SEND_A_CHAR(keyy_pressed);
			num_pressed = Get_Number(keyy_pressed);
			money = money*10 + num_pressed;
			goto stay3;
		}
		break;
	default:
		break;
	}
}


int main(void)
{
	KPD_INIT();
	LCD_INIT();
	LCD_CLEAR_ALL_SCREEN();

	Welcome_User();

	u8 key_pressed, num_pressed=0, password=0, count = 1;
	 state Check_password_result;


	while(1)
	{
		key_pressed = KPD_GETKEY();
		switch(key_pressed)
		{
		case KPD_NOT_PRESSED: //no key pressed
			break;
		case 'C': //clear screen
			LCD_CLEAR_ALL_SCREEN();
			num_pressed=0;
			password=0;
			Check_password_result=0;
			count = 1;
			break;
		case '=':
			Check_password_result = Check_Password(password);
			if(Check_password_result == Correct_password) // if password was correct
			{
				Choose_Operation();
				num_pressed=0;
				password=0;
				Check_password_result=0;
				count = 1;
				LCD_CLEAR_ALL_SCREEN();
				break;
			}
			else if(Check_password_result == wrong_password) //if password was wrong
			{
				count++;
				if(count > input_attempts) // input attempts is more than allowed
				{
					SEND_A_STRING("Many wrong attempts was entered");
					_delay_ms(3000);
					num_pressed=0;
					password=0;
					Check_password_result=0;
					count = 1;
					LCD_CLEAR_ALL_SCREEN();
					break;
				}
				num_pressed=0;
				password=0;
				Check_password_result=0;
				LCD_CLEAR_ALL_SCREEN();
			}
			break;
		default: //store entered numbers as a password
			num_pressed= Get_Number(key_pressed);
			SEND_A_CHAR(key_pressed);
			password = password*10 + num_pressed;
			break;

		}
	}
	return 0;
}
