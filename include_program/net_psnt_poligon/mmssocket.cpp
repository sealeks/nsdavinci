/* 
 * File:   mmssocket.cpp
 * Author: sealeks@mail.ru
 * 
 * Created on 27 Февраль 2013 г., 22:26
 */

#include "mmssocket.h"

namespace prot9506 {


    /*const boost::array<boost::asn1::oidindx_type, 5 > MMSAE1_ARR = {1, 1, 999, 1 , 1};
    const boost::asn1::oid_type MMSAE1_OID = boost::asn1::oid_type(MMSAE1_ARR);

    const boost::array<boost::asn1::oidindx_type, 5 > MMSAE2_ARR =  {1, 1, 999, 1 , 1};
    const boost::asn1::oid_type MMSAE2_OID = boost::asn1::oid_type(MMSAE2_ARR);*/
    
    const boost::array<boost::asn1::oidindx_type, 4 > MMSAE1_ARR = {1, 3, 9999, 106};
    const boost::asn1::oid_type MMSAE1_OID = boost::asn1::oid_type(MMSAE1_ARR);

    const boost::array<boost::asn1::oidindx_type, 4 > MMSAE2_ARR =  {1, 3, 9999, 106};
    const boost::asn1::oid_type MMSAE2_OID = boost::asn1::oid_type(MMSAE2_ARR);


    const MMS::ServiceSupportOptions  MMS_SERVICE_OPTOION_SUPPORT =  MMSO::ServiceSupportOptions_status | MMSO::ServiceSupportOptions_getNameList | MMSO::ServiceSupportOptions_identify | MMSO::ServiceSupportOptions_read | MMSO::ServiceSupportOptions_write |
            MMSO::ServiceSupportOptions_rename |   MMSO::ServiceSupportOptions_deleteNamedVariableList | MMSO::ServiceSupportOptions_getVariableAccessAttributes | MMSO::ServiceSupportOptions_informationReport  ;
    const MMS::ParameterSupportOptions  MMS_CBB_OPTION_SUPPORT    =   MMSO::ParameterSupportOptions_str1 | MMSO::ParameterSupportOptions_str2 | MMSO::ParameterSupportOptions_valt | MMSO::ParameterSupportOptions_valt |
            MMSO::ParameterSupportOptions_vnam |  MMSO::ParameterSupportOptions_vadr | MMSO::ParameterSupportOptions_tpy | MMSO::ParameterSupportOptions_vlis;

    presentation_option init_synaxes() {
        return presentation_option( ACSE_1_OID, MMS_OID);
    }

    boost::system::error_code stream_socket::init_request() {

        acseppm_ = ppm()->get_context(ACSE_1_OID);
        mmsppm_ = ppm()->get_context(MMS_OID);

        if (!acseppm_ || !mmsppm_)
            return boost::itu::ER_OUTDOMAIN;

        if (!acseppm_->valid() || !mmsppm_->valid())
            return boost::itu::ER_OUTDOMAIN;

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
        areq->called_AE_qualifier->aso_qualifier_form2(new ACSE::ASO_qualifier_form2(33));

        areq->calling_AP_title->ap_title_form2__new( new ACSE::AP_title_form2(MMSAE2_OID));
        areq->calling_AE_qualifier->aso_qualifier_form2(new ACSE::ASO_qualifier_form2(33));


        boost::asn1::external_type  userdata;
        userdata.indirect_reference__assign( new int(3));
        userdata.direct_reference__assign( new boost::asn1::oid_type(boost::asn1::BASIC_ENCODING_OID));
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
                return boost::itu::ER_OUTDOMAIN;

            if (!acseppm_->valid() || !mmsppm_->valid())
                return boost::itu::ER_OUTDOMAIN;

            ACSE::ACSE_apdu  apdu;

            acseppm()->get( apdu );

            switch (apdu.type()) {
                case ACSE::ACSE_apdu_aare:
                {
                    const   ACSE::AARE_apdu&  aresp = *apdu.aare();
                    if (aresp->user_information) {
                        if (aresp->user_information->size()) {
                            boost::asn1::external_type& ext = aresp->user_information->operator [](0);
                            MMS::MMSpdu mms;
                            switch (ext.encoding->type()) {
                                case boost::asn1::external_type::encoding_type_single_ASN1_type:
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
                                            return  boost::itu:: ER_REFUSE;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    return boost::itu::ER_PROTOCOL;
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
        return boost::itu::ER_NAADDRESS;
    }



}
