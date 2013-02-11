/* 
 * File:   present.cpp
 * Author: sealeks@mail.ru
 * 
 * Created on 31 Январь 2013 г., 13:28
 */

#include "present.h"
#include "P-EXAMPLE-1.h"

using namespace P_EXAMPLE_1;


const boost::array<boost::asio::asn::oidindx_type, 4 > BASIC_ENCODING_ARRT = {2, 1, 2, 1};
const boost::asio::asn::oid_type BASIC_ENCODINGT_OID = boost::asio::asn::oid_type(BASIC_ENCODING_ARRT);

const boost::array<boost::asio::asn::oidindx_type, 6 > PCNTXT_ARR = {1, 2, 3, 4, 5,  1};
const boost::asio::asn::oid_type PCNTXT_OID = boost::asio::asn::oid_type(PCNTXT_ARR);

const boost::array<boost::asio::asn::oidindx_type, 6 > CMCNTXT_ARR = {1, 2, 3, 4, 5,  2};
const boost::asio::asn::oid_type CMCNTXT_OID = boost::asio::asn::oid_type(CMCNTXT_ARR);


typedef P_EXAMPLE_1::CM_apdu  a_pdu_type;
typedef P_EXAMPLE_1::CM_CONNECT_REQ_apdu  a_connect_req_type;
typedef P_EXAMPLE_1::CM_CONNECT_RSP_apdu  a_connect_resp_type;

using boost::asio::asn::graphicstring_type;
using boost::asio::asn::any_type;


archive_map get_map() {

    typedef boost::asio::asn::x690::iarchive                                                                          input_archive_type;
    typedef boost::asio::asn::x690::oarchive                                                                         output_archive_type;
    typedef boost::asio::iso::archive_temp<input_archive_type, output_archive_type>    presentation_archive;
    typedef boost::shared_ptr<presentation_archive>                                                        presentation_archive_ptr;

    archive_map tmp;
    presentation_archive_ptr arch1 = presentation_archive_ptr( new presentation_archive(PCNTXT_OID));
    tmp.insert(archiver_pair(1, arch1));
    
    a_pdu_type pdu;
    pdu.connect_req(new a_connect_req_type(graphicstring_type("Hello server from C++!!")));
    pdu.serialize(arch1->output());
    presentation_archive_ptr arch2 = presentation_archive_ptr( new presentation_archive(CMCNTXT_OID));
    tmp.insert(archiver_pair(3, arch2));
    return tmp;

}

