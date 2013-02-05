/* 
 * File:   present.h
 * Author: sealeks@mail.ru
 *
 * Created on 31 Январь 2013 г., 13:28
 */

#ifndef PRESENT_H
#define	PRESENT_H

#include <cstdlib>
#include <deque>
#include <iostream>


#include <iso/rfc1006.h>
#include <iso/iso8327.h>
#include <iso/asn/itu_X690.h>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include <cstdio>
#include <cstdlib>
#include <cstring>


std::string  start_request();
std::string  start_response(const std::string& vl);


#endif	/* PRESENT_H */

