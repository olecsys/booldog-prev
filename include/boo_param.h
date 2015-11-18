#ifndef BOO_PARAM_H
#define BOO_PARAM_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <boo_types.h>
#include <boo_hash_times33.h>
namespace booldog
{
	namespace enums
	{
		namespace param
		{
			enum type
			{
				type_none = 0 ,
				type_int32 ,
				type_uint32 , 
				type_bool ,
				type_char ,
				type_wchar ,
				type_uchar ,
				type_short ,
				type_ushort ,
				type_int64 ,
				type_uint64 ,
				type_pchar ,
				type_pwchar ,
				type_pvoid , 
				type_pnamed_param ,
				type_pparam , 
				type_pint32 ,
				type_puint32 , 
				type_pbool ,
				type_puchar ,
				type_pshort ,
				type_pushort ,
				type_pint64 ,
				type_puint64 ,
				type_not_found
			};
		};
	};
	struct named_param;
	typedef struct param
	{
		::booldog::enums::param::type type;
		union
		{
			booldog::int32 int32value;
			booldog::uint32 uint32value;
			bool boolvalue;
			char charvalue;
			booldog::byte ucharvalue;
			short shortvalue;
			unsigned short ushortvalue;
			booldog::int64 int64value;
			booldog::uint64 uint64value;
			wchar_t wcharvalue;
			const char* pcharvalue;
			const wchar_t* pwcharvalue;
			void* pvoidvalue;
			booldog::named_param* pnamed_paramvalue;
			booldog::param* pparamvalue;
			booldog::pint32 pint32value;
			booldog::puint32 puint32value;
			booldog::pbool pboolvalue;
			booldog::puchar pucharvalue;
			booldog::pshort pshortvalue;
			booldog::pushort pushortvalue;
			booldog::pint64 pint64value;
			booldog::puint64 puint64value;
		};
		param( void )
		{
			type = ::booldog::enums::param::type_none;
		};
		param( booldog::int32 value )
		{
			type = ::booldog::enums::param::type_int32;
			int32value = value;
		};
		param( booldog::uint32 value )
		{
			type = ::booldog::enums::param::type_uint32;
			uint32value = value;
		};
		param( bool value )
		{
			type = ::booldog::enums::param::type_bool;
			boolvalue = value;
		};
		param( char value )
		{
			type = ::booldog::enums::param::type_char;
			charvalue = value;
		};
		param( booldog::byte value )
		{
			type = ::booldog::enums::param::type_uchar;
			ucharvalue = value;
		};
		param( short value )
		{
			type = ::booldog::enums::param::type_short;
			shortvalue = value;
		};
		param( unsigned short value )
		{
			type = ::booldog::enums::param::type_ushort;
			ushortvalue = value;
		};
		param( booldog::int64 value )
		{
			type = ::booldog::enums::param::type_int64;
			int64value = value;
		};
		param( booldog::uint64 value )
		{
			type = ::booldog::enums::param::type_uint64;
			uint64value = value;
		};
		param( wchar_t value )
		{
			type = ::booldog::enums::param::type_wchar;
			wcharvalue = value;
		};
		param( const char* value )
		{
			type = ::booldog::enums::param::type_pchar;
			pcharvalue = value;
		};
		param( const wchar_t* value )
		{
			type = ::booldog::enums::param::type_pwchar;
			pwcharvalue = value;
		};
		param( void* value )
		{
			type = ::booldog::enums::param::type_pvoid;
			pvoidvalue = value;
		};
		param( booldog::named_param* value )
		{
			type = ::booldog::enums::param::type_pnamed_param;
			pnamed_paramvalue = value;
		};
		param( booldog::param* value )
		{
			type = ::booldog::enums::param::type_pparam;
			pparamvalue = value;
		};
		param( booldog::pint32 value )
		{
			type = ::booldog::enums::param::type_pint32;
			pint32value = value;
		};
		param( booldog::puint32 value )
		{
			type = ::booldog::enums::param::type_puint32;
			puint32value = value;
		};
		param( booldog::pbool value )
		{
			type = ::booldog::enums::param::type_pbool;
			pboolvalue = value;
		};
		param( booldog::puchar value )
		{
			type = ::booldog::enums::param::type_puchar;
			pucharvalue = value;
		};
		param( booldog::pshort value )
		{
			type = ::booldog::enums::param::type_pshort;
			pshortvalue = value;
		};
		param( booldog::pushort value )
		{
			type = ::booldog::enums::param::type_pushort;
			pushortvalue = value;
		};
		param( booldog::pint64 value )
		{
			type = ::booldog::enums::param::type_pint64;
			pint64value = value;
		};
		param( booldog::puint64 value )
		{
			type = ::booldog::enums::param::type_puint64;
			puint64value = value;
		};
	} param;

	typedef struct named_param
	{
		const char* name;
		booldog::param param;
		::booldog::uint64 hash;
		named_param( const char* pname = 0 , ::booldog::enums::param::type ptype = ::booldog::enums::param::type_none )
			: param()
		{
			memset( &param , 0 , sizeof( param ) );
			param.type = ptype;
			name = pname;
			hash = 0;
		};
		named_param( const char* name , booldog::int32 value )		
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , booldog::uint32 value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , bool value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , char value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , booldog::byte value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , short value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , unsigned short value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , booldog::int64 value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , booldog::uint64 value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , wchar_t value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , const char* value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , const wchar_t* value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , void* value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , booldog::named_param* value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , booldog::param* value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , booldog::pint32 value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , booldog::puint32 value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , booldog::pbool value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , booldog::puchar value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , booldog::pshort value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , booldog::pushort value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , booldog::pint64 value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		named_param( const char* name , booldog::puint64 value )
			: param( value )
		{
			this->name = name;
			hash = 0;
		};
		::booldog::uint64 name_hash( void )
		{
			if( name )
			{
				if( hash == 0 )
					hash = ::booldog::hash::times33::calculate( name , SIZE_MAX );
				return hash;
			}
			else
				return 0;
		};
	} named_param;
	namespace utils
	{
		namespace param
		{
			booinline void search( ::booldog::named_param* src , ::booldog::named_param* dst )
			{
				if( src && dst )
				{
					for( ::booldog::named_param* pdst = (::booldog::named_param*)dst ; pdst && pdst->param.type != ::booldog::enums::param::type_none 
						; ++pdst )
					{
						for( ::booldog::named_param* psrc = (::booldog::named_param*)src ; psrc && psrc->param.type != ::booldog::enums::param::type_none 
							; ++psrc )
						{
							if( pdst->param.type == psrc->param.type && pdst->name_hash() == psrc->name_hash() )
							{
								::memcpy( &pdst->param , &psrc->param , sizeof( psrc->param ) );
								goto goto_found;
							}
						}
						pdst->param.type = ::booldog::enums::param::type_not_found;
		goto_found:
						;
					}
				}
			};
		};
	};
};
#define BOOPARAM_INT32( val ) ::booldog::param( (booldog::int32)val )
#define BOOPARAM_BOOL( val ) ::booldog::param( (bool)val )
#define BOOPARAM_CHAR( val ) ::booldog::param( (char)val )
#define BOOPARAM_UCHAR( val ) ::booldog::param( (unsigned char)val )
#define BOOPARAM_SHORT( val ) ::booldog::param( (short)val )
#define BOOPARAM_USHORT( val ) ::booldog::param( (unsigned short)val )
#define BOOPARAM_INT64( val ) ::booldog::param( (booldog::int64)val )
#define BOOPARAM_UINT64( val ) ::booldog::param( (booldog::uint64)val )
#define BOOPARAM_WCHAR( val ) ::booldog::param( (wchar_t)val )
#define BOOPARAM_PCHAR( val ) ::booldog::param( (char*)val )
#define BOOPARAM_PWCHAR( val ) ::booldog::param( (wchar_t*)val )
#define BOOPARAM_PVOID( val ) ::booldog::param( (void*)val )
#define BOOPARAM_PNAMED_PARAM( val ) ::booldog::param( (booldog::named_param*)val )
#define BOOPARAM_PPARAM( val ) ::booldog::param( (booldog::param*)val )
#define BOOPARAM_PINT32( val ) ::booldog::param( (booldog::pint32)val )
#define BOOPARAM_PUINT32( val ) ::booldog::param( (booldog::puint32)val )
#define BOOPARAM_PBOOL( val ) ::booldog::param( (booldog::pbool)val )
#define BOOPARAM_PUCHAR( val ) ::booldog::param( (booldog::puchar)val )
#define BOOPARAM_PSHORT( val ) ::booldog::param( (booldog::pshort)val )
#define BOOPARAM_PUSHORT( val ) ::booldog::param( (booldog::pushort)val )
#define BOOPARAM_PINT64( val ) ::booldog::param( (booldog::pint64)val )
#define BOOPARAM_PUINT64( val ) ::booldog::param( (booldog::puint64)val )

#define BOONAMED_PARAM_INT32( name , val ) ::booldog::named_param( name , (::booldog::int32)val )
#define BOONAMED_PARAM_BOOL( name , val ) ::booldog::named_param( name , (bool)val )
#define BOONAMED_PARAM_CHAR( name , val ) ::booldog::named_param( name , (char)val )
#define BOONAMED_PARAM_UCHAR( name , val ) ::booldog::named_param( name , (unsigned char)val )
#define BOONAMED_PARAM_SHORT( name , val ) ::booldog::named_param( name , (short)val )
#define BOONAMED_PARAM_USHORT( name , val ) ::booldog::named_param( name , (unsigned short)val )
#define BOONAMED_PARAM_INT64( name , val ) ::booldog::named_param( name , (::booldog::int64)val )
#define BOONAMED_PARAM_UINT64( name , val ) ::booldog::named_param( name , (::booldog::uint64)val )
#define BOONAMED_PARAM_WCHAR( name , val ) ::booldog::named_param( name , (wchar_t)val )
#define BOONAMED_PARAM_PCHAR( name , val ) ::booldog::named_param( name , (char*)val )
#define BOONAMED_PARAM_PWCHAR( name , val ) ::booldog::named_param( name , (wchar_t*)val )
#define BOONAMED_PARAM_PVOID( name , val ) ::booldog::named_param( name , (void*)val )
#define BOONAMED_PARAM_PNAMED_PARAM( name , val ) ::booldog::named_param( name , (::booldog::named_param*)val )
#define BOONAMED_PARAM_PPARAM( name , val ) ::booldog::named_param( name , (::booldog::param*)val )
#define BOONAMED_PARAM_PINT32( name , val ) ::booldog::named_param( name , (booldog::pint32)val )
#define BOONAMED_PARAM_PUINT32( name , val ) ::booldog::named_param( name , (booldog::puint32)val )
#define BOONAMED_PARAM_PBOOL( name , val ) ::booldog::named_param( name , (booldog::pbool)val )
#define BOONAMED_PARAM_PUCHAR( name , val ) ::booldog::named_param( name , (booldog::puchar)val )
#define BOONAMED_PARAM_PSHORT( name , val ) ::booldog::named_param( name , (booldog::pshort)val )
#define BOONAMED_PARAM_PUSHORT( name , val ) ::booldog::named_param( name , (booldog::pushort)val )
#define BOONAMED_PARAM_PINT64( name , val ) ::booldog::named_param( name , (booldog::pint64)val )
#define BOONAMED_PARAM_PUINT64( name , val ) ::booldog::named_param( name , (booldog::puint64)val )

#define BOO_SEARCH_NAMED_PARAM_INT32( name ) ::booldog::named_param( name , ::booldog::enums::param::type_int32 )
#define BOO_SEARCH_NAMED_PARAM_BOOL( name ) ::booldog::named_param( name , ::booldog::enums::param::type_bool )
#define BOO_SEARCH_NAMED_PARAM_CHAR( name ) ::booldog::named_param( name , ::booldog::enums::param::type_char )
#define BOO_SEARCH_NAMED_PARAM_UCHAR( name ) ::booldog::named_param( name , ::booldog::enums::param::type_uchar )
#define BOO_SEARCH_NAMED_PARAM_SHORT( name ) ::booldog::named_param( name , ::booldog::enums::param::type_short )
#define BOO_SEARCH_NAMED_PARAM_USHORT( name ) ::booldog::named_param( name , ::booldog::enums::param::type_ushort )
#define BOO_SEARCH_NAMED_PARAM_INT64( name ) ::booldog::named_param( name , ::booldog::enums::param::type_int64 )
#define BOO_SEARCH_NAMED_PARAM_UINT64( name ) ::booldog::named_param( name , ::booldog::enums::param::type_uint64 )
#define BOO_SEARCH_NAMED_PARAM_WCHAR( name ) ::booldog::named_param( name , ::booldog::enums::param::type_wchar )
#define BOO_SEARCH_NAMED_PARAM_PCHAR( name ) ::booldog::named_param( name , ::booldog::enums::param::type_pchar )
#define BOO_SEARCH_NAMED_PARAM_PWCHAR( name ) ::booldog::named_param( name , ::booldog::enums::param::type_pwchar )
#define BOO_SEARCH_NAMED_PARAM_PVOID( name ) ::booldog::named_param( name , ::booldog::enums::param::type_pvoid )
#define BOO_SEARCH_NAMED_PARAM_PNAMED_PARAM( name ) ::booldog::named_param( name , ::booldog::enums::param::type_pnamed_param )
#define BOO_SEARCH_NAMED_PARAM_PPARAM( name ) ::booldog::named_param( name , ::booldog::enums::param::type_pparam )
#define BOO_SEARCH_NAMED_PARAM_PINT32( name ) ::booldog::named_param( name , ::booldog::enums::param::type_pint32 )
#define BOO_SEARCH_NAMED_PARAM_PUINT32( name ) ::booldog::named_param( name , ::booldog::enums::param::type_puint32 )
#define BOO_SEARCH_NAMED_PARAM_PBOOL( name ) ::booldog::named_param( name , ::booldog::enums::param::type_pbool )
#define BOO_SEARCH_NAMED_PARAM_PUCHAR( name ) ::booldog::named_param( name , ::booldog::enums::param::type_puchar )
#define BOO_SEARCH_NAMED_PARAM_PSHORT( name ) ::booldog::named_param( name , ::booldog::enums::param::type_pshort )
#define BOO_SEARCH_NAMED_PARAM_PUSHORT( name ) ::booldog::named_param( name , ::booldog::enums::param::type_pushort )
#define BOO_SEARCH_NAMED_PARAM_PINT64( name ) ::booldog::named_param( name , ::booldog::enums::param::type_pint64 )
#define BOO_SEARCH_NAMED_PARAM_PUINT64( name ) ::booldog::named_param( name , ::booldog::enums::param::type_puint64 )

#define BOONAMED_PARAM_NONE ::booldog::named_param()
#define BOOPARAM_NONE ::booldog::param()
#define BOO_SEARCH_NAMED_PARAM_NONE BOONAMED_PARAM_NONE
#endif