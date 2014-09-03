/* 
 * File:   group_proccessor.h
 * Author: Serg
 *
 * Created on 23 Р В РїС—Р…Р РЋР вЂ№Р В Р’В»Р РЋР Р‰ 2010 Р В РЎвЂ“., 10:47
 */

#ifndef ___BASEGROUP_PROCCESSOR_H
#define	___BASEGROUP_PROCCESSOR_H

#include <kernel/systemutil.h>
#include <kernel/factory.h>


namespace dvnci {

    const size_t MAX_GROUPMESSAGE = 1000;

    // Стратегия отбора тегов

    class base_tagselector {

    public:

        static const onum NO_OPERATION = 0;
        static const onum ADD_OPERATION = 1;
        static const onum REM_OPERATION = 2;

        base_tagselector(tagsbase_ptr inf) : intf_(inf), appid_(0), group_(npos), link_(1) {
        };

        base_tagselector(tagsbase_ptr inf, appidtype app, metalink lnk) : intf_(inf), appid_(app), group_(npos), link_(lnk) {
        };

        base_tagselector(tagsbase_ptr inf, appidtype app, indx grp) : intf_(inf), appid_(app), group_(grp), link_(1) {
        };

        base_tagselector(tagsbase_ptr inf, appidtype app) : intf_(inf), appid_(app), group_(npos), link_(1) {
        };

        virtual ~base_tagselector() {
        };

        virtual bool get_tags(indx_set& itemset) = 0;

        appidtype appid() const {
            return appid_;
        }

        virtual indx group() const {
            return group_;
        }

        virtual bool group_included(indx id) const {
            return (group_ == id);
        }

        const metalink& link() const {
            return link_;
        }

        virtual bool nilllink() const {
            return false;
        }

        tagsbase_ptr intf() const {
            return intf_;
        }

        const indx_set& groupset() {
            return groupset_;
        };


    protected:

        tagsbase_ptr intf_;
        appidtype appid_;
        indx group_;
        indx_set groupset_;
        metalink link_;
        ;
    };



    // Стратегия отбора тегов  по id группы

    class groupid_selector_strategy : public base_tagselector {

    public:

        groupid_selector_strategy(tagsbase_ptr inf, appidtype app, indx grp) : base_tagselector(inf, app, grp) {
            groupset_.insert(grp);
        };

        virtual bool get_tags(indx_set& itemset) {
            itemset.clear();
            if (intf()) {
                if (intf()->groups()->exists(group_)) {
                    intf()->select_tags_by_groupid(itemset, group());
                    return true;
                }
            }
            return false;
        }
    };


    // Стратегия отбора отчетных тегов

    class report_selector_strategy : public base_tagselector {

    public:

        report_selector_strategy(tagsbase_ptr inf) : base_tagselector(inf) {
        };

        virtual bool get_tags(indx_set& itemset) {
            itemset.clear();
            if (intf()) {
                intf()->select_tags_report(itemset);
                return true;
            }
            return false;
        }

        virtual bool group_included(indx id) const {
            return false;
        }
    };


    // Стратегия отбора тегов  по идентификатору соединения

    class link_selector_strategy : public base_tagselector {

    public:

        link_selector_strategy(tagsbase_ptr inf, appidtype app, const metalink& lnk) :
        base_tagselector(inf, app, lnk) {
            if (intf())
                intf()->select_groups_by_metalink(link_, appid_, groupset_);
        };

        virtual bool get_tags(indx_set& itemset) {
            itemset.clear();
            if (intf()) {
                intf()->select_tags_by_link(itemset, appid_, link_);
                return true;
            }
            return false;
        }

        virtual bool group_included(indx id) const {
            return ((intf()) && (groupset_.find(id) != groupset_.end()));
        }

        virtual bool nilllink() const {
            return (groupset_.empty());
        }
    };



    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    typedef sync_share_ptr_tmpl<base_tagselector> tagselector_ptr;

    typedef std::pair<indx, short_value> executor_value_pair;
    typedef std::map<indx, short_value, std::less<indx>, std::allocator<executor_value_pair > > executor_value_map;

    typedef std::pair<indx, ns_error > executor_error_pair;
    typedef std::map<indx, ns_error, std::less<indx>, std::allocator<executor_error_pair > > executor_error_map;


    // обработчик тегов потока ( в зависимости от процессора : потока группы, потока канала соединения)

    class executor : public executable {

    public:

        executor(tagsbase_ptr inf, tagtype provide_man = TYPE_SIMPL);

        virtual ~executor() {
            clear_errors();
        };

        void add_tags(const indx_set& idset);

        void remove_tags(const indx_set& idset) {
            remove_tags_impl(idset);
        }

        void add_tag(indx id);
        void remove_tag(indx id);

        virtual void optinalchangeid(indx id) {
        }

        const indx_set& groupset() const {
            return groupset_;
        };

        void groupset(const indx_set& vl) {
            groupset_ = vl;
        };

        indx group() {
            return groupset_.empty() ? npos : (*(groupset_.begin()));
        };

        bool requested(indx id);
        bool report_requested(indx id);

        bool event_requested(indx id) {
            return true;
        }

        // запись доставленного значения
        void write_val(indx id, const short_value& val);
        void write_val(indx id, const std::string& val, vlvtype valid = FULL_VALID, datetime time = nill_time, ns_error err = 0);
        void write_val_report(indx id, const dt_val_map& values);
        void write_val_report(indx id, datetime tm, double val);
        void write_val_event(indx id, datetime dt, double vl = NULL_DOUBLE);
        void write_val_event(indx id, const dt_val_pair& val);

        // управлене ошибочными состояниями
        void error(indx id, ns_error err = 0);

        virtual ns_error checklink(bool recheck = false) {
            return 0;
        }

        void set_group_state(indx id = npos, ns_error err = 0, vlvtype valid = 1);
        void group_state_on(indx id = npos);
        void group_state_off(indx id = npos);

        boost::mutex* mtx_internal() {
            return &mtx;
        }

    protected:

        void clear_errors();

        virtual void add_tags_impl(const indx_set& idset) = 0;
        virtual void remove_tags_impl(const indx_set& idset) = 0;

        datetime get_group_timeout(indx id) const;
        void set_group_timeout(indx id);
        void clear_group_timeout(indx id);
        bool is_expire_group_timeout(indx id, num32 tout);

        // проверка на то что обработка типа поддерживается сервисом

        bool type_supported(indx id) const {
            return ((intf->exists(id)) &&
                    ((intf->superstype(id)) & provide_));
        }

        bool isconnected() {
            return isconnected_;
        }


        tagsbase_ptr intf;
        boost::mutex mtx;
        bool isconnected_;
        tagtype provide_;
        indx_set active_set;
        indx_set errors_set;
        indx_dt_map timout_map;
        indx_set tag_errorset;
        indx_set groupset_;
    };

    typedef intrusive_sync_share_ptr_tmpl<executor> executor_ptr;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    class group_proccessor : public executable {

    public:

        typedef onum strategytype;

        static const strategytype STRATEGY_TYPE_NO = 0;
        static const strategytype STRATEGY_TYPE_LINK = 1;
        static const strategytype STRATEGY_TYPE_GROUP = 2;
        static const strategytype STRATEGY_TYPE_REPORT = 3;
        static const strategytype STRATEGY_TYPE_APPID = 4;

        group_proccessor(tagsbase_ptr inf, tagselector_ptr selectr);

        void addmessage(num32 mess, indx id, indx some);

        virtual bool operator()();

        appidtype appid() const {
            THD_EXCLUSIVE_LOCK(*mtx_internal());
            return selector->appid();
        }

        bool group_included(indx id) const {
            THD_EXCLUSIVE_LOCK(*mtx_internal());
            return selector->group_included(id);
        }

        const metalink& link() const {
            THD_EXCLUSIVE_LOCK(*mtx_internal());
            return selector->link();
        }

        boost::mutex* mtx_internal() const {
            return managment.mutex.get();
        }


    protected:

        bool clearmessage();

        bool getmessage(messagestruct& mess);

        strategytype strategy() const {
            return strategy_;
        }

        virtual bool initialize();
        virtual bool uninitialize();

        virtual bool initialize_impl() = 0;
        virtual bool uninitialize_impl() = 0;

        virtual void execute_impl() {
        };

        virtual void addtag(indx id) = 0;
        virtual void removetag(indx id) = 0;

        virtual void optinalchangeid(indx id) = 0;

        bool nilllink() {
            return selector->nilllink();
        }

        struct groupmanagment {

            groupmanagment() {
                mutex = mutex_ptr(new boost::mutex());
            }
            messqueue queue;
            mutex_ptr mutex;
        };

        tagsbase_ptr intf;
        groupmanagment managment;
        messagestruct message;
        strategytype strategy_;
        mutable tagselector_ptr selector;
    };

    template<typename EXECUTOR, tagtype TYPEPROVIDER = TYPE_SIMPL>
    class group_proccessor_templ : public group_proccessor {

    public:

        typedef EXECUTOR executor_type;
        typedef intrusivesync_callable_shared_ptr<executor_type> executor_ptr;

        group_proccessor_templ(tagsbase_ptr inf, appidtype app, metalink lnk) :
        group_proccessor(inf, tagselector_ptr(new link_selector_strategy(inf, app, lnk))) {
            strategy_ = STRATEGY_TYPE_LINK;
            DEBUG_STR_VAL_DVNCI(init group proccessor link_selector_strategy, lnk.id())
        }

        group_proccessor_templ(tagsbase_ptr inf, appidtype app, indx grp) :
        group_proccessor(inf, tagselector_ptr(new groupid_selector_strategy(inf, app, grp))) {
            strategy_ = STRATEGY_TYPE_GROUP;
            DEBUG_STR_VAL_DVNCI(init group proccessor groupid_selector_strategy, grp)
        }

        group_proccessor_templ(tagsbase_ptr inf) :
        group_proccessor(inf, tagselector_ptr(new report_selector_strategy(inf))) {
            strategy_ = STRATEGY_TYPE_REPORT;
            DEBUG_STR_DVNCI(init group proccessor report_selector_strategy)
        }

        virtual ~group_proccessor_templ() {
            uninit();
        }

    protected:

        virtual void addtag(indx id) {
            //#ifdef DVNCI_DEDUG
            //intf->debugwarning("group_proccessor_templ"+ (selector ? to_str(selector->group()) : "nodef")+".addtag id=" + to_str(id));
            //#endif
            executr->add_tag(id);
        }

        virtual void removetag(indx id) {
            //#ifdef DVNCI_DEDUG
            //intf->debugwarning("group_proccessor_templ"+ (selector ? to_str(selector->group()) : "nodef")+".removrag id=" + to_str(id));
            //#endif
            executr->remove_tag(id);
        }

        virtual void optinalchangeid(indx id) {
            //#ifdef DVNCI_DEDUG
            //intf->debug("group_proccessor_templ"+ (selector ? to_str(selector->group()) : "nodef")+".optinalchangeid id=" + to_str(id));
            //#endif
            executr->optinalchangeid(id);
        }

        virtual bool initialize_impl() {

            if ((strategy() == STRATEGY_TYPE_LINK) && (!selector->link())) return false;
            if ((strategy() == STRATEGY_TYPE_GROUP) && (selector->group() == npos)) return false;
            if (!executr) {
                executr = executor_ptr(new executor_type(intf, selector->group(), selector->link(), TYPEPROVIDER));
                executr->groupset(selector->groupset());
            }
            if (!executr->init()) return false;

            indx_set grouptmpset;
            selector->get_tags(grouptmpset);
            executr->add_tags(grouptmpset);
            return true;
        }

        virtual bool uninitialize_impl() {
            if (executr) {
                executr->uninit();
            }
            return true;
        }

        virtual void execute_impl() {

            boost::xtime xt;
            if (executr->operator()())
                addmillisec_to_now(xt, 1);
            else
                addmillisec_to_now(xt, 50);
            boost::thread::sleep(xt);
        }

        executor_ptr executr;
    };





    typedef intrusivesync_callable_shared_ptr<group_proccessor> group_proccessor_ptr;
    typedef boost::shared_ptr<boost::thread> threadgroup_ptr;
}

#endif	/* BASEGROUP_PROCCESSOR_H */

