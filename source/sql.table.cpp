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
#include <sql.table.hpp>
#include <string>
//-----------------------------------------------------------------------------------------------//
using namespace sql;
using namespace concurrency;
//-----------------------------------------------------------------------------------------------//
Table::Table() :sql::ConnectInfo(), 
m_lRecno(-1L)
{
   CreateInstance(__uuidof(Recordset));
   m_recordset = GetInterfacePtr();
}
//-----------------------------------------------------------------------------------------------//
Table::Table(sql::ConnectInfo const & sqlconn):ConnectInfo(sqlconn), 
m_lRecno(-1L)
{
   CreateInstance(__uuidof(Recordset));
   m_recordset = GetInterfacePtr();
   SetRecordsetPtrEventsClass();
}
//-----------------------------------------------------------------------------------------------//
Table::Table(_RecordsetPtr const & rptr):ConnectInfo(),
m_lRecno(-1L)
{
   _RecordsetPtr::operator=(rptr);
   m_recordset = GetInterfacePtr();
   SetRecordsetPtrEventsClass();
   /* reload */
   if(!Eof && rptr->State == adStateOpen)
   {
      Gotop();
      GetFieldList();
   }
}
//-----------------------------------------------------------------------------------------------//
Table::Table(_ConnectionPtr const & conptr):ConnectInfo(), 
m_lRecno(-1L)
{
   CreateInstance(__uuidof(Recordset));
   m_recordset = GetInterfacePtr();
   m_recordset->putref_ActiveConnection(conptr);
   SetRecordsetPtrEventsClass();
}
//-----------------------------------------------------------------------------------------------//
Table::~Table()
{
   /* free list */
   clear();
   /* cancel task if still running */
   cancel();
   /* finalize event class */
   FinalizeRecordsetPtrEventsClass();
   /**/
   if (m_recordset->State == adStateOpen)
   {
      m_recordset->Close();
   }
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Table::Open(std::wstring const & strTableName,
                                  CommandTypeEnum cteCommandType,
                                  CursorTypeEnum ctCursorType,
                                  LockTypeEnum ltLockType)
{
   try
   {
      HRESULT hSuccess = S_FALSE;

      if (Actived)
      {
         m_recordset->Close();
      }
      /* call by pplx */
      {
         m_recordset->put_CursorLocation(adUseClient);
         m_recordset->put_StayInSync(true);
         _variant_t vConnectionString_ptr = ConnectionString.c_str();
         _variant_t vTableName_or_sqlcmd = strTableName.c_str();
         /**/
         hSuccess = m_recordset->Open
            (
            vTableName_or_sqlcmd,
            vConnectionString_ptr,
            ctCursorType,
            ltLockType,
            cteCommandType
            );
         /**/
         if (hSuccess != S_OK)
         {
            std::wstring s =  std::wstring
            {
               L"called table::open(" + ConnectionString + L") failed result " +
               std::to_wstring(hSuccess) + L"!"
            };
            throw std::exception { std::string( LPCSTR( s.c_str() ) ).c_str() };
         }
      }
      //check command
      std::wstring szCmd = strTableName.substr( 0, 6 );
      std::transform( szCmd.begin(), szCmd.end(), szCmd.begin(), ::towupper );
      {
         if ( szCmd.compare( L"insert" ) == 0 || szCmd.compare( L"update" ) == 0 || szCmd.compare( L"delete" ) == 0 )
         {
            return true;
         }
         /**/
         GetFieldList();

         if (!Eof)
         {
            Gotop();
            return true;
         }
      }
      return true;
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   catch(std::exception & e)
   {
      throw e;
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Table::GetEof()
{
   try
   {
      return bool(m_recordset->EndOfFile);
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return true;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Table::GetBof()
{
   try
   {
      return bool(m_recordset->BOF);
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return true;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Table::Go(long const lrecno)
{
   try
   {
      HRESULT result = S_FALSE;

      if(!Eof && !Bof)
      {
         if ((result = m_recordset->Move(lrecno)) == S_OK)
         {
            m_lRecno = lrecno;
            return true;
         }
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
long const __fastcall Table::GetReccount()
{
   try
   {
      long lcount;
      HRESULT result = m_recordset->get_RecordCount(&lcount);

      if (result == S_OK && lcount >= 0L)
      {
         return lcount;
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return 0L;
}
//-----------------------------------------------------------------------------------------------//
long const __fastcall Table::GetRecno()
{
   return m_lRecno;
}
//-----------------------------------------------------------------------------------------------//
long const __fastcall Table::GetLastrec()
{
   try
   {
      return GetReccount();
   }
   catch(std::exception & e)
   {
      throw e;
   }
   return 0L;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Table::Gotop()
{
   try
   {
      if (!Bof)
      {
         return bool(m_lRecno = m_recordset->MoveFirst());
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Table::GoBottom()
{
   try
   {
      if (!Eof)
      {
         return bool(m_lRecno = m_recordset->MoveLast());
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Table::Next()
{
   try
   {
      if (!Eof && !Bof)
      {
         return bool(m_lRecno = m_recordset->MoveNext());
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Table::Previous()
{
   try
   {
      if (!Eof && !Bof)
      {
         return bool(m_lRecno = m_recordset->MovePrevious());
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Table::Skip(long lrecno)
{
   return Go(lrecno);
}
//-----------------------------------------------------------------------------------------------//
void const __fastcall Table::Close()
{
   try
   {
      m_recordset->Close();
      clear();
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
}
//-----------------------------------------------------------------------------------------------//
sql::Field * __fastcall Table::operator[](std::wstring const & strName)
{
   sql::Field * f = at(strName);

   if (f == nullptr)
   {
      std::wstring s
      {
         L"Field" + strName + L" not exists!" 
      };
      throw std::exception( std::string( LPCSTR(s.c_str()) ).c_str() );
   }
   return f;
}
//-----------------------------------------------------------------------------------------------//
sql::Field * __fastcall Table::operator[](unsigned int uIndex)
{
   if (int(uIndex) >= size())
   {
      std::wstring sf
      {
         L"Field " + std::to_wstring(uIndex) + std::wstring(L" index out of range!")
      };
      /**/
      throw std::exception(LPCSTR(sf.c_str()));
   }
   /**/
   unsigned int i = 0;
   {
      iterator p = std::find_if( begin(), end(), [&]( std::pair<std::wstring, Field *> c )
      {
         if ( i == uIndex )
            return true;
         else
            i++;
         return false;
      } );
      /**/
      if ( p != end() )
         return p->second;
   }
   return nullptr;
}
//-----------------------------------------------------------------------------------------------//
sql::Field * __fastcall Table::GetFieldByName(std::wstring const & strName) const
{
   return at(strName);
}
//-----------------------------------------------------------------------------------------------//
sql::Field * __fastcall Table::GetFieldByIndex(unsigned int uIndex)
{
   return Table::operator[](uIndex);
}
//-----------------------------------------------------------------------------------------------//
FieldListMapper & __fastcall Table::GetFieldList()
{
   /* call by pplx */
   run_and_wait([this]
   {
      try
      {
         FieldsPtr fps = GetInterfacePtr()->GetFields();
         int offset = int(fps->Count);
         _variant_t vindex;

         vindex.vt = VT_I2;
         clear();
         reserve(offset);
         /**/
         for (int i = 0; i < offset; i++)
         {
            vindex.iVal = i;
            /**/
            FieldPtr fp = fps->GetItem(vindex);
            std::wstring fName = std::wstring(fp->Name);
            {
               FieldListMapper & f = *this;
               {
                  f[fName] = new Field(fp);
               }
            }
         }
      }
      catch (_com_error & e)
      {
         throw std::exception( format_com_error( e ).c_str() );
      }
   });
   return *this;
}
//-----------------------------------------------------------------------------------------------//
bool const __fastcall Table::GetActived()
{
   try
   {
      if (m_recordset->State == adStateOpen)
      {
         return true;
      }
   }
   catch(_com_error & e)
   {
      throw std::exception( format_com_error( e ).c_str() );
   }
   return false;
}
//-----------------------------------------------------------------------------------------------//
void const __fastcall Table::SetRecordsetPtrEventsClass()
{
   /* check client window handle to notified */
   m_hSuccess = _RecordsetPtr::operator->()->QueryInterface(__uuidof(IConnectionPointContainer), 
      reinterpret_cast<void **>(&m_pConnPointC));
   /**/
   if(FAILED(m_hSuccess))
      throw std::exception("called _RecordsetPtr::operator->()->QueryInterface() failed!");
   /**/
   m_hSuccess = m_pConnPointC->FindConnectionPoint(__uuidof(RecordsetEvents), &m_pConnPoint);
   /**/
   if(FAILED(m_hSuccess))
      throw std::exception("called m_pConnPointC->FindConnectionPoint() failed!");
   /**/
   m_pTableEvent = std::shared_ptr<TableEvent>(new TableEvent(this));
   m_hSuccess = m_pTableEvent->QueryInterface(__uuidof(IUnknown), reinterpret_cast<void **>(&m_pUnknown));
   /**/
   m_hSuccess = m_pConnPoint->Advise(m_pUnknown, static_cast<LPDWORD>(&m_dwRecordEvent));
   /**/
   if(FAILED(m_hSuccess))
      throw std::exception("called m_pConnPoint->Advise() failed!");
   /**/
   m_pConnPoint->Release();
}
//-----------------------------------------------------------------------------------------------//
void const __fastcall Table::FinalizeRecordsetPtrEventsClass()
{
   /* event class not started */
   m_hSuccess = _RecordsetPtr::operator->()->QueryInterface(__uuidof(IConnectionPointContainer),
      reinterpret_cast<void **>(&m_pConnPointC));
   /**/
   if(FAILED(m_hSuccess)) 
      throw std::exception("called _RecordsetPtr::operator->()->QueryInterface() failed!");
   /**/
   m_hSuccess = m_pConnPointC->FindConnectionPoint(__uuidof(RecordsetEvents), &m_pConnPoint);
   m_pConnPointC->Release();
   /**/
   if(FAILED(m_hSuccess)) 
      throw std::exception("called m_pConnPointC->FindConnectionPoint() failed!");
   /**/
   m_hSuccess = m_pConnPoint->Unadvise(m_dwRecordEvent);
   m_pConnPoint->Release();
   /**/
   if(FAILED(m_hSuccess)) 
      throw std::exception("called m_pConnPoint->Unadivse() failed!");
}
//-----------------------------------------------------------------------------------------------//
std::string __stdcall Table::format_com_error( _com_error e )
{
   std::string s = std::string
   {
      "Description: " + std::string( e.Description() ) + "\n" +
      "Error      : " + std::to_string( e.Error() ) + "\n" +
      "Message    : " + std::string( LPSTR( e.ErrorMessage() ) ) + "\n" +
      "Source     : " + std::string( e.Source() ) + "\n" +
      "Code       : " + std::to_string( e.WCode() )
   };
   return s;
}
//-----------------------------------------------------------------------------------------------//
