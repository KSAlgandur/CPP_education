#pragma once
#include <cassert>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>


const int SIZE = 1024;

namespace Net
{
    class Server
    {
        private:
            int sockfd; //= socket(AF_INET,SOCK_STREAM,0);
            std::string ip_adress;
            int port;
            char buff[SIZE];
            struct sockaddr_in servaddr;
            int infolegth;
            int recivelength;
        public:
            Server(int port,std::string ip_adress){};
            ~Server(){};

            void init();
            void start();
            void stop();

        private:
            void receive();
            void process();
            void send();

    };


}