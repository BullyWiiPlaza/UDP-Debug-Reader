/****************************************************************************
 * Copyright (C) 2010-2012
 * by Dimok
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you
 * must not claim that you wrote the original software. If you use
 * this software in a product, an acknowledgment in the product
 * documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and
 * must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 ***************************************************************************/

#include <sys/types.h>
#include <cstring>

#if defined(__linux__) || defined(__APPLE__)

#include <unistd.h>

#else

#pragma comment(lib, "ws2_32.lib")

#endif

#include "network.hpp"

static int sock_id = -1;
static struct sockaddr_in servaddr;

int Bind() {
	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(LISTEN_PORT);
	servaddr.sin_family = AF_INET;

	if (bind(sock_id, reinterpret_cast<struct sockaddr *>(&servaddr), sizeof(servaddr)) < 0) {
#ifdef _WIN32
		closesocket(sock_id);
#else
		close(sock_id);
#endif
		return -1;
	}

	return 0;
}

void CloseSocket() {
	if (sock_id < 0)
		return;

#ifdef _WIN32
	closesocket(sock_id);
#else
	close(sock_id);
#endif

	sock_id = -1;
}

int NetInit() {
	if (sock_id >= 0)
		return sock_id;

#ifdef WIN32
	WSADATA wsaData;

	// Initialize Winsock
	if (WSAStartup(MAKEWORD(2,2), &wsaData) == SOCKET_ERROR)
		return -1;
#endif
	//Get a socket
	if ((sock_id = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP)) == -1)
		return -1;

#ifdef WIN32
	u_long mode = 1;
	ioctlsocket(sock_id, FIONBIO, &mode);
#else
	int flags = fcntl(sock_id, F_GETFL, 0);
	fcntl(sock_id, F_SETFL, flags | O_NONBLOCK);
#endif

	return sock_id;
}

int NetRead(void *buffer, unsigned int buf_len) {
	if (sock_id < 0)
		return sock_id;

	fd_set fdsRead;
	FD_ZERO(&fdsRead);
	FD_SET(sock_id, &fdsRead);

	struct timeval tv{};
	tv.tv_sec = 0;
	tv.tv_usec = 10000;

	if (select(sock_id + 1, &fdsRead, nullptr, nullptr, &tv) != 1) {
		return 0;
	}

	int len = sizeof(servaddr);

#ifdef _WIN32
	return recvfrom(sock_id, static_cast<char*>(buffer), buf_len, 0, reinterpret_cast<struct sockaddr*>(&servaddr), reinterpret_cast<int *>(&len));
#else
	return recvfrom(sock_id, buffer, buf_len, 0, (struct sockaddr *) &servaddr, reinterpret_cast<socklen_t *>(&len));
#endif
}