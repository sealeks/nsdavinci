/* 
 * File:   present.h
 * Author: sealeks@mail.ru
 *
 * Created on 31 Январь 2013 г., 13:28
 */

#ifndef ___PRESENT_H
#define	___PRESENT_H

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

#include <iso/rfc1006.h>
#include <iso/iso8327.h>
#include <iso/iso8823.h>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>



typedef boost::asio::iso::archive_ptr           archive_ptr;
typedef boost::asio::iso::archiver_map      archive_map;
typedef boost::asio::iso::archiver_pair      archiver_pair;


archive_map get_map();





#endif	/* PRESENT_H */

