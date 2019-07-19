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
#include <sql.Database.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class _SQLDYNAMICLINK Query: public Database
   {
   public:
      Query();
      explicit Query(sql::ConnectInfo const & sqlcon);
      virtual ~Query();
      virtual void const __fastcall Close();
      virtual std::shared_ptr<sql::Query> __fastcall Clone();
      _ConnectionPtr & GetConnectionInterfacePtr();
      SQL_DECLARE_OPERATOR(Query);

      __declspec(property(get=GetConnectionInterfacePtr)) _ConnectionPtr & Handle;
   protected:
      _ConnectionPtr m_pConnectionPtr;
   };
};
//-----------------------------------------------------------------------------------------------//