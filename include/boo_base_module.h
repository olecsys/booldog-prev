#ifndef BOO_BASE_MODULE_H
#define BOO_BASE_MODULE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_string.h>
namespace booldog
{
	namespace base
	{
		class module
		{
		public:
			virtual const ::booldog::string name( void )
			{
				::booldog::string s;
				return s;
			};
			virtual const ::booldog::string path( void )
			{
				::booldog::string s;
				return s;
			};
			virtual bool loaded( void )
			{
				return false;
			};
			virtual void* method( const char* name )
			{
				name = name;
				return 0;
			};
			virtual ::booldog::module_handle handle( void )
			{
				return 0;
			};
		};
	};
	class module
	{
	private:
		::booldog::module_handle _handle;
	public:
		module( void )
		{
			_handle = 0;
		};
		virtual const ::booldog::string name( void )
		{
			::booldog::string s;
			return s;
		};
		virtual const ::booldog::string path( void )
		{
			::booldog::string s;
			return s;
		};
		virtual bool loaded( void )
		{
			return _handle != 0;
		};
		virtual void* method( const char* name )
		{
			name = name;
			return 0;
		};
		virtual ::booldog::module_handle handle( void )
		{
			return _handle;
		};
	};
};
#endif