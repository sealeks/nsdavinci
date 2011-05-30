/* 
 * File:   admin_configer.h
 * Author: Serg
 *
 * Created on 11 Апрель 2010 г., 17:16
 */

#ifndef _APPADMINCONFIGURATOR_H
#define	_APPADMINCONFIGURATOR_H


#include <kernel/constdef.h>
#include <kernel/utils.h>

#include <QSettings>

namespace dvnci {
    namespace admin {


        typedef std::vector<std::string> serverinfo_vector;

        class admin_configer {
        public:

            admin_configer() {
                appsetting = new QSettings("davinciconf", "appadmininfo");}

            void servers(serverinfo_vector& sers_) {
                readservers();
                sers_ = servers_;}

            bool addserver(std::string serv) {
                bool finded = false;

                for (serverinfo_vector::iterator it = servers_.begin(); it != servers_.end(); ++it) {
                    if ((*it) == serv) {
                        finded = true;
                        ;
                        break;}}
                if (!finded) {
                    servers_.push_back(serv);
                    writeservers();}
                return (!finded);}

            bool removeserver(std::string serv) {
                bool finded = false;
                for (serverinfo_vector::iterator it = servers_.begin(); it != servers_.end(); ++it) {
                    if ((*it) == serv) {
                        finded = true;
                        servers_.erase(it);
                        break;}}
                if (finded) writeservers();
                return finded;}

            bool changeserver(std::string serv, std::string servnew) {
                bool finded = false;
                for (serverinfo_vector::iterator it = servers_.begin(); it != servers_.end(); ++it) {
                    if ((*it) == serv) {
                        finded = true;
                        (*it) = servnew;
                        break;}}
                if (finded) writeservers();
                return finded;}

            virtual ~admin_configer() {
                delete appsetting;}
        protected:

            bool readservers() {
                servers_.clear();
                int size = appsetting->beginReadArray("servers");

                for (int i = 0; i < size; i++) {
                    appsetting->setArrayIndex(i);
                    std::string host_ = appsetting->value("server").toString().toStdString();
                    std::string port_ = appsetting->value("port").toString().toStdString();
                    std::string admin_ = appsetting->value("admin").toString().toStdString();
                    std::string password_ = appsetting->value("password").toString().toStdString();
                    std::string tmeout_ = appsetting->value("timeout").toString().toStdString();
                    unsigned int timeout_;
                    str_to<unsigned int>(tmeout_, DEFAULT_DVNCI_TIMOUT, timeout_);
                    servers_.push_back(generate_servinfo(host_, port_, timeout_, admin_, password_));}

                appsetting->endArray();
                return true;}

            void writeservers() {
                appsetting->remove("servers");
                appsetting->beginWriteArray("servers");

                for (unsigned int i = 0; i < servers_.size(); i++) {
                    appsetting->setArrayIndex(i);
                    std::string host_;
                    std::string port_;
                    std::string admin_;
                    std::string password_;
                    unsigned int tiout_;
                    parse_servinfo(servers_.at(i), host_, port_, tiout_, admin_, password_);
                    appsetting->setValue("server", QString(host_.c_str()));
                    appsetting->setValue("port", QString(port_.c_str()));
                    appsetting->setValue("admin", QString(admin_.c_str()));
                    appsetting->setValue("password", QString(password_.c_str()));
                    appsetting->setValue("timeout", QString(to_str(tiout_).c_str()));}
                appsetting->endArray();}

        private:
            serverinfo_vector servers_;
            QSettings* appsetting;} ;}}

#endif	/* _APPADMINCONFIGURATOR_H */

