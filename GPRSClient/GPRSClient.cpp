/*
  GPRSClient.cpp
  2014 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:lawliet zou(lawliet.zou@gmail.com)
  2014-2-24

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "GPRSClient.h"

GPRSClient::GPRSClient(int tx, int rx, int baudRate, const char* apn, const char* userName, const char *passWord) : GPRS(tx,rx,baudRate,apn,userName,passWord)
{
    _socket_fd = 0;
    ip_set = false;
}


int GPRSClient::init()
{
    reset();
    return 0;
}

int GPRSClient::join()
{
    return GPRS::join();
}

char* GPRSClient::getIPAddress()
{
    snprintf(ip_string, sizeof(ip_string), "%d.%d.%d.%d", (int)((_ip>>24)&0xff),(int)((_ip>>16)&0xff),(int)((_ip>>8)&0xff),(int)(_ip&0xff)); 
    ip_set = true;
    return ip_string;
}

int GPRSClient::connect(char* host, uint16_t port)
{
    return GPRS::connect(_socket_fd,TCP,host,port,DEFAULT_TIMEOUT);  
}

int GPRSClient::connect(IPAddress ip, uint16_t port)
{
    char ipAddr[17];
    snprintf(ipAddr, sizeof(ipAddr), "%d.%d.%d.%d", (int)((_ip>>24)&0xff),(int)((_ip>>16)&0xff),(int)((_ip>>8)&0xff),(int)(_ip&0xff)); 
    return GPRS::connect(_socket_fd,TCP,ipAddr,port,DEFAULT_TIMEOUT);
}

size_t GPRSClient::write(char data)
{
    char buf = (char)data;
    return GPRS::send(_socket_fd, &buf, 1);
}

size_t GPRSClient::write(char* buf, size_t size)
{
    return GPRS::send(_socket_fd, buf, size);
}

int GPRSClient::available()
{
    return GPRS::wait_readable(_socket_fd, DEFAULT_TIMEOUT);
}

int GPRSClient::read()
{
    char data;
    int size = GPRS::wait_readable(_socket_fd, DEFAULT_TIMEOUT);
    if(size <= 0){
        return -1;
    }
    return GPRS::recv(_socket_fd, &data, 1);
}

int GPRSClient::read(char* buf, size_t length)
{
    int size = GPRS::wait_readable(_socket_fd, DEFAULT_TIMEOUT);
    return GPRS::recv(_socket_fd, buf, size>length?length:size);
}

int GPRSClient::peek()
{
    return 0;
}

void GPRSClient::flush()
{
    return GPRS::flush();
}

void GPRSClient::stop()
{
    GPRS::close(_socket_fd);
    //GPRS::disconnect();
}

uint8_t GPRSClient::connected()
{
    return GPRS::is_connected(_socket_fd);
}


