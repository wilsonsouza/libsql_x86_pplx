//-----------------------------------------------------------------------------------------------//
// Created with pplx Mult plaform C++ Library
// sqlservermanager dynamic library v1.0 2012
//
// Created by Wilson.Souza
//
// Owner Libbs
// Copyright (c) 2012 Dedalus Prime
//-----------------------------------------------------------------------------------------------//
#pragma once
#if(_MSC_VER < 1600)
   #include <ole2.h>
#else
   #include <ole2.h>
   #include <oledb.h>
#endif

#include <adoint.h>
#include <comutil.h>
//-----------------------------------------------------------------------------------------------//
#if(defined(_WINDLL) && !defined(_SQLDYNAMICLINK))
   #define _SQLDYNAMICLINK __declspec(dllexport)
#else
   #define _SQLDYNAMICLINK
#endif
//-----------------------------------------------------------------------------------------------//
#if(defined(UNICODE) || defined(_UNICODE))
#define U(x) L#x
#else
#define U(x) x
#endif
//-----------------------------------------------------------------------------------------------//
#include <memory>
#include <functional>
#include <map>
#include <ppl.h>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   //-----------------------------------------------------------------------------------------------//
   //ADO COM+
   typedef _Connection ConnectionPtr;
   typedef _Recordset  RecordSetPtr;
   //-----------------------------------------------------------------------------------------------//
#define SQL_DECLARE_OPERATOR(_uname) \
   private:\
   std::wstring m_szName;\
   public:\
   virtual operator _uname *(){ return static_cast<_uname *>(this); }\
   virtual std::wstring const GetClassName(){ return std::wstring(L"sql::") + std::wstring(L#_uname); }\
   virtual _uname * operator->(){ return static_cast<_uname *>(this); }\
   virtual _uname & operator *(){ return static_cast<_uname &>(*this); }\
   virtual _uname * Get##_uname(){ return static_cast<_uname *>(this); }\
   virtual std::wstring GetName(){ return m_szName; }\
   virtual void const   SetName(std::wstring const & szName){ m_szName = szName; }\
   public:\
   __declspec(property(get=GetName, put=SetName)) std::wstring Name;\
   __declspec(property(get=GetClassName)) std::wstring const ClassName;\
   //-----------------------------------------------------------------------------------------------//
   enum FIELDTYPE
   {
      SQL_FIELD_UNKNOW_TYPE = 0x0000,
      SQL_FIELD_INT64       = 0x0001,
      SQL_FIELD_BOOL        = 0x0002,
      SQL_FIELD_STRING      = 0x0004,
      SQL_FIELD_DATE        = 0x0008,
      SQL_FIELD_TIME        = 0x0010,
      SQL_FIELD_INT32       = 0x0020,
      SQL_FIELD_WORDCHAR    = 0x0040,
      SQL_FIELD_CURRENCY    = 0x0080,
      SQL_FIELD_WCHAR_T     = 0x0100,
      SQL_FIELD_INT16       = 0x0200,
      SQL_FIELD_DWORD       = 0x0400
   };
   //-----------------------------------------------------------------------------------------------//
   _SQLDYNAMICLINK bool const __fastcall InstallHandler(DWORD dwCoInitializeEx = COINIT_MULTITHREADED);
   _SQLDYNAMICLINK const void __fastcall UninstallHandler();
   //-----------------------------------------------------------------------------------------------//
   enum TIMEOUT
   {
      SQL_CONNECTIONTIMEOUT = 0x64,
      SQL_COMMANDTIMEOUT    = 0x64
   };
   //-----------------------------------------------------------------------------------------------//
#define SQL_CONN_PROVIDER              str::wstring(L"Provider")
#define SQL_CONN_PASSWORD              str::wstring(L"Password")
#define SQL_CONN_PERSIST_SECURITY_INFO str::wstring(L"Persist Security Info")
#define SQL_CONN_USER_ID               str::wstring(L"User ID")
#define SQL_CONN_INITIAL_CATALOG       str::wstring(L"Initial Catalog")
#define SQL_CONN_DATA_SOURCE           str::wstring(L"Data Source")
#define SQL_CONN_CONNECTION_TIMEOUT    str::wstring(L"ConnectionTimeout")
#define SQL_CONN_COMMAND_TIMEOUT       str::wstring(L"CommandTimeout")
#define SQL_CONN_CURSORLOCATION        str::wstring(L"CursorLocation")
#define SQL_CONN_ISOLATIONLEVEL        str::wstring(L"IsolationLevel")
   //-----------------------------------------------------------------------------------------------//
#define IDS_TRUE                       str::wstring(L"TRUE")
#define IDS_FALSE                      str::wstring(L"FALSE")
   //-----------------------------------------------------------------------------------------------//
};