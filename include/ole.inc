; @file        ole.inc
; @date        17-08-2020
; @author      Paul Laîné (@am0nsec)
; @version     1.0
; @brief       Object Linking and Embedding (OLE) Automation definitions.
; @details	
; @link        
; @copyright   This project has been released under the GNU Public License v3 license.

include windef.inc
include guiddef.inc

IFNDEF _OLE_INC
_OLE_INC EQU 1

;--------------------------------------------------------------------------------------------------
; Function prototypes
;--------------------------------------------------------------------------------------------------
CoInitialize     PROTO :QWORD
CoCreateInstance PROTO :QWORD, :QWORD, :DWORD, :REFIID, :PPVOID
CoUninitialize   PROTO 

;--------------------------------------------------------------------------------------------------
; Interface GUIDs
;--------------------------------------------------------------------------------------------------
IID_IUnknown STRUCT
    Data1 DWORD 00000000h
    Data2 WORD  0000h
    Data3 WORD  0000h
    Data4 BYTE  0C0h
    Data5 BYTE  00h
    Data6 BYTE  00h
    Data7 BYTE  00h
    Data8 BYTE  00h
    Data9 BYTE  00h
    DataA BYTE  00h
    DataB BYTE  46h
IID_IUnknown ENDS

IID_AsyncIUnknown STRUCT
    Data1 DWORD 000e0000h
    Data2 WORD  0000h
    Data3 WORD  0000h
    Data4 BYTE  0C0h
    Data5 BYTE  00h
    Data6 BYTE  00h
    Data7 BYTE  00h
    Data8 BYTE  00h
    Data9 BYTE  00h
    DataA BYTE  00h
    DataB BYTE  46h
IID_AsyncIUnknown ENDS

IID_IClassFactory STRUCT
    Data1 DWORD 00000001h
    Data2 WORD  0000h
    Data3 WORD  0000h
    Data4 BYTE  0C0h
    Data5 BYTE  00h
    Data6 BYTE  00h
    Data7 BYTE  00h
    Data8 BYTE  00h
    Data9 BYTE  00h
    DataA BYTE  00h
    DataB BYTE  46h
IID_IClassFactory ENDS

IID_IDispatch STRUCT
    Data1 DWORD 00020400h
    Data2 WORD  0000h
    Data3 WORD  0000h
    Data4 BYTE  0C0h
    Data5 BYTE  00h
    Data6 BYTE  00h
    Data7 BYTE  00h
    Data8 BYTE  00h
    Data9 BYTE  00h
    DataA BYTE  00h
    DataB BYTE  46h
IID_IDispatch ENDS

;--------------------------------------------------------------------------------------------------
; Type definition
;--------------------------------------------------------------------------------------------------
LCID    TYPEDEF DWORD
DISPID  TYPEDEF QWORD
PDISPID TYPEDEF PTR DISPID
BSTR    TYPEDEF PTR PWCHAR
LPBSTR  TYPEDEF PTR BSTR

;--------------------------------------------------------------------------------------------------
; IUnknown
;--------------------------------------------------------------------------------------------------
_QueryInterface  TYPEDEF PROTO T:PVOID, riid:REFIID, ppvObject:PPVOID
_AddRef          TYPEDEF PROTO T:PVOID
_Release         TYPEDEF PROTO T:PVOID

_PQueryInterface TYPEDEF PTR _QueryInterface
_PAddRef         TYPEDEF PTR _AddRef
_PRelease        TYPEDEF PTR _Release

UnknownVtbl STRUCT
    QueryInterface _PQueryInterface ?
    AddRef         _PAddRef ?
    Release        _PRelease ?
UnknownVtbl ENDS

_PUnknownVtbl TYPEDEF PTR UnknownVtbl

IUnknown STRUCT
    lpVtbl _PUnknownVtbl ?
IUnknown ENDS

;--------------------------------------------------------------------------------------------------
; IAsyncIUnknown
;--------------------------------------------------------------------------------------------------
_Begin_QueryInterface   TYPEDEF PROTO T:QWORD, riid:REFIID
_Finish_QueryInterface  TYPEDEF PROTO T:QWORD, ppvObject:PPVOID
_Begin_AddRef           TYPEDEF PROTO T:QWORD
_Finish_AddRef          TYPEDEF PROTO T:QWORD
_Begin_Release          TYPEDEF PROTO T:QWORD
_Finish_Release         TYPEDEF PROTO T:QWORD

_PBegin_QueryInterface  TYPEDEF PTR _Begin_QueryInterface
_PFinish_QueryInterface TYPEDEF PTR _Finish_QueryInterface
_PBegin_AddRef          TYPEDEF PTR _Begin_AddRef
_PFinish_AddRef         TYPEDEF PTR _Finish_AddRef
_PBegin_Release         TYPEDEF PTR _Begin_Release
_PFinish_Release        TYPEDEF PTR _Finish_Release

AsyncIUnknownVtbl STRUCT
    QueryInterface        _PQueryInterface ?
    AddRef                _PAddRef ?
    Release               _PRelease ?
    Begin_QueryInterface  _PBegin_QueryInterface ?
    Finish_QueryInterface _PFinish_QueryInterface ?
    Begin_AddRef          _PBegin_AddRef ? 
    Finish_AddRef         _PFinish_AddRef ?
    Begin_Release         _PBegin_Release ?
    Finish_Release        _PFinish_Release ?
AsyncIUnknownVtbl ENDS

_PAsyncIUnknownVtbl TYPEDEF PTR AsyncIUnknownVtbl

IAsyncIUnknown STRUCT
    lpVtbl _PAsyncIUnknownVtbl ?
IAsyncIUnknown ENDS

;--------------------------------------------------------------------------------------------------
; IClassFactory 
;--------------------------------------------------------------------------------------------------
_CreateInstance TYPEDEF PROTO T:PVOID, riid:REFIID, ppvObject:PPVOID
_LockServer     TYPEDEF PROTO T:PVOID, fLock:BOOL

_PCreateInstance TYPEDEF PTR _CreateInstance
_PLockServer     TYPEDEF PTR _LockServer

IClassFactoryVtbl STRUCT
    QueryInterface _PQueryInterface ?
    AddRef         _PAddRef ?
    Release        _PRelease ?
    CreateInstance _PCreateInstance ?
    LockServer     _PLockServer ?
IClassFactoryVtbl ENDS

_PIClassFactoryVtbl TYPEDEF PTR IClassFactoryVtbl

IClassFactory STRUCT
    lpVtbl _PIClassFactoryVtbl ?
IClassFactory ENDS

;--------------------------------------------------------------------------------------------------
; IDispatch methods
;--------------------------------------------------------------------------------------------------
_GetTypeInfoCount  TYPEDEF PROTO T:PVOID, pctinfo:PUINT
_GetTypeInfo       TYPEDEF PROTO T:PVOID, itinfo:UINT, lcid:LCID, pptinfo:PPVOID
_GetIDsOfNames     TYPEDEF PROTO T:PVOID, riid:LPIID, rgszNames:PWCHAR, cNames:UINT, lcid:LCID, rgdispid:PDISPID
_Invoke            TYPEDEF PROTO T:PVOID, dispidMember:DISPID, riid:LPIID, lcid:LCID, wFlags:WORD, 

_PGetTypeInfoCount TYPEDEF PTR _GetTypeInfoCount
_PGetTypeInfo      TYPEDEF PTR _GetTypeInfo
_PGetIDsOfNames    TYPEDEF PTR _GetIDsOfNames
_PInvoke           TYPEDEF PTR _Invoke

IDispatchVtbl STRUCT
    QueryInterface   _PQueryInterface ?
    AddRef           _PAddRef ?
    Release          _PRelease ?
    GetTypeInfoCount _PGetTypeInfoCount ?
    GetTypeInfo      _PGetTypeInfo ?
    GetIDsOfNames    _PGetIDsOfNames ?
    Invoke_          _PInvoke ?
IDispatchVtbl ENDS

_PIDispatchVtbl TYPEDEF PTR IDispatchVtbl

IDispatch STRUCT
    lpVtbl _PIDispatchVtbl ?
IDispatch ENDS

ENDIF ; !_OLE_INC
