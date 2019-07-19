//-----------------------------------------------------------------------------------------------//
// Created with QT Mult plaform C++ Library
// sqlservermanager dynamic library v1.0 2012
//
// Created by Wilson.Souza
//
// Owner Libbs
// Copyright (c) 2012 Dedalus Prime
//-----------------------------------------------------------------------------------------------//
#include <sql.command.hpp>
#include <sql.table.hpp>
#include <sql.database.hpp>
//-----------------------------------------------------------------------------------------------//
sql::Command::Command():ConnectInfo()
{
   CreateInstance(__uuidof(::Command));
}
//-----------------------------------------------------------------------------------------------//
sql::Command::Command(sql::Database const & db):ConnectInfo()
{
   CreateInstance(__uuidof(::Command));
   _CommandPtr::operator->()->putref_ActiveConnection(db);
   SetConnection(db);
}
//-----------------------------------------------------------------------------------------------//
std::shared_ptr<sql::Table> sql::Command::Execute(std::wstring const & sqlcmd)
{
   VARIANT vrecordsaffected = VARIANT();
   _RecordsetPtr ptr = _CommandPtr::operator->()->Execute(&vrecordsaffected, nullptr, adCmdText);

   if(ptr != nullptr)
   {
      ptr->Requery(adCmdUnspecified);
      std::shared_ptr<sql::Table>(new sql::Table(ptr));
   }
   return nullptr;
}
//-----------------------------------------------------------------------------------------------//
