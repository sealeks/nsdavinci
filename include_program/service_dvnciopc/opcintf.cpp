/* 
 * File:   netintf.cpp
 * Author: Serg
 * 
 * Created on 20 Р В РїС—Р…Р РЋР вЂ№Р В Р’В»Р РЋР Р‰ 2010 Р В РЎвЂ“., 14:24
 */

#include "opcintf.h"


#include <boost/date_time/posix_time/posix_time.hpp>



namespace dvnci {
    namespace external {
    namespace opc {

        std::wstring s2ws(const std::string& s, UINT cp = CP_UTF8) {
            int len;
            int slength = (int) s.length() + 1;
            len = MultiByteToWideChar(cp, 0, s.c_str(), slength, 0, 0);
            wchar_t* buf = new wchar_t[len];
            MultiByteToWideChar(cp, 0, s.c_str(), slength, buf, len);
            std::wstring r(buf);
            delete[] buf;
            return r;}

        bool cast_oletype_by_dvnci(num64 val, num64 tp, VARIANT& vrt) {
            switch (tp) {
                case TYPE_DISCRET:{
                    vrt.boolVal = (val != 0);
                    vrt.vt = VT_BOOL;
                    break;}
                case TYPE_NUM64:{
                    vrt.llVal = from_num64_cast<num64 > (val);
                    vrt.vt = VT_I8;
                    break;}
                case TYPE_UNUM64:{
                    vrt.ullVal = from_num64_cast<unum64 > (val);
                    vrt.vt = VT_UI8;
                    break;}
                case TYPE_NUM32:{
                    vrt.lVal = from_num64_cast<num32 > (val);
                    vrt.vt = VT_I4;
                    break;}
                case TYPE_UNUM32:{
                    vrt.ulVal = from_num64_cast<unum32 > (val);
                    vrt.vt = VT_UI4;
                    break;}
                case TYPE_NUM16:{
                    vrt.iVal = from_num64_cast<num16 > (val);
                    vrt.vt = VT_I2;
                    break;}
                case TYPE_UNUM16:{
                    vrt.uiVal = from_num64_cast<unum16 > (val);
                    vrt.vt = VT_UI2;
                    break;}
                case TYPE_NUM8:{
                    vrt.cVal = from_num64_cast<num8 > (val);
                    vrt.vt = VT_I1;
                    break;}
                case TYPE_UNUM8:{
                    vrt.bVal = from_num64_cast<unum8 > (val);
                    vrt.vt = VT_UI1;
                    break;}
                case TYPE_DOUBLE:{
                    vrt.dblVal = from_num64_cast<double>(val);
                    vrt.vt = VT_R8;
                    break;}
                case TYPE_FLOAT:{
                    vrt.fltVal = from_num64_cast<float>(val);
                    vrt.vt = VT_R4;
                    break;}
                default:{
                    vrt.llVal = from_num64_cast<num32 > (val);
                    vrt.vt = VT_I4;}}
            return true;}

        bool cast_dvnci_by_oletype(const VARIANT& vrt, num64& val, num64& tp) {
            switch (vrt.vt) {
                case VT_BOOL:{
                    tp = TYPE_DISCRET;
                    val = num64_cast<bool>(vrt.boolVal);
                    break;}
                case VT_I8:{
                    tp = TYPE_NUM64;
                    val = num64_cast<num64 > (vrt.llVal);
                    break;}
                case VT_UI8:{
                    tp = TYPE_UNUM64;
                    val = num64_cast<unum64 > (vrt.ullVal);
                    break;}
                case VT_I4:{
                    tp = TYPE_NUM32;
                    val = num64_cast<num32 > (vrt.lVal);
                    break;}
                case VT_UI4:{
                    tp = TYPE_UNUM32;
                    val = num64_cast<unum32 > (vrt.ulVal);
                    break;}
                case VT_I2:{
                    tp = TYPE_NUM16;
                    val = num64_cast<num16 > (vrt.iVal);
                    break;}
                case VT_UI2:{
                    tp = TYPE_UNUM16;
                    val = num64_cast<unum16 > (vrt.uiVal);
                    break;}
                case VT_I1:{
                    tp = TYPE_NUM8;
                    val = num64_cast<num8 > (vrt.cVal);
                    break;}
                case VT_UI1:{
                    tp = TYPE_UNUM8;
                    val = num64_cast<unum8 > (vrt.bVal);
                    break;}
                case VT_R8:{
                    tp = TYPE_DOUBLE;
                    val = num64_cast<double>(vrt.dblVal);
                    break;}
                case VT_R4:{
                    tp = TYPE_FLOAT;
                    val = num64_cast<float>(vrt.fltVal);
                    break;}
                default:{
                    tp = TYPE_NODEF;
                    val = num64_cast<double>(vrt.dblVal);
                    break;}}
            return true;}

        VARTYPE oletype_by_dvncitype(num64 tp) {
            switch (tp) {
                case TYPE_DISCRET: return VT_BOOL;
                case TYPE_NUM64: return VT_I8;
                case TYPE_UNUM64: return VT_UI8;
                case TYPE_NUM32: return VT_I4;
                case TYPE_UNUM32: return  VT_UI4;
                case TYPE_NUM16: return  VT_I2;
                case TYPE_UNUM16: return VT_UI2;
                case TYPE_NUM8: return  VT_I1;
                case TYPE_UNUM8: return  VT_UI1;
                case TYPE_DOUBLE: return  VT_R8;
                case TYPE_FLOAT: return  VT_R4;
                default:{
                    return VT_EMPTY;}}
            return VT_EMPTY;}

        num64 dvnci_dt_fromft(FILETIME tm) {
            return castnum64_from_datetime(boost::posix_time::from_ftime<boost::posix_time::ptime>(tm));}

        vlvtype dvnci_quality(WORD q) {
            return (q==OPC_QUALITY_GOOD) ? 100 : 0;}

	ns_error opcerror_to_dvncierror(HRESULT vl){
			switch(vl){
				case OPC_E_INVALIDITEMID: return ERROR_BINDING;
				case OPC_E_UNKNOWNITEMID: return ERROR_NOFIND_REMOTEITEM;
				case OPC_E_BADTYPE: return ERROR_TYPENOCAST;
				default : return NS_ERROR_NODEF;}
            return NS_ERROR_NODEF;}

    const ns_error ERROR_NOFIND_REMOTEITEM = 0x20C;
 	// тип тега не может быть приведен к требуемому
    const ns_error ERROR_TYPENOCAST = 0x20D;
    
    
        class Callback : public IOPCDataCallback {
        public:

            Callback(opcintf * const opcsimpl_) : opcsimpl(opcsimpl_) {
                m_ulRefs = 1;}

            STDMETHODIMP QueryInterface(REFIID iid, LPVOID* ppInterface) {
                if (ppInterface == NULL) {
                    return E_INVALIDARG;}

                if (iid == IID_IUnknown) {
                    *ppInterface = dynamic_cast<IUnknown*> (this);
                    AddRef();
                    return S_OK;}

                if (iid == IID_IOPCDataCallback) {
                    *ppInterface = dynamic_cast<IOPCDataCallback*> (this);
                    AddRef();
                    return S_OK;}

                return E_NOINTERFACE;}

            STDMETHODIMP_(ULONG) AddRef() {
                return InterlockedIncrement((LONG*) & m_ulRefs);}

            STDMETHODIMP_(ULONG) Release() {
                ULONG ulRefs = InterlockedDecrement((LONG*) & m_ulRefs);
                if (ulRefs == 0) {
                    delete this;
                    return 0;}
                return ulRefs;}

            STDMETHODIMP OnDataChange(
                    DWORD dwTransid,
                    OPCHANDLE hGroup,
                    HRESULT hrMasterquality,
                    HRESULT hrMastererror,
                    DWORD dwCount,
                    OPCHANDLE * phClientItems,
                    VARIANT * pvValues,
                    WORD * pwQualities,
                    FILETIME * pftTimeStamps,
                    HRESULT * pErrors) {
                //THD_EXCLUSIVE_LOCK(opcsimpl->mutex);
                num64 tp=0;
                num64 val=0;
                for (DWORD i = 0; i < dwCount; i++) {
                    if (cast_dvnci_by_oletype(pvValues[i], val, tp))
                            opcsimpl->write_val_id(static_cast<indx>(phClientItems[i]),
                            short_value(val , tp, dvnci_quality(pwQualities[i]), 0 ));}
                    opcsimpl->update_dog();
                return S_OK;}

            STDMETHODIMP OnReadComplete(
                    DWORD dwTransid,
                    OPCHANDLE hGroup,
                    HRESULT hrMasterquality,
                    HRESULT hrMastererror,
                    DWORD dwCount,
                    OPCHANDLE * phClientItems,
                    VARIANT * pvValues,
                    WORD * pwQualities,
                    FILETIME * pftTimeStamps,
                    HRESULT * pErrors) {
                num64 tp=0;
                num64 val=0;
                for (DWORD i = 0; i < dwCount; i++) {
                    if (cast_dvnci_by_oletype(pvValues[i], val, tp))
                            opcsimpl->write_val_id(static_cast<indx>(phClientItems[i]),
                            short_value(val , tp, dvnci_quality(pwQualities[i]), 0 ));}
                    opcsimpl->update_dog();
                return S_OK;}

            STDMETHODIMP OnWriteComplete(
                    DWORD dwTransid,
                    OPCHANDLE hGroup,
                    HRESULT hrMastererr,
                    DWORD dwCount,
                    OPCHANDLE * pClienthandles,
                    HRESULT * pErrors) {
                opcsimpl->writetransaction_ok(dwTransid);
                return S_OK;}

            STDMETHODIMP OnCancelComplete(
                    DWORD dwTransid,
                    OPCHANDLE hGroup) {
                opcsimpl->readtransaction_cancel(dwTransid);
                opcsimpl->writetransaction_cancel(dwTransid);
                return S_OK;}

        private:


            opcintf * const opcsimpl;
            ULONG m_ulRefs;} ;


        class opc_util : public abstract_opc_util {
        public:

            opc_util(opcintf * const opcsimpl_, std::wstring name_, std::wstring group_ = L"", std::wstring host_ = L"", float db_ = 0.1, DWORD UpdateRate_ = 1000) : abstract_opc_util(),
            opcsimpl(opcsimpl_), init_(false), advice_(false), name(name_), group(group_), host(host_), db(db_), UpdateRate(UpdateRate_) {
                dwAdvise = NULL;
                hGroup = NULL;
                ISRV_ = NULL;
                IGRPMGT_ = NULL;
                SIO_ = NULL;
                SIO2_ = NULL;
                ASIO_ = NULL;
                ASIO2_ = NULL;
                ASIO3_ = NULL;
                ICONPTR_ = NULL;
                ipCallback = NULL;}

            virtual ~opc_util() {
                resetinit();}

            IOPCServer * const ISRV() {
                return ISRV_;};

            IOPCItemMgt * const IGRPMGT() {
                return IGRPMGT_;};

            IOPCSyncIO * const SIO() {
                return SIO_;};

            IOPCSyncIO2 * const SIO2() {
                return SIO2_;};

            IOPCAsyncIO * const ASIO() {
                return ASIO_;};

            IOPCAsyncIO2 * const ASIO2() {
                return ASIO2_;};

            IOPCAsyncIO3 * const ASIO3() {
                return ASIO3_;};

            IConnectionPoint * const ICONPTR() {
                return ICONPTR_;};

            virtual bool setinit() {

                if (FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED))) return false;

                CLSID cClsid = GUID_NULL;

                if (FAILED(CLSIDFromProgID(name.c_str(), &cClsid))) {
                    return false;}
                COSERVERINFO cInfo;

                memset(&cInfo, 0, sizeof (cInfo));


                cInfo.pwszName = const_cast<wchar_t*> (host.c_str());
                cInfo.pAuthInfo = NULL;
                cInfo.dwReserved1 = NULL;
                cInfo.dwReserved2 = NULL;


                MULTI_QI cResults;
                memset(&cResults, 0, sizeof (cResults));

                cResults.pIID = &IID_IOPCServer;
                cResults.pItf = NULL;
                cResults.hr = S_OK;


                HRESULT hResult = CoCreateInstanceEx(cClsid,
                        NULL,
                        CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER,
                        &cInfo,
                        1,
                        &cResults);

                if (FAILED(hResult)) {
                    return false;}


                if (FAILED(cResults.hr)) {
                    return false;}

                ISRV_ = (IOPCServer*) cResults.pItf;

                hGroup = 0;
                DWORD dwRevisedUpdateRate = 0;

                IGRPMGT_ = NULL;

                hResult = ISRV_->AddGroup(
                        group.c_str(),
                        TRUE,
                        UpdateRate, // 1 second update rate.
                        NULL,
                        NULL,
                        &db,
                        LOCALE_SYSTEM_DEFAULT,
                        &hGroup,
                        &dwRevisedUpdateRate,
                        IID_IOPCItemMgt,
                        (IUnknown**) & IGRPMGT_);

                if (FAILED(hResult)) {
                    ISRV_->Release();
                    return false;}



                bool findintrf = false;

                SIO_ = NULL;
                hResult = IGRPMGT_->QueryInterface(IID_IOPCSyncIO, (void**) &SIO_);
                if (FAILED(hResult)) {
                    SIO_ = NULL;}
                else {
                    findintrf = true;}

                SIO2_ = NULL;
                hResult = IGRPMGT_->QueryInterface(IID_IOPCSyncIO2, (void**) &SIO2_);
                if (FAILED(hResult)) {
                    SIO2_ = NULL;}
                else {
                    findintrf = true;}

                ASIO_ = NULL;
                hResult = IGRPMGT_->QueryInterface(IID_IOPCAsyncIO, (void**) &ASIO_);
                if (FAILED(hResult)) {
                    ASIO_ = NULL;}
                else {
                    findintrf = true;}

                ASIO2_ = NULL;
                hResult = IGRPMGT_->QueryInterface(IID_IOPCAsyncIO2, (void**) &ASIO2_);
                if (FAILED(hResult)) {
                    ASIO2_ = NULL;}
                else {
                    findintrf = true;}

                ASIO3_ = NULL;
                hResult = IGRPMGT_->QueryInterface(IID_IOPCAsyncIO3, (void**) &ASIO3_);
                if (FAILED(hResult)) {
                    ASIO3_ = NULL;}
                else {
                    findintrf = true;}

                IConnectionPointContainer* ICONPTRC_ = NULL;

                hResult = IGRPMGT_->QueryInterface(IID_IConnectionPointContainer, (void**) &ICONPTRC_);

                if (!FAILED(hResult)) {
                    ICONPTR_ = NULL;

                    hResult = ICONPTRC_->FindConnectionPoint(IID_IOPCDataCallback, &ICONPTR_);

                    if (!FAILED(hResult)) {
                        findintrf = true;}
                    else {
                        ICONPTR_ = NULL;}
                    ICONPTRC_->Release();}
                else {
                    ICONPTR_ = NULL;}

                if (!findintrf) {
                    IGRPMGT_->Release();
                    if ((hGroup) && (ISRV_)) ISRV_->RemoveGroup(hGroup, TRUE);
                    hGroup = 0;
                    ISRV_->Release();
                    return false;}
                init_ = true;
                return true;}

            virtual bool resetinit() {
                if (init_) {
                    resetadvice();
                    if (SIO_) SIO_->Release();
                    if (SIO2_) SIO2_->Release();
                    if (ASIO_) ASIO_->Release();
                    if (ASIO2_) ASIO2_->Release();
                    if (ASIO3_) ASIO3_->Release();
                    if (IGRPMGT_) IGRPMGT_->Release();
                    if ((hGroup) && (ISRV_)) ISRV_->RemoveGroup(hGroup, TRUE);
                    if (ISRV_) ISRV_->Release();}
                CoUninitialize();
                init_ = false;
                return true;}

            virtual bool setadvice(bool& actadv) {
                if (!init_) return false;
                if (!ICONPTR_) return false;
                if (advice_) return false;
                ipCallback = new Callback(opcsimpl);
                dwAdvise = NULL;
                HRESULT hResult = ICONPTR_->Advise(ipCallback, &dwAdvise);
                if (FAILED(hResult)) {
                    if (ipCallback) ipCallback->Release();
                    return false;}
                if (ASIO2_) {
                    HRESULT hResultA = ASIO2_->SetEnable(actadv);
                    if (FAILED(hResultA)) {
                        actadv = false;}}
                else return false;
                advice_ = true;
                return true;}

            virtual bool resetadvice() {
                if (!ICONPTR_) return false;
                if (dwAdvise)
                    ICONPTR_->Unadvise(dwAdvise);
                dwAdvise = NULL;
                if (ipCallback)
                    ipCallback->Release();
                if (ICONPTR_)
                    ICONPTR_->Release();
                advice_ = false;
                return true;}

            virtual int native_ver() {
                if ((ISRV_) && (IGRPMGT_) && (ASIO3_) && (SIO2_)) return 3;
                if ((ISRV_) && (IGRPMGT_) && (ASIO2_) && (SIO_)) return 2;
                if ((ISRV_) && (IGRPMGT_) && (ASIO_) && (SIO_)) return 1;
                return 0;}

            virtual int kindcange() {
                int tmpver = native_ver();
                if (tmpver == 0) return NONEOPC;
                if ((tmpver == 1) || (!ICONPTR_)) return SYNOPC;
                if (tmpver == 2) return (SUBSCROPC | ASYNOPC | SYNOPC);
                if (tmpver == 3) return (SUBSCROPC | ASYNOPC | SYNOPC);
                return NONEOPC;}

            virtual bool isasync() {
                return ICONPTR_;}


        private:

            opcintf * const opcsimpl;
            bool init_;
            bool advice_;

            std::wstring name;
            std::wstring group;
            std::wstring host;
            float db;
            DWORD UpdateRate;

            DWORD dwAdvise;
            OPCHANDLE hGroup;
            IOPCServer* ISRV_;
            IOPCItemMgt* IGRPMGT_;
            IOPCSyncIO* SIO_;
            IOPCSyncIO2* SIO2_;
            IOPCAsyncIO* ASIO_;
            IOPCAsyncIO2* ASIO2_;
            IOPCAsyncIO3* ASIO3_;
            IConnectionPoint* ICONPTR_;
            Callback* ipCallback;} ;



        opcintf::~opcintf() {
            disconnect();};

        bool opcintf::connect() {

            if (!intf) return false;
            if (!intf->groups()->exists(group())) return false;


            DEBUG_VAL_DVNCI(intf->groups()->server(group()))

            std::string szProgID = intf->groups()->server(group());
            std::wstring szProgIDw = s2ws(szProgID);
            std::string szHostName = intf->groups()->host(group());
            std::wstring szHostNamew = s2ws(szHostName);
            std::string szGroupName = intf->groups()->group(group());
            std::wstring szGroupNamew = s2ws(szGroupName);

            ver = intf->groups()->ver(group());
            connecttype = intf->groups()->synctype(group());
            //usehda = static_cast<popcgroupstruct> (intf->groups()->config(group))->usehda();
            deadband = static_cast<float> (intf->groups()->deadbound(group()));
            //updaterate = static_cast<DWORD> (intf->groups()->grouprate(group));
            maintimeout = static_cast<num32> (intf->groups()->timeout(group()));
            tracttimeout = maintimeout*9/10;
            if (updaterate<99) updaterate = 100;

            abstr_opc_util_ptr tmpinf = abstr_opc_util_ptr(new opc_util(this, szProgIDw, szGroupNamew, szHostNamew, deadband, updaterate));
            if (!tmpinf->setinit()) return false;
            opc_spec = tmpinf;

            if (ver == 0 )
                ver = opc_spec->native_ver();

            DEBUG_STR_VAL_DVNCI(NATIV_VER, opc_spec->native_ver());

            if (ver > opc_spec->native_ver())
                ver = opc_spec->native_ver();

            if (ver > 2) ver = 2;


            if ((ver == 1) || (!opc_spec->isasync())) {
                connecttype = CONTYPE_SYNOPC;}


            if (connecttype!=CONTYPE_SYNOPC) {
                bool tmpadv = (connecttype==CONTYPE_SUBSCROPC);
                if (opc_spec->setadvice(tmpadv)) {
                    if (tmpadv!=(connecttype==CONTYPE_SUBSCROPC)) {
                        connecttype = CONTYPE_ASYNOPC;
                        DEBUG_STR_VAL_DVNCI(reset connecttype Bad, connecttype);}
                    else {
                        DEBUG_STR_VAL_DVNCI(set connecttype Ok!, connecttype);};}
                else {
                    DEBUG_STR_VAL_DVNCI(cant set connecttype set sync, connecttype);
                    connecttype = CONTYPE_SYNOPC;}}
            else {
                DEBUG_STR_VAL_DVNCI(set connecttype sync OK!, connecttype);};

            DEBUG_STR_VAL_DVNCI(versionopc, ver)
            DEBUG_STR_VAL_DVNCI(opcconntype, connecttype)
            DEBUG_VAL_DVNCI(updaterate)
            DEBUG_VAL_DVNCI(deadband)

            state_ = connected;

            return true;}

        bool opcintf::disconnect() {

            if (state_ == connected) {
                ver = 0;
                if (opc_spec)
                    opc_spec.reset();
                state_ = disconnected;}
            return true;}

        bool opcintf::checkserverstatus() const{
            if ((!opc_spec) || (!static_cast<opc_util*> (opc_spec.get())->IGRPMGT())) return false;
            OPCSERVERSTATUS status;
            OPCSERVERSTATUS* pstatus = &status;
            HRESULT hResult = static_cast<opc_util*> (opc_spec.get())->ISRV()->GetStatus(&pstatus);

            if (FAILED(hResult)) {
                return false;}

            if (status.dwServerState==OPC_STATUS_RUNNING) return true;
            return false;}
        
        
        

        ns_error opcintf::add_request_impl() {


            checkserverstatus();

            DWORD dwCount = need_add_set.size();
            OPCITEMDEF* pItems = (OPCITEMDEF*) CoTaskMemAlloc(dwCount * sizeof (OPCITEMDEF)); // need free
            OPCITEMRESULT* pResults = NULL; // need free
            HRESULT* pErrors = NULL; // need free

            memset(pItems, 0, sizeof (OPCITEMDEF) * dwCount);

            DWORD i = 0;

            //typedef std::vector<std::wstring> tempwstring;

            //wstring tmpwstr = L"";

            for (indx_set::const_iterator it = need_add_set.begin(); it != need_add_set.end(); ++it) {
                if (intf->exists(*it)) {
//                   opcclient_item itm;
//                    if (!find_by_clid(it->key, itm)) {
                     //tmpwstr.push_back(s2ws(intf->binding(*it).));
                     //pItems[i].szItemID = const_cast<wchar_t*> (tmpwstr.back().c_str());
                     pItems[i].szAccessPath = NULL;
                     pItems[i].bActive = TRUE;
                     pItems[i].hClient = static_cast<OPCHANDLE> (*it);
                     pItems[i].vtRequestedDataType = oletype_by_dvncitype(intf->type(*it));
                     pItems[i].dwBlobSize = 0;
                     pItems[i].pBlob = NULL;
                     i++;}
                    else {
                     req_error(*it, ERROR_ENTNOEXIST);    
                     dwCount--;}}

            if (dwCount > 0) {
                HRESULT hResult = static_cast<opc_util*> (opc_spec.get())->IGRPMGT()->
                        AddItems(dwCount, pItems, &pResults, &pErrors);

                if (FAILED(hResult)) {
                    CoTaskMemFree(pItems); // free
                    CoTaskMemFree(pResults); // free
                    CoTaskMemFree(pErrors); // free
                    return false;}


                for (DWORD i = 0; i < dwCount; i++) {
                    if (pErrors[i] != S_OK) {
                        /*req_error(*it, ERROR_ENTNOEXIST)*/;}
                    else {
                        add_simple(static_cast<indx>(pItems[i].hClient), pResults[i].hServer);}
                    if (pResults[i].dwBlobSize > 0) CoTaskMemFree(pResults[i].pBlob);}}

            CoTaskMemFree(pItems); // free
            CoTaskMemFree(pResults); // free
            CoTaskMemFree(pErrors); // free


            //if (!activateclientitem.empty()) {
            //    cnangeactiveItems(activateclientitem, serveritem, errors, true);}

            update_dog();

            return true;}

        bool opcintf::cnangeactiveItems() {

            /*DWORD dwCount = chitem.size();
            OPCHANDLE* phServer = (OPCHANDLE*) CoTaskMemAlloc(dwCount * sizeof (OPCHANDLE)); // need free
            BOOL bActive = active ? TRUE : FALSE;
            HRESULT* pErrors = NULL; // need free

            memset(phServer, 0, sizeof (OPCHANDLE) * dwCount);

            DWORD i = 0;


            for (indx_vect::const_iterator it = chitem.begin(); it != chitem.end(); ++it) {
                if (find_by_sid(*it)) {
                    if (active) DEBUG_STR_DVNCI(ACTIVATE) else DEBUG_STR_DVNCI(DEACTIVATE)
                        DEBUG_VAL_DVNCI(*it)
                        phServer[i++] = static_cast<OPCHANDLE> (*it);}
                else {
                    dwCount--;}}

            if (dwCount > 0) {
                HRESULT hResult = static_cast<opc_util*> (opc_spec.get())->IGRPMGT()->SetActiveState(
                        dwCount,
                        phServer,
                        bActive,
                        &pErrors);

                if (FAILED(hResult)) {
                    CoTaskMemFree(phServer); // free
                    CoTaskMemFree(pErrors); // free  
                    return false;}

                for (DWORD i = 0; i < dwCount; i++) {
                    if (pErrors[i] == S_OK) {
                        opcclient_item itm;
                        if (find_by_sid(phServer[i], itm)) {
                            opcclient_item tmpitm = {itm.key, phServer[i], 0};
                            serveritem.push_back(tmpitm);}}}
                dwCount = 0;}

            CoTaskMemFree(phServer); // free
            CoTaskMemFree(pErrors); // free*/
            return true;}

        ns_error opcintf::remove_request_impl(){
            return cnangeactiveItems();}


        ns_error opcintf::value_request_impl(){
            if (ver == 1) {
                read_valuesSync1();}
            else {
                switch (connecttype) {
                    case CONTYPE_SYNOPC:{
                        read_valuesSync1();
                        break;}
                    case CONTYPE_ASYNOPC:{
                        if (!isreadtransaction()) {
                            read_valuesASync2();}
                        else {
                            DWORD tsttransact = 0;
                            if (isreadexpiretimout(tracttimeout, tsttransact)) {
                                DEBUG_STR_DVNCI(NEEDCANCELEDREADTRANSACT);
                                cancelTransact(tsttransact);}
                            else {
                                ;}}
                        break;}}}
            return 0;}
        

        bool opcintf::read_valuesSync1() {

            DWORD dwCount = simple_req_map.left.size();
            OPCHANDLE* phServer = (OPCHANDLE*) CoTaskMemAlloc(dwCount * sizeof (OPCHANDLE)); // need free
            OPCITEMSTATE* ppItemValues = NULL; // need free
            HRESULT* pErrors = NULL; // need free

            memset(phServer, 0, sizeof (OPCHANDLE) * dwCount);

            DWORD i = 0;

            for (serverkey_const_iterator it = simple_req_map.left.begin(); it != simple_req_map.left.end(); ++it) {
                    //DEBUG_STR_DVNCI(ADDITEM SYNCREAD1);
                    phServer[i++] = static_cast<OPCHANDLE> (it->first);}

            if (dwCount > 0) {

                HRESULT hResult = static_cast<opc_util*> (opc_spec.get())->SIO()->Read(
                        OPC_DS_CACHE,
                        dwCount,
                        phServer,
                        &ppItemValues,
                        &pErrors);

                if (FAILED(hResult)) {
                    CoTaskMemFree(phServer); // free
                    CoTaskMemFree(ppItemValues); // free
                    CoTaskMemFree(pErrors); // free
                    return false;}


                num64 tp=0;
                num64 val=0;
                for (DWORD i = 0; i < dwCount; i++) {
                    if (pErrors[i] == S_OK) {
                        if (cast_dvnci_by_oletype(ppItemValues[i].vDataValue, val, tp))
                            write_val_id(static_cast<indx>(ppItemValues[i].hClient),
                            short_value(val , tp, dvnci_quality(ppItemValues[i].wQuality), 0 /*,
                                dvnci_dt_fromft(ppItemValues[i].ftTimeStamp)*/));}}}

            CoTaskMemFree(phServer); // free
            CoTaskMemFree(ppItemValues); // free
            CoTaskMemFree(pErrors); // free
            update_dog();
            return true;}

        bool opcintf::read_valuesASync2() {

            DWORD dwCount = simple_req_map.left.size();
            OPCHANDLE* phServer = (OPCHANDLE*) CoTaskMemAlloc(dwCount * sizeof (OPCHANDLE)); // need free
            DWORD      dwTransactionID = transactid();
            DWORD      pdwCancelID = 0;
            HRESULT*   pErrors = NULL; // need free


            memset(phServer, 0, sizeof (OPCHANDLE) * dwCount);

            DWORD i = 0;

            for (serverkey_const_iterator it = simple_req_map.left.begin(); it != simple_req_map.left.end(); ++it) {
                    //DEBUG_STR_DVNCI(ADDITEM SYNCREAD1);
                    phServer[i++] = static_cast<OPCHANDLE> (it->first);}

            if (dwCount > 0) {

                HRESULT hResult = static_cast<opc_util*> (opc_spec.get())->ASIO2()->Read(
                        dwCount,
                        phServer,
                        dwTransactionID,
                        &pdwCancelID,
                        &pErrors);

                if (FAILED(hResult)) {
                    CoTaskMemFree(phServer); // free
                    CoTaskMemFree(pErrors); // free
                    return false;}

                addreadtransaction(dwTransactionID, pdwCancelID);

                DWORD errorcnt=0;

                for (DWORD i = 0; i < dwCount; i++) {
                    if (pErrors[i] != S_OK) {
                        errorcnt++;}}
                
             if (errorcnt<dwCount) addreadtransaction(dwTransactionID, pdwCancelID);}

            CoTaskMemFree(phServer); // free
            CoTaskMemFree(pErrors); // free
            return true;}

        ns_error opcintf::command_request_impl(const sidcmd_map& cmd) {
            if (ver == 1) {
                setValuesSync1(cmd);}
            else {
                switch (connecttype) {
                    case CONTYPE_SYNOPC:{
                        setValuesSync1(cmd);
                        break;}
                    case CONTYPE_SUBSCROPC:
                    case CONTYPE_ASYNOPC:{
                        if (!iswritetransaction()) {
                           setValuesASync2(cmd);}
                        else{
                            DWORD tsttransact = 0;
                            if (iswriteexpiretimout(tracttimeout, tsttransact)) {
                                DEBUG_STR_DVNCI(NEEDCANCELEDREADTRANSACT);
                                cancelTransact(tsttransact);}
                            else {
                                ;}}
                        break;};}}
            return 0;}

        bool opcintf::setValuesSync1(const sidcmd_map& cmd) {

            /*DWORD dwCount = commanditem.size();
            OPCHANDLE* phServer = (OPCHANDLE*) CoTaskMemAlloc(dwCount * sizeof (OPCHANDLE)); // need free
            VARIANT* phItemValues = (VARIANT*) CoTaskMemAlloc(dwCount * sizeof (VARIANT)); // need free
            HRESULT* pErrors = NULL; // need free

            memset(phServer, 0, sizeof (OPCHANDLE) * dwCount);
            memset(phItemValues, 0, sizeof (VARIANT) * dwCount);

            DWORD i = 0;

            for (vect_opccommand_item::const_iterator it = commanditem.begin(); it != commanditem.end(); ++it) {
                VARIANT tmpvariant;

                if ((find_by_sid(it->outkey)) &&
                        (cast_oletype_by_dvnci(it->val, it->type, tmpvariant))) {
                    DEBUG_STR_DVNCI(ADDITEM SYNCWRITE1);
                    phServer[i] = static_cast<OPCHANDLE> (it->outkey);
                    phItemValues[i] = tmpvariant;
                    i++;}
                else {
                    dwCount--;}}

            if (dwCount > 0) {

                HRESULT hResult = static_cast<opc_util*> (opc_spec.get())->SIO()->Write(
                        dwCount,
                        phServer,
                        phItemValues,
                        &pErrors);

                if (FAILED(hResult)) {
                    CoTaskMemFree(phServer); //free
                    CoTaskMemFree(phItemValues); //free
                    CoTaskMemFree(pErrors); //free
                    return false;}


                for (DWORD i = 0; i < dwCount; i++) {
                    if (pErrors[i] == S_OK) {}}}

            CoTaskMemFree(phServer); //free
            CoTaskMemFree(phItemValues); //free
            CoTaskMemFree(pErrors); //free*/
            update_dog();
            return true;}

        bool opcintf::setValuesASync2(const sidcmd_map& cmd) {

            /*DWORD dwCount = commanditem.size();
            OPCHANDLE* phServer = (OPCHANDLE*) CoTaskMemAlloc(dwCount * sizeof (OPCHANDLE)); // need free
            VARIANT* phItemValues = (VARIANT*) CoTaskMemAlloc(dwCount * sizeof (VARIANT)); // need free
            DWORD      dwTransactionID = transactid();
            DWORD      pdwCancelID = 0;
            HRESULT* pErrors = NULL; // need free

            memset(phServer, 0, sizeof (OPCHANDLE) * dwCount);
            memset(phItemValues, 0, sizeof (VARIANT) * dwCount);

            DWORD i = 0;

            for (vect_opccommand_item::const_iterator it = commanditem.begin(); it != commanditem.end(); ++it) {
                VARIANT tmpvariant;

                if ((find_by_sid(it->outkey)) &&
                        (cast_oletype_by_dvnci(it->val, it->type, tmpvariant))) {

                    phServer[i] = static_cast<OPCHANDLE> (it->outkey);
                    phItemValues[i] = tmpvariant;
                    i++;}
                else {
                    dwCount--;}}

            if (dwCount > 0) {

                HRESULT hResult = static_cast<opc_util*> (opc_spec.get())->ASIO2()->Write(
                        dwCount,
                        phServer,
                        phItemValues,
                        dwTransactionID,
                        &pdwCancelID,
                        &pErrors);

                if (FAILED(hResult)) {
                    CoTaskMemFree(phServer); //free
                    CoTaskMemFree(phItemValues); //free
                    CoTaskMemFree(pErrors); //free
                    return false;}

                DWORD errorcnt=0;

                for (DWORD i = 0; i < dwCount; i++) {
                    if (pErrors[i] != S_OK) {
                        errorcnt++;
                        DEBUG_STR_DVNCI(ASYNCWRITE1 ERR);}}
                if (errorcnt<dwCount)  addwritetransaction(dwTransactionID, pdwCancelID);}

            CoTaskMemFree(phServer); //free
            CoTaskMemFree(phItemValues); //free
            CoTaskMemFree(pErrors); //free*/
            return true;}

        bool opcintf::cancelTransact(DWORD tract) {
            HRESULT hResult = static_cast<opc_util*> (opc_spec.get())->ASIO2()->Cancel2(tract);
            if (FAILED(hResult)) {
                DEBUG_STR_DVNCI(FAIL CANCEL);}
            else DEBUG_STR_DVNCI(SUCCESS CANCEL);
            return true;}}}}
