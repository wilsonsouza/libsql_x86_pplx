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
#include <sql.idate.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class _SQLDYNAMICLINK IDate;
   class _SQLDYNAMICLINK Field: public FieldPtr //field:field_ptr
   {
   public:
      Field();
      explicit Field(FieldPtr const & Ptr);
      virtual ~Field();

      //methods get
      /*get_string(), get_long(), get_unsigned_int()
      get_bool(), get_date(), get_double(), get_value(), get_type(),
      get_size(), get_name(), get_binary_object(),
      get_char(),
      set_value
      */
      virtual std::wstring      const __fastcall GetString();
      virtual long         const __fastcall GetLong();
      virtual unsigned int const __fastcall GetUnsignedInt();
      virtual int          const __fastcall GetInt();
      virtual bool         const __fastcall GetBool();
      virtual IDate        const __fastcall GetDate();
      virtual double       const __fastcall GetDouble();
      virtual _variant_t   const __fastcall GetValue() const;
      virtual long         const __fastcall GetType();
      virtual long         const __fastcall GetSize();
      virtual std::wstring      const __fastcall GetName();
      virtual void       const * __fastcall GetBlob();
      virtual char       const   __fastcall GetChar(); 

      //methods set
      virtual void         const __fastcall SetValue(_variant_t const vtvalue);

      //operators inline
      virtual Field & __fastcall operator =(Field const & Field);

      //operators convert inline
      __inline operator std::wstring() { return GetString(); }
      __inline operator long()         { return GetLong();   }
      __inline operator bool()         { return GetBool();   }
      __inline operator unsigned int() { return GetUnsignedInt();    }
      __inline operator int()          { return GetInt(); }
      __inline operator double()       { return GetDouble(); }
      __inline operator IDate()        { return GetDate(); }

      //propertys
      __declspec(property(get=GetValue, put=SetValue)) _variant_t Value;
      __declspec(property(get=GetString, put=SetString)) std::wstring Text;
      __declspec(property(get=GetLong, put=SetLong)) long Long;
      __declspec(property(get=GetBool, put=SetBool)) bool Bool;
      __declspec(property(get=GetUnsignedInt, put=SetUnsignedInt)) unsigned int UnsignedInt;
      __declspec(property(get=GetInt, put=SetInt)) int Integer;
      __declspec(property(get=GetName, put=SetName)) std::wstring Name;
      __declspec(property(get=GetSize, put=SetSize)) long Size;
      __declspec(property(get=GetType, put=SetType)) long Type;
      __declspec(property(get=GetDate, put=SetDate)) IDate Date;
      __declspec(property(get=GetDouble, put=SetDouble)) double Double;
      __declspec(property(get=GetBlob)) void const * Blob;
      __declspec(property(get=GetChar)) char Char;
   };
   /**/
   typedef sql::Field * shared_field_ptr;
};