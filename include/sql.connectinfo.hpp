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
#include <sql.interface.hpp>

namespace sql
{
   class _SQLDYNAMICLINK ConnectInfo: public Interface
   {
   public:
      ConnectInfo();
      explicit ConnectInfo(ConnectInfo const & in);
      explicit ConnectInfo(std::wstring const & user_id, 
         std::wstring const & password, std::wstring const & initial_catalog, std::wstring const & data_source);

      virtual void const __fastcall SetProvider(std::wstring const & value){ m_strProvider = value; }
      virtual void const __fastcall SetIntegratedSecurity(std::wstring const & value){ m_strIntegratedSecurity = value; }
      virtual void const __fastcall SetPersistSecurityInfo(bool value){ m_bPersistSecurityInfo = value; }
      virtual void const __fastcall SetUserID(std::wstring const & value){ m_strUserID = value; }
      virtual void const __fastcall SetInitialCatalog(std::wstring const & value){ m_strInitialCatalog = value; }
      virtual void const __fastcall SetDataSource(std::wstring const & value){ m_strDataSource = value; }
      virtual void const __fastcall SetInitialFileName(std::wstring const & value){ m_strInitialFileName = value; }
      virtual void const __fastcall SetServerSPN(std::wstring const & value){ m_strServerSPN = value; }
      virtual void const __fastcall SetPassword(std::wstring const & value){ m_strPassword = value; }
      std::wstring const & GetProvider(){ return m_strProvider; }
      std::wstring const & GetIntegratedSecurity(){ return m_strIntegratedSecurity; }
      bool    const   GetPersistSecurityInfo(){ return m_bPersistSecurityInfo; }
      std::wstring const & GetUserID(){ return m_strUserID; }
      std::wstring const & GetInitialCatalog(){ return m_strInitialCatalog; }
      std::wstring const & GetDataSource(){ return m_strDataSource; }
      std::wstring const & GetInitialFileName(){ return m_strInitialFileName; }
      std::wstring const & GetServerSPN(){ return m_strServerSPN; }
      std::wstring const & GetPassword(){ return m_strPassword; }

      std::wstring    __fastcall GetConnectionString();
      virtual void const __fastcall SetConnection(sql::ConnectInfo const & in);
      SQL_DECLARE_OPERATOR(ConnectInfo)
      //operators
      bool const __fastcall operator==(sql::ConnectInfo const & in);
      //
      __declspec(property(get=GetConnectionString)) std::wstring ConnectionString;
   protected:
      std::wstring m_strProvider;
      std::wstring m_strIntegratedSecurity;
      bool m_bPersistSecurityInfo;
      std::wstring m_strUserID;
      std::wstring m_strInitialCatalog;
      std::wstring m_strDataSource;
      std::wstring m_strInitialFileName;
      std::wstring m_strServerSPN;
      std::wstring m_strPassword;
   };
};