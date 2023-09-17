/*
 * Money_Safe.c
 *
 *  Created on: Aug 23, 2023
 *      Author: user
 */

#include "../money_con/Money_Safe.h"

u32 balance = 5000;
u32* balance_ptr = &balance;



state Check_Password(u32 password)
{
	if(password == Saved_password)
	{
		return Correct_password; //correct password
	}
	else
	{
		LCD_CLEAR_ALL_SCREEN();
		SEND_A_STRING("Wrong password");
		LCD_CLEAR_ALL_SCREEN();
		return wrong_password;
	}
}

void Show_Balance(void)
{
	SEND_A_STRING("Your Balance");
	LCD_GOTO_XY(1, 0);
	LCD_DISPLAY_NUM(balance);

}

void Inset_Money(u32 money)
{
	*balance_ptr = *balance_ptr + money;
	LCD_GOTO_XY(0, 0);
	SEND_A_STRING("new balance: ");
	LCD_GOTO_XY(1, 0);
	LCD_DISPLAY_NUM(*balance_ptr);
}

void Withdraw(u32 money)
{
	if(money > *balance_ptr)
	{
		SEND_A_STRING("not enough balance");
	}
	else
	{
		*balance_ptr = *balance_ptr - money;
		LCD_GOTO_XY(0, 0);
		SEND_A_STRING("new balance: ");
		LCD_GOTO_XY(1, 0);
		LCD_DISPLAY_NUM(*balance_ptr);
	}
}
