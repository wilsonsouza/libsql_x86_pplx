//-----------------------------------------------------------------------------------------------//
// Created with QT Mult plaform C++ Library
// sqlservermanager dynamic library v1.0 2012
//
// Created by Wilson.Souza
//
// Owner Libbs
// Copyright (c) 2012 Dedalus Prime
//-----------------------------------------------------------------------------------------------//
#include <sql.database.hpp>

using namespace sql;
#if defined(_COMINTERFACE_PTR)
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP ConnectionsEventImpl::QueryInterface(REFIID riid, void ** ppv) 
{
   *ppv = NULL;
   if (riid == __uuidof(IUnknown) || riid == __uuidof(ConnectionEventsVt)) 
      *ppv = this;

   if (*ppv == NULL)
      return ResultFromScode(E_NOINTERFACE);

   AddRef();
   return NOERROR;
}
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP_(ULONG) ConnectionsEventImpl::AddRef() 
{ 
   return ++m_cRef; 
};
//-----------------------------------------------------------------------------------------------//
STDMETHODIMP_(ULONG) ConnectionsEventImpl::Release() 
{ 
   if (0 != --m_cRef) 
      return m_cRef;
   delete this;
   return 0;
}
#endif
//-----------------------------------------------------------------------------------------------//
HRESULT __stdcall  ConnectionsEventImpl::raw_InfoMessage( struct _Error *pError, 
                                         EventStatusEnum *pStatus,
                                         struct _Connection *pConnection) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->pError = (pError);
   pData->pStatus = (pStatus);
   pData->pConnection = (pConnection);
   /**/
   Notify(RAW_INFOMESSAGE, pData);
   return S_OK;
}
//-----------------------------------------------------------------------------------------------//
HRESULT __stdcall  ConnectionsEventImpl::raw_BeginTransComplete( LONG lTransactionLevel,
                                                 struct _Error *pError,
                                                 EventStatusEnum *pStatus,
                                                 struct _Connection *pConnection) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->pError = (pError);
   pData->pStatus = (pStatus);
   pData->pConnection = (pConnection);
   pData->lTransactionLevel = lTransactionLevel;
   /**/
   Notify(RAW_BEGINTRANSCOMPLETE, pData);
   return S_OK;
}
//-----------------------------------------------------------------------------------------------//
HRESULT __stdcall  ConnectionsEventImpl::raw_CommitTransComplete( struct _Error *pError,
                                                  EventStatusEnum *pStatus,
                                                  struct _Connection *pConnection)
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->pError = (pError);
   pData->pStatus = (pStatus);
   pData->pConnection = (pConnection);
   /**/
   Notify(RAW_COMMITTRANSCOMPLETE, pData);
   return S_OK;
}
//-----------------------------------------------------------------------------------------------//
HRESULT __stdcall  ConnectionsEventImpl::raw_RollbackTransComplete( struct _Error *pError,
                                                    EventStatusEnum *pStatus,
                                                    struct _Connection *pConnection) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->pError = (pError);
   pData->pStatus = (pStatus);
   pData->pConnection = (pConnection);
   /**/
   Notify(RAW_ROLLBACKTRANSCOMPLETE, pData);
   return S_OK;
}
//-----------------------------------------------------------------------------------------------//
HRESULT __stdcall  ConnectionsEventImpl::raw_WillExecute( BSTR * pSource,
                                          CursorTypeEnum * pCursorType,
                                          LockTypeEnum * pLockType,
                                          long * pOptions,
                                          EventStatusEnum *pStatus,
                                          struct _Command *pCommand,
                                          struct _Recordset *pRecordset,
                                          struct _Connection *pConnection) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->pSource = std::make_shared<BSTR>(*pSource);
   pData->pCursorType = (pCursorType);
   pData->pLockType = (pLockType);
   pData->pOptions = std::make_shared<long>(*pOptions);
   pData->pStatus = (pStatus);
   pData->pCommand = (pCommand);
   pData->pRecordset = pRecordset;
   pData->pConnection = (pConnection);
   /**/
   Notify(RAW_WILLEXECUTE, pData);
   return S_OK;
}
//-----------------------------------------------------------------------------------------------//
HRESULT __stdcall  ConnectionsEventImpl::raw_ExecuteComplete( LONG lRecordsAffected,
                                              struct _Error *pError,
                                              EventStatusEnum *pStatus,
                                              struct _Command *pCommand,
                                              struct _Recordset *pRecordset,
                                              struct _Connection *pConnection) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->lRecordsAffected = lRecordsAffected;
   pData->pError = (pError);
   pData->pStatus = (pStatus);
   pData->pCommand = (pCommand);
   pData->pRecordset = (pRecordset);
   pData->pConnection = (pConnection);
   /**/
   Notify(RAW_EXECUTECOMPLETE, pData);
   return S_OK;
}
//-----------------------------------------------------------------------------------------------//
HRESULT __stdcall  ConnectionsEventImpl::raw_WillConnect( BSTR * pConnectionString,
                                          BSTR *pUserID,
                                          BSTR *pPassword,
                                          long *pOptions,
                                          EventStatusEnum *pStatus,
                                          struct _Connection *pConnection) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->pConnectionString = std::make_shared<BSTR>(*pConnectionString);
   pData->pUserID = std::make_shared<BSTR>(*pUserID);
   pData->pPassword = std::make_shared<BSTR>(*pPassword);
   pData->pOptions = std::make_shared<long>(*pOptions);
   pData->pStatus = (pStatus);
   pData->pConnection = (pConnection);
   /**/
   Notify(RAW_WILLCONNECT, pData);
   return S_OK;
}
//-----------------------------------------------------------------------------------------------//
HRESULT __stdcall  ConnectionsEventImpl::raw_ConnectComplete( struct _Error *pError,
                                              EventStatusEnum *pStatus,
                                              struct _Connection *pConnection) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->pError = (pError);
   pData->pStatus = (pStatus);
   pData->pConnection = (pConnection);
   /**/
   Notify(RAW_CONNECTCOMPLETE, pData);
   return S_OK;
}
//-----------------------------------------------------------------------------------------------//
HRESULT __stdcall  ConnectionsEventImpl::raw_Disconnect( EventStatusEnum *pStatus, struct _Connection *pConnection) 
{
   std::shared_ptr<DataTransfer> pData = AllocDataTransfer();
   /**/
   pData->pStatus = (pStatus);
   pData->pConnection = (pConnection);
   /**/
   Notify(RAW_DISCONNECT, pData);
   return S_OK;
}
//-----------------------------------------------------------------------------------------------//
void const __fastcall ConnectionsEventImpl::Notify(unsigned int uMessage,
   std::shared_ptr<ConnectionsEventImpl::DataTransfer> & pData)
{
   /**/
   if (m_lpOnDispatchEvent)
   {
      if (m_pDatabase)
      {
         pData->pDatabase = m_pDatabase;
         /* call by pplx task library */
         pData->pDatabase->run([this, uMessage, &pData]
         {
            m_lpOnDispatchEvent(long(uMessage), pData);
         });
      }
      else
         m_lpOnDispatchEvent(long(uMessage), pData);
   }
   else
      *pData->pStatus = adStatusUnwantedEvent;
   /**/
}
//-----------------------------------------------------------------------------------------------//
std::shared_ptr<sql::ConnectionsEventImpl::DataTransfer> __stdcall ConnectionsEventImpl::AllocDataTransfer()
{
   return std::shared_ptr<DataTransfer>(new DataTransfer());
}
//-----------------------------------------------------------------------------------------------//
void ConnectionsEventImpl::Bind(ConnectionsEventImpl::OnDispatchEvent lpOnDispatchEvent)
{
   if (lpOnDispatchEvent)
      m_lpOnDispatchEvent = lpOnDispatchEvent;
}
//-----------------------------------------------------------------------------------------------//
