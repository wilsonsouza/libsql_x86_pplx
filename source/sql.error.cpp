//-----------------------------------------------------------------------------------------------//
// Created with QT Mult plaform C++ Library
// sqlservermanager dynamic library v1.0 2012
//
// Created by Wilson.Souza
//
// Owner Libbs
// Copyright (c) 2012 Dedalus Prime
//-----------------------------------------------------------------------------------------------//
#include <sql.defs.hpp>
#include <sql.Interface.hpp>
#include <sql.Error.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace sql;
//-----------------------------------------------------------------------------------------------//
sql::Error::Error():Interface(), m_strdescription(std::wstring()), m_hrnumber(-1)
{
}
//-----------------------------------------------------------------------------------------------//
sql::Error::Error(_bstr_t const bsd, HRESULT hrn):Interface(),
m_strdescription((bsd)),
m_hrnumber(hrn)
{
}
//-----------------------------------------------------------------------------------------------//
sql::Error::Error(std::shared_ptr<sql::Error> const Error_ptr):Interface()
{
   if(Error_ptr)
   {
      m_strdescription = Error_ptr.operator*().m_strdescription;
      m_hrnumber       = Error_ptr.operator*().m_hrnumber;
   }
}
//-----------------------------------------------------------------------------------------------//