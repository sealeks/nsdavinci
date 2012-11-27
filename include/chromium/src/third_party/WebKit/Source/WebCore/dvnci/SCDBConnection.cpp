/* 
 * File:   DVNCIExternal.cpp
 * Author: sealeks@mail.ru
 *
 * Created on 24 Декабрь 2011 г., 18:49
 */

#include "config.h"
#include "Attribute.h"
#include "Binding.h"
#include "Element.h"
#include "Text.h"
#include "EventTarget.h"

#include "DOMWindow.h"
#include "V8BindingState.h"
#include "V8DOMWindow.h"
#include "V8HiddenPropertyName.h"
#include "ExceptionCode.h"
#include "ContentSecurityPolicy.h"
#include "ScheduledAction.h"

#include <wtf/HashMap.h>
#include <wtf/UnusedParam.h>
#include <wtf/Threading.h>

#undef pow

#include <winsock2.h>
#include <dbaccess/db_task_executor.h>
#include <kernel/utils.h>
#include <kernel/systemutil.h>
#include <kernel/constdef.h>

namespace WebCore {

    const int TICK_DVNCI_DBDURATION = 500;

    struct db_guichrome_terminated_thread {

        db_guichrome_terminated_thread(dvnci::database::db_task_executor_ptr inf_) : inf(inf_), th(inf_) {
        }

        ~db_guichrome_terminated_thread() {
            if (inf && (!inf->terminated())) {
                //inf->detachall();
                inf.terminate();
            }
            th.join();
        }

        void call() {
            if (inf) inf->call();
        }

        dvnci::database::db_task_executor * intf() const {
            return inf.operator->();
        }

    private:
        dvnci::database::db_task_executor_ptr inf;
        boost::thread th;
    } ;



    typedef boost::shared_ptr<db_guichrome_terminated_thread>          db_guichrome_terminated_thread_ptr;
    typedef std::set<db_guichrome_terminated_thread_ptr>               db_guichrome_terminated_thread_set;


    db_guichrome_terminated_thread_set DVNCI_DB_THREAD;

    void dvnciDBThreadInit(dvnci::database::db_task_executor_ptr val) {
        DVNCI_DB_THREAD.insert(db_guichrome_terminated_thread_ptr( new db_guichrome_terminated_thread(val)));
    }

    void dvnciDBThreadRemove(dvnci::database::db_task_executor* val) {

        for (db_guichrome_terminated_thread_set::iterator it = DVNCI_DB_THREAD.begin(); it != DVNCI_DB_THREAD.end(); ++it) {
            if ((*it)->intf() == val) {
				(*it)->intf()->terminate();
                DVNCI_DB_THREAD.erase(*it);
                return;
            }
        }
    }

    void dvnciDBMain(void* cntxt) {
        typedef boost::shared_ptr<dvnci::datetime> time_ptr;
        static time_ptr tick = time_ptr(new dvnci::datetime());


        if ((tick->is_special()) ||
                (dvnci::abs(dvnci::millisecondsbetween(*tick, dvnci::now())) > TICK_DVNCI_DBDURATION)) {
            if (!DVNCI_DB_THREAD.empty()) {
                for (db_guichrome_terminated_thread_set::const_iterator it = DVNCI_DB_THREAD.begin(); it != DVNCI_DB_THREAD.end(); ++it) {
                    (*it)->call();
                }
            }
            tick.swap(time_ptr(new dvnci::datetime(dvnci::now())));
        }
        WTF::callOnMainThread(dvnciDBMain, 0, TICK_DVNCI_DBDURATION);

    }

    void (*dvnciDBMainVar)(void*) = 0;

    void initdvnciDBMain() {
        if (!dvnciDBMainVar) {
            dvnciDBMainVar = dvnciDBMain;
            WTF::callOnMainThread(dvnciDBMain, 0);
        }
    }



    static v8::Handle<v8::Value> db_select_trends_method(const v8::Arguments& args);
    static v8::Handle<v8::Value> db_select_reports_method(const v8::Arguments& args);
    static v8::Handle<v8::Value> db_select_journal_method(const v8::Arguments& args);
    static v8::Handle<v8::Value> db_select_debug_method(const v8::Arguments& args);
    static v8::Handle<v8::Value> db_select_query_method(const v8::Arguments& args);
    static v8::Handle<v8::Value> db_close_method(const v8::Arguments& args);



    namespace DVNCI {



        v8::Persistent<v8::ObjectTemplate> DVNCIDB_TEMPLATE;

        v8::Handle<v8::ObjectTemplate> CreatedvnciDBTemplate() {
            v8::HandleScope handle_scope;

            v8::Local<v8::ObjectTemplate> result = v8::ObjectTemplate::New();
            result->SetInternalFieldCount(2);

            result->Set(v8::String::NewSymbol("select_trends"), v8::FunctionTemplate::New(db_select_trends_method));
            result->Set(v8::String::NewSymbol("select_reports"), v8::FunctionTemplate::New(db_select_reports_method));
            result->Set(v8::String::NewSymbol("select_journal"), v8::FunctionTemplate::New(db_select_journal_method));
            result->Set(v8::String::NewSymbol("select_debug"), v8::FunctionTemplate::New(db_select_debug_method));
            result->Set(v8::String::NewSymbol("select"), v8::FunctionTemplate::New(db_select_query_method));
            result->Set(v8::String::NewSymbol("close"), v8::FunctionTemplate::New(db_close_method));

            return handle_scope.Close(result);
        }

        void dvnciExecutorWeakCallback(v8::Persistent<v8::Value> object, void* parameter) {
            dvnci::database::db_task_executor* db = (dvnci::database::db_task_executor*) parameter;
            dvnciDBThreadRemove(db);
            object.ClearWeak();
            object.Dispose();
        }

        class db_connection_listener : public dvnci::database::connect_db_task {
        public:

            db_connection_listener(dvnci::num32 provider, const std::string& connectstring, bool trendef, dvnci::num32 timeout  , v8::Handle<v8::Context> context, ScriptExecutionContext* scriptcontext, v8::Handle<v8::Function> func) :
            dvnci::database::connect_db_task(provider, connectstring, trendef, timeout) , m_context(context) ,  m_scriptcontext(scriptcontext) {
                m_function = v8::Persistent<v8::Function>::New(func);
            }

            virtual ~db_connection_listener() {
                if (m_function.IsEmpty())
                    return;
                m_function.Dispose();
            }

            virtual void event(const dvnci::database::str_trenddef_map& val, const dvnci::dvncierror& error) {

                if (m_scriptcontext && !m_function.IsEmpty() && m_function->IsFunction()) {
                    V8Proxy* proxy = V8Proxy::retrieve(m_scriptcontext);
                    if (proxy) {
                        v8::HandleScope handleScope;
                        v8::Handle<v8::Context> v8Context = v8::Local<v8::Context>::New(m_context.get());
                        if (v8Context.IsEmpty())
                            return; // JS may not be enabled.
                        v8::Context::Scope scope(v8Context);

                        v8::Handle<v8::String> eventSymbol = V8HiddenPropertyName::event();
                        v8::Local<v8::Value> savedEvent = v8Context->Global()->GetHiddenValue(eventSymbol);

                        v8Context->Global()->SetHiddenValue(eventSymbol, conv(val, error));


                        proxy->callFunction(v8::Persistent<v8::Function>::Cast(m_function), v8Context->Global(), 0, 0);
                        if (savedEvent.IsEmpty())
                            v8Context->Global()->SetHiddenValue(eventSymbol, v8::Undefined());
                        else
                            v8Context->Global()->SetHiddenValue(eventSymbol, savedEvent);
                    }
                }
            }

        protected:

            v8::Handle<v8::Value> conv(const dvnci::database::str_trenddef_map& val, const dvnci::dvncierror& error) {


                v8::HandleScope handle_scope;

                v8::Handle<v8::Object> evnt = v8::Object::New();

                if (error) {
                    evnt->Set(v8::String::New("error"), v8::Integer::New(error.code()));
                    evnt->Set(v8::String::New("what"), v8::String::New(error.str().c_str(), error.str().size()));
                    dvnciDBThreadRemove(executor());
                    return handle_scope.Close(evnt);
                }

                //evnt->Set(v8::String::New("error"), v8::Integer::New(error));

                if (trenddef()) {
                    v8::Handle<v8::Array> array = v8::Array::New(val.size());

                    int i = 0;

                    for (dvnci::database::str_trenddef_map::const_iterator it = val.begin(); it != val.end(); ++it) {

                        v8::HandleScope tmphandle_scope;

                        v8::Handle<v8::Object> tmp = v8::Object::New();
                        tmp->Set(v8::String::New("cod"), v8::Integer::New(it->second.cod));
                        tmp->Set(v8::String::New("name"), v8::String::New(it->first.c_str(), it->first.size()));
                        tmp->Set(v8::String::New("comment"), v8::String::New(it->second.comment.c_str(), it->second.comment.size()));
                        tmp->Set(v8::String::New("eu"), v8::String::New(it->second.eu.c_str(), it->second.eu.size()));
                        tmp->Set(v8::String::New("mineu"), v8::Number::New(it->second.mineu));
                        tmp->Set(v8::String::New("maxeu"), v8::Number::New(it->second.maxeu));
                        tmp->Set(v8::String::New("type"), v8::Integer::New(it->second.type));

                        array->Set(i++, tmphandle_scope.Close(tmp));
                    }

                    evnt->Set(v8::String::New("tags"), array);

                }


                if (!error) {

                    v8::Persistent<v8::Object> obj;

                    if (DVNCIDB_TEMPLATE.IsEmpty())
                        DVNCIDB_TEMPLATE = v8::Persistent<v8::ObjectTemplate>::New(CreatedvnciDBTemplate());

                    obj = v8::Persistent<v8::Object>::New(DVNCIDB_TEMPLATE->NewInstance());

                    obj->SetInternalField(0, v8::External::New(executor()));

                    V8Proxy* proxy = V8Proxy::retrieve(m_scriptcontext);

                    obj.MakeWeak(executor(), dvnciExecutorWeakCallback);

                    obj->SetInternalField(1, v8::External::New(proxy && proxy->frame() ? proxy->frame()->domWindow() : 0));

                    evnt->Set(v8::String::New("connection"), obj);

                }

                return handle_scope.Close(evnt);
            }


        private:

            v8::Persistent<v8::Value> m_function;
            OwnHandle<v8::Context> m_context;
            ScriptExecutionContext* m_scriptcontext;
        } ;

        class db_trend_listener : public dvnci::database::trend_db_task {
        public:

            db_trend_listener(const dvnci::str_set& tags, dvnci::datetime start, dvnci::datetime stop  , v8::Handle<v8::Context> context, ScriptExecutionContext* scriptcontext, v8::Handle<v8::Function> func) :
            dvnci::database::trend_db_task(tags, start, stop) , m_context(context) ,  m_scriptcontext(scriptcontext) {
                m_function = v8::Persistent<v8::Function>::New(func);
            }

            virtual ~db_trend_listener() {
                if (m_function.IsEmpty())
                    return;
                m_function.Dispose();
            }

            virtual void event(const dvnci::database::result_trend_pair_map& val, const dvnci::dvncierror& error) {

                if (m_scriptcontext && !m_function.IsEmpty() && m_function->IsFunction()) {
                    V8Proxy* proxy = V8Proxy::retrieve(m_scriptcontext);
                    if (proxy) {
                        v8::HandleScope handleScope;
                        v8::Handle<v8::Context> v8Context = v8::Local<v8::Context>::New(m_context.get());
                        if (v8Context.IsEmpty())
                            return; // JS may not be enabled.
                        v8::Context::Scope scope(v8Context);

                        v8::Handle<v8::String> eventSymbol = V8HiddenPropertyName::event();
                        v8::Local<v8::Value> savedEvent = v8Context->Global()->GetHiddenValue(eventSymbol);

                        v8Context->Global()->SetHiddenValue(eventSymbol, conv(val, error));

                        proxy->callFunction(v8::Persistent<v8::Function>::Cast(m_function), v8Context->Global(), 0, 0);
                        if (savedEvent.IsEmpty())
                            v8Context->Global()->SetHiddenValue(eventSymbol, v8::Undefined());
                        else
                            v8Context->Global()->SetHiddenValue(eventSymbol, savedEvent);
                    }
                }
            }

        protected:

            v8::Handle<v8::Value> conv(const dvnci::database::result_trend_pair_map& val, const dvnci::dvncierror& error) {


                v8::HandleScope handle_scope;

                v8::Handle<v8::Object> evnto = v8::Object::New();

                if (error) {
                    evnto->Set(v8::String::New("error"), v8::Integer::New(error.code()));
                    evnto->Set(v8::String::New("what"), v8::String::New(error.str().c_str(), error.str().size()));
                    return handle_scope.Close(evnto);
                }
                
                //v8::Handle<v8::Object> evnt = v8::Object::New();

                //evnt->Set(v8::String::New("error"), v8::Integer::New(error));

                v8::Handle<v8::Array> array = v8::Array::New(val.size());

                int i = 0;

                for (dvnci::database::result_trend_pair_map::const_iterator it = val.begin(); it != val.end(); ++it) {


                    v8::Handle<v8::Object> tmp = v8::Object::New();

                    tmp->Set(v8::String::New("cod"), v8::Integer::New(it->first.cod));
                    tmp->Set(v8::String::New("name"), v8::String::New(it->first.name.c_str(), it->first.name.size()));
                    tmp->Set(v8::String::New("comment"), v8::String::New(it->first.comment.c_str(), it->first.comment.size()));
                    tmp->Set(v8::String::New("mineu"), v8::Number::New(it->first.mineu));
                    tmp->Set(v8::String::New("maxeu"), v8::Number::New(it->first.maxeu));
                    tmp->Set(v8::String::New("error"), v8::Integer::New(it->first.error));

                    v8::Handle<v8::Array> arraytag = v8::Array::New(it->second->size());

                    int j = 0;

                    for (dvnci::dt_val_map::const_iterator itval = it->second->begin(); itval != it->second->end(); ++itval) {
                        v8::Handle<v8::Array> point = v8::Array::New(2);
                        point->Set(0, v8::Date::New(dvnci::datetime_to_epoch_msc(itval->first)));
                        point->Set(1, itval->second != itval->second ? v8::Undefined() : v8::Number::New(itval->second));
                        arraytag->Set(j++, point);
                    }

                    tmp->Set(v8::String::New("data"), arraytag);
                    array->Set(i++, tmp);
                }

                //evnt->Set(v8::String::New("tags"), array);


                return handle_scope.Close(array);
            }


        private:

            v8::Persistent<v8::Value> m_function;
            OwnHandle<v8::Context> m_context;
            ScriptExecutionContext* m_scriptcontext;

        } ;

        class db_report_listener : public dvnci::database::report_db_task {
        public:

            db_report_listener(const dvnci::str_set& tags, dvnci::datetime start, dvnci::datetime stop  , v8::Handle<v8::Context> context, ScriptExecutionContext* scriptcontext, v8::Handle<v8::Function> func) :
            dvnci::database::report_db_task(tags, start, stop) , m_context(context) ,  m_scriptcontext(scriptcontext) {
                m_function = v8::Persistent<v8::Function>::New(func);
            }

            virtual ~db_report_listener() {
                if (m_function.IsEmpty())
                    return;
                m_function.Dispose();
            }

            virtual void event(const dvnci::database::result_trend_pair_map& val, const dvnci::dvncierror& error) {

                if (m_scriptcontext && !m_function.IsEmpty() && m_function->IsFunction()) {
                    V8Proxy* proxy = V8Proxy::retrieve(m_scriptcontext);
                    if (proxy) {
                        v8::HandleScope handleScope;
                        v8::Handle<v8::Context> v8Context = v8::Local<v8::Context>::New(m_context.get());
                        if (v8Context.IsEmpty())
                            return; // JS may not be enabled.
                        v8::Context::Scope scope(v8Context);

                        v8::Handle<v8::String> eventSymbol = V8HiddenPropertyName::event();
                        v8::Local<v8::Value> savedEvent = v8Context->Global()->GetHiddenValue(eventSymbol);

                        v8Context->Global()->SetHiddenValue(eventSymbol, conv(val, error));

                        proxy->callFunction(v8::Persistent<v8::Function>::Cast(m_function), v8Context->Global(), 0, 0);
                        if (savedEvent.IsEmpty())
                            v8Context->Global()->SetHiddenValue(eventSymbol, v8::Undefined());
                        else
                            v8Context->Global()->SetHiddenValue(eventSymbol, savedEvent);
                    }
                }
            }

        protected:

            v8::Handle<v8::Value> conv(const dvnci::database::result_trend_pair_map& val, const dvnci::dvncierror& error) {



                v8::HandleScope handle_scope;

                v8::Handle<v8::Object> evnt = v8::Object::New();

                if (error) {
                    evnt->Set(v8::String::New("error"), v8::Integer::New(error.code()));
                    evnt->Set(v8::String::New("what"), v8::String::New(error.str().c_str(), error.str().size()));
                    return handle_scope.Close(evnt);
                }

                //evnt->Set(v8::String::New("error"), v8::Integer::New(error));

                v8::Handle<v8::Array> array = v8::Array::New(val.size());

                int i = 0;

                for (dvnci::database::result_trend_pair_map::const_iterator it = val.begin(); it != val.end(); ++it) {


                    v8::Handle<v8::Object> tmp = v8::Object::New();

                    tmp->Set(v8::String::New("cod"), v8::Integer::New(it->first.cod));
                    tmp->Set(v8::String::New("name"), v8::String::New(it->first.name.c_str(), it->first.name.size()));
                    tmp->Set(v8::String::New("comment"), v8::String::New(it->first.comment.c_str(), it->first.comment.size()));
                    tmp->Set(v8::String::New("mineu"), v8::Number::New(it->first.mineu));
                    tmp->Set(v8::String::New("maxeu"), v8::Number::New(it->first.maxeu));
                    tmp->Set(v8::String::New("error"), v8::Integer::New(it->first.error));

                    v8::Handle<v8::Array> arraytag = v8::Array::New(it->second->size());

                    int j = 0;

                    for (dvnci::dt_val_map::const_iterator itval = it->second->begin(); itval != it->second->end(); ++itval) {
                        v8::Handle<v8::Array> point = v8::Array::New(2);
                        point->Set(0, v8::Date::New(dvnci::datetime_to_epoch_msc(itval->first)));
                        point->Set(1, itval->second != itval->second ? v8::Undefined() : v8::Number::New(itval->second));
                        arraytag->Set(j++, point);
                    }


                    tmp->Set(v8::String::New("data"), arraytag);
                    array->Set(i++, tmp);

                }

                evnt->Set(v8::String::New("tags"), array);

                return handle_scope.Close(evnt);

            }


        private:

            v8::Persistent<v8::Value> m_function;
            OwnHandle<v8::Context> m_context;
            ScriptExecutionContext* m_scriptcontext;

        } ;

        class db_journal_listener : public dvnci::database::select_db_journal_task {
        public:

            db_journal_listener(dvnci::datetime start, dvnci::datetime stop, const std::string& filter  , v8::Handle<v8::Context> context, ScriptExecutionContext* scriptcontext, v8::Handle<v8::Function> func) :
            dvnci::database::select_db_journal_task(start, stop, filter) , m_context(context) ,  m_scriptcontext(scriptcontext) {
                m_function = v8::Persistent<v8::Function>::New(func);
            }

            virtual ~db_journal_listener() {
                if (m_function.IsEmpty())
                    return;
                m_function.Dispose();
            }

            virtual void event(const dvnci::vect_journal_row_ptr& val, const dvnci::dvncierror& error) {

                if (m_scriptcontext && !m_function.IsEmpty() && m_function->IsFunction()) {
                    V8Proxy* proxy = V8Proxy::retrieve(m_scriptcontext);
                    if (proxy) {
                        v8::HandleScope handleScope;
                        v8::Handle<v8::Context> v8Context = v8::Local<v8::Context>::New(m_context.get());
                        if (v8Context.IsEmpty())
                            return; // JS may not be enabled.
                        v8::Context::Scope scope(v8Context);

                        v8::Handle<v8::String> eventSymbol = V8HiddenPropertyName::event();
                        v8::Local<v8::Value> savedEvent = v8Context->Global()->GetHiddenValue(eventSymbol);

                        v8Context->Global()->SetHiddenValue(eventSymbol, conv(val, error));

                        proxy->callFunction(v8::Persistent<v8::Function>::Cast(m_function), v8Context->Global(), 0, 0);
                        if (savedEvent.IsEmpty())
                            v8Context->Global()->SetHiddenValue(eventSymbol, v8::Undefined());
                        else
                            v8Context->Global()->SetHiddenValue(eventSymbol, savedEvent);
                    }
                }
            }

        protected:

            v8::Handle<v8::Value> conv(const dvnci::vect_journal_row_ptr& val, const dvnci::dvncierror& error) {


                v8::HandleScope handle_scope;

                v8::Handle<v8::Object> evnt = v8::Object::New();

                if (error) {
                    evnt->Set(v8::String::New("error"), v8::Integer::New(error.code()));
                    evnt->Set(v8::String::New("what"), v8::String::New(error.str().c_str(), error.str().size()));
                    return handle_scope.Close(evnt);
                }

                //evnt->Set(v8::String::New("error"), v8::Integer::New(error));

                v8::Handle<v8::Array> array = v8::Array::New(val->size());

                int i = 0;

                for (dvnci::vect_journal_row::const_iterator it = val->begin(); it != val->end(); ++it) {

                    v8::HandleScope tmphandle_scope;

                    v8::Handle<v8::Object> tmp = v8::Object::New();

                    tmp->Set(v8::String::New("time"), v8::Date::New(dvnci::datetime_to_epoch_msc(it->time)));
                    tmp->Set(v8::String::New("type"), v8::Integer::New(it->type));
                    tmp->Set(v8::String::New("level"), v8::Integer::New(it->level));
                    tmp->Set(v8::String::New("tag"), v8::String::New(it->tag.c_str(), it->tag.size()));
                    tmp->Set(v8::String::New("text"), v8::String::New(it->text.c_str(), it->text.size()));
                    tmp->Set(v8::String::New("agroup"), v8::String::New(it->agroup.c_str(), it->agroup.size()));
                    tmp->Set(v8::String::New("user"), v8::String::New(it->user.c_str(), it->user.size()));
                    tmp->Set(v8::String::New("value"), v8::String::New(it->value.c_str(), it->value.size()));

                    array->Set(i++, tmphandle_scope.Close(tmp));
                }

                evnt->Set(v8::String::New("table"), array);

                return handle_scope.Close(evnt);
            }


        private:

            v8::Persistent<v8::Value> m_function;
            OwnHandle<v8::Context> m_context;
            ScriptExecutionContext* m_scriptcontext;

        } ;

        class db_debug_listener : public dvnci::database::select_db_debug_task {
        public:

            db_debug_listener(dvnci::datetime start, dvnci::datetime stop, const std::string& filter  , v8::Handle<v8::Context> context, ScriptExecutionContext* scriptcontext, v8::Handle<v8::Function> func) :
            dvnci::database::select_db_debug_task(start, stop, filter) , m_context(context) ,  m_scriptcontext(scriptcontext) {
                m_function = v8::Persistent<v8::Function>::New(func);
            }

            virtual ~db_debug_listener() {
                if (m_function.IsEmpty())
                    return;
                m_function.Dispose();
            }

            virtual void event(const dvnci::vect_debug_row_ptr& val, const dvnci::dvncierror& error) {

                if (m_scriptcontext && !m_function.IsEmpty() && m_function->IsFunction()) {
                    V8Proxy* proxy = V8Proxy::retrieve(m_scriptcontext);
                    if (proxy) {
                        v8::HandleScope handleScope;
                        v8::Handle<v8::Context> v8Context = v8::Local<v8::Context>::New(m_context.get());
                        if (v8Context.IsEmpty())
                            return; // JS may not be enabled.
                        v8::Context::Scope scope(v8Context);

                        v8::Handle<v8::String> eventSymbol = V8HiddenPropertyName::event();
                        v8::Local<v8::Value> savedEvent = v8Context->Global()->GetHiddenValue(eventSymbol);

                        v8Context->Global()->SetHiddenValue(eventSymbol, conv(val, error));

                        proxy->callFunction(v8::Persistent<v8::Function>::Cast(m_function), v8Context->Global(), 0, 0);
                        if (savedEvent.IsEmpty())
                            v8Context->Global()->SetHiddenValue(eventSymbol, v8::Undefined());
                        else
                            v8Context->Global()->SetHiddenValue(eventSymbol, savedEvent);
                    }
                }
            }

        protected:

            v8::Handle<v8::Value> conv(const dvnci::vect_debug_row_ptr& val, const dvnci::dvncierror& error) {


                v8::HandleScope handle_scope;

                v8::Handle<v8::Object> evnt = v8::Object::New();

                if (error) {
                    evnt->Set(v8::String::New("error"), v8::Integer::New(error.code()));
                    evnt->Set(v8::String::New("what"), v8::String::New(error.str().c_str(), error.str().size()));
                    return handle_scope.Close(evnt);
                }

                //evnt->Set(v8::String::New("error"), v8::Integer::New(error));

                v8::Handle<v8::Array> array = v8::Array::New(val->size());

                int i = 0;

                for (dvnci::vect_debug_row::const_iterator it = val->begin(); it != val->end(); ++it) {

                    v8::HandleScope tmphandle_scope;

                    v8::Handle<v8::Object> tmp = v8::Object::New();

                    tmp->Set(v8::String::New("time"), v8::Date::New(dvnci::datetime_to_epoch_msc(it->time)));
                    tmp->Set(v8::String::New("message"), v8::String::New(it->message.c_str(), it->message.size()));
                    tmp->Set(v8::String::New("appid"), v8::Integer::New(it->appid));
                    tmp->Set(v8::String::New("level"), v8::Integer::New(it->level));

                    array->Set(i++, tmphandle_scope.Close(tmp));
                }

                evnt->Set(v8::String::New("table"), array);

                return handle_scope.Close(evnt);
            }


        private:

            v8::Persistent<v8::Value> m_function;
            OwnHandle<v8::Context> m_context;
            ScriptExecutionContext* m_scriptcontext;

        } ;

        class db_select_listener : public dvnci::database::select_db_task {
        public:

            db_select_listener(const std::string& req  , v8::Handle<v8::Context> context, ScriptExecutionContext* scriptcontext, v8::Handle<v8::Function> func) :
            dvnci::database::select_db_task(req) , m_context(context) ,  m_scriptcontext(scriptcontext) {
                m_function = v8::Persistent<v8::Function>::New(func);
            }

            virtual ~db_select_listener() {
                if (m_function.IsEmpty())
                    return;
                m_function.Dispose();
            }

            virtual void event(const dvnci::database::sql_result_ptr& val, const dvnci::dvncierror& error) {

                if (m_scriptcontext && !m_function.IsEmpty() && m_function->IsFunction()) {
                    V8Proxy* proxy = V8Proxy::retrieve(m_scriptcontext);
                    if (proxy) {
                        v8::HandleScope handleScope;
                        v8::Handle<v8::Context> v8Context = v8::Local<v8::Context>::New(m_context.get());
                        if (v8Context.IsEmpty())
                            return; // JS may not be enabled.
                        v8::Context::Scope scope(v8Context);

                        v8::Handle<v8::String> eventSymbol = V8HiddenPropertyName::event();
                        v8::Local<v8::Value> savedEvent = v8Context->Global()->GetHiddenValue(eventSymbol);

                        v8Context->Global()->SetHiddenValue(eventSymbol, conv(val, error));

                        proxy->callFunction(v8::Persistent<v8::Function>::Cast(m_function), v8Context->Global(), 0, 0);
                        if (savedEvent.IsEmpty())
                            v8Context->Global()->SetHiddenValue(eventSymbol, v8::Undefined());
                        else
                            v8Context->Global()->SetHiddenValue(eventSymbol, savedEvent);
                    }
                }
            }

        protected:

            v8::Handle<v8::Value> conv(const dvnci::database::sql_result_ptr& val, const dvnci::dvncierror& error) {


                v8::HandleScope handle_scope;

                v8::Handle<v8::Object> evnt = v8::Object::New();

                if (error) {
                    evnt->Set(v8::String::New("error"), v8::Integer::New(error.code()));
                    evnt->Set(v8::String::New("what"), v8::String::New(error.str().c_str(), error.str().size()));
                    return handle_scope.Close(evnt);
                }

                //evnt->Set(v8::String::New("error"), v8::Integer::New(error));

                v8::Handle<v8::Array> header = v8::Array::New(val->first.size());

                int i = 0;

                typedef std::vector<int> inttype_vect;

                inttype_vect typevect;


                for (dvnci::database::sql_header_vect::const_iterator it = val->first.begin(); it != val->first.end(); ++it) {

                    v8::Handle<v8::Array> arrayh = v8::Array::New(2);

                    arrayh->Set(0, v8::Integer::New(i));
                    arrayh->Set(1, v8::String::New(it->first.c_str(), it->first.size()));
                    typevect.push_back(it->second);

                    header->Set(i++, arrayh);
                }

                evnt->Set(v8::String::New("header"), header);


                v8::Handle<v8::Array> data = v8::Array::New(val->second.size());

                i = 0;

                for (dvnci::database::str_table::const_iterator it = val->second.begin(); it != val->second.end(); ++it) {

                    v8::Handle<v8::Array> arrayr = v8::Array::New(it->size());

                    size_t j = 0;
                    for (dvnci::str_vect::const_iterator itrow = it->begin(); itrow != it->end(); ++itrow) {
                        if (typevect.size() > j) {
                            switch (typevect[j]) {
                                case 2:
                                {
                                    double vl = 0;
                                    arrayr->Set(j++, dvnci::str_to(*itrow, vl) ? v8::Number::New(vl): v8::Null() );
                                    break;
                                }
                                case 3:
                                {
                                    int vl = 0;
                                    arrayr->Set(j++, dvnci::str_to(*itrow, vl) ? v8::Integer::New(vl): v8::Null() );
                                    break;
                                }
                                case 4:
                                {
                                    dvnci::unum64 vl = 0;
                                    arrayr->Set(j++, dvnci::str_to(*itrow, vl) ? v8::Integer::New(vl): v8::Null() );
                                    break;
                                }
                                default:
                                {
                                    arrayr->Set(j++, v8::String::New(itrow->c_str(), itrow->size()));
                                    ;
                                    break;
                                }
                            }
                        }
                        else
                            arrayr->Set(j++, v8::String::New(itrow->c_str(), itrow->size()));
                    }


                    data->Set(i++, arrayr);
                }

                evnt->Set(v8::String::New("data"), data);


                return handle_scope.Close(evnt);

            }


        private:

            v8::Persistent<v8::Value> m_function;
            OwnHandle<v8::Context> m_context;
            ScriptExecutionContext* m_scriptcontext;

        } ;



    }

    dvnci::database::db_task_executor* unwrap_db_task_executor(const v8::Arguments& args) {

        v8::Handle<v8::External> field = v8::Handle<v8::External>::Cast(args.Holder()->GetInternalField(0));
        return static_cast<dvnci::database::db_task_executor*> (field->Value());

    }

    static ScriptExecutionContext* getHandler(const v8::Arguments& args, DOMWindow* & impl, v8::Handle<v8::Value>& function) {

        ScriptExecutionContext* scriptContext = 0;

        impl = static_cast<DOMWindow* > (v8::Local<v8::External>::Cast(args.Holder()->GetInternalField(1))->Value());

        if ( impl  &&  (impl->frame()) && (scriptContext = static_cast<ScriptExecutionContext*> (impl->document()))) {

            WTF::String functionString;
            if (!function->IsFunction()) {
                if (function->IsString())
                    functionString = toWebCoreString(function);
                else {
                    v8::Handle<v8::Value> v8String = function->ToString();
                    functionString = v8String.IsEmpty() ? "" : toWebCoreString(v8String);
                }
                return functionString.length() ? scriptContext : 0;
            }
            else {
                return scriptContext;
            }
        }
        return 0;
    }

    static v8::Handle<v8::Value> db_select_trends_method(const v8::Arguments& args) {

        int argumentCount = args.Length();

        if (argumentCount < 4) return v8::Undefined();

        dvnci::database::db_task_executor* db = unwrap_db_task_executor(args);

        dvnci::str_set tags;

        if (args[1]->IsString()) {
            String tmp = toWebCoreString(args[1]);
            tags.insert(dvnci::wstr_to_utf8(std::wstring(tmp.characters(), tmp.length())));
        }
        else {
            if (args[1]->IsArray()) {
                v8::Handle<v8::Array> array = v8::Handle<v8::Array>::Cast(args[1]);
                for (uint32_t i = 0; i < array->Length(); i++) {
                    if (array->Get(i)->IsString()) {
                        String tmp = toWebCoreString(array->Get(i));
                        tags.insert(dvnci::wstr_to_utf8(std::wstring(tmp.characters(), tmp.length())));
                    }
                }
            }
            else
                return v8::Undefined();
        }

        if (tags.empty())
            return v8::Undefined();

        if (!args[2]->IsDate() || !args[3]->IsDate())
            return v8::Undefined();

        dvnci::datetime start = dvnci::incmillisecond(dvnci::epoch_time, toInt64(args[2]));
        dvnci::datetime stop = dvnci::incmillisecond(dvnci::epoch_time, toInt64(args[3]));

        ScriptExecutionContext* scriptContext = 0;
        DOMWindow* imp = 0;
        v8::Handle<v8::Value> function = args[0];

        if (scriptContext = getHandler(args, imp, function)) {

            dvnci::database::trend_db_task_ptr task = dvnci::database::trend_db_task_ptr(
                    new WebCore::DVNCI::db_trend_listener(tags, start, stop, V8Proxy::context(imp->frame()), scriptContext, v8::Handle<v8::Function>::Cast(function)));

            db->insert_trend_task(task);

            return v8::Boolean::New(true);
        }

        return v8::Undefined();
    }

    static v8::Handle<v8::Value> db_select_reports_method(const v8::Arguments& args) {


        int argumentCount = args.Length();

        if (argumentCount < 4) return v8::Undefined();

        dvnci::database::db_task_executor* db = unwrap_db_task_executor(args);

        dvnci::str_set tags;

        if (args[1]->IsString()) {
            String tmp = toWebCoreString(args[1]);
            tags.insert(dvnci::wstr_to_utf8(std::wstring(tmp.characters(), tmp.length())));
        }
        else {
            if (args[1]->IsArray()) {
                v8::Handle<v8::Array> array = v8::Handle<v8::Array>::Cast(args[1]);
                for (uint32_t i = 0; i < array->Length(); i++) {
                    if (array->Get(i)->IsString()) {
                        String tmp = toWebCoreString(array->Get(i));
                        tags.insert(dvnci::wstr_to_utf8(std::wstring(tmp.characters(), tmp.length())));
                    }
                }
            }
            else
                return v8::Undefined();
        }

        if (tags.empty())
            return v8::Undefined();

        if (!args[2]->IsDate() || !args[3]->IsDate())
            return v8::Undefined();

        dvnci::datetime start = dvnci::incmillisecond(dvnci::epoch_time, toInt64(args[2]));
        dvnci::datetime stop = dvnci::incmillisecond(dvnci::epoch_time, toInt64(args[3]));

        ScriptExecutionContext* scriptContext = 0;
        DOMWindow* imp = 0;
        v8::Handle<v8::Value> function = args[0];

        if (scriptContext = getHandler(args, imp, function)) {

            dvnci::database::report_db_task_ptr task = dvnci::database::report_db_task_ptr(
                    new WebCore::DVNCI::db_report_listener(tags, start, stop, V8Proxy::context(imp->frame()), scriptContext, v8::Handle<v8::Function>::Cast(function)));

            db->insert_report_task(task);

            return v8::Boolean::New(true);
        }

        return v8::Undefined();

    }

    static v8::Handle<v8::Value> db_select_journal_method(const v8::Arguments& args) {

        int argumentCount = args.Length();

        if (argumentCount < 3) return v8::Undefined();

        dvnci::database::db_task_executor* db = unwrap_db_task_executor(args);

        if (!args[1]->IsDate() || !args[2]->IsDate())
            return v8::Undefined();

        dvnci::datetime start =  dvnci::incmillisecond(dvnci::epoch_time, toInt64(args[1]));
        dvnci::datetime stop = dvnci::incmillisecond(dvnci::epoch_time, toInt64(args[2]));

        std::string filter = "";

        if ((argumentCount > 3) && (args[3]->IsString())) {
            String tmp = toWebCoreString(args[3]);
            filter = dvnci::wstr_to_utf8(std::wstring(tmp.characters(), tmp.length()));
        }

        ScriptExecutionContext* scriptContext = 0;
        DOMWindow* imp = 0;
        v8::Handle<v8::Value> function = args[0];

        if (scriptContext = getHandler(args, imp, function)) {

            dvnci::database::select_db_journal_task_ptr task = dvnci::database::select_db_journal_task_ptr(
                    new WebCore::DVNCI::db_journal_listener(start, stop, filter, V8Proxy::context(imp->frame()), scriptContext, v8::Handle<v8::Function>::Cast(function)));

            db->insert_journal_task(task);

            return v8::Boolean::New(true);
        }

        return v8::Undefined();
    }

    static v8::Handle<v8::Value> db_select_debug_method(const v8::Arguments& args) {

        int argumentCount = args.Length();

        if (argumentCount < 3) return v8::Undefined();

        dvnci::database::db_task_executor* db = unwrap_db_task_executor(args);

        if (!args[1]->IsDate() || !args[2]->IsDate())
            return v8::Undefined();

        dvnci::datetime start =  dvnci::incmillisecond(dvnci::epoch_time, toInt64(args[1]));
        dvnci::datetime stop = dvnci::incmillisecond(dvnci::epoch_time, toInt64(args[2]));

        std::string filter = "";

        if ((argumentCount > 3) && (args[3]->IsString())) {
            String tmp = toWebCoreString(args[3]);
            filter = dvnci::wstr_to_utf8(std::wstring(tmp.characters(), tmp.length()));
        }

        ScriptExecutionContext* scriptContext = 0;
        DOMWindow* imp = 0;
        v8::Handle<v8::Value> function = args[0];

        if (scriptContext = getHandler(args, imp, function)) {

            dvnci::database::select_db_debug_task_ptr task = dvnci::database::select_db_debug_task_ptr(
                    new WebCore::DVNCI::db_debug_listener(start, stop, filter, V8Proxy::context(imp->frame()), scriptContext, v8::Handle<v8::Function>::Cast(function)));

            db->insert_debug_task(task);

            return v8::Boolean::New(true);
        }

        return v8::Undefined();
    }

    static v8::Handle<v8::Value> db_select_query_method(const v8::Arguments& args) {

        int argumentCount = args.Length();

        if (argumentCount < 2) return v8::Undefined();

        dvnci::database::db_task_executor* db = unwrap_db_task_executor(args);

        std::string req = "";

        if ((argumentCount > 1) && (args[1]->IsString())) {
            String tmp = toWebCoreString(args[1]);
            req = dvnci::wstr_to_utf8(std::wstring(tmp.characters(), tmp.length()));
        }

        ScriptExecutionContext* scriptContext = 0;
        DOMWindow* imp = 0;
        v8::Handle<v8::Value> function = args[0];

        if (scriptContext = getHandler(args, imp, function)) {

            dvnci::database::select_db_task_ptr task = dvnci::database::select_db_task_ptr(
                    new WebCore::DVNCI::db_select_listener(req, V8Proxy::context(imp->frame()), scriptContext, v8::Handle<v8::Function>::Cast(function)));

            db->insert_select_task(task);

            return v8::Boolean::New(true);
        }


        return v8::Undefined();
    }

    static v8::Handle<v8::Value> db_close_method(const v8::Arguments& args) {

        dvnci::database::db_task_executor* db = unwrap_db_task_executor(args);
	//dvnciDBThreadRemove(db);
        return v8::Boolean::New(db->disconnect());
    }

    
    
    v8::Handle<v8::Value> dvnciSCDBConnection(const v8::Arguments& args, bool trenddef =true) {

        int argumentCount = args.Length();

        initdvnciDBMain();

        dvnci::num32 provider = dvnci::PROPERTY_DB_PROVIDER_POSTGRESS;

        std::string connectionstring = "";

        dvnci::num32 timeout = 15;


        bool hascallback = false;

        if (argumentCount > 2) {

            provider = static_cast<dvnci::num32> (toInt64(args[1]));

            String connectionstr = toWebCoreString(args[2]);
            connectionstring  = std::string(connectionstr.utf8().data());

            if (argumentCount > 3)
                timeout = static_cast<dvnci::indx> (toInt64(args[3]));


            ScriptExecutionContext* scriptContext = 0;
            DOMWindow* imp = V8DOMWindow::toNative(args.Holder());
            v8::Handle<v8::Value> function = argumentCount ? args[0] : v8::Handle<v8::Value > ();



            if ( imp  &&  (imp->frame()) && (argumentCount) && (scriptContext = static_cast<ScriptExecutionContext*> (imp->document()))) {

                WTF::String functionString;
                if (!function->IsFunction()) {
                    if (function->IsString())
                        functionString = toWebCoreString(function);
                    else {
                        v8::Handle<v8::Value> v8String = function->ToString();
                        functionString = v8String.IsEmpty() ? "" : toWebCoreString(v8String);
                    }
                    hascallback = functionString.length();
                }
                else {
                    hascallback = true;
                }
            }

            if (provider && hascallback) {
                dvnci::database::connect_db_task_ptr  exrptr = dvnci::database::connect_db_task_ptr(
                        new WebCore::DVNCI::db_connection_listener(provider , connectionstring , trenddef, timeout, V8Proxy::context(imp->frame()), scriptContext, v8::Handle<v8::Function>::Cast(function)));
                dvnci::database::db_task_executor_ptr func = dvnci::database::db_task_executor_ptr(new dvnci::database::db_task_executor(exrptr));
                dvnciDBThreadInit(func);

                return v8::Boolean::New(true);
            }
        }
        return v8::Boolean::New(false);

    }
    
            
    

}