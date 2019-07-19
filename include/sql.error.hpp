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
   class _SQLDYNAMICLINK Error: public Interface
   {
   public:
      Error();
      Error(_bstr_t const bsd, HRESULT hrn);
      Error(std::shared_ptr<sql::Error> const Error_ptr);
      SQL_DECLARE_OPERATOR(Error);
   protected:
      std::wstring  m_strdescription;
      HRESULT m_hrnumber;
      unsigned int m_uid;
   };
};