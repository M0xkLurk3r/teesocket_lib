/**
 *    Created by Anthony Lee, in project teesocket
 *    Copyright 2020 Anthony Lee
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
	
#include "teesocket.h"

#define __TEESOCKET_MODULE_NAME__	"libteesocket demo"
#define __TEESOCKET_MODULE_VER__	"0.0.1"
	
static uint8_t*	buf;
static size_t	buf_data_len;
static int		orig_argc;
static char**	orig_argv;

#define BUFSIZE 65536
#define WELCOME_MSG	"Welcome to libteesocket demo!\n"

const char* TEESOCKET_MODULE_NAME() { return __TEESOCKET_MODULE_NAME__; }
const char* TEESOCKET_MODULE_VER() { return __TEESOCKET_MODULE_VER__; }

size_t on_teesocket_back_read_ready(int clientid, const void* buffer, const size_t length) {
	size_t least_buf_size = BUFSIZE - buf_data_len;
	size_t actual_size_copied = length > least_buf_size ? least_buf_size : length;
	memcpy(buf, buffer, actual_size_copied);
	buf_data_len += actual_size_copied;
	return actual_size_copied;
}

size_t on_teesocket_peers_write_ready(int clientid, void* buffer, const size_t maxlen) {
	size_t actual_size_copied = buf_data_len > maxlen ? maxlen : buf_data_len;
	memcpy(buffer, buf, actual_size_copied);
	buf_data_len -= actual_size_copied;
	return actual_size_copied;
}

size_t on_teesocket_peers_read_ready(int clientid, const void* buffer, const size_t length) {
	return on_teesocket_back_read_ready(clientid, buffer, length); // Proceed same simple copy in this demo
}

size_t on_teesocket_new_peers(void* buffer, const size_t maxlen) {
	const char* welcome_msg = WELCOME_MSG;
	const int welcome_msg_len = strlen(welcome_msg);
	memcpy(buffer, welcome_msg, welcome_msg_len);
	return welcome_msg_len;
	return 0;
}

void on_teesocket_libinit(int host_argc, char* host_argv[]) {
	orig_argc = host_argc;
	orig_argv = host_argv;
	buf = (uint8_t *) malloc(sizeof(uint8_t) * BUFSIZE);
	buf_data_len = 0;
}

#ifdef __cplusplus
}	// extern "C"
#endif
