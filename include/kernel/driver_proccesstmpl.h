/*
 * File:   driver_proccesstmpl.h
 * Author: Serg
 *
 * Created on 
 */

#ifndef _DVNCI_KRNL_LINKPROCCESSTMPL_H
#define	_DVNCI_KRNL_LINKPROCCESSTMPL_H


#include <kernel/proccesstmpl.h>
#include <kernel/driver_blockmodel.h>
#include <kernel/driver_detail.h>


namespace dvnci {
    namespace driver {



        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Базовый шаблон потока исполнителя опроса устройств, параметризованый
         * менеджерoм устройства, генератором блока, cинхронизатором настоек соединения*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template < typename DEVICEMANAGER,
                typename BLOCKGENERATOR,
                typename METALINKCHACKER = metalink_checker>
                class device_link_executor : public executor {
            
            typedef boost::shared_ptr<DEVICEMANAGER>    device_service_ptr;
            typedef boost::shared_ptr<BLOCKGENERATOR>   block_generator_ptr;
            typedef boost::shared_ptr<metalink_checker> metalink_checker_ptr;

        public:

            device_link_executor(tagsbase_ptr inf, indx groupind, metalink lnk, tagtype provide_man = TYPE_SIMPL) :
            executor(inf, provide_man), link(lnk),  link_checked_error(0), io_error_(0) {
                meta_checker = metalink_checker_ptr(new METALINKCHACKER());};

            virtual bool operator()() {
                if (init()) {
                    if (devicemanager->connected()) {
                        io_error(0);
                        try {
                            if (blockgtor->command(comds)) {
                                io_error(*devicemanager << comds);}
                            if (blockgtor->next(blk)) {
                                size_t tmptrycnt = blk.curenttrycount() + 1;
                                while ((io_error(*devicemanager << blk)) && ((tmptrycnt--)>0)) {}
                                if (!io_error()) {
                                    set_group_state(blk.groupid(), 0);
                                    blockgtor->ok(blk);}
                                else {
                                    if (is_expire_group_timeout(blk.groupid(), blk.timout()))
                                        set_group_state(blk.groupid(), io_error(), FULL_VALID);
                                    blockgtor->fail();}
                                return true;}}
                        catch (dvncierror& errd) {
                            if (errd.code() == ERROR_IO_SERVICE_LOCK) {
                                if (intf )
                                    intf->debugerror("device_link_executor mainloop ERROR_IO_SERVICE_LOCK");
                                resetdevicemanager();
                                return false;}
                            if (intf )
                                intf->debugerror("device_link_executor mainloop dvncierror=" + to_str(errd.code()));
                            return false;}
                        catch (...) {
                            if (intf )
                                intf->debugerror("device_link_executor mainloop undef error");
                            return false;}}
                    else {
                        set_group_state(npos, devicemanager->error(), FULL_VALID);}}
                return false;};
                
            ns_error io_error() const {
                return io_error_;}

            ns_error io_error(ns_error err) {
                return io_error_ = err;}      

        protected:
            
           ns_error checklink() {
            if ((meta_checker) && (intf)) {
                if (link_checked_error)  return link_checked_error;
                metalink_vect mlvect;
                util_devnum_set.clear();
                intf->select_metalinks_vect_by_metalink(link, mlvect, util_devnum_set);
                link_checked_error = meta_checker->operator ()(mlvect);}
            return link_checked_error;}
                           

            virtual void add_tags_impl(const indx_set& idset) {
                if (init()) {
                    for (indx_set::const_iterator it = idset.begin(); it != idset.end(); ++it)
                        blockgtor->insert(*it);}}

            virtual void remove_tags_impl(const indx_set& idset) {
                if (init()) {
                    for (indx_set::const_iterator it = idset.begin(); it != idset.end(); ++it) {
                        blockgtor->erase(*it);}}}

            virtual void resetdevicemanager() {
                if (devicemanager) {
                    devicemanager->uninit();
                    devicemanager.reset();}
                if (intf) intf->debugerror("IO_SERVICE_DEADLOCK. CANCELIO OPERATION NOT WORKS. "
                        "Possible need define BOOST_ASIO_ENABLE_CANCELIO!!!!!!!");
                resetinit();}

            virtual bool initialize() {
                if (checklink()) {
                    set_group_state(npos, link_checked_error, FULL_VALID);
                    return false;}
                if (!blockgtor)
                    blockgtor = block_generator_ptr(new BLOCKGENERATOR(this, intf, link));
                if ((!blockgtor)) {
                    set_group_state(npos, ERROR_IO_NOBLOCKGEN_LINK, FULL_VALID);
                    return false;}
                if (!devicemanager)
                    devicemanager = device_service_ptr(new DEVICEMANAGER(link));
                if (!devicemanager) {
                    set_group_state(npos, ERROR_IO_NODEVMANAGER_LINK, FULL_VALID);
                    return false;}
                if (!devicemanager->init()) {
                    set_group_state(npos, devicemanager->error(), FULL_VALID);
                    return false;}
                set_group_state(npos, devicemanager->error(), FULL_VALID);
                devicemanager->util_device(util_devnum_set);
                return true;}

            virtual bool uninitialize() {
                if (devicemanager) {
                    devicemanager->uninit();
                    devicemanager.reset();}
                if (blockgtor)
                    blockgtor.reset();
                resetinit();
                group_state_off();
                return true;}
            
            block                        blk;
            commands_vect                comds;
            metalink                     link;
            devnum_set                   util_devnum_set;
            ns_error                     link_checked_error;
            ns_error                     io_error_;
            metalink_checker_ptr         meta_checker;
            block_generator_ptr          blockgtor;
            device_service_ptr           devicemanager;} ;}}


#endif	/* LINKPROCCESSTMPL_H */

