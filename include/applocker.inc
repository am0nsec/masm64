; @file        applocker.inc
; @date        18-08-2020
; @author      Paul Laîné (@am0nsec)
; @version     1.0
; @brief       Microsoft AppLocker COM Interfaces.
; @details	
; @link        https://docs.microsoft.com/en-us/windows/security/threat-protection/windows-defender-application-control/applocker/applocker-overview
; @copyright   This project has been released under the GNU Public License v3 license.

INCLUDE ole.inc

IFNDEF _APPLOCKER_INC
_APPLOCKER_INC EQU <1>

; @brief GUID of the IAppIdPolicyHandler COM interface: B6FEA19E-32DD-4367-B5B7-2F5DA140E87D
IID_IAppIdPolicyHandler STRUCT
    Data1 DWORD 0B6FEA19Eh
    Data2 WORD  32DDh
    Data3 WORD  4367h
    Data4 BYTE  0B5h
    Data5 BYTE  0B7h
    Data6 BYTE  2Fh
    Data7 BYTE  5Dh
    Data8 BYTE  0A1h
    Data9 BYTE  40h
    DataA BYTE  0E8h
    DataB BYTE  7Dh
IID_IAppIdPolicyHandler ENDS

; @brief GUID of the IAppIdPolicyHandler class factory: F1ED7D4C-F863-4DE6-A1CA-7253EFDEE1F3
CLSID_AppIdPolicyHandlerClass STRUCT
    Data1 DWORD 0F1ED7D4Ch
    Data2 WORD  0F863h
    Data3 WORD  4DE6h
    Data4 BYTE  0A1h
    Data5 BYTE  0CAh
    Data6 BYTE  72h
    Data7 BYTE  53h
    Data8 BYTE  0EFh
    Data9 BYTE  0DEh
    DataA BYTE  0E1h
    DataB BYTE  0F3h
CLSID_AppIdPolicyHandlerClass ENDS

;-----------------------------------------------------------------------------
; IAppIdPolicyHandler methods
;-----------------------------------------------------------------------------
_SetPolicy          TYPEDEF PROTO T:PVOID, bstrLdapPath:BSTR, bstrXmlPolicy:BSTR
_GetPolicy          TYPEDEF PROTO T:PVOID, bstrLdapPath:BSTR, pbstrXmlPolicy:LPBSTR
_GetEffectivePolicy TYPEDEF PROTO T:PVOID, pbstrXmlPolicies:LPBSTR
_IsFileAllowed      TYPEDEF PROTO T:PVOID, bstrXmlPolicy:BSTR, bstrFilePath:BSTR, bstrUserSid:BSTR, pguidResponsibleRuleId:LPGUID, pbStatus:PLONG
_IsPackageAllowed   TYPEDEF PROTO T:PVOID, bstrXmlPolicy:BSTR, bstrPublisherName:BSTR, bstrPackageName:BSTR, ullPackageVersion:ULONG, bstrUserSid:BSTR, pguidResponsibleRuleId:LPGUID, pbStatus:PLONG

_PSetPolicy          TYPEDEF PTR _SetPolicy
_PGetPolicy          TYPEDEF PTR _GetPolicy
_PGetEffectivePolicy TYPEDEF PTR _GetEffectivePolicy
_PIsFileAllowed      TYPEDEF PTR _IsFileAllowed
_PIsPackageAllowed   TYPEDEF PTR _IsPackageAllowed

;-----------------------------------------------------------------------------
; Interfaces
;-----------------------------------------------------------------------------
AppIdPolicyHandlerVtbl STRUCT
    QueryInterface     _PQueryInterface ? 
    AddRef             _PAddRef ?
    Release            _PRelease ?
    GetTypeInfoCount   _PGetTypeInfoCount ?
    GetTypeInfo        _PGetTypeInfo ?
    GetIDsOfNames      _PGetIDsOfNames ?
    Invoke_            _PInvoke ?
    SetPolicy          _PSetPolicy ?
    GetPolicy          _PGetPolicy ?
    GetEffectivePolicy _PGetEffectivePolicy ?
    IsFileAllowed      _PIsFileAllowed ?
    IsPackageAllowed   _PIsPackageAllowed ?
AppIdPolicyHandlerVtbl ENDS

_PAppIdPolicyHandlerVtbl TYPEDEF PTR AppIdPolicyHandlerVtbl

IAppIdPolicyHandler STRUCT
    lpVtbl _PAppIdPolicyHandlerVtbl ?
IAppIdPolicyHandler ENDS

ENDIF ; !_APPLOCKER_INC
