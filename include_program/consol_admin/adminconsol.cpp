/* 
 * File:   adminconsol.cpp
 * Author: sealeks@mail.ru
 * 
 * Created on 7 Июль 2011 г., 1:01
 */

#include "adminconsol.h"

namespace adminconsol {
    
const wstr_cmd_pair cmd_array[] = { 
    wstr_cmd_pair( wstdstr_ptr ( new std::wstring(L"select tags where")), SELECT_COMMAND_TAG)
   };

    
command_executor_ptr command_factory_switch(adminintf_ptr inf, commandid id, const std::wstring& cmd){
    switch(id){
        case SELECT_COMMAND_TAG: return command_executor_ptr(new select_command_executor(inf, cmd));
        default:{};}
    return command_executor_ptr();}


command_executor_ptr command_factory(adminintf_ptr inf, const std::wstring& cmd){
    std::wstring icmd = dvnci::trim_copy(cmd);
    for (std::size_t i=0; i < (sizeof(cmd_array) / sizeof(wstr_cmd_pair)); ++i){
        if (cmd_array[i].first->size()<=cmd.size()){
            std::wstring::size_type itcmd = cmd_array[i].first->size();
            std::wstring icmd_p = icmd.substr(0,itcmd);
            if (icmd_p==(*(cmd_array[i].first))){
                return command_factory_switch(inf, cmd_array[i].second, icmd.substr(itcmd));}}}
    return command_executor_ptr();}

bool column_factory(columnname_vect& vct, std::wstring& cmd){
   return true; }




}