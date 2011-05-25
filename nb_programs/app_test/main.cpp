/* 
 * File:   main.cpp
 * Author: Serg Alexeev sealeks@mail.ru Alexeev sealeks@mail.ru
 *
 * Created on 22 Февраль 2010 г., 0:30
 */

#include <stdlib.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>
#include "kernel/constdef.h"
#include "kernel/memfile.h"
#include "kernel/timeutils.h"





using namespace dvnci;
using namespace std;
using namespace dvnci::krnl;


double timeval(){
    dvnci::datetime tm=dvnci::now();
    dvnci::normalizeperiod(tm,DAY_TM);
    return (1.0*secondsbetween(tm,dvnci::now())) /60 * 2  * 3.1415; }


struct thread_log
{

    typedef boost::shared_ptr<boost::mutex>    mutex_ptr;

    thread_log () {
       mutex = mutex_ptr(new boost::mutex());}

    thread_log (const thread_log& val){
        intf=val.intf;
        mutex=val.mutex;}

    dvnci::krnl::tagsbase_ptr intf;
    mutex_ptr mutex;

    bool init(){
       if(intf) return true;
       try{
         intf= dvnci::krnl::buildinterface(dvnci::getlocalbasepath(), 10000);
         OUTSTR_DVNCI(SUCCESSFULL INIT);}
       catch(...){
         OUTSTR_DVNCI(INITINFERROR);}
       return (intf);}

    void operator()()
    {
        cout << "in operator ()" << endl;
        while (true){

        boost::xtime xt;
        boost::xtime_get(&xt, boost::TIME_UTC);
        xt.sec += 3;
        if (init()){
        {
           cout << "in interface ()" << endl;
           boost::mutex::scoped_lock lock(*mutex);
           for (int i=0;i<intf->count();i++)
              if (intf->exists(i)){
                if (((intf->groupind(i)==0) || (intf->groupind(i)==12))&& (!intf->isreporttype(i)) && (intf->groups()->appId(intf->groupind(i))!=NS_GROUP_SYSTEMCOUNT) &&
                        (intf->groups()->appId(intf->groupind(i))!=NS_GROUP_SYSTEMVAR) &&
                        (intf->groups()->appId(intf->groupind(i))!=NS_GROUP_SYSTEMCOMMAND) &&
                        (intf->groups()->appId(intf->groupind(i))!=NS_GROUP_SYSTEM)){
                  if (intf->type(i)<=0xC){
                      double tmpMaxEu=intf->maxEU<double>(i);
                      double tmpMinEu=intf->minEU<double>(i);
                      /*double tmpval=intf->value_<double>(i);
                      double tmpEu=tmpval+(tmpMaxEu-tmpMinEu) * ((rand() % 100 - 50)*1.0 / 5000.0);
                      if (tmpMinEu>tmpEu) tmpEu=tmpMinEu;
                      if (tmpMaxEu<tmpEu) tmpEu=tmpMaxEu;*/
                      double tmpEu=timeval() / ((i %  5) *20 +4);
                      tmpEu=tmpMinEu+(sin(tmpEu)+1)/2*(tmpMaxEu-tmpMinEu);
                      intf->setVal(i,tmpEu,100);
                  }}}}}
        boost::thread::sleep(xt);}}



};

int main(int argc, char** argv) {
   
    boost::thread_group threads;
    for (int i=0; i < 1; i++){
    thread_log log1;
    threads.create_thread(log1);}
    threads.join_all();
 
    return (EXIT_SUCCESS);}

