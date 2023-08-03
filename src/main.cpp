/*
 * MainUnit.c
 *
 * Copyright 2023 Megan Toner <megantoner@Megans-MacBook-Air-92.local>
 *
 *
 *
 *
 */
#include <stdio.h>

// To use time library of C
#include <time.h>
#include <Arduino.h>
#include "main.h"

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);

}

/*****
* State definitions, states are the routine the program jumps to, these are prefixed with an 'S' for easy identification
*****/
enum S_IDLE { S_USER = 1, S_OFF = 2, S_INTERRUPT = 3, S_UPLOAD = 4 , S_MAX = 5 };
enum S_WATERING { S_NEUTRAL = 6, S_ALKALINE = 7, S_ACIDIC = 8, S_COMPUTE = 9 };

/*****
* Event definitions, events trigger a transition and are prefixed with an 'E' for easy identification
*****/
enum E_IDLE { E_USER = 1, E_OFF = 2, E_INTERRUPT = 3, E_UPLOAD = 4, E_MAX = 5 };
enum E_ON { E_NEUTRAL = 6, E_ALKALINE = 7, E_ACIDIC = 8, E_WATER = 9 };

// Global variables
// holds current state on first run
int  Current_State = S_OFF;
// holds value that moisture should be set to
double  Moisture_Level = 0;
// stores the value of the latest moisture reading
double  Moisture_Data = 0;
// holds value that pH should be set to
double  pH_Level = 0;
// stores the value of the latest pH reading
double  pH_Data = 0;

External_WiFi_Network external_wifi_network;
ESP32_GPIO gpio;
MQTT mqtt_broker;

bool done_listening = false;

char* moisture_topic = "optimal_moisture_level";
char* pH_topic = "optimal_pH_level";
char* comeplete_topic = "stop";

/*****
* Function prototypes
*****/
void UponEnter( int State);
void ActionWhileInState( int State );
void UponExit( int State);
void StateMachine(int event);
int  ReadKeyInput(void);
void User();
void Off();
void Interrupt();
int UploadData();
int Water();
int UpdateSettings();
void TerminalOutput(int s, int state);

/*****
* Read Keys function definition containing the code to execute
*****/
int ReadKeyInput(void)
{
    char input;
    scanf("%c", &input);
    switch (input)
    {

        case '1':
            return E_USER;
            break;
        case '2':
            return E_OFF;
            break;
        case '3':
            return E_INTERRUPT;
            break;
        case '4':
            return E_UPLOAD;
            break;
        case '5':
            return E_MAX;
            break;
        case '6':
            return E_USER;
            break;
        case '7':
            return E_NEUTRAL;
            break;
        case '8':
            return E_ALKALINE;
            break;
        case '9':
            return E_ACIDIC;
            break;
        case '0':
            return E_WATER;
            break;

    }

    return E_MAX; // default to terminate should invalid case occur
}

/*****
* State Machine function definition containing the code to execute
*****/

void StateMachine(int event)
{
    int Next_State = Current_State;

    switch (Current_State)
    {
    case S_USER:
        switch (event)
        {
            // A transition to the next state will occur here
            case E_OFF:
            	Next_State = S_OFF;
                break;
            case E_USER:
            	Next_State = S_USER;
            	break;
            case E_INTERRUPT:
				Next_State = S_INTERRUPT;
				break;
			case E_UPLOAD:
				Next_State = S_UPLOAD;
				break;
    	    case E_NEUTRAL:
    	        Next_State = S_NEUTRAL;
    	        break;
    	    case E_ALKALINE:
    	        Next_State = S_ALKALINE;
    	        break;
    	    case E_ACIDIC:
    	        Next_State = S_ACIDIC;
    	        break;
			case E_WATER:
				Next_State = S_COMPUTE;
				break;
        }
        break;
    case S_OFF:
        switch (event)
        {
            // A transition to the next state will occur here
            case E_OFF:
            	Next_State = S_OFF;
                break;
            case E_USER:
            	Next_State = S_USER;
                break;
            case E_INTERRUPT:
            	Next_State = S_INTERRUPT;
                break;
            case E_UPLOAD:
            	Next_State = S_UPLOAD;
                break;
    	    case E_NEUTRAL:
    	        Next_State = S_NEUTRAL;
    	        break;
    	    case E_ALKALINE:
    	        Next_State = S_ALKALINE;
    	        break;
    	    case E_ACIDIC:
    	        Next_State = S_ACIDIC;
    	        break;
            case E_WATER:
            	Next_State = S_COMPUTE;
                break;
        }
        break;
    case S_INTERRUPT:
        switch (event)
        {
            // A transition to the next state will occur here
            case E_OFF:
            	Next_State = S_OFF;
                break;
            case E_USER:
            	Next_State = S_USER;
                break;
            case E_INTERRUPT:
            	Next_State = S_INTERRUPT;
                break;
            case E_UPLOAD:
            	Next_State = S_UPLOAD;
                break;
    	    case E_NEUTRAL:
    	        Next_State = S_NEUTRAL;
    	        break;
    	    case E_ALKALINE:
    	        Next_State = S_ALKALINE;
    	        break;
    	    case E_ACIDIC:
    	        Next_State = S_ACIDIC;
    	        break;
            case E_WATER:
                Next_State = S_COMPUTE;
                break;
        }
        break;
    case S_UPLOAD:
    	switch(event)
    	{
    	// A transition to the next state will occur here
    	    case E_OFF:
    	        Next_State = S_OFF;
    	        break;
    	    case E_NEUTRAL:
    	        Next_State = S_NEUTRAL;
    	        break;
    	    case E_ALKALINE:
    	        Next_State = S_ALKALINE;
    	        break;
    	    case E_ACIDIC:
    	        Next_State = S_ACIDIC;
    	        break;
    	    case E_WATER:
    	        Next_State = S_COMPUTE;
    	        break;
    	    case E_INTERRUPT:
    	        Next_State = S_INTERRUPT;
    	        break;
    	    case E_UPLOAD:
    	        Next_State = S_UPLOAD;
    	        break;
    	    case E_USER:
    	        Next_State = S_USER;
    	        break;
    				}
    				break;
     case S_NEUTRAL:
        switch(event)
		{
        // A transition to the next state will occur here
            case E_OFF:
            	Next_State = S_OFF;
                break;
            case E_NEUTRAL:
            	Next_State = S_NEUTRAL;
                break;
            case E_ALKALINE:
            	Next_State = S_ALKALINE;
                break;
            case E_ACIDIC:
            	Next_State = S_ACIDIC;
                break;
            case E_WATER:
                Next_State = S_COMPUTE;
                break;
           case E_INTERRUPT:
           		Next_State = S_INTERRUPT;
           		break;
           	case E_UPLOAD:
           		Next_State = S_UPLOAD;
           		break;
           	case E_USER:
           		Next_State = S_USER;
           		break;
			}
			break;
      case S_ALKALINE:
		switch(event)
		{
        // A transition to the next state will occur here
            case E_OFF:
            	Next_State = S_OFF;
                break;
            case E_NEUTRAL:
            	Next_State = S_NEUTRAL;
                break;
            case E_ALKALINE:
            	Next_State = S_ALKALINE;
                break;
            case E_ACIDIC:
            	Next_State = S_ACIDIC;
                break;
            case E_WATER:
                Next_State = S_COMPUTE;
                break;
            case E_INTERRUPT:
           		Next_State = S_INTERRUPT;
           		break;
           	case E_UPLOAD:
           		Next_State = S_UPLOAD;
           		break;
           	case E_USER:
           		Next_State = S_USER;
           		break;
			}
			break;
      case S_ACIDIC:
    	switch(event)
		{
      // A transition to the next state will occur here
          	case E_OFF:
       		  Next_State = S_OFF;
       		  break;
            case E_NEUTRAL:
              Next_State = S_NEUTRAL;
              break;
            case E_ALKALINE:
          	  Next_State = S_ALKALINE;
              break;
            case E_ACIDIC:
          	  Next_State = S_ACIDIC;
                break;
            case E_WATER:
              Next_State = S_COMPUTE;
              break;
           case E_INTERRUPT:
              Next_State = S_INTERRUPT;
         	  break;
           case E_UPLOAD:
         	  Next_State = S_UPLOAD;
         	  break;
           case E_USER:
         		Next_State = S_USER;
         		break;
		}
			break;
        // The program should never arrive here

		default:
        break;
    }

    if (Next_State != Current_State)
    {
		// Function call for Upon Exit function, it can be omitted but allows extra functionality
        UponExit(Current_State);
		// Function call for Upon Enter function, it can be omitted but allows extra functionality
        UponEnter(Next_State);
        Current_State = Next_State;
    }

    if ( event != E_MAX)
		ActionWhileInState( Current_State );
}

void UponExit(int State) {





}

void ActionWhileInState(int State) {


}
/*****
* Upon Enter function definition containing the code to execute
*****/
void UponEnter(int State)
{
    switch (State)
    {
    case S_USER:
        // Custom code here to execute when entering the new state
    	puts("This is the UponEnter function running for the S_OFF state");
		break;
    case S_OFF:
		// Custom code here to execute when entering the new state
    	puts("This is the UponEnter function running for the S_ON state");
		break;
    case S_INTERRUPT:
		// Custom code here to execute when entering the new state
    	puts("This is the UponEnter function running for the S_PROCESS state");
		break;
    }

    return;
}


void User() {
	// Sets Moisture_Level and pH_Level from user inputs
	input_settings();
}

void Off() {

	if ((Moisture_Level || pH_Level) == 0) {
		int t = 0;
		while (t == 0) {
			t = UpdateSettings();
		}
	}



}
void Interrupt()  {



}
int UploadData() {
	int val = 0; //flag for completed update




	return val;
}
int Water() {
	int val = 0; //flag for completed update
	gpio.output_pump_control();

	return val;
}
int UpdateSettings() {
	int valM = 0, valP = 0; //flag for completed updates
	int temp_Moisture = 0;
	char contM;
	char contP;
	double temp_pH = 0;
	while (valM == 0) {
		printf("Enter Moisture level 1-100: \n");
		scanf("%d", &temp_Moisture);
		printf("Set the Ideal Soil Moisture to %d (out of 100)?\nPress (Y) to confirm.\n", temp_Moisture);
		scanf("%c", &contM);
		if (contM == 'Y' || contM == 'y') {
			printf("Setting moisture level...\n");
			Moisture_Level = temp_Moisture;
			valM = 1;
		}
	}
	while (valP == 0) {
		printf("Enter pH level 0.00-14.00: \n");
		//scanf("%f\n", &temp_pH);
		printf("Set the Ideal Soil pH to %f (14.00)?\nPress (Y) to confirm.\n", temp_pH);
		scanf("%c", &contP);
		if (contP == 'Y' || contP == 'y') {
			printf("Setting pH level...\n");
			pH_Level = temp_pH;
			valP = 1;
		}
	}

	return (valM && valP);

}
void TerminalOutput(int s, int state) {

	//enum S_IDLE { S_USER = 1, S_OFF = 2, S_INTERRUPT = 3, S_UPLOAD = 4 , S_MAX = 5 };
	//enum S_WATERING { S_NEUTRAL = 6, S_ALKALINE = 7, S_ACIDIC = 8, S_COMPUTE = 9 };
	// messages to user for testing purposes
	switch (s) {
		case 2: // start up
			printf("Soil Control Unit Testing V 3.0 \n");
			printf("Welcome to the Main Control Panel. Current State: IDLE-%d. \n", state);
			printf("Possible States:\n");
			printf("\t IDLE- 1:USER 2:OFF 3:INTERRUPT 4:UPLOAD 5:TERMINATED\n");
			printf("WATERING- 6:NEUTRAL 7:ALKALINE 8:ACIDIC 9:COMPUTE\n");
			printf("Select an event to trigger to start: \n");
			printf("EVENTS WITHIN IDLE STATES THAT MAY BE TRIGGERED");
			printf("1: E_USER - simulates receiving data from the user\n");
			printf("2: E_OFF - simulates the system in its most idle state\n");
			printf("3: E_INTERRUPT - simulates requiring the needs for new readings or levels both from user and network\n");
			printf("4: E_UPLOAD - simulates sending current levels or latest readings to user\n");
			printf("5: E_MAX - terminate the machine \n");
			printf("6: E_WATER - simulate the need for transitioning to the S_WATER states\n");
			break;
		case 1: // idle states and events
			printf("Welcome to the Main Control Panel. Current State: IDLE-%d. \n", state);
			printf("Possible States:\n");
			printf("\t IDLE- 1:USER 2:OFF 3:INTERRUPT 4:UPLOAD 5:TERMINATED\n");
			printf("WATERING- 6:NEUTRAL 7:ALKALINE 8:ACIDIC 9:COMPUTE\n");
			printf("Select an event to trigger to start: \n");
			printf("EVENTS WITHIN IDLE STATES THAT MAY BE TRIGGERED");
			printf("1: E_USER - simulates receiving data from the user\n");
			printf("2: E_OFF - simulates the system in its most idle state\n");
			printf("3: E_INTERRUPT - simulates requiring the needs for new readings or levels both from user and network\n");
			printf("4: E_UPLOAD - simulates sending current levels or latest readings to user\n");
			printf("5: E_MAX - terminate the machine \n");
			printf("6: E_WATER - simulate the need for transitioning to the S_WATER states\n");
			break;

	}

	return;
}
/*****
* Main function starts here
*****/
int main_program()
{	
	TerminalOutput(Current_State, Current_State);


    while ( Current_State != S_MAX )
    {
		// Function call for the state machine, which then calls the read keys function and waits for the value returned
        StateMachine( ReadKeyInput() );
    }

    return 0;
}

void set_up_for_main() {
	external_wifi_network = External_WiFi_Network("Rach (2)", "ahrachel");
	input_settings();
}

/*void setup() {
	set_up_for_main();
	//main_program();
}

void loop() {
	//read_sensors();
	//delay(10);
}*/