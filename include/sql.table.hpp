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
#include <sql.field.hpp>
#include <sql.connectinfo.hpp>
#include <sql.tableevent.hpp>
#include <hash_map>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   typedef std::hash_map<std::wstring, sql::Field *> FieldListMapper;
   /**/
   class _SQLDYNAMICLINK Database;
   class _SQLDYNAMICLINK Table: 
      public ConnectInfo, 
      public _RecordsetPtr, public FieldListMapper
   {
   public:
      Table();
      explicit Table(sql::ConnectInfo const & sqlconn);
      explicit Table(_RecordsetPtr const & recptr);
      explicit Table(_ConnectionPtr const & conptr);
      virtual ~Table();
      virtual bool const   __fastcall Open(std::wstring const & strTableName,
                                           CommandTypeEnum ctCommandType = adCmdText,
                                           CursorTypeEnum ctCursorType = adOpenStatic,
                                           LockTypeEnum ltLockType = adLockOptimistic);

      //process
      virtual bool const   __fastcall GetEof();
      virtual bool const   __fastcall GetBof();
      virtual bool const   __fastcall Go(long const lrecno = 0);
      virtual long const   __fastcall GetReccount();
      virtual long const   __fastcall GetRecno();
      virtual long const   __fastcall GetLastrec();
      virtual bool const   __fastcall Gotop();
      virtual bool const   __fastcall GoBottom();

      //move
      virtual bool const   __fastcall Next();
      virtual bool const   __fastcall Previous();
      virtual bool const   __fastcall Skip(long lrecno = 0);

      //Query manager
      virtual void const   __fastcall Close();

      //Start events
      virtual void const   __fastcall SetRecordsetPtrEventsClass();
      virtual void const   __fastcall FinalizeRecordsetPtrEventsClass();

      //Name
      virtual sql::Field * __fastcall operator[](std::wstring const & strName);
      virtual sql::Field * __fastcall operator[](unsigned int uIndex);
      sql::Field * __fastcall GetFieldByName(std::wstring const & strName) const;
      sql::Field * __fastcall GetFieldByIndex(unsigned int uIndex);
      //inlie
      virtual Field * __stdcall GetField(std::wstring const & szName) const throw()
      {
         return GetFieldByName(szName);
      }
      virtual Field * __stdcall GetField(unsigned int uFieldIndex) throw()
      {
         return GetFieldByIndex(uFieldIndex);
      }
      virtual _RecordsetPtr & __stdcall GetRecordsetPtrHandle()
      {
         return m_recordset;
      }
      //Fields
      virtual FieldListMapper & __fastcall GetFieldList();

      //logical result
      virtual bool const   __fastcall GetActived();

      SQL_DECLARE_OPERATOR(Table);

      //propertys
      __declspec(property(get=GetFieldList)) FieldListMapper & Fields;
      __declspec(property(get=GetActived)) bool const Actived;
      __declspec(property(get=GetEof)) bool Eof;
      __declspec(property(get=GetBof)) bool Bof;
      __declspec(property(get=GetReccount)) long const Reccount;
      __declspec(property(get=GetRecno)) long const Recno;
      __declspec(property(get=GetReccount)) long const Lastrec;
      __declspec(property(get = GetRecordsetPtrHandle)) _RecordsetPtr & Handle;

   protected:
      virtual std::string __stdcall format_com_error( _com_error e );

   protected:
      long m_lRecno;
      HRESULT m_hSuccess;
      DWORD m_dwRecordEvent;
      IConnectionPointContainer *m_pConnPointC;
      IConnectionPoint *m_pConnPoint;
      IUnknown *m_pUnknown;
      std::shared_ptr<sql::TableEvent> m_pTableEvent;
      _RecordsetPtr m_recordset;
   };
};
//-----------------------------------------------------------------------------------------------//
