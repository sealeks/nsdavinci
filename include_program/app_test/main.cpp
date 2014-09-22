/* 
 * File:   main.cpp
 * Author: Serg Alexeev sealeks@mail.ru Alexeev sealeks@mail.ru
 *
 * Created on 22 Февраль 2010 г., 0:30
 */

#include <kernel/constdef.h>
#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/service.h>
#include <kernel/proccesstmpl.h>

using namespace dvnci;
using namespace std;

dvnci::executable_ptr     dvnci::mainserv;
std::string               dvnci::DVNCI_SERVICE_NAME = NS_TEST_SERVICE_NAME;
dvnci::appidtype          dvnci::DVNCI_SERVICE_APPID= NS_TEST_SERVICE;

fspath                    basepath;

double randomgenerator(){
    return (1.0 * rand()) / RAND_MAX;
}

double normalgenerator(double d){
    return d * ( randomgenerator() /** randomgenerator()* randomgenerator() * randomgenerator() * randomgenerator()*/ -0.5) * 2;
}


double timeval() {
    dvnci::datetime tm = dvnci::now();
    dvnci::normalizeperiod(tm, DAY_TM);
    return (1.0 * secondsbetween(tm, dvnci::now())) / 60 * 2  * 3.1415;}

struct thread_rep {

    thread_rep(dvnci::tagsbase_ptr inf, dvnci::indx ids) : intf(inf), id(ids) {}

    void operator()() {
        while (true) {
            boost::xtime xt;
            boost::xtime_get(&xt, boost::TIME_UTC_);
            xt.nsec += 300000;
            if (intf->exists(id)) {
                switch (intf->valid(id)) {
                    case REPORT_NOACTIVE:{
                        intf->valid(id, REPORT_NEEDKHOWDEEP);
                        break;}
                    case REPORT_NEEDREQUEST:
                    case REPORT_WAITSOURCE:{
                        tmpmap.clear();
                        datetime strttmp = intf->time_log(id);
                        if (!strttmp.is_special()) {
                            datetime stptmp = now();
                            unum64 it = 0;
                            while (incminute(strttmp, it) < stptmp) {
                                datetime dtt = incminute(strttmp, it++);
                                tmpmap.insert(dt_val_pair(dtt, dtt.time_of_day().minutes()));}}
                        if (!tmpmap.empty())
                            intf->write_vals_report(id, tmpmap);
                        break;}}}
            boost::thread::sleep(xt);}}

    dt_val_map tmpmap;
    dvnci::tagsbase_ptr intf;
    dvnci::indx id;} ;

struct thread_log {
private:
    dvnci::tagsbase_ptr intf;
    volatile bool  terminate_;


public:

    void terminate() {
        terminate_ = false;}

    thread_log () : terminate_(true) {
        terminate_ = true;}

    ~thread_log () {
        terminate_ = false;}

    bool init() {
        return intf;}

    void inited(dvnci::tagsbase_ptr intf_) {
        intf = intf_;}

    void operator()() {
        cout << "in operator ()" << endl;
        while (terminate_) {
            boost::xtime xt;
            boost::xtime_get(&xt, boost::TIME_UTC_);
            if (init()) {{
                    THD_EXCLUSIVE_LOCK(intf);
                    for (indx i = 0; i < intf->count(); i++)
                        if (intf->exists(i)) {
                            if ((!IN_REPORTSET(intf->type(i))) && (intf->groups()->appid(intf->group(i)) == 0)) {
                                if (intf->type(i) == EVENT_TYPE_WITHTIME) {
                                    if ((rand() % 2) == 0) intf->write_val_event(i, now());}
                                else {
                                    if (!intf->alarmed(i)) {
                                        if (intf->type(i) <= 0xF) {
                                            double tmpMaxEu = str_to<double>(intf->maxeu(i));
                                            double tmpMinEu = str_to<double>(intf->mineu(i));
                                            double tmpBnd = (tmpMaxEu-tmpMinEu);
                                            double tmpDif = (tmpMaxEu-tmpMinEu) * 0.005;
                                            double tmpEu = timeval() / ((i %  5) *20 + 4);
                                            double tmpcur = (!intf->valid(i)) ? ((tmpMaxEu-tmpMinEu) / 2) : intf->value<double>(i);
                                            //std::cout << tmpDif << "  "  <<  normalgenerator(tmpDif) << std::endl;    
                                            tmpEu = tmpcur + normalgenerator(tmpDif);/*tmpMinEu + (sin(tmpEu) + 1) / 2 * (tmpMaxEu - tmpMinEu)*/;
                                            intf->write_val(i, tmpEu, 100);}}
                                    else {
                                        if (intf->alarmed(i)) {
                                            if (str_to<double>(intf->alarmconst(i)) == intf->value<double>(i))
                                                intf->write_val(i, intf->value<double>(i) + 1.0, 100);
                                            else
                                                intf->write_val(i, str_to<double>(intf->alarmconst(i)), 100);}}}}
                            else {
                                if ((IN_REPORTSET(intf->type(i))) && (intf->name(i) == "reptest::w")) {
                                    switch (intf->valid(i)) {
                                        case REPORT_NOACTIVE:{
                                            intf->valid(i, REPORT_NEEDKHOWDEEP);
                                            break;}
                                        case REPORT_NEEDREQUEST:
                                        case REPORT_WAITSOURCE:{
                                            datetime strttmp = intf->time_log(i);
                                            datetime stptmp = now();
                                            dt_val_map tmpmap;
                                            unum64 it = 0;
                                            while (incminute(strttmp, it) < stptmp) {
                                                datetime dtt = incminute(strttmp, it++);
                                                tmpmap.insert(dt_val_pair(dtt, dtt.time_of_day().minutes()));}
                                            if (!tmpmap.empty())
                                                intf->write_vals_report(i, tmpmap);
                                            break;}}}}}}}
            addmillisec_to_now(xt, 600);
            boost::thread::sleep(xt);}}} ;

class testbaseservice : public basisservice {
public:

    testbaseservice() : basisservice(basepath, 0,
    NS_TEST_SERVICE)   {}

    typedef intrusivesync_callable_shared_ptr<thread_log> callable_ptr;

protected:

    callable_ptr        log1;
    boost::thread_group threads;

    virtual bool initialize_impl() {
        thread_log* tmp = new thread_log();
        log1 = callable_ptr( tmp);
        tmp->inited(intf);
        threads.create_thread(log1);
        return true;}

    virtual bool uninitialize_impl() {
        log1->terminate();
        threads.join_all();
        log1.reset();
        return true;}} ;

int main(int argc, char** argv) {
    std::string quit_in;
    basepath = dvnci::getlocalbasepath();
    DEBUG_VAL_DVNCI(basepath.string())
    mainserv = executable_ptr(new testbaseservice());
#ifndef DVNCI_DEDUG
    if (serviceargumentparser(argc, argv) == SERVICE_OPEATION_APP) {
#endif
        try {
            DEBUG_STR_DVNCI(start app)
            boost::thread th = boost::thread(mainserv);
            while ((std::cin >> quit_in)  && ((quit_in != "q") && (quit_in != "Q")));
            mainserv.terminate();
            th.join();}
        catch (std::exception& err) {
            DEBUG_VAL_DVNCI(err.what());}
#ifndef DVNCI_DEDUG
    /**/;}
#endif
    DEBUG_STR_DVNCI(FIN)
    return (EXIT_SUCCESS);}

