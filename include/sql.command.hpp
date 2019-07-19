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
#include <sql.connectinfo.hpp>

namespace sql
{
   class _SQLDYNAMICLINK Table;
   class _SQLDYNAMICLINK Database;
   class _SQLDYNAMICLINK Command: public ConnectInfo, public _Command
   {
   public:
      Command();
      explicit Command(sql::Database const & db);
      virtual ~Command(){}
      std::shared_ptr<sql::Table> Execute(std::wstring const & sqlcmd);
      SQL_DECLARE_OPERATOR(Command);
   };
};