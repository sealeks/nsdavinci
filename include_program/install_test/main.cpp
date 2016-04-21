/* 
 * File:   main.cpp
 * Author: Serg
 *
 * Created on 19 РїС—Р…РїС—Р…РїС—Р…РїС—Р…РїС—Р…РїС—Р…РїС—Р… 2010 РїС—Р…., 12:18
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
#include <kernel/serviceapp.h>

#ifdef _DVN_WIN_
#include <windows.h>

HANDLE getdvnConsol(){
    static HANDLE chndl=GetStdHandle(STD_OUTPUT_HANDLE);
    return chndl;
}

void setdvnDefault(){
    SetConsoleTextAttribute(getdvnConsol(), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void setdvnError(){
    SetConsoleTextAttribute(getdvnConsol(), FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void setdvnValid(){
    SetConsoleTextAttribute(getdvnConsol(), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void setdvnInvalid(){
    SetConsoleTextAttribute(getdvnConsol(), FOREGROUND_GREEN | FOREGROUND_BLUE);
}

#else


void setdvnDefault(){
}

void setdvnError(){
}

void setdvnValid(){
}

void setdvnInvalid(){
}

#endif

using namespace dvnci;
using namespace std;
using namespace boost::interprocess;

std::string  dvnci::DVNCI_SERVICE_NAME="";
dvnci::appidtype dvnci::DVNCI_SERVICE_APPID=0;
dvnci::executable_ptr         dvnci::mainserv;


dvnci::tagsbase_ptr intf;
fspath              basepath;





std::ostream & operator<<(std::ostream& os, const dt_val_map& ns){
       for (dt_val_map::const_iterator it = ns.begin(); it!=ns.end(); ++it){
            os << "tm =" << it->first  << " value="  << it->second   << std::endl;}
       return os;}

#if defined(_DVN_LIN_)
    const fspath TESTDEMON_DIR       = "/home/sealeks/";
#endif

namespace dvnci {  
    
    
    class expression_listener{
    public:
        virtual void event(const short_value& val)=0;};
        
    
    template<typename INTF, typename LISTENER = expression_listener>
    
    class gui_executor : public executable {
            
    public:       
        
       typedef INTF                                                            interface_type;
       typedef membase_sync_ptr_tmpl<interface_type>                           interface_type_ptr;
       
       typedef LISTENER                                                        listener_type;      
       typedef boost::shared_ptr<listener_type>                                listener_type_ptr;
       
       typedef dvnci::expr::expression_templ<INTF>                             expression_type;
       typedef boost::shared_ptr<expression_type>                              expression_type_ptr;
       

       struct listener_less : 
            public binary_function<listener_type_ptr, listener_type_ptr , bool>{
            bool operator()(const listener_type_ptr& ls, 
                            const listener_type_ptr& rs) const
              { return ((intptr_t)ls.get()) < ((intptr_t)rs.get()); }};
      
       typedef std::set<listener_type_ptr , listener_less >                    listener_set;
       
       typedef std::pair< short_value , listener_set>                          shv_listset_pair; 
       
       struct expression_less : 
            public binary_function<expression_type_ptr, expression_type_ptr , bool>{
            bool operator()(const expression_type_ptr& ls, 
                            const expression_type_ptr& rs) const
              { return ls->expressionstr() < rs->expressionstr(); }};       
       
       typedef std::pair<expression_type_ptr, shv_listset_pair>                expr_shvlsn_pair;
       typedef std::map<expression_type_ptr, shv_listset_pair, 
                        expression_less,
                        std::allocator<expr_shvlsn_pair > >                    expr_shvlsn_map;
       typedef typename expr_shvlsn_map::iterator                              expr_shvlsn_iterator;
       typedef typename expr_shvlsn_map::const_iterator                        expr_shvlsn_const_iterator;
       
       

        
        gui_executor(interface_type_ptr inf) : executable() , intf(inf) {};
        
        virtual ~gui_executor(){};
        
        virtual bool operator()() {
            return true;}
        
        bool regist(const std::string& expr, listener_type_ptr listener){
            expression_type_ptr  extmp = expression_type_ptr( new expression_type(expr, intf));
            expr_shvlsn_iterator it = expressions.find(extmp);
            if (it==expressions.end()){
                shv_listset_pair shvlst = std::make_pair(short_value(), listener_set());
                expr_shvlsn_pair expr_shvlst = std::make_pair(extmp, shvlst);
                expressions.insert(expr_shvlst);
                it = expressions.find(extmp);
                if (it==expressions.end())
                    return false;}
            it->second.second.insert(listener);
            return false;}
        
        
    protected:
        
        virtual bool    initialize() {
            return intf;}
        
        virtual  bool   uninitialize() {
            return true;}    
        
       interface_type_ptr   intf;
       expr_shvlsn_map      expressions;
    };
    
    
    class select_filterclass {
    public:
        

        select_filterclass(const std::string& filter_) {
            criteria_ = filter_;
            readcriterias();}

        virtual ~select_filterclass() {};

        operator std::string();

        
        
        indx_set indx_criteria(const std::string& name) const {
            return filterkeymap.find(name) != filterkeymap.end() ? 
                filterkeymap.find(name)->second : indx_set();}
        
        void indx_criteria(const std::string& name, const indx_set& val);
        
        bool indx_included(const std::string& name, indx val) const;
        
        void indx_add_criteria(const std::string& name, const indx val);
        
        void indx_remove_criteria(const std::string& name, const indx val);
        
        void indx_clear_criteria(const std::string& name) {
            if (filterkeymap.find(name) != filterkeymap.end()) 
                filterkeymap.erase(filterkeymap.find(name));}
         
 
        
        std::string criteria(const std::string& name) const {
            return (filtermap.find(name) != filtermap.end()) ?
                filtermap.find(name)->second : "";}
        
        void criteria(const std::string& name, const std::string& val);

        bool included(const std::string& name, const std::string& val) const;
        
        void clear_criteria();
        


        bool isEnable() {
            return ((filtermap.size() > 0) || (filterkeymap.size() > 0));}
        


    private:

 
        void readcriteria(const std::string name);
        void readidxcriteria(const std::string name);
        void readcriterias();
        std::string findcriteria(std::string name) const;
        void getkeyswithstring(const std::string str_, indx_set& set_) const;
        void setkeyswithstring(std::string& str_, const indx_set& set_);

        filtered_map            filtermap;
        mutable std::string     criteria_;
        filteredkey_map         filterkeymap;};   
    
 
    select_filterclass::operator std::string() {
        criteria_ = "";
        filtered_map::const_iterator it = filtermap.begin();
        while (it != filtermap.end()) {
            criteria_ = criteria_ + it->first + "=\"" + it->second + "\"\n";
            ++it;}
        filteredkey_map::const_iterator it2 = filterkeymap.begin();
        while (it2 != filterkeymap.end()) {
            std::string tmpstr;
            setkeyswithstring(tmpstr, it2->second);
            if (tmpstr != "")
                criteria_ = criteria_ + it2->first + "=\"" + tmpstr + "\"\n";
            ++it2;}
        return criteria_;}

    void select_filterclass::criteria(const string& name, const string& val) {
        if (filtermap.find(name) != filtermap.end()) filtermap.erase(filtermap.find(name));
        if (val != "") filtermap.insert(filtered_pair(name, val));}

    void select_filterclass::indx_add_criteria(const string& name, const indx val) {
        indx_set tmp = indx_criteria(name);
        indx_set newtmp;
        if (!tmp.empty()) {
            newtmp.insert(tmp.begin(), tmp.end());}
        newtmp.insert(val);
        indx_criteria(name, newtmp);}

    void select_filterclass::indx_remove_criteria(const string& name, const indx val) {
        indx_set tmp = indx_criteria(name);
        indx_set newtmp;
        if (!tmp.empty()) {
            newtmp.insert(tmp.begin(), tmp.end());}
        if (newtmp.find(val) != newtmp.end()) newtmp.erase(val);
        indx_criteria(name, newtmp);}

    bool select_filterclass::included(const std::string& name, const std::string& val) const  {
        if (filtermap.find(name) == filtermap.end()) return true;
        string tmpcriteria = findcriteria(name);
        boost::trim(tmpcriteria);
        if (tmpcriteria == "") return true;
        boost::regex xfnTemplete(tmpcriteria);
        std::string::const_iterator xItStart = val.begin();
        std::string::const_iterator xItEnd = val.end();
        boost::smatch xresults;
        return boost::regex_search(xItStart, xItEnd, xresults, xfnTemplete);}

    bool select_filterclass::indx_included(const string& name, indx val) const {
        if (filterkeymap.find(name) == filterkeymap.end()) 
            return true;
        string tmpcriteria = findcriteria(name);
        boost::trim(tmpcriteria);
        if (tmpcriteria == "") return true;
        indx_set set_;
        getkeyswithstring(tmpcriteria, set_);
        return (set_.find(val) != set_.end());}

    void select_filterclass::clear_criteria() {
        criteria_ = "";
        filtermap.clear();
        filterkeymap.clear();}

    void select_filterclass::indx_criteria(const string& name, const indx_set& val) {
        indx_clear_criteria(name);
        if (!val.empty()) filterkeymap.insert(filteredkey_pair(name, val));}

    void select_filterclass::readcriteria(const string name) {
        string crittmp = findcriteria(name);
        if (filtermap.find(name) != filtermap.end()) filtermap.erase(filtermap.find(name));
        if (crittmp != "") filtermap.insert(filtered_pair(name, crittmp));}

    void select_filterclass::readidxcriteria(const string name) {
        string crittmp = findcriteria(name);

        if (filterkeymap.find(name) != filterkeymap.end()) filterkeymap.erase(filterkeymap.find(name));
        if (crittmp != "") {
            indx_set tmpset;
            getkeyswithstring(crittmp, tmpset);
            filterkeymap.insert(filteredkey_pair(name, tmpset));}}

    void select_filterclass::readcriterias() {
        readcriteria(NAME_CRITERIA);
        readcriteria(COMMENT_CRITERIA);
        readcriteria(BIND_CRITERIA);
        readidxcriteria(GROUP_CRITERIA);
        readidxcriteria(TYPEGROUP_CRITERIA);
        readidxcriteria(TYPERT_CRITERIA);}

    std::string select_filterclass::findcriteria(string name) const {
        boost::regex xfnTemplete(name + "=\"[*A-Za-z_$0-9, ]+\"\n");

        boost::smatch xresults;
        std::string::const_iterator xItStart = criteria_.begin();
        std::string::const_iterator xItEnd = criteria_.end();
        if (boost::regex_search(xItStart, xItEnd, xresults, xfnTemplete)) {
            boost::smatch::iterator it = xresults.begin();
            if (it != xresults.end()) {
                string tmpresult = *it;
                boost::replace_first(tmpresult, name + "=\"", "");
                boost::replace_last(tmpresult, "\"\n", "");
                boost::algorithm::trim(tmpresult);
                return tmpresult;}}
        return "";}

    void select_filterclass::getkeyswithstring(const std::string str_, indx_set& set_) const {
        set_.clear();
        boost::char_separator<char> sep(",");
        chartokenizer tokens(str_, sep);
        for (chartokenizer::iterator tok_iter = tokens.begin();
                tok_iter != tokens.end(); ++tok_iter) {
            std::string tmpstr = *tok_iter;
            boost::trim(tmpstr);
            indx tmp;
            if (str_to(tmpstr, tmp)) {
                set_.insert(tmp);}}}

    void select_filterclass::setkeyswithstring(std::string& str_, const indx_set& set_) {
        indx_set::const_iterator it = set_.begin();
        str_ = "";
        for (indx_set::const_iterator it = set_.begin();
                it != set_.end(); ++it) {
            std::string tmpstr=to_str(*it);
                if (str_ == "") str_ += tmpstr;
                else {
                    str_ = str_ + ", " + tmpstr;}}}    
    
}    

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
const std::string DELETETAG_OPERATION_STR = "deletetag ";

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
const int DELETETAG_OPERATION = 16;

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
   if (operation(vl,DELETETAG_OPERATION_STR ,DELETETAG_OPERATION)==DELETETAG_OPERATION) return DELETETAG_OPERATION; 
   std::cout << "_____________________________________________"  << std::endl;
   std::cout  << "No parse line " << vl  << " !" << std::endl;
   std::cout << "_____________________________________________"  << std::endl;
   return DEFAULT_OPERATION;}


int main(int argc, char** argv) 
{
  setdvnDefault();
  appargumentparser(argc, argv);
  //typedef dvnci::expr::expression_calculator       expression;
  typedef dvnci::expr::expression_templ<tagsbase >   expression;
  typedef gui_executor<tagsbase >                    test_gui_executor;

  std::string quit_in;
  std::wstring wquit_in;
  basepath=dvnci::getlocalbasepath();
  intf = dvnci::krnl::factory::build(basepath);



test_immi_struct();
  while (true){
      std::getline(std::wcin,wquit_in);
      quit_in = wstr_to_utf8(wquit_in);
      try{
      switch (getoperate(quit_in)) {
          case EXIT_OPERATION : return 0;
          case HISTORY_OPERATION:{
              indx ind = str_to<indx>(quit_in,npos);
              dt_val_map tmp;
              if (ind!=npos)
                  intf->select_trendbuff(ind, tmp, incminute(now(),-10), nill_time);
              else
                 intf->select_trendbuff(quit_in, tmp, incminute(now(),-10), nill_time);
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
              test_gui_executor expr(intf);
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
                  double tst3 = 0;
                  tst3 = tan(tst3);
                  std::cout << "NO generate error  tan pi/2 vl="  << tst3 << std::endl;
                  }
              catch(std::exception& e){
                  std::cout << e.what()  << std::endl;}
              break;}
          case EXPR_OPERATION:{
              wquit_in=wquit_in.substr(4);
              expression expr(wquit_in, intf);
              //expression expr(quit_in);
              std::cout << "expr "  << expr.expressionstr() << std::endl;

              expr.active(true);
              short_value shv =expr.value();
              if (shv.error()){
                  setdvnError();
              } else{
                  if (shv.valid()!=0){
                      setdvnValid();
                  }
                  else {
                    setdvnInvalid();
                  }}
          
              std::wcout << "value " << shv.value<std::wstring>() << std::endl;
              if (expr.error()){
              std::cout << "error " << shv.error() << std::endl;
              }
              setdvnDefault();
              break;}

          case DEMONINS_OPERATION:{
              std::cout << "DEMONINS_OPERATION "  <<  std::endl;
              std::cout << demon_entry_factory::createstorige(FULL_EXEC_DIR()) << std::endl;
          break;}     
          
          case DEMONADD_OPERATION :{
              std::cout << "DEMONADD_OPERATION "  <<  std::endl;
               appidtype app = str_to<appidtype>(quit_in,0);
               if (!app){
                   std::cout << "APPID = 0 "  <<  std::endl;
                   break;}
               servicemanager_ptr dms = demon_entry_factory::build(FULL_EXEC_DIR());
               if (!dms){
                   std::cout << "NO CREATE MAP "  <<  std::endl;
                   break;}
               dms->install_demon(NS_NET_SERVICE, NS_NET_SERVICE_NAME);
               std::cout <<   (*dms);
          break;}
          
          case DEMONREM_OPERATION :{
              std::cout << "DEMONREM_OPERATION "  <<  std::endl;
               appidtype app = str_to<appidtype>(quit_in,0);
               if (!app){
                   std::cout << "APPID = 0 "  <<  std::endl;
                   break;}
               servicemanager_ptr dms = demon_entry_factory::build(FULL_EXEC_DIR());
               if (!dms){
                   std::cout << "NO CREATE MAP "  <<  std::endl;
                   break;}
               dms->uninstall_demon(app);
               std::cout <<   (*dms);
          break;}
         case DEMONLST_OPERATION :{
              std::cout << "DEMONLST_OPERATION "  <<  std::endl;

              servicemanager_ptr dms = demon_entry_factory::build(FULL_EXEC_DIR());
              if (!dms){
                   std::cout << "NO CREATE MAP "  <<  std::endl;
                   break;}
              std::cout << "TAB CNT " << dms->count() <<  std::endl; 
               
              std::cout <<   (*dms);
          break;}
         
          case DELETETAG_OPERATION :{
              indx ind = str_to<indx>(quit_in,npos);
              if (ind!=npos) {
                  if (intf->delete_tag(ind)>0)
                     std::cout << "Succses delete "  <<  std::endl; 
              }
          }
              
         
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

