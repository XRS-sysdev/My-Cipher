#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char buffer[256]; 
	char *endptr; 
	while (1) {
		printf("Choose Action: \n1. Encrypt\n2. Decrypt\n3. Exit\n> ");
		if (!fgets(buffer, sizeof(buffer), stdin)) break;
		int num = strtol(buffer, &endptr, 10);
		if (endptr == buffer) { 
			printf("Error: No valid digits found.\n");
			continue;
		}
		if (num == 1) {
			printf("File name (Same directory as the file):\n> ");
			fgets(buffer, sizeof(buffer), stdin);
			buffer[strcspn(buffer, "\n")] = '\0';
			FILE *file = fopen(buffer, "rb+");
			if (file == NULL) {
				printf("Error: Failed to find file.\n");
				continue;
			}
			fseek(file, 0, SEEK_END);
			long fileLen = ftell(file);
			rewind(file);
			char *fileContent = malloc(fileLen);
			fread(fileContent, 1, fileLen, file);
			char *key = malloc(fileLen);
			for (int i = 0; i < fileLen; i++) {
				key[i] = (char)(arc4random() % 256);
			}
			for (int i = 0; i < fileLen; i++) {
				fileContent[i] = fileContent[i] ^ key[i];
			}
			rewind(file);
			fwrite(fileContent, 1, fileLen, file);
			fclose(file);
			FILE *keyFile = fopen("key.txt", "wb");
			if (keyFile != NULL) {
				fwrite(key, 1, fileLen, keyFile);
				fclose(keyFile);
				printf("File encrypted successfully! Key saved to 'key.txt'.\n");
			} else {
				printf("Error saving key file.\n");
			}
			free(fileContent);
			free(key);
		} else if (num == 2) {
			printf("File name (Same directory as the file):\n> ");
			fgets(buffer, sizeof(buffer), stdin);
			buffer[strcspn(buffer, "\n")] = '\0';
			FILE *file = fopen(buffer, "rb+");
			if (file == NULL) {
				printf("Error: Failed to find file.\n");
				continue;
			}
			fseek(file, 0, SEEK_END);
			long fileLen = ftell(file);
			rewind(file);
			char *fileContent = malloc(fileLen);
			fread(fileContent, 1, fileLen, file);
			FILE *keyFile = fopen("key.txt", "rb");
			if (keyFile == NULL) {
				printf("Error: 'key.txt' not found.\n");
				free(fileContent);
				fclose(file);
				continue;
			}
			char *key = malloc(fileLen);
			size_t keyLen = fread(key, 1, fileLen, keyFile);
			fclose(keyFile);
			if ((long)keyLen < fileLen) {
				printf("Error: Key file is shorter than the target file.\n");
				free(fileContent);
				free(key);
				fclose(file);
				continue;
			}
			for (int i = 0; i < fileLen; i++) {
				fileContent[i] = fileContent[i] ^ key[i];
			}
			rewind(file);
			fwrite(fileContent, 1, fileLen, file);
			fclose(file);
			printf("File decrypted successfully!\n");
			free(fileContent);
			free(key);
		} else if (num == 3) {
			printf("Goodbye!\n");
			break;
		} else {
			printf("Error: Invalid choice\n");
			continue;
		}
	}
	return 0;
}