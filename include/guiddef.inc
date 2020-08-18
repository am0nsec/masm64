; @file        guiddef.inc
; @date        17-08-2020
; @author      Paul Laîné (@am0nsec)
; @version     1.0
; @brief       GUID definition.
; @details	   
; @link        
; @copyright   This project has been released under the GNU Public License v3 license.

IFNDEF _GUIDDEF_INC
_GUIDDEF_INC EQU 1

;--------------------------------------------------------------------------------------------------
; Structure
;--------------------------------------------------------------------------------------------------
GUID STRUCT
    Data1 DWORD ?
    Data2 WORD ?
    Data3 WORD ?
    Data4 BYTE 7 dup(?)
GUID ENDS

;--------------------------------------------------------------------------------------------------
; Type definition
;--------------------------------------------------------------------------------------------------
LPGUID   TYPEDEF PTR GUID
LPCGUID  TYPEDEF PTR GUID

IID      TYPEDEF GUID
LPIID    TYPEDEF PTR IID
REFIID   TYPEDEF PTR IID

CLSID    TYPEDEF GUID
LPCLSID  TYPEDEF PTR CLSID
REFCLSID TYPEDEF PTR CLSID

FMTID    TYPEDEF GUID
LPFMTID  TYPEDEF PTR FMTID
REFFMTID TYPEDEF PTR FMTID

;-----------------------------------------------------------------------------
; Macros
;-----------------------------------------------------------------------------
InlineIsEqualGUID MACRO rguid1, rguid2
    lea rsi, rguid1
    lea rdi, rguid2
	mov rcx, 10h
    repz cmpsb
ENDM

IsEqualIID MACRO rguid1, rguid2
    lea rsi, rguid1
    lea rdi, rguid2
	mov rcx, 10h
    repz cmpsb
ENDM

IsEqualCLSID MACRO rguid1, rguid2
    lea rsi, rguid1
    lea rdi, rguid2
	mov rcx, 10h
    repz cmpsb
ENDM

IsEqualFMTID MACRO rguid1, rguid2
    lea rsi, rguid1
    lea rdi, rguid2
	mov rcx, 10h
    repz cmpsb
ENDM

ENDIF ; !_GUIDDEF_INC
