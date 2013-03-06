/* 
 * File:   mmssocket.cpp
 * Author: sealeks@mail.ru
 * 
 * Created on 27 Февраль 2013 г., 22:26
 */

#include "mmssocket.h"

namespace prot9506 {


    const boost::array<boost::asio::asn::oidindx_type, 5 > MMSAE1_ARR = {1, 1, 999, 1 , 1};
    const boost::asio::asn::oid_type MMSAE1_OID = boost::asio::asn::oid_type(MMSAE1_ARR);

    const boost::array<boost::asio::asn::oidindx_type, 5 > MMSAE2_ARR =  {1, 1, 999, 1 , 1};
    const boost::asio::asn::oid_type MMSAE2_OID = boost::asio::asn::oid_type(MMSAE2_ARR);


    const MMS::ServiceSupportOptions  MMS_SERVICE_OPTOION_SUPPORT =  MMSO::ServiceSupportOptions_status | MMSO::ServiceSupportOptions_getNameList | MMSO::ServiceSupportOptions_identify | MMSO::ServiceSupportOptions_read | MMSO::ServiceSupportOptions_write |
            MMSO::ServiceSupportOptions_rename |   MMSO::ServiceSupportOptions_deleteNamedVariableList | MMSO::ServiceSupportOptions_getVariableAccessAttributes | MMSO::ServiceSupportOptions_informationReport  ;
    const MMS::ParameterSupportOptions  MMS_CBB_OPTION_SUPPORT    =   MMSO::ParameterSupportOptions_str1 | MMSO::ParameterSupportOptions_str2 | MMSO::ParameterSupportOptions_valt |
            MMSO::ParameterSupportOptions_vnam |  MMSO::ParameterSupportOptions_vadr | MMSO::ParameterSupportOptions_tpy | MMSO::ParameterSupportOptions_vlis;

    presentation_option init_synaxes() {
        return presentation_option( ACSE_1_OID, MMS_OID);
    }

    boost::system::error_code stream_socket::init_request() {

        acseppm_ = ppm()->get_context(ACSE_1_OID);
        mmsppm_ = ppm()->get_context(MMS_OID);

        if (!acseppm_ || !mmsppm_)
            return boost::asio::iso::ERROR_EDOM;

        if (!acseppm_->valid() || !mmsppm_->valid())
            return boost::asio::iso::ERROR_EDOM;

        MMS::MMSpdu mms;
        mms.initiate_RequestPDU__new();
        MMS::Initiate_RequestPDU& initpdu = *mms.initiate_RequestPDU();

        initpdu.localDetailCalling__assign( new MMS::Integer32(30000));
        initpdu.proposedMaxServOutstandingCalling = MMS::Integer16(1);
        initpdu.proposedMaxServOutstandingCalled = MMS::Integer16(5);
        initpdu.proposedDataStructureNestingLevel__assign(new MMS::Integer8(5));
        initpdu.initRequestDetail->proposedVersionNumber = 1;
        initpdu.initRequestDetail->servicesSupportedCalling = MMS_SERVICE_OPTOION_SUPPORT;
        initpdu.initRequestDetail->proposedParameterCBB  = MMS_CBB_OPTION_SUPPORT;

        mmsppm()->set( mms );

        ACSE::ACSE_apdu  apdu;
        ACSE::AARQ_apdu areq;
        areq->protocol_version__assign( new ACSE::bitstring_type(true, 0));
        areq->aSO_context_name = ACSE::ASO_context_name(MMSA_OID);

        areq->called_AP_title->ap_title_form2__new( new ACSE::AP_title_form2(MMSAE1_OID));
        areq->called_AE_qualifier->aso_qualifier_form2(new ACSE::ASO_qualifier_form2(12));

        areq->calling_AP_title->ap_title_form2__new( new ACSE::AP_title_form2(MMSAE2_OID));
        areq->calling_AE_qualifier->aso_qualifier_form2(new ACSE::ASO_qualifier_form2(12));


        boost::asio::asn::external_type  userdata;
        userdata.indirect_reference__assign( new int(3));
        userdata.direct_reference__assign( new boost::asio::asn::oid_type(boost::asio::BASIC_ENCODING_OID));
        userdata.encoding->single_ASN1_type__new();
        userdata.encoding->single_ASN1_type()->bind(*(mmsppm()->archiver()->out()));

        mmsppm()->archiver()->clear();

        areq->user_information__new();
        areq->user_information->push_back(userdata);
        apdu.aarq( new ACSE::AARQ_apdu(areq));

        acseppm()->set(apdu);

        return boost::system::error_code();

    }

    boost::system::error_code stream_socket::init_response() {
        try {
            acseppm_ = ppm()->get_context(ACSE_1_OID);
            mmsppm_ = ppm()->get_context(MMS_OID);

            if (!acseppm_ || !mmsppm_)
                return boost::asio::iso::ERROR_EDOM;

            if (!acseppm_->valid() || !mmsppm_->valid())
                return boost::asio::iso::ERROR_EDOM;

            ACSE::ACSE_apdu  apdu;

            acseppm()->get( apdu );

            switch (apdu.type()) {
                case ACSE::ACSE_apdu_aare:
                {
                    const   ACSE::AARE_apdu&  aresp = *apdu.aare();
                    if (aresp->user_information) {
                        if (aresp->user_information->size()) {
                            boost::asio::asn::external_type& ext = aresp->user_information->operator [](0);
                            MMS::MMSpdu mms;
                            switch (ext.encoding->type()) {
                                case boost::asio::asn::external_type::encoding_type_single_ASN1_type:
                                {
                                    ext.encoding->single_ASN1_type()->bind(*(mmsppm()->archiver()->in()));
                                    mmsppm()->get(mms);
                                    switch (mms.type()) {
                                        case MMS::MMSpdu_initiate_ResponsePDU:
                                        {
                                            const MMS::Initiate_ResponsePDU& mmsresp = *mms.initiate_ResponsePDU();
                                            //mmsresp.
                                            return boost::system::error_code();
                                        }
                                        default:
                                        {
                                            return  boost::asio::iso::ERROR_ECONNREFUSED;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    return boost::asio::iso::ERROR__EPROTO;
                }
                default:
                {
                }
            }
        }
        catch (const boost::system::system_error& cerr) {
            return cerr.code();
        }
        catch (...) {
        }
        return boost::asio::iso::ERROR_EADDRNOTAVAIL;
    }

    boost::system::error_code stream_socket::identify_request() {
        MMS::MMSpdu mms;
        mms.confirmed_RequestPDU__new();
        MMS::Confirmed_RequestPDU& confermedpdu = *mms.confirmed_RequestPDU();
        confermedpdu.invokeID = 100;
        confermedpdu.service->identify__new();
        mmsppm()->set(mms);
        return boost::system::error_code();
    }

    boost::system::error_code stream_socket::identify_response() {
        MMS::MMSpdu mms;
        mmsppm()->get(mms);
        switch (mms.type()) {
            case MMS::MMSpdu_confirmed_ResponsePDU:
            {
                const MMS::Confirmed_ResponsePDU& mmsresp = *mms.confirmed_ResponsePDU();
                const MMS::ConfirmedServiceResponse& confirmresp = *mmsresp.service;
                switch (confirmresp.type()) {
                    case MMS::ConfirmedServiceResponse_identify:{
                        const MMS::Identify_Response&  idetfy=*confirmresp.identify();
                        std::cout << "Vendor: " << (*idetfy.vendorName) << " Model: " << (*idetfy.modelName)  << " Revision: " << (*idetfy.revision)  << std::endl;
                    }
                    default:{
                        
                    }
                }
                return boost::system::error_code();
            }
            default:
            {
                return  boost::asio::iso::ERROR_ECONNREFUSED;
            }
        }

        return boost::asio::iso::ERROR_EADDRNOTAVAIL;
    }

}
