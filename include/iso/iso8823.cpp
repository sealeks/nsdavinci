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
            namespace prot8823 {

                typedef ISO8823_PRESENTATION::CP_type CP_type;
                typedef ISO8823_PRESENTATION::Mode_selector p_mode_type;
                typedef ISO8823_PRESENTATION::Called_presentation_selector p_cd_selector;
                typedef ISO8823_PRESENTATION::Calling_presentation_selector p_cng_selector;
                typedef ISO8823_PRESENTATION::Context_list_sequence_of p_context_type;
                typedef ISO8823_PRESENTATION::Fully_encoded_data p_full_data_type;
                typedef ISO8823_PRESENTATION::PDV_list pdv_list_type;

                void stream_socket::build_CP(archiver_map archs) {
                    archiver->clear();
                    CP_type cp;
                    cp.mode_selector.mode_value = p_mode_type::mode_value_normal_mode;
                    cp.normal_mode_parameters__new();
                    if (!option_.called().empty())
                        cp.normal_mode_parameters->called_presentation_selector__assign(p_cd_selector(option_.called()));
                    if (!option_.calling().empty())
                        cp.normal_mode_parameters->calling_presentation_selector__assign(p_cng_selector(option_.calling()));
                    if (option_.option().default_conext())
                        cp.normal_mode_parameters->default_context_name = option_.option().default_conext();
                    if (option_.option().p_requirements())
                        cp.normal_mode_parameters->presentation_requirements = option_.option().p_requirements();
                    if (option_.option().u_requirements())
                        cp.normal_mode_parameters->user_session_requirements = option_.option().u_requirements();
                    if (!option_.option().conexts().empty()) {
                        cp.normal_mode_parameters->presentation_context_definition_list__new();
                        for (archiver_map::iterator it = archs.begin(); it != archs.end(); ++it) {
                            p_context_type ctx;
                            ctx.abstract_syntax_name = it->second->abstract_syntax();
                            ctx.presentation_context_identifier = it->first;
                            ctx.transfer_syntax_name_list = BASE_TRANSFER_SINTAXS;
                            cp.normal_mode_parameters->presentation_context_definition_list->push_back(ctx);
                        }
                        cp.normal_mode_parameters->user_data.fully_encoded_data(new p_full_data_type());
                        for (archiver_map::iterator it = archs.begin(); it != archs.end(); ++it) {
                            if (it->second->out() && it->second->out()->size()) {
                                pdv_list_type pdv_lst;
                                pdv_lst.presentation_context_identifier = it->first;
                                pdv_lst.transfer_syntax_name__new();
                                pdv_lst.presentation_data_values.single_ASN1_type( new boost::asio::asn::any_type());
                                pdv_lst.presentation_data_values.single_ASN1_type()->bind(*(it->second->out()));
                                cp.normal_mode_parameters->user_data.fully_encoded_data()->push_back(pdv_lst);
                            }
                        }
                    }
                    (archiver->output()) & cp;
                }

                bool stream_socket::parse_CR(archiver_map archs) {
                    switch (archiver->input().test_class()) {

                    }
                    return false;
                }

            }
        }
    }
}
