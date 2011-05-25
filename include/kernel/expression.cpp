/* 
 * File:   expression.cpp
 * Author: Serg
 * 
 * Created on 12 Май 2010 г., 12:50
 */

#include <kernel/expression.h>



namespace dvnci {
    namespace expr {

        std::ostream & operator<<(std::ostream& os, calc_operation oper) {
                switch (oper) {
                    case notoperation: return os << "nooper";
                    case expr: return os << "var";
                    case constant: return os << "const";
                    case oprt_leftgroup: return os << "(";          // (  1
                    case oprt_rightgroup: return os << ")";         // )  1
                    case oprt_selector: return os << ".";
                    case oprt_comma: return os << ",";
                    case select_mineu: return os << "mineu";
                    case select_maxeu: return os << "maxeu";
                    case select_ack: return os << "ack";
                    case select_alarmack: return os << "alarmack";
                    case select_alarm: return os << "alarm";
                    case select_mod: return os << "sct mod";
                    case select_num: return os << "sct num";
                    case func_num: return os << "num";
                    case select_real: return os << "sct real";
                    case func_real: return os << "real";
                    case select_bool: return os << "sct bool";
                    case func_bool: return os << "bool";
                    case func_min: return os << "min";
                    case func_max: return os << "max";
                    case func_abs: return os << "abs";
                    case func_sin: return os << "sin";
                    case func_cos: return os << "cos";
                    case func_pow: return os << "pow";
                    case func_sqrt: return os << "sqrt";
                    case func_sqr: return os << "sqr";
                    case func_exp: return os << "exp";
                    case func_ln: return os << "ln";
                    case func_log10: return os << "log10";
                    case func_tan: return os << "tan";
                    case func_acos: return os << "acos";
                    case func_asin: return os << "asin";
                    case func_atan: return os << "atan";
                    case func_cosh: return os << "cosh";
                    case func_sinh: return os << "sinh";
                    case func_tanh: return os << "tanh";
                    case func_rnd: return os << "rnd";
                    case func_floor: return os << "floor";
                    case func_ceiling: return os << "seil";
                    case func_round: return os << "round";
                    case const_nan: return os << "null";
                    case const_e: return os << "e";
                    case const_pi: return os << "pi";
                    case oprt_opnot: return os << "!";
                    case oprt_opexnot: return os << "~";
                    case oprt_add_unary: return os << "unary +";
                    case oprt_sub_unary: return os << "unary -";
                    case oper_cast_basetype: return os << "(notype)";
                    case oper_cast_num64: return os << "(num64)";
                    case oper_cast_unum64: return os << "(unum64)";
                    case oper_cast_num32: return os << "(num32)";
                    case oper_cast_unum32: return os << "(unum32)";
                    case oper_cast_num16: return os << "(num16)";
                    case oper_cast_unum16: return os << "(unum16)";
                    case oper_cast_num8: return os << "(num8)";
                    case oper_cast_unum8: return os << "(unum8)";
                    case oper_cast_float: return os << "(float)";
                    case oper_cast_double: return os << "(double)";
                    case oper_cast_bool: return os << "(bool)";
                    case oper_cast_time: return os << "(time)";
                    case oper_cast_text: return os << "(text)";
                    case const_now: return os << "now";
                    case select_time: return os << ".time";
                    case select_logtime: return os << ".logtime";
                    case select_error: return os << ".error";
                    case select_valid: return os << ".valid";
                    case select_epoch: return os << ".epoch";
                    case select_epochmsc: return os << ".epochmsc";
                    case select_epochminute: return os << ".epochminute";
                    case select_epochhour: return os << ".epochhour";
                    case select_epochday: return os << ".epochday";
                    case select_msc: return os << ".msc";
                    case select_sec: return os << ".sec";
                    case select_minute: return os << ".minute";
                    case select_hour: return os << ".hour";
                    case select_day: return os << ".day";
                    case select_month: return os << ".month";
                    case select_year: return os << ".year";
                    case select_dayweek: return os << ".dayweek";
                    case select_dayyear: return os << ".dayyear";
                    case select_monthdays: return os << ".monthdays";
                    case select_lastvalue: return os << ".lastvalue";
                    case oprt_mult: return os << "*";
                    case oprt_div: return os << "/";
                    case oprt_modulo: return os << "%";
                    case oprt_add: return os << "+";
                    case oprt_sub: return os << "-";
                    case oprt_bitleft: return os << "<<";
                    case oprt_bitright: return os << ">>";
                    case oprt_cyclbitleft: return os << "<<<";
                    case oprt_cyclbitright: return os << ">>>";
                    case oprt_compless: return os << "<";
                    case oprt_complessoreq: return os << "<=";
                    case oprt_compmore: return os << ">";
                    case oprt_compmoreoreq: return os << ">=";
                    case oprt_compeq: return os << "==";
                    case oprt_compnoteq: return os << "!=";
                    case oprt_bitand: return os << "&";
                    case oprt_bitexor: return os << "^";
                    case oprt_bitor: return os << "|";
                    case oprt_logicand: return os << "&&";
                    case oprt_casedelim: return os << ":";
                    case oprt_caseleftgroup: return os << "[";
                    case oprt_caserightgroup: return os << "]";
                    case oprt_logicor: return os << "||";
                    case oprt_condit: return os << "?";
                    case oprt_command: return os << "@";
                    case oprt_kvit: return os << "#";
                    case oprt_postinc: return os << "post++";
                    case oprt_postdec: return os << "post--";
                    case oprt_prefinc: return os << "pref++";
                    case oprt_prefdec: return os << "pref--";
                    case func_incmsc: return os << "incmsc";
                    case func_incsec: return os << "incsec";
                    case func_incminute: return os << "incminute";
                    case func_inchour: return os << "inchour";
                    case func_incday: return os << "incday";
                    case oprt_allvalid_unary: return os << "allvld &";}
                return os << "nodef";}

        

        tagtype  type_cast(const calc_token& v1, const calc_token& v2) {
            tagtype mintp = v1.type() < v2.type() ? v1.type() : v2.type();
            tagtype maxtp = v1.type() > v2.type() ? v1.type() : v2.type();
            return (mintp == maxtp) ? mintp :
                    ((mintp < EVENT_TYPE_OSC) ?  ((maxtp <= TYPE_DISCRET) ? mintp : TYPE_NODEF) :
                     (maxtp < REPORTTYPE_YEAR) ?  mintp : TYPE_NODEF);}

        calc_token operator+(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET:  return (lside.value<bool>() || rside.value<bool>());
                case TYPE_NUM64:    return (lside.value<num64 > () + rside.value<num64 > ());
                case TYPE_UNUM64:   return (lside.value<unum64 > () + rside.value<unum64 > ());
                case TYPE_NUM32:    return (lside.value<num32 > () + rside.value<num32 > ());
                case TYPE_UNUM32:   return (lside.value<unum32 > () + rside.value<unum32 > ());
                case TYPE_NUM16:    return (lside.value<num16 > () + rside.value<num16 > ());
                case TYPE_UNUM16:   return (lside.value<unum16 > () + rside.value<unum16 > ());
                case TYPE_NUM8:     return (lside.value<num8 > () + rside.value<num8 > ());
                case TYPE_UNUM8:    return (lside.value<unum8 > () + rside.value<unum8 > ());
                case TYPE_DOUBLE:   return (lside.value<double>() + rside.value<double>());
                case TYPE_FLOAT:    return (lside.value<float>() + rside.value<float>());
                case TYPE_TM:       return NULL_DOUBLE;}
            return (lside.value<double>() + rside.value<double>());}

        calc_token operator-(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET:  return NULL_DOUBLE;
                case TYPE_NUM64:    return (lside.value<num64 > ())-(rside.value<num64 > ());
                case TYPE_UNUM64:   return (lside.value<unum64 > () - rside.value<unum64 > ());
                case TYPE_NUM32:    return (lside.value<num32 > () - rside.value<num32 > ());
                case TYPE_UNUM32:   return (lside.value<unum32 > () - rside.value<unum32 > ());
                case TYPE_NUM16:    return (lside.value<num16 > () - rside.value<num16 > ());
                case TYPE_UNUM16:   return (lside.value<unum16 > () - rside.value<unum16 > ());
                case TYPE_NUM8:     return (lside.value<num8 > () - rside.value<num8 > ());
                case TYPE_UNUM8:    return (lside.value<unum8 > () - rside.value<unum8 > ());
                case TYPE_DOUBLE:   return (lside.value<double>() - rside.value<double>());
                case TYPE_FLOAT:    return (lside.value<float>() - rside.value<float>());
                case TYPE_TM:       return NULL_DOUBLE;}
            return (lside.value<double>() - rside.value<double>());}

        calc_token operator-(calc_token& nval) {
            switch (nval.type()) {
                case TYPE_DISCRET:  return NULL_DOUBLE;
                case TYPE_NUM64:    return (-nval.value<num64 > ());
                case TYPE_UNUM64:   return (nval.value<unum64 > ());
                case TYPE_NUM32:    return (-nval.value<num32 > ());
                case TYPE_UNUM32:   return (nval.value<unum32 > ());
                case TYPE_NUM16:    return (-nval.value<num16 > ());
                case TYPE_UNUM16:   return (nval.value<unum16 > ());
                case TYPE_NUM8:     return (-nval.value<num8 > ());
                case TYPE_UNUM8:    return (nval.value<unum8 > ());
                case TYPE_DOUBLE:   return (-nval.value<double>());
                case TYPE_FLOAT:    return (-nval.value<float>());
                case TYPE_TM:       return NULL_DOUBLE;}
            return (-nval.value<double>());}

        calc_token operator*(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET:  return (lside.value<bool>() && rside.value<bool>());
                case TYPE_NUM64:    return (lside.value<num64 > () * rside.value<num64 > ());
                case TYPE_UNUM64:   return (lside.value<unum64 > () * rside.value<unum64 > ());
                case TYPE_NUM32:    return (lside.value<num32 > () * rside.value<num32 > ());
                case TYPE_UNUM32:   return (lside.value<unum32 > () * rside.value<unum32 > ());
                case TYPE_NUM16:    return (lside.value<num16 > () * rside.value<num16 > ());
                case TYPE_UNUM16:   return (lside.value<unum16 > () * rside.value<unum16 > ());
                case TYPE_NUM8:     return (lside.value<num8 > () * rside.value<num8 > ());
                case TYPE_UNUM8:    return (lside.value<unum8 > () * rside.value<unum8 > ());
                case TYPE_DOUBLE:   return (lside.value<double>() * rside.value<double>());
                case TYPE_FLOAT:    return (lside.value<float>() * rside.value<float>());
                case TYPE_TM:       return NULL_DOUBLE;}
            return (lside.value<double>() * rside.value<double>());}

        calc_token operator/(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET:{
                    return NULL_DOUBLE;}
                case TYPE_NUM64:{
                    if (rside.value<num64 > () == 0) {
                        return NULL_DOUBLE;}
                    return ( lside.value<num64 > () / rside.value<num64 > ());}
                case TYPE_UNUM64:{
                    if (rside.value<unum64 > () == 0) {
                        return NULL_DOUBLE;}
                    return ( lside.value<unum64 > () / rside.value<unum64 > ());}
                case TYPE_NUM32:{
                    if (rside.value<num32 > () == 0) {
                        return NULL_DOUBLE;}
                    return ( lside.value<num32 > () / rside.value<num32 > ());}
                case TYPE_UNUM32:{
                    if (rside.value<unum32 > () == 0) {
                        return NULL_DOUBLE;}
                    return ( lside.value<unum32 > () / rside.value<unum32 > ());}
                case TYPE_NUM16:{
                    if (rside.value<num16 > () == 0) {
                        return NULL_DOUBLE;}
                    return ( lside.value<num16 > () / rside.value<num16 > ());}
                case TYPE_UNUM16:{
                    if (rside.value<unum16 > () == 0) {
                        return NULL_DOUBLE;}
                    return ( lside.value<unum16 > () / rside.value<unum16 > ());}
                case TYPE_NUM8:{
                    if (rside.value<num8 > () == 0) {
                        return NULL_DOUBLE;}
                    return ( lside.value<num8 > () / rside.value<num8 > ());}
                case TYPE_UNUM8:{
                    if (rside.value<unum8 > () == 0) {
                        return NULL_DOUBLE;}
                    return ( lside.value<unum8 > () / rside.value<unum8 > ());}
                case TYPE_DOUBLE:{
                    if (rside.value<double>() == 0) {
                        return NULL_DOUBLE;}
                    return ( lside.value<double>() / rside.value<double>());}
                case TYPE_FLOAT:{
                    if (rside.value<float>() == 0) {
                        return NULL_DOUBLE;}
                    return ( lside.value<float>() / rside.value<float>());}
                case TYPE_TM:  return NULL_DOUBLE;}
            if (rside.value<double>() == 0) {
                return NULL_DOUBLE;}
            return (lside.value<double>() / rside.value<double>());}

        calc_token operator%(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET:{
                    return NULL_DOUBLE;}
                case TYPE_NUM64:{
                    if (rside.value<num64 > () == 0) {
                        return NULL_DOUBLE;}
                    return (lside.value<num64 > () % rside.value<num64 > ());}
                case TYPE_UNUM64:{
                    if (rside.value<unum64 > () == 0) {
                        return NULL_DOUBLE;}
                    return (lside.value<unum64 > () % rside.value<unum64 > ());}
                case TYPE_NUM32:{
                    if (rside.value<num32 > () == 0) {
                        return NULL_DOUBLE;}
                    return (lside.value<num32 > () % rside.value<num32 > ());}
                case TYPE_UNUM32:{
                    if (rside.value<unum32 > () == 0) {
                        return NULL_DOUBLE;}
                    return (lside.value<unum32 > () % rside.value<unum32 > ());}
                case TYPE_NUM16:{
                    if (rside.value<num16 > () == 0) {
                        return NULL_DOUBLE;}
                    return (lside.value<num16 > () % rside.value<num16 > ());}
                case TYPE_UNUM16:{
                    if (rside.value<unum16 > () == 0) {
                        return NULL_DOUBLE;}
                    return (lside.value<unum16 > () % rside.value<unum16 > ());}
                case TYPE_NUM8:{
                    if (rside.value<num8 > () == 0) {
                        return NULL_DOUBLE;}
                    return (lside.value<num8 > () % rside.value<num8 > ());}
                case TYPE_UNUM8:{
                    if (rside.value<unum8 > () == 0) {
                        return NULL_DOUBLE;}
                    return (lside.value<unum8 > () % rside.value<unum8 > ());}
                case TYPE_DOUBLE:    return NULL_DOUBLE;
                case TYPE_FLOAT:     return NULL_DOUBLE;
                case TYPE_TM:        return NULL_DOUBLE;}

            throw dvncierror(ERROR_EXPROPERATOR);}

        bool operator==(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET:  return (lside.value<bool>() == rside.value<bool>());
                case TYPE_NUM64:    return (lside.value<num64 > () == rside.value<num64 > ());
                case TYPE_UNUM64:   return (lside.value<unum64 > () == rside.value<unum64 > ());
                case TYPE_NUM32:    return (lside.value<num32 > () == rside.value<num32 > ());
                case TYPE_UNUM32:   return (lside.value<unum32 > () == rside.value<unum32 > ());
                case TYPE_NUM16:    return (lside.value<num16 > () == rside.value<num16 > ());
                case TYPE_UNUM16:   return (lside.value<unum16 > () == rside.value<unum16 > ());
                case TYPE_NUM8:     return (lside.value<num8 > () == rside.value<num8 > ());
                case TYPE_UNUM8:    return (lside.value<unum8 > () == rside.value<unum8 > ());
                case TYPE_DOUBLE:   return (lside.value<double>() == rside.value<double>());
                case TYPE_FLOAT:    return (lside.value<float>() == rside.value<float>());
                case TYPE_TM:       return (lside.tm() == rside.tm());}
            return (lside.value<double>() == rside.value<double>());}

        bool operator<(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET:  return (lside.value<bool>() < rside.value<bool>());
                case TYPE_NUM64:    return (lside.value<num64 > () < rside.value<num64 > ());
                case TYPE_UNUM64:    return (lside.value<unum64 > () < rside.value<unum64 > ());
                case TYPE_NUM32:    return (lside.value<num32 > () < rside.value<num32 > ());
                case TYPE_UNUM32:    return (lside.value<unum32 > () < rside.value<unum32 > ());
                case TYPE_NUM16:    return (lside.value<num16 > () < rside.value<num16 > ());
                case TYPE_UNUM16:    return (lside.value<unum16 > () < rside.value<unum16 > ());
                case TYPE_NUM8:    return (lside.value<num8 > () < rside.value<num8 > ());
                case TYPE_UNUM8:    return (lside.value<unum8 > () < rside.value<unum8 > ());
                case TYPE_DOUBLE:    return (lside.value<double>() < rside.value<double>());
                case TYPE_FLOAT:    return (lside.value<float>() < rside.value<float>());
                case TYPE_TM:       return (lside.tm() < rside.tm());}
            return (lside.value<double>() < rside.value<double>());}

        bool operator>(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET:  return (lside.value<bool>() > rside.value<bool>());
                case TYPE_NUM64:    return (lside.value<num64 > () > rside.value<num64 > ());
                case TYPE_UNUM64:    return (lside.value<unum64 > () > rside.value<unum64 > ());
                case TYPE_NUM32:    return (lside.value<num32 > () > rside.value<num32 > ());
                case TYPE_UNUM32:    return (lside.value<unum32 > () > rside.value<unum32 > ());
                case TYPE_NUM16:    return (lside.value<num16 > () > rside.value<num16 > ());
                case TYPE_UNUM16:    return (lside.value<unum16 > () > rside.value<unum16 > ());
                case TYPE_NUM8:    return (lside.value<num8 > () > rside.value<num8 > ());
                case TYPE_UNUM8:    return (lside.value<unum8 > () > rside.value<unum8 > ());
                case TYPE_DOUBLE:    return (lside.value<double>() > rside.value<double>());
                case TYPE_FLOAT:    return (lside.value<float>() > rside.value<float>());
                case TYPE_TM:       return (lside.tm() > rside.tm());}
            return (lside.value<double>() > rside.value<double>());}

        bool operator!(calc_token& nval) {
            switch (nval.type()) {
                case TYPE_DISCRET:  return !(nval.value<bool>());
                case TYPE_NUM64:    return (nval.value<num64 > () == 0);
                case TYPE_UNUM64:    return (nval.value<unum64 > () == 0);
                case TYPE_NUM32:    return (nval.value<num32 > () == 0);
                case TYPE_UNUM32:    return (nval.value<unum32 > () == 0);
                case TYPE_NUM16:    return (nval.value<num16 > () == 0);
                case TYPE_UNUM16:    return (nval.value<unum16 > () == 0);
                case TYPE_NUM8:    return (nval.value<num8 > () == 0);
                case TYPE_UNUM8:   return (nval.value<unum8 > () == 0);
                case TYPE_DOUBLE:    return (nval.value<double>() == 0);
                case TYPE_FLOAT:    return (nval.value<float>() == 0);
                case TYPE_TM:        return NULL_DOUBLE;}
            return (nval.value<double>() == 0);}

        calc_token operator~(calc_token& nval) {
            switch (nval.type()) {
                case TYPE_DISCRET:  return !(nval.value<bool>());
                case TYPE_NUM64:    return (~nval.value<num64 > ());
                case TYPE_UNUM64:    return (~nval.value<unum64 > ());
                case TYPE_NUM32:    return (~nval.value<num32 > ());
                case TYPE_UNUM32:    return (~nval.value<unum32 > ());
                case TYPE_NUM16:    return (~nval.value<num16 > ());
                case TYPE_UNUM16:    return (~nval.value<unum16 > ());
                case TYPE_NUM8:    return (~nval.value<num8 > ());
                case TYPE_UNUM8:   return (~nval.value<unum8 > ());
                case TYPE_DOUBLE:    return (nval.value<double>() == 0);
                case TYPE_FLOAT:    return (nval.value<float>() == 0);
                case TYPE_TM:        return NULL_DOUBLE;}
            return (nval.value<double>() == 0);}

        bool operator&&(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_NUM64:
                case TYPE_UNUM64:
                case TYPE_NUM32:
                case TYPE_UNUM32:
                case TYPE_NUM16:
                case TYPE_UNUM16:
                case TYPE_NUM8:
                case TYPE_UNUM8:
                case TYPE_DISCRET:   return ((lside.value() != 0) && (rside.value() != 0));
                case TYPE_DOUBLE:    return ((lside.value<double>() != 0) && (rside.value<double>() != 0));
                case TYPE_FLOAT:     return  ((lside.value<float>() != 0) && (rside.value<float>() != 0));
                case TYPE_TM:        return NULL_DOUBLE;}
            return ((lside.value<double>() != 0) && (rside.value<double>() != 0));}

        bool operator||(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_NUM64:
                case TYPE_UNUM64:
                case TYPE_NUM32:
                case TYPE_UNUM32:
                case TYPE_NUM16:
                case TYPE_UNUM16:
                case TYPE_NUM8:
                case TYPE_UNUM8:
                case TYPE_DISCRET:  return ((lside.value() != 0) || (rside.value() != 0));
                case TYPE_DOUBLE:    return ((lside.value<double>() != 0) || (rside.value<double>() != 0));
                case TYPE_FLOAT:    return  ((lside.value<float>() != 0) || (rside.value<float>() != 0));
                case TYPE_TM:       return NULL_DOUBLE;}
            return ((lside.value<double>() != 0) || (rside.value<double>() != 0));}

        calc_token operator&(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET:  return (lside && rside);
                case TYPE_NUM64:    return (lside.value<num64 > () & rside.value<num64 > ());
                case TYPE_UNUM64:    return (lside.value<unum64 > () & rside.value<unum64 > ());
                case TYPE_NUM32:    return (lside.value<num32 > () & rside.value<num32 > ());
                case TYPE_UNUM32:    return (lside.value<unum32 > () & rside.value<unum32 > ());
                case TYPE_NUM16:    return (lside.value<num16 > () & rside.value<num16 > ());
                case TYPE_UNUM16:    return (lside.value<unum16 > () & rside.value<unum16 > ());
                case TYPE_NUM8:    return (lside.value<num8 > () & rside.value<num8 > ());
                case TYPE_UNUM8:    return (lside.value<unum8 > () & rside.value<unum8 > ());
                case TYPE_DOUBLE:    return (lside && rside);
                case TYPE_FLOAT:    return (lside && rside);
                case TYPE_TM:       return NULL_DOUBLE;}
            return (lside && rside);}

        calc_token operator|(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET:  return (lside || rside);
                case TYPE_NUM64:    return (lside.value<num64 > () | rside.value<num64 > ());
                case TYPE_UNUM64:    return (lside.value<unum64 > () | rside.value<unum64 > ());
                case TYPE_NUM32:    return (lside.value<num32 > () | rside.value<num32 > ());
                case TYPE_UNUM32:    return (lside.value<unum32 > () | rside.value<unum32 > ());
                case TYPE_NUM16:    return (lside.value<num16 > () | rside.value<num16 > ());
                case TYPE_UNUM16:    return (lside.value<unum16 > () | rside.value<unum16 > ());
                case TYPE_NUM8:    return (lside.value<num8 > () | rside.value<num8 > ());
                case TYPE_UNUM8:    return (lside.value<unum8 > () | rside.value<unum8 > ());
                case TYPE_DOUBLE:    return (lside || rside);
                case TYPE_FLOAT:    return (lside || rside);
                case TYPE_TM:        return NULL_DOUBLE;}
            return (lside || rside);}

        calc_token operator^(const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET:  return (lside != rside);
                case TYPE_NUM64:    return (lside.value<num64 > () ^ rside.value<num64 > ());
                case TYPE_UNUM64:    return (lside.value<unum64 > () ^ rside.value<unum64 > ());
                case TYPE_NUM32:    return (lside.value<num32 > () ^ rside.value<num32 > ());
                case TYPE_UNUM32:    return (lside.value<unum32 > () ^ rside.value<unum32 > ());
                case TYPE_NUM16:    return (lside.value<num16 > () ^ rside.value<num16 > ());
                case TYPE_UNUM16:    return (lside.value<unum16 > () ^ rside.value<unum16 > ());
                case TYPE_NUM8:    return (lside.value<num8 > () ^ rside.value<num8 > ());
                case TYPE_UNUM8:    return (lside.value<unum8 > () ^ rside.value<unum8 > ());
                case TYPE_DOUBLE:    return (((lside.value<double>() != 0) && (rside.value<double>() == 0)) ||
                                             ((lside.value<double>() == 0) && (rside.value<double>() != 0)));
                case TYPE_FLOAT:    return (((lside.value<float>() != 0) && (rside.value<float>() == 0)) ||
                                            ((lside.value<float>() == 0) && (rside.value<float>() != 0)));
                case TYPE_TM:        return NULL_DOUBLE;}
            return (((lside.value<double>() != 0) && (rside.value<double>() == 0)) ||
                    ((lside.value<double>() == 0) && (rside.value<double>() != 0)));}

        calc_token operator<<(const calc_token& lside, const calc_token& rside) {
            switch (lside.type()) {
                case TYPE_DISCRET:{
                    return ((!rside.value<bool>()) && ((lside.value<bool>())));}
                case TYPE_NUM64:{
                    if (rside.value<num64 > () > 63) {
                        return 0;};
                    return (lside.value<num64 > () << rside.value<num64 > ());}
                case TYPE_UNUM64:{
                    if (rside.value<unum64 > () > 63) {
                        return 0;};
                    return (lside.value<unum64 > () << rside.value<unum64 > ());}
                case TYPE_NUM32:{
                    if (rside.value<num32 > () > 31) {
                        return 0;};
                    return (lside.value<num32 > () << rside.value<num32 > ());}
                case TYPE_UNUM32:{
                    if (rside.value<unum32 > () > 31) {
                        return 0;};
                    return (lside.value<unum32 > () << rside.value<unum32 > ());}
                case TYPE_NUM16:{
                    if (rside.value<num16 > () > 15) {
                        return 0;};
                    return (lside.value<num16 > () << rside.value<num16 > ());}
                case TYPE_UNUM16:{
                    if (rside.value<unum16 > () > 15) {
                        return 0;};
                    return (lside.value<unum16 > () << rside.value<unum16 > ());}
                case TYPE_NUM8:{
                    if (rside.value<num8 > () > 7) {
                        return 0;};
                    return (lside.value<num8 > () << rside.value<num8 > ());}
                case TYPE_UNUM8:{
                    if (rside.value<unum8 > () > 7) {
                        return 0;};
                    return (lside.value<unum8 > () << rside.value<unum8 > ());}
                default:        return NULL_DOUBLE;}
            return NULL_DOUBLE;}

        calc_token operator>>(const calc_token& lside, const calc_token& rside) {
            switch (lside.type()) {
                case TYPE_DISCRET:{
                    return ((!rside.value<bool>()) && ((lside.value<bool>())));}
                case TYPE_NUM64:{
                    if (rside.value<num64 > () > 63) {
                        return 0;};
                    return (lside.value<num64 > () >> rside.value<num64 > ());}
                case TYPE_UNUM64:{
                    if (rside.value<unum64 > () > 63) {
                        return 0;};
                    return (lside.value<unum64 > () >> rside.value<unum64 > ());}
                case TYPE_NUM32:{
                    if (rside.value<num32 > () > 31) {
                        return 0;};
                    return (lside.value<num32 > () >> rside.value<num32 > ());}
                case TYPE_UNUM32:{
                    if (rside.value<unum32 > () > 31) {
                        return 0;};
                    return (lside.value<unum32 > () >> rside.value<unum32 > ());}
                case TYPE_NUM16:{
                    if (rside.value<num16 > () > 15) {
                        return 0;};
                    return (lside.value<num16 > () >> rside.value<num16 > ());}
                case TYPE_UNUM16:{
                    if (rside.value<unum16 > () > 15) {
                        return 0;};
                    return (lside.value<unum16 > () >> rside.value<unum16 > ());}
                case TYPE_NUM8:{
                    if (rside.value<num8 > () > 7) {
                        return 0;};
                    return (lside.value<num8 > () >> rside.value<num8 > ());}
                case TYPE_UNUM8:{
                    if (rside.value<unum8 > () > 7) {
                        return 0;};
                    return (lside.value<unum8 > () >> rside.value<unum8 > ());}
                default: return NULL_DOUBLE;}
            return NULL_DOUBLE;}

          calc_token cycl_operator_btlft(const calc_token& lside, const calc_token& rside) {
            switch (lside.type()) {
                case TYPE_DISCRET:{
                    return ((!rside.value<bool>()) && ((lside.value<bool>())));}
                case TYPE_NUM64:{
                    return (cycl_btlft(lside.value<num64 > () , rside.value<size_t > ()));}
                case TYPE_UNUM64:{
                    return (cycl_btlft(lside.value<unum64 > () , rside.value<size_t > ()));}
                case TYPE_NUM32:{
                    return (cycl_btlft(lside.value<num32 > () , rside.value<size_t > ()));}
                case TYPE_UNUM32:{
                    return (cycl_btlft(lside.value<unum32 > () , rside.value<size_t > ()));}
                case TYPE_NUM16:{
                    return (cycl_btlft(lside.value<num16 > () , rside.value<size_t > ()));}
                case TYPE_UNUM16:{
                    return (cycl_btlft(lside.value<unum16 > () , rside.value<size_t > ()));}
                case TYPE_NUM8:{
                    return (cycl_btlft(lside.value<num8 > () , rside.value<size_t > ()));}
                case TYPE_UNUM8:{
                    return (cycl_btlft(lside.value<unum8 > () , rside.value<size_t > ()));}
                default:        return NULL_DOUBLE;}
            return NULL_DOUBLE;}

        calc_token cycl_operator_btrgt(const calc_token& lside, const calc_token& rside) {
            switch (lside.type()) {
                case TYPE_DISCRET:{
                    return ((!rside.value<bool>()) && ((lside.value<bool>())));}
                case TYPE_NUM64:{
                    return (cycl_btrgt(lside.value<num64 > () , rside.value<size_t > ()));}
                case TYPE_UNUM64:{
                    return (cycl_btrgt(lside.value<unum64 > () , rside.value<size_t > ()));}
                case TYPE_NUM32:{
                    return (cycl_btrgt(lside.value<num32 > () , rside.value<size_t > ()));}
                case TYPE_UNUM32:{
                    return (cycl_btrgt(lside.value<unum32 > () , rside.value<size_t > ()));}
                case TYPE_NUM16:{
                    return (cycl_btrgt(lside.value<num16 > () , rside.value<size_t > ()));}
                case TYPE_UNUM16:{
                    return (cycl_btrgt(lside.value<unum16 > () , rside.value<size_t > ()));}
                case TYPE_NUM8:{
                    return (cycl_btrgt(lside.value<num8 > () , rside.value<size_t > ()));}
                case TYPE_UNUM8:{
                    return (cycl_btrgt(lside.value<unum8 > () , rside.value<size_t > ()));}
                default:        return NULL_DOUBLE;}
            return NULL_DOUBLE;}

        calc_token calc_token::math_func1(calc_operation opr) {
            if (operation() != constant) throw dvncierror(ERROR_EXPROPERATOR);
            switch (opr) {
                case func_sin: return sin(value<double>());
                case func_cos: return cos(value<double>());
                case func_sqrt:{
                    return sqrt(value<double>());}
                case func_sqr: return pow(value<double>(), 2);
                case func_exp: return exp(value<double>());
                case func_ln:{
                    return log(value<double>());}
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
                case func_round: return ((value<double>() - floor(value<double>())) < 0.5) ?  floor(value<double>()): ceil(value<double>());
                default: return 0;}
            return (*this);}

        calc_token calc_token::getabs() {
            if (operation() != constant) throw dvncierror(ERROR_EXPROPERATOR);
            switch (type()) {
                case TYPE_DISCRET:  return (value<bool>());
                case TYPE_NUM64:    return  value<num64 > () < 0 ? -(*this): (*this);
                case TYPE_UNUM64:  return  (*this);
                case TYPE_NUM32:    return  value<num32 > () < 0 ? -(*this): (*this);
                case TYPE_UNUM32:   return  (*this);
                case TYPE_NUM16:    return  value<num16 > () < 0 ? -(*this): (*this);
                case TYPE_UNUM16:   return  (*this);
                case TYPE_NUM8:     return  value<num8 > () < 0 ? -(*this): (*this);
                case TYPE_UNUM8:   return   (*this);
                case TYPE_DOUBLE:  return  value<double>() < 0 ? -(*this): (*this);
                case TYPE_FLOAT:   return   value<float>() < 0 ? -(*this): (*this);
                case TYPE_TM:      return NULL_DOUBLE;}
            return  value<double>() < 0 ? -(*this) : (*this);}

        calc_token calc_token::gettypedval(calc_operation oper) {
            switch (oper) {
                case oper_cast_basetype:{
                    return value<double>();}
                case oper_cast_num64:{
                    return value<num64 > ();}
                case oper_cast_unum64:{
                    return value<unum64 > ();}
                case oper_cast_num32:{
                    return value<num32 > ();}
                case oper_cast_unum32:{
                    return value<unum32 > ();}
                case oper_cast_num16:{
                    return value<num16 > ();}
                case oper_cast_unum16:{
                    return value<unum16 > ();}
                case oper_cast_num8:{
                    return value<num8 > ();}
                case oper_cast_unum8:{
                    return value<unum8 > ();}
                case oper_cast_float:{
                    return value<float>();}
                case oper_cast_double:{
                    return value<double>();}
                case oper_cast_bool:{
                    return value<bool>();}
                default:{
                    return value<double>();}}
            return value<double>();}

        calc_token math_pow(const calc_token& lside, const calc_token& rside) {
            if (lside.operation() != constant) return NULL_DOUBLE;
            if (rside.operation() != constant) return NULL_DOUBLE;
            return (pow(lside.value<double>(), rside.value<double>()));}

        calc_token minim (const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET:  return (lside.value<bool>() && rside.value<bool>());
                case TYPE_NUM64:    return (lside.value<num64 > () < rside.value<num64 > ()) ? lside.value<num64 > (): rside.value<num64 > ();
                case TYPE_UNUM64:  return (lside.value<unum64 > () < rside.value<unum64 > ()) ? lside.value<unum64 > (): rside.value<unum64 > ();
                case TYPE_NUM32:    return (lside.value<num32 > () < rside.value<num32 > ()) ? lside.value<num32 > (): rside.value<num32 > ();
                case TYPE_UNUM32:    return (lside.value<unum32 > () < rside.value<unum32 > ()) ? lside.value<unum32 > (): rside.value<unum32 > ();
                case TYPE_NUM16:    return (lside.value<num16 > () < rside.value<num16 > ()) ? lside.value<num16 > (): rside.value<num16 > ();
                case TYPE_UNUM16:    return (lside.value<unum16 > () < rside.value<unum16 > ()) ? lside.value<unum16 > (): rside.value<unum16 > ();
                case TYPE_NUM8:     return (lside.value<num8 > () < rside.value<num8 > ()) ? lside.value<num8 > (): rside.value<num8 > ();
                case TYPE_UNUM8:    return (lside.value<unum8 > () < rside.value<unum8 > ()) ? lside.value<unum8 > (): rside.value<unum8 > ();
                case TYPE_DOUBLE:    return (lside.value<double>() < rside.value<double>()) ? lside.value<double>(): rside.value<double>();
                case TYPE_FLOAT:    return (lside.value<float>() < rside.value<float>()) ? lside.value<float>(): rside.value<float>();
                case TYPE_TM:         return (lside.tm() < rside.tm()) ? lside.tm(): rside.tm();}
            return (lside.value<double>() < rside.value<double>()) ? lside.value<double>() : rside.value<double>();}

        calc_token maxim (const calc_token& lside, const calc_token& rside) {
            switch (type_cast(lside, rside)) {
                case TYPE_DISCRET:  return (lside.value<bool>() || rside.value<bool>());
                case TYPE_NUM64:    return (lside.value<num64 > () > rside.value<num64 > ()) ? lside.value<num64 > (): rside.value<num64 > ();
                case TYPE_UNUM64:  return (lside.value<unum64 > () > rside.value<unum64 > ()) ? lside.value<unum64 > (): rside.value<unum64 > ();
                case TYPE_NUM32:    return (lside.value<num32 > () > rside.value<num32 > ()) ? lside.value<num32 > (): rside.value<num32 > ();
                case TYPE_UNUM32:    return (lside.value<unum32 > () > rside.value<unum32 > ()) ? lside.value<unum32 > (): rside.value<unum32 > ();
                case TYPE_NUM16:    return (lside.value<num16 > () > rside.value<num16 > ()) ? lside.value<num16 > (): rside.value<num16 > ();
                case TYPE_UNUM16:    return (lside.value<unum16 > () > rside.value<unum16 > ()) ? lside.value<unum16 > (): rside.value<unum16 > ();
                case TYPE_NUM8:     return (lside.value<num8 > () > rside.value<num8 > ()) ? lside.value<num8 > (): rside.value<num8 > ();
                case TYPE_UNUM8:    return (lside.value<unum8 > () > rside.value<unum8 > ()) ? lside.value<unum8 > (): rside.value<unum8 > ();
                case TYPE_DOUBLE:    return (lside.value<double>() > rside.value<double>()) ? lside.value<double>(): rside.value<double>();
                case TYPE_FLOAT:    return (lside.value<float>() > rside.value<float>()) ? lside.value<float>(): rside.value<float>();
                case TYPE_TM:         return (lside.tm() > rside.tm()) ? lside.tm(): rside.tm();}
            return (lside.value<double>() > rside.value<double>()) ? lside.value<double>() : rside.value<double>();}

        datetime calc_token::tm() const {
            if (type()== TYPE_TM) {
                try {
                    return cast_datetime_fromnum64(value());}
                catch (...) {}}
            return datetime();}






}}
