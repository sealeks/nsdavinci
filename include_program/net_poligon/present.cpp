/* 
 * File:   present.cpp
 * Author: sealeks@mail.ru
 * 
 * Created on 31 Январь 2013 г., 13:28
 */

#include "present.h"
#include "ISO8823-PRESENTATION.h"
#include "ASN1-Object-Identifier-Module.h"
#include "Reliable-Transfer-APDUs.h"
#include "P-EXAMPLE-1.h"

//using namespace ISO8823_PRESENTATION;
//using namespace P_EXAMPLE_1;


const boost::array<boost::asio::asn::oidindx_type, 3 > BASIC_ENCODING_ARR = {2, 1, 1};
const boost::asio::asn::oid_type BASIC_ENCODING_OID = boost::asio::asn::oid_type(BASIC_ENCODING_ARR);

const boost::array<boost::asio::asn::oidindx_type, 6 > PCNTXT_ARR = {1, 2, 3, 4, 5,  1};
const boost::asio::asn::oid_type PCNTXT_OID = boost::asio::asn::oid_type(PCNTXT_ARR);

const boost::array<boost::asio::asn::oidindx_type, 6 > CMCNTXT_ARR = {1, 2, 3, 4, 5,  2};
const boost::asio::asn::oid_type CMCNTXT_OID = boost::asio::asn::oid_type(CMCNTXT_ARR);

typedef ISO8823_PRESENTATION::Mode_selector p_mode_type;
typedef ISO8823_PRESENTATION::Called_presentation_selector p_cd_selector;
typedef ISO8823_PRESENTATION::Calling_presentation_selector p_cng_selector;
typedef ISO8823_PRESENTATION::Context_list_sequence_of  p_context_type;
typedef ISO8823_PRESENTATION::Fully_encoded_data  p_full_data_type;
typedef ISO8823_PRESENTATION::PDV_list  pdv_list_type;

typedef P_EXAMPLE_1::CM_apdu  a_pdu_type;
typedef P_EXAMPLE_1::CM_CONNECT_REQ_apdu  a_connect_req_type;
typedef P_EXAMPLE_1::CM_CONNECT_RSP_apdu  a_connect_resp_type;

using boost::asio::asn::graphicstring_type;
using boost::asio::asn::any_type;

std::string start_request() {



    ISO8823_PRESENTATION::CP_type cp;
    cp.mode_selector.mode_value = p_mode_type::mode_value_normal_mode;
    cp.normal_mode_parameters__new();
    cp.normal_mode_parameters->called_presentation_selector__assign( p_cd_selector("P-EXAMPLE-SERVER"));
    cp.normal_mode_parameters->calling_presentation_selector__assign( p_cng_selector("P-EXAMPLE-SERVER"));


    p_context_type cl1;
    cl1.abstract_syntax_name = PCNTXT_OID;
    cl1.presentation_context_identifier = 1;
    //ISO8823_PRESENTATION::Context_list_sequence_of::transfer_syntax_name_list_type tr1 = OIDTEST;
    cl1.transfer_syntax_name_list.push_back(BASIC_ENCODING_OID);


    p_context_type cl2;
    cl2.abstract_syntax_name = CMCNTXT_OID;
    cl2.presentation_context_identifier = 3;
    cl2.transfer_syntax_name_list.push_back(BASIC_ENCODING_OID);

    cp.normal_mode_parameters->presentation_context_definition_list__new();

    cp.normal_mode_parameters->presentation_context_definition_list->push_back(cl1);
    cp.normal_mode_parameters->presentation_context_definition_list->push_back(cl2);

    {
        boost::asio::asn::x690::oarchive OARCV1;


        a_pdu_type pdu;
        pdu.connect_req(new a_connect_req_type(graphicstring_type("Hello server from C++!!")));


        pdu.serialize(OARCV1);

        p_full_data_type fdta;
        pdv_list_type pdlst;
        pdlst.presentation_context_identifier = 1;
        pdlst.presentation_data_values.single_ASN1_type(new any_type());

        pdlst.presentation_data_values.single_ASN1_type()->bind(OARCV1);

        fdta.push_back(pdlst);
        //cp.normal_mode_parameters->user_data;
        cp.normal_mode_parameters->user_data.fully_encoded_data(new p_full_data_type(fdta));
    }

    boost::asio::asn::x690::oarchive OARCV;


    boost::asio::iso::raw_type data;


    OARCV & cp;

    OARCV.bind(data);

    return std::string(data.begin(), data.end());

}

std::string  start_response(const std::string& vl) {

    boost::asio::asn::x690::iarchive IARCV;
    boost::asio::asn::x690::iarchive IARCV2;
    IARCV.add(boost::asio::asn::raw_type(vl.begin(), vl.end()));

    ISO8823_PRESENTATION::CPA_PPDU cp;

    IARCV & cp;

    if (cp.normal_mode_parameters->user_data.fully_encoded_data()) {
        boost::shared_ptr<any_type> dtv = cp.normal_mode_parameters->user_data.fully_encoded_data()->
                front().presentation_data_values.single_ASN1_type();
        a_pdu_type pdu;
        dtv->bind(IARCV2);
        pdu.serialize(IARCV2);
        a_connect_resp_type resp = *pdu.connect_rsp();


        return resp.value();
    }
    return "";




}

