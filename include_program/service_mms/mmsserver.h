/* 
 * File:   netserver.h
 * Author: Serg
 *
 * Created on 23 Июль 2010 г., 0:32
 */

#ifndef _DVNCI_MMSSERVER_H
#define	_DVNCI_MMSSERVER_H


/*#include <custom/netfactory.h>
#include <custom/netsession.h>

#include <kernel/constdef.h>
#include <kernel/systemutil.h>
#include <kernel/rpcioclient.h>
#include <kernel/factory.h>

namespace dvnci{
namespace custom{
namespace net{



//using dvnci::net::dbtsk_exec;
//using dvnci::net::dbtsk_exec_ptr;

using boost::asio::ip::tcp;


class ns_mmsserver {
    
    typedef boost::shared_ptr<netsession> ns_netsession_ptr;
    
public:


    ns_mmsserver(boost::asio::io_service& io_service,
            const tcp::endpoint& endpoint, dvnci::tagsbase_ptr inf)
    : intf(inf),  io_service_(io_service),
    acceptor_(io_service, endpoint) {
        netintf_ptr inf_tmp = dvnci::custom::net::factory::build(intf);
        ns_netsession_ptr new_session(new netsession(io_service_, inf_tmp));
        acceptor_.async_accept(new_session->socket(),
                boost::bind(&ns_mmsserver::handle_accept, this, new_session,
                boost::asio::placeholders::error));}

    void handle_accept(ns_netsession_ptr session,
            const boost::system::error_code& error) {
        if (!error) {
            session->start();
            DEBUG_STR_DVNCI(Handle accepted);
            netintf_ptr infnet = netintf_ptr(dvnci::custom::net::factory::build(intf));
            ns_netsession_ptr new_session(new netsession(io_service_, infnet));
            acceptor_.async_accept(new_session->socket(),
                    boost::bind(&ns_mmsserver::handle_accept, this, new_session,
                    boost::asio::placeholders::error));}}

private:
    dvnci::tagsbase_ptr      intf;
    boost::asio::io_service& io_service_;
    tcp::acceptor            acceptor_;};
    
    
    

typedef boost::shared_ptr<ns_mmsserver> ns_mmsserver_ptr;

class mms_server_service : public executable {
public:

    mms_server_service(dvnci::tagsbase_ptr inf) : executable(), intf(inf) {}

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
        std::string remote_prt = dvnci::to_str(intf->conf_property(NS_CNFG_REMOTEPORT));
        tcp::endpoint endpoint(tcp::v4(), atoi(remote_prt.c_str()));
        DEBUG_VAL_DVNCI(remote_prt);
        ns_mmsserver_ptr server(new ns_mmsserver(io_service, endpoint, intf));
        io_service.run();
        return true;}

    virtual bool uninitialize() {
        return true;}

private:
    boost::asio::io_service io_service;
    dvnci::tagsbase_ptr     intf;};
    
    
}}}*/



#endif	/* NETSERVER_H */

