#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <isteamnetworkingsockets.h>
#include <isteamnetworkingutils.h>
#include <steamnetworkingtypes.h>

class SteamNetworkingManager;

using boost::asio::ip::tcp;

// TCP Server class
class TCPServer {
public:
    TCPServer(int port, SteamNetworkingManager* manager);
    ~TCPServer();

    bool start();
    void stop();
    void sendToAll(const std::string& message, std::shared_ptr<tcp::socket> excludeSocket = nullptr);
    void sendToAll(const char* data, size_t size, std::shared_ptr<tcp::socket> excludeSocket = nullptr);
    int getClientCount();

private:
    void start_accept();
    void start_read(std::shared_ptr<tcp::socket> socket);

    int port_;
    bool running_;
    boost::asio::io_context io_context_;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_;
    tcp::acceptor acceptor_;
    std::vector<std::shared_ptr<tcp::socket>> clients_;
    std::mutex clientsMutex_;
    std::thread serverThread_;
    bool hasAcceptedConnection_;
    SteamNetworkingManager* manager_;
    bool forwarding_;
};