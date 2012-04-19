/* 
 * File:   expression.h
 * Author: Serg
 *
 * Created on 12 Май 2010 г., 12:50
 */

#ifndef _DVNCI_KRNL_EXPRESSION_H
#define	_DVNCI_KRNL_EXPRESSION_H

#include <kernel/constdef.h>
#include <kernel/systemutil.h>
#include <kernel/short_value.h>

namespace dvnci {
    namespace expr {

        const boost::wregex WFULLEXPR_REGEX = boost::wregex(utf8_to_wstr(FULLEXPR_REGEXTAMPL));

        /*Шаблон expression_templ прдоставляет сервис языка расчитываемых выражений.
          Параметром шаблона является интерфейс доступа к тегам. Требование к интерфейсу:
          BASEINTF = intf
          1. size_t          intf(std::string vl) возврат индекса тега по имени в таблице или npos при отсутствии.
          2. short_value     intf->value_shv(size_t id) возврат short_value (структуры значение и тип) для значения тега id
          3. tgtype          intf->typed(size_t id) возврат типа  тега id
          4. ns_error        intf->error(size_t id) возврат кода ошибки  тега id
          4. vlvtype         intf->valid(size_t id) возврат валидности для тега id
          5. short_value     intf->mineeu_typed(size_t id) возврат short_value (структуры значение и тип) для нижней границы шкалы тега id
          6. short_value     intf->maxeeu_typed(size_t id) возврат short_value (структуры значение и тип) для верхней границы шкалы тега id
          7. bool            intf->alarmon(size_t id) возврат установленного тревожного состояния для тега id
          8. bool            intf->alarmkvit(size_t id) возврат квитированного  тревожного состояния для тега id
          9. bool            intf->kvit(size_t id = npos) квитирование тега id ( npos - всех)
          10.                intf->send_command(calcstack.top().id, short_value vl) посылка команды  vl тега id
         *
         *       Операции допустимые в выражениях, соответствуют операциям языка C++ , за исключением операций присваивания (=,+=,-= ..),
         * косвенного обращения и разыменовывания (->, *), функции (), выделения элемента [], определения размера sizeof и постфикных ++, --
         *       Операция  определения адреса (&) изменяет смысл и действует таким образом , что операнд приобретает валидность.
         * Kроме того, вводятся дополнительные операции:
         *          1. Операция @  (@@, @=, @@=) - посылка команды. (@@ с постановкой в очередь, @=, @@= c установкой значения)
         *          Вырважение tag @ expr означает посыку команды val.value. Команда не посылается в случае нулевой валидности expr
         *          Операция возвращает значение и в во многом (в том числе приоритетом) соответсвует присваиванию ( т.е "tag1 @ ((tag2 @ expr) + 1)" - корректно )
         *          2. Операция квитирования #
         *          Выражение #tag означает квитирование тега tag (включая группу алармовую группу)
         *
         * Селекторные операции над тегами:
          1. .mineu, .maxeu - минимальные и максимальные границы значений (пример tag.mineu), имеет тип тега
          2. .ack, .alarm, .alarmack - квитированная тревожноое состояние, тревожное и квитированное с проверкой
             тревожности для тега (пример tag.ack), имеет тип bool
          3. .time, .logtime - время установки значения и время установки предыдущего значения для тега (пример tag.time), имеет тип datetime
          4. .lastvalue - предыдущее значение  тега (пример tag.lastvalue), имеет тип тега
          5  .epoch, .msc ,.sec, .minute, .hour, .day, .month, .monthdays, .year
             .dayweek, .dayyear, .epochmsc, .epochday, .epochhour, .epochminute - селекторы для значений типа TYPE_TM ( переменная now,
         *    результат возвращаемый селекторами .time .logtime и теги типа TYPE_TM. Возвращемый тип TYPE_NUM64
         *
         * Функции преобразования типов: (notype), (num64), (unum64), (num32), (unum32), (num16)
                                         (unum16), (num8), (unum8), (float), (double), (bool). Пример: (float)tag или (double)(tag1 / tag2 - 1)
         * Существует простой аналог в селекторной нотации tag.num == (num64)tag, tag.bool == (bool)tag, tag.real == (double)tag
         *
         * Математические функции: abs, sin, cos, pow, sqrt, sqr, exp, ln, rnd, floor, trunc, min( arg1, arg2), max( arg1 , arg2) : Пример: sin(tag1)
         *
         * Операция условия может иметь произвольное число вложений, что позволяет осуществлять case - логику
         * Пример tag @ ( ( tag0 == 1) ? tag1 : (( tag0 == 2) ? tag2 : null))
         *
         * Функции инкримента для типа TYPE_TM :   incmsc, incsec, incminute, inchour, incday. Пример: incminute(now, 10) или incsec(tag.time, 12)
         *
         * Константы pi , e и переменная текущего времени now;
         */

        /* calc_operation
         * Основные операторы, селекторы и функции
         * До 1000 хранятся операнды, так как они тоже участвуют в очередях и стеках.
         * Приоритет определет численный номер (/1000) и имеет обратную интерпетацию
         * ( чем меньше число, тем выще приоритет).
         *  Левоассоцированные четны, правоассоциированные нечетны
         *
         */

        enum calc_operation {
            notoperation = 0,
            expr = 1,
            constant = 2,

            oprt_leftgroup = 1000, // (  1
            oprt_rightgroup = 1002, // )  1
            select_mineu = 1006,
            select_maxeu = 1008,
            select_ack = 1010,
            select_alarmack = 1012,
            select_alarm = 1014,
            select_mod = 1016,
            select_num = 1018,
            func_num = 1019,
            select_real = 1020,
            func_real = 1021,
            select_bool = 1022,
            func_bool = 1023,
            func_min = 1025,
            func_max = 1027,
            func_abs = 1029,
            func_sin = 1031,
            func_cos = 1033,
            func_pow = 1035,
            func_sqrt = 1037,
            func_sqr = 1039,
            func_exp = 1041,
            func_ln = 1043,
            func_rnd = 1047,
            func_floor = 1049,
            func_ceiling = 1051,
            func_round = 1053,
            const_e = 1055,
            const_pi = 1057,
            const_nan = 1059,
            const_now = 1061,
            oprt_selector = 1052, // .  1
            oprt_caseleftgroup = 1058, // [
            oprt_caserightgroup = 1060, // ]
            oprt_prefinc = 1062, /* ++*/
            oprt_prefdec = 1064, /* --*/
            select_time = 1066, /*  .time*/
            select_logtime = 1068, /*  .logtime*/
            select_error = 1070, /* .error*/
            select_valid = 1072, /* .valid*/
            select_epoch = 1074, /* .epoch*/
            select_msc = 1076, /* .msc*/
            select_sec = 1078, /* .sec*/
            select_minute = 1080, /* .minute*/
            select_hour = 1082, /* .hour*/
            select_day = 1084, /* .day*/
            select_month = 1086, /* .month*/
            select_year = 1088, /* .year*/
            select_dayweek = 1090, /* .dayweek*/
            select_dayyear = 1092, /* .dayyear*/
            select_epochmsc = 1094, /* .dayyear*/
            select_epochminute = 1096, /* .epochminute*/
            select_epochhour = 1098, /* .epochhour*/
            select_epochday = 1100, /* .epochday*/
            select_monthdays = 1102, /* .epochday*/
            select_lastvalue = 1104, /* .lastvalue*/
            func_incmsc = 1105, /* incmsc(*/
            func_incsec = 1107, /* incsec(*/
            func_incminute = 1109, /* incminute(*/
            func_inchour = 1111, /* inchour(*/
            func_incday = 1113, /* incday(*/
            func_log10 = 1115, /* log10*/
            func_tan = 1117, /* tan*/
            func_acos = 1119, /* acos*/
            func_asin = 1121, /* asin*/
            func_atan = 1123, /* atan*/
            func_cosh = 1125, /* cosh*/
            func_sinh = 1127, /* sinh*/
            func_tanh = 1129, /* tanh*/
            func_format = 1131, /* format*/
            select_comment = 1110, /* .comment*/
            select_binding = 1112, /* .binding*/
            select_eu = 1114, /* .eu*/
            select_alarmmsg = 1116, /* .alarmmsg*/
            oprt_opnot = 2001, // !  2
            oprt_opexnot = 2003, // ~  2
            oprt_add_unary = 2005, // +   2
            oprt_sub_unary = 2007, // -   2
            oprt_allvalid_unary = 2009, // -   &tag allways valid
            oper_cast_basetype = 2021, // (notype)
            oper_cast_num64 = 2023, // (num64)
            oper_cast_unum64 = 2025, // (unum64)
            oper_cast_num32 = 2027, // (num32)
            oper_cast_unum32 = 2029, // (unum32)
            oper_cast_num16 = 2031, // (num16)
            oper_cast_unum16 = 2033, // (unum16)
            oper_cast_num8 = 2035, // (num8)
            oper_cast_unum8 = 2037, // (unum8)
            oper_cast_float = 2039, // (float)
            oper_cast_double = 2041, // (double)
            oper_cast_bool = 2043, // (bool)
            oper_cast_time = 2045, // (time)
            oper_cast_text = 2049, // (text)
            oper_cast_vbool = 2051, // (vbool)
            oprt_mult = 3000, // *   3
            oprt_div = 3002, // /  3
            oprt_modulo = 3004, //  %  3
            oprt_add = 4000, // +   4
            oprt_sub = 4002, // -   4
            oprt_bitleft = 5000, // <<   5
            oprt_bitright = 5002, // >>   5
            oprt_cyclbitleft = 5004, // <<<   5
            oprt_cyclbitright = 5006, // >>>   5
            oprt_compless = 6000, // <    6
            oprt_complessoreq = 6002, // <= 6
            oprt_compmore = 6004, // >    6
            oprt_compmoreoreq = 6006, // >= 6
            oprt_compeq = 7000, // ==    7
            oprt_compnoteq = 7002, // != 7
            oprt_bitand = 8000, // & 8
            oprt_bitexor = 9000, // ^ 9
            oprt_bitor = 10000, // | 10
            oprt_logicand = 11000, // && 11
            oprt_logicor = 12000, // || 12
            oprt_condit = 13001, //  ?
            oprt_casedelim = 13058, /* :*/
            oprt_command = 14000, /* @*/
            oprt_kvit = 14051, /* #*/
            oprt_command1 = 14020, /* @@*/
            oprt_commandset = 14060, /* @= */
            oprt_commandset1 = 14080, /* @@ =*/
            //oprt_command2 = 14040, /* @@@*/
            oprt_postinc = 15000, /* ++*/
            oprt_comma = 15002, //1004,             //,            
            oprt_postdec = 15020, /* --*/
        } ;

        class exprintf_stub {
        public:

            typedef num32 struct_type;
            typedef struct_type *struct_type_ptr;

            exprintf_stub() {}

            ~exprintf_stub() {}

            indx operator()(std::string vl) const {
                return npos;}

            struct_type_ptr operator[](indx vl) const {
                return 0;}

            bool operator[] (std::string vl) {
                return false;}

            std::string name(indx id) const {
                return "";}

            datetime time(indx id) const {
                return nill_time;}

            datetime time_log(indx id) const {
                return nill_time;}

            short_value value_shv(indx id) const {
                return short_value();}

            short_value value_log_shv(indx id) const {
                return short_value();}

            tagtype type(indx id) const {
                return 0;}

            ns_error error(indx id) const {
                return ERROR_NILLINF;}

            vlvtype valid(indx id) const {
                return 0;}

            short_value mineu_shv(indx id) const {
                return short_value();}

            short_value maxeu_shv(indx id) const {
                return short_value();}

            bool alarmon(indx id) const {
                return false;}

            bool alarmkvit(indx id) const {
                return false;}

            bool kvit(indx id = npos) {
                return false;}

            void send_command(indx id, const short_value& vl, addcmdtype queue = acQueuedCommand, indx clid = npos) {};

            void incref(indx id) {}

            void decref(indx id) {}} ;



        std::ostream & operator<<(std::ostream& os, calc_operation oper);

        class calc_token {
        public:

            calc_token() : shv_(), id_(npos), operation_(notoperation) {};

            calc_token(bool val) : shv_(val), id_(npos), operation_(constant) {};

            calc_token(num64 val) : shv_(val), id_(npos), operation_(constant) {};

            calc_token(unum64 val) : shv_(val), id_(npos), operation_(constant) {};

            calc_token(num32 val) : shv_(val), id_(npos), operation_(constant) {};

            calc_token(unum32 val) : shv_(val), id_(npos), operation_(constant) {};

            calc_token(num16 val) : shv_(val), id_(npos), operation_(constant) {};

            calc_token(unum16 val) : shv_(val), id_(npos), operation_(constant) {};

            calc_token(num8 val) : shv_(val), id_(npos), operation_(constant) {};

            calc_token(unum8 val) : shv_(val), id_(npos), operation_(constant) {};

            calc_token(float val) : shv_(val), id_(npos), operation_(constant) {};

            calc_token(double val) : shv_(val), id_(npos), operation_(constant) {};

            calc_token(const datetime& val) : shv_(val), id_(npos), operation_(constant) {};

            calc_token(const short_value& val, indx idx = npos) : shv_(val), id_(idx), operation_(constant) {};

            calc_token(const std::string& val) : shv_(val), id_(npos), operation_(constant) {};

            calc_token(const calc_operation& val) : shv_(), id_(npos), operation_(val) {};

            calc_token(indx idtag, tagtype type, ns_error err) : shv_(0, type, 0, err),
            id_(idtag), operation_(expr) {};

            num64 value() const {
                return shv_.value64();}

            void value(num64 val) {
                shv_.value64(val);}

            short_value value_shv() {
                return shv_;}

            tagtype type() const {
                return shv_.type();}

            void type(tagtype val) {
                shv_.type(val);}

            vlvtype valid() const {
                return shv_.valid();
                ;}

            void valid(vlvtype val) {
                shv_.valid(val);}

            datetime time() const {
                return shv_.time();}

            void time(datetime val) {
                shv_.time(val);}

            ns_error error() const {
                return shv_.error();}

            void error(ns_error val) {
                shv_.error(val);}

            indx id() const {
                return id_;}

            void id(indx val) {
                id_ = val;}

            calc_operation operation() const {
                return operation_;}

            void operation(calc_operation val) {
                operation_ = val;}

            calc_token getnum() const {
                if (operation() != constant) return NULL_DOUBLE;
                return value<num64 > ();}

            calc_token getreal() const {
                if (operation() != constant) return NULL_DOUBLE;
                return value<double>();}

            calc_token getbool() const {
                if (operation() != constant) return NULL_DOUBLE;
                return value<bool>();}

            calc_token gettypedval(calc_operation oper);

            template <typename T>
            T value() const {
                return shv_.value<T > ();}

            bool needassign() const {
                return ((operation() == expr) && (id() != npos));}

            bool isoperation() const {
                return ((operation_ != notoperation) &&
                        (operation_ != expr) && (operation_ != constant));}

            bool isnan() const {
                return (((operation_ == constant) && (num64_and_type_cast<double>(value(), type()) !=
                        num64_and_type_cast<double>(value(), type()))));}

            bool isnumber() const {
                return ((operation_ == expr) && (operation_ == constant));}

            bool iserror() const {
                return ((!isoperation()) && (error() != NS_ERROR_SUCCESS));}

            std::string to_string() const {
                if (isoperation()) return "op" + to_str<int>(static_cast<int> (operation())) + " ";
                return operation() == expr ? to_str(id_) : shv_.value<std::string > ();}

            short_value to_valuetype() {
                return shv_;}

            void set_unary() {
                if (operation_ == oprt_add) operation_ = oprt_add_unary;
                if (operation_ == oprt_sub) operation_ = oprt_sub_unary;
                if (operation_ == oprt_bitand) operation_ = oprt_allvalid_unary;}

            void set_postfix() {
                if (operation_ == oprt_prefinc) operation_ = oprt_postinc;
                if (operation_ == oprt_prefdec) operation_ = oprt_postdec;}

            static int operationpriority(calc_operation val) {
                return ((static_cast<int> (val)) / 1000);}

            static bool find_unaryoperator(calc_operation val) {
                return (((static_cast<int> (val)) >= 2000) || (static_cast<int> (val) == oprt_leftgroup) || (static_cast<int> (val) == oprt_comma));}

            static bool find_post_pref_operator(calc_operation val) {
                return ((static_cast<int> (val) == oprt_prefinc) || (static_cast<int> (val) == oprt_prefdec) ||
                        (static_cast<int> (val) == oprt_postinc) || (static_cast<int> (val) == oprt_postdec));}

            static bool is_rightside_operation(calc_operation val) {
                return (((static_cast<int> (val)) % 2) != 0);}

            static bool can_unary(calc_operation val) {
                return ((val == oprt_add) || (val == oprt_sub) || (val == oprt_bitand));}

            static bool can_post_pref(calc_operation val) {
                return ((static_cast<int> (val) == oprt_prefinc) || (static_cast<int> (val) == oprt_prefdec) ||
                        (static_cast<int> (val) == oprt_postinc) || (static_cast<int> (val) == oprt_postdec));}

            static bool is_group(calc_operation val) {
                return ((val == oprt_leftgroup) || (val == oprt_rightgroup) || (val == oprt_caseleftgroup));}

            static bool is_need_popstack(calc_operation ls, calc_operation rs) {
                return ((operationpriority(ls) < operationpriority(rs)) ||
                        ((operationpriority(ls) == operationpriority(rs) && (!is_rightside_operation(rs)))));}

            friend tagtype type_cast(const calc_token& v1, const calc_token& v2);

            friend calc_token operator+(const calc_token& lside, const calc_token& rside);
            friend calc_token operator-(const calc_token& lside, const calc_token& rside);
            friend calc_token operator-(calc_token& nval);
            friend calc_token operator*(const calc_token& lside, const calc_token& rside);
            friend calc_token operator/(const calc_token& lside, const calc_token& rside);
            friend calc_token operator%(const calc_token& lside, const calc_token& rside);
            friend bool operator==(const calc_token& lside, const calc_token& rside);

            friend bool operator!=(const calc_token& lside, const calc_token& rside) {
                return !(operator==(lside, rside));}

            friend bool operator<(const calc_token& lside, const calc_token& rside);

            friend bool operator>=(const calc_token& lside, const calc_token& rside) {
                return !(operator<(lside, rside));}

            friend bool operator>(const calc_token& lside, const calc_token& rside);

            friend bool operator<=(const calc_token& lside, const calc_token& rside) {
                return !(operator>(lside, rside));}

            friend bool operator!(calc_token& nval);
            friend calc_token operator~(calc_token& nval);
            friend bool operator&&(const calc_token& lside, const calc_token& rside);
            friend bool operator||(const calc_token& lside, const calc_token& rside);
            friend calc_token operator&(const calc_token& lside, const calc_token& rside);
            friend calc_token operator|(const calc_token& lside, const calc_token& rside);
            friend calc_token operator^(const calc_token& lside, const calc_token& rside);
            friend calc_token operator<<(const calc_token& lside, const calc_token& rside);
            friend calc_token operator>>(const calc_token& lside, const calc_token& rside);
            friend calc_token cycl_operator_btlft(const calc_token& lside, const calc_token& rside);
            friend calc_token cycl_operator_btrgt(const calc_token& lside, const calc_token& rside);
            calc_token math_func1(calc_operation opr);
            calc_token getabs();
            friend calc_token math_pow(const calc_token& lside, const calc_token& rside);
            friend calc_token minim(const calc_token& lside, const calc_token& rside);
            friend calc_token maxim(const calc_token& lside, const calc_token& rside);
            datetime tm() const;

        private:

            short_value shv_;
            indx id_;
            calc_operation operation_;} ;

        template<typename BASEINTF, typename REFCOUNTER = refcounter_templ<BASEINTF> >
                class expression_templ {
            typedef BASEINTF interface_type;
            typedef membase_sync_ptr_tmpl<interface_type> interface_type_ptr;
            typedef REFCOUNTER refcounter_type;
            typedef boost::shared_ptr<refcounter_type> refcounter_type_ptr;

            typedef std::stack<calc_token> polishstack;
            typedef std::vector<calc_token> polishline;
            typedef typename polishline::iterator polishline_iterator;
            typedef typename polishline::const_iterator polishline_constiterator;
            typedef str_vect exprstack;

        public:

            enum const_type {
                hex_const, dec_const, oct_const, bin_const, real_const, none_const} ;

            expression_templ(const std::string& val, interface_type_ptr inf) : changepoll(false), intf(inf), error_(ERROR_EXPRNOINIT), expression_("") {
                refcntr = refcounter_type_ptr(new refcounter_type(intf));
                refcntr->active(true);
                expressionstr(val);};

            expression_templ(const std::string& val = "") : changepoll(false), intf(), error_(ERROR_EXPRNOINIT), expression_("") {
                refcntr = refcounter_type_ptr();
                expressionstr(val);};
                
            expression_templ(const std::wstring& val, interface_type_ptr inf) : changepoll(false), intf(inf), error_(ERROR_EXPRNOINIT), expression_("") {
                refcntr = refcounter_type_ptr(new refcounter_type(intf));
                refcntr->active(true);
                expressionstr(val);};
              

            virtual ~expression_templ() {}

            short_value value() {
                calculate();
                return error() ? short_value() : rslt.value_shv();}

            vlvtype valid() const {
                return (error_) ? 0 : rslt.valid();}

            friend std::ostream & operator<<(std::ostream& os, expression_templ& ns) {
                ns.calculate();
                if (ns.error()) {
                    return os << "error calculate expassion";}
                return os << "value=" << ns.rslt.to_string() << " valid=" << ns.rslt.valid();}

            friend std::string & operator>>(std::string& str, expression_templ& ns) {
                ns.calculate();
                if (error()) {
                    return str = "error";}
                return str = ns.rslt.to_string();}

            template<typename T>
            T value_cast() {
                calculate();
                return error() ? 0 : num64_and_type_cast<T > (rslt.value(), rslt.type());}

            std::string expressionstr() const {
                return expression_;}

            bool active() const {
                return (refcntr) ? refcntr->active() : false;}

            void active(bool val) {
                if (refcntr) refcntr->active(val);}

            ns_error error() const {
                return error_;}

            ns_error testerror() {
                calculate();
                return error();}

            bool rebuild_if_need(indx id = npos);

            const indx_set& indexes() const {
                return refcntr ? refcntr->indexes() : indexes_;}


        protected:

            ns_error error(ns_error er) {
                return error_ = er;}

            void expressionstr(std::string val) {
                lower_and_fulltrim(val);
                parse(val);
                expression_ = val;}
            
            void expressionstr(std::wstring val) {
                lower_and_fulltrim(val);
                parse(val);
                expression_ = wstr_to_utf8(val);}

            calc_token getoperation(std::string val);

            const_type parseconstype(std::string& val, bool& flt) {
                flt = false;
                std::string::size_type posFloat = val.find_last_of("f");
                if (val.find_first_of(".") != std::string::npos) {
                    flt = (posFloat != std::string::npos);
                    if (posFloat != std::string::npos) {
                        val = val.substr(0, posFloat);}
                    return real_const;}
                if (val.find("0b") == 0) {
                    val = val.substr(2);
                    return bin_const;}
                if (val.find("0x") == 0) {
                    val = val.substr(2);
                    return hex_const;}
                flt = (posFloat != std::string::npos);
                if (posFloat != std::string::npos) {
                    val = val.substr(0, posFloat);}
                if (flt) return real_const;
                if (((val.find_first_of("0") == 0) && (val.size() > 1))) {
                    val = val.substr(1);
                    return oct_const;}
                if (flt) return real_const;
                return dec_const;}

            calc_token testconst(std::string val);

            calc_token getmineu(calc_token& it);

            calc_token getmaxeu(const calc_token& it);

            virtual calc_token gettime(const calc_token& it);

            virtual calc_token getlogtime(const calc_token& it);

            virtual calc_token getvalid(const calc_token& it);

            virtual calc_token geterror(const calc_token& it);

            virtual calc_token getalarm(const calc_token& it);

            virtual calc_token getack(const calc_token& it);

            virtual calc_token getalarmack(const calc_token& it);

            virtual calc_token getcomment(const calc_token& it);

            virtual calc_token getbinding(const calc_token& it);

            virtual calc_token geteu(const calc_token& it);

            virtual calc_token getalarmmsg(const calc_token& it);

            virtual calc_token calc_token_factory(const std::string& val);

            virtual calc_token assignexpr(const calc_token& it);

            virtual calc_token assignlastexpr(const calc_token& it);

            ns_error calculate();

            ns_error caseswitch(polishline_iterator& iter, const calc_token& tkn);

            ns_error parse(std::string val);

            ns_error parse(std::wstring val);

            ns_error parsetoken();

            void print_line(const polishline& ln);

            calc_token prepareitem(calc_token& val) {
                if (!val.needassign()) return val;
                else return assignexpr(val);}

            calc_token preparelastitem(calc_token& val) {
                if (!val.needassign()) return val;
                else return assignlastexpr(val);}

            void clearstack() {
                while (!calcstack.empty()) calcstack.pop();}

            void clearall() {
                clearstack();
                polline.clear();
                stringvector.clear();}


            polishstack calcstack;
            polishline polline;
            bool changepoll;
            polishline savedpolline;
            exprstack stringvector;
            calc_token rslt;
            interface_type_ptr intf;
            refcounter_type_ptr refcntr;
            ns_error error_;
            std::string expression_;
            indx_set indexes_;} ;

        template<typename BASEINTF, typename REFCOUNTER>
        bool expression_templ<BASEINTF, REFCOUNTER>::rebuild_if_need(indx id) {
            if ((intf) || (id == npos) || (error()) || ((refcntr) && (refcntr->index_included(id)))) {
                clearall();
                refcounter_type_ptr refcntrtmp = refcounter_type_ptr(new refcounter_type(intf));
                if (refcntr) refcntr.swap(refcntrtmp);
                else refcntr = refcntrtmp;
                expressionstr(expression_);
                return true;}
            return false;}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::getoperation(std::string val) {
            if (val.empty()) return calc_token(notoperation);
            lower_and_trim(val);
            if (val.size() == 1) {
                char vltmp = *(val.c_str());
                switch (vltmp) {
                    case '(': return calc_token(oprt_leftgroup);
                    case ')': return calc_token(oprt_rightgroup);
                    case '!': return calc_token(oprt_opnot);
                    case '*': return calc_token(oprt_mult);
                    case '/': return calc_token(oprt_div);
                    case '%': return calc_token(oprt_modulo);
                    case '+': return calc_token(oprt_add);
                    case '-': return calc_token(oprt_sub);
                    case '<': return calc_token(oprt_compless);
                    case '>': return calc_token(oprt_compmore);
                    case '=': return calc_token(oprt_compeq);
                    case '&': return calc_token(oprt_bitand);
                    case '^': return calc_token(oprt_bitexor);
                    case '|': return calc_token(oprt_bitor);
                    case '~': return calc_token(oprt_opexnot);
                    case ',': return calc_token(oprt_comma);
                    case ':': return calc_token(oprt_casedelim);
                    case '[': return calc_token(oprt_caseleftgroup);
                    case ']': return calc_token(oprt_caserightgroup);
                    case '@': return calc_token(oprt_command);
                    case '#': return calc_token(oprt_kvit);
                    case '?': return calc_token(oprt_condit);}}
            if (val.size() == 2) {
                if (val == "<<") return calc_token(oprt_bitleft);
                if (val == ">>") return calc_token(oprt_bitright);
                if (val == "==") return calc_token(oprt_compeq);
                if (val == "!=") return calc_token(oprt_compnoteq);
                if (val == "<=") return calc_token(oprt_complessoreq);
                if (val == ">=") return calc_token(oprt_compmoreoreq);
                if (val == "||") return calc_token(oprt_logicor);
                if (val == "&&") return calc_token(oprt_logicand);
                if (val == "++") return calc_token(oprt_prefinc);
                if (val == "--") return calc_token(oprt_prefdec);
                if (val == "''") return calc_token("");
                if (val == "@@") return calc_token(oprt_command1);
                if (val == "@=") return calc_token(oprt_commandset);
                if (val == "\"\"") return calc_token("");}
            if (val == "<<<") return calc_token(oprt_cyclbitleft);
            if (val == ">>>") return calc_token(oprt_cyclbitright);
            if (val == "@@=") return calc_token(oprt_commandset1);
            if (val == "mod") return calc_token(select_mod);
            if (val == ".mineu") return calc_token(select_mineu);
            if (val == ".maxeu") return calc_token(select_maxeu);
            if (val == ".ack") return calc_token(select_ack);
            if (val == ".alarm") return calc_token(select_alarm);
            if (val == ".alarmack") return calc_token(select_alarmack);
            if (val == ".num") return calc_token(select_num);
            if (val == "num") return calc_token(func_num);
            if (val == ".real") return calc_token(select_real);
            if (val == "real") return calc_token(func_real);
            if (val == ".bool") return calc_token(select_bool);
            if (val == "bool") return calc_token(func_bool);
            if (val == "abs") return calc_token(func_abs);
            if (val == "min") return calc_token(func_min);
            if (val == "max") return calc_token(func_max);
            if (val == "sin") return calc_token(func_sin);
            if (val == "cos") return calc_token(func_cos);
            if (val == "pow") return calc_token(func_pow);
            if (val == "sqrt") return calc_token(func_sqrt);
            if (val == "sqr") return calc_token(func_sqr);
            if (val == "exp") return calc_token(func_exp);
            if (val == "log") return calc_token(func_ln);
            if (val == "ln") return calc_token(func_ln);
            if (val == "log10") return calc_token(func_log10);
            if (val == "tan") return calc_token(func_tan);
            if (val == "acos") return calc_token(func_acos);
            if (val == "asin") return calc_token(func_asin);
            if (val == "atan") return calc_token(func_atan);
            if (val == "format") return calc_token(func_format);
            if (val == ".comment") return calc_token(select_comment);
            if (val == ".binding") return calc_token(select_binding);
            if (val == ".eu") return calc_token(select_eu);
            if (val == ".alarmmsg") return calc_token(select_alarmmsg);
            if (val == "cosh") return calc_token(func_cosh);
            if (val == "sinh") return calc_token(func_sinh);
            if (val == "tanh") return calc_token(func_tanh);
            if (val == "rnd") return calc_token(func_rnd);
            if (val == "floor") return calc_token(func_floor);
            if (val == "seil") return calc_token(func_ceiling);
            if (val == "round") return calc_token(func_round);
            if (val == "e") return calc_token(const_e);
            if (val == "null") return calc_token(NULL_DOUBLE);
            if (val == "nan") return calc_token(NULL_DOUBLE);
            if (val == "pi") return calc_token(const_pi);
            if (val == "incmsc") return calc_token(func_incmsc);
            if (val == "incsec") return calc_token(func_incsec);
            if (val == "incminute") return calc_token(func_incminute);
            if (val == "inchour") return calc_token(func_inchour);
            if (val == "incday") return calc_token(func_incday);
            if (val == "(notype)") return calc_token(oper_cast_basetype);
            if (val == "(num64)") return calc_token(oper_cast_num64);
            if (val == "(unum64)") return calc_token(oper_cast_unum64);
            if (val == "(num32)") return calc_token(oper_cast_num32);
            if (val == "(unum32)") return calc_token(oper_cast_unum32);
            if (val == "(num16)") return calc_token(oper_cast_num16);
            if (val == "(unum16)") return calc_token(oper_cast_unum16);
            if (val == "(num8)") return calc_token(oper_cast_num8);
            if (val == "(unum8)") return calc_token(oper_cast_unum8);
            if (val == "(float)") return calc_token(oper_cast_float);
            if (val == "(double)") return calc_token(oper_cast_double);
            if (val == "(bool)") return calc_token(oper_cast_bool);
            if (val == "(vbool)") return calc_token(oper_cast_vbool);
            if (val == "(time)") return calc_token(oper_cast_time);
            if (val == "(text)") return calc_token(oper_cast_text);
            if (val == "now") return calc_token(const_now);
            if (val == ".time") return calc_token(select_time);
            if (val == ".logtime") return calc_token(select_logtime);
            if (val == ".error") return calc_token(select_error);
            if (val == ".valid") return calc_token(select_valid);
            if (val == ".epoch") return calc_token(select_epoch);
            if (val == ".msc") return calc_token(select_msc);
            if (val == ".sec") return calc_token(select_sec);
            if (val == ".minute") return calc_token(select_minute);
            if (val == ".hour") return calc_token(select_hour);
            if (val == ".day") return calc_token(select_day);
            if (val == ".month") return calc_token(select_month);
            if (val == ".monthdays") return calc_token(select_monthdays);
            if (val == ".year") return calc_token(select_year);
            if (val == ".dayweek") return calc_token(select_dayweek);
            if (val == ".dayyear") return calc_token(select_dayyear);
            if (val == ".epochmsc") return calc_token(select_epochmsc);
            if (val == ".epochday") return calc_token(select_epochday);
            if (val == ".epochhour") return calc_token(select_epochhour);
            if (val == ".epochminute") return calc_token(select_epochminute);
            if (val == ".lastvalue") return calc_token(select_lastvalue);
            return testconst(val);};

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::testconst(std::string val) {
            boost::regex ex(NUMBER_REGEXTAMPL_EXT);
            boost::smatch xResults;
            if (boost::regex_match(val, xResults, ex)) {
                //DEBUG_STR_VAL_DVNCI(ISNUMERIC_CONST, val)
                std::string::size_type posLong = val.find_last_of("l");
                std::string::size_type posUnsign = val.find_last_of("u");
                std::string::size_type posLongUnsign = val.find_first_of("lu");
                std::string::size_type posUnsignLong = val.find_first_of("ul");
                bool isFloat = false;
                bool isLong = ((posLong != std::string::npos) || (posUnsignLong != std::string::npos) || (posLongUnsign != std::string::npos));
                bool isUnsign = ((posUnsign != std::string::npos) || (posUnsignLong != std::string::npos) || (posLongUnsign != std::string::npos));
                if (posLongUnsign != std::string::npos) {
                    val = val.substr(0, posLongUnsign);}
                else if (posUnsignLong != std::string::npos) {
                    val = val.substr(0, posUnsignLong);}
                else if (posLong != std::string::npos) {
                    val = val.substr(0, posLong);}
                else if (posUnsign != std::string::npos) {
                    val = val.substr(0, posUnsign);}

                //DEBUG_VAL_DVNCI(isLong)
                //DEBUG_VAL_DVNCI(isUnsign)
                //DEBUG_VAL_DVNCI(val)
                switch (parseconstype(val, isFloat)) {
                    case real_const:{
                        if (isFloat) {
                            float tmpfl = 0;
                            if (str_to(val, tmpfl)) {
                                return calc_token(tmpfl);}
                            else {
                                return calc_token(NULL_DOUBLE);}}
                        double tmpdbl = NULL_DOUBLE;
                        str_to(val, tmpdbl);
                        return calc_token(tmpdbl);}
                    case bin_const:{
                        if (isLong) {
                            if (isUnsign) {
                                unum64 tmp = 0;
                                if (binstr_to<unum64 > (val, tmp)) {
                                    return calc_token(tmp);}}
                            else {
                                num64 tmp = 0;
                                if (binstr_to<num64 > (val, tmp)) {
                                    return calc_token(tmp);}}}
                        else {
                            if (isUnsign) {
                                unum32 tmp = 0;
                                if (binstr_to<unum32 > (val, tmp)) {
                                    return calc_token(tmp);}}
                            else {
                                num32 tmp = 0;
                                if (binstr_to<num32 > (val, tmp)) {
                                    return calc_token(tmp);}}}
                        return calc_token(NULL_DOUBLE);}
                    case oct_const:{
                        if (isLong) {
                            if (isUnsign) {
                                unum64 tmp = 0;
                                if (octstr_to<unum64 > (val, tmp)) {
                                    return calc_token(tmp);}}
                            else {
                                num64 tmp = 0;
                                if (octstr_to<num64 > (val, tmp)) {
                                    return calc_token(tmp);}}}
                        else {
                            if (isUnsign) {
                                unum32 tmp = 0;
                                if (octstr_to<unum32 > (val, tmp)) {
                                    return calc_token(tmp);}}
                            else {
                                num32 tmp = 0;
                                if (octstr_to<num32 > (val, tmp)) {
                                    return calc_token(tmp);}}}
                        return calc_token(NULL_DOUBLE);}
                    case hex_const:{
                        if (isLong) {
                            if (isUnsign) {
                                unum64 tmp = 0;
                                if (hexstr_to<unum64 > (val, tmp)) {
                                    return calc_token(tmp);}}
                            else {
                                num64 tmp = 0;
                                if (hexstr_to<num64 > (val, tmp)) {
                                    return calc_token(tmp);}}}
                        else {
                            if (isUnsign) {
                                unum32 tmp = 0;
                                if (hexstr_to<unum32 > (val, tmp)) {
                                    return calc_token(tmp);}}
                            else {
                                num32 tmp = 0;
                                if (hexstr_to<num32 > (val, tmp)) {
                                    return calc_token(tmp);}}}
                        return calc_token(NULL_DOUBLE);}
                    case dec_const:{
                        if (isLong) {
                            if (isUnsign) {
                                unum64 tmp = 0;
                                if (str_to<unum64 > (val, tmp)) {
                                    return calc_token(tmp);}}
                            else {
                                num64 tmp = 0;
                                if (str_to<num64 > (val, tmp)) {
                                    return calc_token(tmp);}}}
                        else {
                            if (isUnsign) {
                                unum32 tmp = 0;
                                if (str_to<unum32 > (val, tmp)) {
                                    return calc_token(tmp);}}
                            else {
                                num32 tmp = 0;
                                if (str_to<num32 > (val, tmp)) {
                                    return calc_token(tmp);}}}
                        return calc_token(NULL_DOUBLE);}
                    default: calc_token(NULL_DOUBLE);}
                return calc_token(NULL_DOUBLE);}

            if (val.size() >= 2) {
                if (((*val.begin()) == '"') || ((*val.begin()) == '\'')) {
                    if (((*val.begin()) == '"') && ((*val.rbegin()) == '"')) {
                        return calc_token(val.substr(1, val.size() - 2));}
                    if (((*val.begin()) == '\'') && ((*val.rbegin()) == '\'')) {
                        return calc_token(val.substr(1, val.size() - 2));}
                    calc_token(NULL_DOUBLE);}}


            indx idtag = (intf) ? intf(val) : npos;
            if ((idtag != npos) && (refcntr)) refcntr->add(idtag);
            return calc_token(idtag,
                    ((intf) && (idtag != npos) && (!IN_REPORTSET(intf->type(idtag)))) ? intf->type(idtag) : 0,
                    (idtag == npos) ? ERROR_TAGNOEXIST : 0);};

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::getmineu(calc_token& it) {
            if (it.operation() != expr) throw dvncierror(ERROR_EXPROPERATOR);
            if (intf) {
                return intf->mineu_shv(it.id());}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::getmaxeu(const calc_token& it) {
            if (it.operation() != expr) throw dvncierror(ERROR_EXPROPERATOR);
            if (intf) {
                return intf->maxeu_shv(it.id());}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::gettime(const calc_token& it) {
            if (it.operation() != expr) throw dvncierror(ERROR_EXPROPERATOR);
            if (intf) {
                return intf->time(it.id());}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::getlogtime(const calc_token& it) {
            if (it.operation() != expr) throw dvncierror(ERROR_EXPROPERATOR);
            if (intf) {
                return intf->time_log(it.id());}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::getvalid(const calc_token& it) {
            if (it.operation() != expr) return it.valid();
            if (intf) {
                return intf->valid(it.id());}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::geterror(const calc_token& it) {
            if (it.operation() != expr) throw dvncierror(ERROR_EXPROPERATOR);
            if (intf) {
                return intf->error(it.id());}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::getalarm(const calc_token& it) {
            if (it.operation() != expr) throw dvncierror(ERROR_EXPROPERATOR);
            if (intf) {
                calc_token tmp(static_cast<bool> (intf->alarmon(it.id())));
                tmp.valid(intf->valid(it.id()));
                return tmp;}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::getack(const calc_token& it) {
            if (it.operation() != expr) throw dvncierror(ERROR_EXPROPERATOR);
            if (intf) {
                calc_token tmp(static_cast<bool> (intf->alarmkvit(it.id())));
                tmp.valid(intf->valid(it.id()));
                return tmp;}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::getalarmack(const calc_token& it) {
            if (it.operation() != expr) throw dvncierror(ERROR_EXPROPERATOR);
            if (intf) {
                calc_token tmp((static_cast<bool> (intf->alarmkvit(it.id()))) && (static_cast<bool> (intf->alarmon(it.id()))));
                tmp.valid(intf->valid(it.id()));
                return tmp;}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::getcomment(const calc_token& it) {
            if (it.operation() != expr) throw dvncierror(ERROR_EXPROPERATOR);
            if (intf) {
                return intf->comment(it.id());}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::geteu(const calc_token& it) {
            if (it.operation() != expr) throw dvncierror(ERROR_EXPROPERATOR);
            if (intf) {
                return intf->eu(it.id());}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::getbinding(const calc_token& it) {
            if (it.operation() != expr) throw dvncierror(ERROR_EXPROPERATOR);
            if (intf) {
                return intf->binding(it.id());}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::getalarmmsg(const calc_token& it) {
            if (it.operation() != expr) throw dvncierror(ERROR_EXPROPERATOR);
            if (intf) {
                return intf->alarmmsg(it.id());}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::calc_token_factory(const std::string& val) {
            return getoperation(trim_copy(val));}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::assignexpr(const calc_token& it) {
            if (intf) {
                return intf->value_shv(it.id());}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        calc_token expression_templ<BASEINTF, REFCOUNTER>::assignlastexpr(const calc_token& it) {
            if (intf) {
                return intf->value_log_shv(it.id());}
            throw dvncierror(ERROR_NILLINF);}

        template<typename BASEINTF, typename REFCOUNTER>
        ns_error expression_templ<BASEINTF, REFCOUNTER>::calculate() {
            if (error()) return error();
            clearstack();
            error(0);
            try {
                if (changepoll) {
                    changepoll = false;
                    polline = savedpolline;}
                polishline_iterator it = polline.begin();
                polishline_iterator endit = polline.end();
                while (it != endit) {
                    if (it->operation() == oprt_caseleftgroup) {
                        if (!calcstack.empty()) {
                            calc_token nmidit = prepareitem(calcstack.top());
                            calcstack.pop();
                            if (caseswitch(it, nmidit)) {
                                clearall();
                                changepoll = true;
                                return error();};}
                        else {
                            clearall();
                            return error(ERROR_EXPRPARSE);}
                        it = polline.begin();
                        endit = polline.end();
                        changepoll = true;}
                    else {
                        switch (it->operation()) {
                            case notoperation: break;
                            case expr:{
                                calcstack.push(*it);
                                break;}
                            case constant:{
                                calcstack.push(*it);
                                break;}
                            case const_e:{
                                calcstack.push(calc_token(DV_E_CONST));
                                break;}
                            case const_nan:{
                                calcstack.push(calc_token(NULL_DOUBLE));
                                break;}
                            case const_pi:{
                                calcstack.push(calc_token(DV_PI_CONST));
                                break;}
                            case const_now:{
                                calcstack.push(calc_token(now()));
                                break;}
                            case select_msc:
                            case select_sec:
                            case select_minute:
                            case select_hour:
                            case select_day:
                            case select_dayweek:
                            case select_dayyear:
                            case select_month:
                            case select_monthdays:
                            case select_year:
                            case select_epoch:
                            case select_epochminute:
                            case select_epochday:
                            case select_epochhour:
                            case select_epochmsc:{
                                if (!calcstack.empty()) {
                                    calc_token rsideit = prepareitem(calcstack.top());
                                    calcstack.pop();
                                    if (rsideit.type() == TYPE_TM) {
                                        datetime tmtmp = cast_datetime_fromnum64(rsideit.value());
                                        if (!tmtmp.is_special()) {
                                            switch (it->operation()) {
                                                case select_msc:{
                                                    calcstack.push(calc_token(static_cast<num64> (tmtmp.time_of_day().total_milliseconds())));
                                                    break;}
                                                case select_sec:{
                                                    calcstack.push(calc_token(static_cast<num64> (tmtmp.time_of_day().seconds())));
                                                    break;}
                                                case select_minute:{
                                                    calcstack.push(calc_token(static_cast<num64> (tmtmp.time_of_day().minutes())));
                                                    break;}
                                                case select_hour:{
                                                    calcstack.push(calc_token(static_cast<num64> (tmtmp.time_of_day().hours())));
                                                    break;}
                                                case select_day:{
                                                    calcstack.push(calc_token(static_cast<num64> (tmtmp.date().day())));
                                                    break;}
                                                case select_dayweek:{
                                                    calcstack.push(calc_token(static_cast<num64> (tmtmp.date().day_of_week())));
                                                    break;}
                                                case select_dayyear:{
                                                    calcstack.push(calc_token(static_cast<num64> (tmtmp.date().day_of_year())));
                                                    break;}
                                                case select_month:{
                                                    calcstack.push(calc_token(static_cast<num64> (tmtmp.date().month())));
                                                    break;}
                                                case select_monthdays:{
                                                    calcstack.push(calc_token(static_cast<num64> (tmtmp.date().end_of_month().day())));
                                                    break;}
                                                case select_year:{
                                                    calcstack.push(calc_token(static_cast<num64> (tmtmp.date().year())));
                                                    break;}
                                                case select_epochminute:{
                                                    calcstack.push(calc_token(static_cast<num64> (datetime_to_epoch_minute(tmtmp))));
                                                    break;}
                                                case select_epochhour:{
                                                    calcstack.push(calc_token(static_cast<num64> (datetime_to_epoch_hour(tmtmp))));
                                                    break;}
                                                case select_epochday:{
                                                    calcstack.push(calc_token(static_cast<num64> (datetime_to_epoch_day(tmtmp))));
                                                    break;}
                                                case select_epoch:{
                                                    calcstack.push(calc_token(static_cast<num64> (datetime_to_epoch(tmtmp))));
                                                    break;}
                                                case select_epochmsc:{
                                                    calcstack.push(calc_token(static_cast<num64> (datetime_to_epoch_msc(tmtmp))));
                                                    break;}}}
                                        else {
                                            calcstack.push(calc_token(tmtmp));}
                                        break;}
                                    else {
                                        clearall();
                                        return error(ERROR_EXPROPERATOR);}}
                                clearall();
                                return error(ERROR_EXPRPARSE);
                                break;}

                            case func_incmsc:
                            case func_incsec:
                            case func_incminute:
                            case func_inchour:
                            case func_incday:{
                                if (calcstack.size() > 1) {
                                    calc_token incit = prepareitem(calcstack.top()).gettypedval(oper_cast_num64);
                                    calcstack.pop();
                                    num64 incnum = incit.value();
                                    calc_token tmit = prepareitem(calcstack.top());
                                    calcstack.pop();
                                    if (tmit.type() == TYPE_TM) {
                                        try {
                                            switch (it->operation()) {
                                                case func_incmsc:{
                                                    tmit.value(castnum64_from_datetime(incmillisecond(tmit.tm(), incnum)));
                                                    break;}
                                                case func_incsec:{
                                                    tmit.value(castnum64_from_datetime(incsecond(tmit.tm(), incnum)));
                                                    break;}
                                                case func_incminute:{
                                                    tmit.value(castnum64_from_datetime(incminute(tmit.tm(), incnum)));
                                                    break;}
                                                case func_inchour:{
                                                    tmit.value(castnum64_from_datetime(inchour(tmit.tm(), incnum)));
                                                    break;}
                                                case func_incday:{
                                                    tmit.value(castnum64_from_datetime(incday(tmit.tm(), incnum)));
                                                    break;}}
                                            calcstack.push(calc_token(tmit));}
                                        catch (...) {}}
                                    else {
                                        clearall();
                                        return error(ERROR_EXPROPERATOR);}}
                                else {
                                    clearall();
                                    return error(ERROR_EXPROPERATOR);}

                                break;}


                            case func_rnd:{
                                calcstack.push(calc_token((1.0 * rand()) / RAND_MAX));
                                break;}
                            case oprt_commandset:
                            case oprt_commandset1:
                            case oprt_command:
                            case oprt_command1:{
                                if (calcstack.size() >= 2) {
                                    if ((calcstack.top().operation() == constant) && (calcstack.top().isnan())) {
                                        //calcstack.pop();
                                        calcstack.pop();
                                        break;}
                                    calc_token rsideit = prepareitem(calcstack.top());
                                    if (rsideit.valid() < FULL_VALID) {
                                        //calcstack.pop();
                                        calcstack.pop();
                                        break;}
                                    calcstack.pop();
                                    if ((intf) && (!calcstack.top().isnan()) && (calcstack.top().id() != npos)) {
                                        if (rsideit.valid() == FULL_VALID) {
                                            intf->send_command(calcstack.top().id(), short_value(rsideit.value(), rsideit.type(), FULL_VALID),
                                                    ((it->operation() == oprt_command) || (it->operation() == oprt_commandset))  ? acQueuedCommand : 
                                                        (((it->operation() == oprt_command1) || (it->operation() == oprt_commandset1))  ? acNewCommand : acImpulseCommand),
                                                    ((it->operation() == oprt_commandset) || (it->operation() == oprt_commandset1)));}
                                        //calcstack.pop();
                                        /*calcstack.push(rsideit);*/
                                    }
                                    else {
                                        //calcstack.pop();
                                        /*calcstack.push(rsideit);*/
                                    }}
                                else {
                                    clearall();
                                    return error(ERROR_EXPRPARSE);}
                                break;}
                            case oprt_kvit:{
                                if (!calcstack.empty()) {
                                    if (calcstack.top().id() != npos) {
                                        intf->kvit(calcstack.top().id());}
                                    else {
                                        intf->kvit(calcstack.top().id());
                                        return error(ERROR_EXPRPARSE);}}
                                else {
                                    intf->kvit();
                                    return error();}
                                break;}
                            default:{
                                switch (it->operation()) {
                                    case oprt_add:
                                    case oprt_sub:
                                    case oprt_mult:
                                    case oprt_div:
                                    case oprt_modulo:{
                                        if (!calcstack.empty()) {
                                            calc_token rsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            if ((calcstack.empty())) {
                                                clearall();
                                                return error(ERROR_EXPRPARSE);}
                                            calc_token lsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = (it->operation() == oprt_add) ? lsideit + rsideit :
                                                    (it->operation() == oprt_sub) ? lsideit - rsideit :
                                                    (it->operation() == oprt_mult) ? lsideit * rsideit :
                                                    (it->operation() == oprt_div) ? lsideit / rsideit : lsideit % rsideit;
                                            resultit.valid(lsideit.valid() < rsideit.valid() ? lsideit.valid() : rsideit.valid());
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case oprt_prefinc:
                                    case oprt_postinc:{
                                        if (!calcstack.empty()) {
                                            calc_token rsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            rsideit = rsideit + calc_token(1);
                                            calcstack.push(rsideit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case oprt_prefdec:
                                    case oprt_postdec:{
                                        if (!calcstack.empty()) {
                                            calc_token rsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            rsideit = rsideit - calc_token(1);
                                            calcstack.push(rsideit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case oprt_compless:
                                    case oprt_complessoreq:
                                    case oprt_compmore:
                                    case oprt_compmoreoreq:
                                    case oprt_compeq:
                                    case oprt_compnoteq:{
                                        if (!calcstack.empty()) {
                                            calc_token rsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            if ((calcstack.empty())) {
                                                clearall();
                                                return error(ERROR_EXPRPARSE);}
                                            calc_token lsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = (it->operation() == oprt_compless) ? (lsideit < rsideit) :
                                                    (it->operation() == oprt_complessoreq) ? (lsideit <= rsideit) :
                                                    (it->operation() == oprt_compmore) ? (lsideit > rsideit) :
                                                    (it->operation() == oprt_compmoreoreq) ? (lsideit >= rsideit) :
                                                    (it->operation() == oprt_compeq) ? (lsideit == rsideit) :
                                                    (lsideit != rsideit);
                                            resultit.valid(lsideit.valid() < rsideit.valid() ? lsideit.valid() : rsideit.valid());
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case oprt_opnot:
                                    case oprt_opexnot:
                                    case oprt_sub_unary:{
                                        if (!calcstack.empty()) {
                                            calc_token nmidit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = (it->operation() == oprt_opnot) ? (!nmidit) :
                                                    (it->operation() == oprt_opexnot) ? (~nmidit) :
                                                    (-nmidit);
                                            resultit.valid(nmidit.valid());
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}
                                    case oprt_allvalid_unary:{
                                        if (!calcstack.empty()) {
                                            calc_token resultit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            resultit.valid(FULL_VALID);
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}
                                    case oprt_bitand:
                                    case oprt_bitor:
                                    case oprt_bitexor:{
                                        if (!calcstack.empty()) {
                                            calc_token rsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            if ((calcstack.empty())) {
                                                clearall();
                                                return error(ERROR_EXPRPARSE);}
                                            calc_token lsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = (it->operation() == oprt_bitand) ? (lsideit & rsideit) :
                                                    (it->operation() == oprt_bitor) ? (lsideit | rsideit) :
                                                    (lsideit ^ rsideit);
                                            resultit.valid(lsideit.valid() < rsideit.valid() ? lsideit.valid() : rsideit.valid());
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}


                                    case oprt_logicand:
                                    case oprt_logicor:{
                                        if (!calcstack.empty()) {
                                            calc_token rsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            if ((calcstack.empty())) {
                                                clearall();
                                                return error(ERROR_EXPRPARSE);}
                                            calc_token lsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = (it->operation() == oprt_logicand) ? (lsideit && rsideit) :
                                                    (lsideit || rsideit);
                                            resultit.valid(lsideit.valid() < rsideit.valid() ? lsideit.valid() : rsideit.valid());
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case oprt_bitleft:
                                    case oprt_bitright:{
                                        if (!calcstack.empty()) {
                                            calc_token rsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            if ((calcstack.empty())) {
                                                clearall();
                                                return error(ERROR_EXPRPARSE);}
                                            calc_token lsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = (it->operation() == oprt_bitleft) ? (lsideit << rsideit) :
                                                    (lsideit >> rsideit);
                                            resultit.valid(lsideit.valid() < rsideit.valid() ? lsideit.valid() : rsideit.valid());
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case oprt_cyclbitleft:
                                    case oprt_cyclbitright:{
                                        if (!calcstack.empty()) {
                                            calc_token rsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            if ((calcstack.empty())) {
                                                clearall();
                                                return error(ERROR_EXPRPARSE);}
                                            calc_token lsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = (it->operation() == oprt_cyclbitleft) ? (cycl_operator_btlft(lsideit, rsideit)) :
                                                    (cycl_operator_btrgt(lsideit, rsideit));
                                            resultit.valid(lsideit.valid() < rsideit.valid() ? lsideit.valid() : rsideit.valid());
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}



                                    case select_mineu:
                                    case select_maxeu:
                                    case select_ack:
                                    case select_alarm:
                                    case select_alarmack:{
                                        if (!calcstack.empty() && (calcstack.top().id() != npos)) {
                                            calc_token nmidit = calcstack.top();
                                            calcstack.pop();
                                            calc_token resultit = (it->operation() == select_mineu) ? getmineu(nmidit) :
                                                    (it->operation() == select_maxeu) ? getmaxeu(nmidit) :
                                                    (it->operation() == select_ack) ? getack(nmidit) :
                                                    (it->operation() == select_alarm) ? getalarm(nmidit) :
                                                    getalarmack(nmidit);
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case select_time:
                                    case select_logtime:{
                                        if ((!calcstack.empty()) && (calcstack.top().id() != npos)) {
                                            calc_token nmidit = calcstack.top();
                                            calc_token resultit = (it->operation() == select_time) ? gettime(nmidit) : getlogtime(nmidit);
                                            calcstack.pop();
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case select_lastvalue:{
                                        if ((!calcstack.empty()) && (calcstack.top().id() != npos)) {
                                            calc_token resultit = preparelastitem(calcstack.top());
                                            calcstack.pop();
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case select_error:{
                                        if ((!calcstack.empty()) && (calcstack.top().id() != npos)) {
                                            calc_token nmidit = calcstack.top();
                                            calc_token resultit = geterror(nmidit);
                                            calcstack.pop();
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case select_valid:{
                                        if ((!calcstack.empty())) {
                                            calc_token nmidit = calcstack.top();
                                            calc_token resultit = getvalid(nmidit);
                                            calcstack.pop();
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case func_num:
                                    case select_num:{
                                        if (!calcstack.empty()) {
                                            calc_token nmidit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = nmidit.getnum();
                                            resultit.valid(nmidit.valid());
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case func_real:
                                    case select_real:{
                                        if (!calcstack.empty()) {
                                            calc_token nmidit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = nmidit.getreal();
                                            resultit.valid(nmidit.valid());
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case func_bool:
                                    case select_bool:{
                                        if (!calcstack.empty()) {
                                            calc_token nmidit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = nmidit.getbool();
                                            resultit.valid(nmidit.valid());
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case oper_cast_basetype:
                                    case oper_cast_num64:
                                    case oper_cast_unum64:
                                    case oper_cast_num32:
                                    case oper_cast_unum32:
                                    case oper_cast_num16:
                                    case oper_cast_unum16:
                                    case oper_cast_num8:
                                    case oper_cast_unum8:
                                    case oper_cast_float:
                                    case oper_cast_double:
                                    case oper_cast_bool:{
                                        if (!calcstack.empty()) {
                                            calc_token nmidit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = nmidit.gettypedval(it->operation());
                                            resultit.valid(nmidit.valid());
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case oper_cast_vbool:{
                                        if (!calcstack.empty()) {
                                            calc_token nmidit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = nmidit.gettypedval(it->operation());
                                            resultit = resultit.value<bool>() && nmidit.valid();
                                            resultit.valid(FULL_VALID);
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case func_format:{
                                        if (!calcstack.empty()) {
                                            calc_token lsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            if ((calcstack.empty())) {
                                                clearall();
                                                return error(ERROR_EXPRPARSE);}
                                            calc_token rsideit = prepareitem(calcstack.top());
                                            vlvtype vld = rsideit.valid();
                                            datetime tm = rsideit.time();
                                            std::string frmttmp = lsideit.value<std::string > ();
                                            lsideit = rsideit.to_valuetype().format(frmttmp);
                                            lsideit.valid(vld);
                                            lsideit.time(tm);
                                            calcstack.pop();
                                            calcstack.push(lsideit);}
                                        break;}

                                    case select_comment:
                                    case select_eu:
                                    case select_binding:
                                    case select_alarmmsg:{
                                        if (!calcstack.empty() && (calcstack.top().id() != npos)) {
                                            calc_token nmidit = calcstack.top();
                                            calcstack.pop();
                                            calc_token resultit = (it->operation() == select_comment) ? getcomment(nmidit) :
                                                    (it->operation() == select_eu) ? geteu(nmidit) :
                                                    (it->operation() == select_binding) ? getbinding(nmidit) :
                                                    getalarmmsg(nmidit);
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}

                                    case oper_cast_time:
                                    case oper_cast_text:{
                                        clearall();
                                        return error(ERROR_EXPRPARSE);}

                                    case func_abs:{
                                        if (!calcstack.empty()) {
                                            calc_token nmidit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = nmidit.getabs();
                                            resultit.valid(nmidit.valid());
                                            calcstack.push(resultit);
                                            break;}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);
                                            break;}}

                                    case func_sin:
                                    case func_cos:
                                    case func_sqrt:
                                    case func_sqr:
                                    case func_exp:
                                    case func_log10:
                                    case func_tan:
                                    case func_acos:
                                    case func_asin:
                                    case func_atan:
                                    case func_cosh:
                                    case func_sinh:
                                    case func_tanh:
                                    case func_ln:
                                    case func_floor:
                                    case func_ceiling:
                                    case func_round:{
                                        if (!calcstack.empty()) {
                                            calc_token nmidit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = nmidit.math_func1(it->operation());
                                            resultit.valid(nmidit.valid());
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}
                                    case func_pow:{
                                        if (!calcstack.empty()) {
                                            calc_token rsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            if ((calcstack.empty())) {
                                                clearall();
                                                return error(ERROR_EXPRPARSE);}
                                            calc_token lsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = math_pow(lsideit, rsideit);
                                            resultit.valid(lsideit.valid() < rsideit.valid() ? lsideit.valid() : rsideit.valid());
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}
                                    case func_min:
                                    case func_max:{
                                        if (!calcstack.empty()) {
                                            calc_token rsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            if ((calcstack.empty())) {
                                                clearall();
                                                return error(ERROR_EXPRPARSE);}
                                            calc_token lsideit = prepareitem(calcstack.top());
                                            calcstack.pop();
                                            calc_token resultit = (it->operation() == func_min) ? minim(lsideit, rsideit) : maxim(lsideit, rsideit);
                                            resultit.valid(lsideit.valid() < rsideit.valid() ? lsideit.valid() : rsideit.valid());
                                            calcstack.push(resultit);}
                                        else {
                                            clearall();
                                            return error(ERROR_EXPRPARSE);}
                                        break;}
                                    default:{}}}}
                        ++it;}}}
            catch (dvncierror& er) {
                calc_token tmp;
                rslt = tmp;
                return error(er.code());}
            if (calcstack.size() < 1) {
                clearall();
                return error(ERROR_EXPRPARSE);}
            if (calcstack.top().needassign()) {
                try {
                    rslt = prepareitem(calcstack.top());}
                catch (dvncierror& er) {
                    calc_token tmp;
                    rslt = tmp;
                    return error(er.code());}}
            else rslt = calcstack.top();
            return error();}

        template<typename BASEINTF, typename REFCOUNTER>
        ns_error expression_templ<BASEINTF, REFCOUNTER>::caseswitch(polishline_iterator& iter, const calc_token& tkn) {
            bool fnd = false;
            //if ((tkn.valid() != FULL_VALID) || (tkn.isnan())) {
            //polline.clear();
            //polline.push_back(calc_token(NULL_DOUBLE));
            //return true;}
            bool cs = tkn.getbool().value() && tkn.valid();
            polishline_iterator it = iter;
            size_t cntr = 0;
            polishline_iterator strtit = cs ? it : polline.end();
            polishline_iterator stpit = polline.end();
            polishline_iterator externalit = polline.end();
            while ((!fnd) && (it != polline.end())) {
                it++;
                switch (it->operation()) {
                    case oprt_caseleftgroup:{
                        cntr++;
                        break;}
                    case oprt_casedelim:{
                        if (cntr == 0) {
                            if (cs) {
                                stpit = it;}
                            else {
                                strtit = it;}}
                        break;}
                    case oprt_caserightgroup:{
                        if (cntr > 0) {
                            cntr--;}
                        else {
                            if (!cs) {
                                stpit = it;
                                externalit = it + 1;
                                fnd = true;}
                            else {
                                externalit = it + 1;
                                fnd = true;}}
                        break;}
                    default:{
                        break;}}}
            if ((!fnd) || (strtit == polline.end()) || (stpit == polline.end()))
                return error(ERROR_EXPRPARSE);
            strtit++;
            polishline newln;
            newln.insert(newln.begin(), strtit, stpit);
            if (externalit != polline.end()) newln.insert(newln.end(), externalit, polline.end());
            polline.swap(newln);
            iter = polline.begin();
            //print_line(polline);
            return error();}

        template<typename BASEINTF, typename REFCOUNTER>
        ns_error expression_templ<BASEINTF, REFCOUNTER>::parse(std::string val) {
            if (val.empty())
                return error(ERROR_EXPRNOINIT);
            error(0);
            stringvector.clear();

            std::wstring wval = utf8_to_wstr(val);
            wstr_vect wstringvector;
            size_t tokencount = regex_tokin_parser(wval, wstringvector, WFULLEXPR_REGEX);
            for (wstr_vect::const_iterator itw = wstringvector.begin(); itw != wstringvector.end(); ++itw)
                stringvector.push_back(wstr_to_utf8(*itw));

            wstringvector.clear();

            if (tokencount) {
                clearstack();
                polline.clear();
                parsetoken();}
            //print_line(polline);
            savedpolline = polline;
            return error();}

        template<typename BASEINTF, typename REFCOUNTER>
        ns_error expression_templ<BASEINTF, REFCOUNTER>::parse(std::wstring val) {
            if (val.empty())
                return error(ERROR_EXPRNOINIT);
            error(0);
            stringvector.clear();


            wstr_vect wstringvector;
            size_t tokencount = regex_tokin_parser(val, wstringvector, WFULLEXPR_REGEX);
            for (wstr_vect::const_iterator itw = wstringvector.begin(); itw != wstringvector.end(); ++itw)
                stringvector.push_back(wstr_to_utf8(*itw));

            wstringvector.clear();

            if (tokencount) {
                clearstack();
                polline.clear();
                parsetoken();}
            //print_line(polline);
            savedpolline = polline;
            return error();}

        template<typename BASEINTF, typename REFCOUNTER>
        ns_error expression_templ<BASEINTF, REFCOUNTER>::parsetoken() {

            calc_operation last_oper = notoperation;
            size_t casecounter = 0;
            size_t counter = 0;
            for (exprstack::iterator it = stringvector.begin(); it != stringvector.end(); ++it) {
                //DEBUG_VAL_DVNCI(*it)
                calc_token tmpit = calc_token_factory(*it);
                if (tmpit.iserror()) {
                    if (tmpit.error() == ERROR_TAGNOEXIST) { // возможно появится
                        if (refcntr)
                            refcntr->clear();
                        error(ERROR_TAGNOEXIST);}
                    else {
                        if (refcntr)
                            refcntr->clear();
                        clearall();
                        return error(tmpit.error());}}
                switch (tmpit.operation()) {
                    case notoperation:{
                        clearall();
                        return error(ERROR_EXPRPARSE);}
                    case expr:{
                        polline.push_back(tmpit);
                        break;}
                    case constant:{
                        polline.push_back(tmpit);
                        break;}
                    case oprt_leftgroup:{
                        calcstack.push(tmpit);
                        break;}
                    case oprt_comma:
                    case oprt_rightgroup:
                    case oprt_casedelim:{
                        if (!calcstack.empty()) {
                            while ((!calcstack.empty()) && (calcstack.top().operation() != oprt_leftgroup) && (calcstack.top().operation() != oprt_caseleftgroup)) {
                                if (calcstack.top().operation() == oprt_condit) {
                                    calc_token tmpitcond = calc_token_factory("]");
                                    polline.push_back(tmpitcond);}
                                else
                                    polline.push_back(calcstack.top());
                                calcstack.pop();}
                            if ((!calcstack.empty()) && ((calcstack.top().operation() == oprt_leftgroup) || (calcstack.top().operation() == oprt_caseleftgroup))) {
                                if (tmpit.operation() != oprt_comma) calcstack.pop();}
                            else {
                                if (tmpit.operation() != oprt_comma) {
                                    clearall();
                                    return error(ERROR_EXPRPARSE);}}}
                        else {
                            if (tmpit.operation() != oprt_comma) {
                                clearall();
                                return error(ERROR_EXPRPARSE);}}
                        if (tmpit.operation() == oprt_casedelim) polline.push_back(tmpit);
                        break;}
                    default:{
                        if (!calcstack.empty()) {
                            if ((calc_token::can_unary(tmpit.operation())) && (calc_token::find_unaryoperator(last_oper)))
                                tmpit.set_unary();
                            if (calc_token::can_post_pref(tmpit.operation()))
                                if (!((polline.empty()) || ((counter) && ((last_oper != oprt_rightgroup) && (last_oper >= 1000)))))
                                    tmpit.set_postfix();
                            if (calc_token::is_need_popstack(calcstack.top().operation(), tmpit.operation()))
                                while ((!calcstack.empty()) &&
                                        (calc_token::is_need_popstack(calcstack.top().operation(), tmpit.operation()))
                                        && (calcstack.top().operation() != oprt_leftgroup)) {
                                    if (calcstack.top().operation() == oprt_condit) {
                                        calc_token tmpitcond = calc_token_factory("]");
                                        polline.push_back(tmpitcond);}
                                    else
                                        polline.push_back(calcstack.top());
                                    calcstack.pop();}}
                        else {
                            if (polline.empty()) {
                                tmpit.set_unary();}
                            if (calc_token::can_post_pref(tmpit.operation()))
                                if (!((polline.empty()) || ((counter) && ((last_oper != oprt_rightgroup) && (last_oper >= 1000)))))
                                    tmpit.set_postfix();}
                        calcstack.push(tmpit);
                        if (tmpit.operation() == oprt_condit) {
                            calc_token tmpitcond = calc_token_factory("[");
                            polline.push_back(tmpitcond);
                            casecounter++;
                            tmpitcond = calc_token_factory("[");
                            calcstack.push(tmpitcond);}}}
                counter++;
                last_oper = tmpit.operation();}

            if ((calcstack.empty()) && (polline.empty())) {
                return error(ERROR_EXPRNOINIT);}

            while (!calcstack.empty()) {
                if (calc_token::is_group(calcstack.top().operation())) {
                    clearall();
                    return error(ERROR_EXPRPARSE);}
                if (calcstack.top().operation() == oprt_condit) {
                    calc_token tmpitcond = calc_token_factory("]");
                    polline.push_back(tmpitcond);}
                else
                    polline.push_back(calcstack.top());
                calcstack.pop();}
            return error();}

        template<typename BASEINTF, typename REFCOUNTER>
        void expression_templ<BASEINTF, REFCOUNTER>::print_line(const polishline& ln) {
            for (polishline_constiterator it = ln.begin(); it != ln.end(); ++it) {
                if (it->operation() == 1) {
                    if (intf) {
                        std::cout << ((intf->name(it->id()) == "") ? "noexisttag" : intf->name(it->id())) << "   ";}
                    else {
                        std::cout << "const" << "   ";}}
                else
                    std::cout << it->operation() << "   ";}
            std::cout << std::endl;}





        typedef dvnci::expr::expression_templ<exprintf_stub> expression_calculator;}}

#endif	/* _EXPRESSION_H */

