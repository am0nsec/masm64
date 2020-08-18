; @file        kernel32.inc
; @date        17-08-2020
; @author      Paul Laîné (@am0nsec)
; @version     1.0
; @brief       Kernel32 function prototypes.
; @details	   
; @link        
; @copyright   This project has been released under the GNU Public License v3 license.

IFNDEF _KERNEL32_INC
_KERNEL32_INC EQU <1>

lstrlenW      PROTO :QWORD
GetStdHandle  PROTO :DWORD
WriteConsoleW PROTO :QWORD, :QWORD, :QWORD, :QWORD, :QWORD
WriteConsoleA PROTO :QWORD, :QWORD, :QWORD, :QWORD, :QWORD
CloseHandle   PROTO :QWORD

ENDIF ; !_KERNEL32_INC
