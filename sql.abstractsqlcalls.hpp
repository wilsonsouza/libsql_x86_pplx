//-----------------------------------------------------------------------------------------------//
// Created with QT Mult plaform C++ Library
// sql.manager.x86 library v1.0 2012, 2013
//
// Created by Wilson.Souza
//
// Owner Libbs
// Copyright (c) 2012, 2013 Dedalus Prime
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <sql.query.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class _SQLDYNAMICLINK AbstractSQLCalls: public std::shared_ptr<sql::Table>
   {
   public:
      AbstractSQLCalls(std::shared_ptr<sql::Query> const & pSQL):
         std::shared_ptr<sql::Table>(new sql::Table(pSQL->Handle))
      {
      }
      virtual ~AbstractSQLCalls()
      {
         std::shared_ptr<sql::Table>::operator->()->Close();
      }
      sql::Field * operator[](std::wstring const & szFieldName)
      {
         return std::shared_ptr<sql::Table>::operator->()->operator[](szFieldName);
      }
      /* abstract methods */
      bool const Launch(std::wstring const & szValue) = 0;
   };
};
