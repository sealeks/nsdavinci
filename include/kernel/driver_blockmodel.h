/* 
 * File:   driver_blockgenerator.h
 * Author: Serg
 *
 * Created on 19  test alexeev 16:48
 *   from note 16:29*/

#ifndef _DVNCI_KRNL_BLOCKGENERATOR_H
#define	_DVNCI_KRNL_BLOCKGENERATOR_H

#include <boost/bimap/multiset_of.hpp>

#include <kernel/memfile.h>
#include <kernel/proccesstmpl.h>

namespace dvnci {
    namespace driver {



        typedef  onum                    parcelkind;

        const  size_t BLOCKMAXDISTANCE = 0x1FFFFFFF;


        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Базовый класс ячейки опроса*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct basis_req_parcel {
            basis_req_parcel(std::string vl, tagtype tgtp, const metalink & mlnk);

            virtual ~basis_req_parcel() {};

            virtual size_t operator-(const basis_req_parcel & rs) const {
                return BLOCKMAXDISTANCE;};

            virtual bool operator==(const basis_req_parcel & rs) const;

            virtual bool operator!=(const basis_req_parcel & rs) const {
                return !operator==(rs);};

            virtual bool operator<(const basis_req_parcel & rs) const;

            devnumtype devnum() const {
                return devnum_;}

            parcelkind kind() const {
                return kind_;};

            num32 chanel() const {
                return chanel_;}

            num32 addr() const {
                return addr_;}

            num32 binnum() const {
                return indx_;}

            num32 indx() const {
                return indx_;}

            size_t size() const {
                return size_;}

            protocoltype protocol() const {
                return protocol_;}

            tagtype type() const {
                return type_;}

            ns_error error() const {
                return value_.error();}

            ns_error error(ns_error vl) {
                if (vl) isvalue_ = false;
                return value_.error(vl);}

            bool isvalue() const {
                return isvalue_;}

            bool iscorrect() const {
                return iscorrect_;}

            bool is_bcd() const {
                return isbcd_;}

            virtual std::string to_string();

            template<typename T>
                    void value_cast(T val, const datetime& tm = nill_time, vlvtype valid = FULL_VALID) {
                if (IN_SMPLSET(type())) {
                    if ((!is_bcd()) || ((is_bcd()) && (bcd_to_dec<T > (val)))) {
                        value_ = short_value(val);
                        value_.time(tm);
                        value_.valid(valid);
                        isvalue_ = true;
                        error(0);
                        return;}}
                error(ERROR_IO_DATA_CONV);}

            template<typename T >
                    T value_cast() const {
                return (isvalue()) ? value_.value<T > () : 0;}


            void value_byte_seq(const std::string& val, const datetime& tm = nill_time, vlvtype valid = FULL_VALID);


            short_value value() const;

            void value(const short_value & val);




            void value_event(const datetime& dt, double vl = NULL_DOUBLE, ns_error err = 0);

            void value_event(const dt_val_pair& vl, ns_error err = 0) {
                value_event(vl.first, vl.second, err);}

            dt_val_pair value_event() const;




            void value_report(const dt_val_map & dt, ns_error err = 0);

            const dt_val_map & value_report() const;


            void report_range(const datetime& start, const datetime &  stop);

            void report_range(const datetime_pair & vl) {
                report_range(vl.first, vl.second);}

            datetime_pair report_range() const;

            bool is_report_range() const {
                return reportrange_;}

            friend std::ostream & operator<<(std::ostream& os, const basis_req_parcel & ns) {
                return os << "dev=" << ns.devnum() << " chanal=" << ns.chanel() << "  type=" << ns.kind() << " addr=" << ns.addr();}

        protected:

            virtual void getspecificator(std::string & vl) {
                upper_and_trim(vl);
                if (vl.find(":B") != std::string::npos) {
                    isbcd_ = true;
                    vl.replace(vl.find(":B"), 2, "");}}


            bool                      iscorrect_;
            devnumtype                devnum_;
            parcelkind                kind_;
            num32                     chanel_;
            num32                     addr_;
            num32                     indx_;
            size_t                    size_;
            tagtype                   type_;
            protocoltype              protocol_;
            bool                      isbcd_;
            mutable bool              isvalue_;
            mutable short_value       value_;
            mutable datetime_val_ptr  eventvalue_;
            mutable dt_val_map        reportvalue_;
            mutable datetime_pair_ptr reportrange_;} ;

        template<>
        std::string basis_req_parcel::value_cast<std::string>() const;

        template<>
        void basis_req_parcel::value_cast<double>(double val, const datetime& tm, vlvtype valid);

        template<>
        void basis_req_parcel::value_cast<float>(float val, const datetime& tm, vlvtype valid);

        template<>
        void basis_req_parcel::value_cast<std::string>(std::string val, const datetime& tm, vlvtype valid);



        /////////////////////////////////////////////////////////////////////////////////////////////////////////


        typedef boost::shared_ptr<basis_req_parcel> parcel_ptr;

        size_t calculate_blocksize(parcel_ptr msblk, parcel_ptr lsblk);




        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Базовый класс генератора блока опроса*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class abstract_block_model {
        protected:

            struct parcel_ptr_less {

                bool operator() (parcel_ptr ls, parcel_ptr rs) const {
                    if ((!ls) || (!rs)) return false;
                    return (*ls)<(*rs);}} ;

        public:

            struct block;

            typedef boost::bimaps::set_of<indx, std::less<indx> >                          tags_setof;
            typedef boost::bimaps::multiset_of<parcel_ptr, parcel_ptr_less >               parcelptr_multisetof;
            typedef boost::bimaps::bimap<parcelptr_multisetof, tags_setof >                parcel_tags_map;
            typedef parcel_tags_map::left_map                                              parcels_map;
            typedef parcel_tags_map::right_map                                             tags_map;
            typedef parcel_tags_map::left_iterator                                         parcel_iterator;
            typedef parcel_tags_map::left_const_iterator                                   parcel_const_iterator;
            typedef parcel_tags_map::left_map::data_type                                   parcel;
            typedef parcel_tags_map::right_iterator                                        tags_iterator;
            typedef parcel_tags_map::value_type                                            parcel_tag_pair;



            typedef std::vector<block>                                                     block_vector;
            typedef std::vector<block>::const_iterator                                     block_iterator;

            typedef std::vector<parcel_ptr>                                                parcels_vect;
            typedef parcels_vect                                                           commands_vect;
            typedef commands_vect::iterator                                                commands_iterator;

            struct block {

                block() : groupid_(0) {};

                block(parcel_iterator strt, parcel_iterator stp, indx grpid, timeouttype tmout, size_t trycnt) :
                start_(strt), stop_(stp), groupid_(grpid) {
                    timout_ = in_bounded<timeouttype > (10, 600000, tmout);
                    trycount_ = in_bounded<size_t > (1, 10, trycnt);
                    curenttrycount_ = trycount_;}

                virtual ~block() {};

                indx groupid() const {
                    return groupid_;}

                void groupid(indx vl) {
                    groupid_ = vl;}

                timeouttype timout() const {
                    return timout_;}

                void timout(timeouttype vl) {
                    timout_ = in_bounded<timeouttype > (10, 600000, vl);}

                const parcel_iterator & begin() const {
                    return start_;}

                const parcel_iterator & end() const {
                    return stop_;}

                void begin(const parcel_iterator & val) {
                    start_ = val;}

                void end(const parcel_iterator & val) {
                    stop_ = val;}

                size_t trycount() const {
                    return trycount_;}

                void trycount(size_t vl) {
                    trycount_ = in_bounded<size_t > (1, 10, vl);}

                size_t curenttrycount() const {
                    return curenttrycount_;}

                void curenttrycount(size_t vl) {
                    curenttrycount_ = in_bounded<size_t > (1, 10, vl);}

                void set_ok() const {
                    curenttrycount_ = trycount_;};

                void set_fail() const {
                    if (curenttrycount_ > 1) curenttrycount_ = curenttrycount_ - 1;};

            private:

                parcel_iterator start_;
                parcel_iterator stop_;
                indx            groupid_;
                timeouttype     timout_;
                size_t          trycount_;
                mutable size_t  curenttrycount_;} ;

            abstract_block_model(executor* execr, tagsbase_ptr inf, const metalink& mlnk) :
            intf(inf), executr(execr), needgenerate(true), protocol(0), blocksize(0), archblocksize(0), eventblocksize(0) {
                protocol = mlnk.protocol();
                blocksize = mlnk.blocksize();
                archblocksize = mlnk.archblocksize();
                eventblocksize = mlnk.eventblocksize();};

            virtual ~abstract_block_model() {};

            virtual bool next(block& blk);

            virtual void fail() {
                if (currentblockiteator != end()) currentblockiteator->set_fail();
                currentblockiteator++;}

            virtual bool command(commands_vect& cmdvect);

            virtual void ok(block& blk);

            virtual bool insert(indx id) = 0;

            virtual bool erase(indx id) = 0;

            virtual bool check_parcel_active(parcel_iterator& prsl);

            virtual bool check_block_active(block& blk, parcel_iterator& bgn, parcel_iterator& ed);



        protected:

            virtual block_iterator begin() = 0;

            virtual block_iterator end() = 0;

            void generate() {
                if (!needgenerate) return;
                blocks.clear();
                generate_impl();}

            virtual void generate_impl() = 0;


            parcel_tags_map   bmap;
            block_vector      blocks;
            block_iterator    currentblockiteator;
            tagsbase_ptr      intf;
            executor*         executr;
            bool              needgenerate;
            protocoltype      protocol;
            size_t            blocksize;
            size_t            archblocksize;
            size_t            eventblocksize;
            indx_dtvalmap_map cash_reportval_map;
            indx_set          groupset_;} ;

        ///////////////////////////////////////////////////////////////////////////////////////////////


        typedef abstract_block_model::parcel_tags_map                      parcel_tags_map;
        typedef abstract_block_model::parcels_map                          parcels_map;
        typedef abstract_block_model::block_iterator                       block_iterator;
        typedef abstract_block_model::parcel_iterator                      parcel_iterator;
        typedef abstract_block_model::parcel_const_iterator                parcel_const_iterator;
        typedef abstract_block_model::block                                block;
        typedef abstract_block_model::parcels_vect                         parcels_vect;
        typedef abstract_block_model::commands_vect                        commands_vect;
        typedef commands_vect::iterator                                        commands_iterator;

        std::ostream & operator<<(std::ostream& os, const block& ns);
        parcels_vect & operator<<(parcels_vect& vct, const block& blk);
        std::ostream & operator<<(std::ostream& os, const parcels_vect& ns);


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Базовый шаблон генератора блока опроса для драйверов с линейной памятью, параметризованный типом ячейки опроса*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename BLOCKITEMTYPE>
        class flatmemory_block_model : public abstract_block_model {
        public:

            flatmemory_block_model(executor* exectr, tagsbase_ptr inf, const metalink& mlnk) :
            abstract_block_model(exectr, inf, mlnk) {};

            virtual ~flatmemory_block_model() {};

            virtual bool insert(indx id) {
                if (intf) {
                    if ((intf->exists(id)) && (intf->groups()->exists(intf->group((id))))) {

                        parcel_ptr tmpit = parcel_ptr(new BLOCKITEMTYPE(intf->binding(id),
                                intf->type(id),
                                intf->groups()->link(intf->group(id))));
                        if (tmpit->iscorrect()) {
                            tags_iterator it = bmap.right.find(id);
                            if (it != bmap.right.end()) bmap.right.erase(it);
                            bmap.insert(parcel_tag_pair(tmpit, id));
                            needgenerate = true;
                            return true;}
                        else {
                            executr->error(id, tmpit->error());
                            intf->debugwarning("Error binding " + intf->binding(id));}}}
                return false;}

            virtual bool erase(indx id) {
                if (intf) {
                    tags_iterator it = bmap.right.find(id);
                    if (it != bmap.right.end()) {
                        bmap.right.erase(it);
                        needgenerate = true;
                        executr->error(id);
                        return true;}}
                return false;}


        protected:

            virtual block_iterator begin() {
                if (needgenerate) generate();
                return blocks.begin();}

            virtual block_iterator end() {
                return blocks.end();}

            virtual void generate_impl();} ;


        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename BLOCKITEMTYPE>
        void flatmemory_block_model<BLOCKITEMTYPE>::generate_impl() {
            parcel_iterator its = bmap.left.begin();
            if (its == bmap.left.end()) {
                needgenerate = false;
                return;}
            block blkit(its, its, intf->group(its->second),
                    intf->groups()->indicateto(intf->group(its->second)),
                    intf->groups()->trycount(intf->group(its->second)));
            for (parcel_iterator it = bmap.left.begin(); it != bmap.left.end(); ++it) {
                if (calculate_blocksize(it->first, its->first) >= blocksize) {
                    blocks.push_back(blkit);
                    blkit.groupid(intf->group(it->second));
                    blkit.timout(intf->groups()->indicateto(blkit.groupid()));
                    blkit.trycount(intf->groups()->trycount(blkit.groupid()));
                    blkit.begin(it);
                    blkit.end(it);
                    its = it;}
                else {
                    blkit.end(it);}}
            blocks.push_back(blkit);
            needgenerate = false;}



        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Базовый шаблон генератора блока опроса для драйверов с "ячеистой" памятью, параметризованный типом ячейки опроса*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename BLOCKITEMTYPE>
        class parcel_block_model : public flatmemory_block_model<BLOCKITEMTYPE> {
        public:

            typedef flatmemory_block_model<BLOCKITEMTYPE> basetype;
            typedef abstract_block_model::block block;
            typedef abstract_block_model::parcel_iterator parcel_iterator;

            parcel_block_model(executor* exectr, tagsbase_ptr inf, const metalink& mlnk) :
            flatmemory_block_model<BLOCKITEMTYPE>(exectr, inf, mlnk) {}

        protected:

            virtual void generate_impl();} ;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename BLOCKITEMTYPE>
        void parcel_block_model<BLOCKITEMTYPE>::generate_impl() {
            parcel_iterator its = basetype::bmap.left.begin();
            if (its == basetype::bmap.left.end()) {
                basetype::needgenerate = false;
                return;}
            block blkit(its, its, basetype::intf->group(its->second),
                    basetype::intf->groups()->indicateto(basetype::intf->group(its->second)),
                    basetype::intf->groups()->trycount(basetype::intf->group(its->second)));
            its++;
            if (its == basetype::bmap.left.end()) {
                basetype::blocks.push_back(blkit);
                return;}
            size_t counter = 1;
            for (parcel_iterator it = its; it != basetype::bmap.left.end(); ++it) {
                if ((it->first->devnum() != its->first->devnum()) ||
                        (it->first->kind() != its->first->kind()) ||
                        (counter >= basetype::blocksize)) {
                    counter = 1;
                    basetype::blocks.push_back(blkit);
                    blkit.groupid(basetype::intf->group(it->second));
                    blkit.timout(basetype::intf->groups()->indicateto(blkit.groupid()));
                    blkit.trycount(basetype::intf->groups()->trycount(blkit.groupid()));
                    blkit.begin(it);
                    blkit.end(it);
                    its = it;}
                else {
                    counter++;
                    blkit.end(it);}}
            basetype::blocks.push_back(blkit);
            basetype::needgenerate = false;}}}

#endif	/* BLOCKGENERATOR_H */

