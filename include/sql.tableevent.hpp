//-----------------------------------------------------------------------------------------------//
// Created with QT Mult plaform C++ Library
// sqlservermanager dynamic library v1.0 2012
//
// Created by Wilson.Souza
//
// Owner Libbs
// Copyright (c) 2012, 2013 Dedalus Prime
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <sql.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class _SQLDYNAMICLINK Table;
   class _SQLDYNAMICLINK TableEvent: public RecordsetEventsVt
   {
      struct DataTransfer;
   private:
      ULONG m_cRef;
      /* parent to dispatch event */
      Table * m_pTbl;
      std::function<void(long lmsg, std::shared_ptr<TableEvent::DataTransfer> &)> m_notify;
   public:
      /* data transfer */
      struct DataTransfer
      {
         LONG lFields;
         VARIANT vFields;
         EventStatusEnum * pStatus;
         struct _Recordset * pRecordset;
         EventReasonEnum eReason;
         struct Error * pError;
         VARIANT_BOOL * pMoreData;
         long lProgress;
         long lMaxProgress;
         LONG lRecords;
         unsigned int uMessage;
         Table * pTbl;
         /**/
         virtual void __stdcall Initialize()
         {
            lFields = 0;
            vFields = VARIANT();
            pStatus = nullptr;
            pRecordset = nullptr;
            eReason = adRsnClose;
            pError = nullptr;
            pMoreData = nullptr;
            lProgress = 0;
            lMaxProgress = 0;
            lRecords = 0;
            uMessage = 0;
            pTbl = nullptr;
         }
         /* expand macro methods*/
         SQL_DECLARE_OPERATOR(DataTransfer)
      };
      /* enum messages */
      typedef enum EVENTS
      {
         RAW_WILLCHANGEFIELD = 0x1000,
         RAW_FIELDCHANGECOMPLETE,
         RAW_WILLCHANGERECORD,
         RAW_RECORDCHANGECOMPLETE,
         RAW_WILLCHANGERECORDSET,
         RAW_RECORDSETCHANGECOMPLETE,
         RAW_WILLMOVE,
         RAW_MOVECOMPLETE,
         RAW_ENDOFRECORDSET,
         RAW_FETCHPROGRESS,
         RAW_FETCHCOMPLETE
      }EVENTS, *PEVENTS, *LPEVENTS;
      typedef std::function < void(long, std::shared_ptr<TableEvent::DataTransfer> &) > OnNotify;
   public:
      TableEvent() : m_pTbl(nullptr), m_cRef(0), m_notify(nullptr){}
      explicit TableEvent(Table * pTbl) :m_pTbl(pTbl), m_cRef(0), m_notify(nullptr){}
      virtual ~TableEvent(){}
      void Bind(TableEvent::OnNotify lpOnNotify);
      /* */
      STDMETHODIMP QueryInterface(REFIID riid, void ** ppv);
      STDMETHODIMP_(ULONG) AddRef();
      STDMETHODIMP_(ULONG) Release();

      STDMETHODIMP raw_WillChangeField(LONG lFields, VARIANT vFields,
         EventStatusEnum * pStatus, struct _Recordset *pRecordset);

      STDMETHODIMP raw_FieldChangeComplete(LONG lFields, VARIANT vFields,
         struct Error *pError, EventStatusEnum * pStatus, struct _Recordset *pRecordset);

      STDMETHODIMP raw_WillChangeRecord(EventReasonEnum eReason, LONG lRecords,
         EventStatusEnum * pStatus, struct _Recordset *pRecordset);

      STDMETHODIMP raw_RecordChangeComplete(EventReasonEnum eReason, LONG lRecords,
         struct Error *pError, EventStatusEnum * pStatus, struct _Recordset *pRecordset);

      STDMETHODIMP raw_WillChangeRecordset(EventReasonEnum eReason,
         EventStatusEnum * pStatus, struct _Recordset *pRecordset);

      STDMETHODIMP raw_RecordsetChangeComplete(EventReasonEnum eReason,
         struct Error *pError, EventStatusEnum * pStatus, struct _Recordset *pRecordset);

      STDMETHODIMP raw_WillMove( EventReasonEnum eReason,
         EventStatusEnum *adStatus, struct _Recordset *pRecordset);

      STDMETHODIMP raw_MoveComplete( EventReasonEnum eReason,
         struct Error *pError, EventStatusEnum *adStatus, struct _Recordset *pRecordset);

      STDMETHODIMP raw_EndOfRecordset( VARIANT_BOOL *pMoreData,
         EventStatusEnum *adStatus, struct _Recordset *pRecordset);

      STDMETHODIMP raw_FetchProgress( long lProgress,
         long lMaxProgress, EventStatusEnum *pStatus, struct _Recordset *pRecordset);

      STDMETHODIMP raw_FetchComplete( struct Error *pError, 
         EventStatusEnum *pStatus, struct _Recordset *pRecordset);
      /**/
   protected:
      virtual void const __fastcall Notify(unsigned int uMessage, 
         std::shared_ptr<TableEvent::DataTransfer> & pData);
      virtual std::shared_ptr<TableEvent::DataTransfer> AllocDataTransfer();
   };
};
//-----------------------------------------------------------------------------------------------//
