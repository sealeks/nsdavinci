/* 
 * File:   iec60870_protocol.h
 * Author: Serg
 *
 * Created on 18 ?????? 2010 ?., 17:22
 */

#ifndef IEC60870_PROTOCOL_H
#define	 IEC60870_PROTOCOL_H

#include <boost/asio/read_at.hpp>

#include <kernel/utils.h>
#include <kernel/systemutil.h>
#include <kernel/error.h>
#include <kernel/constdef.h>
#include <kernel/short_value.h>

#include <iec60870/iec60870_detail.h>

namespace dvnci {
    namespace prot80670 {

        template<typename T>
        class callable_shared {

            typedef boost::shared_ptr<T> shared_type;

        public:

            callable_shared() {
            }

            callable_shared(shared_type sh) : shr_(sh) {
            }

            ~callable_shared() {
            }

            void operator()() {
                if (shr_)
                    shr_->operator()();
            }

        private:

            shared_type shr_;

        };

        typedef std::vector<boost::uint8_t> octet_sequence;
        typedef boost::shared_ptr<octet_sequence> octet_sequence_ptr;

        typedef boost::uint8_t type_id;
        typedef boost::uint8_t cause_type;
        typedef boost::uint8_t sourse_type;
        typedef boost::uint8_t interrogation_type;
        typedef boost::uint16_t device_address; // 1,2
        typedef boost::uint16_t selector_address; // 1,2
        typedef boost::uint32_t data_address; // 1, 2 ,3        
        typedef boost::uint8_t bit_number;
        const bit_number NULL_BITNUMBER = '\xFF';


        const cause_type CS_CYCLIC = 1; //  periodical, cyclic
        const cause_type CS_PROCIMG = 2; //  generated for renewal of the process image
        const cause_type CS_SPONT = 3; //  spontaneous
        const cause_type CS_INIT = 4; //  initialized
        const cause_type CS_POLL = 5; //  polled
        const cause_type CS_ACT = 6; //  activation
        const cause_type CS_CONF_ACT = 7; //  confirmation of activation
        const cause_type CS_ABORT_ACT = 8; //  aborting of activation
        const cause_type CS_ABORT_ACT_CONF = 9; //  confirmation of aborting of activation
        const cause_type CS_END_ACT = 10; //  end of activation     
        const cause_type SC_STATUS_REMCMD = 11; //  status information, caused by a remote command
        const cause_type SC_STATUS_LOCCMD = 12; //  status information, caused by a local command
        const cause_type SC_INTERROG_GEN = 20; //  interrogated by general interrogation
        const cause_type SC_INTERROG_G1 = 21; //  interrogated by interrogation of group 1
        const cause_type SC_INTERROG_G2 = 22; //  interrogated by interrogation of group 2
        const cause_type SC_INTERROG_G3 = 23; //  interrogated by interrogation of group 3
        const cause_type SC_INTERROG_G4 = 24; //  interrogated by interrogation of group 4
        const cause_type SC_INTERROG_G5 = 25; //  interrogated by interrogation of group 5
        const cause_type SC_INTERROG_G6 = 26; //  interrogated by interrogation of group 6
        const cause_type SC_INTERROG_G7 = 27; //  interrogated by interrogation of group 7
        const cause_type SC_INTERROG_G8 = 28; //  interrogated by interrogation of group 8
        const cause_type SC_INTERROG_G9 = 29; //  interrogated by interrogation of group 9
        const cause_type SC_INTERROG_G10 = 30; //  interrogated by interrogation of group 10
        const cause_type SC_INTERROG_G11 = 31; //  interrogated by interrogation of group 11
        const cause_type SC_INTERROG_G12 = 32; //  interrogated by interrogation of group 12
        const cause_type SC_INTERROG_G13 = 33; //  interrogated by interrogation of group 13
        const cause_type SC_INTERROG_G14 = 34; //  interrogated by interrogation of group 14
        const cause_type SC_INTERROG_G15 = 35; //  interrogated by interrogation of group 15
        const cause_type SC_INTERROG_G16 = 36; //  interrogated by interrogation of group 16
        const cause_type SC_INTERROG_CNT_GEN = 37; //  interrogated by general counter interrogation
        const cause_type SC_INTERROG_CNT_G1 = 38; //  interrogated by interrogation of counter group 1
        const cause_type SC_INTERROG_CNT_G2 = 39; //  interrogated by interrogation of counter group 2
        const cause_type SC_INTERROG_CNT_G3 = 40; //  interrogated by interrogation of counter group 3
        const cause_type SC_INTERROG_CNT_G4 = 41; //  interrogated by interrogation of counter group 4
        const cause_type SC_INTERROG_CNT_SNGL = 42; //  interrogated by interrogation of a single counter



        const type_id M_SP_NA_1 = 1; //Single-point information
        const type_id M_SP_TA_1 = 2; //Single-point information with time-tag
        const type_id M_DP_NA_1 = 3; //Double-point information
        const type_id M_DP_TA_1 = 4; //Double-point information with time-tag
        const type_id M_ST_NA_1 = 5; //Step position information
        const type_id M_ST_TA_1 = 6; //Step position information with time-tag
        const type_id M_BO_NA_1 = 7; //Bitstring of 32 bits
        const type_id M_BO_TA_1 = 8; //Bitstring of 32 bits with time-tag
        const type_id M_ME_NA_1 = 9; //Measured value, normalized value
        const type_id M_ME_TA_1 = 10; //Measured value, normalized value with time-tag
        const type_id M_ME_NB_1 = 11; //Measured value, scaled value
        const type_id M_ME_TB_1 = 12; //Measured value, scaled value with time-tag
        const type_id M_ME_NC_1 = 13; //Measured value, short floating point value
        const type_id M_ME_TC_1 = 14; //Measured value, short floating point value with time-tag
        const type_id M_IT_NA_1 = 15; //Integrated totals
        const type_id M_IT_TA_1 = 16; //Integrated totals with time-tag
        const type_id M_EP_TA_1 = 17; //Event of protection equipment with time-tag
        const type_id M_EP_TB_1 = 18; //Packed start events of protection equipment with time-tag
        const type_id M_EP_TC_1 = 19; //Packed output circuit information of protection equipment with timetag
        const type_id M_PS_NA_1 = 20; //Packed single point information with status change detection
        const type_id M_ME_ND_1 = 21; //Measured value, normalized value without quality descriptor
        const type_id M_SP_TB_1 = 30; //Single-point information with time tag CP56Time2a
        const type_id M_DP_TB_1 = 31; //Double-point information with time tag CP56Time2a
        const type_id M_ST_TB_1 = 32; //Step position information with time tag CP56Time2a
        const type_id M_BO_TB_1 = 33; //Bitstring of 32 bit with time tag CP56Time2a
        const type_id M_ME_TD_1 = 34; //Measured value, normalized value with time tag CP56Time2a
        const type_id M_ME_TE_1 = 35; //Measured value, scaled value with time tag CP56Time2a
        const type_id M_ME_TF_1 = 36; //Measured value, short floating point value with time tag CP56Time2a
        const type_id M_IT_TB_1 = 37; //Integrated totals with time tag CP56Time2a
        const type_id M_EP_TD_1 = 38; //Event of protection equipment with time-tag CP56Time2a
        const type_id M_EP_TE_1 = 39; //Packed start events of protection equipment with time-tag CP56Time2a
        const type_id M_EP_TF_1 = 40; //Packed output circuit information of protection equipment with timetag CP56Time2a

        const type_id C_SC_NA_1 = 45; // Single command 
        const type_id C_DC_NA_1 = 46; // Double command
        const type_id C_RC_NA_1 = 47; // Regulating step command
        const type_id C_SE_NA_1 = 48; // Set point command, normalized value
        const type_id C_SE_NB_1 = 49; // Set point command, scaled value
        const type_id C_SE_NC_1 = 50; // Set point command, short floating point value
        const type_id C_BO_NA_1 = 51; // Bitstring of 32 bit
        const type_id C_SC_TA_1 = 58; // Single command with time tag CP56Time 2a 
        const type_id C_DC_TA_1 = 59; // Double command with time tag CP56Time 2a
        const type_id C_RC_TA_1 = 60; // Regulating step command with time tag CP56Time 2a
        const type_id C_SE_TA_1 = 61; // Set point command, normalized value with time tag CP56Time 2a
        const type_id C_SE_TB_1 = 62; // Set point command, scaled value with time tag CP56Time 2a
        const type_id C_SE_TC_1 = 63; // Set point command, short floating point value with time tag CP56Time 2a
        const type_id C_BO_TA_1 = 64; // Bitstring of 32 bit with time tag CP56Time 2a      

        const type_id M_EI_NA_1 = 70; //End of initialization

        const type_id C_IC_NA_1 = 100; // Interrogation command 100
        const type_id C_CI_NA_1 = 101; // Counter interrogation command
        const type_id C_RD_NA_1 = 102; // Read command
        const type_id C_CS_NA_1 = 103; // Clock synchronization command
        const type_id C_TS_NA_1 = 104; // Test command
        const type_id C_RP_NA_1 = 105; // Reset process command
        const type_id C_CD_NA_1 = 106; // Delay acquisition command
        const type_id C_TS_TA_1 = 107; // Test command with time tag CP56time2a      

        const type_id P_ME_NA_1 = 110; // Parameter of measured value, normalized value 110
        const type_id P_ME_NB_1 = 111; // Parameter of measured value, scaled value
        const type_id P_ME_NC_1 = 112; // Parameter of measured value, short floating point value
        const type_id P_AC_NA_1 = 113; // Parameter activation

        const type_id F_FR_NA_1 = 120; // File ready 120
        const type_id F_SR_NA_1 = 121; // Section ready
        const type_id F_SC_NA_1 = 122; // Call directory, select file, call file, call section
        const type_id F_LS_NA_1 = 123; // Last section, last segment
        const type_id F_AF_NA_1 = 124; // Ack file, ack section
        const type_id F_SG_NA_1 = 125; // Segment
        const type_id F_DR_TA_1 = 126; // Directory {blank or X, only available in monitor (standard) direction}
        const type_id F_SC_NB_1 = 127; // Query log ? Request archive file

        const interrogation_type INTERROG_GLOBAL = 20; // station interrogation (global)

        typedef std::pair<std::string, type_id> string_type_id_pair;
        typedef std::map<std::string, type_id> string_type_id_map;
        typedef std::pair<type_id, std::size_t> type_id_size_pair;
        typedef std::map<type_id, std::size_t> type_id_size_map;

        type_id find_type_id(const std::string& val);
        std::size_t find_type_size(type_id val);

        template<COT_sizetype COT, SECTOR_sizetype Selector, IOA_sizetype IOA>
        struct protocol_traits {

            static std::size_t selector_size() {
                return static_cast<std::size_t> (Selector);
            }

            static std::size_t start_selector() {
                return 2 + static_cast<std::size_t> (COT);
            }

            static std::size_t stop_selector() {
                return 2 + static_cast<std::size_t> (COT) + static_cast<std::size_t> (Selector);
            }

            static std::size_t min_size() {
                return 2 + static_cast<std::size_t> (COT) + static_cast<std::size_t> (Selector);
            }

            static std::size_t ioa_size() {
                return static_cast<std::size_t> (IOA);
            }

            static std::size_t cot_size() {
                return static_cast<std::size_t> (COT);
            }

            static bool has_OA() {
                return (static_cast<std::size_t> (COT) > 1);
            }

        };

        template<ADDRESS_sizetype LinkAddress>
        struct link_traits {

            static std::size_t link_size() {
                return static_cast<std::size_t> (LinkAddress);
            }

        };


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// dataobject
        /////////////////////////////////////////////////////////////////////////////////////////////////    


        class dataobject;
        typedef boost::shared_ptr<dataobject> dataobject_ptr;

        class dataobject {

        public:

            dataobject();

            dataobject(device_address dev, type_id tp, selector_address sel,
                    data_address addr, const octet_sequence& dt = octet_sequence());

            dataobject(device_address dev, type_id tp, selector_address sel,
                    data_address addr, bit_number bt, const octet_sequence& dt = octet_sequence());

            dataobject(device_address dev, type_id tp, selector_address sel, data_address addr,
                    cause_type cs, bool tst, bool neg, const octet_sequence& dt = octet_sequence());

            dataobject(device_address dev, type_id tp, selector_address sel, data_address addr,
                    bit_number bt, cause_type cs, bool tst, bool neg, const octet_sequence& dt = octet_sequence());

            ~dataobject() {
            };

            static dataobject_ptr create_activation_1(device_address dev, selector_address sel, cause_type cs = CS_ACT, interrogation_type tp = SC_INTERROG_GEN);


            static dataobject_ptr build_from_bind(device_address dev, std::string bind);

            device_address devnum() const {
                return devnum_;
            }

            cause_type cause() const {
                return cause_;
            }

            void cause(cause_type vl) {
                cause_ = vl;
            }

            bool test() const {
                return test_;
            }

            void test(bool vl) {
                test_ = vl;
            }

            bool negative() const {
                return negative_;
            }

            void negative(bool vl) {
                negative_ = vl;
            }

            selector_address selector() const {
                return selector_;
            }

            data_address ioa() const {
                return ioa_;
            }

            type_id type() const {
                return type_;
            }

            bit_number bit() const {
                return bit_;
            }

            bool has_bit() const {
                return bit_ != NULL_BITNUMBER;
            }

            const octet_sequence& data() const {
                return data_;
            }

            bool valid() const {
                return type_;
            }

            bool readable() const;

            bool command() const;

            bool service() const;

            friend bool operator==(const dataobject& ls, const dataobject& rs);
            friend bool operator<(const dataobject& ls, const dataobject& rs);

        protected:

            device_address devnum_;
            selector_address selector_;
            data_address ioa_;
            type_id type_;
            bit_number bit_;
            cause_type cause_;
            bool test_;
            bool negative_;
            octet_sequence data_;

        };

        bool operator==(dataobject_ptr ls, dataobject_ptr rs);
        bool operator<(dataobject_ptr ls, dataobject_ptr rs);


        typedef std::set<dataobject_ptr> dataobject_set;
        typedef std::vector<dataobject_ptr> dataobject_vct;
        typedef std::deque<dataobject_ptr> dataobject_deq;

        typedef std::pair<dvnci::indx, dataobject_ptr> indx_dataobject_pair;
        typedef std::vector<indx_dataobject_pair> indx_dataobject_vct;

        void error_and_valid_QDS(boost::uint8_t vl, vlvtype& vld, ns_error& err);
        datetime to_datetime_7(const octet_sequence& v);
        datetime to_datetime_3(const octet_sequence& vl);
        boost::int16_t to_int16_t(const octet_sequence& vl);
        float to_float_4(const octet_sequence& vl);

        dvnci::short_value to_short_value(dataobject_ptr v);





        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// asdu_body
        /////////////////////////////////////////////////////////////////////////////////////////////////

        const std::size_t MAX_ASDU_SIZE = 249;

        template<COT_sizetype COT, SECTOR_sizetype Selector, IOA_sizetype IOA>
        class asdu_body {

        public:

            typedef protocol_traits<COT, Selector, IOA> protocol_traits_type;

            asdu_body(dataobject_ptr vl, bool sq = false)
            : body_(new octet_sequence()) {
                body_->reserve(MAX_ASDU_SIZE);
                encode(vl, sq);
            };

            asdu_body(const dataobject_vct& vl, cause_type cs, std::size_t cnt, bool sq = false, bool ngt = false, bool tst = false)
            : body_(new octet_sequence()) { // sq = 1 only the first information object has an information object address, all other information objects have the addresses +1, +2, ...
                body_->reserve(MAX_ASDU_SIZE);
                encode(vl, cs, sq, ngt, tst);
            };

            asdu_body(const dataobject_vct& vl, cause_type cs, bool sq = false, bool ngt = false, bool tst = false)
            : body_(new octet_sequence()) {// sq = 0  each information object has its own information object address in the message       
                body_->reserve(MAX_ASDU_SIZE);
                encode(vl, cs, sq, ngt, tst);
            };

            asdu_body(octet_sequence_ptr dt) : body_(dt) {
            }

            ~asdu_body() {
            }

            static asdu_body create(dataobject_ptr vl, bool sq = false) {
                return asdu_body(vl);
            }

            octet_sequence& body() {
                return *body_;
            }

            const octet_sequence& body() const {
                return *body_;
            }

            octet_sequence_ptr body_ptr() const {
                return body_;
            }

            type_id type() const {
                if (!body().empty())
                    return body()[0];
                return 0;
            }

            bool sq() const {
                if (body().size() > 1)
                    return body()[1] & '\x80';
                return false;
            }

            std::size_t count() const {
                if (body().size() > 1)
                    return static_cast<std::size_t> (body()[1] & '\x7F');
                return 0;
            }

            bool test() const {
                if (body().size() > 2)
                    return body()[2] & '\x80';
                return false;
            }

            bool negative() const {
                if (body().size() > 2)
                    return body()[2] & '\x40';
                return false;
            }

            cause_type cause() const {
                if (body().size() > 2)
                    return static_cast<cause_type> (body()[2] & '\x3F');
                return 0;
            }

            boost::uint8_t oa() const {
                if ((protocol_traits_type::has_OA()) && (body().size() > 3))
                    return static_cast<boost::uint8_t> (body()[3]);
                return 0;
            }

            selector_address selector() const {
                if (body().size() >= protocol_traits_type::stop_selector())
                    if (protocol_traits_type::selector_size() == 1)
                        return *reinterpret_cast<const boost::uint8_t*> (&(body()[protocol_traits_type::start_selector()]));
                    else
                        return *reinterpret_cast<const device_address*> (&(body()[protocol_traits_type::start_selector()]));
                return 0;
            }

            bool get(dataobject_vct& rslt, device_address devaddr = 0) {
                rslt.clear();
                if (body().size() >= protocol_traits_type::min_size()) {
                    type_id tp = type();
                    selector_address selctr = selector();
                    std::size_t szdata = find_type_size(tp);
                    std::size_t datacnt = count();
                    std::size_t it = protocol_traits_type::min_size();
                    std::size_t ioasz = protocol_traits_type::ioa_size();
                    cause_type cs = cause();
                    bool tst = test();
                    bool neg = negative();
                    if (!datacnt)
                        return true;
                    if (szdata) {
                        if (sq()) {
                            if ((it + ioasz + szdata) <= body().size()) {
                                data_address addr = *reinterpret_cast<const data_address*> (&(body()[it])) & 0xFFFFFF;
                                octet_sequence data(&body()[it + ioasz], &body()[it + ioasz] + szdata);
                                rslt.push_back(dataobject_ptr(new dataobject(devaddr, tp, selctr, addr, cs, tst, neg, data)));
                                it = it + ioasz + szdata;
                                datacnt--;
                                while ((datacnt--) && ((it + szdata) <= body().size())) {
                                    octet_sequence data(&body()[it], &body()[it] + szdata);
                                    rslt.push_back(dataobject_ptr(new dataobject(devaddr, tp, selctr, ++addr, cs, tst, neg, data)));
                                    it = it + szdata;
                                }
                                return !(rslt.empty());
                            }
                        } else {
                            while ((datacnt--) && ((it + ioasz + szdata) <= body().size())) {
                                data_address addr = (*reinterpret_cast<const data_address*> (&(body()[it]))) & 0xFFFFFF;
                                octet_sequence data(&body()[it + ioasz], &body()[it + ioasz] + szdata);
                                rslt.push_back(dataobject_ptr(new dataobject(devaddr, tp, selctr, addr, cs, tst, neg, data)));
                                it = it + ioasz + szdata;
                            }
                            return !(rslt.empty());
                        }
                    }
                }
                return false;
            }

        private:

            void encode(dataobject_ptr vl, bool sq, sourse_type src = 0) {
                dataobject_vct tmp;
                tmp.push_back(vl);
                encode(tmp, sq, src);
            }

            void encode(const dataobject_vct& vl, bool sq, sourse_type src = 0) {
                if (!vl.empty()) {
                    dataobject_ptr hdrelm = vl[0];
                    encode(vl, hdrelm->cause(), sq, hdrelm->negative(), hdrelm->test(), src);
                }
            }

            void encode(dataobject_ptr vl, cause_type cs, bool sq, bool ngt, bool tst, sourse_type src = 0) {
                dataobject_vct tmp;
                tmp.push_back(vl);
                encode(tmp, cs, sq, ngt, tst, src);
            }

            void encode(const dataobject_vct& vl, cause_type cs, bool sq, bool ngt, bool tst, sourse_type src = 0) {
                body().clear();
                if (!vl.empty()) {
                    dataobject_ptr hdrelm = vl[0];
                    body().push_back(hdrelm->type());
                    boost::uint8_t szobj = static_cast<boost::uint8_t> (vl.size());
                    if (sq)
                        szobj |= '\x80';
                    body().push_back(szobj);
                    if (tst)
                        cs |= '\x80';
                    if (ngt)
                        cs |= '\x40';
                    body().push_back(cs);
                    if (protocol_traits_type::has_OA())
                        body().push_back(src);
                    selector_address tmpsel = hdrelm->selector();
                    body().insert(body().end(), (const char*) &tmpsel, (const char*) &tmpsel + protocol_traits_type::selector_size());
                    if (sq) {
                        for (dataobject_vct::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                            data_address tmpioa = (*it)->ioa();
                            body().insert(body().end(), (const char*) &tmpioa, (const char*) &tmpioa + protocol_traits_type::ioa_size());
                            body().insert(body().end(), (*it)->data().begin(), (*it)->data().end());
                        }
                    } else {
                        data_address tmpioa = hdrelm->ioa();
                        body().insert(body().end(), (const char*) &tmpioa, (const char*) &tmpioa + protocol_traits_type::ioa_size());
                        for (dataobject_vct::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                            body().insert(body().end(), (*it)->data().begin(), (*it)->data().end());
                        }
                    }
                }
            }


            octet_sequence_ptr body_;
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_data_listener
        /////////////////////////////////////////////////////////////////////////////////////////////////       

        class iec60870_data_listener : public boost::enable_shared_from_this<iec60870_data_listener> {

        public:

            virtual void execute60870(dataobject_ptr vl, const ns_error& error = 0) = 0;
            virtual void execute60870(const dataobject_vct& vl, const ns_error& error = 0) = 0;
            virtual void execute60870(device_address dev, const ns_error& error = 0) = 0;
            virtual void execute60870(const boost::system::error_code& err) = 0;
            virtual void terminate60870() = 0;

        };


        typedef boost::shared_ptr<iec60870_data_listener> iec60870_data_listener_ptr;
        typedef boost::weak_ptr<iec60870_data_listener> iec60870_data_listener_wptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_datanotificator
        /////////////////////////////////////////////////////////////////////////////////////////////////  

        class iec60870_datanotificator {

        public:

            iec60870_datanotificator(iec60870_data_listener_ptr listr);

            ~iec60870_datanotificator() {
            };

            void execute60870(dataobject_ptr vl, const ns_error& error = 0);
            void execute60870(const dataobject_vct& vl, const ns_error& error = 0);
            void execute60870(device_address dev, const ns_error& error = 0);

        protected:

            iec60870_data_listener_ptr listener();

            iec60870_data_listener_wptr listener_;
        };






        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_sector
        /////////////////////////////////////////////////////////////////////////////////////////////////  


        typedef std::pair<data_address, dataobject_ptr> ioa_dataobject_pair;
        typedef std::map<data_address, dataobject_ptr> ioa_dataobject_map;


        class iec60870_sector;
        typedef boost::shared_ptr<iec60870_sector> iec60870_sector_ptr;

        class iec60870_sector : public iec60870_datanotificator {

        public:

            enum SectorState {

                s_noaciveted, s_activate, s_confirmactivated, s_fullactivated, s_deactivate, s_deactivated, s_error
            };

            iec60870_sector(selector_address sl, iec60870_data_listener_ptr listr) :
            iec60870_datanotificator(listr), selector_(sl), state_(s_noaciveted) {
            }

            ~iec60870_sector() {
            }

            selector_address selector() const {
                return selector_;
            }

            SectorState state() const {
                return state_;
            }

            void state(SectorState vl);

            const ioa_dataobject_map& line() const {
                return line_;
            }

            dataobject_ptr operator()(data_address id) const;

            bool operator()(dataobject_ptr vl);

            bool as_service(dataobject_ptr vl);

            bool insert(dataobject_ptr vl);

            bool erase(dataobject_ptr vl);

            std::size_t size() const {
                return line_.size();
            }

            bool empty() const {
                return line_.empty();
            }


        private:

            selector_address selector_;
            SectorState state_;
            ioa_dataobject_map line_;

        };


        typedef std::pair<selector_address, iec60870_sector_ptr> id_selestor_pair;
        typedef std::map<selector_address, iec60870_sector_ptr> id_selestor_map;





        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_device
        /////////////////////////////////////////////////////////////////////////////////////////////////        


        class iec60870_device;
        typedef boost::shared_ptr<iec60870_device> iec60870_device_ptr;

        class iec60870_device : public iec60870_datanotificator {

        public:

            enum DeviceState {

                d_disconnect, d_connected
            };

            iec60870_device(device_address adr, std::size_t trycnt, iec60870_data_listener_ptr listr) :
            iec60870_datanotificator(listr), address_(adr), state_(d_disconnect), trycount_(trycnt ? trycnt : 3), currtrycount_(trycount_), fcb_(0) {
            }

            ~iec60870_device() {
            }

            device_address address() const {
                return address_;
            }

            DeviceState state() const {
                return state_;
            }

            void state(DeviceState vl);

            const id_selestor_map& sectors() const {
                return sectors_;
            }

            id_selestor_map& sectors() {
                return sectors_;
            }

            iec60870_sector_ptr operator()(selector_address id) const;

            dataobject_ptr operator()(selector_address sl, data_address id) const;

            bool operator()(dataobject_ptr vl);

            // result if new created
            iec60870_sector_ptr insert(selector_address vl);

            bool insert(dataobject_ptr vl);

            // result if realy erased            
            iec60870_sector_ptr erase(selector_address vl);

            bool erase(dataobject_ptr vl);

            std::size_t size() const {
                return sectors_.size();
            }

            bool empty() const;

            std::size_t trycount() const {
                return currtrycount_ ? currtrycount_ : 1;
            }

            void dec_trycount() {
                if (currtrycount_ > 1)
                    currtrycount_--;
            }

            bool fcb() {
                return ((++fcb_) % 2);
            }


        private:

            device_address address_;
            DeviceState state_;
            id_selestor_map sectors_;
            std::size_t trycount_;
            std::size_t currtrycount_;
            std::size_t fcb_;
        };


        typedef std::pair<device_address, iec60870_device_ptr> id_device_pair;
        typedef std::map<device_address, iec60870_device_ptr> id_device_map;






        const boost::system::error_code ERR_BADADDRESS = boost::system::error_code(boost::system::errc::bad_address, boost::system::system_category());
        const boost::system::error_code ERR_TIMEOUT = boost::system::error_code(boost::system::errc::timed_out, boost::system::system_category());
        const boost::system::error_code ERR_BEDSEQ = boost::system::error_code(boost::system::errc::illegal_byte_sequence, boost::system::system_category());


        const std::size_t PM_SHORT_TIMER = 10;

        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_PM
        /////////////////////////////////////////////////////////////////////////////////////////////////        

        class iec60870_PM : public iec60870_datanotificator {

        public:

            enum State {

                connected, disconnected
            };

            enum PMState {

                noconnected, noaciveted, activated, todisconnect
            };

            iec60870_PM(const iec_option& opt, timeouttype tout, iec60870_data_listener_ptr listr = iec60870_data_listener_ptr());

            virtual ~iec60870_PM();

            State state() const {
                return state_;
            }

            PMState pmstate() const {
                return pmstate_;
            }

            boost::system::error_code error() const {
                return error_cod;
            }

            void pmstate(PMState vl);

            virtual bool operator()();

            virtual bool add_items(const indx_dataobject_vct& cids, indx_dataobject_vct& rslt);

            virtual bool read_items(const dataobject_set& cids);

            virtual bool remove_items(const dataobject_set& cids);

            virtual void disconnect() = 0;


        protected:

            virtual void connect() = 0;

            virtual void terminate() = 0;

            virtual void work() {
            }

            virtual void update_model();

            virtual void update_model_insert();

            virtual void update_model_read();

            virtual void update_model_remove();

            virtual boost::system::error_code error(const boost::system::error_code& vl);

            const id_device_map& devices() const {
                return devices_;
            }

            id_device_map& devices() {
                return devices_;
            }

            std::size_t trycount() const {
                return trycount_ ? trycount_ : 3;
            }

            iec60870_device_ptr device(device_address dev) const;

            iec60870_device_ptr device(dataobject_ptr vl) const;

            iec60870_device_ptr insert_device(device_address dev);

            iec60870_device_ptr remove_device(device_address dev);


            iec60870_sector_ptr sector(device_address dev, selector_address slct) const;

            iec60870_sector_ptr sector(dataobject_ptr vl) const;

            iec60870_sector_ptr insert_sector(device_address dev, selector_address slct);

            iec60870_sector_ptr remove_sector(device_address dev, selector_address slct);

            dataobject_ptr data(dataobject_ptr vl) const;




            void execute_data(dataobject_ptr vl);

            void execute_data(const dataobject_vct& vl);

            void execute_error(device_address dev, const ns_error& error);

            virtual void insert_device_sevice(device_address dev) {
            };

            virtual void remove_device_sevice(device_address dev) {
            };

            virtual void insert_sector_sevice(device_address dev, selector_address slct) {
            };

            virtual void remove_sector_sevice(device_address dev, selector_address slct) {
            };

            virtual void insert_data_sevice(dataobject_ptr vl) {
            };

            virtual void remove_data_sevice(dataobject_ptr vl) {
            };


            boost::asio::io_service io_service_;
            boost::asio::deadline_timer tmout_timer;
            boost::asio::deadline_timer short_timer;
            std::size_t trycount_;
            volatile bool terminate_;
            volatile State state_;
            volatile PMState pmstate_;
            boost::system::error_code error_cod;
            timeouttype timout;
            bool need_disconnect_;
            id_device_map devices_;

            boost::mutex mtx;
            // start protected block
            dataobject_set additems_;
            dataobject_set removeitems_;
            // end protected block

            dataobject_set inrequestdata_;
            dataobject_deq waitrequestdata_;
            dataobject_deq waitcommanddata_;


        };

        typedef boost::shared_ptr<iec60870_PM> iec60870_PM_ptr;

    }
}

#endif	/* MODBUS_PROTOCOL_H */

