/* 
 * File:   netintf.cpp
 * Author: Serg
 * 
 * Created on 20 Р пїЅРЎР‹Р В»РЎРЉ 2010 Р С–., 14:24
 */

#include "ddeintf.h"

#include <boost/date_time/posix_time/posix_time.hpp>



namespace dvnci {
    namespace dde {


            
        typedef std::pair< HCONV, ddeintf* > conv_ddeintf_pair;
        typedef std::map<  HCONV, ddeintf* , std::less<HCONV> , std::allocator<conv_ddeintf_pair > > conv_ddeintf_map;

		bool cast_dvnci_by_dde(HDDEDATA dt, UINT dtp, num64& val, num64& tp) {
             if (!dt) return false;
             DWORD len = 0;
			 LPBYTE vl=DdeAccessData(dt, &len);
			 if (vl) {
			    std::string vlstr((char*)vl,len-1);
			    tp=0;
			    val = num64_from_string_and_type(vlstr,static_cast<tagtype>(tp));
			    DdeUnaccessData(dt);
                DdeFreeDataHandle(dt);
                return true;}
			 else{
				DdeUnaccessData(dt);
                DdeFreeDataHandle(dt);
				return false;}}        
        
        conv_ddeintf_map CONVERSATIONMAP;
        
   
        HDDEDATA EXPENTRY  DdeCallBack ( UINT     iType,
                                         UINT     iFmt,
                                         HCONV    hConv,
                                         HSZ      hsz1,
                                         HSZ      hsz2,
                                         HDDEDATA hData,
                                         DWORD    dwData1,
                                         DWORD    dwData2 ){
               switch ( iType ){
				   case XTYP_ERROR:{
                      conv_ddeintf_map::iterator it=CONVERSATIONMAP.find(hConv);
                      if (it!=CONVERSATIONMAP.end()){
                           // unregister;
                       }}
	
                   case XTYP_ADVDATA: {
                       conv_ddeintf_map::iterator it=CONVERSATIONMAP.find(hConv);
                       if (it!=CONVERSATIONMAP.end()){
				it->second->addvalmap(hsz2,hData);}
					   return((HDDEDATA)DDE_FACK);}
                  case XTYP_DISCONNECT:{
                      conv_ddeintf_map::iterator it=CONVERSATIONMAP.find(hConv);
                      if (it!=CONVERSATIONMAP.end()){
                           // unregister;
                       }}
                  case XTYP_REGISTER:
                      conv_ddeintf_map::iterator it=CONVERSATIONMAP.find(hConv);
                      if (it!=CONVERSATIONMAP.end()){
                           // register;
                       }}
                   return (HDDEDATA)FALSE;}

        std::wstring s2ws(const std::string& s, UINT cp = CP_UTF8) {
            int len;
            int slength = (int) s.length() + 1;
            len = MultiByteToWideChar(cp, 0, s.c_str(), slength, 0, 0);
            wchar_t* buf = new wchar_t[len];
            MultiByteToWideChar(cp, 0, s.c_str(), slength, buf, len);
            std::wstring r(buf);
            delete[] buf;
            return r;}





        class dde_util : public abstract_dde_util {
        public:

            dde_util(ddeintf * const ddesimpl_, std::string serv, std::string topc = "", std::string hst = "") :
            abstract_dde_util(), ddesimpl(ddesimpl_), init_(false),  DdeInstance(0), host(hst), server(serv), topic(topc) {}

            virtual ~dde_util() {
                resetinit();}

             
        
            virtual bool setinit() {
                 DdeInstance = 0;
                 UINT rstinit=DdeInitialize( &DdeInstance, (PFNCALLBACK)&DdeCallBack,
                            APPCLASS_STANDARD,
                            0L );
                 if (rstinit) return false;
                 HSZ        hszService = DdeCreateStringHandle( DdeInstance, server.c_str(), CP_WINANSI );
                 HSZ        hszTopic = DdeCreateStringHandle( DdeInstance, topic.c_str(), CP_WINANSI );
                 hDdeConv = DdeConnect( DdeInstance, hszService, hszTopic, (PCONVCONTEXT)NULL );
                 DdeFreeStringHandle( DdeInstance, hszTopic );
                 DdeFreeStringHandle( DdeInstance, hszService );
                 if (!hDdeConv) return false;
                 CONVERSATIONMAP.insert(conv_ddeintf_pair(hDdeConv,ddesimpl));
                 init_ = true;
		 return true;}

             virtual bool resetinit() {
                if (hDdeConv) {
                    DdeDisconnect(hDdeConv);
                    conv_ddeintf_map::iterator it=CONVERSATIONMAP.find(hDdeConv);
                    if (it!=CONVERSATIONMAP.end()){
                        CONVERSATIONMAP.erase(hDdeConv);}}
                if (DdeInstance) DdeUninitialize(DdeInstance);
                return true;}

			 HCONV& conversation()  {  return hDdeConv;};
			 DWORD instance()  {  return DdeInstance;};
        private:
            ddeintf * const ddesimpl;        
            bool            init_;
            bool            advice_;
            DWORD           DdeInstance;
            HCONV           hDdeConv ;
            std::string     host;
            std::string     server;
            std::string     topic;};

        

        ddeintf::~ddeintf() {
            disconnect();};

        bool ddeintf::connect() {

            if (!intf) return false;
            if (!intf->groups()->exists(group)) return false;


            DEBUG_VAL_DVNCI(static_cast<pddegroupstruct> (intf->groups()->config(group))->server())

            std::string szServerName = static_cast<pddegroupstruct> (intf->groups()->config(group))->server();
            std::string szTopicName = static_cast<pddegroupstruct> (intf->groups()->config(group))->topic();    
            std::string szHostName = static_cast<pddegroupstruct> (intf->groups()->config(group))->host();


            abstr_dde_util_ptr tmpinf = abstr_dde_util_ptr(new dde_util(this,  szServerName, szTopicName, szHostName));
            if (!tmpinf->setinit()) return false;
            dde_spec = tmpinf;

            _state = Connected;

            return true;}

        bool ddeintf::disconnect() {

            if (_state == Connected) {
                if (dde_spec)
                    dde_spec.reset();
                _state = disConnected;
                valitemmap.clear();
                srv_clientmap.clear();
                clt_servermap.clear();}
            return true;}


       void ddeintf::addvalmap( HSZ hsz, HDDEDATA hData) {
                char tmp[255];
                if (dde_spec) {
                    num64 val, tp;
                    if (cast_dvnci_by_dde(hData,0,val, tp)){
                        DWORD len = DdeQueryString( static_cast<dde_util*>(dde_spec.get())->instance(), hsz, (LPTSTR)&tmp , 254, CP_WINANSI);
                        if (len<255){
                           std::string tmpstr((char*)&tmp,len);
                           ddevalue_item tmpval = {tmpstr, val, 100, tp};
                           addvalmap(tmpstr,tmpval);}}}}

        bool ddeintf::add_items(const vect_ddeclient_item& clientitem, vect_ddeclient_item& serveritem, vect_ddeerror_item& errors) {

            serveritem.clear();
            errors.clear();
            for (vect_ddeclient_item::const_iterator it = clientitem.begin(); it != clientitem.end(); ++it) {
                if (intf->exists(it->key)) {
                    if (!find_by_clid(it->key)) {
						ddeclient_item tmp = { it->key , it->tpitem , it->name};
						serveritem.push_back(tmp);}}}
			return true;}

        bool ddeintf::cnangeactiveItems(const str_vect& chitem, vect_ddeclient_item& serveritem, vect_ddeerror_item& errors, bool active) {
            return true;}

        bool ddeintf::remove_items(const str_vect& delitem, vect_ddeerror_item& errors) {
            errors.clear();
            vect_ddeclient_item serveritem;
            return cnangeactiveItems(delitem, serveritem, errors, false);}

        bool ddeintf::read_values(vect_ddevalue_item& values, vect_ddereport_value_items& reportvalues,  vect_ddeevent_value_item& eventvalues) {
            values.clear();
            reportvalues.clear();
            eventvalues.clear();
            for (ddevalue_item_map::iterator it = valitemmap.begin(); it != valitemmap.end(); ++it) {
                values.push_back(it->second);}
            return true;}

        bool ddeintf::read_values(const str_vect& servids, vect_ddevalue_item& values, vect_ddereport_value_items& reportvalues, vect_ddeevent_value_item& eventvalues,  vect_ddeerror_item& errors) {
                values.clear();
                reportvalues.clear();
                eventvalues.clear();
                errors.clear();
		for(str_vect::const_iterator it=servids.begin();it!=servids.end();++it){
            	    DWORD pdwResult;
                    HSZ FHszItem  = DdeCreateStringHandle(static_cast<dde_util*> (dde_spec.get())->instance(), (*it).c_str(), CP_WINANSI);
                    if (FHszItem){
	                HDDEDATA dt= DdeClientTransaction(NULL, (DWORD)-1 , static_cast<dde_util*> (dde_spec.get())->conversation() , FHszItem ,
                          CF_TEXT, XTYP_REQUEST   , 1000, &pdwResult);
		        if (dt) addvalmap(FHszItem,dt);
                        DdeFreeStringHandle(static_cast<dde_util*> (dde_spec.get())->instance(),FHszItem);}}
		read_values(values, reportvalues, eventvalues);
            return true;}



       
        bool ddeintf::add_commands(const vect_ddecommand_item& commanditem, vect_ddeerror_item& errors) {
            return true;}


}}
