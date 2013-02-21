/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#include <iso/iso8823.h>
#include <iso/presentation/ISO8823-PRESENTATION.h>

namespace boost {
    namespace asio {
        namespace iso {

            namespace prot8823 {


                typedef ISO8823_PRESENTATION::CP_type                                                      CP_type;
                typedef ISO8823_PRESENTATION::CPA_PPDU                                                   CPA_type;
                typedef ISO8823_PRESENTATION::User_data                                                    User_data;
                typedef ISO8823_PRESENTATION::Mode_selector                                              mode_type;
                typedef ISO8823_PRESENTATION::Called_presentation_selector                         cd_selector_type;
                typedef ISO8823_PRESENTATION::Calling_presentation_selector                        cng_selector_type;
                typedef ISO8823_PRESENTATION::Simply_encoded_data                                   simpledata_type;
                typedef ISO8823_PRESENTATION::Fully_encoded_data                                      fulldata_type;
                typedef ISO8823_PRESENTATION::Context_list_sequence_of                             p_context_type;
                typedef ISO8823_PRESENTATION::PDV_list                                                      pdv_list_type;
                typedef ISO8823_PRESENTATION::PDV_list::presentation_data_values_type       data_values_type;
                typedef ISO8823_PRESENTATION::Result_list                                                    result_list_type;

                static archive_ptr build_by_syntaxes(const oid_type& asyntax, const encoding_rule& tsyntax) {

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

                bool operator<(presentation_context_unit_ptr ls, presentation_context_unit_ptr rs) {
                    if (ls && rs)
                        return ls->abstract_syntax() < rs->abstract_syntax();
                    return rs ? true : false;
                }


                ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                presentation_connection_option::presentation_connection_option(const oid_type& asyntax, const encoding_rule& tsyntax , const presentation_req_type& req) : preq_(req) {
                    connection_syntax_.insert(presentation_context_unit_ptr( new presentation_context_unit(asyntax, tsyntax)));
                }

                presentation_connection_option::presentation_connection_option(const oid_type& asyntax1, const oid_type& asyntax2, const encoding_rule& tsyntax , const presentation_req_type& req) : preq_(req) {
                    connection_syntax_.insert(presentation_context_unit_ptr( new presentation_context_unit(asyntax1, tsyntax)));
                    connection_syntax_.insert(presentation_context_unit_ptr( new presentation_context_unit(asyntax2, tsyntax)));
                }

                void presentation_connection_option::insert_abstract_syntax(const oid_type& asyntax, const encoding_rule& tsyntax ) {
                    insert_abstract_syntax(presentation_context_unit_ptr( new presentation_context_unit(asyntax, tsyntax))) ;
                }

                bool presentation_connection_option::has_abstract_syntax(const oid_type& asyntax, const encoding_rule& tsyntax ) {
                    return connection_syntax_.find(presentation_context_unit_ptr( new presentation_context_unit(asyntax, tsyntax))) != connection_syntax_.end();
                }

                ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                presentation_pm::presentation_pm(const presentation_connection_option& opt , context_id_type  id) :
                nextid_(id) , preq_(opt.p_requirements()) {
                    for (presentation_context_unit_set::const_iterator it = opt.abstract_syntaxes().begin(); it != opt.abstract_syntaxes().end(); ++it) {
                        insert_context(*it);
                    }
                }

                presentation_pm::presentation_pm(const presentation_req_type& preq , context_id_type  id ) :
                nextid_(id) , preq_(preq) {
                }

                context_id_type presentation_pm::insert_context(context_id_type id, const oid_type& asyntax, const encoding_rule& tsyntax, const transfer_synaxes_type&  tsxs) {
                    transfer_synaxes_type  tsxs_ = tsxs;
                    if ( tsxs_.empty())
                        tsxs_.insert(encoding_to_oid(tsyntax));
                    nextid_ += 2;
                    presentation_context_unit_ptr tmp = presentation_context_unit_ptr( new presentation_context_unit(asyntax, tsyntax, tsxs_));
                    if (!tmp->valid())
                        return 0;
                    contexts_.insert(presentation_context_type(id, tmp));
                    return id;
                }

                context_id_type presentation_pm::insert_context(context_id_type id, presentation_context_unit_ptr ctx) {
                    if (!ctx || !ctx->valid())
                        return 0;
                    contexts_.insert(presentation_context_type(id, ctx));
                    return id;
                }

                context_id_type presentation_pm::remove_contex(context_id_type id) {
                    presentation_context_map::iterator it = contexts_.find(id);
                    if (it != contexts_.end()) {
                        contexts_.erase(it);
                        return id;
                    }
                    return 0;
                }

                context_id_type presentation_pm::insert_context(presentation_context_unit_ptr ctx) {
                    context_id_type tmp = insert_context(nextid_, ctx);
                    if (tmp) nextid_ += 2;
                    return tmp;
                }

                context_id_type presentation_pm::insert_context(const oid_type& asyntax, const encoding_rule& tsyntax, const transfer_synaxes_type&  tsxs) {
                    context_id_type tmp = insert_context(nextid_, asyntax, tsyntax, tsxs);
                    if (tmp) nextid_ += 2;
                    return tmp;
                }

                presentation_context_map::iterator  presentation_pm::find(const oid_type& oid) {
                    for (presentation_context_map::iterator it = contexts_.begin(); it != contexts_.end(); ++it) {
                        if (it->second->abstract_syntax() == oid && it->second->archiver())
                            return it;
                    }
                    return contexts_.end();
                }

                ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                static void build_userdata(presentation_pm_ptr ppm,  User_data& data) {
                    if (ppm->is_simple_encoding()) {
                        data.simply_encoded_data__new();
                    }
                    else {
                        data.fully_encoded_data__new();
                        for (presentation_context_map::const_iterator it = ppm->contexts().begin(); it != ppm->contexts().end(); ++it) {
                            if (it->second->valid() && it->second->archiver()->out()->size()) {
                                pdv_list_type pdv_lst;
                                pdv_lst.presentation_context_identifier = it->first;
                                pdv_lst.presentation_data_values.single_ASN1_type__new();
                                pdv_lst.presentation_data_values.single_ASN1_type()->bind(*(it->second->archiver()->out()));
                                data.fully_encoded_data()->push_back(pdv_lst);
                            }
                        }
                    }
                }

                static bool parse_USERDATA(presentation_pm_ptr ppm, const User_data& data) {
                    switch (data.type()) {
                        case ISO8823_PRESENTATION::User_data_Simply_encoded_data:
                        {
                            if (!data.simply_encoded_data())
                                return false;
                            const simpledata_type& value = *data.simply_encoded_data();
                            ///
                            return true;
                        }
                        case ISO8823_PRESENTATION::User_data_Fully_encoded_data:
                        {
                            if (!data.fully_encoded_data())
                                return false;
                            const fulldata_type& values = *data.fully_encoded_data();
                            for (fulldata_type::const_iterator it = values.begin(); it != values.end() ; ++it ) {
                                if (ppm->exists(it->presentation_context_identifier)) {
                                    if (it->transfer_syntax_name) {
                                        ppm->transfer_syntax(it->presentation_context_identifier, *(it->transfer_syntax_name));
                                        if (!ppm->exists(it->presentation_context_identifier)) continue;
                                    }
                                    const data_values_type& values = it->presentation_data_values;
                                    switch (values.type()) {
                                        case ISO8823_PRESENTATION::PDV_list::presentation_data_values_type_ABSTRACT_SYNTAX:
                                        {
                                            if (values.single_ASN1_type())
                                                values.single_ASN1_type()->bind(*(ppm->find(it->presentation_context_identifier)->in()));
                                            break;
                                        }
                                        case ISO8823_PRESENTATION::PDV_list::presentation_data_values_type_octet_aligned_type:
                                        {

                                            break;
                                        }
                                        case ISO8823_PRESENTATION::PDV_list::presentation_data_values_type_arbitrary_type:
                                        {

                                            break;
                                        }
                                        default:
                                        {
                                        }
                                    }

                                }
                            }
                            return true;
                        }
                        default:
                        {
                        }
                    }
                    return false;
                }

                void stream_socket::build_CP_type() {
                    CP_type cp;
                    cp.mode_selector.mode_value = mode_type::mode_value_normal_mode;
                    cp.normal_mode_parameters__new();
                    if (!selector().called().empty())
                        cp.normal_mode_parameters->called_presentation_selector__assign(cd_selector_type(selector().called()));
                    if (!selector().calling().empty())
                        cp.normal_mode_parameters->calling_presentation_selector__assign(cng_selector_type(selector().calling()));
                    if (ppm()->is_context_menagment())
                        cp.normal_mode_parameters->presentation_requirements__assign(ppm()->p_requirements());
                    cp.normal_mode_parameters->presentation_context_definition_list__new();
                    cp.normal_mode_parameters->protocol_version__assign(PRSNT_VERSION);
                    for (presentation_context_map::const_iterator it = ppm()->contexts().begin(); it != ppm()->contexts().end(); ++it) {
                        if (it->second->valid()) {
                            p_context_type ctx;
                            ctx.abstract_syntax_name = it->second->abstract_syntax();
                            ctx.presentation_context_identifier = it->first;
                            ctx.transfer_syntax_name_list.insert(ctx.transfer_syntax_name_list.begin(),
                                    it->second->transfer_syntaxs().begin(), it->second->transfer_syntaxs().end());
                            cp.normal_mode_parameters->presentation_context_definition_list->push_back(ctx);
                        }
                    }
                    build_userdata(ppm(), cp.normal_mode_parameters->user_data);
                    (coder()->output()) & cp;
                }

                void stream_socket::build_DT_type() {

                    User_data udt;
                    build_userdata(ppm(), udt);
                    udt.serialize(coder()->output());
                }

                bool stream_socket::parse_CR() {
                    switch (coder()->input().test_id()) {
                        case boost::asio::asn::TYPE_SET:
                        {
                            CPA_type cpa;
                            (coder()->input()) & cpa;
                            if (cpa.mode_selector.mode_value == mode_type::mode_value_normal_mode) {
                                if (cpa.normal_mode_parameters) {

                                    if ((cpa.normal_mode_parameters->presentation_context_definition_result_list) &&
                                            (!cpa.normal_mode_parameters->presentation_context_definition_result_list->empty())) {
                                        presentation_context_map::iterator ctxit = ppm()->contexts().begin();
                                        for (result_list_type::const_iterator it = cpa.normal_mode_parameters->presentation_context_definition_result_list->begin();
                                                it != cpa.normal_mode_parameters->presentation_context_definition_result_list->end(); ++it) {
                                            if (it->result != ISO8823_PRESENTATION::Result_acceptance) {
                                                if (ctxit != ppm()->contexts().end()) {
                                                    std::cout << "Remove context id: " << ctxit->first  << " AS: " << ctxit->second->abstract_syntax()
                                                            << " rsn: " << ( it->provider_reason ? (*it->provider_reason) :  -1 ) << std::endl;
                                                    ppm()->remove_contex(ctxit->first);
                                                }
                                            }
                                            else {
                                                if ((it->transfer_syntax_name) && (ctxit != ppm()->contexts().end())) {
                                                    std::cout << "Accept context id: " << ctxit->first  << " AS: " << ctxit->second->abstract_syntax()
                                                            << " TS: " << ( it->transfer_syntax_name ? (*it->transfer_syntax_name) :  oid_type() ) << std::endl;
                                                    ppm()->transfer_syntax(ctxit->first, (*(it->transfer_syntax_name)));
                                                }
                                                ctxit++;
                                            }
                                        }
                                    }
                                    if (cpa.normal_mode_parameters->responding_presentation_selector) {
                                        selector().called(std::string(cpa.normal_mode_parameters->responding_presentation_selector->begin(),
                                                cpa.normal_mode_parameters->responding_presentation_selector->end()));
                                    }
                                    if (cpa.normal_mode_parameters->presentation_requirements) {
                                        ppm()->p_requirements(ppm()->p_requirements() &
                                                (*(cpa.normal_mode_parameters->presentation_requirements)));
                                        std::cout << "Negotiated client presentation_requirements: " << ppm()->p_requirements()  << std::endl;
                                    }

                                    parse_USERDATA(ppm(), cpa.normal_mode_parameters->user_data);
                                }
                            }

                        }
                    }
                    return false;
                }

                bool stream_socket::parse_RESPONSE() {
                    int recl = coder()->input().test_class();
                    switch (coder()->input().test_id()) {
                        case 1:
                        {
                            switch (coder()->input().test_class()) {
                                case 64:
                                {
                                    User_data data;
                                    data.serialize(coder()->input());
                                    parse_USERDATA(ppm(), data);
                                    return true;
                                }

                            }
                        }

                    }
                    return false;
                }
            }
        }
    }
}