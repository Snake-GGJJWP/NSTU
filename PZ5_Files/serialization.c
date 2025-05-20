#include "serialization.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define BUF 16
#define WM_BYTES (MODEL_MAX_LEN + sizeof(double) + sizeof(double))

// Print error for a file
static void printerr(const char* file) {
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

static char wmdump_fd(int fd, const char* path, const WashingMachine* wm) {
	// Since we have a pointer field in WashingMachine, we gotta write the fields separately
	if (write(fd, wm->model, MODEL_MAX_LEN) == -1 ||
		write(fd, &(wm->waterConsume_l), sizeof(wm->waterConsume_l)) == -1 ||
		write(fd, &(wm->priceUsd), sizeof(wm->priceUsd)) == -1)
	{
		printerr(path);
		return 0;
	}

	return 1;
}

static WashingMachine* wmload_fd(int fd, const char* path) {
	WashingMachine* wm = newWashingMachine();
	char* model = (char*)malloc(MODEL_MAX_LEN);
	double waterConsume_l = 0;
	double priceUsd = 0;

	if (read(fd, model, MODEL_MAX_LEN) == -1 ||
		read(fd, &waterConsume_l, sizeof(double)) == -1 ||
		read(fd, &priceUsd, sizeof(double)) == -1)
	{
		printerr(path);
		return NULL;
	}

	if (wmSetModel(wm, model) == 0 ||
		wmSetWaterConsumption(wm, waterConsume_l) == 0 ||
		wmSetPrice(wm, priceUsd) == 0)
	{
		printf("[WARNING]: the file %s may be corrupted", path);
		return NULL;
	}

	return wm;
}

// Dump WashingMachine structure into the file. Return 0 on failure, 1 on success
char wmdump(const char* path, const WashingMachine* wm) {
	int fd = open(path, O_WRONLY | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
	if (fd == -1) {
		printerr(path);
		return 0;
	}

	char result = wmdump_fd(fd, path, wm);

	char cl = close(fd);
	if (cl == -1) {
		printerr(path);
		return 0;
	}

	return result;
}
WashingMachine* wmload(const char* path) {
	int fd = open(path, O_RDONLY | O_BINARY, S_IWRITE);
	if (fd == -1) {
		printerr(path);
		return NULL;
	}

	WashingMachine* wm = wmload_fd(fd, path);

	char cl = close(fd);
	if (cl == -1) {
		printerr(path);
		return NULL;
	}

	return wm;
}

char wmarrdump(const char* path, const WashingMachine** wm, int size) {
	int fd = open(path, O_WRONLY | O_BINARY | O_CREAT | O_TRUNC, S_IWRITE);
	if (fd == -1) {
		printerr(path);
		return 0;
	}

	for (int i = 0; i < size; i++) {
		if (wmdump_fd(fd, path, wm[i]) == 0) {
			return 0;
		}
	}

	char* fullstop = calloc(WM_BYTES, 0);
	write(fd, fullstop, WM_BYTES); // put a full stop (EOF)
	free(fullstop);

	char cl = close(fd);
	if (cl == -1) {
		printerr(path);
		return 0;
	}

	return 1;
}
WashingMachine** wmarrload(const char* path, int* size) {
	WashingMachine** wmarr = (WashingMachine**)malloc(sizeof(WashingMachine*) * BUF);
	int i = 0;
	int n = 1; // number of reallocations

	char* fullstop = calloc(WM_BYTES, 0);

	int fd = open(path, O_RDONLY | O_BINARY, S_IWRITE);
	if (fd == -1) {
		printerr(path);
		return NULL;
	}

	while (1) {

		// Check for EOF
		void* buf = malloc(WM_BYTES);
		read(fd, buf, WM_BYTES);
		if (memcmp(fullstop, buf, WM_BYTES) == 0) {
			*size = i;
			return wmarr;
		}
		else {
			lseek(fd, -(char)(WM_BYTES), SEEK_CUR); // move back if EOF is not reached yet, to read it like a man
		}

		wmarr[i] = wmload_fd(fd, path);
		if (wmarr[i] == NULL) {
			return NULL;
		}

		i++;

		if (i >= BUF) {
			n++;
			wmarr = (WashingMachine**)realloc(wmarr, sizeof(WashingMachine*) * BUF * n);
		}
	}

	char cl = close(fd);
	if (cl == -1) {
		printerr(path);
		return NULL;
	}

	return wmarr;
}

char wmqueuedump(const char* path, WMQueue* wmqueue) {
	WashingMachine** wmarr = (WashingMachine**)malloc(sizeof(WashingMachine*) * BUF);
	int i = 0;
	int n = 1;
	WMQueue* q = wmqueue;

	q->prev->next = NULL; // Remove cycle
	while (q != NULL) {
		wmarr[i] = &(q->val);
		q = q->next;
		
		i++;
		if (i >= BUF) {
			n++;
			wmarr = (WashingMachine**)realloc(wmarr, sizeof(WashingMachine*) * BUF * n);
		}
	}
	wmqueue->prev->next = wmqueue; // Restore cycle

	wmarrdump(path, wmarr, i);
	free(wmarr);

	return 0;
}

WMQueue* wmqueueload(const char* path) {
	int size = 0;
	WashingMachine** wmarr = wmarrload(path, &size);
	WMQueue* wmqueue = NULL;

	for (int i = 0; i < size; i++)
	{
		wmqueueAppendRight(&wmqueue, *wmarr[i]);
	}

	return wmqueue;
}