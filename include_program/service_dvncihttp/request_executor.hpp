//
// request_handler.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2014 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_EXECUTOR_HANDLER_HPP
#define HTTP_EXECUTOR_HANDLER_HPP

#define BOOST_SPIRIT_THREADSAFE

#include <string>


#include <kernel/constdef.h>
#include <kernel/utils.h>
#include <kernel/systemutil.h>
#include <kernel/factory.h>
#include <custom/gui_executor.h>

#include <boost/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "reply.hpp"

namespace http {
    namespace server {


        typedef int operationid_type;
        typedef std::map<std::string, operationid_type> operationmap;
        typedef std::pair<std::string, operationid_type> operationpair;        

        typedef dvnci::custom::gui_executor<dvnci::tagsbase > http_gui_executor;
        typedef callable_shared_ptr<http_gui_executor> http_executor_ptr;

        class http_session;
        typedef boost::shared_ptr<http_session> http_session_ptr;

        ////////////////////////////////////////////////////////
        //  http_terminated_thread
        ////////////////////////////////////////////////////////        

        struct http_terminated_thread {

            http_terminated_thread(http_executor_ptr inf_) : inf(inf_), th(inf_) {
            }

            ~http_terminated_thread() {
                if (inf && (!inf->terminated())) {
                    inf->detachall();
                    inf.terminate();
                }
                th.join();
            }

            http_executor_ptr intf() {
                return inf;
            }

        private:
            http_executor_ptr inf;
            boost::thread th;
        };

        typedef boost::shared_ptr<http_terminated_thread> http_terminated_thread_ptr;



        ////////////////////////////////////////////////////////
        //  http_terminated_thread
        ////////////////////////////////////////////////////////        

        http_executor_ptr build_http_executor();

        http_terminated_thread_ptr build_http_execthread();




        ////////////////////////////////////////////////////////
        //  http_base_listener
        ////////////////////////////////////////////////////////         

        class http_expression_listener : public dvnci::expression_listener {

        public:

            http_expression_listener(const std::string& exp, http_session_ptr sess, bool single = false, bool test = false);

            virtual ~http_expression_listener() {
            }

            virtual void event(const dvnci::short_value& val);

        private:
            std::string expr;
            http_session_ptr session;
        };



        ////////////////////////////////////////////////////////
        //  http_session
        ////////////////////////////////////////////////////////       

         const std::size_t MIN_SESSION_LT=60;        
         const std::size_t DEFAULT_SESSION_LT=600;
         const std::size_t MAX_SESSION_LT=3600;   

        typedef boost::uint64_t sessionid_type;
        typedef dvnci::short_value value_type;
        typedef std::set<std::string > tagset_type;
        typedef std::vector<std::string > executevect_type;        
        typedef std::map<std::string, value_type> valuemap_type;

        class http_session :
        public boost::enable_shared_from_this<http_session> {

        public:

            http_session(sessionid_type id, http_terminated_thread_ptr th_, std::size_t ltm = DEFAULT_SESSION_LT);

            virtual ~http_session() {
            }

            sessionid_type id() const {
                return id_;
            }
            
            std::size_t session_livetm() const;

            boost::mutex& mtx() {
                return mtx_;
            }

            valuemap_type& updatelist() {
                return updatelist_;
            };

            tagset_type& errortag() {
                return errortag_;
            }

            void addtags(const tagset_type& vl);

            void addexecutes(const executevect_type& vl);            

            void removetags(const tagset_type& vl);

            void call();

            reply::status_type proccess_request(operationid_type oper, const boost::property_tree::ptree& req, boost::property_tree::ptree& resp);
            
            bool expired() const;
               
            void updtate_time();            

        protected:

            http_executor_ptr intf();

        private:
            sessionid_type id_;
            std::size_t session_livetm_;            
            http_terminated_thread_ptr th;
            boost::mutex mtx_;
            dvnci::datetime dt_;

            valuemap_type updatelist_;
            tagset_type errortag_;
            

        };

        typedef boost::shared_ptr<http_session> http_session_ptr;
        typedef std::map<sessionid_type, http_session_ptr> http_session_map;

        http_session_ptr build_http_session(sessionid_type id);
          

        
        
        
        ////////////////////////////////////////////////////////
        //  http_session_manager
        ////////////////////////////////////////////////////////    
        
        class http_session_manager; 
        typedef boost::shared_ptr<http_session_manager> http_session_manager_ptr;        
        

        class http_session_manager {

        public:

            http_session_manager() : nextid_(1), mtx() {
            }

            virtual ~http_session_manager() {
            }  
            
            void check();

            reply::status_type proccess_request(const std::string& req, std::string& resp);


        protected:
            
            sessionid_type nextid() const {
                return nextid_;
            }

            http_session_ptr create();              
            
             http_session_ptr get(sessionid_type id);            

            reply::status_type proccess_request(const boost::property_tree::ptree& req, boost::property_tree::ptree& resp);


        private:

            sessionid_type nextid_;
            http_session_map session_map;
            boost::mutex mtx;
        };




    }
}

#endif // HTTP_SERVER_REQUEST_HANDLER_HPP
