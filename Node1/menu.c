#include "OLED.h"
#include "ADC.h"
#include "joystick.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

int selectedOption = 0;


const char* menuOptions[] = {
	"Start game",
	"Joystick pos"
};

const char* menuGame[] = {
	"Stop game"
};

void displayMainMenu(int selectedOption) {
	
	clear_oled();

	set_position(0, 0);
	print_string("Menu:");

	for (int i = 0; i < sizeof(menuOptions) / sizeof(menuOptions[0]); i++) {
		set_position(i + 1, 0); 

		if (i == selectedOption) 
		{
			print_string(">");
		} 
		else 
		{
			print_string(" ");
		}

		print_string(menuOptions[i]);
	}
	
}

void displayGameMenu(int selectedOption)
{
		clear_oled();

		for (int i = 0; i < sizeof(menuGame) / sizeof(menuGame[0]); i++) {
			set_position(i + 1, 0); 
			if (i == selectedOption)
			{
				print_string(">");
			}
			else
			{
				print_string(" ");
			}

			print_string(menuGame[i]);
		}
}


int selection_menu(int button, int select_menu) {
	
	int select;
	int direction;
	
	// Get joystick value 
	joystick_position_analog value = get_joystick_position();
	if(button)
	{
		direction = joystick_get_direction();
	}
	

	switch (direction) 
	{
		case 2: // Haut
		if (selectedOption > 0) 
		{
			selectedOption--;
		}
		break;
		
		case 3: // Bas
		if (selectedOption < sizeof(menuOptions) / sizeof(menuOptions[0]) - 1)
	    {
			selectedOption++;
		}
		break;
	}
	
	_delay_ms(200);
	 // Rafraîchir l'affichage après la sélection
	
	switch (select_menu)
	{
		case 0 :
			displayMainMenu(selectedOption);
			break;
		
		case 1 :
			displayGameMenu(selectedOption);
			break;
	}
	

	
 	if (selectedOption == 0 ) // if start game is selected 
 	{ 
		 if(button == 0) // SW0 button 
		 {
 			select = 0;
 			return select;
		 }
		 else
		 {
			 select = 3;
			 return select;
		 }
 	}
 	else if(selectedOption == 1) // if joystick pos is selected 
 	{
		 if(button == 0) // SW0 button
		 {
 			select = 1;
 			return select;
		 }
		 else
		 {
			 select = 3;
			 return select;
		 }
 	}
	else 
	{
		
	}
	 
}





	