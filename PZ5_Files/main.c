#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define N 100

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
	fd = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IWRITE);
	if (fd == -1) {
		printerr(path);
		return 0;
	}

	char ch = 0x0F; // 1 byte
	char str[N] = { 0x0F, 0x0F, 0x0F, 0x0F, '\0' }; // 5 x 1 bytes
	short sht = 0x0FFF; // 2 bytes
	int i = 0x0FFFFFFF; // 4 bytes
	int iarr[4] = { 0x0BBBBBBB, 0x0BBBBBBB, 0x0BBBBBBB, 0x0BBBBBBB }; // 4 x 4 bytes
	float fl = 0xFFFFFFFF; // 4 bytes
	double db = 0xFFFFFFFFFFFFFFFF; // 8 bytes

	write(fd, ch, sizeof(char));
//	write(fd, str, sizeof(char)*strlen(str));
	write(fd, sht, sizeof(short));
	write(fd, i, sizeof(int));
//	write(fd, iarr, sizeof(int)*4);
	write(fd, fl, sizeof(float));
	write(fd, ch, sizeof(db));

	close(fd);
	


	return 0;
}