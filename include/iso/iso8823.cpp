/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#include <iosfwd>
#include <iostream>
#include <sstream>

#include <iso/iso8823.h>
#include <iso/archive_stream.h>
#include <iso/presentation/ISO8823-PRESENTATION.h>

/*


   p_context_type cl1;
   cl1.abstract_syntax_name = PCNTXT_OID;
   cl1.presentation_context_identifier = 1;
   //ISO8823_PRESENTATION::Context_list_sequence_of::transfer_syntax_name_list_type tr1 = OIDTEST;
   cl1.transfer_syntax_name_list.push_back(boost::asio::BASIC_ENCODING_OID);
   cl1.transfer_syntax_name_list.push_back(boost::asio::CANONICAL_ENCODING_OID);
   cl1.transfer_syntax_name_list.push_back(boost::asio::DISTINGUISH_ENCODING_OID);    
   //cl1.transfer_syntax_name_list.push_back(boost::asio::BASIC_ENCODING_OID);

   p_context_type cl2;
   cl2.abstract_syntax_name = CMCNTXT_OID;
   cl2.presentation_context_identifier = 3;
   cl2.transfer_syntax_name_list.push_back(boost::asio::BASIC_ENCODING_OID);

   cp.normal_mode_parameters->presentation_context_definition_list__new();

   cp.normal_mode_parameters->presentation_context_definition_list->push_back(cl1);
   cp.normal_mode_parameters->presentation_context_definition_list->push_back(cl2);
    
   cp.normal_mode_parameters->user_session_requirements__assign(ISO8823_PRESENTATION::User_session_requirements_half_duplex); 
   cp.normal_mode_parameters->presentation_requirements__assign(ISO8823_PRESENTATION::Presentation_requirements_context_management); 
    
    
cp.normal_mode_parameters->default_context_name__new();
cp.normal_mode_parameters->default_context_name->abstract_syntax_name = PCNTXT_OID;
cp.normal_mode_parameters->default_context_name->transfer_syntax_name = boost::asio::BASIC_ENCODING_OID;

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


   OARCV & cp;*/



namespace boost {
    namespace asio {
        namespace iso {

            static archive_ptr build_by_syntaxes(const oid_type& asyntax, const encoding_rule& tsyntax) {

                typedef boost::asio::asn::x690::iarchive                                                                           x690_iarchive_type;
                typedef boost::asio::asn::x690::oarchive                                                                          x690_oarchive_type;
                typedef boost::asio::iso::archive_temp<x690_iarchive_type, x690_oarchive_type>              x690_archive;

                switch (tsyntax) {
                    case BER_ENCODING:
                    case DER_ENCODING:
                    case CER_ENCODING:   return archive_ptr( new x690_archive(asyntax, tsyntax ));
                    default:
                    {
                    }
                }
                return archive_ptr();
            }



            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


            const oid_type X690_TRANSFER_SINTAXS_ARR[] = {BASIC_ENCODING_OID, CANONICAL_ENCODING_OID, DISTINGUISH_ENCODING_OID};
            const transfer_synaxes_type X690_TRANSFER_SINTAXS = transfer_synaxes_type (X690_TRANSFER_SINTAXS_ARR, X690_TRANSFER_SINTAXS_ARR + 3);

            const oid_type BASE_TRANSFER_SINTAXS_ARR[] = {BASIC_ENCODING_OID};
            const transfer_synaxes_type BASE_TRANSFER_SINTAXS = transfer_synaxes_type(BASE_TRANSFER_SINTAXS_ARR, BASE_TRANSFER_SINTAXS_ARR + 1);

            presentation_context::presentation_context(int id, const oid_type& asyntax, const encoding_rule& tsyntax, const transfer_synaxes_type&  tsxs = BASE_TRANSFER_SINTAXS ) :
            abstract_syntax_(asyntax), transfer_syntaxes_(tsxs) {
                archiver_ = build_by_syntaxes(asyntax , tsyntax);

            }

            presentation_context::presentation_context(int id , const oid_type& asyntax, const transfer_synaxes_type&  tsxs = BASE_TRANSFER_SINTAXS ) :
            abstract_syntax_(asyntax), transfer_syntaxes_(tsxs) {
            }

            bool presentation_context::encoding(encoding_rule val )  {
                if (encoding() != val) {
                    archiver_ = build_by_syntaxes(abstract_syntax_ , val);
                }
                return archiver_;
            }

            bool presentation_context::transfer_syntax(const oid_type& val)  {
                if (transfer_syntax() != val)   {
                   archiver_ = build_by_syntaxes(abstract_syntax_, oid_to_encoding(val));
                }
                return archiver_;
            }


            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


            namespace prot8823 {

                typedef ISO8823_PRESENTATION::CP_type CP_type;
                typedef ISO8823_PRESENTATION::Mode_selector p_mode_type;
                typedef ISO8823_PRESENTATION::Called_presentation_selector p_cd_selector;
                typedef ISO8823_PRESENTATION::Calling_presentation_selector p_cng_selector;
                typedef ISO8823_PRESENTATION::Context_list_sequence_of p_context_type;
                typedef ISO8823_PRESENTATION::Fully_encoded_data p_full_data_type;
                typedef ISO8823_PRESENTATION::PDV_list pdv_list_type;






            }
        }
    }
}
