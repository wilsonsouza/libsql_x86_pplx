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
#include <sql.connectionseventimpl.hpp>
#include <sql.connectinfo.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   static std::wstring const IDS_CATALOGNAME = U("CATALOG_NAME");
   static std::wstring const IDS_TABLENAME   = U("TABLE_NAME");
   class _SQLDYNAMICLINK Table;
   class _SQLDYNAMICLINK InterfaceInfo;
   class _SQLDYNAMICLINK Database: 
      public ConnectInfo,
      public _ADOConnection
   {
   public:
      Database();
      explicit Database(sql::ConnectInfo const & sqlcon);
      explicit Database(_Connection const & conptr);
      virtual ~Database();
      virtual bool const __fastcall Disconnect();
      virtual bool const __fastcall SetActiveConnection(bool bEnable = false);
      virtual bool const __fastcall IsConnected();
      virtual bool const __fastcall BeginTransaction();
      virtual bool const __fastcall CommitTransaction();
      virtual bool const __fastcall Rollback();
      //
      virtual void const __fastcall SetInitialCatalog(std::wstring const & strInitialCatalog);
      //
      virtual bool const __fastcall IsCatalog(std::wstring const & strCatalogName);
      virtual bool const __fastcall IsTable(std::wstring const & TableName);
      //
      virtual bool const __fastcall CreateDatabase(std::wstring const & strCatalogName);
      virtual bool const __fastcall CreateTable(std::wstring const & strTableName, std::wstring const & Fields);
      //list
      virtual std::shared_ptr<sql::Table> __fastcall GetCatalogsPtr();
      virtual std::shared_ptr<sql::Table> __fastcall GetTablesPtr();
      virtual std::shared_ptr<sql::Table> __fastcall OpenSchemaPtr(SchemaEnum se);
      //set
      virtual void const __fastcall SetConnectParameters(sql::ConnectInfo const & in);
      virtual sql::ConnectInfo &  __fastcall GetConnectParameters();
      //
      //Start events
      virtual void const   __fastcall SetConnectionPtrEventsClass();
      virtual void const   __fastcall FinalizeConnectionPtrEventsClass();
      //
      virtual std::shared_ptr<sql::Table> __fastcall Execute(std::wstring const & strcmd, ExecuteOptionEnum mode = adExecuteRecord);
      virtual bool const __fastcall ExecutenonQuery(std::wstring const & strcmd);
      //pplx
      virtual task_group & GetTask();
      /**/
      virtual bool DropDatabase( std::wstring const & szCatalogName );
      virtual bool DropTable( std::wstring const & szTableName );
      /**/
      SQL_DECLARE_OPERATOR(Database);

      //propertys
      __declspec(property(get=IsConnected, put=SetActiveConnection)) bool Connected;
      __declspec(property(get=GetConnectParameters, put=SetConnectParameters)) sql::ConnectInfo & ConnectParameters;
   protected:
      virtual std::string __stdcall format_com_error(_com_error e);
      std::exception const __stdcall _throw_exception_com_error(_com_error e);
   protected:
      HRESULT m_hSuccess;
      DWORD m_dwConnectionEvent;
      IConnectionPointContainer *m_pConnPointC;
      IConnectionPoint *m_pConnPoint;
      IUnknown *m_pUnknown;
      _Connection * m_conn;
   };
};
//-----------------------------------------------------------------------------------------------//