/* 
 * File:   interface_proccesstmpl.h
 * Author: Serg
 *
 * Created on 23 Р пїЅРЎР‹Р В»РЎРЉ 2010 Р С–., 12:07
 */

#ifndef SUBSCRIPTGROUP_PROCCESSOR_TEMPLU_H
#define	SUBSCRIPTGROUP_PROCCESSOR_TEMPLU_H

#include <kernel/proccesstmpl.h>
#include <kernel/constdef.h>

namespace dvnci {
    namespace external {

        const blksizetype DEFAULT_ARCHIVEBS = 15;

        class externalintf {
            typedef boost::shared_ptr<boost::mutex> mutex_ptr;

        public:

            enum intfstate {
                disconnected, connected
            };

            explicit externalintf(tagsbase_ptr inf, executor* exctr, indx grp, tagtype provide_man, subcripttype subsrcr = CONTYPE_SYNC) :
            state_(disconnected), intf(inf), exectr(exctr), group_(grp), groups_(), lnk_(),
            provide_(provide_man), subsrcript_(subsrcr), error_(0), mtx(new boost::mutex()) {
                groups_.insert(grp);
            };

            explicit externalintf(tagsbase_ptr inf, executor* exctr, const indx_set& grps, const metalink& lnk, tagtype provide_man, subcripttype subsrcr = CONTYPE_SYNC) :
            state_(disconnected), intf(inf), exectr(exctr), group_(dvnci::npos), groups_(grps), lnk_(lnk),
            provide_(provide_man), subsrcript_(subsrcr), error_(0), mtx(new boost::mutex()) {
            };

            virtual ~externalintf() {
            };

            bool isconnected() {
                return ((state_ == connected) || (!error(connect_impl())));
            };

            bool disconnect() {
                return ((state_ != connected) || (!error(disconnect_impl())));
            }

            indx group() const {
                return group_;
            }

            const indx_set& groups() const {
                return groups_;
            }

            const metalink& link() const {
                return lnk_;
            }

            bool multigroup() const {
                return groups_.size() > 1;
            }

            tagtype provide() const {
                return provide_;
            }

            subcripttype subsrcript() const {
                return subsrcript_;
            }

            ns_error error() const {
                return error_;
            }

            virtual bool operator()() {
                return true;
            }

            virtual void insert(const indx_set& idset) = 0;

            virtual void remove(const indx_set& idset) = 0;

            boost::mutex* mtx_internal() const {
                return mtx.get();
            }

            bool needsync() const {
                return (subsrcript_ != CONTYPE_SYNC);
            }

        protected:

            virtual ns_error connect_impl() = 0;

            virtual ns_error disconnect_impl() = 0;

            ns_error error(ns_error err) {
                return error_ = err;
            }

            void subsrcript(subcripttype val) {
                subsrcript_ = val;
            }

            volatile intfstate state_;
            tagsbase_ptr intf;
            executor* exectr;
            indx group_;
            indx_set groups_;
            metalink lnk_;
            tagtype provide_;
            subcripttype subsrcript_;
            ns_error error_;
            mutex_ptr mtx;
        };

        template < typename EXTERNALINTF>
        class externalintf_executor : public executor {
            typedef boost::shared_ptr<EXTERNALINTF> externintf_ptr;

        public:

            externalintf_executor(tagsbase_ptr inf, indx groupind, const metalink& lnk, tagtype provide_man = TYPE_SIMPL) :
            executor(inf, provide_man), lnk_(lnk) {
            };

            virtual bool operator()() {
                if (init()) {
                    if (externmanager->isconnected()) {
                        try {
                            externmanager->operator()();
                            set_group_state(npos, externmanager->error(), FULL_VALID);
                            return true;
                        } catch (dvncierror& errd) {
                            error(errd.code());
                            intf->debugerror("externalintf_executor mainloop dvnci_error");
                            set_group_state(npos, externmanager->error(), FULL_VALID);
                            return false;
                        } catch (...) {
                            if (intf)
                                intf->debugerror("externalintf_executor mainloop undef error");
                            set_group_state(npos, externmanager->error(), FULL_VALID);
                            return false;
                        }
                    } else {
                        set_group_state(npos, externmanager->error(), FULL_VALID);
                    }
                }
                return true;
            }

        protected:

            virtual void add_tags_impl(const indx_set& idset) {
                if (init()) {
                    externmanager->insert(idset);
                }
            }

            virtual void remove_tags_impl(const indx_set& idset) {
                if (init()) {
                    externmanager->remove(idset);
                }
            }

            virtual bool initialize() {
                if (!externmanager) {
                    if (strategy() != group_proccessor::STRATEGY_TYPE_LINK) {
                        externmanager = externintf_ptr(new EXTERNALINTF(intf, (executor*)this, group()));
                    } else {
                        externmanager = externintf_ptr(new EXTERNALINTF(intf, (executor*)this, groupset(), lnk_));
                    }
                }
                return externmanager;
            }

            virtual bool uninitialize() {
                if (externmanager) {
                    externmanager->disconnect();
                }
                group_state_off();
                return true;
            }

            externintf_ptr externmanager;
            metalink lnk_;
        };




    }
}

#endif	/* SUBSCRIPTGROUP_PROCCESSOR_TEMPL_H */

