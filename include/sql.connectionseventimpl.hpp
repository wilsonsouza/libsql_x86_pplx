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
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class _SQLDYNAMICLINK Database;
   struct _SQLDYNAMICLINK ConnectionsEventImpl: protected ConnectionEventsVt
   {
      struct DataTransfer;
   private:
      ULONG m_cRef;
      Database * m_pDatabase;
      std::function<void(long lMsg, std::shared_ptr<ConnectionsEventImpl::DataTransfer> &)> 
         m_lpOnDispatchEvent;
      /**/
   public:
      struct DataTransfer
      {
         struct _Error * pError;
         EventStatusEnum * pStatus;
         struct _Connection * pConnection;
         LONG lTransactionLevel;
         std::shared_ptr<BSTR> pSource;
         CursorTypeEnum * pCursorType;
         LockTypeEnum * pLockType;
         std::shared_ptr<long> pOptions;
         struct _Command * pCommand;
         struct _Recordset * pRecordset;
         LONG lRecordsAffected;
         std::shared_ptr<BSTR> pConnectionString;
         std::shared_ptr<BSTR> pUserID;
         std::shared_ptr<BSTR> pPassword;
         Database * pDatabase;
         /**/
         void __stdcall Initialize()
         {
            pError = nullptr;
            pStatus = nullptr;
            pConnection = nullptr;
            lTransactionLevel = 0;
            pSource = nullptr;
            pCursorType = nullptr;
            pLockType = nullptr;
            pOptions = nullptr;
            pCommand = nullptr;
            pRecordset = nullptr;
            lRecordsAffected = 0;
            pConnectionString = nullptr;
            pUserID = nullptr;
            pPassword = nullptr;
            pDatabase = nullptr;
         }
         /**/
         SQL_DECLARE_OPERATOR(DataTransfer);
      };
      /**/
      enum
      {
         RAW_INFOMESSAGE = 0x2000,
         RAW_BEGINTRANSCOMPLETE,
         RAW_COMMITTRANSCOMPLETE,
         RAW_ROLLBACKTRANSCOMPLETE,
         RAW_WILLEXECUTE,
         RAW_EXECUTECOMPLETE,
         RAW_WILLCONNECT,
         RAW_CONNECTCOMPLETE,
         RAW_DISCONNECT
      };
      /**/
      typedef std::function<void(long lMsg, std::shared_ptr<ConnectionsEventImpl::DataTransfer> &)> OnDispatchEvent;
   public:
      ConnectionsEventImpl() : m_lpOnDispatchEvent(nullptr), m_cRef(0), m_pDatabase(nullptr){}
      explicit ConnectionsEventImpl(Database * pDatabase) :
         m_lpOnDispatchEvent(nullptr), m_cRef(0)
      {
         m_pDatabase = pDatabase;
      }
      virtual ~ConnectionsEventImpl(){}
      void Bind(ConnectionsEventImpl::OnDispatchEvent lpDispatchEvent);
#if defined(_COMINTERFACE_PTR)
      STDMETHODIMP QueryInterface(REFIID riid, void ** ppv);
      STDMETHODIMP_(ULONG) AddRef();
      STDMETHODIMP_(ULONG) Release();
#endif

#if !defined(_CONNECTIONSEVENT_OLD)
    virtual HRESULT __stdcall raw_InfoMessage (struct _Error * pError, 
       enum EventStatusEnum * adStatus, struct _Connection * pConnection );
    virtual HRESULT __stdcall raw_BeginTransComplete (long TransactionLevel,
        struct _Error * pError, enum EventStatusEnum * adStatus, struct _Connection * pConnection );
    virtual HRESULT __stdcall raw_CommitTransComplete (struct _Error * pError,
        enum EventStatusEnum * adStatus, struct _Connection * pConnection );
    virtual HRESULT __stdcall raw_RollbackTransComplete (struct _Error * pError,
        enum EventStatusEnum * adStatus, struct _Connection * pConnection );
    virtual HRESULT __stdcall raw_WillExecute (BSTR * Source,
        enum CursorTypeEnum * CursorType, enum LockTypeEnum * LockType, long * Options, enum EventStatusEnum * adStatus,
        struct _Command * pCommand, struct _Recordset * pRecordset,  struct _Connection * pConnection );
    virtual HRESULT __stdcall raw_ExecuteComplete (long RecordsAffected,
        struct _Error * pError, enum EventStatusEnum * adStatus, struct _Command * pCommand, struct _Recordset * pRecordset,
        struct _Connection * pConnection );
    virtual HRESULT __stdcall raw_WillConnect (BSTR * ConnectionString,
        BSTR * UserID,  BSTR * Password,  long * Options, enum EventStatusEnum * adStatus, struct _Connection * pConnection );
    virtual HRESULT __stdcall raw_ConnectComplete (struct _Error * pError,
        enum EventStatusEnum * adStatus, struct _Connection * pConnection );
    virtual HRESULT __stdcall raw_Disconnect (enum EventStatusEnum * adStatus, struct _Connection * pConnection );

#else 
      STDMETHODIMP raw_InfoMessage( struct _Error *pError, EventStatusEnum *pStatus, struct _Connection *pConnection);
      STDMETHODIMP raw_BeginTransComplete( LONG lTransactionLevel, struct _Error *pError, EventStatusEnum *pStatus,
                                           struct _Connection *pConnection);
      STDMETHODIMP raw_CommitTransComplete( struct _Error *pError, 
                                            EventStatusEnum *pStatus,
                                            struct _Connection *pConnection);
      STDMETHODIMP raw_RollbackTransComplete( struct _Error *pError, 
                                              EventStatusEnum *pStatus,
                                              struct _Connection *pConnection);
      STDMETHODIMP raw_WillExecute( BSTR *pSource,
                                    CursorTypeEnum *pCursorType,
                                    LockTypeEnum *pLockType,
                                    long *pOptions,
                                    EventStatusEnum *pStatus,
                                    struct _Command *pCommand,
                                    struct _Recordset *pRecordset,
                                    struct _Connection *pConnection);
      STDMETHODIMP raw_ExecuteComplete( LONG lRecordsAffected,
                                        struct _Error *pError,
                                        EventStatusEnum *pStatus,
                                        struct _Command *pCommand,
                                        struct _Recordset *pRecordset,
                                        struct _Connection *pConnection);
      STDMETHODIMP raw_WillConnect( BSTR *pConnectionString,
                                    BSTR *pUserID,
                                    BSTR *pPassword,
                                    long *pOptions,
                                    EventStatusEnum *pStatus,
                                    struct _Connection *pConnection);
      STDMETHODIMP raw_ConnectComplete( struct _Error *pError,
                                        EventStatusEnum *pStatus,
                                        struct _Connection *pConnection);
      STDMETHODIMP raw_Disconnect( EventStatusEnum *pStatus, struct _Connection *pConnection);
#endif
   protected:
      virtual void const __fastcall Notify(unsigned int uMessage, std::shared_ptr<sql::ConnectionsEventImpl::DataTransfer> & pData);
      virtual std::shared_ptr<sql::ConnectionsEventImpl::DataTransfer> __stdcall AllocDataTransfer();
   };
};
//-----------------------------------------------------------------------------------------------//
