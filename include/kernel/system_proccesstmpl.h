/* 
 * File:   grouptreadtamplate.h
 * Author: Serg
 *
 * Created on 21 Р�СЋРЅСЊ 2010 Рі., 15:38
 */

#ifndef _DVNCI_GROUPPROCCESSOR_TEMPL
#define	_DVNCI_GROUPPROCCESSOR_TEMPL

#include <kernel/proccesstmpl.h>



namespace dvnci {

    class system_tag {

    public:

        system_tag(executor* exectr, tagsbase_ptr inf, indx idn = npos) : id(idn), intf(inf),
        error_(ERROR_EXPRNOINIT), expression_(""), executr(exectr) {
            ;
        };

        system_tag() : error_(ERROR_EXPRNOINIT), expression_("") {
            ;
        };

        virtual ~system_tag() {
        };

        ns_error error() const {
            return error_;
        }

        std::string expressionstr() const {
            return expression_;
        }

        void execute(indx id) {
            if (intf)
                execute_impl(id);
        }

        virtual bool rebuild_if_need(indx id = npos) {
            return false;
        }

    protected:

        ns_error error(ns_error err) {
            return error_ = err;
        }

        virtual void expressionstr(std::string val) {
            /*lower_and_*/fulltrim(val);
            if (val != expression_) {
                if (!val.empty()) parse(val);
                else error(ERROR_EXPRNOINIT);
                expression_ = val;
            }
        }

        virtual void execute_impl(indx id) = 0;
        virtual void parse(std::string val) = 0;

        indx id;
        tagsbase_ptr intf;
        ns_error error_;
        std::string expression_;
        executor* executr;
    };

    template<typename GROUPITEMTYPE>
    class system_executor : public executor {

    public:

        typedef typename boost::shared_ptr<GROUPITEMTYPE> exprtag_ptr;
        typedef typename std::pair<indx, exprtag_ptr > inx_exprtag_ptr_pair;
        typedef typename std::map<indx, exprtag_ptr, std::less<indx>,
        std::allocator<inx_exprtag_ptr_pair > > inx_exprtag_ptr_map;
        typedef typename inx_exprtag_ptr_map::iterator inx_exprtag_ptr_iterator;

        system_executor(tagsbase_ptr inf, indx groupind, metalink lnk, tagtype provide_man = TYPE_SIMPL) :
        executor(inf, provide_man) {
        }

        virtual bool operator()() {
            boost::xtime xt;
            for (inx_exprtag_ptr_iterator it = tagexpressionmap.begin(); it != tagexpressionmap.end(); ++it) {
                if (terminated()) break;
                boost::xtime xt_loop;
                addmillisec_to_now(xt_loop, 3);
                it->second->execute(it->first);
                boost::thread::sleep(xt_loop);
                addmillisec_to_now(xt, 10);
            }
            return true;
        }

        virtual void optinalchangeid(indx id) {
            DEBUG_STR_VAL_DVNCI(optinalchange, id)
            for (inx_exprtag_ptr_iterator it = tagexpressionmap.begin(); it != tagexpressionmap.end(); ++it) {
                it->second->rebuild_if_need(id);
            }
        }


    protected:

        virtual void add_tags_impl(const indx_set& idset) {
            for (indx_set::const_iterator id = idset.begin(); id != idset.end(); ++id) {
                inx_exprtag_ptr_iterator it = tagexpressionmap.find(*id);
                if (it != tagexpressionmap.end()) {
                    remove_tag(*id);
                }
                exprtag_ptr tmp(new GROUPITEMTYPE(this, intf, *id));
                tagexpressionmap.insert(inx_exprtag_ptr_pair(*id, tmp));
            }
        }

        virtual void remove_tags_impl(const indx_set& idset) {
            for (indx_set::const_iterator id = idset.begin(); id != idset.end(); ++id) {
                inx_exprtag_ptr_iterator it = tagexpressionmap.find(*id);
                if (tagexpressionmap.find(*id) != tagexpressionmap.end()) {
                    tagexpressionmap.erase(it);
                    intf->valid(*id, 0);
                }
            }
        }

        virtual bool initialize() {
            group_state_on();
            return true;
        }

        virtual bool uninitialize() {
            tagexpressionmap.clear();
            group_state_off();
            return true;
        }

        inx_exprtag_ptr_map tagexpressionmap;
    };


}


#endif	/* _DVNCI_GROUPPROCCESSOR_TEMPL */

