//-----------------------------------------------------------------------------------------------//
// Created with QT Mult plaform C++ Library
// sqlservermanager dynamic library v1.0 2012
//
// Created by Wilson.Souza
//
// Owner Libbs
// Copyright (c) 2012 Dedalus Prime
//-----------------------------------------------------------------------------------------------//
#include <sql.ConnectInfo.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace sql;
//-----------------------------------------------------------------------------------------------//
ConnectInfo::ConnectInfo():Interface()
{
   //Provider=SQLNCLI11.1;Integrated Security=SSPI;Persist Security Info=False;User ID="";
   //Initial Catalog="";Data Source=DEDPRINB029\SQLEXPRESS_2005;Initial File Name="";Server SPN=""

   m_strProvider = L"SQLNCLI11.1";
   m_strIntegratedSecurity = L"SSPI";
   m_bPersistSecurityInfo = true;
   m_strUserID = std::wstring();
   m_strInitialCatalog = std::wstring();
   m_strDataSource = std::wstring();
   m_strInitialFileName = std::wstring();
   m_strServerSPN = std::wstring();
   m_strPassword = std::wstring();
}
//-----------------------------------------------------------------------------------------------//
ConnectInfo::ConnectInfo(sql::ConnectInfo const & in)
{
   m_strProvider = in.m_strProvider; 
   m_strIntegratedSecurity = in.m_strIntegratedSecurity;
   m_bPersistSecurityInfo = in.m_bPersistSecurityInfo;
   m_strUserID = in.m_strUserID;
   m_strPassword = in.m_strPassword;
   m_strInitialCatalog = in.m_strInitialCatalog;
   m_strDataSource = in.m_strDataSource;
   m_strInitialFileName = in.m_strInitialFileName;
   m_strServerSPN = in.m_strServerSPN;
}
//-----------------------------------------------------------------------------------------------//
ConnectInfo::ConnectInfo(std::wstring const & user_id,
                         std::wstring const & password,
                         std::wstring const & initial_catalog,
                         std::wstring const & data_source):Interface()
{
   m_strProvider = L"SQLNCLI";
   m_strIntegratedSecurity = L"SSPI";
   m_bPersistSecurityInfo = true;
   m_strUserID = user_id;
   m_strPassword = password;
   m_strInitialCatalog = initial_catalog;
   m_strDataSource = data_source;
   m_strInitialFileName = std::wstring();
   m_strServerSPN = std::wstring();
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall ConnectInfo::operator == (ConnectInfo const & in)
{
   //compare two objects address on memory
   bool bSuccess = (m_strProvider == in.m_strProvider && 
                   m_strIntegratedSecurity == in.m_strIntegratedSecurity &&
                   m_bPersistSecurityInfo == in.m_bPersistSecurityInfo &&
                   m_strUserID == in.m_strUserID &&
                   m_strPassword == in.m_strPassword &&
                   m_strInitialCatalog == in.m_strInitialCatalog &&
                   m_strDataSource == in.m_strDataSource &&
                   m_strInitialFileName == in.m_strInitialFileName &&
                   m_strServerSPN == in.m_strServerSPN);
   return bSuccess;
}
//-----------------------------------------------------------------------------------------------//
std::wstring __fastcall ConnectInfo::GetConnectionString()
{
   std::wstring strConn = std::wstring();
   std::wstring strProvider = L"Provider=";
   std::wstring strPassword = L"Password=";
   std::wstring strIntegratedSecurity = L"Integrated Security=";
   std::wstring strPersistSecurityInfo = L"Persist Security Info=";
   std::wstring strUserID = L"User ID=";
   std::wstring strInitialCatalog = L"Initial Catalog=";
   std::wstring strDataSource = L"Data Source=";
   std::wstring strInitialFileName = L"Initial File Name=";
   std::wstring strServerSPN = L"Server SPN=";

   if (m_strProvider.length())
   {
      strConn += std::wstring
      {
         strProvider + std::wstring(L"'") + m_strProvider + std::wstring(L"';")
      };
   }
   if (m_strPassword.length())
   {
      strConn += std::wstring
      {
         strPassword + std::wstring(L"'") + m_strPassword + std::wstring(L"';")
      };
   }
   if (m_strIntegratedSecurity.length())
   {
      strConn += std::wstring
      {
         strIntegratedSecurity + m_strIntegratedSecurity + std::wstring(L";")
      };
   }
   /**/
   strConn += std::wstring
   {
      strPersistSecurityInfo +
      std::wstring
      {
         m_bPersistSecurityInfo ? std::wstring(L"True") : std::wstring(L"False")
      } +std::wstring(L";")
   };
   /**/
   if (m_strUserID.length())
   {
      strConn += std::wstring
      {
         strUserID + std::wstring(L"'") + m_strUserID + std::wstring(L"';")
      };
   }
   /**/
   if (m_strInitialCatalog.length())
   {
      strConn += std::wstring
      {
         strInitialCatalog + std::wstring(L"'") + m_strInitialCatalog + std::wstring(L"';")
      };
   }
   /**/
   if (m_strDataSource.length())
   {
      strConn += std::wstring
      {
         strDataSource + std::wstring(L"'") + m_strDataSource + std::wstring(L"';")
      };
   }
   /**/
   if (m_strServerSPN.length())
   {
      strConn += std::wstring
      {
         strServerSPN + std::wstring(L"'") + m_strServerSPN + std::wstring(L"';")
      };
   }
   /**/
   return strConn;
}
//-----------------------------------------------------------------------------------------------//
void const __fastcall sql::ConnectInfo::SetConnection(sql::ConnectInfo const & in)
{
   if(in.m_strProvider.length())
      m_strProvider = in.m_strProvider;

   m_strIntegratedSecurity = in.m_strIntegratedSecurity;
   m_strUserID = in.m_strUserID;
   m_strPassword = in.m_strPassword;
   m_strInitialCatalog = in.m_strInitialCatalog;
   m_strDataSource = in.m_strDataSource;
   m_strInitialFileName = in.m_strInitialFileName;
   m_strServerSPN = in.m_strServerSPN;
}
//-----------------------------------------------------------------------------------------------//