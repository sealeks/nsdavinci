/* 
 * File:   dbwriter.h
 * Author: Alexeev
 *
 * Created on 4 Апрель 2011 г., 14:17
 */

#ifndef DBWRITER_H
#define	DBWRITER_H

#include <kernel/system_proccesstmpl.h>
#include <dbaccess/dbconnectionfactory.h>




namespace dvnci {
    namespace database {





        class db_writer : public executable {
            
            const static num64 JOURNAL_WRITE_SCALE = 5000;
            const static num64 DEBUG_WRITE_SCALE   = 5000;
            const static num64 TREND_WRITE_SCALE   = 5000;

            const static std::size_t   MAX_TREND_BUFFER = 0x8000;

            typedef dvnci::mutex_ptr                                                                mutex_ptr;
            typedef boost::mutex&                                                                   mutex_ref;
            


        public:

            db_writer(tagsbase_ptr  inf) : executable(), j_guid(0), j_cursor(0), j_count(0),
            d_guid(0), d_cursor(0), d_count(0), trendupdated(false), lasttrday(32),
            last_j_time(), last_d_time(), last_t_time(), intf(inf) {
                mtx = mutex_ptr(new boost::mutex());}

            virtual ~db_writer() {};

            static void setdbdriver(dvnci::database::dbdriver_ptr val) {
                dbdrv = val;}

            void write_trend(indx id, datetime tm, double val = NULL_DOUBLE);

            void write_trends(indx id, const dt_val_map& vlmap);

            virtual bool operator()();
            
            bool is_connected(){
                return ((dbdrv) && (dbdrv->isconnected()));}

            boost::mutex* mtx_internal() const {
                return mtx.operator ->();}


        protected:

            virtual bool    initialize() {
                if (!intf) return false;
                j_guid = j_guid ? j_guid : intf->guid_journal();
                d_guid = d_guid ? d_guid : intf->guid_debug();
                last_j_time = now();
                last_d_time = now();
                last_t_time = now();
                return true;}

            virtual  bool   uninitialize() {
                return true;}

            bool j_needwrite() const {
                return (dvnci::abs(millisecondsbetween(last_j_time, now())) > JOURNAL_WRITE_SCALE);}

            bool d_needwrite() const {
                return (dvnci::abs(millisecondsbetween(last_d_time, now())) > DEBUG_WRITE_SCALE);}

            bool t_needwrite() const {
                return (dvnci::abs(millisecondsbetween(last_t_time, now())) > TREND_WRITE_SCALE);}

            bool flash_trend();

            bool connected() {
                if (dbdrv) {
                    if (dbdrv->isconnected()) return true;
                    dbdrv->connect();
                    if (dbdrv->isconnected()) return true;}
                return false;}

        private:
            guidtype            j_guid;
            size_t              j_cursor;
            size_t              j_count;
            guidtype            d_guid;
            size_t              d_cursor;
            size_t              d_count;
            volatile  bool      trendupdated;
            num32               lasttrday;
            datetime            last_j_time;
            datetime            last_d_time;
            datetime            last_t_time;
            tagsbase_ptr        intf;
            mutex_ptr           mtx;
            journal_item_vect   journal_vect;
            debug_item_vect     debug_vect;
            dt_val_deque        trend_dqu;
            static dbdriver_ptr dbdrv;};



     class trend_observer : public executable{

            typedef dvnci::mutex_ptr                                                           mutex_ptr;
            typedef boost::mutex&                                                              mutex_ref;

        public:

            trend_observer(tagsbase_ptr  inf, db_writer* db_wr) : executable(), intf(inf), db_wrtr(db_wr){
                  mtx = mutex_ptr(new boost::mutex());}

            ~trend_observer(){}

            boost::mutex* mtx_internal() const {
                return mtx.operator ->();}

            virtual bool operator()();

            void add_trend(indx id);

            void remove_trend(indx id);

        protected:

            virtual bool    initialize();

            virtual  bool   uninitialize();

        private:

           tagsbase_ptr         intf;
           db_writer*           db_wrtr;
           indxdt_map           keyset;
           dt_val_map           vlmap;
           mutex_ptr            mtx;};






    }}

#endif	/* DBWRITER_H */

