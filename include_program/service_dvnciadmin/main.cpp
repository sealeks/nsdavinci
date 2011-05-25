/* 
 * File:   main.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 9 Январь 2010 г., 1:20
 */

//#define IS_DVNCI_SERVICE


#include <admin/factory.h>
#include <admin/adminsession.h>

#include "kernel/constdef.h"
#include <kernel/memfile.h>
#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>


using namespace dvnci;
using namespace dvnci::admin;
using namespace std;

std::string remote_port = DEFAULT_ADMIN_PORT;



using boost::asio::ip::tcp;

dvnci::executable_ptr   dvnci::mainserv;
std::string                   dvnci::dvnciservicename = NS_ADMIN_SERVICE_NAME;
boost::asio::io_service       io_service;
fspath                        basepath;

class ns_adminserver {
public:

    void setIntf(adminintf_ptr intf_) {
        intf = intf_;}

    bool isIntf() {
        return (intf);}

    ns_adminserver(boost::asio::io_service& io_service,
            const tcp::endpoint& endpoint, adminintf_ptr intf_)
    : io_service_(io_service),
    acceptor_(io_service, endpoint) {
        intf = intf_;
        ns_adminsession_ptr new_session(new adminsession(io_service_, intf_));
        acceptor_.async_accept(new_session->socket(),
                boost::bind(&ns_adminserver::handle_accept, this, new_session,
                boost::asio::placeholders::error));}

    void handle_accept(ns_adminsession_ptr session,
            const boost::system::error_code& error) {
        if (!error) {
            session->start();
            DEBUG_STR_DVNCI(Handle accepted);
            ns_adminsession_ptr new_session(new adminsession(io_service_, intf));
            acceptor_.async_accept(new_session->socket(),
                    boost::bind(&ns_adminserver::handle_accept, this, new_session,
                    boost::asio::placeholders::error));}}

private:
    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
    adminintf_ptr intf;} ;

typedef boost::shared_ptr<ns_adminserver> ns_adminserver_ptr;

class adminservice : public executable {
public:

    adminservice() : executable() {}

    virtual bool operator()() {
        while (terminate_var) {
            if (init()) {
                if  (!terminate_var) break;
                boost::xtime xt_loop;
                addmillisec_to_now(xt_loop, 1000);
                boost::thread::sleep(xt_loop);
                if  (!terminate_var) break;}}

        intf.reset();
        return true;}

    virtual void terminate() {
        executable::terminate();
        io_service.stop();}

protected:

    virtual bool initialize()  {
        adminintf_ptr intf = factory::build(basepath,  NS_ADMIN_SERVICE);
        if (!intf) return false;
        remote_port = to_str(intf->conf_numproperty(NS_CNFG_ADMINPORT));
        tcp::endpoint endpoint(tcp::v4(), str_to<int>(remote_port.c_str()));
        ns_adminserver_ptr server(new ns_adminserver(io_service, endpoint, intf));
        io_service.run();
        return true;}

    virtual bool uninitialize() {
        return true;}

private:
    adminintf_ptr intf;} ;

int main(int argc, char* argv[]) {
    std::string quit_in;
    basepath = getlocalbasepath();
    dvnci::mainserv = executable_ptr(new adminservice());
#ifndef DVNCI_DEDUG
    if (serviceargumentparser(argc, argv)==SERVICE_OPEATION_APP) {
#endif
        try {
            DEBUG_STR_DVNCI(start app)
            boost::thread th = boost::thread(mainserv);
            while ((std::cin >> quit_in)  && ((quit_in!="q") && (quit_in!="Q")));
            mainserv.terminate();
            th.join();}
        catch (std::exception& err) {
            DEBUG_VAL_DVNCI(err.what());}
#ifndef DVNCI_DEDUG
    }
#endif
    DEBUG_STR_DVNCI(FIN)
    return (EXIT_SUCCESS);}

