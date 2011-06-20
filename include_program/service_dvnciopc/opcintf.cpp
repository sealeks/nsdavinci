/* 
 * File:   netintf.cpp
 * Author: Serg
 * 
 * Created on 20 Р В РїС—Р…Р РЋР вЂ№Р В Р’В»Р РЋР Р‰ 2010 Р В РЎвЂ“., 14:24
 */

#include "opcintf.h"

#include <opc/opcda_i.c>
#include <opc/opcerror.h>


#include <boost/date_time/posix_time/posix_time.hpp>



namespace dvnci {
    namespace external {
        namespace opc {

            ///  util function

            std::wstring string_to_wstring(const std::string& s, UINT cp = CP_UTF8) {
                std::string::size_type slength =  s.length() + 1;
                std::string::size_type len = MultiByteToWideChar(cp, 0, s.c_str(), slength, 0, 0);
                wchar_t* buf = new wchar_t[len];
                MultiByteToWideChar(cp, 0, s.c_str(), slength, buf, len);
                std::wstring r(buf);
                delete[] buf;
                return r;}

            vlvtype valid_from_quality(WORD q) {
                return (q == OPC_QUALITY_GOOD) ? FULL_VALID : NULL_VALID;}
            
            datetime dt_from_filetime(const FILETIME& tm) {
            return boost::posix_time::from_ftime<boost::posix_time::ptime>(tm);}

            VARTYPE oletype(tagtype tp) {
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
                    case TYPE_TEXT: return  VT_LPWSTR;
                    case TYPE_TIME: return  VT_FILETIME;
                    case TYPE_NODEF: return  VT_R8;
                    default:{
                        return VT_EMPTY;}}
                return VT_EMPTY;}

            ns_error from_opcerror(HRESULT vl) {
                switch (vl) {
                    case OPC_E_INVALIDITEMID: return ERROR_BINDING;
                    case OPC_E_UNKNOWNITEMID: return ERROR_NOFIND_REMOTEITEM;
                    case OPC_E_BADTYPE: return ERROR_TYPENOCAST;
                    default: return NS_ERROR_NODEF;}
                return NS_ERROR_NODEF;}

            VARIANT to_oletype_cast(const short_value& val) {
                VARIANT vrt;
                vrt.vt = oletype(val.type());
                switch (val.type()) {
                    case TYPE_DISCRET:{
                        vrt.boolVal = val.value<bool>();
                        break;}
                    case TYPE_NUM64:{
                        vrt.llVal = val.value<num64 > ();
                        break;}
                    case TYPE_UNUM64:{
                        vrt.ullVal = val.value<unum64 > ();
                        break;}
                    case TYPE_NUM32:{
                        vrt.lVal = val.value<num32 > ();
                        break;}
                    case TYPE_UNUM32:{
                        vrt.ulVal = val.value<unum32 > ();
                        break;}
                    case TYPE_NUM16:{
                        vrt.iVal = val.value<num16 > ();
                        break;}
                    case TYPE_UNUM16:{
                        vrt.uiVal = val.value<unum16 > ();
                        break;}
                    case TYPE_NUM8:{
                        vrt.cVal = val.value<num8 > ();
                        break;}
                    case TYPE_UNUM8:{
                        vrt.bVal = val.value<unum8 > ();
                        break;}
                    case TYPE_DOUBLE:{
                        vrt.dblVal = val.value<unum8 > ();
                        break;}
                    case TYPE_FLOAT:{
                        vrt.fltVal = val.value<double>();
                        break;}
                    case TYPE_NODEF:{
                        vrt.dblVal = val.value<double>();
                        break;}
                    default:{
                        vrt.llVal = 0;
                        vrt.vt = VT_ILLEGAL;}}
                return vrt;}

            short_value from_oletype_cast(const VARIANT& vrt, const WORD& quo, const FILETIME& tm) {
                switch (vrt.vt) {
                    case VT_BOOL:{
                        short_value vl(static_cast<bool> (vrt.boolVal));
                        vl.valid(valid_from_quality(quo));
                        vl.time(dt_from_filetime(tm));
                        return vl;}
                    case VT_I8:{
                        short_value vl(static_cast<num64> (vrt.llVal));
                        vl.valid(valid_from_quality(quo));
                        vl.time(dt_from_filetime(tm));
                        return vl;}
                    case VT_UI8:{
                        short_value vl(static_cast<unum64> (vrt.ullVal));
                        vl.valid(valid_from_quality(quo));
                        vl.time(dt_from_filetime(tm));
                        return vl;}
                    case VT_I4:{
                        short_value vl(static_cast<num32> (vrt.lVal));
                        vl.valid(valid_from_quality(quo));
                        vl.time(dt_from_filetime(tm));
                        return vl;}
                    case VT_UI4:{
                        short_value vl(static_cast<unum32> (vrt.ulVal));
                        vl.valid(valid_from_quality(quo));
                        vl.time(dt_from_filetime(tm));
                        return vl;}
                    case VT_I2:{
                        short_value vl(static_cast<num16> (vrt.iVal));
                        vl.valid(valid_from_quality(quo));
                        vl.time(dt_from_filetime(tm));
                        return vl;}
                    case VT_UI2:{
                        short_value vl(static_cast<unum16> (vrt.uiVal));
                        vl.valid(valid_from_quality(quo));
                        vl.time(dt_from_filetime(tm));
                        return vl;}
                    case VT_I1:{
                        short_value vl(static_cast<num8> (vrt.cVal));
                        vl.valid(valid_from_quality(quo));
                        vl.time(dt_from_filetime(tm));
                        return vl;}
                    case VT_UI1:{
                        short_value vl(static_cast<unum8> (vrt.bVal));
                        vl.valid(valid_from_quality(quo));
                        vl.time(dt_from_filetime(tm));
                        return vl;}
                    case VT_R8:{
                        short_value vl(static_cast<double> (vrt.dblVal));
                        vl.valid(valid_from_quality(quo));
                        vl.time(dt_from_filetime(tm));
                        return vl;}
                    case VT_R4:{
                        short_value vl(static_cast<float> (vrt.fltVal));
                        vl.valid(valid_from_quality(quo));
                        vl.time(dt_from_filetime(tm));
                        return vl;}
                    default:{
                        return short_value();}}
                return short_value();}
            
            
            
            //transaction_mng_map

            bool transaction_mng_map::add(DWORD ok_transact, DWORD cancel_transact,  boost::xtime tm ) {
                if ((!find_by_cancel(cancel_transact)) && (!find_by_ok(ok_transact))) {
                    transactstruct tmp = { ok_transact , cancel_transact, tm };
                    ok_map.insert(dword_transact_pair(ok_transact, tmp));
                    cancel_map.insert(dword_transact_pair(cancel_transact, tmp));
                    return true;}
                return false;}

            bool transaction_mng_map::remove_by_cancel(DWORD cancel_transact) {
                dword_transact_map::iterator it = cancel_map.find(cancel_transact);
                if (it == cancel_map.end()) return false;
                DWORD ok_transact = it->second.ok_transact;
                cancel_map.erase(it->first);
                it = ok_map.find(ok_transact);
                if (it == ok_map.end()) return false;
                ok_map.erase(it->first);
                return true;}

            bool transaction_mng_map::remove_by_ok(DWORD ok_transact) {
                dword_transact_map::iterator it = ok_map.find(ok_transact);
                if (it == ok_map.end()) return false;
                DWORD cancel_transact = it->second.cancel_transact;
                ok_map.erase(it->first);
                it = cancel_map.find(cancel_transact);
                if (it == cancel_map.end()) return false;
                cancel_map.erase(it->first);
                return true;}

            bool transaction_mng_map::expiretimout(timeouttype tmo, DWORD& canceltract) {
                for (dword_transact_map::iterator it = ok_map.begin(); it != ok_map.end(); ++it) {
                    if (expire_from_utc_millsec(it->second.tm, tmo)) {
                        DWORD oktract = it->second.ok_transact;
                        transactstruct transacttmp;
                        if (find_by_ok(oktract, transacttmp)) {
                            canceltract = transacttmp.cancel_transact;
                            remove_by_ok(oktract);
                            return true;}
                        remove_by_ok(oktract);
                        return false;}}
                return false;}

            bool transaction_mng_map::find_by_cancel(DWORD cancel_transact, transactstruct& transact) {
                dword_transact_map::iterator it = cancel_map.find(cancel_transact);
                if (it == cancel_map.end()) return false;
                transact = it->second;
                return true;}

            bool transaction_mng_map::find_by_ok(DWORD ok_transact, transactstruct& transact) {
                dword_transact_map::iterator it = ok_map.find(ok_transact);
                if (it == ok_map.end()) return false;
                transact = it->second;
                return true;}





            //  callback interface

            class opc_callback : public IOPCDataCallback {
            public:

                opc_callback(opcintf * const opcsimpl_) : opcsimpl(opcsimpl_) {
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
                    for (DWORD i = 0; i < dwCount; i++) {
                        opcsimpl->write_val_id(static_cast<indx> (phClientItems[i]),
                                from_oletype_cast(pvValues[i], pwQualities[i], pftTimeStamps[i] ));}
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
                    for (DWORD i = 0; i < dwCount; i++) {
                        opcsimpl->write_val_id(static_cast<indx> (phClientItems[i]),
                                from_oletype_cast(pvValues[i], pwQualities[i], pftTimeStamps[i] ));}
					opcsimpl->readtransaction_ok(dwTransid);
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



            // opc_util

            class opc_util : public abstract_opc_util {

            public:

                opc_util(opcintf * const opcsimpl_, const std::wstring& nm, const std::wstring& grp = L"",
                        const std::wstring& hst = L"", double db_ = 0.1, DWORD UpdateRate_ = 1000) :
                abstract_opc_util(), opcsimpl(opcsimpl_), init_(false), advice_(false), name(nm),
                group(grp), host(hst), db(db_), UpdateRate(UpdateRate_), dwAdvise(0), hGroup(0),
                ISRV_(0), IGRPMGT_(0), SIO_(0), SIO2_(0), ASIO_(0), ASIO2_(0), ASIO3_(0),
                ICONPTR_(0), ipCallback(0) {}

                virtual ~opc_util() {
                    uninit();}

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

                virtual bool init() {

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

                    IGRPMGT_ = 0;

                    float db_flt = static_cast<float> (db);

                    hResult = ISRV_->AddGroup(
                            group.c_str(),
                            TRUE,
                            UpdateRate, // 1 second update rate.
                            NULL,
                            NULL,
                            &db_flt,
                            LOCALE_SYSTEM_DEFAULT,
                            &hGroup,
                            &dwRevisedUpdateRate,
                            IID_IOPCItemMgt,
                            (IUnknown**) & IGRPMGT_);

                    if (FAILED(hResult)) {
                        ISRV_->Release();
                        return false;}



                    bool findintrf = false;

                    SIO_ = 0;
                    hResult = IGRPMGT_->QueryInterface(IID_IOPCSyncIO, (void**) &SIO_);
                    if (FAILED(hResult)) {
                        SIO_ = 0;}
                    else {
                        findintrf = true;}

                    SIO2_ = 0;
                    hResult = IGRPMGT_->QueryInterface(IID_IOPCSyncIO2, (void**) &SIO2_);
                    if (FAILED(hResult)) {
                        SIO2_ = 0;}
                    else {
                        findintrf = true;}

                    ASIO_ = 0;
                    hResult = IGRPMGT_->QueryInterface(IID_IOPCAsyncIO, (void**) &ASIO_);
                    if (FAILED(hResult)) {
                        ASIO_ = 0;}
                    else {
                        findintrf = true;}

                    ASIO2_ = 0;
                    hResult = IGRPMGT_->QueryInterface(IID_IOPCAsyncIO2, (void**) &ASIO2_);
                    if (FAILED(hResult)) {
                        ASIO2_ = 0;}
                    else {
                        findintrf = true;}

                    ASIO3_ = 0;
                    hResult = IGRPMGT_->QueryInterface(IID_IOPCAsyncIO3, (void**) &ASIO3_);
                    if (FAILED(hResult)) {
                        ASIO3_ = 0;}
                    else {
                        findintrf = true;}

                    IConnectionPointContainer* ICONPTRC_ = 0;

                    hResult = IGRPMGT_->QueryInterface(IID_IConnectionPointContainer, (void**) &ICONPTRC_);

                    if (!FAILED(hResult)) {
                        ICONPTR_ = 0;

                        hResult = ICONPTRC_->FindConnectionPoint(IID_IOPCDataCallback, &ICONPTR_);

                        if (!FAILED(hResult)) {
                            findintrf = true;}
                        else {
                            ICONPTR_ = 0;}
                        ICONPTRC_->Release();}
                    else {
                        ICONPTR_ = 0;}

                    if (!findintrf) {
                        IGRPMGT_->Release();
                        if ((hGroup) && (ISRV_)) ISRV_->RemoveGroup(hGroup, TRUE);
                        hGroup = 0;
                        ISRV_->Release();
                        return false;}
                    init_ = true;
                    return true;}

                virtual bool uninit() {
                    if (init_) {
                        unadvice();
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

                virtual bool advice(bool& actadv) {
                    if (!init_) return false;
                    if (!ICONPTR_) return false;
                    if (advice_) return false;
                    ipCallback = new opc_callback(opcsimpl);
                    dwAdvise = 0;
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

                virtual bool unadvice() {
                    if (!ICONPTR_) return false;
                    if (dwAdvise)
                        ICONPTR_->Unadvise(dwAdvise);
                    dwAdvise = 0;
                    if (ipCallback) {
                        ipCallback->Release();}
                    if (ICONPTR_)
                        ICONPTR_->Release();
                    advice_ = false;
                    return true;}

                virtual intfvertype native_ver() const {
                    if ((ISRV_) && (IGRPMGT_) && (ASIO3_) && (SIO2_)) return 3;
                    if ((ISRV_) && (IGRPMGT_) && (ASIO2_) && (SIO_)) return 2;
                    if ((ISRV_) && (IGRPMGT_) && (ASIO_) && (SIO_)) return 1;
                    return 0;}

                virtual bool isasync() {
                    return ICONPTR_;}


            private:

                opcintf * const   opcsimpl;
                bool              init_;
                bool              advice_;

                std::wstring      name;
                std::wstring      group;
                std::wstring      host;
                double            db;
                DWORD             UpdateRate;
                DWORD             dwAdvise;
                OPCHANDLE         hGroup;
                IOPCServer*       ISRV_;
                IOPCItemMgt*      IGRPMGT_;
                IOPCSyncIO*       SIO_;
                IOPCSyncIO2*      SIO2_;
                IOPCAsyncIO*      ASIO_;
                IOPCAsyncIO2*     ASIO2_;
                IOPCAsyncIO3*     ASIO3_;
                IConnectionPoint* ICONPTR_;
                opc_callback*     ipCallback;} ;

            opcintf::opcintf(tagsbase_ptr intf_, executor* exctr, indx grp) :
            extintf_wraper<OPCHANDLE>(intf_, exctr, grp, TYPE_SIMPLE_REQ, intf_ ? intf_->groups()->synctype(grp) : CONTYPE_SYNC ) ,
            transactid_(1) ,  setadviceactive(false) {
                update_dog();}

            opcintf::~opcintf() {
				disconnect();};

            ns_error opcintf::checkserverstatus() {
                error(0);
                if ((!opc_spec) || (!static_cast<opc_util*> (opc_spec.get())->IGRPMGT()))
                    throw dvncierror(ERROR_FAILNET_CONNECTED);

                OPCSERVERSTATUS status;
                OPCSERVERSTATUS* pstatus = &status;
                HRESULT hResult = static_cast<opc_util*> (opc_spec.get())->ISRV()->GetStatus(&pstatus);

                if (FAILED(hResult)) {
                    throw dvncierror(ERROR_FAILNET_CONNECTED);}

                return error();

                //if (status.dwServerState == OPC_STATUS_RUNNING) return 0;
                throw dvncierror(ERROR_FAILNET_CONNECTED);}

            ns_error  opcintf::connect_impl() {


                DEBUG_VAL_DVNCI(intf->groups()->server(group()))

                std::string szProgID      = intf->groups()->server(group());
                std::wstring szProgIDw    = string_to_wstring(szProgID);
                std::string szHostName    = intf->groups()->host(group());
                std::wstring szHostNamew  = string_to_wstring(szHostName);
                std::string szGroupName   = intf->groups()->group(group());
                std::wstring szGroupNamew = string_to_wstring(szGroupName);


                ver = intf->groups()->ver(group());
                deadband = intf->groups()->deadbound(group());
                updaterate = intf->groups()->grouprate(group());
                maintimeout = intf->groups()->timeout(group());
                tracttimeout = maintimeout * 9 / 10;
                if (updaterate < 99)
                    updaterate = 100;
                if (updaterate < 500)
                    updaterate = 500;

                abstr_opc_util_ptr tmpinf =
                        abstr_opc_util_ptr(new opc_util(this, szProgIDw, szGroupNamew, szHostNamew, deadband, static_cast<DWORD> (updaterate)));

                if (!tmpinf->init())
                    return error(ERROR_NOINTF_CONNECTED);
                opc_spec = tmpinf;

                if (ver == 0 )
                    ver = opc_spec->native_ver();

                DEBUG_STR_VAL_DVNCI(NATIV_VER, opc_spec->native_ver());

                if (ver > opc_spec->native_ver())
                    ver = opc_spec->native_ver();

                if (ver > 2) ver = 2;


                if ((ver == 1) || (!opc_spec->isasync())) {
                    subsrcript(CONTYPE_SYNC);}


                if (subsrcript() != CONTYPE_SYNC) {
                    bool tmpadv = (subsrcript() == CONTYPE_SUBSCR);
                    if (opc_spec->advice(tmpadv)) {
                        if (tmpadv != (subsrcript() == CONTYPE_SUBSCR)) {
                            subsrcript(CONTYPE_ASYNC);
                            DEBUG_STR_VAL_DVNCI(reset connecttype Bad, subsrcript());}
                        else {
                            DEBUG_STR_VAL_DVNCI(set connecttype Ok!, subsrcript());};}
                    else {
                        DEBUG_STR_VAL_DVNCI(cant set connecttype set sync, subsrcript());
                        subsrcript(CONTYPE_SYNC);}}
                else {
                    DEBUG_STR_VAL_DVNCI(set connecttype sync OK!, subsrcript());};

                DEBUG_STR_VAL_DVNCI(versionopc, ver)
                DEBUG_STR_VAL_DVNCI(opcconntype, subsrcript())
                DEBUG_VAL_DVNCI(updaterate)
                DEBUG_VAL_DVNCI(deadband)

                state_ = connected;
                return 0;}

            ns_error  opcintf::disconnect_impl() {
		if (state_ == connected) {
                disconnect_util();
                readtractmap.clear();
                writetractmap.clear();
                state_ = disconnected;
		if (opc_spec)
                        opc_spec.reset();
			ver = 0;}
                return 0;}

            ns_error opcintf::add_request_impl() {

                error(0);
                if (need_add().empty()) 
                    return error();


                DWORD dwCount = need_add().size();
                OPCITEMDEF* pItems = (OPCITEMDEF*) CoTaskMemAlloc(dwCount * sizeof (OPCITEMDEF)); // need free
                OPCITEMRESULT* pResults = NULL; // need free
                HRESULT* pErrors = NULL; // need free

                memset(pItems, 0, sizeof (OPCITEMDEF) * dwCount);


                typedef std::vector<std::wstring> tempwstring;

                tempwstring tmpwstr;
                
                for (indx_set::const_iterator it = need_add().begin(); it != need_add().end(); ++it) {
                    if (intf->exists(*it)) {
                        tmpwstr.push_back(string_to_wstring(intf->binding(*it)));}}

                tempwstring::const_iterator wsit = tmpwstr.begin();

                DWORD i = 0;

                for (indx_set::const_iterator it = need_add().begin(); it != need_add().end(); ++it) {
                    if (intf->exists(*it)) {
                        pItems[i].szItemID = const_cast<wchar_t*> (wsit != tmpwstr.end() ? wsit->c_str() : L"");
                        pItems[i].szAccessPath = NULL;
                        pItems[i].bActive = TRUE;
                        pItems[i].hClient = static_cast<OPCHANDLE> (*it);
                        pItems[i].vtRequestedDataType = oletype(intf->type(*it));
                        pItems[i].dwBlobSize = 0;
                        pItems[i].pBlob = NULL;
                        wsit++;
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
                        return error(from_opcerror(OPC_E_INVALIDHANDLE));}


                    for (i = 0; i < dwCount; i++) {
                        if (pErrors[i] != S_OK) {
                            req_error(static_cast<indx> (pItems[i].hClient), from_opcerror(pErrors[i]));}
                        else {
                            add_simple(static_cast<indx> (pItems[i].hClient), pResults[i].hServer);}
                        if (pResults[i].dwBlobSize > 0) CoTaskMemFree(pResults[i].pBlob);}}

                CoTaskMemFree(pItems); // free
                CoTaskMemFree(pResults); // free
                CoTaskMemFree(pErrors); // free


                update_dog();

                return error();}

            ns_error opcintf::remove_request_impl() {

                error(0);
                if (need_remove().empty()) return error();

                DWORD dwCount = need_remove().size();
                OPCHANDLE * phServer = (OPCHANDLE*) CoTaskMemAlloc(dwCount * sizeof (OPCHANDLE)); // need free
                HRESULT* pErrors = NULL; // need free

                memset(phServer, 0, sizeof (OPCHANDLE) * dwCount);

                DWORD i = 0;

                for (serverkey_set::const_iterator it = need_remove().begin(); it != need_remove().end(); ++it) {
                    phServer[i++] = *it;}


                if (dwCount > 0) {
                    HRESULT hResult = static_cast<opc_util*> (opc_spec.get())->IGRPMGT()->
                            RemoveItems( dwCount,
                            phServer,
                            &pErrors);

                    if (FAILED(hResult)) {
                        CoTaskMemFree(phServer); // free
                        CoTaskMemFree(pErrors); // free
                        return error(from_opcerror(OPC_E_INVALIDHANDLE));}

                    for (i = 0; i < dwCount; i++) {
                        if (pErrors[i] != S_OK) {
                            remove_custom(phServer[i]);}
                        else {
                            remove_custom(phServer[i]);}}

                    CoTaskMemFree(phServer); // free
                    CoTaskMemFree(pErrors); // free;
                    ;}
                update_dog();
                return error();}

            ns_error opcintf::value_request_impl() {
                error(0);
                if (ver == 1) {
                    read_valuessync1();}
                else {
                    switch (subsrcript()) {
                        case CONTYPE_SYNC:{
                            read_valuessync1();
                            break;}
                        case CONTYPE_ASYNC:{
                            if (!isreadtransaction()) {
                                read_valuesasync2();}
                            else {
                                DWORD tsttransact = 0;
                                if (isreadexpiretimout(tracttimeout, tsttransact)) {
                                    DEBUG_STR_DVNCI(NEEDCANCELEDREADTRANSACT);
                                    cancelTransact(tsttransact);}
                                else {
                                    ;}}
                            break;}}}
                return error();}

            ns_error opcintf::command_request_impl(const sidcmd_map& cmd) {
                error(0);
                if (ver == 1) {
                    setvaluessync1(cmd);}
                else {
                    switch (subsrcript()) {
                        case CONTYPE_SYNC:{
                            setvaluessync1(cmd);
                            break;}
                        case CONTYPE_SUBSCR:
                        case CONTYPE_ASYNC:{
                            if (!iswritetransaction()) {
                                setvaluesasync2(cmd);}
                            else {
                                DWORD tsttransact = 0;
                                if (iswriteexpiretimout(tracttimeout, tsttransact)) {
                                    DEBUG_STR_DVNCI(NEEDCANCELEDREADTRANSACT);
                                    cancelTransact(tsttransact);}
                                else {
                                    ;}}
                            break;};}}
                return error();}

            bool opcintf::read_valuessync1() {
                
                DWORD dwCount              = simple_req().left.size();
                OPCHANDLE* phServer        = (OPCHANDLE*) CoTaskMemAlloc(dwCount * sizeof (OPCHANDLE)); // need free
                OPCITEMSTATE* ppItemValues = NULL; // need free
                HRESULT* pErrors           = NULL; // need free

                memset(phServer, 0, sizeof (OPCHANDLE) * dwCount);

                DWORD i = 0;

                for (serverkey_const_iterator it = simple_req().left.begin(); it != simple_req().left.end(); ++it) {
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

                    ;
                    for (i = 0; i < dwCount; i++) {
                        if (pErrors[i] == S_OK) {
                            write_val_id(static_cast<indx> (ppItemValues[i].hClient),
                                    from_oletype_cast(ppItemValues[i].vDataValue, ppItemValues[i].wQuality, ppItemValues[i].ftTimeStamp));}
                        else {
                            req_error(static_cast<indx> (ppItemValues[i].hClient), from_opcerror(pErrors[i]));}}}

                CoTaskMemFree(phServer); // free
                CoTaskMemFree(ppItemValues); // free
                CoTaskMemFree(pErrors); // free
                update_dog();
                return true;}

            bool opcintf::read_valuesasync2() {
                
                DWORD dwCount              = simple_req().left.size();
                OPCHANDLE* phServer        = (OPCHANDLE*) CoTaskMemAlloc(dwCount * sizeof (OPCHANDLE)); // need free
                DWORD      dwTransactionID = transactid();
                DWORD      pdwCancelID     = 0;
                HRESULT*   pErrors         = NULL; // need free


                memset(phServer, 0, sizeof (OPCHANDLE) * dwCount);

                DWORD i = 0;

                for (serverkey_const_iterator it = simple_req().left.begin(); it != simple_req().left.end(); ++it) {
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

                    //addreadtransaction(dwTransactionID, pdwCancelID);

                    DWORD errorcnt = 0;

                    for (i = 0; i < dwCount; i++) {
                        if (pErrors[i] != S_OK) {
                            errorcnt++;}}

                    if (errorcnt < dwCount) addreadtransaction(dwTransactionID, pdwCancelID);}

                CoTaskMemFree(phServer); // free
                CoTaskMemFree(pErrors); // free
                return true;}

            bool opcintf::setvaluessync1(const sidcmd_map& cmd) {

                DWORD dwCount = cmd.size();
                OPCHANDLE* phServer = (OPCHANDLE*) CoTaskMemAlloc(dwCount * sizeof (OPCHANDLE)); // need free
                VARIANT* phItemValues = (VARIANT*) CoTaskMemAlloc(dwCount * sizeof (VARIANT)); // need free
                HRESULT* pErrors = NULL; // need free

                memset(phServer, 0, sizeof (OPCHANDLE) * dwCount);
                memset(phItemValues, 0, sizeof (VARIANT) * dwCount);

                DWORD i = 0;

                for (sidcmd_map::const_iterator it = cmd.begin(); it != cmd.end(); ++it) {
                    VARIANT tmpvariant = to_oletype_cast(it->second);
                    DEBUG_STR_DVNCI(ADDITEM SYNCWRITE1);
                    if (tmpvariant.vt != VT_ILLEGAL) {
                        phServer[i] = static_cast<OPCHANDLE> (it->first);
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


                    for (i = 0; i < dwCount; i++) {
                        if (pErrors[i] == S_OK) {}}}

                CoTaskMemFree(phServer); //free
                CoTaskMemFree(phItemValues); //free
                CoTaskMemFree(pErrors); //free
                update_dog();
                return true;}
            
            

            bool opcintf::setvaluesasync2(const sidcmd_map& cmd) {

                DWORD dwCount = cmd.size();
                OPCHANDLE* phServer = (OPCHANDLE*) CoTaskMemAlloc(dwCount * sizeof (OPCHANDLE)); // need free
                VARIANT* phItemValues = (VARIANT*) CoTaskMemAlloc(dwCount * sizeof (VARIANT)); // need free
                DWORD      dwTransactionID = transactid();
                DWORD      pdwCancelID = 0;
                HRESULT* pErrors = NULL; // need free

                memset(phServer, 0, sizeof (OPCHANDLE) * dwCount);
                memset(phItemValues, 0, sizeof (VARIANT) * dwCount);

                DWORD i = 0;

                for (sidcmd_map::const_iterator it = cmd.begin(); it != cmd.end(); ++it) {
                    VARIANT tmpvariant = to_oletype_cast(it->second);
                    DEBUG_STR_DVNCI(ADDITEM SYNCWRITE1);
                    if (tmpvariant.vt != VT_ILLEGAL) {
                        phServer[i] = static_cast<OPCHANDLE> (it->first);
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

                    DWORD errorcnt = 0;

                    for (i = 0; i < dwCount; i++) {
                        if (pErrors[i] != S_OK) {
                            errorcnt++;
                            DEBUG_STR_DVNCI(ASYNCWRITE1 ERR);}}
                    if (errorcnt < dwCount)  addwritetransaction(dwTransactionID, pdwCancelID);}

                CoTaskMemFree(phServer); //free
                CoTaskMemFree(phItemValues); //free
                CoTaskMemFree(pErrors); //free
                return true;}

            bool opcintf::cancelTransact(DWORD tract) {
                HRESULT hResult = static_cast<opc_util*> (opc_spec.get())->ASIO2()->Cancel2(tract);
                if (FAILED(hResult)) {
                    DEBUG_STR_DVNCI(FAIL CANCEL);}
                else DEBUG_STR_DVNCI(SUCCESS CANCEL);
                return true;}}}}
