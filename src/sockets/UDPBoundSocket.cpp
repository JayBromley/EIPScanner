//
// Created by Aleksey Timin on 11/21/19.
//
#include <arpa/inet.h>
#include <stdexcept>
#include <system_error>

//#include <sys/socket.h>
//#include <netinet/in.h>

#include "UDPBoundSocket.h"
#include "Platform.h"

namespace eipScanner {
namespace sockets {

	UDPBoundSocket::UDPBoundSocket(std::string host, int port)
		: UDPBoundSocket(EndPoint(host, port), "") {

	}

	UDPBoundSocket::UDPBoundSocket(EndPoint endPoint)
		: UDPBoundSocket(endPoint, "") {

	}

	UDPBoundSocket::UDPBoundSocket(EndPoint endPoint, const std::string &client)
		: UDPSocket(std::move(endPoint)) {
		int on = 1;
		if (setsockopt(_sockedFd, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on)) < 0) {
			throw std::system_error(BaseSocket::getLastError(), BaseSocket::getErrorCategory());
		}

		auto addr = _remoteEndPoint.getAddr();
		if (client.empty()) {
			addr.sin_addr.s_addr = INADDR_ANY;	
		} else {
			int result = inet_pton(AF_INET, client.c_str(), &(addr.sin_addr.s_addr));
			if (result == 0) {
				throw std::runtime_error("invalid client IP address");
			} else if (result == -1) {
				throw std::runtime_error("invalid inet family");	
			}
		}
		
		if (bind(_sockedFd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
			throw std::system_error(BaseSocket::getLastError(), BaseSocket::getErrorCategory());
		}
	}

	sockets::UDPBoundSocket::~UDPBoundSocket() = default;
}
}
