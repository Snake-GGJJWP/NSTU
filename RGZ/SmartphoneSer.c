#include "SmartphoneSer.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define BUF 16
#define SM_BYTES (MODEL_MAX_LEN + sizeof(COLOR) + sizeof(short) + sizeof(double) + sizeof(double)) // number of bytes used by Smartphone's fields

// Print error for a file
static void printerr(const char* file) {
	switch (errno) {
	case EACCES:
		printf("[WARNING]: Access denied! Path: %s\n", file);
		break;
	case EEXIST:
		printf("[WARNING]: File already exists! Path: %s\n", file);
		break;
	case EISDIR:
		printf("[WARNING]: Cannot read/write a directory! Path: %s\n", file);
		break;
	case ENOENT:
		printf("[WARNING]: No such file! Path: %s\n", file);
		break;
	case ENOSPC:
		printf("[WARNING]: No space left! Path: %s\n", file);
		break;
	case EBADF:
		printf("[WARNING]: Incorrect file descriptor! Path: %s\n", file);
		break;
	case EINVAL:
		printf("[WARNING]: Wrong mode! Path: %s\n", file);
		break;
	default:
		printf("[WARNING]: Some error occured during file processing! Path: %s\n", file);
	}
}
// Dump structure into a file descriptor. Allows to avoid constantly closing and reopening a file
static char smdump_fd(int fd, const char* path, const Smartphone* sm) {
	// Since we have a pointer field in WashingMachine, we gotta write the fields separately
	if (write(fd, sm->model, MODEL_MAX_LEN) == -1 ||
		write(fd, &(sm->color), sizeof(sm->color)) == -1 ||
		write(fd, &(sm->year), sizeof(sm->year)) == -1 ||
		write(fd, &(sm->size), sizeof(sm->size)) == -1 ||
		write(fd, &(sm->priceUsd), sizeof(sm->priceUsd)) == -1)
	{
		printerr(path);
		return 0;
	}

	return 1;
}

// Load structure into a file descriptor. Allows to avoid constantly closing and reopening a file
static Smartphone* smload_fd(int fd, const char* path) {
	Smartphone* sm = (Smartphone*)malloc(sizeof(Smartphone));
	char* model = (char*)malloc(MODEL_MAX_LEN);
	COLOR color = 0;
	short year = 0;
	double size = 0;
	double priceUsd = 0;

	if (read(fd, model, MODEL_MAX_LEN) == -1 ||
		read(fd, &color, sizeof(COLOR)) == -1 ||
		read(fd, &year, sizeof(short)) == -1 ||
		read(fd, &size, sizeof(double)) == -1 ||
		read(fd, &priceUsd, sizeof(double)) == -1)
	{
		printerr(path);
		return NULL;
	}

	smInit(sm, model, color, year, size, priceUsd);

	return sm;
}

// Dump Smartphone structure into the file. Return 0 on failure, 1 on success
char smdump(const char* path, const Smartphone* sm) {
	int fd = open(path, O_WRONLY | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
	if (fd == -1) {
		printerr(path);
		return 0;
	}

	char result = smdump_fd(fd, path, sm);

	char cl = close(fd);
	if (cl == -1) {
		printerr(path);
		return 0;
	}

	return result;
}
// Load  Smartphone structure from the file. Return NULL on failure, loaded structure on success
Smartphone* smload(const char* path) {
	int fd = open(path, O_RDONLY | O_BINARY, S_IWRITE);
	if (fd == -1) {
		printerr(path);
		return NULL;
	}

	Smartphone* sm = smload_fd(fd, path);

	char cl = close(fd);
	if (cl == -1) {
		printerr(path);
		return NULL;
	}

	return sm;
}

// Dump list of Smartphone structures into the file. Return 0 on failure, 1 on success
char smlistdump(const char* path, const SMList* smlist) {
	int fd = open(path, O_WRONLY | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
	if (fd == -1) {
		printerr(path);
		return 0;
	}

	for (SMList* node = smlist; node != NULL; node = node->next) {
		Smartphone val = node->val;
		if (smdump_fd(fd, path, &val) == 0) {
			return 0;
		}
	}

	char* fullstop = calloc(SM_BYTES, 0);
	write(fd, fullstop, SM_BYTES); // put a full stop (EOF)
	free(fullstop);

	char cl = close(fd);
	if (cl == -1) {
		printerr(path);
		return 0;
	}

	return 1;
}
// Load list of Smartphone structures into the file. Return NULL on failure, loaded list on success
SMList* smlistload(const char* path) {
	SMList* head = (SMList*)malloc(sizeof(SMList));
	head->next = NULL;

	char* fullstop = calloc(SM_BYTES, 0);

	int fd = open(path, O_RDONLY | O_BINARY, S_IWRITE);
	if (fd == -1) {
		printerr(path);
		return NULL;
	}

	SMList* curnode = head;
	while (1) {
		SMList* node = (SMList*)malloc(sizeof(SMList));

		// Check for EOF
		void* buf = malloc(SM_BYTES);
		read(fd, buf, SM_BYTES);
		if (memcmp(fullstop, buf, SM_BYTES) == 0) {
			free(node);
			break;
		}
		else {
			lseek(fd, -(char)(SM_BYTES), SEEK_CUR); // move back if EOF is not reached yet, to read it like a man
		}

		Smartphone* val = smload_fd(fd, path);
		if (val == NULL) {
			free(node);
			return NULL;
		}

		node->val = *val;
		node->next = NULL;
		free(val);
		curnode->next = node;
		curnode = curnode->next;
	}

	char cl = close(fd);
	if (cl == -1) {
		printerr(path);
		return NULL;
	}

	return head->next;
}