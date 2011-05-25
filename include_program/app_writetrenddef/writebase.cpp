//
// Copyright (C) 2004-2008 Maciej Sobczak, Stephen Hutton
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <kernel/constdef.h>
#include <kernel/utils.h>
#include <kernel/factory.h>

#include <dbaccess/dbconnectionfactory.h>

dvnci::tagsbase_ptr intf;

using namespace std;
using namespace dvnci;
using namespace dvnci::database;


int main(int argc, char** argv)
{
   fspath basepath=dvnci::getlocalbasepath();
   intf= dvnci::krnl::factory::build(dvnci::getlocalbasepath(), 10000, 0);

   std::string con_str=intf->conf_property(NS_CNFG_DBCONSTR);
   num32 provider_db=intf->conf_intproperty(NS_CNFG_DBMANAGER);

   cout << " connected by "<< con_str << endl;

   dbdriver_ptr testdrv=bdconnectionfactory::build(provider_db,con_str);
   if (testdrv){
   testdrv->connect();
   if (testdrv->isconnected()){
       cout << "is connected" << endl;

    /* datetime dt = now();
     datetime dtout = incminute(dt, 1);
     num64 r=0;
     num64 cnt=0;
     vect_indx_dt_val tmpvect;

     while (now()<dtout){
         num64 dt1 = castnum64_from_datetime(now());
         indx u = static_cast<indx>(rand() % 100);
         double uv = ((rand() % 100) < 10) ? NULL_DOUBLE: static_cast<indx>((rand() % 1000)*100.0);
         if (tmpvect.size()<100){
            tmpvect.push_back(indx_dt_val(u,dt_val_pair(now(),uv)));
         }
         else{
           testdrv->insert_trend(tmpvect);
           tmpvect.clear();}
         r += (castnum64_from_datetime(now())-dt1);
         cnt++;}*/

     //std::cout << "count=" << cnt << " interv=" << r/cnt << std::endl;
     /* datetime strt = incminute(now(), -2);
      normalizeperiod(strt, MINUTE_TM);
      datetime stpt = incminute(strt);
      double result = 0;

      testdrv->select_trend_statistic(14,strt,stpt,REPORT_STATISTIC_AVER,result);
      std::cout << " fr " << strt << " in " << castnum64_from_datetime(strt) << " to " << stpt << "result=" << result << std::endl;*/

      // std::cout << testdrv->insert_trendef<dvnci::tagsbase_ptr>(intf) << std::endl;
       datetime tm = now();
       tm=incmonth(tm,-2);
       datetime tmr = now();
       normalizeperiod(tm,REPORTTYPE_MIN);
       boost::xtime xt;

       for (int i=0;i<1000;i++){
           boost::xtime_get(&xt, boost::TIME_UTC);
           xt.sec += 1;
           tm = now();
           tm=incmonth(tm,-2);
           std::cout << tm <<" " <<testdrv->insert_report(1, REPORTTYPE_MIN, 0 , tm)   << std::endl;
           boost::thread::sleep(xt);}
       

   }}

   return EXIT_FAILURE;
}
