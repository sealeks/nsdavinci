/* 
 * File:   expression.cpp
 * Author: Serg
 * 
 * Created on 12 Май 2010 г., 12:50
 */

#include <kernel/expression.h>



namespace dvnci {
    namespace expr {


        typedef std::pair<std::string, calc_token> name_token_pair;
        typedef std::map<std::string, calc_token, std::less<std::string>, std::allocator<name_token_pair > > name_token_map;

        typedef std::pair<calc_operation, std::string> operator_name_pair;
        typedef std::map<calc_operation, std::string, std::less<calc_operation>, std::allocator<operator_name_pair > > operator_name_map;

        struct name_token_initillizer {

            static name_token_map create() {
                name_token_map map;
                map["("] = oprt_leftgroup;
                map[")"] = oprt_rightgroup;
                map["!"] = oprt_opnot;
                map["*"] = oprt_mult;
                map["/"] = oprt_div;
                map["%"] = oprt_modulo;
                map["+"] = oprt_add;
                map["-"] = oprt_sub;
                map["<"] = oprt_compless;
                map[">"] = oprt_compmore;
                map["="] = oprt_assign;
                map["&"] = oprt_bitand;
                map["^"] = oprt_bitexor;
                map["|"] = oprt_bitor;
                map["~"] = oprt_opexnot;
                map[","] = oprt_comma;
                map[":"] = oprt_casedelim;
                map["["] = oprt_caseleftgroup;
                map["]"] = oprt_caserightgroup;
                map["@"] = oprt_command;
                map["#"] = oprt_kvit;
                map["?"] = oprt_condit;
                map["<<"] = oprt_bitleft;
                map[">>"] = oprt_bitright;
                map["=="] = oprt_compeq;
                map["!="] = oprt_compnoteq;
                map["<="] = oprt_complessoreq;
                map[">="] = oprt_compmoreoreq;
                map["||"] = oprt_logicor;
                map["&&"] = oprt_logicand;
                map["++"] = oprt_prefinc;
                map["--"] = oprt_prefdec;
                map["''"] = calc_token(std::string());
                map["@@"] = oprt_command1;
                map["@="] = oprt_commandset;
                map["\"\""] = calc_token(std::string());
                map["<<<"] = oprt_cyclbitleft;
                map[">>>"] = oprt_cyclbitright;
                map["@@="] = oprt_commandset1;
                map["mod"] = select_mod;
                map[".mineu"] = select_mineu;
                map[".maxeu"] = select_maxeu;
                map[".ack"] = select_ack;
                map[".alarm"] = select_alarm;
                map[".nack"] = select_nack;
                map["ack"] = func_ack;
                map["alarm"] = func_alarm;
                map["nack"] = func_nack;
                map["tags"] = func_tags;
                map["alarmlevel"] = func_alarmlevel;
                map[".num"] = select_num;
                map["num"] = func_num;
                map[".real"] = select_real;
                map["real"] = func_real;
                map[".bool"] = select_bool;
                map["bool"] = func_bool;
                map["abs"] = func_abs;
                map["min"] = func_min;
                map["max"] = func_max;
                map["sin"] = func_sin;
                map["cos"] = func_cos;
                map["pow"] = func_pow;
                map["sqrt"] = func_sqrt;
                map["sqr"] = func_sqr;
                map["exp"] = func_exp;
                map["log"] = func_ln;
                map["ln"] = func_ln;
                map["log10"] = func_log10;
                map["tan"] = func_tan;
                map["acos"] = func_acos;
                map["asin"] = func_asin;
                map["atan"] = func_atan;
                map["format"] = func_format;
                map[".comment"] = select_comment;
                map[".binding"] = select_binding;
                map[".eu"] = select_eu;
                map[".alarmmsg"] = select_alarmmsg;
                map[".alarmlevel"] = select_alarmlevel;
                map["cosh"] = func_cosh;
                map["sinh"] = func_sinh;
                map["tanh"] = func_tanh;
                map["rnd"] = func_rnd;
                map["floor"] = func_floor;
                map["seil"] = func_ceiling;
                map["round"] = func_round;
                map["e"] = const_e;
                map["nan"] = NULL_DOUBLE;
                map["user"] = const_user;
                map["access"] = const_access;
                map["null"] = const_null;
                map["pi"] = const_pi;
                map["incmsc"] = func_incmsc;
                map["incsec"] = func_incsec;
                map["incminute"] = func_incminute;
                map["inchour"] = func_inchour;
                map["incday"] = func_incday;
                map["(notype)"] = oper_cast_basetype;
                map["(num64)"] = oper_cast_num64;
                map["(unum64)"] = oper_cast_unum64;
                map["(num32)"] = oper_cast_num32;
                map["(unum32)"] = oper_cast_unum32;
                map["(num16)"] = oper_cast_num16;
                map["(unum16)"] = oper_cast_unum16;
                map["(num8)"] = oper_cast_num8;
                map["(unum8)"] = oper_cast_unum8;
                map["(float)"] = oper_cast_float;
                map["(double)"] = oper_cast_double;
                map["(bool)"] = oper_cast_bool;
                map["(vbool)"] = oper_cast_vbool;
                map["(time)"] = oper_cast_time;
                map["(text)"] = oper_cast_text;
                map["now"] = const_now;
                map[".time"] = select_time;
                map[".logtime"] = select_logtime;
                map[".error"] = select_error;
                map[".valid"] = select_valid;
                map[".epoch"] = select_epoch;
                map[".msc"] = select_msc;
                map[".sec"] = select_sec;
                map[".minute"] = select_minute;
                map[".hour"] = select_hour;
                map[".day"] = select_day;
                map[".month"] = select_month;
                map[".monthdays"] = select_monthdays;
                map[".year"] = select_year;
                map[".dayweek"] = select_dayweek;
                map[".dayyear"] = select_dayyear;
                map[".epochmsc"] = select_epochmsc;
                map[".epochday"] = select_epochday;
                map[".epochhour"] = select_epochhour;
                map[".epochminute"] = select_epochminute;
                map[".lastvalue"] = select_lastvalue;
                return map;
            }

            static operator_name_map create_names() {
                name_token_map tmp = create();
                operator_name_map map;
                for (name_token_map::const_iterator it = tmp.begin(); it != tmp.end(); ++it) {
                    if ((it->second.operation() != notoperation) && (it->second.operation() != expr)
                            && (it->second.operation() != constant))
                        map[it->second.operation()] = it->first;
                }
                map[constant] = "{constant}";
                map[expr] = "{expr}";
                map[notoperation] = "{not operate}";
                return map;
            }
        };


        const name_token_map TOKEN_OPERATOR_MAP = name_token_initillizer::create();
        const operator_name_map OPERATOR_NAME_MAP = name_token_initillizer::create_names();

        calc_token test_operator_token(const std::string& val) {
            name_token_map::const_iterator it = TOKEN_OPERATOR_MAP.find(val);
            return (it != TOKEN_OPERATOR_MAP.end()) ? it->second : calc_token();
        }

        std::string string_from_operator(calc_operation val) {
            operator_name_map::const_iterator it = OPERATOR_NAME_MAP.find(val);
            return (it != OPERATOR_NAME_MAP.end()) ? it->second : "nodef";
        }

        const_type parseconstype(std::string& val, bool& flt, bool isint) {
            flt = false;
            std::string::size_type posFloat = val.find_last_of("f");
            if (val.find_first_of(".") != std::string::npos) {
                flt = (posFloat != std::string::npos);
                if (posFloat != std::string::npos) {
                    val = val.substr(0, posFloat);
                }
                return real_const;
            }
            if (val.find("0b") == 0) {
                val = val.substr(2);
                return bin_const;
            }
            if (val.find("0x") == 0) {
                val = val.substr(2);
                return hex_const;
            }
            flt = (posFloat != std::string::npos);
            if (posFloat != std::string::npos) {
                val = val.substr(0, posFloat);
            }
            if (flt) return real_const;
            if (((val.find_first_of("0") == 0) && (val.size() > 1))) {
                val = val.substr(1);
                return oct_const;
            }
            if (flt) return real_const;
            return isint ? dec_const : real_const;
        }

        calc_token test_const_token(std::string val) {
            boost::regex ex(NUMBER_REGEXTAMPL_EXT);
            boost::smatch xResults;
            if (boost::regex_match(val, xResults, ex)) {
                DEBUG_STR_VAL_DVNCI(ISNUMERIC_CONST, val)
                std::string::size_type posLong = val.find_last_of("l");
                std::string::size_type posUnsign = val.find_last_of("u");
                std::string::size_type posLongUnsign = val.find_first_of("lu");
                std::string::size_type posUnsignLong = val.find_first_of("ul");
                bool isFloat = false;
                bool isLong = ((posLong != std::string::npos) || (posUnsignLong != std::string::npos) || (posLongUnsign != std::string::npos));
                bool isUnsign = ((posUnsign != std::string::npos) || (posUnsignLong != std::string::npos) || (posLongUnsign != std::string::npos));
                if (posLongUnsign != std::string::npos) {
                    val = val.substr(0, posLongUnsign);
                } else if (posUnsignLong != std::string::npos) {
                    val = val.substr(0, posUnsignLong);
                } else if (posLong != std::string::npos) {
                    val = val.substr(0, posLong);
                } else if (posUnsign != std::string::npos) {
                    val = val.substr(0, posUnsign);
                }

                //DEBUG_VAL_DVNCI(isLong)
                //DEBUG_VAL_DVNCI(isUnsign)
                //DEBUG_VAL_DVNCI(val)
                switch (parseconstype(val, isFloat, isLong || isUnsign)) {
                    case real_const:
                    {
                        if (isFloat) {
                            float tmpfl = 0;
                            if (str_to(val, tmpfl)) {
                                return calc_token(tmpfl);
                            } else {
                                return calc_token(NULL_DOUBLE);
                            }
                        }
                        double tmpdbl = NULL_DOUBLE;
                        str_to(val, tmpdbl);
                        return calc_token(tmpdbl);
                    }
                    case bin_const:
                    {
                        if (isLong) {
                            if (isUnsign) {
                                unum64 tmp = 0;
                                if (binstr_to<unum64 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            } else {
                                num64 tmp = 0;
                                if (binstr_to<num64 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            }
                        } else {
                            if (isUnsign) {
                                unum32 tmp = 0;
                                if (binstr_to<unum32 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            } else {
                                num32 tmp = 0;
                                if (binstr_to<num32 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            }
                        }
                        return calc_token(NULL_DOUBLE);
                    }
                    case oct_const:
                    {
                        if (isLong) {
                            if (isUnsign) {
                                unum64 tmp = 0;
                                if (octstr_to<unum64 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            } else {
                                num64 tmp = 0;
                                if (octstr_to<num64 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            }
                        } else {
                            if (isUnsign) {
                                unum32 tmp = 0;
                                if (octstr_to<unum32 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            } else {
                                num32 tmp = 0;
                                if (octstr_to<num32 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            }
                        }
                        return calc_token(NULL_DOUBLE);
                    }
                    case hex_const:
                    {
                        if (isLong) {
                            if (isUnsign) {
                                unum64 tmp = 0;
                                if (hexstr_to<unum64 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            } else {
                                num64 tmp = 0;
                                if (hexstr_to<num64 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            }
                        } else {
                            if (isUnsign) {
                                unum32 tmp = 0;
                                if (hexstr_to<unum32 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            } else {
                                num32 tmp = 0;
                                if (hexstr_to<num32 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            }
                        }
                        return calc_token(NULL_DOUBLE);
                    }
                    case dec_const:
                    {
                        if (isLong) {
                            if (isUnsign) {
                                unum64 tmp = 0;
                                if (str_to<unum64 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            } else {
                                num64 tmp = 0;
                                if (str_to<num64 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            }
                        } else {
                            if (isUnsign) {
                                unum32 tmp = 0;
                                if (str_to<unum32 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            } else {
                                num32 tmp = 0;
                                if (str_to<num32 > (val, tmp)) {
                                    return calc_token(tmp);
                                }
                            }
                        }
                        return calc_token(NULL_DOUBLE);
                    }
                    default: calc_token(NULL_DOUBLE);
                }
                return calc_token(NULL_DOUBLE);
            }
            return calc_token();
        }

        calc_token test_stringtype_token(const std::string& val) {
            if (val.size() >= 2) {
                if (((*val.begin()) == '"') || ((*val.begin()) == '\'')) {
                    if (((*val.begin()) == '"') && ((*val.rbegin()) == '"')) {
                        return calc_token(val.substr(1, val.size() - 2));
                    }
                    if (((*val.begin()) == '\'') && ((*val.rbegin()) == '\'')) {
                        return calc_token(val.substr(1, val.size() - 2));
                    }
                    calc_token(NULL_DOUBLE);
                }
            }
            return calc_token();
        }

        std::ostream & operator<<(std::ostream& os, calc_operation oper) {
            return os << string_from_operator(oper);
        }

        tagtype type_cast(const calc_token& v1, const calc_token& v2) {
            tagtype mintp = v1.type() < v2.type() ? v1.type() : v2.type();
            tagtype maxtp = v1.type() > v2.type() ? v1.type() : v2.type();
            return (mintp == maxtp) ? mintp :
                    ((mintp < EVENT_TYPE_OSC) ? ((maxtp <= TYPE_DISCRET) ? mintp : TYPE_NODEF) :
                    (maxtp < REPORTTYPE_YEAR) ? mintp : TYPE_NODEF);
        }

        calc_token operator+(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_NODEF: return (lside.value<double>() + rside.value<double>());
                case TYPE_DISCRET: return (lside.value<bool>() || rside.value<bool>());
                case TYPE_NUM64: return (lside.value<num64 > () + rside.value<num64 > ());
                case TYPE_UNUM64: return (lside.value<unum64 > () + rside.value<unum64 > ());
                case TYPE_NUM32: return (lside.value<num32 > () + rside.value<num32 > ());
                case TYPE_UNUM32: return (lside.value<unum32 > () + rside.value<unum32 > ());
                case TYPE_NUM16: return (lside.value<num16 > () + rside.value<num16 > ());
                case TYPE_UNUM16: return (lside.value<unum16 > () + rside.value<unum16 > ());
                case TYPE_NUM8: return (lside.value<num8 > () + rside.value<num8 > ());
                case TYPE_UNUM8: return (lside.value<unum8 > () + rside.value<unum8 > ());
                case TYPE_DOUBLE: return (lside.value<double>() + rside.value<double>());
                case TYPE_FLOAT: return (lside.value<float>() + rside.value<float>());
                case TYPE_TEXT: return (lside.value<std::string > () + rside.value<std::string > ());
                case TYPE_TM: return NULL_DOUBLE;
            }
            return (lside.value<double>() + rside.value<double>());
        }

        calc_token operator-(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_NODEF: return (lside.value<double>() - rside.value<double>());
                case TYPE_DISCRET: return NULL_DOUBLE;
                case TYPE_NUM64: return (lside.value<num64 > ())-(rside.value<num64 > ());
                case TYPE_UNUM64: return (lside.value<unum64 > () - rside.value<unum64 > ());
                case TYPE_NUM32: return (lside.value<num32 > () - rside.value<num32 > ());
                case TYPE_UNUM32: return (lside.value<unum32 > () - rside.value<unum32 > ());
                case TYPE_NUM16: return (lside.value<num16 > () - rside.value<num16 > ());
                case TYPE_UNUM16: return (lside.value<unum16 > () - rside.value<unum16 > ());
                case TYPE_NUM8: return (lside.value<num8 > () - rside.value<num8 > ());
                case TYPE_UNUM8: return (lside.value<unum8 > () - rside.value<unum8 > ());
                case TYPE_DOUBLE: return (lside.value<double>() - rside.value<double>());
                case TYPE_FLOAT: return (lside.value<float>() - rside.value<float>());
                case TYPE_TM: return NULL_DOUBLE;
            }
            return (lside.value<double>() - rside.value<double>());
        }

        calc_token operator-(calc_token& nval) {
            switch (nval.type()) {
                case TYPE_NODEF: return -nval.value<double>();
                case TYPE_DISCRET: return NULL_DOUBLE;
                case TYPE_NUM64: return (-nval.value<num64 > ());
                case TYPE_UNUM64: return (nval.value<unum64 > ());
                case TYPE_NUM32: return (-nval.value<num32 > ());
                case TYPE_UNUM32: return (nval.value<unum32 > ());
                case TYPE_NUM16: return (-nval.value<num16 > ());
                case TYPE_UNUM16: return (nval.value<unum16 > ());
                case TYPE_NUM8: return (-nval.value<num8 > ());
                case TYPE_UNUM8: return (nval.value<unum8 > ());
                case TYPE_DOUBLE: return (-nval.value<double>());
                case TYPE_FLOAT: return (-nval.value<float>());
                case TYPE_TM: return NULL_DOUBLE;
            }
            return (-nval.value<double>());
        }

        calc_token operator*(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_NODEF: return (lside.value<double>() * rside.value<double>());
                case TYPE_DISCRET: return (lside.value<bool>() && rside.value<bool>());
                case TYPE_NUM64: return (lside.value<num64 > () * rside.value<num64 > ());
                case TYPE_UNUM64: return (lside.value<unum64 > () * rside.value<unum64 > ());
                case TYPE_NUM32: return (lside.value<num32 > () * rside.value<num32 > ());
                case TYPE_UNUM32: return (lside.value<unum32 > () * rside.value<unum32 > ());
                case TYPE_NUM16: return (lside.value<num16 > () * rside.value<num16 > ());
                case TYPE_UNUM16: return (lside.value<unum16 > () * rside.value<unum16 > ());
                case TYPE_NUM8: return (lside.value<num8 > () * rside.value<num8 > ());
                case TYPE_UNUM8: return (lside.value<unum8 > () * rside.value<unum8 > ());
                case TYPE_DOUBLE: return (lside.value<double>() * rside.value<double>());
                case TYPE_FLOAT: return (lside.value<float>() * rside.value<float>());
                case TYPE_TM: return NULL_DOUBLE;
            }
            return (lside.value<double>() * rside.value<double>());
        }

        calc_token operator/(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_NODEF: return (lside.value<double>() / rside.value<double>());
                case TYPE_DISCRET:
                {
                    return NULL_DOUBLE;
                }
                case TYPE_NUM64:
                {
                    if (rside.value<num64 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return ( lside.value<num64 > () / rside.value<num64 > ());
                }
                case TYPE_UNUM64:
                {
                    if (rside.value<unum64 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return ( lside.value<unum64 > () / rside.value<unum64 > ());
                }
                case TYPE_NUM32:
                {
                    if (rside.value<num32 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return ( lside.value<num32 > () / rside.value<num32 > ());
                }
                case TYPE_UNUM32:
                {
                    if (rside.value<unum32 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return ( lside.value<unum32 > () / rside.value<unum32 > ());
                }
                case TYPE_NUM16:
                {
                    if (rside.value<num16 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return ( lside.value<num16 > () / rside.value<num16 > ());
                }
                case TYPE_UNUM16:
                {
                    if (rside.value<unum16 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return ( lside.value<unum16 > () / rside.value<unum16 > ());
                }
                case TYPE_NUM8:
                {
                    if (rside.value<num8 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return ( lside.value<num8 > () / rside.value<num8 > ());
                }
                case TYPE_UNUM8:
                {
                    if (rside.value<unum8 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return ( lside.value<unum8 > () / rside.value<unum8 > ());
                }
                case TYPE_DOUBLE:
                {
                    if (rside.value<double>() == 0) {
                        return NULL_DOUBLE;
                    }
                    return ( lside.value<double>() / rside.value<double>());
                }
                case TYPE_FLOAT:
                {
                    if (rside.value<float>() == 0) {
                        return NULL_DOUBLE;
                    }
                    return ( lside.value<float>() / rside.value<float>());
                }
                case TYPE_TM: return NULL_DOUBLE;
            }
            if (rside.value<double>() == 0) {
                return NULL_DOUBLE;
            }
            return (lside.value<double>() / rside.value<double>());
        }

        calc_token operator%(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_NODEF: return NULL_DOUBLE;
                case TYPE_DISCRET:
                {
                    return NULL_DOUBLE;
                }
                case TYPE_NUM64:
                {
                    if (rside.value<num64 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return (lside.value<num64 > () % rside.value<num64 > ());
                }
                case TYPE_UNUM64:
                {
                    if (rside.value<unum64 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return (lside.value<unum64 > () % rside.value<unum64 > ());
                }
                case TYPE_NUM32:
                {
                    if (rside.value<num32 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return (lside.value<num32 > () % rside.value<num32 > ());
                }
                case TYPE_UNUM32:
                {
                    if (rside.value<unum32 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return (lside.value<unum32 > () % rside.value<unum32 > ());
                }
                case TYPE_NUM16:
                {
                    if (rside.value<num16 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return (lside.value<num16 > () % rside.value<num16 > ());
                }
                case TYPE_UNUM16:
                {
                    if (rside.value<unum16 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return (lside.value<unum16 > () % rside.value<unum16 > ());
                }
                case TYPE_NUM8:
                {
                    if (rside.value<num8 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return (lside.value<num8 > () % rside.value<num8 > ());
                }
                case TYPE_UNUM8:
                {
                    if (rside.value<unum8 > () == 0) {
                        return NULL_DOUBLE;
                    }
                    return (lside.value<unum8 > () % rside.value<unum8 > ());
                }
                case TYPE_DOUBLE: return NULL_DOUBLE;
                case TYPE_FLOAT: return NULL_DOUBLE;
                case TYPE_TM: return NULL_DOUBLE;
            }

            throw dvncierror(ERROR_EXPROPERATOR);
        }

        bool operator==(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_NODEF: return (lside.value<double>() == rside.value<double>());
                case TYPE_DISCRET: return (lside.value<bool>() == rside.value<bool>());
                case TYPE_NUM64: return (lside.value<num64 > () == rside.value<num64 > ());
                case TYPE_UNUM64: return (lside.value<unum64 > () == rside.value<unum64 > ());
                case TYPE_NUM32: return (lside.value<num32 > () == rside.value<num32 > ());
                case TYPE_UNUM32: return (lside.value<unum32 > () == rside.value<unum32 > ());
                case TYPE_NUM16: return (lside.value<num16 > () == rside.value<num16 > ());
                case TYPE_UNUM16: return (lside.value<unum16 > () == rside.value<unum16 > ());
                case TYPE_NUM8: return (lside.value<num8 > () == rside.value<num8 > ());
                case TYPE_UNUM8: return (lside.value<unum8 > () == rside.value<unum8 > ());
                case TYPE_DOUBLE: return (lside.value<double>() == rside.value<double>());
                case TYPE_FLOAT: return (lside.value<float>() == rside.value<float>());
                case TYPE_TEXT: return (lside.value<std::string>() == rside.value<std::string>());
                case TYPE_TM: return (lside.tm() == rside.tm());
            }
            return (lside.value<double>() == rside.value<double>());
        }

        bool operator<(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_NODEF: return (lside.value<double>() < rside.value<double>());
                case TYPE_DISCRET: return (lside.value<bool>() < rside.value<bool>());
                case TYPE_NUM64: return (lside.value<num64 > () < rside.value<num64 > ());
                case TYPE_UNUM64: return (lside.value<unum64 > () < rside.value<unum64 > ());
                case TYPE_NUM32: return (lside.value<num32 > () < rside.value<num32 > ());
                case TYPE_UNUM32: return (lside.value<unum32 > () < rside.value<unum32 > ());
                case TYPE_NUM16: return (lside.value<num16 > () < rside.value<num16 > ());
                case TYPE_UNUM16: return (lside.value<unum16 > () < rside.value<unum16 > ());
                case TYPE_NUM8: return (lside.value<num8 > () < rside.value<num8 > ());
                case TYPE_UNUM8: return (lside.value<unum8 > () < rside.value<unum8 > ());
                case TYPE_DOUBLE: return (lside.value<double>() < rside.value<double>());
                case TYPE_FLOAT: return (lside.value<float>() < rside.value<float>());
                case TYPE_TEXT: return (lside.value<std::string>() < rside.value<std::string>());
                case TYPE_TM: return (lside.tm() < rside.tm());
            }
            return (lside.value<double>() < rside.value<double>());
        }

        bool operator>(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_NODEF: return (lside.value<double>() > rside.value<double>());
                case TYPE_DISCRET: return (lside.value<bool>() > rside.value<bool>());
                case TYPE_NUM64: return (lside.value<num64 > () > rside.value<num64 > ());
                case TYPE_UNUM64: return (lside.value<unum64 > () > rside.value<unum64 > ());
                case TYPE_NUM32: return (lside.value<num32 > () > rside.value<num32 > ());
                case TYPE_UNUM32: return (lside.value<unum32 > () > rside.value<unum32 > ());
                case TYPE_NUM16: return (lside.value<num16 > () > rside.value<num16 > ());
                case TYPE_UNUM16: return (lside.value<unum16 > () > rside.value<unum16 > ());
                case TYPE_NUM8: return (lside.value<num8 > () > rside.value<num8 > ());
                case TYPE_UNUM8: return (lside.value<unum8 > () > rside.value<unum8 > ());
                case TYPE_DOUBLE: return (lside.value<double>() > rside.value<double>());
                case TYPE_FLOAT: return (lside.value<float>() > rside.value<float>());
                case TYPE_TEXT: return (lside.value<std::string>() > rside.value<std::string>());
                case TYPE_TM: return (lside.tm() > rside.tm());
            }
            return (lside.value<double>() > rside.value<double>());
        }

        bool operator!(calc_token& nval) {
            switch (nval.type()) {
                case TYPE_NODEF: return (!nval.value<double>());
                case TYPE_DISCRET: return !(nval.value<bool>());
                case TYPE_NUM64: return (nval.value<num64 > () == 0);
                case TYPE_UNUM64: return (nval.value<unum64 > () == 0);
                case TYPE_NUM32: return (nval.value<num32 > () == 0);
                case TYPE_UNUM32: return (nval.value<unum32 > () == 0);
                case TYPE_NUM16: return (nval.value<num16 > () == 0);
                case TYPE_UNUM16: return (nval.value<unum16 > () == 0);
                case TYPE_NUM8: return (nval.value<num8 > () == 0);
                case TYPE_UNUM8: return (nval.value<unum8 > () == 0);
                case TYPE_DOUBLE: return (nval.value<double>() == 0);
                case TYPE_FLOAT: return (nval.value<float>() == 0);
                case TYPE_TEXT: return (nval.value<std::string>() == "");
                case TYPE_TM: return NULL_DOUBLE;
            }
            return (nval.value<double>() == 0);
        }

        calc_token operator~(calc_token& nval) {
            switch (nval.type()) {
                case TYPE_NODEF: return (nval.value<double>() == 0);
                case TYPE_DISCRET: return !(nval.value<bool>());
                case TYPE_NUM64: return (~nval.value<num64 > ());
                case TYPE_UNUM64: return (~nval.value<unum64 > ());
                case TYPE_NUM32: return (~nval.value<num32 > ());
                case TYPE_UNUM32: return (~nval.value<unum32 > ());
                case TYPE_NUM16: return (~nval.value<num16 > ());
                case TYPE_UNUM16: return (~nval.value<unum16 > ());
                case TYPE_NUM8: return (~nval.value<num8 > ());
                case TYPE_UNUM8: return (~nval.value<unum8 > ());
                case TYPE_DOUBLE: return (nval.value<double>() == 0);
                case TYPE_FLOAT: return (nval.value<float>() == 0);
                case TYPE_TM: return NULL_DOUBLE;
            }
            return (nval.value<double>() == 0);
        }

        bool operator&&(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_NODEF:
                case TYPE_NUM64:
                case TYPE_UNUM64:
                case TYPE_NUM32:
                case TYPE_UNUM32:
                case TYPE_NUM16:
                case TYPE_UNUM16:
                case TYPE_NUM8:
                case TYPE_UNUM8:
                case TYPE_DISCRET:
                case TYPE_DOUBLE:
                case TYPE_FLOAT: return ((lside.value<bool>()) && (rside.value<bool>()));
                case TYPE_TM: return NULL_DOUBLE;
            }
            return ((lside.value<bool>()) && (rside.value<bool>()));
        }

        bool operator||(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_NODEF:
                case TYPE_NUM64:
                case TYPE_UNUM64:
                case TYPE_NUM32:
                case TYPE_UNUM32:
                case TYPE_NUM16:
                case TYPE_UNUM16:
                case TYPE_NUM8:
                case TYPE_UNUM8:
                case TYPE_DISCRET:
                case TYPE_DOUBLE:
                case TYPE_FLOAT: return ((lside.value<bool>()) || (rside.value<bool>()));
                case TYPE_TM: return NULL_DOUBLE;
            }
            return ((lside.value<bool>()) || (rside.value<bool>()));
        }

        calc_token operator&(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_NODEF: return (lside && rside);
                case TYPE_DISCRET: return (lside && rside);
                case TYPE_NUM64: return (lside.value<num64 > () & rside.value<num64 > ());
                case TYPE_UNUM64: return (lside.value<unum64 > () & rside.value<unum64 > ());
                case TYPE_NUM32: return (lside.value<num32 > () & rside.value<num32 > ());
                case TYPE_UNUM32: return (lside.value<unum32 > () & rside.value<unum32 > ());
                case TYPE_NUM16: return (lside.value<num16 > () & rside.value<num16 > ());
                case TYPE_UNUM16: return (lside.value<unum16 > () & rside.value<unum16 > ());
                case TYPE_NUM8: return (lside.value<num8 > () & rside.value<num8 > ());
                case TYPE_UNUM8: return (lside.value<unum8 > () & rside.value<unum8 > ());
                case TYPE_DOUBLE: return (lside && rside);
                case TYPE_FLOAT: return (lside && rside);
                case TYPE_TM: return NULL_DOUBLE;
            }
            return (lside && rside);
        }

        calc_token operator|(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_NODEF: return (lside || rside);
                case TYPE_DISCRET: return (lside || rside);
                case TYPE_NUM64: return (lside.value<num64 > () | rside.value<num64 > ());
                case TYPE_UNUM64: return (lside.value<unum64 > () | rside.value<unum64 > ());
                case TYPE_NUM32: return (lside.value<num32 > () | rside.value<num32 > ());
                case TYPE_UNUM32: return (lside.value<unum32 > () | rside.value<unum32 > ());
                case TYPE_NUM16: return (lside.value<num16 > () | rside.value<num16 > ());
                case TYPE_UNUM16: return (lside.value<unum16 > () | rside.value<unum16 > ());
                case TYPE_NUM8: return (lside.value<num8 > () | rside.value<num8 > ());
                case TYPE_UNUM8: return (lside.value<unum8 > () | rside.value<unum8 > ());
                case TYPE_DOUBLE: return (lside || rside);
                case TYPE_FLOAT: return (lside || rside);
                case TYPE_TM: return NULL_DOUBLE;
            }
            return (lside || rside);
        }

        calc_token operator^(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET: return (lside != rside);
                case TYPE_NUM64: return (lside.value<num64 > () ^ rside.value<num64 > ());
                case TYPE_UNUM64: return (lside.value<unum64 > () ^ rside.value<unum64 > ());
                case TYPE_NUM32: return (lside.value<num32 > () ^ rside.value<num32 > ());
                case TYPE_UNUM32: return (lside.value<unum32 > () ^ rside.value<unum32 > ());
                case TYPE_NUM16: return (lside.value<num16 > () ^ rside.value<num16 > ());
                case TYPE_UNUM16: return (lside.value<unum16 > () ^ rside.value<unum16 > ());
                case TYPE_NUM8: return (lside.value<num8 > () ^ rside.value<num8 > ());
                case TYPE_UNUM8: return (lside.value<unum8 > () ^ rside.value<unum8 > ());
                case TYPE_DOUBLE: return (((lside.value<double>() != 0) && (rside.value<double>() == 0)) ||
                            ((lside.value<double>() == 0) && (rside.value<double>() != 0)));
                case TYPE_FLOAT: return (((lside.value<float>() != 0) && (rside.value<float>() == 0)) ||
                            ((lside.value<float>() == 0) && (rside.value<float>() != 0)));
                case TYPE_TM: return NULL_DOUBLE;
            }
            return (((lside.value<double>() != 0) && (rside.value<double>() == 0)) ||
                    ((lside.value<double>() == 0) && (rside.value<double>() != 0)));
        }

        calc_token operator<<(const calc_token& lside, const calc_token& rside) {
            switch (lside.type()) {
                case TYPE_DISCRET:
                {
                    return ((!rside.value<bool>()) && ((lside.value<bool>())));
                }
                case TYPE_NUM64:
                {
                    if (rside.value<num64 > () > 63) {
                        return 0;
                    };
                    return (lside.value<num64 > () << rside.value<num64 > ());
                }
                case TYPE_UNUM64:
                {
                    if (rside.value<unum64 > () > 63) {
                        return 0;
                    };
                    return (lside.value<unum64 > () << rside.value<unum64 > ());
                }
                case TYPE_NUM32:
                {
                    if (rside.value<num32 > () > 31) {
                        return 0;
                    };
                    return (lside.value<num32 > () << rside.value<num32 > ());
                }
                case TYPE_UNUM32:
                {
                    if (rside.value<unum32 > () > 31) {
                        return 0;
                    };
                    return (lside.value<unum32 > () << rside.value<unum32 > ());
                }
                case TYPE_NUM16:
                {
                    if (rside.value<num16 > () > 15) {
                        return 0;
                    };
                    return (lside.value<num16 > () << rside.value<num16 > ());
                }
                case TYPE_UNUM16:
                {
                    if (rside.value<unum16 > () > 15) {
                        return 0;
                    };
                    return (lside.value<unum16 > () << rside.value<unum16 > ());
                }
                case TYPE_NUM8:
                {
                    if (rside.value<num8 > () > 7) {
                        return 0;
                    };
                    return (lside.value<num8 > () << rside.value<num8 > ());
                }
                case TYPE_UNUM8:
                {
                    if (rside.value<unum8 > () > 7) {
                        return 0;
                    };
                    return (lside.value<unum8 > () << rside.value<unum8 > ());
                }
                default: return NULL_DOUBLE;
            }
            return NULL_DOUBLE;
        }

        calc_token operator>>(const calc_token& lside, const calc_token& rside) {
            switch (lside.type()) {
                case TYPE_DISCRET:
                {
                    return ((!rside.value<bool>()) && ((lside.value<bool>())));
                }
                case TYPE_NUM64:
                {
                    if (rside.value<num64 > () > 63) {
                        return 0;
                    };
                    return (lside.value<num64 > () >> rside.value<num64 > ());
                }
                case TYPE_UNUM64:
                {
                    if (rside.value<unum64 > () > 63) {
                        return 0;
                    };
                    return (lside.value<unum64 > () >> rside.value<unum64 > ());
                }
                case TYPE_NUM32:
                {
                    if (rside.value<num32 > () > 31) {
                        return 0;
                    };
                    return (lside.value<num32 > () >> rside.value<num32 > ());
                }
                case TYPE_UNUM32:
                {
                    if (rside.value<unum32 > () > 31) {
                        return 0;
                    };
                    return (lside.value<unum32 > () >> rside.value<unum32 > ());
                }
                case TYPE_NUM16:
                {
                    if (rside.value<num16 > () > 15) {
                        return 0;
                    };
                    return (lside.value<num16 > () >> rside.value<num16 > ());
                }
                case TYPE_UNUM16:
                {
                    if (rside.value<unum16 > () > 15) {
                        return 0;
                    };
                    return (lside.value<unum16 > () >> rside.value<unum16 > ());
                }
                case TYPE_NUM8:
                {
                    if (rside.value<num8 > () > 7) {
                        return 0;
                    };
                    return (lside.value<num8 > () >> rside.value<num8 > ());
                }
                case TYPE_UNUM8:
                {
                    if (rside.value<unum8 > () > 7) {
                        return 0;
                    };
                    return (lside.value<unum8 > () >> rside.value<unum8 > ());
                }
                default: return NULL_DOUBLE;
            }
            return NULL_DOUBLE;
        }

        calc_token cycl_operator_btlft(const calc_token& lside, const calc_token& rside) {
            switch (lside.type()) {
                case TYPE_DISCRET:
                {
                    return ((!rside.value<bool>()) && ((lside.value<bool>())));
                }
                case TYPE_NUM64:
                {
                    return (cycl_btlft(lside.value<num64 > (), rside.value<size_t > ()));
                }
                case TYPE_UNUM64:
                {
                    return (cycl_btlft(lside.value<unum64 > (), rside.value<size_t > ()));
                }
                case TYPE_NUM32:
                {
                    return (cycl_btlft(lside.value<num32 > (), rside.value<size_t > ()));
                }
                case TYPE_UNUM32:
                {
                    return (cycl_btlft(lside.value<unum32 > (), rside.value<size_t > ()));
                }
                case TYPE_NUM16:
                {
                    return (cycl_btlft(lside.value<num16 > (), rside.value<size_t > ()));
                }
                case TYPE_UNUM16:
                {
                    return (cycl_btlft(lside.value<unum16 > (), rside.value<size_t > ()));
                }
                case TYPE_NUM8:
                {
                    return (cycl_btlft(lside.value<num8 > (), rside.value<size_t > ()));
                }
                case TYPE_UNUM8:
                {
                    return (cycl_btlft(lside.value<unum8 > (), rside.value<size_t > ()));
                }
                default: return NULL_DOUBLE;
            }
            return NULL_DOUBLE;
        }

        calc_token cycl_operator_btrgt(const calc_token& lside, const calc_token& rside) {
            switch (lside.type()) {
                case TYPE_DISCRET:
                {
                    return ((!rside.value<bool>()) && ((lside.value<bool>())));
                }
                case TYPE_NUM64:
                {
                    return (cycl_btrgt(lside.value<num64 > (), rside.value<size_t > ()));
                }
                case TYPE_UNUM64:
                {
                    return (cycl_btrgt(lside.value<unum64 > (), rside.value<size_t > ()));
                }
                case TYPE_NUM32:
                {
                    return (cycl_btrgt(lside.value<num32 > (), rside.value<size_t > ()));
                }
                case TYPE_UNUM32:
                {
                    return (cycl_btrgt(lside.value<unum32 > (), rside.value<size_t > ()));
                }
                case TYPE_NUM16:
                {
                    return (cycl_btrgt(lside.value<num16 > (), rside.value<size_t > ()));
                }
                case TYPE_UNUM16:
                {
                    return (cycl_btrgt(lside.value<unum16 > (), rside.value<size_t > ()));
                }
                case TYPE_NUM8:
                {
                    return (cycl_btrgt(lside.value<num8 > (), rside.value<size_t > ()));
                }
                case TYPE_UNUM8:
                {
                    return (cycl_btrgt(lside.value<unum8 > (), rside.value<size_t > ()));
                }
                default: return NULL_DOUBLE;
            }
            return NULL_DOUBLE;
        }

        calc_token calc_token::math_func1(calc_operation opr) {
            if (operation() != constant) throw dvncierror(ERROR_EXPROPERATOR);
            switch (opr) {
                case func_sin: return sin(value<double>());
                case func_cos: return cos(value<double>());
                case func_sqrt:
                {
                    return sqrt(value<double>());
                }
                case func_sqr: return ::pow(value<double>(), 2);
                case func_exp: return exp(value<double>());
                case func_ln:
                {
                    return log(value<double>());
                }
                case func_floor: return floor(value<double>());
                case func_ceiling: return ceil(value<double>());
                case func_log10: return log10(value<double>());
                case func_tan: return tan(value<double>());
                case func_acos: return acos(value<double>());
                case func_asin: return asin(value<double>());
                case func_atan: return acos(value<double>());
                case func_cosh: return cosh(value<double>());
                case func_sinh: return sinh(value<double>());
                case func_tanh: return tanh(value<double>());
                case func_round: return ((value<double>() - floor(value<double>())) < 0.5) ? floor(value<double>()): ceil(value<double>());
                default: return 0;
            }
            return (*this);
        }

        calc_token calc_token::getabs() {
            if (operation() != constant) throw dvncierror(ERROR_EXPROPERATOR);
            switch (type()) {
                case TYPE_DISCRET: return (value<bool>());
                case TYPE_NUM64: return value<num64 > () < 0 ? -(*this): (*this);
                case TYPE_UNUM64: return (*this);
                case TYPE_NUM32: return value<num32 > () < 0 ? -(*this): (*this);
                case TYPE_UNUM32: return (*this);
                case TYPE_NUM16: return value<num16 > () < 0 ? -(*this): (*this);
                case TYPE_UNUM16: return (*this);
                case TYPE_NUM8: return value<num8 > () < 0 ? -(*this): (*this);
                case TYPE_UNUM8: return (*this);
                case TYPE_DOUBLE: return value<double>() < 0 ? -(*this): (*this);
                case TYPE_FLOAT: return value<float>() < 0 ? -(*this): (*this);
                case TYPE_TM: return NULL_DOUBLE;
            }
            return value<double>() < 0 ? -(*this) : (*this);
        }

        calc_token calc_token::gettypedval(calc_operation oper) {
            switch (oper) {
                case oper_cast_basetype:
                {
                    return value<double>();
                }
                case oper_cast_num64:
                {
                    return value<num64 > ();
                }
                case oper_cast_unum64:
                {
                    return value<unum64 > ();
                }
                case oper_cast_num32:
                {
                    return value<num32 > ();
                }
                case oper_cast_unum32:
                {
                    return value<unum32 > ();
                }
                case oper_cast_num16:
                {
                    return value<num16 > ();
                }
                case oper_cast_unum16:
                {
                    return value<unum16 > ();
                }
                case oper_cast_num8:
                {
                    return value<num8 > ();
                }
                case oper_cast_unum8:
                {
                    return value<unum8 > ();
                }
                case oper_cast_float:
                {
                    return value<float>();
                }
                case oper_cast_double:
                {
                    return value<double>();
                }
                case oper_cast_bool:
                {
                    return value<bool>();
                }
                case oper_cast_text:
                {
                    return value<std::string > ();
                }
                default:
                {
                    return value<double>();
                }
            }
            return value<double>();
        }

        calc_token math_pow(const calc_token& lside, const calc_token& rside) {
            if (lside.operation() != constant) return NULL_DOUBLE;
            if (rside.operation() != constant) return NULL_DOUBLE;
            return (::pow(lside.value<double>(), rside.value<double>()));
        }

        calc_token minim(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET: return (lside.value<bool>() && rside.value<bool>());
                case TYPE_NUM64: return (lside.value<num64 > () < rside.value<num64 > ()) ? lside.value<num64 > (): rside.value<num64 > ();
                case TYPE_UNUM64: return (lside.value<unum64 > () < rside.value<unum64 > ()) ? lside.value<unum64 > (): rside.value<unum64 > ();
                case TYPE_NUM32: return (lside.value<num32 > () < rside.value<num32 > ()) ? lside.value<num32 > (): rside.value<num32 > ();
                case TYPE_UNUM32: return (lside.value<unum32 > () < rside.value<unum32 > ()) ? lside.value<unum32 > (): rside.value<unum32 > ();
                case TYPE_NUM16: return (lside.value<num16 > () < rside.value<num16 > ()) ? lside.value<num16 > (): rside.value<num16 > ();
                case TYPE_UNUM16: return (lside.value<unum16 > () < rside.value<unum16 > ()) ? lside.value<unum16 > (): rside.value<unum16 > ();
                case TYPE_NUM8: return (lside.value<num8 > () < rside.value<num8 > ()) ? lside.value<num8 > (): rside.value<num8 > ();
                case TYPE_UNUM8: return (lside.value<unum8 > () < rside.value<unum8 > ()) ? lside.value<unum8 > (): rside.value<unum8 > ();
                case TYPE_DOUBLE: return (lside.value<double>() < rside.value<double>()) ? lside.value<double>(): rside.value<double>();
                case TYPE_FLOAT: return (lside.value<float>() < rside.value<float>()) ? lside.value<float>(): rside.value<float>();
                case TYPE_TM: return (lside.tm() < rside.tm()) ? lside.tm(): rside.tm();
            }
            return (lside.value<double>() < rside.value<double>()) ? lside.value<double>() : rside.value<double>();
        }

        calc_token maxim(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET: return (lside.value<bool>() || rside.value<bool>());
                case TYPE_NUM64: return (lside.value<num64 > () > rside.value<num64 > ()) ? lside.value<num64 > (): rside.value<num64 > ();
                case TYPE_UNUM64: return (lside.value<unum64 > () > rside.value<unum64 > ()) ? lside.value<unum64 > (): rside.value<unum64 > ();
                case TYPE_NUM32: return (lside.value<num32 > () > rside.value<num32 > ()) ? lside.value<num32 > (): rside.value<num32 > ();
                case TYPE_UNUM32: return (lside.value<unum32 > () > rside.value<unum32 > ()) ? lside.value<unum32 > (): rside.value<unum32 > ();
                case TYPE_NUM16: return (lside.value<num16 > () > rside.value<num16 > ()) ? lside.value<num16 > (): rside.value<num16 > ();
                case TYPE_UNUM16: return (lside.value<unum16 > () > rside.value<unum16 > ()) ? lside.value<unum16 > (): rside.value<unum16 > ();
                case TYPE_NUM8: return (lside.value<num8 > () > rside.value<num8 > ()) ? lside.value<num8 > (): rside.value<num8 > ();
                case TYPE_UNUM8: return (lside.value<unum8 > () > rside.value<unum8 > ()) ? lside.value<unum8 > (): rside.value<unum8 > ();
                case TYPE_DOUBLE: return (lside.value<double>() > rside.value<double>()) ? lside.value<double>(): rside.value<double>();
                case TYPE_FLOAT: return (lside.value<float>() > rside.value<float>()) ? lside.value<float>(): rside.value<float>();
                case TYPE_TM: return (lside.tm() > rside.tm()) ? lside.tm(): rside.tm();
            }
            return (lside.value<double>() > rside.value<double>()) ? lside.value<double>() : rside.value<double>();
        }

        datetime calc_token::tm() const {
            if (type() == TYPE_TM) {
                try {
                    return cast_datetime_fromnum64(value());
                }                catch (...) {
                }
            }
            return datetime();
        }




    }
}
