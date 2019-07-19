//-----------------------------------------------------------------------------------------------//
// Created with pplx Mult plaform C++ Library
// sqlservermanager dynamic library v1.0 2012
//
// Created by Wilson.Souza
//
// Owner
// Copyright (c) 2012, 2015
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <sql.defs.hpp>

namespace sql
{
   class _SQLDYNAMICLINK IDate
   {
   public:
      IDate()
      {
         m_value = _variant_t();
      }
      IDate(_variant_t value)
      {
         m_value = value;
      }
      virtual DATE const __stdcall GetValue()
      {
         return m_value.date;
      }
      /* propertys */
      __declspec(property(get = GetValue)) DATE Value;
   private:
      _variant_t m_value;
   };
};