/* 
 * File:   present.h
 * Author: sealeks@mail.ru
 *
 * Created on 31 Январь 2013 г., 13:28
 */

#ifndef ___PRESENT_H
#define	___PRESENT_H


#include <iso/asn/itu_X690.h>
#include <iso/iso8823.h>


typedef boost::asio::iso::presentation_pm_ptr                  presentation_pm_ptr;
typedef boost::asio::iso::presentation_option                    presentation_option;

presentation_option getpresentotion();
void prepare_connect(presentation_pm_ptr vl);
std::string complete_connect(presentation_pm_ptr vl);
void bld_write_request(presentation_pm_ptr ppm, const std::string& val);
std::string prs_read_request(presentation_pm_ptr ppm);


#endif	/* PRESENT_H */

