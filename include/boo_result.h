#ifndef BOO_RESULT_H
#define BOO_RESULT_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_allocator.h>
#include <errno.h>
namespace booldog
{
	namespace enums
	{
		namespace result
		{
			enum error_type
			{
				error_type_no_error ,
				error_type_errno ,
#ifdef __WINDOWS__
				error_type_GetLastError , 
#else
				error_type_dlerror ,
#endif
				error_type_booerr
			};
		};
	};
	class result
	{
	private:
// copy and assignment not allowed
		result( const ::booldog::result& )
		{
		};
		::booldog::result& operator = ( const ::booldog::result& )
		{
			return *this;
		};
	public:
		::booldog::enums::result::error_type error_type;
		union
		{
			int errno_err;
#ifdef __WINDOWS__
			::booldog::uint32 get_last_error;
#else
			struct
			{
				::booldog::allocator* _allocator;
				char* _dlerror;
			};
#endif	
			::booldog::uint32 booerror;
		};
		result( void )
		{
			error_type = ::booldog::enums::result::error_type_no_error;
		};
		virtual ~result( void )
		{
#ifdef __UNIX__
			dlerrorclear();
#endif
		};
		virtual ::booldog::enums::result::error_type get_error_type( void )
		{
			return error_type;
		};
		virtual bool succeeded( void )
		{
			return error_type == ::booldog::enums::result::error_type_no_error;
		};
		void seterrno( void )
		{
			clear();
			this->error_type = ::booldog::enums::result::error_type_errno;
			this->errno_err = errno;
		};
		void seterrno( int error )
		{
			clear();
			this->error_type = ::booldog::enums::result::error_type_errno;
			this->errno_err = error;
		};
#ifdef __WINDOWS__
		void GetLastError( void )
		{
			clear();
			this->error_type = ::booldog::enums::result::error_type_GetLastError;
			this->get_last_error = ::GetLastError();
		};
		void GetLastError( ::booldog::uint32 get_last_error )
		{
			clear();
			this->error_type = ::booldog::enums::result::error_type_GetLastError;
			this->get_last_error = get_last_error;
		};
#else
		char* dlerror( void )
		{
			return _dlerror;
		};
		void setdlerror( const char* dlerrorstr , booldog::allocator* allocator = ::booldog::_allocator 
			, ::booldog::debug::info* debuginfo = 0 )
		{
			clear();			
			size_t dstlen = 0 , dstsize_in_bytes = 0;
			if( ::booldog::utils::string::mbs::insert( 0 , 0 , this->_dlerror , dstlen , dstsize_in_bytes , dlerrorstr , 0 , SIZE_MAX 
				, allocator , debuginfo ) )
				this->_allocator = allocator;
			else
				this->_dlerror = 0;
			this->error_type = ::booldog::enums::result::error_type_dlerror;
		};
		void dlerrorclear( void )
		{
			if( this->error_type == ::booldog::enums::result::error_type_dlerror )
			{
				if( this->_dlerror )
					this->_allocator->free( this->_dlerror );
				this->_dlerror = 0;
			}
		};
#endif
		void booerr( ::booldog::uint32 booerror )
		{
			clear();
			this->error_type = ::booldog::enums::result::error_type_booerr;
			this->booerror = booerror;
		};
		void copy( const ::booldog::result& obj )
		{
			clear();
			::booldog::result* _obj_ = const_cast< ::booldog::result* >( &obj );
			size_t size = sizeof( ::booldog::result );
			void* zero = (void*)&this->error_type;
			size -= (char*)zero - (char*)this;
			::memcpy( zero , &_obj_->error_type , size );
		};
		virtual void clear( void ) const
		{
			::booldog::result* _obj_ = const_cast< ::booldog::result* >( this );
#ifdef __UNIX__
			_obj_->dlerrorclear();
#endif
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
		};
	};
	class result_wchar : public ::booldog::result
	{
	private:
// copy and assignment not allowed
		result_wchar( const ::booldog::result_wchar& )
		{
		};
		result_wchar( const ::booldog::result& )
		{
		};
		::booldog::result_wchar& operator = ( const ::booldog::result_wchar& )
		{
			return *this;
		};
	public:
		wchar_t* wchar;
		size_t wsize;
		size_t wlen;
		booldog::allocator* wallocator;
		result_wchar( booldog::allocator* allocator )
 			: wchar( 0 ) , wlen( 0 ) , wsize( 0 ) , wallocator( allocator ) , result()
		{
		};
		virtual ~result_wchar( void )
		{
			if( wchar )
				wallocator->free( wchar );
		};
		wchar_t* detach( void )
		{
			wchar_t* res = wchar;
			wchar = 0;
			wsize = 0;
			wlen = 0;
			return res;
		};
		virtual void clear( void ) const
		{
			::booldog::result_wchar* _obj_ = const_cast< ::booldog::result_wchar* >( this );
#ifdef __UNIX__
			_obj_->dlerrorclear();
#endif
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
			if( _obj_->wchar )
				wallocator->free( _obj_->wchar );
			_obj_->wchar = 0;
			_obj_->wsize = 0;
			_obj_->wlen = 0;
		};
	};
	class result_mbchar : public ::booldog::result
	{
	private:
// copy and assignment not allowed
		result_mbchar( const ::booldog::result_mbchar& )
		{
		};
		result_mbchar( const ::booldog::result& )
		{
		};
		::booldog::result_mbchar& operator = ( const ::booldog::result_mbchar& )
		{
			return *this;
		};
	public:
		char* mbchar;
		size_t mblen;
		size_t mbsize;
		booldog::allocator* mballocator;
		result_mbchar( booldog::allocator* allocator )
 			: mbchar( 0 ) , mblen( 0 ) , mbsize( 0 ) , mballocator( allocator ) , result()
		{
		};
		virtual ~result_mbchar( void )
		{
			if( mbchar )
				mballocator->free( mbchar );
		};
		char* detach( void )
		{
			char* res = mbchar;
			mbchar = 0;
			mbsize = 0;
			mblen = 0;
			return res;
		};
		virtual void clear( void ) const
		{
			::booldog::result_mbchar* _obj_ = const_cast< ::booldog::result_mbchar* >( this );
#ifdef __UNIX__
			_obj_->dlerrorclear();
#endif
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
			if( _obj_->mbchar )
				_obj_->mballocator->free( _obj_->mbchar );
			_obj_->mbchar = 0;
			_obj_->mbsize = 0;
			_obj_->mblen = 0;
		};
	};
	class result_bool : public ::booldog::result
	{
	private:
// copy and assignment not allowed
		result_bool( const ::booldog::result_bool& )
		{
		};
		result_bool( const ::booldog::result& )
		{
		};
		::booldog::result_bool& operator = ( const ::booldog::result_bool& )
		{
			return *this;
		};
	public:
		bool bres;
		result_bool( void )
 			: result()
		{
		};
		virtual ~result_bool( void )
		{
		};
		virtual void clear( void ) const
		{
			::booldog::result_bool* _obj_ = const_cast< ::booldog::result_bool* >( this );
#ifdef __UNIX__
			_obj_->dlerrorclear();
#endif
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
			_obj_->bres = false;
		};
	};
	class result_size : public ::booldog::result
	{
	private:
// copy and assignment not allowed
		result_size( const ::booldog::result_size& )
		{
		};
		result_size( const ::booldog::result& )
		{
		};
		::booldog::result_size& operator = ( const ::booldog::result_size& )
		{
			return *this;
		};
	public:
		size_t sres;
		result_size( void )
 			: result()
		{
		};
		virtual ~result_size( void )
		{
		};
		virtual void clear( void ) const
		{
			::booldog::result_size* _obj_ = const_cast< ::booldog::result_size* >( this );
#ifdef __UNIX__
			_obj_->dlerrorclear();
#endif
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
			_obj_->sres = SIZE_MAX;
		};
	};
#define BOOINIT_RESULT( booclass ) booclass* res = 0;\
	if( pres )\
	{\
		res = pres;\
		res->clear();\
	}\
	else\
		res = &locres
};
#endif