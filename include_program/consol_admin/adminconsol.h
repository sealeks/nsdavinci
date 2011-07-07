/* 
 * File:   adminconsol.h
 * Author: sealeks@mail.ru
 *
 * Created on 7 Р�СЋР»СЊ 2011 Рі., 1:01
 */

#ifndef ADMINCONSOL_H
#define	ADMINCONSOL_H

#include <kernel/memfile.h>
#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/factory.h>


#include <admin/factory.h>
#include <admin/adminsession.h>

namespace adminconsol {
    
using namespace std;
using namespace dvnci;
using namespace dvnci::admin;
using namespace boost::interprocess;


typedef std::vector<std::string>                                  stdstr_vect;
typedef num32                                                     commandid;

typedef boost::shared_ptr<std::wstring>                           wstdstr_ptr; 
typedef std::pair<wstdstr_ptr, commandid >                        wstr_cmd_pair;

typedef num64                                                     columnname; 
typedef std::vector<columnname>                                   columnname_vect;
    
const columnname CN_NO      = 0;
const columnname CN_ALL     = 0x1;
const columnname CN_ID      = 0x2;
const columnname CN_NAME    = 0x4;
const columnname CN_COMMENT = 0x8;
const columnname CN_BINDING = 0x10;
const columnname CN_MINEU   = 0x20;
const columnname CN_MAXEU   = 0x40;
const columnname CN_VALUE   = 0x80;
const columnname CN_TIME    = 0x100;
const columnname CN_ERROR   = 0x200;

enum tablename {
        no,
        tag,
        group,
        agroup,
        user,
        accessrule};

const commandid  SELECT_COMMAND_TAG = 10;




class basic_command_executor{
    
     
public:


               
    basic_command_executor(adminintf_ptr inf, const std::wstring& arg) : intf(inf), args(arg) {}
    
    virtual ~basic_command_executor(){}
    
    void execute(){
        parse();
        execute_impl();}
    
protected:
    
    virtual void parse(){};
    virtual void execute_impl(){
       std::wcout << L"Basis executed :" << std::endl;};
    adminintf_ptr intf;
    std::wstring   args;};
    
    
typedef boost::shared_ptr<basic_command_executor> command_executor_ptr;  


command_executor_ptr command_factory(adminintf_ptr inf, const std::wstring& cmd);
bool column_factory(std::wstring& cmd);


    
class main_executor{
public:
    main_executor(const stdstr_vect& arg) : init_(false) {}
    
    main_executor(const fspath& path) : init_(false) {
        tagsbase_ptr kintf = dvnci::krnl::factory::build(path,  NS_ADMIN_SERVICE);
        if (!kintf) return;
        intf = dvnci::admin::factory::build(kintf);
        if (!intf) return;
        init_=true;}
    
    virtual ~main_executor(){}
    
    bool execute(const std::wstring& cmd){
        if (intf) {
           command_executor_ptr ex = command_factory(intf, cmd);
           if (ex) {
               ex->execute();
               return true;}
           else{
               std::wcout << L": No find cmd: " << cmd << std::endl;}
           return true;}
        std::wcout << L"No parse cmd :" << cmd << std::endl;
        return false;}
    
    bool inited() const {
        return init_;}
    
protected:
    bool          init_;
    adminintf_ptr intf;};
    
typedef boost::shared_ptr<main_executor> main_executor_ptr;  


/*
 select tag where pid=(@parentid|@parenname)
 */

class select_command_executor : public basic_command_executor{
public:
    select_command_executor(adminintf_ptr inf, const std::wstring& arg) : basic_command_executor(inf, arg) {}
protected:
    virtual void parse(){
    
    };
    
    virtual void execute_impl(){
       iteminfo_map tmp;
       if (!intf->select_entities(NT_GROUP,tmp,0)){
           std::wcout << L"count : " << tmp.size() << std::endl;
           for (iteminfo_map::const_iterator it=tmp.begin();it!=tmp.end();++it){
               std::wcout << L"Tag : id=" << it->first << L" name="<<  dvnci::trim_copy(utf8_to_wstr(it->second.name())) << std::endl;}}
       else{
          std::wcout << L"Error : " << args << std::endl;}};};
       
       
    
    
}

#endif	/* ADMINCONSOL_H */

