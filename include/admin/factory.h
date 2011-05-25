/* 
 * File:   bulder_nsAdminInterface.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 8 Январь 2010 г., 23:23
 */

#ifndef _ADMININTF_BUILDER_NSADMININTERFACE_H
#define	_ADMININTF_BUILDER_NSADMININTERFACE_H

#include <kernel/constdef.h>
#include <kernel/utils.h>
#include <kernel/templ.h>

#include <admin/remoteadminintf.h>
#include <admin/localadminintf.h>



namespace dvnci{
namespace admin{

class factory {
public:

    static adminintf_ptr build(const fspath& path, appidtype appid_=0 ,
            eventtypeset events_ = 0, bool needconnect = true){
        adminintf* tmpintf= new localadminintf(path, appid_, events_);
        if (needconnect) tmpintf->connect();
         return adminintf_ptr(tmpintf);}

    
    static adminintf_ptr build(const char* host_, bool needconnect = false){
        std::string tmp=host_;
        std::string host="";
        std::string port="";
        unsigned int tout;
        std::string admin="";
        std::string password="";
        parse_servinfo(tmp, host, port, tout, admin, password);
        adminintf* tmpintf= new remoteadminintf(host,port,tout);
        tmpintf->fullnamed(host_);
        if (needconnect) tmpintf->connect(admin,password);
         return adminintf_ptr(tmpintf);}


};


}
}

#endif	/* _BUILDER_NSADMININTERFACE_H */

