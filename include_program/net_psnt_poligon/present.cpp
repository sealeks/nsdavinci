/* 
 * File:   present.cpp
 * Author: sealeks@mail.ru
 * 
 * Created on 31 Январь 2013 г., 13:28
 */

#include "present.h"
#include "P-EXAMPLE-1.h"

using namespace P_EXAMPLE_1;


const boost::array<boost::asio::asn::oidindx_type, 6 > PCNTXT_ARR = {1, 2, 3, 4, 5,  1};
const boost::asio::asn::oid_type PCNTXT_OID = boost::asio::asn::oid_type(PCNTXT_ARR);

const boost::array<boost::asio::asn::oidindx_type, 6 > CMCNTXT_ARR = {1, 2, 3, 4, 5,  2};
const boost::asio::asn::oid_type CMCNTXT_OID = boost::asio::asn::oid_type(CMCNTXT_ARR);

const boost::array<boost::asio::asn::oidindx_type, 6 > CMTNTXT_ARR = {1, 2, 3, 4, 5,  3};
const boost::asio::asn::oid_type CMTNTXT_OID = boost::asio::asn::oid_type(CMTNTXT_ARR);


typedef P_EXAMPLE_1::CM_apdu  a_pdu_type;
typedef P_EXAMPLE_1::CM_CONNECT_REQ_apdu  a_connect_req_type;
typedef P_EXAMPLE_1::CM_CONNECT_RSP_apdu  a_connect_resp_type;

typedef P_EXAMPLE_1::DATA_apdu                      data_pdu_type;
typedef P_EXAMPLE_1::DATA_RSP_apdu              data_resp_pdu_type;
typedef P_EXAMPLE_1::DATA_REQ_apdu              data_req_pdu_type;

using boost::asio::asn::graphicstring_type;
using boost::asio::asn::any_type;


presentation_option getpresentotion(){
    return presentation_option(PCNTXT_OID, CMCNTXT_OID);
}

void prepare_connect(presentation_pm_ptr vl) {

    typedef boost::asio::asn::x690::iarchive                                                                          input_archive_type;
    typedef boost::asio::asn::x690::oarchive                                                                         output_archive_type;
    typedef boost::asio::iso::archive_temp<input_archive_type, output_archive_type>    presentation_archive;
    typedef boost::shared_ptr<presentation_archive>                                                        presentation_archive_ptr;

   /* presentation_pm_ptr tmp = presentation_pm_ptr(new  presentation_pm());
    tmp->insert_context(1, PCNTXT_OID);
    tmp->insert_context(3, CMCNTXT_OID);    
    tmp->insert_context(5 , CMTNTXT_OID);   */    
 
    a_pdu_type pdu;
    pdu.connect_req(new a_connect_req_type(graphicstring_type("Hello server from C++!!")));
    vl->set(PCNTXT_OID, pdu);

}


std::string complete_connect(presentation_pm_ptr ppm){
    if (ppm->has_input()) {
        a_pdu_type pdu;
        ppm->get(1, pdu);
        if (pdu.connect_rsp())
        return pdu.connect_rsp()->value();
    }
    return "";
}

void bld_write_request(presentation_pm_ptr ppm, const std::string& val) {
    data_pdu_type pdu; 
    static int i=0;
    data_req_pdu_type req;
    req.value().information=val;
    req.value().msgId=++i; 
    pdu.req( new data_req_pdu_type(req));        
    ppm->set(3, pdu);

}

std::string prs_read_request(presentation_pm_ptr ppm){
    if (ppm->has_input()) {
        data_pdu_type pdu;
        ppm->get(3, pdu);
        if (pdu.rsp())
        return pdu.rsp()->value().information;
        if (pdu.req())
        return pdu.req()->value().information;        
    }
    return "";
}    


