#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "serialization.h"

#define N 100
#define IARRLEN 4

// Print error for a file
void printerr(const char* file) {
	switch (errno) {
	case EACCES:
		printf("[WARNING]: Access denied! Path: %s", file);
		break;
	case EEXIST:
		printf("[WARNING]: File already exists! Path: %s", file);
		break;
	case EISDIR:
		printf("[WARNING]: Cannot read/write a directory! Path: %s", file);
		break;
	case ENOENT:
		printf("[WARNING]: No such file! Path: %s", file);
		break;
	case ENOSPC:
		printf("[WARNING]: No space left! Path: %s", file);
		break;
	case EBADF:
		printf("[WARNING]: Incorrect file descriptor! Path: %s", file);
		break;
	case EINVAL:
		printf("[WARNING]: Wrong mode! Path: %s", file);
		break;
	default:
		printf("[WARNING]: Some error occured during file processing! Path: %s", file);
	}
}

int main() {
	const char path[N] = "test.txt";
	int fd;
	
	// Part 1
	// ### open, write, creat ###

	// Testing creat
	/*fd = creat(path, S_IWRITE|S_IREAD); // It won't trigger EEXCL error, beacause doesn't have O_EXCL flag
	if (fd == -1) {
		printerr(path);
		return 0;
	}*/


	fd = open(path, O_RDWR | O_TRUNC | O_CREAT | O_EXCL, S_IWRITE);
	if (fd == -1) {
		// printerr(path);
		fd = open(path, O_RDWR | O_APPEND, S_IWRITE);
		// return 0;
	}

	if (write(fd, "some", 4) == -1) {
		printerr(path);
		return 0;
	}

	if (close(fd) == -1) {
		printerr(path);
		return 0;
	}

	// Part 2
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, S_IWRITE);
	if (fd == -1) {
		printerr(path);
		return 0;
	}

	char ch = 0x01; // 1 byte
	char str[N] = { 0x02, 0x03, 0x04, 0x05, '\0' }; // 5 x 1 bytes
	short sht = 0x0607; // 2 bytes
	int i = 0x08090A0B; // 4 bytes
	int iarr[IARRLEN] = { 0x0C0D0E0F, 0x10111213, 0x14151617, 0x18191A1B }; // 4 x 4 bytes

	// float and doubles can't be written with such hexademical representation
	uint32_t buf4 = 0xBC1D1E1F;
	float fl;
	memcpy(&fl, &buf4, sizeof(float));

	uint64_t buf8 = 0x0102030405060708;
	double db;
	memcpy(&db, &buf8, sizeof(double));

	int len = strlen(str) + 1; // char string length

	write(fd, &ch, sizeof(char));
    write(fd, &str, sizeof(char)*len); // don't forget '\0'
	write(fd, &sht, sizeof(short));
	write(fd, &i, sizeof(int));
    write(fd, &iarr, sizeof(int)*IARRLEN);
	write(fd, &fl, sizeof(float));
	write(fd, &db, sizeof(double));

	close(fd);

	// ### PART 3 ###
	fd = open(path, O_RDONLY | O_BINARY, S_IWRITE);
	if (fd == -1) {
		printerr(path);
		return 0;
	}

	void* buf = malloc(16); // allocate 16 bytes

	read(fd, buf, sizeof(char));
	printf("Char: %d, %X\n", *(char*)buf, *(char*)buf);

	read(fd, buf, sizeof(char)*len);
	char* s = (char*)malloc(len);
	memcpy(s, buf, len);
	printf("Str: ");
	for (int i = 0; i < len; i++) {
		printf("%d, %X; ", *(s+i), *(s+i));
	}
	printf("\n");
	free(s);

	read(fd, buf, sizeof(short));
	printf("Short: %d, %X\n", *(short*)buf, *(short*)buf);
	 
	read(fd, buf, sizeof(int));
	printf("Int: %d, %X\n", *(int*)buf, *(int*)buf);

	read(fd, buf, IARRLEN * sizeof(int));
	int* riarr = (int*)malloc(IARRLEN*sizeof(int));
	memcpy(riarr, buf, IARRLEN * sizeof(int));
	printf("Int array: ");
	for (int i = 0; i < IARRLEN; i++) {
		printf("%d, %X; ", *(riarr + i), *(riarr + i));
	}
	printf("\n");
	free(riarr);

	read(fd, buf, sizeof(float));
	printf("Float: %f, %X\n", *(float*)buf, *(int*)buf);

	read(fd, buf, sizeof(double));
	printf("Double: %lf, %llX\n", *(double*)buf, *(long long int*)buf);

	close(fd);
	free(buf);
	printf("\n");

	// Part 4
	buf = malloc(16);

	fd = open(path, O_RDWR | O_BINARY, S_IWRITE);
	if (fd == -1) {
		printerr(path);
		return 0;
	}

	lseek(fd, sizeof(char), SEEK_SET); // skip char variable
	read(fd, buf, sizeof(char) * len);
	s = malloc(len);
	memcpy(s, buf, len);
	printf("Str: ");
	for (int i = 0; i < len; i++) {
		printf("%d, %X; ", *(s + i), *(s + i));
	}
	printf("\n");
	free(s);

	lseek(fd, sizeof(short), SEEK_CUR); // skip short
	read(fd, buf, sizeof(int));
	printf("Int: %d, %X\n", *(int*)buf, *(int*)buf);

	lseek(fd, IARRLEN*sizeof(int) + sizeof(float), SEEK_CUR); // skip int array and float
	read(fd, buf, sizeof(double));
	printf("Double: %lf, %llX\n", *(double*)buf, *(long long int*)buf);

	// change values
	lseek(fd, sizeof(char) * 3, SEEK_SET); // skip char and 2 elements of char array
	ch = 0xFF;
	write(fd, &ch, sizeof(ch));

	lseek(fd, -(char)(sizeof(double) + sizeof(float)), SEEK_END); // skip double value from the end
	buf4 = 0xBFFFFFFF;
	memcpy(&fl, &buf4, sizeof(float));
	write(fd, &fl, sizeof(float));

	free(buf);

	// ### PART 5 ###
	// Single dumping and loading
	WashingMachine* wm = newWashingMachine();
	wmInit(wm, "Samsung", 20, 2000);
	
	if (wmdump("wm.bin", wm) == 0) {
		printf("Error occured during dumping");
	}
	else {
		printf("Dumped: %s\n", wmToString(wm));
	}

	wm = wmload("wm.bin");
	if (wm == NULL) {
		printf("Error occured during loading");
	}
	else {
		printf("Loaded: %s\n", wmToString(wm));
	}

	// List dumping and loading
	int size = 17;
	WashingMachine** wmarr = (WashingMachine**)malloc(sizeof(WashingMachine*) * size); // array of 16 elements
	for (int i = 0; i < size; i++) {
		wmarr[i] = newWashingMachine(); 
		wmSetPrice(wmarr[i], i*i);
	}
	wmarrdump("wmarr.bin", wmarr, size);

	size = 0;
	wmarr = wmarrload("wmarr.bin", &size);
	printf("Loaded array: \n");
	for (int i = 0; i < size; i++) {
		printf("%s\n", wmToString(wmarr[i]));
	}
	
	// Queue dumping and loading
	WMQueue* wmqueue = NULL;
	for (int i = 0; i < size; i++)
	{
		wmqueueAppendRight(&wmqueue, *wmarr[i]);
	}

	wmqueuedump("wmqueue.bin", wmqueue);

	wmqueue = wmqueueload("wmqueue.bin");
	printf("Loaded queue:\n");
	while (wmqueue != NULL) {
		WashingMachine wm = wmqueuePopLeft(&wmqueue);
		printf("%s\n", wmToString(&wm));
	}



	return 0;
}