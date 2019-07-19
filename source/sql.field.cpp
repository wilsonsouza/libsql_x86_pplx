//-----------------------------------------------------------------------------------------------//
// Created with QT Mult plaform C++ Library
// sqlservermanager dynamic library v1.0 2012
//
// Created by Wilson.Souza
//
// Owner Libbs
// Copyright (c) 2012 Dedalus Prime
//-----------------------------------------------------------------------------------------------//
#include <sql.field.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace sql;
//-----------------------------------------------------------------------------------------------//
sql::Field::Field()
{
   CreateInstance(__uuidof(::Field));
}
//-----------------------------------------------------------------------------------------------//
sql::Field::Field(FieldPtr const & Ptr)
{
   FieldPtr::operator=(Ptr);
}
//-----------------------------------------------------------------------------------------------//
sql::Field::~Field()
{
   FieldPtr::operator->()->Release();
}
//-----------------------------------------------------------------------------------------------//
std::wstring const __fastcall sql::Field::GetString()
{
   _variant_t v = GetValue();

   if(v.vt == VT_BSTR || v.vt == VT_LPSTR || v.vt == VT_LPWSTR)
      return std::wstring(v.operator bstr_t());

   if(v.vt != VT_NULL)
      return std::wstring(v.operator bstr_t());

   return std::wstring();
}
//-----------------------------------------------------------------------------------------------//
long const __fastcall sql::Field::GetLong()
{
   _variant_t v = GetValue();

   if(v.vt == VT_DECIMAL || v.vt == VT_INT || v.vt == VT_BOOL || v.vt == VT_UI4)
      return v.operator long();

   return 0L;
}
//-----------------------------------------------------------------------------------------------//
unsigned int const __fastcall sql::Field::GetUnsignedInt()
{
   _variant_t v = GetValue();

   if(v.vt == VT_UINT || v.vt == VT_DECIMAL || v.vt == VT_UI1 || v.vt == VT_UI2 || v.vt == VT_UI4)
      return v.operator unsigned int();

   return 0;
}
//-----------------------------------------------------------------------------------------------//
int const __fastcall sql::Field::GetInt()
{
   _variant_t v = GetValue();

   if(v.vt == VT_INT || v.vt == VT_I4)
      return v.operator int();

   return 0;
}
//-----------------------------------------------------------------------------------------------//
char const __fastcall sql::Field::GetChar()
{
   _variant_t v = GetValue();

   if(v.vt == VT_BSTR)
   {
      std::wstring strT = v.operator _bstr_t();
      return *strT.c_str();
   }
   return 0;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall sql::Field::GetBool()
{
   _variant_t v = GetValue();

   if(v.vt == VT_BOOL)
      return v.operator bool();

   return false;
}
//-----------------------------------------------------------------------------------------------//
IDate const __fastcall sql::Field::GetDate()
{
   _variant_t v = GetValue();

   if (v.vt == VT_DATE)
      return IDate(v.operator bstr_t());

   return IDate();
}
//-----------------------------------------------------------------------------------------------//
void const * __fastcall sql::Field::GetBlob()
{
   _variant_t v = GetValue();

   if(v.vt == VT_BLOB || v.vt == VT_BLOB_OBJECT || v.vt == VT_BLOB_PROPSET)
      return (void *)&v.operator _bstr_t();
   return nullptr;
}
//-----------------------------------------------------------------------------------------------//
_variant_t const __fastcall sql::Field::GetValue() const
{
   _variant_t v = _variant_t();

   if(FieldPtr::operator->()->get_Value(&v) == S_OK)
   {
      if(v.vt == VT_NULL)
         return _variant_t();
      else
         return v;
   }
   return v;
}
//-----------------------------------------------------------------------------------------------//
void const __fastcall sql::Field::SetValue(_variant_t const vtvalue)
{
   if(vtvalue.vt != VT_NULL)
      FieldPtr::operator->()->PutValue(_variant_t(vtvalue));
}
//-----------------------------------------------------------------------------------------------//
long const __fastcall sql::Field::GetType()
{
   long ltype = SQL_FIELD_UNKNOW_TYPE;
   int nType = FieldPtr::operator->()->Type;

   switch(nType)
   {
      case adBigInt:
         ltype = SQL_FIELD_INT64;
         break;
      case adBinary:
      case adBoolean:
         ltype = SQL_FIELD_BOOL;
         break;
      case adChar:
      case adVarBinary:
      case adVarChar:
         ltype = SQL_FIELD_STRING;
         break;
      case adDate:
      case adDBDate:
         ltype = SQL_FIELD_DATE;
         break;
      case adDBTime:
      case adDBTimeStamp:
         ltype = SQL_FIELD_TIME|SQL_FIELD_DATE;
         break;
      case adNumeric:
      case adDecimal:
         ltype = SQL_FIELD_INT32;
         break;
      case adLongVarBinary:
      case adLongVarChar:
      case adLongVarWChar:
         ltype = SQL_FIELD_WORDCHAR;
         break;
      case adCurrency:
         ltype = SQL_FIELD_CURRENCY;
         break;
      case adWChar:
      case adVarWChar:
         ltype = SQL_FIELD_WCHAR_T;
         break;
      case adSmallInt:
         ltype = SQL_FIELD_INT16;
         break;
      case adUnsignedBigInt:
      case adUnsignedInt:
      case adUnsignedSmallInt:
      case adUnsignedTinyInt:
      case adInteger:
         ltype = SQL_FIELD_DWORD;
      default:
         return SQL_FIELD_UNKNOW_TYPE;
   }

   return ltype;
}
//-----------------------------------------------------------------------------------------------//
long const __fastcall sql::Field::GetSize()
{
   long loffset = 0;

   if(FieldPtr::operator->()->get_DefinedSize(&loffset) == S_OK)
      return loffset;

   return 0;
}
//-----------------------------------------------------------------------------------------------//
std::wstring const __fastcall sql::Field::GetName()
{
   bstr_t b = FieldPtr::operator->()->Name;

   if(b.length() > 0)
      return std::wstring(b);

   return std::wstring();
}
//-----------------------------------------------------------------------------------------------//
sql::Field & __fastcall sql::Field::operator =(const sql::Field &Field)
{
   FieldPtr::operator=(Field);
   return *this;
}
//-----------------------------------------------------------------------------------------------//
double const __fastcall sql::Field::GetDouble()
{
   _variant_t v = GetValue();

   if(v.vt == VT_I8 || v.vt == VT_UI8 || v.vt == VT_DECIMAL)
      return v.operator double();

   return 0;
}
//-----------------------------------------------------------------------------------------------//