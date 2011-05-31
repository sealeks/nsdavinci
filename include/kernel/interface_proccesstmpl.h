/* 
 * File:   interface_proccesstmpl.h
 * Author: Serg
 *
 * Created on 23 Р пїЅРЎР‹Р В»РЎРЉ 2010 Р С–., 12:07
 */

#ifndef SUBSCRIPTGROUP_PROCCESSOR_TEMPLU_H
#define	SUBSCRIPTGROUP_PROCCESSOR_TEMPLU_H

#include <kernel/proccesstmpl.h>

namespace dvnci {

    const blksizetype DEFAULT_ARCHIVEBS = 15;

    template <typename CLIENTITEM, typename SERVERITEM, typename ERRORITEM,
            typename SERVERKEYTYPE, typename VALUE, typename REPORTVALUES, typename REPORTVALUE,
            typename EVENTVALUE, typename COMMAND, typename CLIENTKEYTYPE = indx>
            class externalintf {
    public:

        typedef CLIENTITEM client_item_type;
        typedef SERVERITEM server_item_type;
        typedef ERRORITEM error_item_type;
        typedef SERVERKEYTYPE server_key_type;
        typedef VALUE value_type;
        typedef REPORTVALUES reportvalues_type;
        typedef REPORTVALUE reportvalue_type;
        typedef EVENTVALUE eventvalue_type;
        typedef COMMAND command_type;
        typedef CLIENTKEYTYPE client_key_type;

        typedef std::vector<CLIENTITEM > vct_client_item;
        typedef std::vector<SERVERITEM > vct_server_item;
        typedef std::vector<ERRORITEM > vct_error_item;
        typedef std::vector<SERVERKEYTYPE > vct_server_key;
        typedef std::vector<VALUE > vct_value;
        typedef std::vector<REPORTVALUES > vct_reportvalues;
        typedef std::vector<REPORTVALUE > vct_reportvalue;
        typedef std::vector<EVENTVALUE > vct_eventvalue;
        typedef std::vector<COMMAND > vct_command;
        typedef std::vector<CLIENTKEYTYPE > vct_client_key;

        enum intfstate {
            disconnected, connected};

        virtual bool islocal() {
            return true;}

        externalintf() : _state(disconnected), archiveblocksize_(DEFAULT_ARCHIVEBS) {};

        virtual ~externalintf() {};

        virtual bool connect() = 0;
        virtual bool disconnect() = 0;

        intfstate state() {
            return _state;}

        bool isconnected() const {
            return (_state == connected);}

        void clearerrors() {
            errmap.clear();}

        boost::mutex* mtx_internal() {
            return &mutex;}

        blksizetype archiveblocksize() const{
            return ((archiveblocksize_<1) || (archiveblocksize_>1000)) ? DEFAULT_ARCHIVEBS : archiveblocksize_;}

        /* add_items запрашивает айтемсы у сервера
         * @param clientitem вектор клиентских айтемсов
         * @param serveritem вектор серверных айтемсов
         * @param errors вектор ошибок
         * @return  успешность выполнения
         */
        virtual bool add_items(const vct_client_item& clientitem, vct_server_item& serveritem, vct_error_item& errors) = 0;
        virtual bool read_values(const vct_server_key& servids, vct_value& values, vct_reportvalues& reportvalues, vct_eventvalue& eventvalues, vct_error_item& errors) = 0;
        virtual bool read_values(vct_value& values, vct_reportvalues& reportvalues, vct_eventvalue& eventvalues) = 0;
        virtual bool remove_items(const vct_server_key& delitem, vct_error_item& errors) = 0;
        virtual bool add_commands(const vct_command& commanditem, vct_error_item& errors) = 0;
        virtual bool add_report_task(server_key_type key, datetime start, datetime stop) = 0;

    protected:
        boost::mutex       mutex;
        intfstate          _state;
        blksizetype        archiveblocksize_;
        int_dvncierror_map errmap;};

    template<typename EXTERNALINTF, tagtype PROVIDETYPE = TYPE_SIMPL>
    class abstract_subscriptor : public executor {
    public:

        typedef EXTERNALINTF extintf;
        typedef intrusive_sync_share_ptr_tmpl<extintf> extintf_ptr;
        typedef typename extintf::server_key_type server_key_type;
        typedef typename extintf::client_key_type client_key_type;
        typedef typename extintf::reportvalues_type reportvalues_type;
        typedef typename extintf::reportvalue_type reportvalue_type;
        typedef typename extintf::vct_client_item vct_client_item;
        typedef typename extintf::vct_server_item vct_server_item;
        typedef typename vct_server_item::const_iterator vct_server_item_const_iterator;
        typedef typename extintf::vct_command vct_command;
        typedef typename extintf::vct_server_key vct_server_key;
        typedef typename vct_server_key::const_iterator vct_server_key_const_iterator;
        typedef typename extintf::vct_error_item vct_error_item;
        typedef typename vct_error_item::const_iterator vct_error_item_const_iterator;
        typedef typename extintf::vct_value vct_value;
        typedef typename vct_value::const_iterator vct_value_const_iterator;
        typedef typename extintf::vct_reportvalue vct_reportvalue;
        typedef typename vct_reportvalue::const_iterator vct_reportvalue_const_iterator;
        typedef typename extintf::vct_reportvalues vct_reportvalues;
        typedef typename vct_reportvalues::const_iterator vct_reportvalues_const_iterator;
        typedef typename extintf::vct_eventvalue vct_eventvalue;
        typedef typename vct_eventvalue::const_iterator vct_eventvalue_const_iterator;

        typedef bidirectinal_map_one_to_many<server_key_type, client_key_type> serverid_clienid_map;

        abstract_subscriptor(tagsbase_ptr inf, indx grp, metalink lnk, tagtype provide_man = TYPE_SIMPL) :
                          executor(inf, provide_man), group(grp) {};

        virtual bool operator()() {

            if (!intf) return false;
            if (invokereq()) {
                for (indx_set::const_iterator it = all_items.begin();
                        it != all_items.end(); ++it) {
                    check_item_in_active(*it);}}
            return true;}

    protected:

        virtual void add_tags_impl(const indx_set& idset) {
            for (indx_set::const_iterator it = idset.begin();
                    it != idset.end(); ++it) {
                    add_item_in_all(*it);}}

        virtual void remove_tags_impl(const indx_set& idset) {
            for (indx_set::const_iterator it = idset.begin();
                    it != idset.end(); ++it) {
                rem_item_from_all(*it);}}

        virtual bool initialize() {

            if ((!intf) || (!intf->groups()->exists(group))) return false;
            if (!extinf) {
                if (!initialize_impl()) return false;}
            if (!extinf) return extinf;
            if (!extinf->isconnected()) extinf->connect();
            if (!extinf->isconnected()) {
                set_group_state(npos, ERROR_NONET_CONNECTED);
                return false;}
            fill_need_reqitems(get_active_items());
            DEBUG_STR_DVNCI(exintf connected)
            return true;}

        virtual bool initialize_impl() = 0;

        virtual bool uninitialize() {
            if (extinf) extinf->disconnect();
            extinf.reset();
            add_req_items.clear();
            del_req_items.clear();
            sid_clid_registry.clear();
            group_state_off();
            DEBUG_STR_DVNCI(THROWING RICH uninitialize end)
            return true;}



        virtual bool invokereq() {

            if (!init()) {
                DEBUG_STR_DVNCI(NOTINIT);
                return false;}
            try {

                if (prepare_del_items(req_remv)) {
                    vct_error_item errors_tmp;
                    if (extinf->remove_items(req_remv, errors_tmp)) {
                        del_req_items.clear();}}

                if (prepare_add_command(req_command)) {
                    vct_error_item errors_tmp;
                    DEBUG_STR_VAL_DVNCI(FINDCOMMAND, req_command.size())
                    extinf->add_commands(req_command, errors_tmp);}

                if (prepare_req_values()) {
                    vct_value values_tmp;
                    vct_reportvalues reportvalues_tmp;
                    vct_eventvalue eventvalues_tmp;
                    vct_error_item errvect_tmp;

                    if (extinf->read_values(activ_servid, values_tmp, reportvalues_tmp, eventvalues_tmp, errvect_tmp)) {
                        set_values(values_tmp);
                        //if (is_report_provided()){
                        for (vct_reportvalues_const_iterator it = reportvalues_tmp.begin(); it != reportvalues_tmp.end(); ++it) {
                            set_reportvalues(static_cast<server_key_type> (it->outkey), it->values);}}}//}


                if (prepare_add_reporttask(req_reptask)) {
                    report_task_map::iterator it = add_report_tasks.begin();
                    server_key_type servkey = serverkey(req_reptask.first);
                    if (extinf->add_report_task(static_cast<server_key_type>(servkey), req_reptask.second.start, req_reptask.second.stop)) {
                        if (it != add_report_tasks.end()) add_report_tasks.erase(it);}}

               if (prepare_add_items(req_add)) {
                    vct_server_item serveritem_tmp;
                    vct_error_item errors_tmp;
                    if (extinf->add_items(req_add, serveritem_tmp, errors_tmp)) {
                        add_server_ids(serveritem_tmp);
                        add_in_errormap(errors_tmp);}
                    add_req_items.clear();}}

            catch (dvncierror& err_) {
                if ((err_.code() == ERROR_FAILNET_CONNECTED) || (err_.code() == ERROR_NONET_CONNECTED)) {
                    DEBUG_STR_DVNCI(THROWING RICH invokereq)
                    uninit();
                    return false;}}
            catch (...) {}
            return true;}


        //  добавление тега в процесс обработки

        void add_item_in_all(indx id) {
            if (all_items.find(id) == all_items.end()) {
                all_items.insert(id);
                check_item_in_active(id);}}

        // удаление тега из процесса обработки

        void rem_item_from_all(indx id) {
            if (all_items.find(id) != all_items.end()) {
                check_item_in_active(id);
                all_items.erase(id);}}

        // проверка тега на активность

        virtual bool check_item_in_active(indx id) {
            if (requested(id)) {
                if (active_items.find(id) == active_items.end()) {
                        fill_need_reqitem(id);
                        active_items.insert(id);
                        DEBUG_STR_VAL_DVNCI(setactiv, id);}
                       check_reportitem_in_active(id);
                return true;}
            else {
                if (!IN_REPORTSET(intf->type(id))){
                   if (active_items.find(id) != active_items.end()) {
                       active_items.erase(id);
                       del_req_items.insert(id);
                       //remove_reporvalue_from_map(id);
                       DEBUG_STR_VAL_DVNCI(resetactiv, id);}
                   return false;}}
            return false;}


        virtual bool check_reportitem_in_active(indx id){
              if ((!is_report_task(id))) {
                  add_report_task(id);
		  return true;}
	      return false;}

        // очистка отчетного задания

        virtual void clear_report_task(indx id) {
            report_task_map::iterator it = report_tasks.find(id);
            if (it != report_tasks.end()) report_tasks.erase(it);}

        // добавить отчетное задание

        void add_report_task(indx id) {
                datetime start = intf->time_log(id);
                increporttime(start, intf->type(id), -1);
                datetime stop= start;
                increporttime(stop, intf->type(id), static_cast<reporthisttype>(extinf->archiveblocksize()));
                stop = stop > now() ? now() : stop;
                DEBUG_STR_DVNCI(add_report_task_remote);
                DEBUG_VAL_DVNCI(id);
                DEBUG_VAL_DVNCI(start);
                DEBUG_VAL_DVNCI(stop);
                report_task_pair newtask = std::make_pair(id, date_time_pair(start, stop));
                report_tasks.insert(newtask);
                add_report_tasks.insert(newtask);}

        // отчетное задание уже поставлено

        bool is_report_task(indx id) {
            return report_tasks.find(id) != report_tasks.end();}

        // предоставление карты  тегов (используется реализацией)

        const indx_set& get_active_items() {
            return active_items;}

        void fill_need_reqitems(const indx_set& itemset_) {
            add_req_items.insert(itemset_.begin(), itemset_.end());}

        void fill_need_reqitem(indx id) {
            add_req_items.insert(id);}

        virtual bool prepare_add_items(vct_client_item& clientitems) = 0;

        virtual bool prepare_add_command(vct_command& cmditems) = 0;

        virtual bool prepare_del_items(vct_server_key& delitems) {
            delitems.clear();
            indx_set tmp_null_remove;
            for (indx_set::iterator it = del_req_items.begin(); it != del_req_items.end(); ++it) {
                server_key_type servkey = serverkey(*it);
                if (sid_clid_registry.remove_by_second(*it)) {
                    if (servkey > nill_server_key()) {
                        remove_server_id(static_cast<server_key_type> (servkey));
                        delitems.push_back(servkey);}}
                else
                    // еще есть элементы с этим серверным id - снимать с опроса не надо
                    tmp_null_remove.insert(*it);}
            for (indx_set::iterator it = tmp_null_remove.begin(); it != tmp_null_remove.end(); ++it) {
                del_req_items.erase(*it);}
            return (!delitems.empty());}

        bool prepare_req_values() {
            return !sid_clid_registry.empty();}

        bool prepare_add_reporttask(report_task_pair& task) {
            if (add_report_tasks.empty()) return false;
            task = *add_report_tasks.begin();
            return true;}

        virtual server_key_type serverkey(client_key_type inkey) {
            return sid_clid_registry.is_second(inkey) ? sid_clid_registry.first_by_second(inkey) : nill_server_key();}

        virtual void set_values(const vct_value& values) {
            for (vct_value_const_iterator it = values.begin(); it != values.end(); ++it) {
                indx_set set_;
                if (sid_clid_registry.second_by_first(static_cast<server_key_type> (it->outkey), set_)) {
                    for (indx_set::const_iterator itval = set_.begin(); itval != set_.end(); ++itval) {
                        short_value tmpval;
                        tmpval << (*it);
                        if (!set_values_impl(*itval, tmpval))
                            write_val(*itval, tmpval);}}}}

        virtual bool set_values_impl(indx id, const short_value& value){ return false;}

        virtual void set_reportvalues(server_key_type id, const vct_reportvalue& values) {
            if (!values.empty()) {
                for (vct_reportvalue_const_iterator it = values.begin(); it != values.end(); ++it) {
                    indx_set idset;
                    if (sid_clid_registry.second_by_first(id, idset)) {
                        for (indx_set::const_iterator itval = idset.begin(); itval != idset.end(); ++itval) {
                            error(*itval);
                            clear_report_task(*itval);
                            write_val_report(*itval, cast_datetime_fromnum64(it->time), from_num64_cast<double>(it->val));}}}}
            else {
                indx_set idset;
                if (sid_clid_registry.second_by_first(id, idset)) {
                    for (indx_set::const_iterator itval = idset.begin(); itval != idset.end(); ++itval) {
                        error(*itval, ERROR_NULLRESPONSE);
                        clear_report_task(*itval);}}}}

        virtual void add_server_ids(const vct_server_item& outids) {
            for (vct_server_item_const_iterator it = outids.begin(); it != outids.end(); ++it) {
                sid_clid_registry.add(static_cast<server_key_type> (it->outkey), static_cast<client_key_type> (it->key));
                if (std::find(activ_servid.begin(), activ_servid.end(), static_cast<server_key_type> (it->outkey)) == activ_servid.end())
                    activ_servid.push_back(static_cast<server_key_type> (it->outkey));}}

        virtual void remove_server_ids(const vct_server_key& outids) {
            for (vct_server_key_const_iterator it = outids.begin(); it != outids.end(); ++it) {
                activ_servid.erase(std::remove(activ_servid.begin(), activ_servid.end(), *it), activ_servid.end());}}

        virtual void remove_server_id(server_key_type id) {
            activ_servid.erase(std::remove(activ_servid.begin(), activ_servid.end(), id), activ_servid.end());}

        virtual void add_in_errormap(const vct_error_item& errorsvct) {
            for (vct_error_item_const_iterator it = errorsvct.begin(); it != errorsvct.end(); ++it) {
                error(static_cast<indx> (it->key), static_cast<ns_error> (it->code));}}

        virtual server_key_type nill_server_key() const = 0;

        //  внешний интерфейс
        extintf_ptr extinf;

        // двунаправленная карта ключ внешнего интерфеса <-> ключ базы
        serverid_clienid_map sid_clid_registry;

        //карта всех обслуживаемых тегов
        indx_set all_items;
        //карта всех тегов поставленных в опрос
        indx_set active_items;
        // отчетное задание
        report_task_map report_tasks;

        // карта айтемсов на добавление в опрос
        indx_set add_req_items;
        //карта айтемсов на удаление из опроса
        indx_set del_req_items;
        //карта заданий на запрос отчетных тегов
        report_task_map add_report_tasks;

        indx group;

        // временные значения
        vct_client_item  req_add;
        vct_command      req_command;
        vct_server_key   req_remv;
        report_task_pair req_reptask;

        vct_server_key   activ_servid;};


}

#endif	/* SUBSCRIPTGROUP_PROCCESSOR_TEMPL_H */

