#ifndef BOO_STACK_H
#define BOO_STACK_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_allocator.h>
#include <boo_mem.h>
namespace booldog
{
	namespace allocators
	{
		namespace stack
		{
			template< size_t s >
			class simple : public ::booldog::allocator
			{
				char _data[ s + sizeof( ::booldog::mem::info ) ];
				size_t _avail;
				::booldog::mem::info* _begin;
			public:
				simple( void )
				{
					_avail = s + sizeof( ::booldog::mem::info );
					_begin = (::booldog::mem::info*)_data;
					_begin->_busy = false;
					_begin->_size = s;
				};
			private:
				booinline ::booldog::mem::info* check_alloc( ::booldog::mem::info* begin , size_t size , size_t total )
				{
					if( begin->_size == size )
					{
						_avail -= total;
						begin->_busy = true;
						return begin;
					}
					else if( begin->_size > total )
					{
						_avail -= total;
						begin->_busy = true;
						size_t diff = begin->_size - size;
						begin->_size = size;

						char* ptr = (char*)begin;
						ptr += size + sizeof( ::booldog::mem::info );

						::booldog::mem::info* info = (::booldog::mem::info*)ptr;
						info->_busy = false;
						info->_size = diff - sizeof( ::booldog::mem::info );
						return begin;
					}
					else
						return 0;
				};
			public:
				size_t available( void )
				{
					return _avail;
				};
				void* begin( void )
				{
					return _begin;
				};
				void* end( void )
				{
					return &_data[ s + sizeof( ::booldog::mem::info ) ];
				};
				virtual void* alloc( size_t size , const char* file , int line )
				{
					file = file;
					line = line;
					if( _avail > 0 )
					{
						void* endptr = end();
						::booldog::mem::info* info = _begin;
						for( ; ; )
						{
							info = (::booldog::mem::info*)( ( (char*)info ) + info->_size + sizeof( ::booldog::mem::info ) );
							if( info >= endptr || info->_busy )
								break;
							_begin->_size += info->_size + sizeof( ::booldog::mem::info );
						}

						size_t total = sizeof( ::booldog::mem::info ) + size;
						::booldog::mem::info* begin = check_alloc( _begin , size , total );
						if( begin )
						{
							info = begin;
							for( ; ; )
							{
								info = (::booldog::mem::info*)( ( (char*)info ) + info->_size + sizeof( ::booldog::mem::info ) );
								if( info >= endptr || info->_busy == false )
								{
									_begin = info;
									break;
								}
							}
						}
						else
						{
							info = _begin;
							for( ; ; )
							{
								info = (::booldog::mem::info*)( ( (char*)info ) + info->_size + sizeof( ::booldog::mem::info ) );
								begin = check_alloc( info , size , total );
								if( info >= endptr || begin )
									break;
							}
						}
						if( begin )
							return ( (char*)begin ) + sizeof( ::booldog::mem::info );
					}
					return 0;
				};
				virtual void free( void* pointer )
				{
					char* ptr = (char*)pointer;
					::booldog::mem::info* begin = (::booldog::mem::info*)( ptr - sizeof( ::booldog::mem::info ) );
					if( begin->_busy )
					{
						begin->_busy = false;
						_avail += begin->_size + sizeof( ::booldog::mem::info );
								
						void* endptr = end();
						::booldog::mem::info* info = begin;
						for( ; ; )
						{
							info = (::booldog::mem::info*)( ( (char*)info ) + info->_size + sizeof( ::booldog::mem::info ) );
							if( info >= endptr || info->_busy )
								break;
							begin->_size += info->_size + sizeof( ::booldog::mem::info );
						}
						if( _begin > begin )
							_begin = begin;
					}
				};
				virtual void* realloc( void* pointer , size_t size , const char* file , int line )
				{
					if( size == 0 )
					{
						free( pointer );
						return 0;
					}
					if( pointer == 0 )
						return alloc( size , file , line );

					char* ptr = (char*)pointer;
					::booldog::mem::info* begin = (::booldog::mem::info*)( ptr - sizeof( ::booldog::mem::info ) );
					if( begin->_size == size )
						return pointer;
					else if( begin->_size > size )
					{
						size_t diff = begin->_size - size;
						void* endptr = end();
						::booldog::mem::info* info = (::booldog::mem::info*)( ptr + begin->_size );
						if( info < endptr && info->_busy == false )
						{
							_avail -= info->_size + sizeof( ::booldog::mem::info );
							diff += info->_size + sizeof( ::booldog::mem::info );
						}
						if( diff > sizeof( ::booldog::mem::info ) )
						{
							begin->_size = size;
							info = (::booldog::mem::info*)( ptr + size );
							info->_busy = false;
							info->_size = diff - sizeof( ::booldog::mem::info );
							_avail += info->_size + sizeof( ::booldog::mem::info );
							if( _begin > info )
								_begin = info;
						}
						return pointer;
					}
					else
					{
						void* endptr = end();
						size_t old_size = begin->_size;
						::booldog::mem::info* info = begin;
						::booldog::byte it_was_begin = 0;
						for( ; ; )
						{
							info = (::booldog::mem::info*)( ( (char*)info ) + info->_size + sizeof( ::booldog::mem::info ) );
							if( info >= endptr || info->_busy )
								break;
							begin->_size += info->_size + sizeof( ::booldog::mem::info );
							_avail -= info->_size + sizeof( ::booldog::mem::info );
							if( info == _begin )
								it_was_begin = 1;
							if( begin->_size >= size )
								break;
						}
						if( begin->_size == size )
						{
							if( it_was_begin )
							{
								info = begin;
								for( ; ; )
								{
									info = (::booldog::mem::info*)( ( (char*)info ) + info->_size + sizeof( ::booldog::mem::info ) );
									if( info >= endptr || info->_busy == false )
									{
										_begin = info;
										break;
									}
								}
							}
							return pointer;
						}
						else if( begin->_size > size )
						{							
							size_t diff = begin->_size - size;
							info = (::booldog::mem::info*)( ptr + begin->_size );
							if( info < endptr && info->_busy == false )
							{
								_avail -= info->_size + sizeof( ::booldog::mem::info );
								diff += info->_size + sizeof( ::booldog::mem::info );
							}
							if( diff > sizeof( ::booldog::mem::info ) )
							{
								begin->_size = size;
								info = (::booldog::mem::info*)( ptr + size );
								info->_busy = false;
								info->_size = diff - sizeof( ::booldog::mem::info );
								_avail += info->_size + sizeof( ::booldog::mem::info );
								if( it_was_begin || _begin > info )
									_begin = info;
							}
							else if( it_was_begin )
							{
								info = begin;
								for( ; ; )
								{
									info = (::booldog::mem::info*)( ( (char*)info ) + info->_size + sizeof( ::booldog::mem::info ) );
									if( info >= endptr || info->_busy == false )
									{
										_begin = info;
										break;
									}
								}
							}
							return pointer;
						}
						else
						{
							void* new_pointer = alloc( size , file , line );
							if( new_pointer )
								::memcpy( new_pointer , pointer , old_size );
							free( pointer );
							return new_pointer;
						}
					}
				};
			};
		};
	};
};
#endif
