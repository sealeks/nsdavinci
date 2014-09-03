/* 
 * File:   expression.h
 * Author: Serg
 *
 * Created on 12 Май 2010 г., 12:50
 */

#ifndef _DVNCI_SYSGROUP_EXPRESSION_H
#define	_DVNCI_SYSGROUP_EXPRESSION_H

#include <kernel/memfile.h>
#include <kernel/constdef.h>
#include <kernel/expression.h>
#include <kernel/system_proccesstmpl.h>

#include <dbaccess/dbconnectionfactory.h>

namespace dvnci {



    ////////////////////////////////////////////////////
    /* expr_executor */
    //////////////////////////////////////////////////

    using dvnci::expr::expression_templ;

    class expr_executor : public system_tag {

        typedef expression_templ<tagsbase> expression;
        typedef boost::shared_ptr<expression> expression_ptr;
        typedef membase_sync_ptr_tmpl<tagsbase> base_ptr;

    public:

        expr_executor(executor* exectr, base_ptr intf, indx id) :
        system_tag(exectr, intf, id), oldactive(false) {
            if (intf) expressionstr(intf->binding(id));
        };

        virtual bool rebuild_if_need(indx idsrc = npos);

    protected:

        virtual void execute_impl(indx idex);
        virtual void parse(std::string val);

    private:
        expression_ptr expressionptr;
        bool oldactive;
    };


    ////////////////////////////////////////////////////
    /* sysreport_executor */
    //////////////////////////////////////////////////

    class sysreport_executor : public system_tag {

        typedef membase_sync_ptr_tmpl<tagsbase> base_ptr;

    public:

        sysreport_executor(executor* exectr, base_ptr inf, indx id = npos) :
        system_tag(exectr, inf, id), type(0),
        sourseid(npos), soursetype(0), counttype(REP_COUNT_NODEF) {
            if (intf) expressionstr(intf->binding(id));
        };

        virtual bool rebuild_if_need(indx idsrc = npos);

        static void setdbdriver(dvnci::database::dbdriver_ptr val) {
            dbdriver = val;
        }

    protected:

        virtual void parse(std::string val);
        virtual void execute_impl(indx idex);
        void readvalue();
        bool checkredy();
        ns_error checktypes();
        bool count_from_localsourse(const datetime& strt, const datetime& stp, double& rslt);

    private:
        tagtype type;
        indx sourseid;
        tagtype soursetype;
        reportsrctype counttype;
        static dvnci::database::dbdriver_ptr dbdriver;
    };


    ////////////////////////////////////////////////////
    /* sysreportcnt_executor */
    //////////////////////////////////////////////////


    namespace expr {

        class report_refcounter {

        public:

            report_refcounter(tagsbase_ptr inf, bool act = false) : intf(inf) {
            }

            virtual ~report_refcounter() {
            }

            void add(indx id) {
                if (countermap.find(id) == countermap.end()) {
                    countermap.insert(id);
                }
            }

            void remove(indx id) {
                if (countermap.find(id) != countermap.end()) {
                    countermap.erase(id);
                }
            }

            bool active() const {
                return true;
            }

            void active(bool val) {
            }

            void clear() {
                countermap.clear();
            }

            bool index_included(indx id) {
                return (countermap.find(id) != countermap.end());
            }

            const indx_set& indexes() const {
                return countermap;
            }


        private:

            void setallactive(bool val) {
            }

            tagsbase_ptr intf;
            indx_set countermap;
        };

        class reportcnt_expression : public expression_templ<tagsbase, report_refcounter> {

        public:

            reportcnt_expression(const std::string& expr, tagsbase_ptr inf) : expression_templ<tagsbase, report_refcounter>(expr, inf) {
            }

            virtual ~reportcnt_expression() {
            };

            double reportvalue(const indx_double_map& vl) {
                valuemap = vl;
                return value_cast<double>();
            }

        protected:

            virtual calc_token getalarm(const calc_token& it) {
                return false;
            }

            virtual calc_token getack(const calc_token& it) {
                return false;
            }

            virtual calc_token getnack(const calc_token& it) {
                return false;
            }

            virtual calc_token assignexpr(const calc_token& it) {
                if (intf) {
                    indx_double_map::const_iterator itr = valuemap.find(it.id());
                    return itr != valuemap.end() ? itr->second : NULL_DOUBLE;
                }
                throw dvncierror(ERROR_NILLINF);
            }

            virtual calc_token assignlastexpr(const calc_token& it) {
                return assignexpr(it);
            }

            indx_double_map valuemap;

        };
    }

    class sysreportcnt_executor : public system_tag {

        typedef dvnci::expr::reportcnt_expression expression;
        typedef boost::shared_ptr<expression> expression_ptr;
        typedef membase_sync_ptr_tmpl<tagsbase> base_ptr;

    public:

        sysreportcnt_executor(executor* exectr, base_ptr inf, indx id) :
        system_tag(exectr, inf, id), type(0) {
            if (intf) expressionstr(intf->binding(id));
        };

        virtual bool rebuild_if_need(indx idsrc = npos);

        static void setdbdriver(dvnci::database::dbdriver_ptr val) {
            dbdriver = val;
        }

    protected:

        virtual void execute_impl(indx idex);
        virtual void parse(std::string val);
        void readvalue();
        bool checkredy();
        ns_error checktypes();

    private:

        tagtype type;
        expression_ptr expressionptr;
        indx_double_map valuemap;
        static dvnci::database::dbdriver_ptr dbdriver;
    };
    ;
}

#endif	/* _EXPRESSION_H */

