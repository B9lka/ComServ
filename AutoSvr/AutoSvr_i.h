

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Dec 22 15:14:27 2015
 */
/* Compiler settings for AutoSvr.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __AutoSvr_i_h__
#define __AutoSvr_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISvcControl_FWD_DEFINED__
#define __ISvcControl_FWD_DEFINED__
typedef interface ISvcControl ISvcControl;

#endif 	/* __ISvcControl_FWD_DEFINED__ */


#ifndef __SvcControlComponent_FWD_DEFINED__
#define __SvcControlComponent_FWD_DEFINED__

#ifdef __cplusplus
typedef class SvcControlComponent SvcControlComponent;
#else
typedef struct SvcControlComponent SvcControlComponent;
#endif /* __cplusplus */

#endif 	/* __SvcControlComponent_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ISvcControl_INTERFACE_DEFINED__
#define __ISvcControl_INTERFACE_DEFINED__

/* interface ISvcControl */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISvcControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B89677AD-4C07-4CF8-96E2-366FD3E9497F")
    ISvcControl : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DoStartSvc( 
            /* [in] */ LPCWSTR szSvcName,
            /* [retval][out] */ BSTR *result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DoUpdateSvcDacl( 
            /* [in] */ LPCWSTR szSvcName,
            /* [retval][out] */ BSTR *result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DoStopSvc( 
            /* [in] */ LPCWSTR szSvcName,
            /* [retval][out] */ BSTR *result) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISvcControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISvcControl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISvcControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISvcControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISvcControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISvcControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISvcControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISvcControl * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *DoStartSvc )( 
            ISvcControl * This,
            /* [in] */ LPCWSTR szSvcName,
            /* [retval][out] */ BSTR *result);
        
        HRESULT ( STDMETHODCALLTYPE *DoUpdateSvcDacl )( 
            ISvcControl * This,
            /* [in] */ LPCWSTR szSvcName,
            /* [retval][out] */ BSTR *result);
        
        HRESULT ( STDMETHODCALLTYPE *DoStopSvc )( 
            ISvcControl * This,
            /* [in] */ LPCWSTR szSvcName,
            /* [retval][out] */ BSTR *result);
        
        END_INTERFACE
    } ISvcControlVtbl;

    interface ISvcControl
    {
        CONST_VTBL struct ISvcControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISvcControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISvcControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISvcControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISvcControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISvcControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISvcControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISvcControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISvcControl_DoStartSvc(This,szSvcName,result)	\
    ( (This)->lpVtbl -> DoStartSvc(This,szSvcName,result) ) 

#define ISvcControl_DoUpdateSvcDacl(This,szSvcName,result)	\
    ( (This)->lpVtbl -> DoUpdateSvcDacl(This,szSvcName,result) ) 

#define ISvcControl_DoStopSvc(This,szSvcName,result)	\
    ( (This)->lpVtbl -> DoStopSvc(This,szSvcName,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISvcControl_INTERFACE_DEFINED__ */



#ifndef __AutoSvrLib_LIBRARY_DEFINED__
#define __AutoSvrLib_LIBRARY_DEFINED__

/* library AutoSvrLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_AutoSvrLib;

EXTERN_C const CLSID CLSID_SvcControlComponent;

#ifdef __cplusplus

class DECLSPEC_UUID("CCE632FB-6FEB-497C-BD71-74E99DE8447E")
SvcControlComponent;
#endif
#endif /* __AutoSvrLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


