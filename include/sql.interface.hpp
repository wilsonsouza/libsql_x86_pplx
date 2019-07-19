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
#include <sql.defs.hpp>
namespace sql
{
   class _SQLDYNAMICLINK Interface: public Concurrency::task_group
   {
   public:
      explicit Interface() :task_group(){}
      virtual ~Interface(){}

      SQL_DECLARE_OPERATOR(Interface);
   };
};