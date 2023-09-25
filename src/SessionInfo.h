//
// Created by Aleksey Timin on 11/16/19.
//

#ifndef _SRC_SESSIONINFO_H_
#define _SRC_SESSIONINFO_H_

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include "SessionInfoIf.h"
#include "sockets/TCPSocket.h"

namespace eipScanner {
	/**
	* @class SessionInfo
	*
	* @brief Implementation of EIP session
	*/
	class SessionInfo : public SessionInfoIf {
	public:
		using SPtr = std::shared_ptr<SessionInfo>;

		/**
		 * @brief Establishes an EIP session with an EIP adapter
		 * This constructor should be used when a socket needs to be bound to a 
		 * specific IP address to allow multiple device clients on the local client.
		 * @param host The IP address of the adapter
		 * @param port The port of the adapter
		 * @param timeout timout to connect and receive the response
		 * @param client The IP address of the local client
		 * @throw std::runtime_error
		 * @throw std::system_error
		 */
		SessionInfo(const std::string &host, int port, const std::chrono::milliseconds& timeout, const std::string &client);

		/**
		 * @brief Establishes an EIP session with an EIP adapter
		 * @param host The IP address of the adapter
		 * @param port The port of the adapter
		 * @param timeout timout to connect and receive the response
		 * @throw std::runtime_error
		 * @throw std::system_error
		 */
		SessionInfo(const std::string &host, int port, const std::chrono::milliseconds& timeout);

		/**
		 * @brief Establishes an EIP session with an EIP adapter
		 * @param host The IP address of the adapter
		 * @param port The port of the adapter
		 * @throw std::runtime_error
		 * @throw std::system_error
		 */
		SessionInfo(const std::string &host, int port);

		/**
		 * @brief Default destructor
		 */
		~SessionInfo();

		/**
		 * @sa SessionInfo::sendAndReceive
		 * @param packet
		 * @return
		 */
		eip::EncapsPacket sendAndReceive(const eip::EncapsPacket& packet) const override;

		/**
		 * @sa SessionInfo::getSessionHandle
		 * @return
		 */
		cip::CipUdint getSessionHandle() const override;

		/**
		 * @sa SessionInfo::getRemoteEndPoint
		 * @return
		 */
		sockets::EndPoint getRemoteEndPoint() const override;

		/**
		 * @sa SessionInfo::getClient
		 * @return
		 */
		std::string getClient() const override;

	private:
		sockets::TCPSocket _socket;
		cip::CipUdint _sessionHandle;
		std::string _client;
	};
}

#endif  // _SRC_SESSIONINFO_H_
