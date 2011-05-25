/* 
 * File:   comandcaseexpession.h
 * Author: Serg
 *
 * Created on 18 Июнь 2010 г., 14:10
 */

#ifndef _DVNCI_ALLREPORTITEM
#define	_DVNCI_ALLREPORTITEM

#include <kernel/memfile.h>
#include <kernel/serviceapp.h>
#include <kernel/system_proccesstmpl.h>

#include <dbaccess/dbconnectionfactory.h>



namespace dvnci {

    class reporttype_executor : public system_tag {
    public:

        reporttype_executor(executor* exectr, tagsbase_ptr inf , indx id) :
        system_tag(exectr, inf, id), type(0) {
            if (intf) expressionstr(intf->name(id));};

        static void setdbdriver(dvnci::database::dbdriver_ptr val) {
            dbdriver = val;}

    protected:

        virtual void execute_impl(indx id);
        virtual void parse(std::string val);

    private:

        tagtype                              type;
        static dvnci::database::dbdriver_ptr dbdriver;} ;}



#endif	/* _DVNCI_ALLREPORTITEM */

