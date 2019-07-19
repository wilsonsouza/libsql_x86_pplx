//-----------------------------------------------------------------------------------------------//
// Created with QT Mult plaform C++ Library
// sqlservermanager dynamic library v1.0 2012
//
// Created by Wilson.Souza
//
// Owner Libbs
// Copyright (c) 2012 Dedalus Prime
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <sql.manager.hpp>

namespace sql
{
   class _SQLDYNAMICLINK InterfaceDatabase;
   class _SQLDYNAMICLINK InterfaceTable;
   class _SQLDYNAMICLINK InterfaceQuery;
   class _SQLDYNAMICLINK InterfaceField;
   //-----------------------------------------------------------------------------------------------//
   class _SQLDYNAMICLINK InterfaceDatabase  //abstract class
   {
   public:
      InterfaceDatabase(){}
      explicit InterfaceDatabase(InterfaceDatabase const & db){}

      virtual void const __fastcall SetCatalog(std::wstring const & strcatalog) = 0;
      virtual void const __fastcall SetUser(std::wstring const & struserName) = 0;
      virtual void const __fastcall SetPassword(std::wstring const & strpassword) = 0;
      virtual void const __fastcall SetHost(std::wstring const & striphost_hostName) = 0;

      virtual std::wstring const __fastcall GetCatalog() const = 0;
      virtual std::wstring const __fastcall GetUser() const = 0;
      virtual std::wstring const __fastcall GetPassword() const = 0;
      virtual std::wstring const __fastcall GetHost() const = 0;

      virtual bool const __fastcall IsOnline() const = 0;
      virtual void const __fastcall Disconnect();
      virtual bool const __fastcall Connect(InterfaceDatabase const & ID = InterfaceDatabase()) = 0;
      SQL_DECLARE_OPERATOR(InterfaceDatabase)
   protected:
      std::wstring m_strCatalog;
      std::wstring m_strUserName;
      std::wstring m_strPassword;
      std::wstring m_strHostName;
      ConnectionPtr m_pPtr;
   };
   //-----------------------------------------------------------------------------------------------//
   class _SQLDYNAMICLINK InterfaceField
   {
   public:
      InterfaceField(){}
      InterfaceField(unsigned int uFieldindex, InterfaceQuery const & sql){}
      InterfaceField(std::wstring const & strFieldName, InterfaceQuery const & sql){}

      virtual Variant const __fastcall GetValue(Variant const & vvalue) = 0;
      virtual void     const __fastcall SetValue(Variant const & vvalue) = 0;
      SQL_DECLARE_OPERATOR(InterfaceField)
   protected:
      FieldPtr m_Ptr;
   };
   //-----------------------------------------------------------------------------------------------//
   class _SQLDYNAMICLINK InterfaceTable
   {
   public:
      InterfaceTable(){}
      InterfaceTable(std::wstring const & strTableName){}
      InterfaceTable(InterfaceTable const & tbl){}
      InterfaceTable(InterfaceDatabase const & db){}
      SQL_DECLARE_OPERATOR(InterfaceTable)
   protected:
      RecordSetPtr m_Ptr;
      InterfaceDatabase m_ID;
   };
   //-----------------------------------------------------------------------------------------------//
   class _SQLDYNAMICLINK InterfaceQuery: public InterfaceTable
   {
   public:
      InterfaceQuery(){}
      InterfaceQuery(InterfaceDatabase const & ID){}
      SQL_DECLARE_OPERATOR(InterfaceQuery)
   }
   //-----------------------------------------------------------------------------------------------//
};