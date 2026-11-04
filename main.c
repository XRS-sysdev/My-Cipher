#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char buffer[256]; // Declare our program's input buffer now
	char *endptr; // Same goes for our endptr for buffer conversion
	while (1) {
		printf("Choose Action: \n1. Encrypt/Decrypt\n2. Exit\n> ");
		fgets(buffer, sizeof(buffer), stdin);
		int num = strtol(buffer, &endptr, 10);
		if (endptr == buffer) { // Check if the input was a valid int
			printf("Error: No valid digits found.\n");
			continue;
		}
		// If we got here, we know we have a valid int input, now just cmp
		if (num == 1) {
			// Encrypt/Decrypt
		} else if (num == 2) {
			// Exit
			printf("Goodbye!\n");
			break;
		} else {
			// Invalid choice
			printf("Error: Invalid choice\n");
			continue;
		}
	}
	return 0;
}