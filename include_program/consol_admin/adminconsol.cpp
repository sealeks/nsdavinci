/* 
 * File:   adminconsol.cpp
 * Author: sealeks@mail.ru
 * 
 * Created on 7 Июль 2011 г., 1:01
 */

#include "adminconsol.h"

namespace adminconsol {



    const wstr_cmd_pair cmd_array[] = {
        wstr_cmd_pair( wstdstr_ptr ( new std::wstring(L"select ")), SELECT_COMMAND_TAG)};

    command_executor_ptr command_factory_switch(adminintf_ptr inf, commandid id, const std::wstring& cmd) {
        switch (id) {
            case SELECT_COMMAND_TAG: return command_executor_ptr(new select_command_executor(inf, cmd));
            default:{};}
        return command_executor_ptr();}

    command_executor_ptr command_factory(adminintf_ptr inf, const std::wstring& cmd) {
        std::wstring icmd = dvnci::trim_copy(cmd);
        for (std::size_t i = 0; i < (sizeof (cmd_array) / sizeof (wstr_cmd_pair)); ++i) {
            if (cmd_array[i].first->size() <= cmd.size()) {
                std::wstring::size_type itcmd = cmd_array[i].first->size();
                std::wstring icmd_p = icmd.substr(0, itcmd);
                if (icmd_p == (*(cmd_array[i].first))) {
                    return command_factory_switch(inf, cmd_array[i].second, icmd.substr(itcmd));}}}
        return command_executor_ptr();}




    // parser (*|id|name|...)* from

    bool column_factory(columnname_vect& vct, std::wstring column) {
        if (boost::algorithm::find_first(column, L"*")) {
            vct.push_back(CN_ALL);
            return true;}
        if (boost::algorithm::find_first(column, L"id")) {
            vct.push_back(CN_ID);}
        if (boost::algorithm::find_first(column, L"name")) {
            vct.push_back(CN_NAME);}
        if (boost::algorithm::find_first(column, L"comment")) {
            vct.push_back(CN_COMMENT);}
        if (boost::algorithm::find_first(column, L"binding")) {
            vct.push_back(CN_BINDING);}
        return vct.empty();}

    bool colump_parser(const std::wstring& next, std::wstring& val, columnname_vect& vct) {
        if (boost::algorithm::find_first(val, next)) {
            boost::algorithm::find_first(val, next).begin();
            std::wstring bf(val.begin(), boost::algorithm::find_first(val, next).begin());
            val = std::wstring(boost::algorithm::find_first(val, next).begin() + next.size(), val.end());
            return column_factory(vct, bf);}
        return false;}

    // parser (tags|groups|agroups|users|...)

    tablename table_parser(const std::wstring& next, std::wstring& val) {
        std::wstring tn = val;
        if (boost::algorithm::find_first(val, next)) {
            tn = std::wstring(val.begin(), boost::algorithm::find_first(val, next).begin());
            val = std::wstring(boost::algorithm::find_first(val, next).begin() + next.size(), val.end());}
        else {
            val = L"";};
        if (boost::algorithm::find_first(tn, L"tags")) {
            return tags;}
        if (boost::algorithm::find_first(tn, L"groups")) {
            return groups;}
        if (boost::algorithm::find_first(tn, L"agroups")) {
            return agroups;}
        if (boost::algorithm::find_first(tn, L"users")) {
            return users;}
        if (boost::algorithm::find_first(tn, L"accessrules")) {
            return accessrules;}
        return no;}





}