//-----------------------------------------------------------------------------------------------//
// Created with QT Mult plaform C++ Library
// sqlservermanager dynamic library v1.0 2012
//
// Created by Wilson.Souza
//
// Owner Libbs
// Copyright (c) 2012, 2013 Dedalus Prime
//-----------------------------------------------------------------------------------------------//
#include <sql.tableevent.hpp>
#include <sql.table.hpp>
using namespace sql;
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP TableEvent::raw_WillChangeField(LONG lFields,
   VARIANT vFields, EventStatusEnum * pStatus, struct _Recordset *pRecordset) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->lFields = lFields;
   pData->vFields = vFields;
   pData->pStatus = pStatus;
   pData->pRecordset = pRecordset;
   /* emit object event*/
   Notify(RAW_WILLCHANGEFIELD, pData);
   return S_OK;
}
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP TableEvent::raw_FieldChangeComplete(LONG lFields, VARIANT vFields,
struct Error *pError, EventStatusEnum *pStatus, struct _Recordset *pRecordset)
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->lFields = lFields;
   pData->vFields = vFields;
   pData->pError  = pError;
   pData->pStatus = pStatus;
   pData->pRecordset = pRecordset;
   /**/
   Notify(RAW_FIELDCHANGECOMPLETE, pData);
   return S_OK;
}
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP TableEvent::raw_WillChangeRecord(EventReasonEnum eReason,
   LONG lRecords, EventStatusEnum *pStatus, struct _Recordset *pRecordset)
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->eReason = eReason;
   pData->lRecords = lRecords;
   pData->pStatus = pStatus;
   pData->pRecordset = pRecordset;
   /**/
   Notify(RAW_WILLCHANGERECORD, pData);
   return S_OK;
}
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP TableEvent::raw_RecordChangeComplete(EventReasonEnum eReason,
   LONG lRecords, struct Error *pError, EventStatusEnum *pStatus, struct _Recordset *pRecordset)
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->eReason = eReason;
   pData->lRecords = lRecords;
   pData->pError = pError;
   pData->pStatus = pStatus;
   pData->pRecordset = pRecordset;
   /**/
   Notify(RAW_RECORDCHANGECOMPLETE, pData);
   return S_OK;
}
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP TableEvent::raw_WillChangeRecordset( EventReasonEnum eReason,
   EventStatusEnum *pStatus, struct _Recordset *pRecordset) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->eReason = eReason;
   pData->pStatus = pStatus;
   pData->pRecordset = pRecordset;
   /**/
   Notify(RAW_WILLCHANGERECORDSET, pData);
   return S_OK;
}
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP TableEvent::raw_RecordsetChangeComplete( EventReasonEnum eReason,
                                                     struct Error *pError,
                                                     EventStatusEnum *pStatus,
                                                     struct _Recordset *pRecordset) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->eReason = eReason;
   pData->pError = pError;
   pData->pStatus = pStatus;
   pData->pRecordset = pRecordset;
   /**/
   Notify(RAW_RECORDCHANGECOMPLETE, pData);
   return S_OK;
};
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP TableEvent::raw_WillMove( EventReasonEnum eReason, 
                                      EventStatusEnum *pStatus,
                                      struct _Recordset *pRecordset) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->eReason = eReason;
   pData->pStatus = pStatus;
   pData->pRecordset = pRecordset;
   /**/
   Notify(RAW_WILLMOVE, pData);
   return S_OK;
};
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP TableEvent::raw_MoveComplete( EventReasonEnum eReason,
                                          struct Error *pError,
                                          EventStatusEnum *pStatus,
                                          struct _Recordset *pRecordset) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->eReason = eReason;
   pData->pError = pError;
   pData->pStatus = pStatus;
   pData->pRecordset = pRecordset;
   return S_OK;
};
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP TableEvent::raw_EndOfRecordset( VARIANT_BOOL *pMoreData,
                                            EventStatusEnum *pStatus,
                                            struct _Recordset *pRecordset) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->pMoreData = pMoreData;
   pData->pStatus = pStatus;
   pData->pRecordset = pRecordset;
   /**/
   Notify(RAW_ENDOFRECORDSET, pData);
   return S_OK;
};
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP TableEvent::raw_FetchProgress( long lProgress,
                                           long lMaxProgress,
                                           EventStatusEnum *pStatus,
                                           struct _Recordset *pRecordset) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->lProgress = lProgress;
   pData->lMaxProgress = lMaxProgress;
   pData->pStatus = pStatus;
   pData->pRecordset = pRecordset;
   /**/
   Notify(RAW_FETCHPROGRESS, pData);
   return S_OK;
};
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP TableEvent::raw_FetchComplete( struct Error *pError,
                                           EventStatusEnum *pStatus,
                                           struct _Recordset *pRecordset) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->pError = pError;
   pData->pStatus = pStatus;
   pData->pRecordset = pRecordset;
   /**/
   Notify(RAW_FETCHCOMPLETE, pData);
   return S_OK;
};
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP TableEvent::QueryInterface(REFIID riid, void ** ppv) 
{
   *ppv = NULL;
   if (riid == __uuidof(IUnknown) || riid == __uuidof(RecordsetEventsVt)) 
      *ppv = this;

   if (*ppv == NULL)
      return ResultFromScode(E_NOINTERFACE);

   AddRef();
   return NOERROR;
}
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP_(ULONG) TableEvent::AddRef() 
{ 
   return ++m_cRef; 
}
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP_(ULONG) TableEvent::Release() 
{ 
   if (0 != --m_cRef) 
      return m_cRef;
   delete this;
   return 0;
}
//-----------------------------------------------------------------------------------------------//
void const __fastcall TableEvent::Notify(unsigned int uMessage, 
   std::shared_ptr<TableEvent::DataTransfer> & pData)
{
   if (m_notify)
   {
      pData->pTbl = m_pTbl;
      m_notify(long(uMessage), pData);
   }
   else
      *pData->pStatus = adStatusUnwantedEvent;
   /**/
}
//-----------------------------------------------------------------------------------------------//
std::shared_ptr<TableEvent::DataTransfer> TableEvent::AllocDataTransfer()
{
   return std::shared_ptr<DataTransfer>(new DataTransfer());
}
//-----------------------------------------------------------------------------------------------//
void TableEvent::Bind(TableEvent::OnNotify lpOnNotify)
{
   if (lpOnNotify)
      m_notify = lpOnNotify;
}
//-----------------------------------------------------------------------------------------------//

