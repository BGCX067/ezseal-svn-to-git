/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Jan 15 20:56:39 2011
 */
/* Compiler settings for D:\My Documents\Visual Studio 2008\Projects\ezSeal\ezSeal.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __ezSeal_h__
#define __ezSeal_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ImySeal_FWD_DEFINED__
#define __ImySeal_FWD_DEFINED__
typedef interface ImySeal ImySeal;
#endif 	/* __ImySeal_FWD_DEFINED__ */


#ifndef __ICreateSeal_FWD_DEFINED__
#define __ICreateSeal_FWD_DEFINED__
typedef interface ICreateSeal ICreateSeal;
#endif 	/* __ICreateSeal_FWD_DEFINED__ */


#ifndef __mySeal_FWD_DEFINED__
#define __mySeal_FWD_DEFINED__

#ifdef __cplusplus
typedef class mySeal mySeal;
#else
typedef struct mySeal mySeal;
#endif /* __cplusplus */

#endif 	/* __mySeal_FWD_DEFINED__ */


#ifndef __CreateSeal_FWD_DEFINED__
#define __CreateSeal_FWD_DEFINED__

#ifdef __cplusplus
typedef class CreateSeal CreateSeal;
#else
typedef struct CreateSeal CreateSeal;
#endif /* __cplusplus */

#endif 	/* __CreateSeal_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ImySeal_INTERFACE_DEFINED__
#define __ImySeal_INTERFACE_DEFINED__

/* interface ImySeal */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ImySeal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D0D38B3B-0A50-46E6-A58F-1BE775CA095A")
    ImySeal : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ImySealVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ImySeal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ImySeal __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ImySeal __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ImySeal __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ImySeal __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ImySeal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ImySeal __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ImySealVtbl;

    interface ImySeal
    {
        CONST_VTBL struct ImySealVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ImySeal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ImySeal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ImySeal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ImySeal_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ImySeal_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ImySeal_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ImySeal_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ImySeal_INTERFACE_DEFINED__ */


#ifndef __ICreateSeal_INTERFACE_DEFINED__
#define __ICreateSeal_INTERFACE_DEFINED__

/* interface ICreateSeal */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICreateSeal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A94858F9-F53F-4A91-B191-F5817FDF5E4C")
    ICreateSeal : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ICreateSealVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICreateSeal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICreateSeal __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICreateSeal __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICreateSeal __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICreateSeal __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICreateSeal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICreateSeal __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ICreateSealVtbl;

    interface ICreateSeal
    {
        CONST_VTBL struct ICreateSealVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICreateSeal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICreateSeal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICreateSeal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICreateSeal_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICreateSeal_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICreateSeal_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICreateSeal_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICreateSeal_INTERFACE_DEFINED__ */



#ifndef __EZSEALLib_LIBRARY_DEFINED__
#define __EZSEALLib_LIBRARY_DEFINED__

/* library EZSEALLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EZSEALLib;

EXTERN_C const CLSID CLSID_mySeal;

#ifdef __cplusplus

class DECLSPEC_UUID("E548AEC4-1B4E-4ED3-BD5D-DBF491334C02")
mySeal;
#endif

EXTERN_C const CLSID CLSID_CreateSeal;

#ifdef __cplusplus

class DECLSPEC_UUID("83027F81-FCDB-4E61-BFA7-A3048BBAD3D8")
CreateSeal;
#endif
#endif /* __EZSEALLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
