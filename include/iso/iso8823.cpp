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









            }
        }
    }
}
