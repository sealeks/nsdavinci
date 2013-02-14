/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#include <iso/iso8823.h>





namespace boost {
    namespace asio {
        namespace iso {

            static archive_ptr build_by_syntaxes(const oid_type& asyntax, const encoding_rule& tsyntax) {

                /*typedef boost::asio::asn::x690::iarchive                                                                           x690_iarchive_type;
                typedef boost::asio::asn::x690::oarchive                                                                          x690_oarchive_type;
                typedef boost::asio::iso::archive_temp<x690_iarchive_type, x690_oarchive_type>              x690_archive;*/

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

            presentation_context_unit::presentation_context_unit(const oid_type& asyntax, const encoding_rule& tsyntax, const transfer_synaxes_type&  tsxs = BASE_TRANSFER_SINTAXS ) :
            abstract_syntax_(asyntax), transfer_syntaxes_(tsxs) {
                archiver_ = build_by_syntaxes(asyntax , tsyntax);

            }

            //presentation_context_unit::presentation_context_unit( const oid_type& asyntax, const transfer_synaxes_type&  tsxs = BASE_TRANSFER_SINTAXS ) :
            //abstract_syntax_(asyntax), transfer_syntaxes_(tsxs) {
            //}

            bool presentation_context_unit::encoding(encoding_rule val )  {
                if (encoding() != val) {
                    archiver_ = build_by_syntaxes(abstract_syntax_ , val);
                }
                return archiver_;
            }

            bool presentation_context_unit::transfer_syntax(const oid_type& val)  {
                if (transfer_syntax() != val)   {
                    archiver_ = build_by_syntaxes(abstract_syntax_, oid_to_encoding(val));
                }
                return archiver_;
            }


            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            context_id_type presentation_pm::insert_context(context_id_type id, const oid_type& asyntax, const encoding_rule& tsyntax, const transfer_synaxes_type&  tsxs) {
                transfer_synaxes_type  tsxs_ = tsxs;
                if ( tsxs_.empty())
                    tsxs_.insert(encoding_to_oid(tsyntax));
                presentation_context_unit_ptr tmp = presentation_context_unit_ptr( new presentation_context_unit(asyntax, tsyntax, tsxs_));
                if (!tmp->valid())
                    return 0;
                contexts_.insert(presentation_context_type(id, tmp));
                return id;
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



                void build_CP(boost::asio::iso::prot8823::stream_socket  * sock, presentation_pm_ptr ppm) {
                    sock->basiccoder->clear();
                    CP_type cp;
                    cp.mode_selector.mode_value = p_mode_type::mode_value_normal_mode;
                    cp.normal_mode_parameters__new();
                    if (!sock->selector_.called().empty())
                        cp.normal_mode_parameters->called_presentation_selector__assign(p_cd_selector(sock->selector_.called()));
                    if (!sock->selector_.calling().empty())
                        cp.normal_mode_parameters->calling_presentation_selector__assign(p_cng_selector(sock->selector_.calling()));
                    /* if (option_.option().default_conext())
                         cp.normal_mode_parameters->default_context_name = option_.option().default_conext();
                     if (option_.option().p_requirements())
                         cp.normal_mode_parameters->presentation_requirements = option_.option().p_requirements();
                     if (option_.option().u_requirements())
                         cp.normal_mode_parameters->user_session_requirements = option_.option().u_requirements();*/
                    //if (!option_.option().conexts().empty()) {
                    cp.normal_mode_parameters->presentation_context_definition_list__new();
                    for (presentation_context_map::const_iterator it = ppm->contexts().begin(); it != ppm->contexts().end(); ++it) {
                        if (it->second->valid()) {
                            p_context_type ctx;
                            ctx.abstract_syntax_name = it->second->abstract_syntax();
                            ctx.presentation_context_identifier = it->first;
                            ctx.transfer_syntax_name_list.insert(ctx.transfer_syntax_name_list.begin(),
                                    it->second->transfer_syntaxs().begin(), it->second->transfer_syntaxs().end());
                            cp.normal_mode_parameters->presentation_context_definition_list->push_back(ctx);
                        }
                    }
                    cp.normal_mode_parameters->user_data.fully_encoded_data(new p_full_data_type());
                    for (presentation_context_map::const_iterator it = ppm->contexts().begin(); it != ppm->contexts().end(); ++it) {
                        if (it->second->valid() && it->second->archiver()->out()->size()) {
                            pdv_list_type pdv_lst;
                            pdv_lst.presentation_context_identifier = it->first;
                            //pdv_lst.transfer_syntax_name__new();
                            pdv_lst.presentation_data_values.single_ASN1_type( new boost::asio::asn::any_type());
                            pdv_lst.presentation_data_values.single_ASN1_type()->bind(*(it->second->archiver()->out()));
                            cp.normal_mode_parameters->user_data.fully_encoded_data()->push_back(pdv_lst);
                        }
                    }
                    //}
                    (sock->basiccoder->output()) & cp;
                }





            }
        }
    }
}
