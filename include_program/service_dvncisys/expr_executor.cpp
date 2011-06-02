/* 
 * File:   expression.cpp
 * Author: Serg
 * 
 * Created on 12 Май 2010 г., 12:50
 */

#include "expr_executor.h"

namespace dvnci {


    ////////////////////////////////////////////////////
    /* expr_executor */
    ///////////////////////////////////////////////////

    using namespace dvnci::expr;

    void expr_executor::execute_impl(indx idex) {
        if (expressionptr) {
            if (!intf->refcnt(idex)) {
                if (oldactive)
                    expressionptr->active(oldactive = false);}
            else {
                if (!oldactive)
                    expressionptr->active(oldactive = true);
                if (executr) {
                    if (!error()) {
                        short_value tmp = expressionptr->value();
                        if (!error(expressionptr->error()))
                            executr->write_val(idex, tmp);
                        else
                            executr->error(idex, error());}
                    else {
                        executr->error(idex, error());}}}}}

    void expr_executor::parse (std::string val) {
        DEBUG_STR_VAL_DVNCI(PARSE, val)
        expressionptr = expression_ptr(new expression(val, intf));
        if (error(expressionptr->testerror()))
            intf->debugwarning("Binding error id=" + intf->name(id) + " bind=" + val);}

    bool expr_executor::rebuild_if_need(indx id) {
        if ((expressionptr) && (expressionptr->rebuild_if_need(id))) {
            error(0);
            oldactive = false;
            return true;}
        return false;}



    using namespace dvnci::database;

    ////////////////////////////////////////////////////
    /* sysreportcnt_executor */
    ///////////////////////////////////////////////////

    dbdriver_ptr sysreport_executor::dbdriver = dbdriver_ptr();

    bool sysreport_executor::rebuild_if_need(indx idsrc) {
        if ((error()) || (idsrc == npos) || (sourseid == idsrc)) {
            error(0);
            intf->error(id, 0);
            intf->time(id, nill_time);
            intf->time_log(id, nill_time);
            parse(expressionstr());
            return true;}
        return false;}

    void sysreport_executor::execute_impl(indx idex) {
        if (executr) {
            if (error()) {
                executr->error(idex, error());}
            else {
                if (dbdriver) {
                    THD_EXCLUSIVE_LOCK(dbdriver);
                    if (!dbdriver->isconnected()) {
                        dbdriver->connect();
                        if (!dbdriver->isconnected()) {
                            DEBUG_STR_DVNCI(FIND_DISCONNECTION)
                            executr->set_group_state(npos, ERROR_NO_DATABASE_CONN, FULL_VALID);
			    return;}}
                    executr->set_group_state(npos, 0);
                    if ((checkredy()) && (executr->report_requested(idex))) {
                        readvalue();}}}}}

    void sysreport_executor::parse (std::string val) {
        error(0);
        DEBUG_VAL_DVNCI(val)
        if ((!intf) || (!intf->exists(id)) || (!intf->exists(val))) {
            sourseid = npos;
            type = 0;
            error(ERROR_BINDING);
            return;}
        else {
            sourseid = intf(val);
            soursetype = intf->type(sourseid);
            type = intf->type(id);
            if (!checktypes()) {
                DEBUG_STR_VAL_DVNCI(SUSCCESSBIND, id);
                DEBUG_STR_VAL_DVNCI(BIND, val);}}}

    void sysreport_executor::readvalue() {
        if (dbdriver->isconnected()) {
            datetime stoptm = intf->time_log(id);
            normalizereporttime(stoptm, intf->type(id));
            datetime starttm = stoptm;
            increporttime(starttm, intf->type(id), -1);
            double retval = 0;
            if ((count_from_localsourse(starttm, stoptm, retval)) ||
                    (dbdriver->select_statistic(counttype, sourseid, intf->type(sourseid), starttm, stoptm, intf->reportstatistic(id), retval))) {
                executr->write_val_report(id, stoptm, retval);}}}

    bool sysreport_executor::count_from_localsourse(const datetime& strt, const datetime& stp , double& rslt) {
        rslt = NULL_DOUBLE;
        if (intf->exists(sourseid)) {
            dt_val_map tmpvals;
            switch (counttype) {
                case REP_COUNT_BY_LOG:{
                    datetime stp1 = incmillisecond(stp, -1);
                    datetime stp1_lst = stp1;
                    increporttime(stp1_lst, intf->type(id), 1);
                    if ((intf->select_trendbuff(sourseid, tmpvals, strt, stp1_lst > now() ? nill_time : stp1))) {
                        dt_val_map::iterator it = tmpvals.begin();
                        while (it != tmpvals.end()) {
                            if (it->second != it->second)
                                tmpvals.erase(it++);
                            else
                                ++it;}
                        if (tmpvals.empty()) return true;
                        if (intf->reportstatistic(id) == REPORT_STATISTIC_INTEG) {
                            dt_val_pair strtval = std::make_pair(strt, tmpvals.begin()->second);
                            dt_val_pair stpval = std::make_pair(stp, tmpvals.rbegin()->second);
                            tmpvals.insert(strtval);
                            tmpvals.insert(stpval);
                            integr_statistic_functor stfctr(strtval);
                            std::for_each<dt_val_map::const_iterator, integr_statistic_functor&>(tmpvals.begin(), tmpvals.end(), stfctr);
                            rslt = stfctr.countedvalue();
                            DEBUG_STR_VAL_DVNCI(COUNTBYLOCALBUFFER INTEGR TREND, rslt);
                            return true;}
                        else {
                            statistic_functor stfctr(intf->reportstatistic(id));
                            std::for_each<dt_val_map::const_iterator, statistic_functor&>(tmpvals.begin(), tmpvals.end(), stfctr);
                            rslt = stfctr.countedvalue();
                            DEBUG_STR_VAL_DVNCI(COUNTBYLOCALBUFFER TREND, rslt);
                            return true;}}
                    return false;}
                case REP_COUNT_BY_REP:{
                    datetime strt1 = incsecond(strt);
                    if ((intf->select_reportbuff(sourseid, tmpvals, strt1, stp))) {
                        dt_val_map::iterator it = tmpvals.begin();
                        while (it != tmpvals.end()) {
                            if (it->second != it->second)
                                tmpvals.erase(it++);
                            else
                                ++it;}
                        if (tmpvals.empty()) return true;
                        statistic_functor stfctr(intf->reportstatistic(id) == REPORT_STATISTIC_INTEG ?
                            REPORT_STATISTIC_SUM : intf->reportstatistic(id));
                        std::for_each<dt_val_map::const_iterator, statistic_functor&>(tmpvals.begin(), tmpvals.end(), stfctr);
                        rslt = stfctr.countedvalue();
                        DEBUG_STR_VAL_DVNCI(COUNTBYLOCALBUFFER REPORT, rslt);
                        return true;}
                    return false;}
                default:{
                    return false;}}}
        return false;}

    bool sysreport_executor::checkredy() {
        if ((!intf) || (sourseid == npos)) return false;
        return (intf->valid_as_reportsource(sourseid));}

    ns_error sysreport_executor::checktypes() {

        if (!IN_REPORTSET(soursetype)) {
            if (!intf->logged(sourseid)) {
                return error(ERROR_BINDING);}
            else {
                counttype = REP_COUNT_BY_LOG;}}
        else {
            counttype = REP_COUNT_BY_REP;}

        if (counttype == REP_COUNT_NODEF) {
            return error(ERROR_BINDING);}

        if (counttype == REP_COUNT_BY_LOG) {
            error(0);
            switch (type) {
                case REPORTTYPE_YEAR:
                case REPORTTYPE_DEC:
                case REPORTTYPE_DAY:
                case REPORTTYPE_MONTH:
                case REPORTTYPE_QVART:
                case REPORTTYPE_CUSTOM:
                case REPORTTYPE_NONE:{
                    return error(ERROR_BINDING);}}
            return error();}
        else {
            error(0);
            switch (type) {
                case REPORTTYPE_YEAR:{
                    switch (soursetype) {
                        case  REPORTTYPE_DEC:
                        case  REPORTTYPE_DAY:
                        case  REPORTTYPE_QVART:
                        case  REPORTTYPE_MONTH:{
                            return error();}}
                    break;}

                case  REPORTTYPE_MIN:{
                    break;}

                case  REPORTTYPE_HOUR:{
                    switch (soursetype) {
                        case  REPORTTYPE_MIN:
                        case  REPORTTYPE_10MIN:
                        case  REPORTTYPE_30MIN:{
                            return error();}}
                    break;}

                case REPORTTYPE_DEC:{
                    switch (soursetype) {
                        case  REPORTTYPE_DAY:{
                            return error();}
                            break;}}

                case REPORTTYPE_DAY:{
                    switch (soursetype) {
                        case  REPORTTYPE_MIN:
                        case  REPORTTYPE_10MIN:
                        case  REPORTTYPE_HOUR:
                        case  REPORTTYPE_30MIN:{
                            return error();}}
                    break;}

                case REPORTTYPE_MONTH:{
                    switch (soursetype) {
                        case  REPORTTYPE_DEC:
                        case  REPORTTYPE_DAY:
                        case  REPORTTYPE_HOUR:
                        case  REPORTTYPE_30MIN:{
                            return error();}}
                    break;}

                case  REPORTTYPE_10MIN:{
                    switch (soursetype) {
                        case  REPORTTYPE_MIN:{
                            return error();}}
                    break;}

                case  REPORTTYPE_30MIN:{
                    switch (soursetype) {
                        case  REPORTTYPE_MIN:
                        case  REPORTTYPE_10MIN:{
                            return error();}}
                    break;}

                case REPORTTYPE_QVART:{
                    switch (soursetype) {
                        case  REPORTTYPE_DEC:
                        case  REPORTTYPE_DAY:
                        case  REPORTTYPE_MONTH:{
                            return error();}}
                    break;}}}
        return error(ERROR_BINDING);}





    ////////////////////////////////////////////////////
    /* sysreportcnt_executor */
    ///////////////////////////////////////////////////

    dbdriver_ptr sysreportcnt_executor::dbdriver = dbdriver_ptr();

    void sysreportcnt_executor::execute_impl(indx idex) {
        if (executr) {
            if (error()) {
                executr->error(idex, error());}
            else {
                if (dbdriver) {
                    THD_EXCLUSIVE_LOCK(dbdriver);
                    if (!dbdriver->isconnected()) {
                        dbdriver->connect();
                        if (!dbdriver->isconnected()) {
                            executr->set_group_state(npos, ERROR_NO_DATABASE_CONN, FULL_VALID);
                            return;}}
                    executr->set_group_state(npos, 0);
                    if ((checkredy()) && (executr->report_requested(idex))) {
                        readvalue();}}}}}

    void sysreportcnt_executor::parse (std::string val) {
        error(0);
        DEBUG_STR_VAL_DVNCI(PARSEREPORTCOUNT, val)
        if ((!intf) || (!intf->exists(id))) {
            type = 0;
            error( ERROR_BINDING);
            return ;}
        type=intf->type(id);
        expressionptr = expression_ptr(new expression(val, intf));
        if ((checktypes()) || (error(expressionptr->testerror()))) {
            intf->debugwarning("Binding error id=" + intf->name(id) + " bind=" + val);}}

    void sysreportcnt_executor::readvalue() {
        if (dbdriver->isconnected()) {
            dvnci::datetime tmreq = intf->time_log(id);
            normalizereporttime(tmreq, intf->type(id));
            double retval = 0;
            if ((intf->select_reportvals_by_time(tmreq, valuemap )) || (dbdriver->select_reports(type, tmreq, valuemap))) {
                retval = expressionptr->reportvalue(valuemap);
                DEBUG_STR_VAL_DVNCI(PARSEREPORTCOUNT_VALUE, retval)
                executr->write_val_report(id, tmreq, retval);}}}

    bool sysreportcnt_executor::checkredy() {
        if ((!intf) || (!expressionptr)) return false;
        for (indx_set::const_iterator it = expressionptr->indexes().begin(); it != expressionptr->indexes().end(); ++it) {
            if (!intf->valid_as_reportsource(*it)) return false;}
        return true;}

    ns_error  sysreportcnt_executor::checktypes() {
        if (!expressionptr) return ERROR_EXPRPARSE;
        valuemap.clear();
        for (indx_set::const_iterator it = expressionptr->indexes().begin(); it != expressionptr->indexes().end(); ++it) {
            if (!intf->exists(*it)) {
                return error(ERROR_BINDING);}
            if (intf->type(*it) != type) {
                return error(ERROR_BINDING);}
            valuemap.insert(std::make_pair(*it, NULL_DOUBLE));}
        return error();}

    bool sysreportcnt_executor::rebuild_if_need(indx idsrc) {
        if ((expressionptr) && (expressionptr->rebuild_if_need(id))) {
            error(0);
            intf->error(id, 0);
            intf->time(id, nill_time);
            intf->time_log(id, nill_time);
            parse(expressionstr());
            return true;}
        return false;}

}
