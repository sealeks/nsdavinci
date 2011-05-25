/* 
 * File:   mainstruct.cpp
 * Author: Serg
 * 
 * Created on 1 РЎРµРЅС‚СЏР±СЂСЊ 2010 Рі., 20:14
 */

#include <kernel/mainstruct.h>




namespace dvnci {

    tagstruct::tagstruct(indx mid, indx grp) : id_(mid) {
        type(TYPE_NODEF);
        minraw<double>(0);
        maxraw<double>(100);
        mineu<double>(0);
        maxeu<double>(100);
        logdb(0.2);
        devdb(0.0);
        alarmconst<double>(0);
        namepos(0);
        poscomment(0);
        posbinding(0);
        posonmsg(0);
        posoffmsg(0);
        posalarmmsg(0);
        poseu(0);
        alwactive(false);
        unusepos1_ = 0;
        unusepos2_ = 0;
        allwaysactiv_helper_ = 0;
        logged(false);
        onmsged(false);
        offmsged(false);
        group(grp);
        agroup(npos);
        logkey(npos);
        reporthistory(1000);
        reportsubdelt(0);
        reportstatistic(REPORT_STATISTIC_AVER);}

    void tagstruct::reportstatistic(repstattype val) {
        if (!IN_REPORTSET(type())) return;
        num32 tmp = static_cast<repstattype> (val);
        switch (tmp) {
            case REPORT_STATISTIC_AVER:
            case REPORT_STATISTIC_INTEG:
            case REPORT_STATISTIC_SUM:
            case REPORT_STATISTIC_MIN:
            case REPORT_STATISTIC_MAX:
            case REPORT_STATISTIC_MOD:{
                reportstatistic_ = tmp;
                break;}
            default: reportstatistic_ = 0;}}

    repstattype tagstruct::reportstatistic() const {
        if (!IN_REPORTSET(type())) return 0;
        num32 tmp = static_cast<repstattype> (reportstatistic_);
        switch (tmp) {
            case REPORT_STATISTIC_AVER:
            case REPORT_STATISTIC_INTEG:
            case REPORT_STATISTIC_SUM:
            case REPORT_STATISTIC_MIN:
            case REPORT_STATISTIC_MAX:
            case REPORT_STATISTIC_MOD:{
                return tmp;
                break;}}
        return 0;}

    onum tagstruct::landscape_range() const {
        if (IN_REPORTSET(static_cast<tagtype> (type_))) return 3;
        if (!IN_FLOATINGSET(static_cast<tagtype> (type_))) return 0;
        double tmp = std::abs(maxeu<double>() - mineu<double>());
        if (tmp==0) return 0;
        tmp = - std::log10(tmp) + 5;
        tmp = (tmp<0) ? 
            0 :  (tmp> 10) ? 
                10 : tmp;
        return static_cast<onum> (tmp);}

    void tagstruct::clone(tagstruct& dst, const tagstruct& src) {

        dst.minraw_ = src.minraw_;
        dst.maxraw_ = src.maxraw_;
        dst.mineu_ = src.mineu_;
        dst.maxeu_ = src.maxeu_;
        dst.logdb_ = src.logdb_;
        dst.devdb_ = src.devdb_;
        dst.alarmconst_ = src.alarmconst_;
        dst.alwactive_ = src.alwactive_;
        dst.alarmlevel_ = src.alarmlevel_;
        dst.alarmcase_ = src.alarmcase_;
        dst.alwactive_ = src.alwactive_;
        dst.allwaysactiv_helper_ = src.allwaysactiv_helper_;
        dst.type_ = src.type_;
        dst.logged_ = src.logged_;
        dst.onmsged_ = src.onmsged_;
        dst.offmsged_ = src.offmsged_;
        dst.reporthistory_ = src.reporthistory_;
        dst.reportsubdelt_ = src.reportsubdelt_;
        dst.reportstatistic_ = src.reportstatistic_;
        dst.accesslevel_ = src.accesslevel_;
        dst.rwtype_ = src.rwtype_;}

    tagstruct tagstruct::get_for_write_to_file(bool firstcriteria) {
        tagstruct dst = *this;
        dst.error(0);
        dst.refcnt(0);
        dst.alarmkvit(false);
        dst.alarmon(false);
        dst.time_log_n64(0);
        dst.time_n64(0);
        dst.value_log<num64 > (0);
        dst.value_before<num64 > (0);
        dst.logkey(npos);
        if (!firstcriteria) {
            switch (alarmcase()) {
                case alarmEqual:{
                    if (alarmconst<num64 > () == 0) {
                        dst.value<num64 > (1);} else {
                        dst.value<num64 > (0);}
                    break;}
                default:{
                    dst.value<num64 > (alarmconst<num64 > ());
                    break;}}
            dst.time_n64(0);
            dst.valid(NULL_VALID);} 
        else {
            dst.valid(FULL_VALID);}
        monitor_=0;}


    ///////////////////////////////////////////////////////////////// 

    tagsstruct_hdr::tagsstruct_hdr(lcltype loc) {
        version_ = DVNCI_VERSION;
        headersize_ = static_cast<num64> (sizeof (tagsstruct_hdr));
        recordsize_ = static_cast<num64> (sizeof (tagstruct));
        count_ = static_cast<num64> (0);
        datasize_ = static_cast<num64> (sizeof (tagsstruct_hdr)) + 0 * static_cast<size_t> (sizeof (tagstruct));
        local_ = static_cast<num64> (loc);
        monitor_ = 0;
        debuglevel_ = static_cast<num64> (DEBUGLEVEL_LOW);
        posname_ = 0;
        poscomment_ = 0;
        dbprovider_ = 0;
        posdbstring_ = 0;
        analogbuf_ = 0;
        bddepth_ = 0;
        posadmin_ = 0;
        pospass_ = 0;
        posadminport_ = 0;
        posremoteport_ = 0;
        posopcport_ = 0;
        os_type_ = 0;
        texttagcnt_ = 0;
        archtagcnt_ = 0;
        reporttagcnt_ = 0;
        n_use1 = 0;
        n_use2 = 0;
        n_use3 = 0;}

    tagsstruct_hdr::tagsstruct_hdr(const tagsstruct_hdr & src) {
        version_ = src.version_;
        headersize_ = src.headersize_;
        recordsize_ = src.recordsize_;
        count_ = src.count_;
        datasize_ = src.datasize_;
        local_ = src.local_;
        monitor_ = static_cast<num64> (0);
        debuglevel_ = src.debuglevel_;
        posname_ = src.posname_;
        poscomment_ = src.poscomment_;
        dbprovider_ = src.dbprovider_;
        posdbstring_ = src.posdbstring_;
        analogbuf_ = src.analogbuf_;
        bddepth_ = src.bddepth_;
        posadmin_ = src.posadmin_;
        pospass_ = src.pospass_;
        posadminport_ = src.posadminport_;
        posremoteport_ = src.posremoteport_;
        posopcport_ = src.posopcport_;
        texttagcnt_ = src.texttagcnt_;
        archtagcnt_ = src.archtagcnt_;
        reporttagcnt_ = src.reporttagcnt_;
        os_type_ = 0;
        n_use1 = 0;
        n_use2 = 0;
        n_use3 = 0;}

    tagsstruct_hdr& tagsstruct_hdr::operator=(const tagsstruct_hdr & src) {
        version_ = src.version_;
        headersize_ = src.headersize_;
        recordsize_ = src.recordsize_;
        count_ = src.count_;
        datasize_ = src.datasize_;
        local_ = src.local_;
        monitor_ = static_cast<num64> (0);
        debuglevel_ = src.debuglevel_;
        posname_ = src.posname_;
        poscomment_ = src.poscomment_;
        dbprovider_ = src.dbprovider_;
        posdbstring_ = src.posdbstring_;
        analogbuf_ = src.analogbuf_;
        bddepth_ = src.bddepth_;
        posadmin_ = src.posadmin_;
        pospass_ = src.pospass_;
        posadminport_ = src.posadminport_;
        posremoteport_ = src.posremoteport_;
        posopcport_ = src.posopcport_;
        texttagcnt_ = src.texttagcnt_;
        archtagcnt_ = src.archtagcnt_;
        reporttagcnt_ = src.reporttagcnt_;
        os_type_ = 0;
        n_use1 = 0;
        n_use2 = 0;
        n_use3 = 0;
        return *this;}

    void tagsstruct_hdr::count(size_t val) {
        if (val < 0) return;
        count_ = static_cast<num64> (val);
        datasize_ = static_cast<num64> (sizeof (tagsstruct_hdr)) + count_ * static_cast<num64> (sizeof (tagstruct));
        monitor_++;}



    ///groupstruct

    groupstruct::groupstruct(indx mid) : id_(mid) {
        trycount(3);
        namepos(0);
        unusetype_ = static_cast<num64> (TYPE_DISCRET);
        time_n64(0);
        hostpos(0);
        serverpos(0);
        userpos(0);
        passpos(0);
        grouppos(0);
        portpos(0);
        etherpos(0);
        topicpos(0);
        strpos1(0);
        strpos2(0);
        strpos3(0);
        strpos4(0);
        strpos5(0);
        strpos6(0);}

    tagsstruct_hdr & tagsstruct_hdr::operator++() {
        count_++;
        datasize_ = static_cast<unum64> (sizeof (tagsstruct_hdr)) + count_ * static_cast<unum64> (sizeof (tagstruct));
        monitor_++;
        return *this;}

    tagsstruct_hdr & tagsstruct_hdr::operator++(int) {
        count_++;
        datasize_ = static_cast<unum64> (sizeof (tagsstruct_hdr)) + count_ * static_cast<unum64> (sizeof (tagstruct));
        monitor_++;
        return *this;}

    groupstruct groupstruct::get_for_write_to_file(bool firstcriteria) {
        groupstruct dst = *this;
        dst.error(0);
        dst.active(firstcriteria ? 1 : 0);
        dst.valid(firstcriteria ? FULL_VALID : 0);
        monitor_=0;}

    void groupstruct::clone(groupstruct& dst, const groupstruct& src) {
        dst.appid_ = src.appid_;
        dst.time_ = 0;
        dst.unusetype_ = static_cast<num64> (TYPE_DISCRET);
        dst.chanaltype_ = src.chanaltype_;
        dst.chanalnum_ = src.chanalnum_;
        dst.devspec_ = src.devspec_;
        dst.devnum_ = src.devnum_;
        dst.protocol_ = src.protocol_;
        dst.portnum_ = src.portnum_;
        dst.timeout_ = src.timeout_;
        dst.deadbound_ = src.deadbound_;
        dst.grouprate_ = src.grouprate_;
        dst.utiloperation_ = src.utiloperation_;
        dst.blocksize_ = src.blocksize_;
        dst.archblocksize_ = src.archblocksize_;
        dst.trycount_ = src.trycount_;
        dst.indicateto_ = src.indicateto_;
        dst.tcpport_ = src.tcpport_;
        dst.local_ = src.local_;
        dst.synctype_ = src.synctype_;
        dst.ver_ = src.ver_;
        dst.supporttype_ = src.supporttype_;
        memcpy(dst.config_, src.config_, GROP_CONFIG_SIZE);}

    bool baudratevalid(baudratetype vl) {
        switch (vl) {
            case NT_RS_DOUNDRATE_110:
            case NT_RS_DOUNDRATE_300:
            case NT_RS_DOUNDRATE_600:
            case NT_RS_DOUNDRATE_1200:
            case NT_RS_DOUNDRATE_2400:
            case NT_RS_DOUNDRATE_4800:
            case NT_RS_DOUNDRATE_9600:
            case NT_RS_DOUNDRATE_14400:
            case NT_RS_DOUNDRATE_19200:
            case NT_RS_DOUNDRATE_38400:
            case NT_RS_DOUNDRATE_56000:
            case NT_RS_DOUNDRATE_57600:
            case NT_RS_DOUNDRATE_115200:
            case NT_RS_DOUNDRATE_128000:
            case NT_RS_DOUNDRATE_256000: return true;}
        return false;}


    //metalink

    metalink::metalink(const groupstruct & src, indx idn, const std::string& hst,
            const std::string& usr,
            const std::string& pass,
            const std::string& serv,
            const std::string& grp,
            const std::string& prt,
            const std::string& ethr,
            const std::string& tpc) :
    id_(idn), appid_(0), host_(hst), user_(usr), password_(pass), server_(serv), group_(grp), port_(prt), ether_(ethr), topic_(tpc) {

        chanaltype_ = src.chanaltype();
        appid_ = src.appid();
        protocol_ = src.protocol();
        blocksize_ = src.blocksize();
        archblocksize_ = src.archblocksize();
        timeout_ = src.timeout();
        indicateto_ = src.indicateto();
        chanalnum_ = src.chanalnum();
        portnum_ = src.portnum();
        devnum_ = src.devnum();
        switch (chanaltype_) {
            case NT_CHTP_RS232_4XX:{
                inf_.cominf.boundrate = static_cast<const rs232_property*> (src.config())->baudrate();
                inf_.cominf.parity = static_cast<const rs232_property*> (src.config())->parity();
                inf_.cominf.stopbit = static_cast<const rs232_property*> (src.config())->stopbit();
                inf_.cominf.flowcontrol = static_cast<const rs232_property*> (src.config())->flowcontrol();
                inf_.cominf.flowcontrolaftersleep = static_cast<const rs232_property*> (src.config())->flowcontrolaftersleep();
                inf_.cominf.flowcontrolbeforesleep = static_cast<const rs232_property*> (src.config())->flowcontrolbeforesleep();
                inf_.cominf.readinterval = static_cast<const rs232_property*> (src.config())->readinterval();
                inf_.cominf.rtm = static_cast<const rs232_property*> (src.config())->rtm();
                inf_.cominf.rtc = static_cast<const rs232_property*> (src.config())->rtc();
                inf_.cominf.wtm = static_cast<const rs232_property*> (src.config())->wtm();
                inf_.cominf.wtc = static_cast<const rs232_property*> (src.config())->wtc();
                break;}
            case NT_CHTP_UDP_IP:
            case NT_CHTP_TCP_IP:{
                break;}
            default:{}}}

    bool operator==(const metalink& ls, const metalink & rs) {
        if (ls.appid() != rs.appid()) return false;
        if (ls.chanaltype_ != rs.chanaltype_) return false;
        if (ls.chanaltype_ == NT_CHTP_RS232_4XX) {
            return (ls.chanalnum_ == rs.chanalnum_);}
        if (ls.id_ == rs.id_) {
            return true;}
        return false;}

    bool operator!=(const metalink& ls, const metalink & rs) {
        return (!operator==(ls, rs));}

    bool operator<(const metalink& ls, const metalink & rs) {
        if (ls.appid() != rs.appid()) return ls.appid() < rs.appid();
        if (ls.chanaltype_ != rs.chanaltype_) return ls.chanaltype_ < rs.chanaltype_;
        if (ls.chanaltype_ == NT_CHTP_RS232_4XX) return ls.chanalnum_ < rs.chanalnum_;
        return (ls.id_ < rs.id_);}

    ns_error metalink_checker::operator()(const metalink_vect & mlvect) {
        ns_error rslt = 0;
        if (mlvect.size() < 2) return 0;
        metalink_vect::const_iterator itnext;
        for (metalink_vect::const_iterator it = mlvect.begin(); it != mlvect.end();) {
            itnext = it;
            if ((++it) != mlvect.end()) rslt = compare(*it, *itnext);
            if (rslt) return rslt;}
        return 0;}

    //agroupstruct

    agroupstruct::agroupstruct(indx mid) : id_(mid) {
        unusevalue_ = 0;
        unusetime_ = 0;
        unusetype_ = 0;
        unusevalid_ = 100;
        unuseerror_ = 0;
        notuse1 = 0;
        notuse2 = 0;
        namepos(0);
        headernamepos(0);}

    agroupstruct agroupstruct::get_for_write_to_file(bool firstcriteria) {
        return *this;}


    // userstruct

    userstruct::userstruct(indx mid) : id_(mid) {
        accesslevel(0);
        namepos(0);
        passpos(0);}

    userstruct userstruct::get_for_write_to_file(bool firstcriteria) {
        return *this;}


    // userstruct

    accessrulestruct::accessrulestruct(indx mid) : id_(mid) {
        namepos(0);
        cidrpos(0);
        apppos(0);
        unusepos1_ = 0;
        unusepos2_ = 0;
        appid(0);
        accesslevel(0);
        rule(0);}

    accessrulestruct accessrulestruct::get_for_write_to_file(bool firstcriteria) {
        return *this;}


    // journalstruct

    journalstruct::journalstruct(guidtype gid, const datetime& tm, indx tgid, msgtype tp,
            altype lev, indx agrp, double val, indx userid) {
        guid_ = static_cast<unum64> (gid);
        time_ = castnum64_from_datetime(tm);
        tagid_ = static_cast<num64> (tgid);
        type_ = static_cast<num64> (tp & 7);
        level_ = static_cast<num32> (lev & 3);
        user_ = static_cast<num64> (userid);
        value_ = static_cast<num64> (val);}



    // debugstruct    

    debugstruct::debugstruct(guidtype gid, const datetime& tm, const std::string& msg,
            debuglvtype lev, appidtype app) {
        guid_ = static_cast<unum64> (gid);
        time_ = castnum64_from_datetime(tm);
        level_ = static_cast<num64> (lev & 3);
        appid_ = static_cast<num64> (app);
        string_to_pascalstr((void*) &debugmessage_, msg, LOGMESSAGE_STRINGSIZE);}



    // debugstruct 

    alarmsstruct::alarmsstruct(guidtype gid, datetime tm, indx tgid, msgtype tp, altype lev,
            indx grp, indx agrp, const double& val) {
        guid_ = static_cast<unum64> (gid);
        group_ = static_cast<num64> (grp);
        agroup_ = static_cast<num64> (agrp);
        tagid_ = static_cast<num64> (tgid);
        time(tm);
        kvit(false);
        off(false);
        level(lev);
        type(tp);
        value_ = static_cast<num64> (val);}



    // registrystruct 

    registrystruct::registrystruct(guidtype gid, appidtype app, eventtypeset evs, guidtype hndl) {
        guid_ = static_cast<unum64> (gid);
        eventsset_ = static_cast<num64> (evs);
        appid_ = static_cast<num64> (app);
        handle_ = static_cast<unum64> (hndl);}




    // commandstruct 

    commandstruct::commandstruct(guidtype gid, indx tgid, indx grp, num64 val_b,
            num64 val_s, guidtype clid, tagtype tp) {
        guid_ = static_cast<unum64> (gid);
        tagid_ = static_cast<num64> (tgid);
        type(tp);
        clientid(clid);
        executed(false);
        group(grp);
        value_before<num64 > (val_b);
        value_set<num64 > (val_s);
        istext(false);}

    commandstruct::commandstruct(guidtype gid, indx tgid, indx grp, const std::string& vl,
            guidtype clid) {
        guid_ = static_cast<unum64> (gid);
        tagid_ = static_cast<num64> (tgid);
        clientid(clid);
        type(TYPE_TEXT);
        executed(false);
        group(grp);
        value_before<num64 > (0);
        value_set<num64 > (0);
        strvalue(vl);
        istext(true);}

    void commandstruct::reset_commandstruct(num64 val_s, guidtype clid) {
        value_set<num64 > (val_s);
        istext(false);
        if (clid != NULL_CLIENT) clientid(clid);
        executed(false);}

    void commandstruct::reset_commandstruct(const std::string& vl, guidtype clid) {
        istext(true);
        strvalue(vl);
        if (clid != NULL_CLIENT) clientid(clid);
        executed(false);}




    // commandstruct 

    clientstruct::clientstruct(guidtype gid, appidtype app, acclevtype lev, const std::string& hst,
            const std::string& ip_, const std::string& usernm_, indx clid) {
        guid_ = static_cast<unum64> (gid);
        accesslevel(lev);
        appid(app);
        host(hst);
        user(clid);
        username(usernm_);
        ip(ip_);}

}

