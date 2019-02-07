#ifndef BOO_RESULT_H
#define BOO_RESULT_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_allocator.h"
#include "boo_types.h"
#ifdef __UNIX__
#include <string.h>
#endif
#include <errno.h>
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
#include <stdint.h>
#ifndef SIZE_MAX
#ifdef __SIZE_MAX__
#define SIZE_MAX __SIZE_MAX__
#else
#define SIZE_MAX ((size_t) - 1)
#endif
#endif
namespace booldog
{
	namespace enums
	{
		namespace result
		{
			typedef enum
			{
				error_type_no_error ,
				error_type_errno ,
#ifdef __WINDOWS__
				error_type_GetLastError , 
				error_type_HRESULT_error ,
#else
				error_type_dlerror ,
				error_type_pthread ,
#endif
				error_type_booerr , 
				error_type_OpenGL, 
				error_type_alsa
			} error_type;
			};
		};
	class result
	{
	private:
// copy and assignment not allowed
		result(const ::booldog::result&);
		::booldog::result& operator = (const ::booldog::result&);
	public:
		::booldog::enums::result::error_type error_type;
		union
		{
			int errno_err;
#ifdef __WINDOWS__
			::booldog::uint32 get_last_error;
			HRESULT hr;
#else
			struct
			{
				::booldog::allocator* _allocator;
				char* _dlerror;
			};
			int pthreaderror;
			int alsaerror;
#endif	
			::booldog::uint32 booerror;
			unsigned int openglerror;
		};
		result()
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
		void glGetError( unsigned int glerror )
		{
			clear();
			this->error_type = ::booldog::enums::result::error_type_OpenGL;
			this->openglerror = glerror;
		};
#ifdef __WINDOWS__
		void setHRESULT( HRESULT hresult )
		{
			clear();
			this->error_type = ::booldog::enums::result::error_type_HRESULT_error;
			this->hr = hresult;
		};
		void GetLastError( void )
		{
			clear();
			this->error_type = ::booldog::enums::result::error_type_GetLastError;
			this->get_last_error = ::GetLastError();
		};
		void GetLastError( ::booldog::uint32 _get_last_error )
		{
			clear();
			this->error_type = ::booldog::enums::result::error_type_GetLastError;
			this->get_last_error = _get_last_error;
		};
#else
		void setalsaerror(int alsaerror)
		{
			clear();
			this->error_type = ::booldog::enums::result::error_type_alsa;
			this->alsaerror = alsaerror;
		};
		void setpthreaderror( int pthreaderror )
		{
			clear();
			this->error_type = ::booldog::enums::result::error_type_pthread;
			this->pthreaderror = pthreaderror;
		};
		char* dlerror( void )
		{
			if( this->error_type == ::booldog::enums::result::error_type_dlerror )
				return _dlerror;
			return 0;
		};
		void setdlerror( booldog::allocator* allocator , const char* dlerrorstr
			, const ::booldog::debug::info& debuginfo = debuginfo_macros )
		{
			clear();
			const char* ptr = "unknown dl error";
			if( dlerrorstr )
				ptr = dlerrorstr;
			const char* begin = ptr;
			for( ; ; )
			{
				switch( *ptr++ )
				{
				case 0:
					goto goto_next;
				}
			}
goto_next:
			size_t srccharcount = ptr - begin;
			this->_dlerror = allocator->realloc_array< char >( 0 , srccharcount , debuginfo );
			if( this->_dlerror )
			{
				srccharcount--;
				::memcpy( this->_dlerror , begin , srccharcount );
				this->_dlerror[ srccharcount ] = 0;
				this->_allocator = allocator;
			}
			this->error_type = ::booldog::enums::result::error_type_dlerror;
		};
		void dlerrorclear( void )
		{
			if( this->error_type == ::booldog::enums::result::error_type_dlerror )
			{
				if( this->_dlerror )
					this->_allocator->free( this->_dlerror );
			}
		};
#endif
		void booerr( ::booldog::uint32 _booerror )
		{
			clear();
			this->error_type = ::booldog::enums::result::error_type_booerr;
			this->booerror = _booerror;
		}
		/* Copy obj to this
		* @param obj a source object
		*/
		void copy(const ::booldog::result& obj)
		{
			clear();
			::booldog::result* _obj_ = const_cast< ::booldog::result* >( &obj );
			size_t size = sizeof( ::booldog::result );
			void* zero = (void*)&this->error_type;
			size -= (char*)zero - (char*)this;
			::memcpy( zero , &_obj_->error_type , size );
#ifdef __UNIX__
			if( _obj_->error_type == ::booldog::enums::result::error_type_dlerror )
				_obj_->_dlerror = 0;
#endif
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
		result_wchar(const ::booldog::result_wchar&);
		result_wchar(const ::booldog::result&);
		::booldog::result_wchar& operator = (const ::booldog::result_wchar&);
	public:
		wchar_t* wchar;
		size_t wsize;
		size_t wlen;
		booldog::allocator* wallocator;
		result_wchar( booldog::allocator* allocator )
                        : result(), wchar(0), wsize(0), wlen(0), wallocator(allocator)
		{
                }
		virtual ~result_wchar( void )
		{
			if( wchar )
				wallocator->free( wchar );
                }
		wchar_t* detach( void )
		{
			wchar_t* res = wchar;
			wchar = 0;
			wsize = 0;
			wlen = 0;
			return res;
                }
		virtual void clear( void ) const
		{
			::booldog::result_wchar* _obj_ = const_cast< ::booldog::result_wchar* >( this );
#ifdef __UNIX__
			_obj_->dlerrorclear();
#endif
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
			if( _obj_->wchar )
				_obj_->wchar[ 0 ] = 0;
			_obj_->wlen = 0;
		}
		booinline operator ::booldog::allocator*() const
		{
			return wallocator;
		}
	};
	class result_mbchar : public ::booldog::result
	{
	private:
// copy and assignment not allowed
		result_mbchar(const ::booldog::result_mbchar&);
		result_mbchar(const ::booldog::result&);
		::booldog::result_mbchar& operator = (const ::booldog::result_mbchar&);
	public:
		union
		{
			char* mbchar;
			const char* cmbchar;
		};
		size_t mblen;
		size_t mbsize;
		booldog::allocator* mballocator;
		result_mbchar( booldog::allocator* allocator )
                        : result(), mbchar(0), mblen(0), mbsize(0), mballocator(allocator)
		{
                }
		virtual ~result_mbchar()
		{
			if(mbchar)
				mballocator->free( mbchar );
		}
		char* detach() const
		{
			char* res = mbchar;
			::booldog::result_mbchar* _this = const_cast< ::booldog::result_mbchar* >(this);
			_this->mbchar = 0;
			_this->mbsize = 0;
			_this->mblen = 0;
			return res;
		}
		virtual void clear() const
		{
			::booldog::result_mbchar* _obj_ = const_cast< ::booldog::result_mbchar* >( this );
#ifdef __UNIX__
			_obj_->dlerrorclear();
#endif
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
			if( _obj_->mbchar )
				_obj_->mbchar[ 0 ] = 0;
			_obj_->mblen = 0;
		}
		booinline operator ::booldog::allocator*() const
		{
			return mballocator;
		}
		booinline operator const char*() const
		{
			return mbchar;
		}
	};
	class result_buffer : public ::booldog::result
	{
	private:
// copy and assignment not allowed
		result_buffer(const ::booldog::result_buffer&);
		result_buffer(const ::booldog::result&);
		::booldog::result_buffer& operator = ( const ::booldog::result_buffer& );
	public:
		unsigned char* buf;
		size_t bufdatasize;
		size_t bufsize;
		booldog::allocator* allocator;
		result_buffer(booldog::allocator* pallocator)
			: result(), buf(0), bufdatasize(0), bufsize(0), allocator(pallocator)
		{
		}
		virtual ~result_buffer()
		{
			if( buf )
				allocator->free( buf );
		}
		unsigned char* detach()
		{
			unsigned char* res = buf;
			buf = 0;
			bufsize = 0;
			bufdatasize = 0;
			return res;
		};
		virtual void clear( void ) const
		{
			::booldog::result_buffer* _obj_ = const_cast< ::booldog::result_buffer* >( this );
#ifdef __UNIX__
			_obj_->dlerrorclear();
#endif
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
			_obj_->bufdatasize = 0;
		}
		bool copyfrom(const result_buffer& resbuf)
		{
			if(resbuf.bufdatasize)
			{
				if(bufsize < resbuf.bufdatasize)
				{
					bufsize = resbuf.bufdatasize;
					buf = allocator->realloc_array<unsigned char>(buf, bufsize);
					if(buf == 0)
						return false;
				}
				bufdatasize = resbuf.bufdatasize;
				::memcpy(buf, resbuf.buf, resbuf.bufdatasize);
				return true;
			}
			return false;
		}
		template< size_t step >
		booinline bool append(unsigned char* buffer, size_t buffer_size, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			if(buffer && buffer_size)
			{
				size_t offset = bufdatasize;
				bufdatasize += buffer_size;
				if(bufsize < bufdatasize)
				{
					bufsize = bufdatasize + step;
					buf = allocator->realloc_array< unsigned char >(buf, bufsize, debuginfo);
					if(buf == 0)
						return false;
				}
				::memcpy(&buf[offset], buffer, buffer_size);
				return true;
			}
			return false;
		}
		booinline operator ::booldog::allocator*() const
		{
			return allocator;
		}
		booinline bool append(unsigned char* buffer, size_t buffer_size, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			return append< 16 >(buffer, buffer_size, debuginfo);
		}
		/** Append buffer data to buf field
		* @param buffer an appended buffer
		* @return this
		*/
		::booldog::result_buffer& operator +=(const ::booldog::data::buffer& buffer)
		{
			append< 16 >((unsigned char*)buffer.buf, buffer.size, debuginfo_macros);
			return *this;
		}
	};
	class result_bool : public ::booldog::result
	{
	private:
// copy and assignment not allowed
		result_bool(const ::booldog::result_bool&);
		result_bool(const ::booldog::result&);
		::booldog::result_bool& operator = (const ::booldog::result_bool&);
	public:
		bool bres;
		result_bool()
 			: result()
		{
		}
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
	class result_pointer : public ::booldog::result
	{
	private:
// copy and assignment not allowed
		result_pointer(const ::booldog::result_pointer&);
		result_pointer(const ::booldog::result&);
		::booldog::result_pointer& operator = (const ::booldog::result_pointer&);
	public:
		void* pres;
		result_pointer()
 			: result()
		{
			pres = 0;
		};
		virtual ~result_pointer()
		{
		};
		virtual void clear() const
		{
			::booldog::result_pointer* _obj_ = const_cast< ::booldog::result_pointer* >( this );
#ifdef __UNIX__
			_obj_->dlerrorclear();
#endif
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
			_obj_->pres = 0;
		};
	};
	class result_size : public ::booldog::result
	{
	private:
// copy and assignment not allowed
		result_size(const ::booldog::result_size&);
		result_size(const ::booldog::result&);
		::booldog::result_size& operator = (const ::booldog::result_size&);
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
	class result_int64 : public ::booldog::result
	{
	private:
// copy and assignment not allowed
		result_int64(const ::booldog::result_int64&);
		result_int64(const ::booldog::result&);
		::booldog::result_int64& operator = (const ::booldog::result_int64&);
	public:
		::booldog::int64 int64res;
		result_int64( void )
 			: result()
		{
		};
		virtual ~result_int64( void )
		{
		};
		virtual void clear( void ) const
		{
			::booldog::result_int64* _obj_ = const_cast< ::booldog::result_int64* >( this );
#ifdef __UNIX__
			_obj_->dlerrorclear();
#endif
			_obj_->error_type = ::booldog::enums::result::error_type_no_error;
			_obj_->int64res = INT64_MAX;
		};
	};
	namespace results
	{
		typedef ::booldog::result_bool boolean;
		typedef ::booldog::result_mbchar mbchar;
		typedef ::booldog::result_int64 int64;
		typedef ::booldog::result_wchar wchar;
		typedef ::booldog::result_buffer buffer;
		typedef ::booldog::result_size size;
		typedef ::booldog::result_pointer pointer;
	}
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
