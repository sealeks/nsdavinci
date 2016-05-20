//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2014 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>

#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"


/*
 Type request:
           
 1. init
  
                                        user                                                                                                                                      server
                                  {  "init-req":  "0"    }                                                          ->           
                                                                                                                                                    <-              {"init-resp" : "RESPID"}
 
 2. process
 
    2.1 add tags in request
 
              { "session" : "RESPID" , add-tag : [... added tags list...] }         ->
     2.2                             
 
 
 */


namespace http {
    namespace server {

        namespace ptree = boost::property_tree;

        typedef int operationid_type;
        typedef std::map<std::string, operationid_type> operationmap;

        const operationid_type SESSION_REQUEST = 1;
        const operationid_type INIT_REQUEST = 2;
        const operationid_type ADDTAG_REQUEST = 3;
        const operationid_type REMOVETAG_REQUEST = 4;
        const operationid_type UPDATE_REQUEST = 5;

        const std::string& SESSION_REQUEST_S = "session";
        const std::string& INIT_REQUEST_S = "init-req";
        const std::string& INIT_RESPONSE_S = "init-resp";
        const std::string& ADDTAG_REQUEST_S = "add-tags";
        const std::string& REMOVETAG_REQUEST_S = "remove-tags";
        const std::string& UPDATE_REQUEST_S = "get-update";

        request_handler::request_handler(const std::string& doc_root, http_session_manager_ptr mngr)
        : doc_root_(doc_root), manager_(mngr) {
        }

        void request_handler::handle_request(const request& req, reply& rep) {
            // Decode url to path.
            std::string request_path;
            if (!url_decode(req.uri, request_path)) {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }

            //DEBUG_VAL_DVNCI(request_path);

            // Request path must be absolute and not contain "..".
            if (request_path.empty() || request_path[0] != '/'
                    || request_path.find("..") != std::string::npos) {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }

            boost::algorithm::trim(request_path);

            // If path ends in slash (i.e. is a directory) then add "index.html".
            if (request_path[request_path.size() - 1] == '/') {
                request_path += "index.html";
            }

            // Determine the file extension.
            std::size_t last_slash_pos = request_path.find_last_of("/");
            std::size_t last_dot_pos = request_path.find_last_of(".");
            std::string extension;
            if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos) {
                extension = request_path.substr(last_dot_pos + 1);
            }

            // Open the file to send back.
            std::string full_path = doc_root_ + request_path;


            std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
            if (!is) {
                rep = reply::stock_reply(reply::not_found);
                return;
            }

            if ((request_path.find("/data") == 0) && (handle_datarequest(req, rep))) {
                return;
            }


            // Fill out the reply to be sent to the client.
            rep.status = reply::ok;
            char buf[512];
            while (is.read(buf, sizeof (buf)).gcount() > 0)
                rep.content.append(buf, is.gcount());
            rep.headers.resize(2);
            rep.headers[0].name = "Content-Length";
            rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
            rep.headers[1].name = "Content-Type";
            rep.headers[1].value = mime_types::extension_to_type(extension);
        }

        bool request_handler::url_decode(const std::string& in, std::string& out) {
            out.clear();
            out.reserve(in.size());
            for (std::size_t i = 0; i < in.size(); ++i) {
                if (in[i] == '%') {
                    if (i + 3 <= in.size()) {
                        int value = 0;
                        std::istringstream is(in.substr(i + 1, 2));
                        if (is >> std::hex >> value) {
                            out += static_cast<char> (value);
                            i += 2;
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else if (in[i] == '+') {
                    out += ' ';
                } else {
                    out += in[i];
                }
            }
            return true;
        }

        bool request_handler::handle_datarequest(const request& req, reply& rep) {
            //return false;
            if (!req.content.empty()) {

                std::string resp;
                if (proccess_request(req.content, resp, manager_)) {

                    rep.status = reply::ok;
                    rep.content = resp;
                    rep.headers.resize(2);
                    rep.headers[0].name = "Content-Length";
                    rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
                    rep.headers[1].name = "Content-Type";
                    rep.headers[1].value = "application/json";
                    return true;

                }
            }
            return false;
        }

        bool proccess_request(const std::string& req, std::string& resp, http_session_manager_ptr self) {

            ptree::ptree req_tree;
            ptree::ptree resp_tree;

            std::stringstream ss;
            std::stringstream so;
            ss << req;

            ptree::json_parser::read_json(ss, req_tree);

            if (proccess_requests(req_tree, resp_tree, self)) {

                ptree::json_parser::write_json(so, resp_tree);
                resp = so.str();

                return true;

            }

            return false;
        }
        
        static bool get_tags_list(const boost::property_tree::ptree& req, tagset_type& tgs){
            for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) 
                tgs.insert(it->second.get_value<std::string>());
            return !tgs.empty();
        }

        bool proccess_requests(const ptree::ptree& req, ptree::ptree& resp, http_session_manager_ptr self) {

            bool result = false;
            sessionid_type sid = 0;
            http_session_ptr sess;

            if (self) {
                for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                    if (it->first == INIT_REQUEST_S) {
                        if (sid = self->create()) {
                            resp.put(INIT_RESPONSE_S, sid);
                            result = true;
                        }
                    } else if (it->first == SESSION_REQUEST_S) {
                        sid = it->second.get_value<sessionid_type>();
                        sess = self->get(sid);
                        if (sess)
                            sess->call();
                    } else if (it->first == UPDATE_REQUEST_S) {
                        if (sess) {
                            resp.put(INIT_RESPONSE_S, sid);
                            result = true;
                        }
                    } else if (it->first == ADDTAG_REQUEST_S) {
                        if (sess) {
                            tagset_type tgs;
                            if (get_tags_list(it->second, tgs))
                                sess->addtags(tgs);
                            resp.put(INIT_RESPONSE_S, sid);
                            result = true;
                        }
                    } else if (it->first == REMOVETAG_REQUEST_S) {
                        if (sess) {
                            tagset_type tgs;
                            if (get_tags_list(it->second, tgs))
                                sess->removetags(tgs);
                            resp.put(INIT_RESPONSE_S, sid);
                            result = true;
                        }
                    }
                }
            }
            return result;
        }
        








    } // namespace server
} // namespace http
