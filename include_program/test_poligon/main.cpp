/* 
 * File:   main.cpp
 * Author: Serg
 *
 * Created on 19 ������� 2010 �., 12:18
 */

//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////





#include <exception>


#include <kernel/constdef.h>
#include <kernel/factory.h>
#include <kernel/utils.h>
#include <kernel/memfile.h>
#include <kernel/expression.h>
#include <kernel/nix_demon_templ.h>

using namespace dvnci;
using namespace std;
using namespace boost::interprocess;


dvnci::tagsbase_ptr intf;
fspath              basepath;

std::ostream & operator<<(std::ostream& os, const dt_val_map& ns){
       for (dt_val_map::const_iterator it = ns.begin(); it!=ns.end(); ++it){
            os << "tm =" << it->first  << " value="  << it->second   << std::endl;}
       return os;}

#if defined(_DVN_LIN_)
    const fspath TESTDEMON_DIR       = "/home/sealeks/";
#endif

const std::string EXIT_OPERATION_STR = "quit";
const std::string HISTORY_OPERATION_STR = "history ";
const std::string REPORT_OPERATION_STR = "report ";
const std::string TAGID_OPERATION_STR = "tagid ";
const std::string TAGVAL_OPERATION_STR = "tagval ";
const std::string CREATETAG_OPERATION_STR = "createtag ";
const std::string CREATEGROUP_OPERATION_STR = "creategroup ";
const std::string VIEWINDEX_OPERATION_STR = "viewindex";
const std::string DUPLICATEGROUP_OPERATION_STR = "dupgroup ";
const std::string EXPR_OPERATION_STR = "expr ";
const std::string MATH_OPERATION_STR = "math";
const std::string DEMONADD_OPERATION_STR = "demonadd ";
const std::string DEMONREM_OPERATION_STR = "demonrem ";
const std::string DEMONLST_OPERATION_STR = "demonlst";
const std::string DEMONINS_OPERATION_STR = "demonins";

const int DEFAULT_OPERATION = 0;
const int EXIT_OPERATION = 1;
const int HISTORY_OPERATION = 2;
const int TAGID_OPERATION = 3;
const int CREATETAG_OPERATION = 4;
const int CREATEGROUP_OPERATION= 5;
const int VIEWINDEX_OPERATION = 6;
const int TAGVAL_OPERATION = 7;
const int DUPLICATEGROUP_OPERATION = 8;
const int EXPR_OPERATION = 9;
const int REPORT_OPERATION = 10;
const int MATH_OPERATION = 11;
const int DEMONADD_OPERATION = 12;
const int DEMONREM_OPERATION = 13;
const int DEMONLST_OPERATION = 14;
const int DEMONINS_OPERATION = 15;

int operation(std::string& vl, const std::string& oper, int operid){
    dvnci::lower_copy(vl);
    std::string::size_type pos=vl.find(oper);
    if (pos!=std::string::npos) {
       vl= dvnci::trim_copy((pos + oper.size()) < vl.size() ? trim_copy(vl.substr(pos+oper.size())) : "");
       std::cout << "_____________________________________________"  << std::endl;
       std::cout  << "execute command: " << oper  <<  " arguments: " << vl << std::endl;
       std::cout  <<  std::endl;
       return  operid;}
    return 0;}

int getoperate(std::string& vl){
   if (operation(vl,EXIT_OPERATION_STR,EXIT_OPERATION)==EXIT_OPERATION) return EXIT_OPERATION;
   if (operation(vl,HISTORY_OPERATION_STR,HISTORY_OPERATION)==HISTORY_OPERATION) return HISTORY_OPERATION;
   if (operation(vl,TAGID_OPERATION_STR,TAGID_OPERATION)==TAGID_OPERATION) return TAGID_OPERATION;
   if (operation(vl,TAGVAL_OPERATION_STR,TAGVAL_OPERATION)==TAGVAL_OPERATION) return TAGVAL_OPERATION;
   if (operation(vl,CREATETAG_OPERATION_STR,CREATETAG_OPERATION)==CREATETAG_OPERATION) return CREATETAG_OPERATION;
   if (operation(vl,CREATEGROUP_OPERATION_STR,CREATEGROUP_OPERATION)==CREATEGROUP_OPERATION) return CREATEGROUP_OPERATION;
   if (operation(vl,VIEWINDEX_OPERATION_STR,VIEWINDEX_OPERATION)==VIEWINDEX_OPERATION) return VIEWINDEX_OPERATION;
   if (operation(vl,DUPLICATEGROUP_OPERATION_STR,DUPLICATEGROUP_OPERATION)==DUPLICATEGROUP_OPERATION) return DUPLICATEGROUP_OPERATION;
   if (operation(vl,EXPR_OPERATION_STR,EXPR_OPERATION)==EXPR_OPERATION) return EXPR_OPERATION;
   if (operation(vl,REPORT_OPERATION_STR,REPORT_OPERATION)==REPORT_OPERATION) return REPORT_OPERATION;
   if (operation(vl,MATH_OPERATION_STR,MATH_OPERATION)==MATH_OPERATION) return MATH_OPERATION;
   if (operation(vl,DEMONADD_OPERATION_STR ,DEMONADD_OPERATION)==DEMONADD_OPERATION) return DEMONADD_OPERATION;
   if (operation(vl,DEMONREM_OPERATION_STR ,DEMONREM_OPERATION)==DEMONREM_OPERATION) return DEMONREM_OPERATION;
   if (operation(vl,DEMONLST_OPERATION_STR ,DEMONLST_OPERATION)==DEMONLST_OPERATION) return DEMONLST_OPERATION;
   if (operation(vl,DEMONINS_OPERATION_STR ,DEMONINS_OPERATION)==DEMONINS_OPERATION) return DEMONINS_OPERATION; 
   std::cout << "_____________________________________________"  << std::endl;
   std::cout  << "No parse line " << vl  << " !" << std::endl;
   std::cout << "_____________________________________________"  << std::endl;
   return DEFAULT_OPERATION;}


int main() 
{

  //typedef dvnci::expr::expression_calculator       expression;
  typedef dvnci::expr::expression_templ<tagsbase >   expression;

  std::string quit_in;
  basepath=dvnci::getlocalbasepath();
  intf = dvnci::krnl::factory::build(basepath);



test_immi_struct();
  while (true){
      std::getline(std::cin,quit_in);
      try{
      switch (getoperate(quit_in)) {
          case EXIT_OPERATION : return 0;
          case HISTORY_OPERATION:{
              indx ind = str_to<indx>(quit_in,npos);
              dt_val_map tmp;
              if (ind!=npos)
                  intf->select_trendbuff(ind, tmp, nill_time, nill_time,15.0);
              else
                 intf->select_trendbuff(quit_in, tmp, nill_time, nill_time,15.0);
              std::cout << tmp;
              break;}
          case REPORT_OPERATION:{
              indx ind = str_to<indx>(quit_in,npos);
              dt_val_map tmp;
              if (ind!=npos)
                  intf->select_reportbuff(ind, tmp);
              else{
                 std::cout << "buffervalid -500 -400 =" << intf->select_reportbuff(quit_in, tmp, incminute(now(),-500) ,incminute(now(),-400))  << std::endl;
                 std::cout << "buffervalid -500 - 4=" << intf->select_reportbuff(quit_in, tmp, incminute(now(),-500) ,incminute(now(),-4))  << std::endl;
                 std::cout << "buffervalid 400 500=" << intf->select_reportbuff(quit_in, tmp, incminute(now(),400) ,incminute(now(),500))  << std::endl;
                 std::cout << "buffervalid 400 300=" << intf->select_reportbuff(quit_in, tmp, incminute(now(),400) ,incminute(now(),300))  << std::endl;
                 std::cout << "buffervalid -500 -2 =" << intf->select_reportbuff(quit_in, tmp, incminute(now(),-500) ,incminute(now(),-2))  << std::endl;
                 std::cout << "buffervalid -300 -2=" << intf->select_reportbuff(quit_in, tmp, incminute(now(),-300) ,incminute(now(),-2))  << std::endl;
                 std::cout << "buffervalid -30 -2 =" << intf->select_reportbuff(quit_in, tmp, incminute(now(),-30) ,incminute(now(),-2))  << std::endl;
                 std::cout << "buffervalid -20 -2=" << intf->select_reportbuff(quit_in, tmp, incminute(now(),-20) ,incminute(now(),-2))  << std::endl;
                 std::cout << "buffervalid -15 -2 =" << intf->select_reportbuff(quit_in, tmp, incminute(now(),-15) ,incminute(now(),-2))  << std::endl;
                 std::cout << "buffervalid -10 -2=" << intf->select_reportbuff(quit_in, tmp, incminute(now(),-10) ,incminute(now(),-2))  << std::endl;
                 std::cout << "buffervalid -5 -2=" << intf->select_reportbuff(quit_in, tmp, incminute(now(),-5) ,incminute(now(),-2))  << std::endl;
                 dt_val_pair tmppr;
                 datetime testfind =incminute(now(),-3);
                 normalizereporttime(testfind, REPORTTYPE_MIN);
                 std::cout << "testfindreport tm=" << testfind  << std::endl;
                 if (intf->select_reportval_by_time(intf(quit_in),testfind,tmppr)) {
                     std::cout << "finded tm=" << tmppr.first << std::endl;
                     std::cout << "finded vl=" << tmppr.second << std::endl;}
                 else{
                     std::cout << "not finded" << std::endl;}
                 intf->select_reportbuff(quit_in, tmp);
                 }
              std::cout << tmp;
              break;}
          case TAGID_OPERATION:{
             std::cout << "tagname=" << quit_in  << " index=" << intf->operator ()(quit_in)   << std::endl;
             boost::mutex mtxtest;
             THD_COND_EXCLUSIVE_LOCK(true, mtxtest)
             std::cout << "first lock "  << std::endl;
             THD_COND_EXCLUSIVE_LOCK1(true, mtxtest)
             std::cout << "second lock " << std::endl;        
             break;}
          case TAGVAL_OPERATION:{
             indx ind = intf->operator ()(quit_in);
             if (ind==-1) {
                 std::cout << "tagname " << quit_in << " not found!"  << std::endl;}
             else{
                std::cout << "tagname " << intf->name(ind) << std::endl;
                std::cout << "value =" << intf->value<std::string>(ind) << std::endl;
                std::cout << "valid =" << intf->valid(ind) << std::endl;}
             break;}
          case CREATETAG_OPERATION:{
             std::string::size_type pos=quit_in.find("::");
             if (pos==std::string::npos) {
                std::cout << "can`t creat tag with name =" <<  quit_in  << std::endl;
                break;}
             indx ind = intf->groups()->operator ()(quit_in.substr(0,pos));
             if (ind == npos){
                std::cout << "can`t creat tag. group no exist name = " <<  quit_in.substr(0,pos)  << std::endl;
                break;}
             ind = intf->insert_tag(quit_in.substr(pos+2),ind);
             std::cout << "susccessfull create tag name = " <<  intf->name(ind)  << " id=" << ind << std::endl;
             break;}
          case CREATEGROUP_OPERATION:{
             indx ind = intf->insert_group(quit_in);
             std::cout << "susccessfull create group name = " <<  intf->groups()->name(ind)  << " id=" << ind << std::endl;
             break;}
          case DUPLICATEGROUP_OPERATION:{
             std::string tnm = "";
             std::string nnm = "";
             split_2str(quit_in, " ",tnm, nnm);
             indx ind = intf->groups()->operator ()(tnm);
             if (ind == npos){
                std::cout << "can`t duplicate. group no exist name = " <<  tnm  << std::endl;
                break;}
             ind = intf->duplicate_group(ind, nnm);
             std::cout << "susccessfull duplicate group name = " <<  intf->groups()->name(ind)  << " id=" << ind << std::endl;
             break;}
          case VIEWINDEX_OPERATION:{
              //intf->test_list();;
              break;}
          case MATH_OPERATION:{
              try{
                  double gg = 0;
                  double dbl = -1 /gg;
                  std::cout << "NO generate error  /0 vl="  << dbl << std::endl;
                  double tst1 = -1;
                  tst1 = sqrt(tst1);
                  std::cout << "NO generate error  sqrt neg vl="  << tst1 << std::endl;
                  double tst2 = 2;
                  tst2 = acos(tst2);
                  std::cout << "NO generate error  acos >1 vl="  << tst2 << std::endl;
                  double tst3 = M_PI_2;
                  tst3 = tan(tst3);
                  std::cout << "NO generate error  tan pi/2 vl="  << tst3 << std::endl;
                  }
              catch(std::exception& e){
                  std::cout << e.what()  << std::endl;}
              break;}
          case EXPR_OPERATION:{
              expression expr(quit_in, intf);
              //expression expr(quit_in);
              std::cout << "exprtest "  <<  std::endl;
              std::cout << "expr "  << expr.expressionstr() << std::endl;
              expr.active(true);
              std::cout << "value " << expr << std::endl;
              std::cout << "error " << expr.error() << std::endl;
              break;}
          
#if defined(_DVN_LIN_)
          case DEMONINS_OPERATION:{
              std::cout << "DEMONINS_OPERATION "  <<  std::endl;
              std::cout << demon_entry_factory::createstorige(TESTDEMON_DIR) << std::endl;
          break;}     
          
          case DEMONADD_OPERATION :{
              std::cout << "DEMONADD_OPERATION "  <<  std::endl;
               appidtype app = str_to<appidtype>(quit_in,0);
               if (!app){
                   std::cout << "APPID = 0 "  <<  std::endl;
                   break;}
               demon_entry_ptr dms = demon_entry_factory::build(TESTDEMON_DIR);
               if (!dms){
                   std::cout << "NO CREATE MAP "  <<  std::endl;
                   break;}
               dms->install_demon(app, "test");
               std::cout <<   (*dms);
          break;}
          
          case DEMONREM_OPERATION :{
              std::cout << "DEMONREM_OPERATION "  <<  std::endl;
               appidtype app = str_to<appidtype>(quit_in,0);
               if (!app){
                   std::cout << "APPID = 0 "  <<  std::endl;
                   break;}
               demon_entry_ptr dms = demon_entry_factory::build(TESTDEMON_DIR);
               if (!dms){
                   std::cout << "NO CREATE MAP "  <<  std::endl;
                   break;}
               dms->uninstall_demon(app);
               std::cout <<   (*dms);
          break;}
         case DEMONLST_OPERATION :{
              std::cout << "DEMONLST_OPERATION "  <<  std::endl;

              demon_entry_ptr dms = demon_entry_factory::build(TESTDEMON_DIR);
              if (!dms){
                   std::cout << "NO CREATE MAP "  <<  std::endl;
                   break;}
              std::cout << "TAB CNT " << dms->count() <<  std::endl; 
               
              std::cout <<   (*dms);
          break;}
          
#endif          
          default:{}}
      std::cout << "_____________________________________________"  << std::endl;}
      catch (dvnci::dvncierror& er){
          std::cout << "dvnci::error:" << std::endl;
          std::cout << er;
          std::cout << "_____________________________________________"  << std::endl;}
      catch (...){
	  std::cout << "Undef error" << std::endl;
          std::cout << "_____________________________________________"  << std::endl;}
	  quit_in="";}}

