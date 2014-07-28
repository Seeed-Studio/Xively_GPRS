/*
 * GPRSClient.cpp
 *
 * Copyright (c) 2014 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : lawliet zou
 * Create Time: Feb 2014
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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


