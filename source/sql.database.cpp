//-----------------------------------------------------------------------------------------------//
// Created with QT Mult plaform C++ Library
// sqlservermanager dynamic library v1.0 2012
//
// Created by Wilson.Souza
//
// Owner Libbs
// Copyright (c) 2012, 2015 wilson.souza
// complete support to sql server within pplx
//-----------------------------------------------------------------------------------------------//
#include <sql.Table.hpp>
#include <sql.Error.hpp>
#include <sql.connectinfo.hpp>
#include <sql.database.hpp>
#include <string>
//-----------------------------------------------------------------------------------------------//
using namespace sql;
using namespace Concurrency;
//-----------------------------------------------------------------------------------------------//
Database::Database() :ConnectInfo()
{
   HRESULT hr = CreateInstance(__uuidof(Connection));
   //
   if(hr == S_OK)
   {
      SetConnectionPtrEventsClass();
   }
   /**/
   m_conn = _ConnectionPtr::operator->();
}
//-----------------------------------------------------------------------------------------------//
Database::Database(sql::ConnectInfo const & sqlcon) :ConnectInfo(sqlcon)
{
   HRESULT hr = CreateInstance(__uuidof(Connection));
   //
   if(hr == S_OK)
   {
      SetConnectionPtrEventsClass();
   }
   /**/
   m_conn = _ConnectionPtr::operator->();
}
//-----------------------------------------------------------------------------------------------//
Database::Database(_ConnectionPtr const & cptr) :ConnectInfo()
{
   CreateInstance(__uuidof(Connection));
   _ConnectionPtr::operator=(cptr);
   SetConnectionPtrEventsClass();
   m_conn = _ConnectionPtr::operator->();
}
//-----------------------------------------------------------------------------------------------//
Database::~Database()
{
   cancel();
   /* wait 100 milliseconds to disconnect */
   Sleep(0x64);
   FinalizeConnectionPtrEventsClass();
   Disconnect();
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Database::Disconnect()
{
   try
   {
      long lState;
      /**/
      if (m_conn->get_State(&lState) == S_OK)
      {
         if (lState == adStateOpen)
         {
            if (m_conn->Close() == S_OK)
            {
               return true;
            }
         }
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Database::SetActiveConnection(bool bEnable)
{
   try
   {
      bstr_t bConnectionString = ConnectionString.c_str();
      HRESULT m_hSuccess = S_FALSE;

      run_and_wait([&]
      {
         if (m_conn->State == adStateOpen)
         {
            return;
         }
         /*pplx*/
         m_conn->put_ConnectionTimeout(SQL_CONNECTIONTIMEOUT);
         m_conn->put_CommandTimeout(SQL_COMMANDTIMEOUT);
         m_conn->put_CursorLocation(adUseClient);
         m_conn->put_IsolationLevel(adXactUnspecified);
         m_conn->put_ConnectionString(bConnectionString);
         /**/
         if ((m_hSuccess = m_conn->Open("", "", "", adConnectUnspecified)) != S_OK)
         {
            throw std::exception("SQL-Server connection failed!");
         }
      });
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   catch(std::exception & e)
   {
      throw e;
   }
   return true;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Database::IsConnected()
{
   try
   {
      if (m_conn->State == adStateOpen)
      {
         return true;
      }
   }
   catch(_com_error & e)
   {
      throw _throw_exception_com_error(e);
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Database::BeginTransaction()
{
   try
   {
      if (m_conn->BeginTrans() == S_OK)
      {
         return true;
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Database::CommitTransaction()
{
   try
   {
      if (GetInterfacePtr()->CommitTrans() == S_OK)
      {
         return true;
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Database::Rollback()
{
   try
   {
      if (GetInterfacePtr()->RollbackTrans() == S_OK)
      {
         return true;
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
std::shared_ptr<sql::Table> __fastcall Database::Execute(std::wstring const & szCmd, ExecuteOptionEnum eMode)
{
   try
   {
      _bstr_t bszCmd = szCmd.c_str();
      VARIANT vRecordsAffected = VARIANT();
      _RecordsetPtr pDataSet = GetInterfacePtr()->Execute(bszCmd, &vRecordsAffected, eMode);
      {
         if (eMode != adExecuteNoRecords)
         {
            return std::shared_ptr<Table>(new Table(pDataSet));
         }
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return nullptr;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Database::ExecutenonQuery(std::wstring const & szCmd)
{
   try
   {
      run_and_wait([&]
      {
         _bstr_t bszCmd = szCmd.c_str();
         GetInterfacePtr()->Execute(bszCmd, nullptr, adExecuteNoRecords);
      });
      return true;
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
void const __fastcall Database::SetConnectParameters(sql::ConnectInfo const & in)
{
   if (this != &in)
   {
      SetConnection(in);
   }
}
//-----------------------------------------------------------------------------------------------//
sql::ConnectInfo & __fastcall Database::GetConnectParameters()
{
   return *this;
}
//-----------------------------------------------------------------------------------------------//
std::shared_ptr<sql::Table> __fastcall Database::GetCatalogsPtr()
{
   try
   {
      auto & r = GetInterfacePtr()->OpenSchema(adSchemaCatalogs);

      if (r != nullptr)
      {
         return std::shared_ptr<sql::Table>(new Table(r));
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return nullptr;
}
//-----------------------------------------------------------------------------------------------//
std::shared_ptr<sql::Table> __fastcall Database::GetTablesPtr()
{
   try
   {
      _RecordsetPtr ptr = GetInterfacePtr()->OpenSchema(adSchemaTables);
      {
         if (ptr != nullptr)
         {
            return std::shared_ptr<Table>(new Table(ptr));
         }
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return nullptr;
}
//-----------------------------------------------------------------------------------------------//
std::shared_ptr<sql::Table> __fastcall Database::OpenSchemaPtr(SchemaEnum se)
{
   try
   {
      _RecordsetPtr r = GetInterfacePtr()->OpenSchema(se);

      if (r != nullptr)
      {
         return std::shared_ptr<Table>(new Table(r));
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return nullptr;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Database::IsCatalog(std::wstring const & szCatalogName)
{
   try
   {
      bool bExists = false;
      /**/
      run_and_wait([&]
      {
         std::shared_ptr<sql::Table> p = OpenSchemaPtr(adSchemaCatalogs);

         if (p != nullptr)
         {
            while (!p->Eof && !is_canceling() && !bExists)
            {
               sql::Field * f = p->operator[](L"CATALOG_NAME");
               std::wstring Name = f->Text;

               if (Name.compare(szCatalogName) == 0)
               {
                  bExists = !bExists;
                  return;
               }
               /**/
               p->Next();
            }
         }
      });
      return bExists;
   }
   catch(std::exception & e)
   {
      throw e;
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Database::IsTable(std::wstring const & szTableName)
{
   try
   {
      bool bSuccess = false;
      /* call by pplx */
      run_and_wait([&]
      {
         std::shared_ptr<sql::Table> pTbl = GetTablesPtr();

         if (pTbl != nullptr)
         {
            while (!pTbl->Eof && !is_canceling())
            {
               sql::Field * f = pTbl->operator[](L"TABLE_NAME");
               /**/
               if (f != nullptr)
               {
                  if (f->Name == szTableName)
                  {
                     bSuccess = !bSuccess;
                     return;
                  }
               }
               /**/
               pTbl->Next();
            }
         }
      });
      /* catch result */
      return bSuccess;
   }
   catch (_com_error const & e)
   {
      throw std::exception( format_com_error( const_cast<_com_error &>( e ) ).c_str() );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Database::CreateDatabase(std::wstring const & strCatalogName)
{
   try
   {
      std::wstring fmt
      {
         L"create database " + strCatalogName
      };
      ExecutenonQuery(fmt);
      m_conn->put_DefaultDatabase(bstr_t(strCatalogName.c_str()));
      return true;
   }
   catch(std::exception & e)
   {
      throw e;
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Database::CreateTable(std::wstring const & szTableName, 
   std::wstring const & szFields)
{
   try
   {
      std::wstring fmt = std::wstring
      {
         L"create table dbo." + szTableName + L"(" + szFields + L")"
      };
      ExecutenonQuery(fmt);
      return true;
   }
   catch(std::exception & e)
   {
      throw e;
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
void const Database::SetInitialCatalog(std::wstring const & strInitialCatalog)
{
   m_conn->put_DefaultDatabase(bstr_t(strInitialCatalog.c_str()));
   ConnectInfo::SetInitialCatalog(strInitialCatalog);
}
//-----------------------------------------------------------------------------------------------//
void const   __fastcall Database::SetConnectionPtrEventsClass()
{
#if 0
   /* check client window handle to notified */
   m_hSuccess = m_conn->QueryInterface(__uuidof(IConnectionPointContainer), 
      reinterpret_cast<void **>(&m_pConnPointC));
   /**/
   if(FAILED(m_hSuccess))
      throw std::exception("called m_conn->QueryInterface() failed!");
   /**/
   m_hSuccess = m_pConnPointC->FindConnectionPoint(__uuidof(ConnectionEvents), &m_pConnPoint);
   /**/
   if(FAILED(m_hSuccess))
      throw std::exception("called m_pConnPointC->FindConnectionPoint() failed!");
   /**/
   m_hSuccess = m_pConnPoint->QueryInterface(__uuidof(IUnknown), reinterpret_cast<void **>(&m_pUnknown));
   /**/
   m_hSuccess = m_pConnPoint->Advise(m_pUnknown, static_cast<LPDWORD>(&m_dwConnectionEvent));
   /**/
   if (FAILED(m_hSuccess))
   {
      throw std::exception("called m_pConnPoint->Advise() failed!");
   }
   /**/
   m_pConnPoint->Release();
#endif
}
//-----------------------------------------------------------------------------------------------//
void const   __fastcall Database::FinalizeConnectionPtrEventsClass()
{
#if 0
   m_hSuccess = m_conn->QueryInterface(__uuidof(IConnectionPointContainer),
      reinterpret_cast<void **>(&m_pConnPointC));
   /**/
   if(FAILED(m_hSuccess)) 
      throw std::exception("called m_conn->QueryInterface() failed!");
   /**/
   m_hSuccess = m_pConnPointC->FindConnectionPoint(__uuidof(ConnectionEvents), &m_pConnPoint);
   m_pConnPointC->Release();
   /**/
   if(FAILED(m_hSuccess)) 
      throw std::exception("called m_pConnPointC->FindConnectionPoint() failed!");
   /**/
   m_hSuccess = m_pConnPoint->Unadvise(m_dwConnectionEvent);
   m_pConnPoint->Release();
   /**/
   if(FAILED(m_hSuccess)) 
      throw std::exception("called m_pConnPoint->Unadivse() failed!");
#endif
}
//-----------------------------------------------------------------------------------------------//
task_group & Database::GetTask()
{
   return *this;
}
//-----------------------------------------------------------------------------------------------//
bool Database::DropDatabase( std::wstring const & szCatalogName )
{
   try
   {
      SetInitialCatalog( std::wstring( L"master" ) );
      SetActiveConnection( true );
      /**/
      if ( IsCatalog( szCatalogName ) )
      {
         return ExecutenonQuery( std::wstring { L"drop database " } +szCatalogName );
      }
   }
   catch ( std::exception const & e )
   {
      throw e;
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool Database::DropTable( std::wstring const & szTableName )
{
   try
   {
      if ( IsTable( szTableName ) )
      {
         return ExecutenonQuery( std::wstring { L"drop table " } +szTableName );
      }
   }
   catch ( std::exception const & e )
   {
      throw e;
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
std::string __stdcall Database::format_com_error(_com_error e)
{
   std::string s = std::string
   {
      "Description: " + std::string(e.Description()) + "\n" +
      "Error      : " + std::to_string(e.Error()) + "\n" +
      "Message    : " + std::string(LPSTR(e.ErrorMessage())) + "\n" +
      "Source     : " + std::string(e.Source()) + "\n" +
      "Code       : " + std::to_string(e.WCode())
   };
   return s;
}
//-----------------------------------------------------------------------------------------------//
std::exception const __stdcall Database::_throw_exception_com_error(_com_error e)
{
   return std::exception(format_com_error(e).c_str());
}
//-----------------------------------------------------------------------------------------------//

