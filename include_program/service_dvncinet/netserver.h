/* 
 * File:   netserver.h
 * Author: Serg
 *
 * Created on 23 Июль 2010 г., 0:32
 */

#ifndef _DVNCI_NETSERVER_H
#define	_DVNCI_NETSERVER_H


#include <netinterface/factory.h>
#include <netinterface/netsession.h>
#include <netinterface/rpcnetstruct.h>
#include <netinterface/dvnci_net_subsciptor.h>

#include <kernel/constdef.h>
#include <kernel/systemutil.h>
#include <kernel/rpcioclient.h>
#include <kernel/factory.h>

namespace dvnci{
namespace net{



using dvnci::net::dbtsk_exec;
using dvnci::net::dbtsk_exec_ptr;

using boost::asio::ip::tcp;


class ns_netserver {
public:

    bool isIntf() {
        return (inf_);}

    ns_netserver(boost::asio::io_service& io_service,
            const tcp::endpoint& endpoint, dvnci::tagsbase_ptr _inf_, dbtsk_exec_ptr dbexec_ptr_)
    : inf_(_inf_), dbexec_ptr(dbexec_ptr_), io_service_(io_service),
    acceptor_(io_service, endpoint) {
        THD_EXCLUSIVE_LOCK(inf_);
        dvnci::net::netintf_ptr inf_tmp = dvnci::net::netintf_ptr(dvnci::net::factory::build(inf_, dbexec_ptr));

        ns_netsession_ptr new_session(new netsession(io_service_, inf_tmp));
        acceptor_.async_accept(new_session->socket(),
                boost::bind(&ns_netserver::handle_accept, this, new_session,
                boost::asio::placeholders::error));}

    void handle_accept(ns_netsession_ptr session,
            const boost::system::error_code& error) {
        DEBUG_VAL_DVNCI(error);
        if (!error) {
            THD_EXCLUSIVE_LOCK(inf_);
            session->start();
            DEBUG_STR_DVNCI(Handle accepted);


            dvnci::net::netintf_ptr inf_tmp = dvnci::net::netintf_ptr(dvnci::net::factory::build(inf_, dbexec_ptr));
            ns_netsession_ptr new_session(new netsession(io_service_, inf_tmp));
            acceptor_.async_accept(new_session->socket(),
                    boost::bind(&ns_netserver::handle_accept, this, new_session,
                    boost::asio::placeholders::error));}}

private:
    dvnci::tagsbase_ptr inf_;
    dbtsk_exec_ptr dbexec_ptr;
    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;};

typedef boost::shared_ptr<ns_netserver> ns_netserver_ptr;

class net_server_service : public executable {
public:

    net_server_service(dvnci::tagsbase_ptr _inf) : executable() {
        intf = _inf;}

    virtual bool operator()() {
        while (!terminated()) {
            if (init()) {
                if (terminated()) break;
                boost::xtime xt_loop;
                addmillisec_to_now(xt_loop, 1000);
                boost::thread::sleep(xt_loop);
                if (!terminated()) break;}}
        return true;}

    virtual void terminate() {
        executable::terminate();
        io_service.stop();}

protected:

    virtual bool initialize() {

        if (!intf) return false;
        DEBUG_STR_DVNCI(startinitnetserv1);
        if (!intf) return false;
        DEBUG_STR_DVNCI(intf);
        dbexec_ptr = dbtsk_exec_ptr(new dbtsk_exec(intf->conf_numproperty(NS_CNFG_DBMANAGER), intf->conf_property(NS_CNFG_DBCONSTR)));
        th_db = boost::thread(dbexec_ptr);
        using namespace std; 
        std::string remote_prt = dvnci::to_str(intf->conf_property(NS_CNFG_REMOTEPORT));
        tcp::endpoint endpoint(tcp::v4(), atoi(remote_prt.c_str()));
        DEBUG_VAL_DVNCI(remote_prt);
        ns_netserver_ptr server(new ns_netserver(io_service, endpoint, intf, dbexec_ptr));
        DEBUG_STR_DVNCI(PRED_RUN);
        io_service.run();
        DEBUG_STR_DVNCI(POSLE_RUN);
        return true;}

    virtual bool uninitialize() {
        if (dbexec_ptr) dbexec_ptr->terminate();
        th_db.join();
        return true;}

private:
    boost::asio::io_service io_service;
    dvnci::tagsbase_ptr intf;
    dbtsk_exec_ptr dbexec_ptr;
    boost::thread th_db;};
    
    
}}



#endif	/* NETSERVER_H */

