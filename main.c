#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum					//////////////
{							/////////////////////
	CMD_A = 0,							//////////////////////
	CMD_B,										//////
	CMD_C,										//////
	CMD_EXIT, // Optional command for terminating the program.			//////
	CMD_INVALID // There should always be a command invalid.			//////////
} cmd_t;											/////////// Edit these accordingly when adding commands.
											//////////
char *cmdList[] =									//////
{											//////
	"one",										//////
	"two",								//////////////////////
	"three",					/////////////////////
	"exit"					//////////////
};

void flushStdin(void)
{
	char c = '\0';
	while((c = getchar()) != EOF && c != '\n');
}

int commandMode(void)
{
	// Loop termination bool
	int loopBool = 1;

	// Get command list size for scalability
	int cmdListSize = sizeof(cmdList) / sizeof(cmdList[0]);

	// Initial message
	printf("\x1b[93mExplain the program functionality...\n\n\x1b[97m");

	while(loopBool)
	{
		// Command type
		cmd_t currentCmd = CMD_INVALID;

		// Command buffer
		char cmd[64];
		
		// Prompt user
		printf("[cmd-mode]>>> ");

		// Get user input
		scanf("%63s", &cmd);
		
		// Flush stdin
		flushStdin();

		// Remove case sensitivity
		for(size_t i = 0 ; i < strlen(cmd) ; i++)
		{
			// Buffer for the character
			char c = cmd[i];

			// Convert to lower and save
			cmd[i] = tolower(c);
		}
		
		// Search for command
		for(int i = 0 ; i < cmdListSize ; i++)
		{
			if(!strncmp(cmd, cmdList[i], 63))
			{
				currentCmd = i;
			}
		}

		switch(currentCmd)
		{
			case CMD_A:
				// Do something
				break;
			case CMD_B:
				// Do something
				break;
			case CMD_C:
				// Do something
				break;
			case CMD_EXIT:
				printf("\x1b[93mExiting...\n\x1b[97m");
				loopBool = 0;
				break;
			case CMD_INVALID:
				// Notify user of the invalid command entered
				printf("Invalid command entry. You entered \x1b[91m\"%s\"\x1b[97m, but the available commands are:\n", cmd);

				// Display available commands
				for(int i = 0 ; i < cmdListSize ; i++)
				{
					printf("\x1b[93m%d. %s\n\x1b[97m", i + 1, cmdList[i]);
				}

				break;
			default:
				// This should never be able to run, but if it somehow does an error will be displayed and commandMode will return 1. The entry point will also return 1.
				printf("\x1b[91mError: the command provided is not located in the command list.\x1b[97m\nIf this error is visible then something went wrong.\nCommand value: %d\n\nTerminating program...\n\n", currentCmd);
				return 1;
				break;
		}
	}

	return 0;
}

int main(void)
{
	return (commandMode());
}
