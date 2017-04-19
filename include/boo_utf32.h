#ifndef BOO_UTF32_H
#define BOO_UTF32_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_utf32_consts.h"
#include "boo_string_enums.h"
#include "boo_utils.h"
#include "boo_result.h"
#include "boo_error.h"
namespace booldog
{
	namespace utf32
	{
		booinline bool isdigit( ::booldog::uint32 utfchar )
		{
			return ( utfchar > 0x2f && utfchar < 0x3a )
				|| ( utfchar > 0xb1 && utfchar < 0xb4 )
				|| ( utfchar > 0x065f && utfchar < 0x066a )
				|| ( utfchar > 0x06ef && utfchar < 0x06fa )
				|| ( utfchar > 0x07bf && utfchar < 0x07ca )
				|| ( utfchar > 0x0965 && utfchar < 0x0970 )
				|| ( utfchar > 0x09e5 && utfchar < 0x09f0 )
				|| ( utfchar > 0x0a65 && utfchar < 0x0a70 )
				|| ( utfchar > 0x0ae5 && utfchar < 0x0af0 )
				|| ( utfchar > 0x0b65 && utfchar < 0x0b70 )
				|| ( utfchar > 0x0be5 && utfchar < 0x0bf0 )
				|| ( utfchar > 0x0c65 && utfchar < 0x0c70 )
				|| ( utfchar > 0x0ce5 && utfchar < 0x0cf0 )
				|| ( utfchar > 0x0d65 && utfchar < 0x0d70 )
				|| ( utfchar > 0x0e4f && utfchar < 0x0e5a )
				|| ( utfchar > 0x0ecf && utfchar < 0x0eda )
				|| ( utfchar > 0x0f1f && utfchar < 0x0f2a )
				|| ( utfchar > 0x103f && utfchar < 0x104a )
				|| ( utfchar > 0x108f && utfchar < 0x109a )
				|| ( utfchar > 0x17df && utfchar < 0x17ea )
				|| ( utfchar > 0x180f && utfchar < 0x181a )
				|| ( utfchar > 0x1945 && utfchar < 0x1950 )
				|| ( utfchar > 0x19cf && utfchar < 0x19da )
				|| ( utfchar > 0x1b4f && utfchar < 0x1b5a )
				|| ( utfchar > 0x1baf && utfchar < 0x1bba )
				|| ( utfchar > 0x1c3f && utfchar < 0x1c4a )
				|| ( utfchar > 0x1c4f && utfchar < 0x1c5a )
				|| ( utfchar > 0xa61f && utfchar < 0xa62a )
				|| ( utfchar > 0xa8cf && utfchar < 0xa8da )
				|| ( utfchar > 0xa8ff && utfchar < 0xa90a )
				|| ( utfchar > 0xaa4f && utfchar < 0xaa5a )
				|| ( utfchar > 0xff0f && utfchar < 0xff1a )
				|| utfchar == 0xb9;
		};
		booinline bool isalpha( ::booldog::uint32 utfchar )
		{
			return ( utfchar > 0x40 && utfchar < 0x5b )
				|| ( utfchar > 0x60 && utfchar < 0x7b )
				|| ( utfchar > 0xbf && utfchar < 0xd7 )
				|| ( utfchar > 0xd7 && utfchar < 0xf7 )
				|| ( utfchar > 0xf7 && utfchar < 0x02b9 )
				|| ( utfchar > 0x02ba && utfchar < 0x02c2 )
				|| ( utfchar > 0x02cf && utfchar < 0x02d2 )
				|| ( utfchar > 0x02df && utfchar < 0x02e5 )
				|| ( utfchar > 0x036f && utfchar < 0x0374 )
				|| ( utfchar > 0x0375 && utfchar < 0x0378 )
				|| ( utfchar > 0x0379 && utfchar < 0x037e )
				|| ( utfchar > 0x0387 && utfchar < 0x038b )
				|| ( utfchar > 0x038d && utfchar < 0x03a2 )
				|| ( utfchar > 0x03a2 && utfchar < 0x03f6 )
				|| ( utfchar > 0x03f6 && utfchar < 0x0482 )
				|| ( utfchar > 0x0489 && utfchar < 0x0524 )
				|| ( utfchar > 0x0530 && utfchar < 0x0557 )
				|| ( utfchar > 0x0560 && utfchar < 0x0588 )
				|| ( utfchar > 0x05cf && utfchar < 0x05eb )
				|| ( utfchar > 0x05ef && utfchar < 0x05f3 )
				|| ( utfchar > 0x0620 && utfchar < 0x064b )
				|| ( utfchar > 0x066d && utfchar < 0x0670 )
				|| ( utfchar > 0x0670 && utfchar < 0x06d4 )
				|| ( utfchar > 0x06e4 && utfchar < 0x06e7 )
				|| ( utfchar > 0x06ed && utfchar < 0x06f0 )
				|| ( utfchar > 0x06f9 && utfchar < 0x06fd )
				|| ( utfchar > 0x0711 && utfchar < 0x0730 )
				|| ( utfchar > 0x074c && utfchar < 0x07a6 )
				|| ( utfchar > 0x07c9 && utfchar < 0x07eb )
				|| ( utfchar > 0x07f3 && utfchar < 0x07f6 )
				|| ( utfchar > 0x0903 && utfchar < 0x093a )
				|| ( utfchar > 0x0957 && utfchar < 0x0962 )
				|| ( utfchar > 0x0970 && utfchar < 0x0973 )
				|| ( utfchar > 0x097a && utfchar < 0x0980 )
				|| ( utfchar > 0x0984 && utfchar < 0x098d )
				|| ( utfchar > 0x098e && utfchar < 0x0991 )
				|| ( utfchar > 0x0992 && utfchar < 0x09a9 )
				|| ( utfchar > 0x09a9 && utfchar < 0x09b1 )
				|| ( utfchar > 0x09b5 && utfchar < 0x09ba )
				|| ( utfchar > 0x09db && utfchar < 0x09de )
				|| ( utfchar > 0x09de && utfchar < 0x09e2 )
				|| ( utfchar > 0x09ef && utfchar < 0x09f2 )
				|| ( utfchar > 0x0a04 && utfchar < 0x0a0b )
				|| ( utfchar > 0x0a0e && utfchar < 0x0a11 )
				|| ( utfchar > 0x0a12 && utfchar < 0x0a29 )
				|| ( utfchar > 0x0a29 && utfchar < 0x0a31 )
				|| ( utfchar > 0x0a31 && utfchar < 0x0a34 )
				|| ( utfchar > 0x0a34 && utfchar < 0x0a37 )
				|| ( utfchar > 0x0a37 && utfchar < 0x0a3a )
				|| ( utfchar > 0x0a58 && utfchar < 0x0a5d )
				|| ( utfchar > 0x0a71 && utfchar < 0x0a75 )
				|| ( utfchar > 0x0a84 && utfchar < 0x0a8e )
				|| ( utfchar > 0x0a8e && utfchar < 0x0a92 )
				|| ( utfchar > 0x0a92 && utfchar < 0x0aa9 )
				|| ( utfchar > 0x0aa9 && utfchar < 0x0ab1 )
				|| ( utfchar > 0x0ab1 && utfchar < 0x0ab4 )
				|| ( utfchar > 0x0ab4 && utfchar < 0x0aba )
				|| ( utfchar > 0x0adf && utfchar < 0x0ae2 )
				|| ( utfchar > 0x0b04 && utfchar < 0x0b0d )
				|| ( utfchar > 0x0b0e && utfchar < 0x0b11 )
				|| ( utfchar > 0x0b12 && utfchar < 0x0b29 )
				|| ( utfchar > 0x0b29 && utfchar < 0x0b31 )
				|| ( utfchar > 0x0b31 && utfchar < 0x0b34 )
				|| ( utfchar > 0x0b34 && utfchar < 0x0b3a )
				|| ( utfchar > 0x0b5b && utfchar < 0x0b5e )
				|| ( utfchar > 0x0b5e && utfchar < 0x0b62 )
				|| ( utfchar > 0x0b84 && utfchar < 0x0b8b )
				|| ( utfchar > 0x0b8d && utfchar < 0x0b91 )
				|| ( utfchar > 0x0b91 && utfchar < 0x0b96 )
				|| ( utfchar > 0x0b98 && utfchar < 0x0b9b )
				|| ( utfchar > 0x0b9d && utfchar < 0x0ba0 )
				|| ( utfchar > 0x0ba2 && utfchar < 0x0ba5 )
				|| ( utfchar > 0x0ba7 && utfchar < 0x0bab )
				|| ( utfchar > 0x0bad && utfchar < 0x0bba )
				|| ( utfchar > 0x0c04 && utfchar < 0x0c0d )
				|| ( utfchar > 0x0c0d && utfchar < 0x0c11 )
				|| ( utfchar > 0x0c11 && utfchar < 0x0c29 )
				|| ( utfchar > 0x0c29 && utfchar < 0x0c34 )
				|| ( utfchar > 0x0c34 && utfchar < 0x0c3a )
				|| ( utfchar > 0x0c57 && utfchar < 0x0c5a )
				|| ( utfchar > 0x0c5f && utfchar < 0x0c62 )
				|| ( utfchar > 0x0c84 && utfchar < 0x0c8d )
				|| ( utfchar > 0x0c8d && utfchar < 0x0c91 )
				|| ( utfchar > 0x0c91 && utfchar < 0x0ca9 )
				|| ( utfchar > 0x0ca9 && utfchar < 0x0cb4 )
				|| ( utfchar > 0x0cb4 && utfchar < 0x0cba )
				|| ( utfchar > 0x0cdf && utfchar < 0x0ce2 )
				|| ( utfchar > 0x0d04 && utfchar < 0x0d0d )
				|| ( utfchar > 0x0d0d && utfchar < 0x0d11 )
				|| ( utfchar > 0x0d11 && utfchar < 0x0d29 )
				|| ( utfchar > 0x0d29 && utfchar < 0x0d3a )
				|| ( utfchar > 0x0d5f && utfchar < 0x0d62 )
				|| ( utfchar > 0x0d79 && utfchar < 0x0d80 )
				|| ( utfchar > 0x0d84 && utfchar < 0x0d97 )
				|| ( utfchar > 0x0d99 && utfchar < 0x0db2 )
				|| ( utfchar > 0x0db2 && utfchar < 0x0dbc )
				|| ( utfchar > 0x0dbf && utfchar < 0x0dc7 )
				|| ( utfchar > 0x0e00 && utfchar < 0x0e3b )
				|| ( utfchar > 0x0e3f && utfchar < 0x0e4f )
				|| ( utfchar > 0x0e80 && utfchar < 0x0e83 )
				|| ( utfchar > 0x0e86 && utfchar < 0x0e89 )
				|| ( utfchar > 0x0e93 && utfchar < 0x0e98 )
				|| ( utfchar > 0x0e98 && utfchar < 0x0ea0 )
				|| ( utfchar > 0x0ea0 && utfchar < 0x0ea4 )
				|| ( utfchar > 0x0ea9 && utfchar < 0x0eac )
				|| ( utfchar > 0x0eac && utfchar < 0x0eb1 )
				|| ( utfchar > 0x0eb1 && utfchar < 0x0eb4 )
				|| ( utfchar > 0x0ebf && utfchar < 0x0ec5 )
				|| ( utfchar > 0x0edb && utfchar < 0x0ede )
				|| ( utfchar > 0x0f3f && utfchar < 0x0f48 )
				|| ( utfchar > 0x0f48 && utfchar < 0x0f6d )
				|| ( utfchar > 0x0f87 && utfchar < 0x0f8c )
				|| ( utfchar > 0x0fff && utfchar < 0x102b )
				|| ( utfchar > 0x104f && utfchar < 0x1056 )
				|| ( utfchar > 0x1059 && utfchar < 0x105e )
				|| ( utfchar > 0x1064 && utfchar < 0x1067 )
				|| ( utfchar > 0x106d && utfchar < 0x1071 )
				|| ( utfchar > 0x1074 && utfchar < 0x1082 )
				|| ( utfchar > 0x109f && utfchar < 0x10c6 )
				|| ( utfchar > 0x10cf && utfchar < 0x10fb )
				|| ( utfchar > 0x10ff && utfchar < 0x115a )
				|| ( utfchar > 0x115e && utfchar < 0x11a3 )
				|| ( utfchar > 0x11a7 && utfchar < 0x11fa )
				|| ( utfchar > 0x11ff && utfchar < 0x1249 )
				|| ( utfchar > 0x1249 && utfchar < 0x124e )
				|| ( utfchar > 0x124f && utfchar < 0x1257 )
				|| ( utfchar > 0x1259 && utfchar < 0x125e )
				|| ( utfchar > 0x125f && utfchar < 0x1289 )
				|| ( utfchar > 0x1289 && utfchar < 0x128e )
				|| ( utfchar > 0x128f && utfchar < 0x12b1 )
				|| ( utfchar > 0x12b1 && utfchar < 0x12b6 )
				|| ( utfchar > 0x12b7 && utfchar < 0x12bf )
				|| ( utfchar > 0x12c1 && utfchar < 0x12c6 )
				|| ( utfchar > 0x12c7 && utfchar < 0x12d7 )
				|| ( utfchar > 0x12d7 && utfchar < 0x1311 )
				|| ( utfchar > 0x1311 && utfchar < 0x1316 )
				|| ( utfchar > 0x1317 && utfchar < 0x135b )
				|| ( utfchar > 0x137f && utfchar < 0x1390 )
				|| ( utfchar > 0x139f && utfchar < 0x13f5 )
				|| ( utfchar > 0x1400 && utfchar < 0x166d )
				|| ( utfchar > 0x166e && utfchar < 0x1677 )
				|| ( utfchar > 0x1680 && utfchar < 0x169b )
				|| ( utfchar > 0x169f && utfchar < 0x16eb )
				|| ( utfchar > 0x16ed && utfchar < 0x16f1 )
				|| ( utfchar > 0x16ff && utfchar < 0x170d )
				|| ( utfchar > 0x170d && utfchar < 0x1712 )
				|| ( utfchar > 0x171f && utfchar < 0x1732 )
				|| ( utfchar > 0x173f && utfchar < 0x1752 )
				|| ( utfchar > 0x175f && utfchar < 0x176d )
				|| ( utfchar > 0x176d && utfchar < 0x1771 )
				|| ( utfchar > 0x177f && utfchar < 0x17b4 )
				|| ( utfchar > 0x181f && utfchar < 0x1878 )
				|| ( utfchar > 0x187f && utfchar < 0x18a9 )
				|| ( utfchar > 0x18ff && utfchar < 0x191d )
				|| ( utfchar > 0x194f && utfchar < 0x196e )
				|| ( utfchar > 0x196f && utfchar < 0x1975 )
				|| ( utfchar > 0x197f && utfchar < 0x19aa )
				|| ( utfchar > 0x19c0 && utfchar < 0x19c8 )
				|| ( utfchar > 0x19ff && utfchar < 0x1a17 )
				|| ( utfchar > 0x1b04 && utfchar < 0x1b34 )
				|| ( utfchar > 0x1b44 && utfchar < 0x1b4c )
				|| ( utfchar > 0x1b82 && utfchar < 0x1ba1 )
				|| ( utfchar > 0x1bad && utfchar < 0x1bb0 )
				|| ( utfchar > 0x1bff && utfchar < 0x1c24 )
				|| ( utfchar > 0x1c4c && utfchar < 0x1c50 )
				|| ( utfchar > 0x1c59 && utfchar < 0x1c7e )
				|| ( utfchar > 0x1cff && utfchar < 0x1dc0 )
				|| ( utfchar > 0x1dff && utfchar < 0x1f16 )
				|| ( utfchar > 0x1f17 && utfchar < 0x1f1e )
				|| ( utfchar > 0x1f1f && utfchar < 0x1f46 )
				|| ( utfchar > 0x1f47 && utfchar < 0x1f4e )
				|| ( utfchar > 0x1f4f && utfchar < 0x1f58 )
				|| ( utfchar > 0x1f5e && utfchar < 0x1f7e )
				|| ( utfchar > 0x1f7f && utfchar < 0x1fb5 )
				|| ( utfchar > 0x1fb5 && utfchar < 0x1fbd )
				|| ( utfchar > 0x1fc1 && utfchar < 0x1fc5 )
				|| ( utfchar > 0x1fc5 && utfchar < 0x1fcd )
				|| ( utfchar > 0x1fcf && utfchar < 0x1fd4 )
				|| ( utfchar > 0x1fd5 && utfchar < 0x1fdc )
				|| ( utfchar > 0x1fdf && utfchar < 0x1fed )
				|| ( utfchar > 0x1ff1 && utfchar < 0x1ff5 )
				|| ( utfchar > 0x1ff5 && utfchar < 0x1ffd )
				|| ( utfchar > 0x208f && utfchar < 0x2095 )
				|| ( utfchar > 0x2109 && utfchar < 0x2114 )
				|| ( utfchar > 0x2118 && utfchar < 0x211e )
				|| ( utfchar > 0x2129 && utfchar < 0x212e )
				|| ( utfchar > 0x212e && utfchar < 0x213a )
				|| ( utfchar > 0x213b && utfchar < 0x2140 )
				|| ( utfchar > 0x2144 && utfchar < 0x214a )
				|| ( utfchar > 0x215f && utfchar < 0x2189 )
				|| ( utfchar > 0x2bff && utfchar < 0x2c2f )
				|| ( utfchar > 0x2c2f && utfchar < 0x2c5f )
				|| ( utfchar > 0x2c5f && utfchar < 0x2c70 )
				|| ( utfchar > 0x2c70 && utfchar < 0x2c7e )
				|| ( utfchar > 0x2c7f && utfchar < 0x2ce5 )
				|| ( utfchar > 0x2cff && utfchar < 0x2d26 )
				|| ( utfchar > 0x2d2f && utfchar < 0x2d66 )
				|| ( utfchar > 0x2d7f && utfchar < 0x2d97 )
				|| ( utfchar > 0x2d9f && utfchar < 0x2da7 )
				|| ( utfchar > 0x2da7 && utfchar < 0x2daf )
				|| ( utfchar > 0x2daf && utfchar < 0x2db7 )
				|| ( utfchar > 0x2db7 && utfchar < 0x2dbf )
				|| ( utfchar > 0x2dbf && utfchar < 0x2dc7 )
				|| ( utfchar > 0x2dc7 && utfchar < 0x2dcf )
				|| ( utfchar > 0x2dcf && utfchar < 0x2dd7 )
				|| ( utfchar > 0x2dd7 && utfchar < 0x2ddf )
				|| ( utfchar > 0x3004 && utfchar < 0x3008 )
				|| ( utfchar > 0x3020 && utfchar < 0x302a )
				|| ( utfchar > 0x3030 && utfchar < 0x3036 )
				|| ( utfchar > 0x3037 && utfchar < 0x303d )
				|| ( utfchar > 0x3040 && utfchar < 0x3097 )
				|| ( utfchar > 0x309c && utfchar < 0x30a0 )
				|| ( utfchar > 0x30a0 && utfchar < 0x30fb )
				|| ( utfchar > 0x30fb && utfchar < 0x3100 )
				|| ( utfchar > 0x3104 && utfchar < 0x312e )
				|| ( utfchar > 0x3130 && utfchar < 0x318f )
				|| ( utfchar > 0x319f && utfchar < 0x31b8 )
				|| ( utfchar > 0x31ef && utfchar < 0x3200 )
				|| ( utfchar > 0x33ff && utfchar < 0x4db6 )
				|| ( utfchar > 0x4dff && utfchar < 0x9fc4 )
				|| ( utfchar > 0x9fff && utfchar < 0xa48d )
				|| ( utfchar > 0xa4ff && utfchar < 0xa60d )
				|| ( utfchar > 0xa60f && utfchar < 0xa620 )
				|| ( utfchar > 0xa629 && utfchar < 0xa62c )
				|| ( utfchar > 0xa63f && utfchar < 0xa660 )
				|| ( utfchar > 0xa661 && utfchar < 0xa66f )
				|| ( utfchar > 0xa67f && utfchar < 0xa698 )
				|| ( utfchar > 0xa721 && utfchar < 0xa788 )
				|| ( utfchar > 0xa78a && utfchar < 0xa78d )
				|| ( utfchar > 0xa7fa && utfchar < 0xa802 )
				|| ( utfchar > 0xa802 && utfchar < 0xa806 )
				|| ( utfchar > 0xa806 && utfchar < 0xa80b )
				|| ( utfchar > 0xa80b && utfchar < 0xa823 )
				|| ( utfchar > 0xa83f && utfchar < 0xa874 )
				|| ( utfchar > 0xa881 && utfchar < 0xa8b4 )
				|| ( utfchar > 0xa909 && utfchar < 0xa926 )
				|| ( utfchar > 0xa92f && utfchar < 0xa947 )
				|| ( utfchar > 0xa9ff && utfchar < 0xaa29 )
				|| ( utfchar > 0xaa3f && utfchar < 0xaa43 )
				|| ( utfchar > 0xaa43 && utfchar < 0xaa4c )
				|| ( utfchar > 0xabff && utfchar < 0xd7a4 )
				|| ( utfchar > 0xf8ff && utfchar < 0xfa2e )
				|| ( utfchar > 0xfa2f && utfchar < 0xfa6b )
				|| ( utfchar > 0xfa6f && utfchar < 0xfada )
				|| ( utfchar > 0xfaff && utfchar < 0xfb07 )
				|| ( utfchar > 0xfb12 && utfchar < 0xfb18 )
				|| ( utfchar > 0xfb1e && utfchar < 0xfb29 )
				|| ( utfchar > 0xfb29 && utfchar < 0xfb37 )
				|| ( utfchar > 0xfb37 && utfchar < 0xfb3d )
				|| ( utfchar > 0xfb3f && utfchar < 0xfb42 )
				|| ( utfchar > 0xfb42 && utfchar < 0xfb45 )
				|| ( utfchar > 0xfb45 && utfchar < 0xfbb2 )
				|| ( utfchar > 0xfbd2 && utfchar < 0xfd3e )
				|| ( utfchar > 0xfd4f && utfchar < 0xfd90 )
				|| ( utfchar > 0xfd91 && utfchar < 0xfdc8 )
				|| ( utfchar > 0xfdef && utfchar < 0xfdfc )
				|| ( utfchar > 0xfe6f && utfchar < 0xfe75 )
				|| ( utfchar > 0xfe75 && utfchar < 0xfefd )
				|| ( utfchar > 0xff20 && utfchar < 0xff3b )
				|| ( utfchar > 0xff40 && utfchar < 0xff5b )
				|| ( utfchar > 0xff65 && utfchar < 0xffbf )
				|| ( utfchar > 0xffc1 && utfchar < 0xffc8 )
				|| ( utfchar > 0xffc9 && utfchar < 0xffd0 )
				|| ( utfchar > 0xffd1 && utfchar < 0xffd8 )
				|| ( utfchar > 0xffd9 && utfchar < 0xffdd )
				|| utfchar == 0xaa || utfchar == 0xb5 || utfchar == 0xba || utfchar == 0x02ee || utfchar == 0x0386
				|| utfchar == 0x038c || utfchar == 0x0559 || utfchar == 0x06d5 || utfchar == 0x06ff	|| utfchar == 0x0710
				|| utfchar == 0x07b1 || utfchar == 0x07fa || utfchar == 0x093d || utfchar == 0x0950 || utfchar == 0x09b2
				|| utfchar == 0x09bd || utfchar == 0x09ce || utfchar == 0x0a5e || utfchar == 0x0abd || utfchar == 0x0ad0
				|| utfchar == 0x0b3d || utfchar == 0x0b71 || utfchar == 0x0b83 || utfchar == 0x0b9c || utfchar == 0x0bd0
				|| utfchar == 0x0c3d || utfchar == 0x0cbd || utfchar == 0x0cde || utfchar == 0x0d3d || utfchar == 0x0dbd
				|| utfchar == 0x0e84 || utfchar == 0x0e8a || utfchar == 0x0e8d || utfchar == 0x0ea5	|| utfchar == 0x0ea7
				|| utfchar == 0x0ebd || utfchar == 0x0ec6 || utfchar == 0x0f00 || utfchar == 0x103f	|| utfchar == 0x1061
				|| utfchar == 0x108e || utfchar == 0x10fc || utfchar == 0x1258 || utfchar == 0x12c0	|| utfchar == 0x17d7
				|| utfchar == 0x17dc || utfchar == 0x18aa || utfchar == 0x1f59 || utfchar == 0x1f5b	|| utfchar == 0x1f5d
				|| utfchar == 0x1fbe || utfchar == 0x2071 || utfchar == 0x207f || utfchar == 0x2102	|| utfchar == 0x2107
				|| utfchar == 0x2115 || utfchar == 0x2124 || utfchar == 0x2126 || utfchar == 0x2128	|| utfchar == 0x214e
				|| utfchar == 0x2d6f || utfchar == 0xfb1d || utfchar == 0xfb3e;
		};
		booinline bool isalnum( ::booldog::uint32 utfchar )
		{
			return ( utfchar > 0x2f && utfchar < 0x3a )
				|| ( utfchar > 0x40 && utfchar < 0x5b )
				|| ( utfchar > 0x60 && utfchar < 0x7b )
				|| ( utfchar > 0xb1 && utfchar < 0xb4 )
				|| ( utfchar > 0xb8 && utfchar < 0xbb )
				|| ( utfchar > 0xbf && utfchar < 0xd7 )
				|| ( utfchar > 0xd7 && utfchar < 0xf7 )
				|| ( utfchar > 0xf7 && utfchar < 0x02b9 )
				|| ( utfchar > 0x02ba && utfchar < 0x02c2 )
				|| ( utfchar > 0x02cf && utfchar < 0x02d2 )
				|| ( utfchar > 0x02df && utfchar < 0x02e5 )
				|| ( utfchar > 0x036f && utfchar < 0x0374 )
				|| ( utfchar > 0x0375 && utfchar < 0x0378 )
				|| ( utfchar > 0x0379 && utfchar < 0x037e )
				|| ( utfchar > 0x0387 && utfchar < 0x038b )
				|| ( utfchar > 0x038d && utfchar < 0x03a2 )
				|| ( utfchar > 0x03a2 && utfchar < 0x03f6 )
				|| ( utfchar > 0x03f6 && utfchar < 0x0482 )
				|| ( utfchar > 0x0489 && utfchar < 0x0524 )
				|| ( utfchar > 0x0530 && utfchar < 0x0557 )
				|| ( utfchar > 0x0560 && utfchar < 0x0588 )
				|| ( utfchar > 0x05cf && utfchar < 0x05eb )
				|| ( utfchar > 0x05ef && utfchar < 0x05f3 )
				|| ( utfchar > 0x0620 && utfchar < 0x064b )
				|| ( utfchar > 0x065f && utfchar < 0x066a )
				|| ( utfchar > 0x066d && utfchar < 0x0670 )
				|| ( utfchar > 0x0670 && utfchar < 0x06d4 )
				|| ( utfchar > 0x06e4 && utfchar < 0x06e7 )
				|| ( utfchar > 0x06ed && utfchar < 0x06fd )
				|| ( utfchar > 0x0711 && utfchar < 0x0730 )
				|| ( utfchar > 0x074c && utfchar < 0x07a6 )
				|| ( utfchar > 0x07bf && utfchar < 0x07eb )
				|| ( utfchar > 0x07f3 && utfchar < 0x07f6 )
				|| ( utfchar > 0x0903 && utfchar < 0x093a )
				|| ( utfchar > 0x0957 && utfchar < 0x0962 )
				|| ( utfchar > 0x0965 && utfchar < 0x0970 )
				|| ( utfchar > 0x0970 && utfchar < 0x0973 )
				|| ( utfchar > 0x097a && utfchar < 0x0980 )
				|| ( utfchar > 0x0984 && utfchar < 0x098d )
				|| ( utfchar > 0x098e && utfchar < 0x0991 )
				|| ( utfchar > 0x0992 && utfchar < 0x09a9 )
				|| ( utfchar > 0x09a9 && utfchar < 0x09b1 )
				|| ( utfchar > 0x09b5 && utfchar < 0x09ba )
				|| ( utfchar > 0x09db && utfchar < 0x09de )
				|| ( utfchar > 0x09de && utfchar < 0x09e2 )
				|| ( utfchar > 0x09e5 && utfchar < 0x09f2 )
				|| ( utfchar > 0x0a04 && utfchar < 0x0a0b )
				|| ( utfchar > 0x0a0e && utfchar < 0x0a11 )
				|| ( utfchar > 0x0a12 && utfchar < 0x0a29 )
				|| ( utfchar > 0x0a29 && utfchar < 0x0a31 )
				|| ( utfchar > 0x0a31 && utfchar < 0x0a34 )
				|| ( utfchar > 0x0a34 && utfchar < 0x0a37 )
				|| ( utfchar > 0x0a37 && utfchar < 0x0a3a )
				|| ( utfchar > 0x0a58 && utfchar < 0x0a5d )
				|| ( utfchar > 0x0a65 && utfchar < 0x0a70 )
				|| ( utfchar > 0x0a71 && utfchar < 0x0a75 )
				|| ( utfchar > 0x0a84 && utfchar < 0x0a8e )
				|| ( utfchar > 0x0a8e && utfchar < 0x0a92 )
				|| ( utfchar > 0x0a92 && utfchar < 0x0aa9 )
				|| ( utfchar > 0x0aa9 && utfchar < 0x0ab1 )
				|| ( utfchar > 0x0ab1 && utfchar < 0x0ab4 )
				|| ( utfchar > 0x0ab4 && utfchar < 0x0aba )
				|| ( utfchar > 0x0adf && utfchar < 0x0ae2 )
				|| ( utfchar > 0x0ae5 && utfchar < 0x0af0 )
				|| ( utfchar > 0x0b04 && utfchar < 0x0b0d )
				|| ( utfchar > 0x0b0e && utfchar < 0x0b11 )
				|| ( utfchar > 0x0b12 && utfchar < 0x0b29 )
				|| ( utfchar > 0x0b29 && utfchar < 0x0b31 )
				|| ( utfchar > 0x0b31 && utfchar < 0x0b34 )
				|| ( utfchar > 0x0b34 && utfchar < 0x0b3a )
				|| ( utfchar > 0x0b5b && utfchar < 0x0b5e )
				|| ( utfchar > 0x0b5e && utfchar < 0x0b62 )
				|| ( utfchar > 0x0b65 && utfchar < 0x0b70 )
				|| ( utfchar > 0x0b84 && utfchar < 0x0b8b )
				|| ( utfchar > 0x0b8d && utfchar < 0x0b91 )
				|| ( utfchar > 0x0b91 && utfchar < 0x0b96 )
				|| ( utfchar > 0x0b98 && utfchar < 0x0b9b )
				|| ( utfchar > 0x0b9d && utfchar < 0x0ba0 )
				|| ( utfchar > 0x0ba2 && utfchar < 0x0ba5 )
				|| ( utfchar > 0x0ba7 && utfchar < 0x0bab )
				|| ( utfchar > 0x0bad && utfchar < 0x0bba )
				|| ( utfchar > 0x0be5 && utfchar < 0x0bf0 )
				|| ( utfchar > 0x0c04 && utfchar < 0x0c0d )
				|| ( utfchar > 0x0c0d && utfchar < 0x0c11 )
				|| ( utfchar > 0x0c11 && utfchar < 0x0c29 )
				|| ( utfchar > 0x0c29 && utfchar < 0x0c34 )
				|| ( utfchar > 0x0c34 && utfchar < 0x0c3a )
				|| ( utfchar > 0x0c57 && utfchar < 0x0c5a )
				|| ( utfchar > 0x0c5f && utfchar < 0x0c62 )
				|| ( utfchar > 0x0c65 && utfchar < 0x0c70 )
				|| ( utfchar > 0x0c84 && utfchar < 0x0c8d )
				|| ( utfchar > 0x0c8d && utfchar < 0x0c91 )
				|| ( utfchar > 0x0c91 && utfchar < 0x0ca9 )
				|| ( utfchar > 0x0ca9 && utfchar < 0x0cb4 )
				|| ( utfchar > 0x0cb4 && utfchar < 0x0cba )
				|| ( utfchar > 0x0cdf && utfchar < 0x0ce2 )
				|| ( utfchar > 0x0ce5 && utfchar < 0x0cf0 )
				|| ( utfchar > 0x0d04 && utfchar < 0x0d0d )
				|| ( utfchar > 0x0d0d && utfchar < 0x0d11 )
				|| ( utfchar > 0x0d11 && utfchar < 0x0d29 )
				|| ( utfchar > 0x0d29 && utfchar < 0x0d3a )
				|| ( utfchar > 0x0d5f && utfchar < 0x0d62 )
				|| ( utfchar > 0x0d65 && utfchar < 0x0d70 )
				|| ( utfchar > 0x0d79 && utfchar < 0x0d80 )
				|| ( utfchar > 0x0d84 && utfchar < 0x0d97 )
				|| ( utfchar > 0x0d99 && utfchar < 0x0db2 )
				|| ( utfchar > 0x0db2 && utfchar < 0x0dbc )
				|| ( utfchar > 0x0dbf && utfchar < 0x0dc7 )
				|| ( utfchar > 0x0e00 && utfchar < 0x0e3b )
				|| ( utfchar > 0x0e3f && utfchar < 0x0e4f )
				|| ( utfchar > 0x0e4f && utfchar < 0x0e5a )
				|| ( utfchar > 0x0e80 && utfchar < 0x0e83 )
				|| ( utfchar > 0x0e86 && utfchar < 0x0e89 )
				|| ( utfchar > 0x0e93 && utfchar < 0x0e98 )
				|| ( utfchar > 0x0e98 && utfchar < 0x0ea0 )
				|| ( utfchar > 0x0ea0 && utfchar < 0x0ea4 )
				|| ( utfchar > 0x0ea9 && utfchar < 0x0eac )
				|| ( utfchar > 0x0eac && utfchar < 0x0eb1 )
				|| ( utfchar > 0x0eb1 && utfchar < 0x0eb4 )
				|| ( utfchar > 0x0ebf && utfchar < 0x0ec5 )
				|| ( utfchar > 0x0ecf && utfchar < 0x0eda )
				|| ( utfchar > 0x0edb && utfchar < 0x0ede )
				|| ( utfchar > 0x0f1f && utfchar < 0x0f2a )
				|| ( utfchar > 0x0f3f && utfchar < 0x0f48 )
				|| ( utfchar > 0x0f48 && utfchar < 0x0f6d )
				|| ( utfchar > 0x0f87 && utfchar < 0x0f8c )
				|| ( utfchar > 0x0fff && utfchar < 0x102b )
				|| ( utfchar > 0x103e && utfchar < 0x104a )
				|| ( utfchar > 0x104f && utfchar < 0x1056 )
				|| ( utfchar > 0x1059 && utfchar < 0x105e )
				|| ( utfchar > 0x1064 && utfchar < 0x1067 )
				|| ( utfchar > 0x106d && utfchar < 0x1071 )
				|| ( utfchar > 0x1074 && utfchar < 0x1082 )
				|| ( utfchar > 0x108f && utfchar < 0x109a )
				|| ( utfchar > 0x109f && utfchar < 0x10c6 )
				|| ( utfchar > 0x10cf && utfchar < 0x10fb )
				|| ( utfchar > 0x10ff && utfchar < 0x115a )
				|| ( utfchar > 0x115e && utfchar < 0x11a3 )
				|| ( utfchar > 0x11a7 && utfchar < 0x11fa )
				|| ( utfchar > 0x11ff && utfchar < 0x1249 )
				|| ( utfchar > 0x1249 && utfchar < 0x124e )
				|| ( utfchar > 0x124f && utfchar < 0x1257 )
				|| ( utfchar > 0x1259 && utfchar < 0x125e )
				|| ( utfchar > 0x125f && utfchar < 0x1289 )
				|| ( utfchar > 0x1289 && utfchar < 0x128e )
				|| ( utfchar > 0x128f && utfchar < 0x12b1 )
				|| ( utfchar > 0x12b1 && utfchar < 0x12b6 )
				|| ( utfchar > 0x12b7 && utfchar < 0x12bf )
				|| ( utfchar > 0x12c1 && utfchar < 0x12c6 )
				|| ( utfchar > 0x12c7 && utfchar < 0x12d7 )
				|| ( utfchar > 0x12d7 && utfchar < 0x1311 )
				|| ( utfchar > 0x1311 && utfchar < 0x1316 )
				|| ( utfchar > 0x1317 && utfchar < 0x135b )
				|| ( utfchar > 0x137f && utfchar < 0x1390 )
				|| ( utfchar > 0x139f && utfchar < 0x13f5 )
				|| ( utfchar > 0x1400 && utfchar < 0x166d )
				|| ( utfchar > 0x166e && utfchar < 0x1677 )
				|| ( utfchar > 0x1680 && utfchar < 0x169b )
				|| ( utfchar > 0x169f && utfchar < 0x16eb )
				|| ( utfchar > 0x16ed && utfchar < 0x16f1 )
				|| ( utfchar > 0x16ff && utfchar < 0x170d )
				|| ( utfchar > 0x170d && utfchar < 0x1712 )
				|| ( utfchar > 0x171f && utfchar < 0x1732 )
				|| ( utfchar > 0x173f && utfchar < 0x1752 )
				|| ( utfchar > 0x175f && utfchar < 0x176d )
				|| ( utfchar > 0x176d && utfchar < 0x1771 )
				|| ( utfchar > 0x177f && utfchar < 0x17b4 )
				|| ( utfchar > 0x17df && utfchar < 0x17ea )
				|| ( utfchar > 0x180f && utfchar < 0x181a )
				|| ( utfchar > 0x181f && utfchar < 0x1878 )
				|| ( utfchar > 0x187f && utfchar < 0x18a9 )
				|| ( utfchar > 0x18ff && utfchar < 0x191d )
				|| ( utfchar > 0x1945 && utfchar < 0x196e )
				|| ( utfchar > 0x196f && utfchar < 0x1975 )
				|| ( utfchar > 0x197f && utfchar < 0x19aa )
				|| ( utfchar > 0x19c0 && utfchar < 0x19c8 )
				|| ( utfchar > 0x19cf && utfchar < 0x19da )
				|| ( utfchar > 0x19ff && utfchar < 0x1a17 )
				|| ( utfchar > 0x1b04 && utfchar < 0x1b34 )
				|| ( utfchar > 0x1b44 && utfchar < 0x1b4c )
				|| ( utfchar > 0x1b4f && utfchar < 0x1b5a )
				|| ( utfchar > 0x1b82 && utfchar < 0x1ba1 )
				|| ( utfchar > 0x1bad && utfchar < 0x1bba )
				|| ( utfchar > 0x1bff && utfchar < 0x1c24 )
				|| ( utfchar > 0x1c3f && utfchar < 0x1c4a )
				|| ( utfchar > 0x1c4c && utfchar < 0x1c7e )
				|| ( utfchar > 0x1cff && utfchar < 0x1dc0 )
				|| ( utfchar > 0x1dff && utfchar < 0x1f16 )
				|| ( utfchar > 0x1f17 && utfchar < 0x1f1e )
				|| ( utfchar > 0x1f1f && utfchar < 0x1f46 )
				|| ( utfchar > 0x1f47 && utfchar < 0x1f4e )
				|| ( utfchar > 0x1f4f && utfchar < 0x1f58 )
				|| ( utfchar > 0x1f5e && utfchar < 0x1f7e )
				|| ( utfchar > 0x1f7f && utfchar < 0x1fb5 )
				|| ( utfchar > 0x1fb5 && utfchar < 0x1fbd )
				|| ( utfchar > 0x1fc1 && utfchar < 0x1fc5 )
				|| ( utfchar > 0x1fc5 && utfchar < 0x1fcd )
				|| ( utfchar > 0x1fcf && utfchar < 0x1fd4 )
				|| ( utfchar > 0x1fd5 && utfchar < 0x1fdc )
				|| ( utfchar > 0x1fdf && utfchar < 0x1fed )
				|| ( utfchar > 0x1ff1 && utfchar < 0x1ff5 )
				|| ( utfchar > 0x1ff5 && utfchar < 0x1ffd )
				|| ( utfchar > 0x208f && utfchar < 0x2095 )
				|| ( utfchar > 0x2109 && utfchar < 0x2114 )
				|| ( utfchar > 0x2118 && utfchar < 0x211e )
				|| ( utfchar > 0x2129 && utfchar < 0x212e )
				|| ( utfchar > 0x212e && utfchar < 0x213a )
				|| ( utfchar > 0x213b && utfchar < 0x2140 )
				|| ( utfchar > 0x2144 && utfchar < 0x214a )
				|| ( utfchar > 0x215f && utfchar < 0x2189 )
				|| ( utfchar > 0x2bff && utfchar < 0x2c2f )
				|| ( utfchar > 0x2c2f && utfchar < 0x2c5f )
				|| ( utfchar > 0x2c5f && utfchar < 0x2c70 )
				|| ( utfchar > 0x2c70 && utfchar < 0x2c7e )
				|| ( utfchar > 0x2c7f && utfchar < 0x2ce5 )
				|| ( utfchar > 0x2cff && utfchar < 0x2d26 )
				|| ( utfchar > 0x2d2f && utfchar < 0x2d66 )
				|| ( utfchar > 0x2d7f && utfchar < 0x2d97 )
				|| ( utfchar > 0x2d9f && utfchar < 0x2da7 )
				|| ( utfchar > 0x2da7 && utfchar < 0x2daf )
				|| ( utfchar > 0x2daf && utfchar < 0x2db7 )
				|| ( utfchar > 0x2db7 && utfchar < 0x2dbf )
				|| ( utfchar > 0x2dbf && utfchar < 0x2dc7 )
				|| ( utfchar > 0x2dc7 && utfchar < 0x2dcf )
				|| ( utfchar > 0x2dcf && utfchar < 0x2dd7 )
				|| ( utfchar > 0x2dd7 && utfchar < 0x2ddf )
				|| ( utfchar > 0x3004 && utfchar < 0x3008 )
				|| ( utfchar > 0x3020 && utfchar < 0x302a )
				|| ( utfchar > 0x3030 && utfchar < 0x3036 )
				|| ( utfchar > 0x3037 && utfchar < 0x303d )
				|| ( utfchar > 0x3040 && utfchar < 0x3097 )
				|| ( utfchar > 0x309c && utfchar < 0x30a0 )
				|| ( utfchar > 0x30a0 && utfchar < 0x30fb )
				|| ( utfchar > 0x30fb && utfchar < 0x3100 )
				|| ( utfchar > 0x3104 && utfchar < 0x312e )
				|| ( utfchar > 0x3130 && utfchar < 0x318f )
				|| ( utfchar > 0x319f && utfchar < 0x31b8 )
				|| ( utfchar > 0x31ef && utfchar < 0x3200 )
				|| ( utfchar > 0x33ff && utfchar < 0x4db6 )
				|| ( utfchar > 0x4dff && utfchar < 0x9fc4 )
				|| ( utfchar > 0x9fff && utfchar < 0xa48d )
				|| ( utfchar > 0xa4ff && utfchar < 0xa60d )
				|| ( utfchar > 0xa60f && utfchar < 0xa62c )
				|| ( utfchar > 0xa63f && utfchar < 0xa660 )
				|| ( utfchar > 0xa661 && utfchar < 0xa66f )
				|| ( utfchar > 0xa67f && utfchar < 0xa698 )
				|| ( utfchar > 0xa721 && utfchar < 0xa788 )
				|| ( utfchar > 0xa78a && utfchar < 0xa78d )
				|| ( utfchar > 0xa7fa && utfchar < 0xa802 )
				|| ( utfchar > 0xa802 && utfchar < 0xa806 )
				|| ( utfchar > 0xa806 && utfchar < 0xa80b )
				|| ( utfchar > 0xa80b && utfchar < 0xa823 )
				|| ( utfchar > 0xa83f && utfchar < 0xa874 )
				|| ( utfchar > 0xa881 && utfchar < 0xa8b4 )
				|| ( utfchar > 0xa8cf && utfchar < 0xa8da )
				|| ( utfchar > 0xa8ff && utfchar < 0xa926 )
				|| ( utfchar > 0xa92f && utfchar < 0xa947 )
				|| ( utfchar > 0xa9ff && utfchar < 0xaa29 )
				|| ( utfchar > 0xaa3f && utfchar < 0xaa43 )
				|| ( utfchar > 0xaa43 && utfchar < 0xaa4c )
				|| ( utfchar > 0xaa4f && utfchar < 0xaa5a )
				|| ( utfchar > 0xabff && utfchar < 0xd7a4 )
				|| ( utfchar > 0xf8ff && utfchar < 0xfa2e )
				|| ( utfchar > 0xfa2f && utfchar < 0xfa6b )
				|| ( utfchar > 0xfa6f && utfchar < 0xfada )
				|| ( utfchar > 0xfaff && utfchar < 0xfb07 )
				|| ( utfchar > 0xfb12 && utfchar < 0xfb18 )
				|| ( utfchar > 0xfb1e && utfchar < 0xfb29 )
				|| ( utfchar > 0xfb29 && utfchar < 0xfb37 )
				|| ( utfchar > 0xfb37 && utfchar < 0xfb3d )
				|| ( utfchar > 0xfb3f && utfchar < 0xfb42 )
				|| ( utfchar > 0xfb42 && utfchar < 0xfb45 )
				|| ( utfchar > 0xfb45 && utfchar < 0xfbb2 )
				|| ( utfchar > 0xfbd2 && utfchar < 0xfd3e )
				|| ( utfchar > 0xfd4f && utfchar < 0xfd90 )
				|| ( utfchar > 0xfd91 && utfchar < 0xfdc8 )
				|| ( utfchar > 0xfdef && utfchar < 0xfdfc )
				|| ( utfchar > 0xfe6f && utfchar < 0xfe75 )
				|| ( utfchar > 0xfe75 && utfchar < 0xfefd )
				|| ( utfchar > 0xff0f && utfchar < 0xff1a )
				|| ( utfchar > 0xff20 && utfchar < 0xff3b )
				|| ( utfchar > 0xff40 && utfchar < 0xff5b )
				|| ( utfchar > 0xff65 && utfchar < 0xffbf )
				|| ( utfchar > 0xffc1 && utfchar < 0xffc8 )
				|| ( utfchar > 0xffc9 && utfchar < 0xffd0 )
				|| ( utfchar > 0xffd1 && utfchar < 0xffd8 )
				|| ( utfchar > 0xffd9 && utfchar < 0xffdd )
				|| utfchar == 0xaa || utfchar == 0xb5 || utfchar == 0x02ee || utfchar == 0x0386 || utfchar == 0x038c
				|| utfchar == 0x0559 || utfchar == 0x06d5 || utfchar == 0x06ff || utfchar == 0x0710	|| utfchar == 0x07b1
				|| utfchar == 0x07fa || utfchar == 0x093d || utfchar == 0x0950 || utfchar == 0x09b2	|| utfchar == 0x09bd
				|| utfchar == 0x09ce || utfchar == 0x0a5e || utfchar == 0x0abd || utfchar == 0x0ad0 || utfchar == 0x0b3d
				|| utfchar == 0x0b71 || utfchar == 0x0b83 || utfchar == 0x0b9c || utfchar == 0x0bd0	|| utfchar == 0x0c3d
				|| utfchar == 0x0cbd || utfchar == 0x0cde || utfchar == 0x0d3d || utfchar == 0x0dbd	|| utfchar == 0x0e84
				|| utfchar == 0x0e8a || utfchar == 0x0e8d || utfchar == 0x0ea5 || utfchar == 0x0ea7	|| utfchar == 0x0ebd
				|| utfchar == 0x0ec6 || utfchar == 0x0f00 || utfchar == 0x1061 || utfchar == 0x108e	|| utfchar == 0x10fc
				|| utfchar == 0x1258 || utfchar == 0x12c0 || utfchar == 0x17d7 || utfchar == 0x17dc || utfchar == 0x18aa
				|| utfchar == 0x1f59 || utfchar == 0x1f5b || utfchar == 0x1f5d || utfchar == 0x1fbe	|| utfchar == 0x2071
				|| utfchar == 0x207f || utfchar == 0x2102 || utfchar == 0x2107 || utfchar == 0x2115	|| utfchar == 0x2124
				|| utfchar == 0x2126 || utfchar == 0x2128 || utfchar == 0x214e || utfchar == 0x2d6f	|| utfchar == 0xfb1d
				|| utfchar == 0xfb3e;
		};
		booinline ::booldog::enums::string::conversion_result to_utf8( const char* utf32_ptr , size_t& srcbyteindex 
			, size_t utf32charcount , char* utf8_ptr , size_t& dstbyteindex , size_t utf8allocbytes , size_t& utf8_bytes 
			, size_t& utf8length )
		{
			const ::booldog::uint32* source = (::booldog::uint32*)(utf32_ptr + srcbyteindex)
				, * source_end = (::booldog::uint32*)(utf32_ptr + utf32charcount);
			if(source_end < source)
				source_end = (::booldog::uint32*)SIZE_MAX;
			::booldog::uint8* target = (::booldog::uint8*)utf8_ptr + dstbyteindex
				, * target_end = (::booldog::uint8*)utf8_ptr + utf8allocbytes;
			::booldog::uint32 ch = 0;
			::booldog::byte diff = 0;
			if(utf8_ptr == 0)
				goto goto_conversion_result_targetExhausted;					
			while( source < source_end )
			{
				ch = *source++;
				/* UTF-16 surrogate values are illegal in UTF-32 */
				if( ch >= (::booldog::uint32)0xD800 && ch <= (::booldog::uint32)0xDFFF )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				/*
				* Figure out how many bytes the result will require. Turn any
				* illegally large UTF32 things (> Plane 17) into replacement chars.
				*/
				if( ch < (::booldog::uint32)0x80 )
				{
					target += 1;
					if( target > target_end )
					{
						if( (::booldog::byte)( ch | ::booldog::consts::utf32::_firstByteMark[ 1 ] ) == 0 )
						{
							target--;
							break;
						}
						diff = 1;
						goto goto_conversion_result_targetExhausted;
					}
					target[ -1 ] = (::booldog::byte)( ch | ::booldog::consts::utf32::_firstByteMark[ 1 ] );
					if( target[ -1 ] == 0 )
					{
						target--;
						break;
					}
				}
				else if( ch < (::booldog::uint32)0x800 )
				{
					target += 2;
					if( target > target_end )
					{
						diff = 2;
						goto goto_conversion_result_targetExhausted;
					}
					target[ -1 ] = (::booldog::byte)((ch | 0x80) & 0xBF); ch >>= 6;
					target[ -2 ] = (::booldog::byte)( ch | ::booldog::consts::utf32::_firstByteMark[ 2 ] );
				} 
				else if( ch < (::booldog::uint32)0x10000 )
				{
					target += 3;
					if( target > target_end )
					{
						diff = 3;
						goto goto_conversion_result_targetExhausted;
					}
					target[ -1 ] = (::booldog::byte)((ch | 0x80) & 0xBF); ch >>= 6;
					target[ -2 ] = (::booldog::byte)((ch | 0x80) & 0xBF); ch >>= 6;
					target[ -3 ] = (::booldog::byte)( ch | ::booldog::consts::utf32::_firstByteMark[ 3 ] );
				}
				else if( ch <= (::booldog::uint32)0x0010FFFF )
				{
					target += 4;
					if( target > target_end )
					{
						diff = 4;
						goto goto_conversion_result_targetExhausted;
					}
					target[ -1 ] = (::booldog::byte)((ch | 0x80) & 0xBF); ch >>= 6;
					target[ -2 ] = (::booldog::byte)((ch | 0x80) & 0xBF); ch >>= 6;
					target[ -3 ] = (::booldog::byte)((ch | 0x80) & 0xBF); ch >>= 6;
					target[ -4 ] = (::booldog::byte)( ch | ::booldog::consts::utf32::_firstByteMark[ 4 ] );
				} 
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				utf8length++;
			}
			utf8_bytes = (char*)target - utf8_ptr;
			srcbyteindex = ((char*)source - utf32_ptr);
			dstbyteindex = utf8_bytes;
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:
			if(utf8_ptr)
			{
				utf8_bytes = (char*)target - utf8_ptr;
				srcbyteindex = ((char*)source - utf32_ptr) - 4;
				dstbyteindex = utf8_bytes - diff;
			}
			while( source < source_end ) 
			{
				ch = *source++;
				if( ch >= (::booldog::uint32)0xD800 && ch <= (::booldog::uint32)0xDFFF )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				if( ch < (::booldog::uint32)0x80 )
				{
					if( (::booldog::byte)( ch | ::booldog::consts::utf32::_firstByteMark[ 1 ] ) == 0 )
						break;
					++utf8_bytes;
				}
				else if( ch < (::booldog::uint32)0x800 )
					utf8_bytes += 2;
				else if( ch < (::booldog::uint32)0x10000 )
					utf8_bytes += 3;
				else if( ch <= (::booldog::uint32)0x0010FFFF )
					utf8_bytes += 4;
				else
					return ::booldog::enums::string::conversion_result_sourceIllegal;
			}
			return ::booldog::enums::string::conversion_result_targetExhausted;
		}		
		template< size_t step >
		booinline bool toutf8(::booldog::result* pres, ::booldog::allocator* allocator, char*& dst , size_t& dstlen , size_t& dstsize
			, const char* utf32, size_t& srcbyteindex, size_t utf32bytescount
			, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			::booldog::result locres;
			BOOINIT_RESULT(::booldog::result);
			size_t dstbyteindex = 0, utf8bytes = step;
			::booldog::enums::string::conversion_result convres = ::booldog::enums::string::conversion_result_OK;
			for(;;)
			{
				if(dstsize < utf8bytes + 1)
				{
					dstsize = utf8bytes + 1;
					dst = allocator->realloc_array< char >(dst, dstsize, debuginfo);
				}
				if(dst == 0)
				{
					res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
					return false;
				}
				convres = ::booldog::utf32::to_utf8(utf32, srcbyteindex, utf32bytescount, dst, dstbyteindex , dstsize, utf8bytes
					, dstlen);
				if(convres == ::booldog::enums::string::conversion_result_sourceIllegal)
				{
					res->booerr(::booldog::enums::result::booerr_type_conversion_result_source_illegal);
					return false;
				}
				else if(convres == ::booldog::enums::string::conversion_result_OK)
				{
					if(utf8bytes == dstsize)
					{
						++dstsize;
						dst = allocator->realloc_array< char >(dst, dstsize, debuginfo);
						if(dst == 0)
						{
							res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
							return false;
						}
					}
					dstlen = utf8bytes;
					dst[utf8bytes] = 0;
					return true;
				}
				else if(convres == ::booldog::enums::string::conversion_result_sourceExhausted)
				{
					res->booerr(::booldog::enums::result::booerr_type_conversion_result_source_exhausted);
					return false;
				}
			}
		}
		template< size_t step >
		booinline bool toutf8(::booldog::result_mbchar& pres, const char* utf32, size_t& srcbyteindex, size_t utf32bytescount
			, const ::booldog::debug::info& debuginfo = debuginfo_macros)
		{
			::booldog::result res;
			if(::booldog::utf32::toutf8< step >(&res, pres.mballocator, pres.mbchar, pres.mblen, pres.mbsize, utf32, srcbyteindex
				, utf32bytescount, debuginfo))
				return true;
			else
			{
				pres.copy(res);
				return false;
			}
		}
		booinline ::booldog::enums::string::conversion_result to_utf16( const char* utf32_ptr , size_t utf32_ptr_count , char* utf16_ptr , size_t utf16_ptr_count , size_t& utf16_bytes )
		{
			utf16_bytes = 0;
			const ::booldog::uint32* source = (::booldog::uint32*)utf32_ptr , * source_end = (::booldog::uint32*)( &utf32_ptr[ utf32_ptr_count - 1 ] + 1 );
			::booldog::uint16* target = (::booldog::uint16*)utf16_ptr , * target_end = 0;
			if( utf16_ptr )
				target_end = (::booldog::uint16*)( &utf16_ptr[ utf16_ptr_count - 1 ] + 1 );
			::booldog::uint32 ch = 0;
			while( source < source_end )
			{
				ch = *source++;
				if( ch <= (::booldog::uint32)0x0000FFFF )
				{ /* Target is a character <= 0xFFFF */
					/* UTF-16 surrogate values are illegal in UTF-32; 0xffff or 0xfffe are both reserved values */
					if( ch >= (::booldog::uint32)0xD800 && ch <= (::booldog::uint32)0xDFFF )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					else
					{
						if( target >= target_end )
						{
							target++;
							goto goto_conversion_result_targetExhausted;
						}
						*target++ = (::booldog::uint16)ch; /* normal case */
					}
				}
				else if( ch > (::booldog::uint32)0x0010FFFF )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				else 
				{
					/* target is a character in range 0xFFFF - 0x10FFFF. */
					if( target + 1 >= target_end )
					{
						target += 2;
						goto goto_conversion_result_targetExhausted;
					}
					ch -= 0x0010000UL;
					*target++ = (::booldog::uint16)( ( ch >> 10 ) + (::booldog::uint32)0xD800 );
					*target++ = (::booldog::uint16)( ( ch & 0x3FFUL ) + (::booldog::uint32)0xDC00 );
				}
			}
			if( target )
				utf16_bytes = (char*)target - utf16_ptr;
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:
			if( target )
				utf16_bytes = (char*)target - utf16_ptr;
			while( source < source_end )
			{
				ch = *source++;
				if( ch <= (::booldog::uint32)0x0000FFFF )
				{
					if( ch >= (::booldog::uint32)0xD800 && ch <= (::booldog::uint32)0xDFFF )
						return ::booldog::enums::string::conversion_result_sourceIllegal;
					else
						utf16_bytes += 2;
				}
				else if( ch > (::booldog::uint32)0x0010FFFF )
					return ::booldog::enums::string::conversion_result_sourceIllegal;
				else
					utf16_bytes += 4;
			}
			return ::booldog::enums::string::conversion_result_targetExhausted;
		};
		booinline ::booldog::enums::string::conversion_result to_lower( const char* src_ptr , size_t src_ptr_count , char* dst_ptr , size_t dst_ptr_count , size_t& dst_bytes )
		{
			dst_bytes = 0;
			const ::booldog::uint32* source = (::booldog::uint32*)src_ptr , * source_end = (::booldog::uint32*)( src_ptr + src_ptr_count );
			::booldog::uint32* target = (::booldog::uint32*)dst_ptr , * target_end = (::booldog::uint32*)( dst_ptr + dst_ptr_count );
			::booldog::uint32 utfchar = 0;
			if( target == 0 )
				goto goto_conversion_result_targetExhausted;					
			while( source < source_end )
			{
				if( target >= target_end )
					goto goto_conversion_result_targetExhausted;
				utfchar = *source++;
				if( utfchar == 0 )
				{
					*target++ = 0;
					break;
				}
				else if( utfchar > 0x40 && utfchar < 0x5b )
				{
					utfchar += 0x20;
				}
				else if( utfchar > 0xbf && utfchar < 0xdf )
				{
					switch( utfchar )
					{
					case 0xd7:
						break;
					default:
						utfchar += 0x20;
					}
				}
				else if( utfchar > 0xff && utfchar < 0x0137 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
					{
						switch( utfchar )
						{
						case 0x012f:
						case 0x0130:
						case 0x0131:
							break;
						default:
							utfchar++;
						}
					}
				}
				else if( utfchar > 0x0138 && utfchar < 0x0148 )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar++;
				}
				else if( utfchar > 0x0149 && utfchar < 0x0177 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar++;
				}
				else if( utfchar > 0x0178 && utfchar < 0x017e )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar++;
				}
				else if( utfchar > 0x0181 && utfchar < 0x0185 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar++;
				}
				else if( utfchar > 0x0188 && utfchar < 0x018b )
				{
					utfchar += 0xcd;
				}
				else if( utfchar > 0x019f && utfchar < 0x01a5 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar++;
				}
				else if( utfchar > 0x01b0 && utfchar < 0x01b3 )
				{
					utfchar += 0xd9;
				}
				else if( utfchar > 0x01b2 && utfchar < 0x01b6 )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar++;
				}
				else if( utfchar > 0x01cc && utfchar < 0x01dc )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar++;
				}
				else if( utfchar > 0x01dd && utfchar < 0x01f5 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
					{
						switch( utfchar )
						{
						case 0x01ef:
						case 0x01f0:
						case 0x01f2:
						case 0x01f3:
							break;
						case 0x01f1:
							{
								utfchar = 0x01f3;
								break;
							}
						default:
							utfchar++;
						}
					}
				}
				else if( utfchar > 0x01f7 && utfchar < 0x0233 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
					{
						switch( utfchar )
						{
						case 0x021f:
						case 0x0221:
							break;
						case 0x0220:
							{
								utfchar = 0x019e;
								break;
							}
						default:
							utfchar++;
						}
					}
				}
				else if( utfchar > 0x0245 && utfchar < 0x024f )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar++;
				}
				else if( utfchar > 0x036f && utfchar < 0x0377 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
					{
						switch( utfchar )
						{
						case 0x0373:
						case 0x0374:
						case 0x0375:
							break;
						default:
							utfchar++;
						}
					}
				}
				else if( utfchar > 0x0387 && utfchar < 0x038b )
				{
					utfchar += 0x25;
				}
				else if( utfchar > 0x038d && utfchar < 0x0390 )
				{
					utfchar += 0x3f;
				}
				else if( utfchar > 0x0390 && utfchar < 0x03ac )
				{
					switch( utfchar )
					{
					case 0x03a2:
						break;
					default:
						utfchar += 0x20;
					}
				}
				else if( utfchar > 0x03d7 && utfchar < 0x03ef )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar++;
				}
				else if( utfchar > 0x03fc && utfchar < 0x0400 )
				{
					utfchar -= 0x82;
				}
				else if( utfchar > 0x03ff && utfchar < 0x0410 )
				{
					utfchar += 0x50;
				}
				else if( utfchar > 0x040f && utfchar < 0x0430 )
				{
					utfchar += 0x20;
				}
				else if( utfchar > 0x045f && utfchar < 0x0481 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar++;
				}
				else if( utfchar > 0x0489 && utfchar < 0x04bf )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar++;
				}
				else if( utfchar > 0x04c0 && utfchar < 0x04ce )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar++;
				}
				else if( utfchar > 0x04cf && utfchar < 0x0523 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar++;
				}
				else if( utfchar > 0x0530 && utfchar < 0x0557 )
				{
					utfchar += 0x30;
				}
				else if( utfchar > 0x109f && utfchar < 0x10c6 )
				{
					utfchar += 0x1c60;
				}
				else if( utfchar > 0x1dff && utfchar < 0x1e95 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar++;
				}
				else if( utfchar > 0x1e9f && utfchar < 0x1eff )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar++;
				}
				else if( utfchar > 0x1f07 && utfchar < 0x1f10 )
				{
					utfchar -= 0x08;
				}
				else if( utfchar > 0x1f17 && utfchar < 0x1f1e )
				{
					utfchar -= 0x08;
				}
				else if( utfchar > 0x1f27 && utfchar < 0x1f30 )
				{
					utfchar -= 0x08;
				}
				else if( utfchar > 0x1f37 && utfchar < 0x1f40 )
				{
					utfchar -= 0x08;
				}
				else if( utfchar > 0x1f47 && utfchar < 0x1f4e )
				{
					utfchar -= 0x08;
				}
				else if( utfchar > 0x1f67 && utfchar < 0x1f70 )
				{
					utfchar -= 0x08;
				}
				else if( utfchar > 0x1f87 && utfchar < 0x1f90 )
				{
					utfchar -= 0x08;
				}
				else if( utfchar > 0x1f97 && utfchar < 0x1fa0 )
				{
					utfchar -= 0x08;
				}
				else if( utfchar > 0x1fa7 && utfchar < 0x1fb0 )
				{
					utfchar -= 0x08;
				}
				else if( utfchar > 0x1fb7 && utfchar < 0x1fba )
				{
					utfchar -= 0x08;
				}
				else if( utfchar > 0x1fb9 && utfchar < 0x1fbc )
				{
					utfchar -= 0x4a;
				}
				else if( utfchar > 0x1fc7 && utfchar < 0x1fcc )
				{
					utfchar -= 0x56;
				}
				else if( utfchar > 0x1fd7 && utfchar < 0x1fda )
				{
					utfchar -= 0x08;
				}
				else if( utfchar > 0x1fd9 && utfchar < 0x1fdc )
				{
					utfchar -= 0x64;
				}
				else if( utfchar > 0x1fe7 && utfchar < 0x1fea )
				{
					utfchar -= 0x08;
				}
				else if( utfchar > 0x1fe9 && utfchar < 0x1fec )
				{
					utfchar -= 0x70;
				}
				else if( utfchar > 0x1ff7 && utfchar < 0x1ffa )
				{
					utfchar -= 0x80;
				}
				else if( utfchar > 0x1ff9 && utfchar < 0x1ffc )
				{
					utfchar -= 0x7e;
				}
				else if( utfchar > 0x215f && utfchar < 0x2170 )
				{
					utfchar += 0x10;
				}
				else if( utfchar > 0x24b5 && utfchar < 0x24d0 )
				{
					utfchar += 0x1a;
				}
				else if( utfchar > 0x2bff && utfchar < 0x2c2f )
				{
					utfchar += 0x30;
				}
				else if( utfchar > 0x2c66 && utfchar < 0x2c6c )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar++;
				}
				else if( utfchar > 0x2c7f && utfchar < 0x2ce3 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar++;
				}
				else if( utfchar > 0xa63f && utfchar < 0xa66d )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
					{
						switch( utfchar )
						{
						case 0xa65f:
						case 0xa660:
						case 0xa661:
							break;
						default:
							utfchar++;
						}
					}
				}
				else if( utfchar > 0xa67f && utfchar < 0xa697 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar++;
				}
				else if( utfchar > 0xa721 && utfchar < 0xa76f )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
					{
						switch( utfchar )
						{
						case 0xa72f:
						case 0xa730:
						case 0xa731:
							break;
						default:
							utfchar++;
						}
					}
				}
				else if( utfchar > 0xa778 && utfchar < 0xa77c )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar++;
				}
				else if( utfchar > 0xa77d && utfchar < 0xa787 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar++;
				}
				else if( utfchar > 0xff20 && utfchar < 0xff3b )
				{
					utfchar += 0x20;
				}
				else
				{
					switch( utfchar )
					{
					case 0x0178:
						utfchar = 0xff;
						break;
					case 0x0181:
						utfchar = 0x0253;
						break;
					case 0x0186:
						utfchar = 0x0254;
						break;
					case 0x0187:
						utfchar = 0x0188;
						break;
					case 0x018b:
						utfchar = 0x018c;
						break;
					case 0x018e:
						utfchar = 0x01dd;
						break;
					case 0x018f:
						utfchar = 0x0259;
						break;
					case 0x0190:
						utfchar = 0x025b;
						break;
					case 0x0191:
						utfchar = 0x0192;
						break;
					case 0x0193:
						utfchar = 0x0260;
						break;
					case 0x0194:
						utfchar = 0x0263;
						break;
					case 0x0196:
						utfchar = 0x0269;
						break;
					case 0x0197:
						utfchar = 0x0268;
						break;
					case 0x0198:
						utfchar = 0x0199;
						break;
					case 0x019c:
						utfchar = 0x026f;
						break;
					case 0x019d:
						utfchar = 0x0272;
						break;
					case 0x019f:
						utfchar = 0x0275;
						break;
					case 0x01a6:
						utfchar = 0x0280;
						break;
					case 0x01a7:
						utfchar = 0x01a8;
						break;
					case 0x01a9:
						utfchar = 0x0283;
						break;
					case 0x01ac:
						utfchar = 0x01ad;
						break;
					case 0x01ae:
						utfchar = 0x0288;
						break;
					case 0x01af:
						utfchar = 0x01b0;
						break;
					case 0x01b7:
						utfchar = 0x0292;
						break;
					case 0x01b8:
						utfchar = 0x01b9;
						break;
					case 0x01bc:
						utfchar = 0x01bd;
						break;
					case 0x01c4:
						utfchar = 0x01c6;
						break;
					case 0x01c7:
						utfchar = 0x01c9;
						break;
					case 0x01ca:
						utfchar = 0x01cc;
						break;
					case 0x01f1:
						utfchar = 0x01f3;
						break;
					case 0x01f6:
						utfchar = 0x0195;
						break;
					case 0x01f7:
						utfchar = 0x01bf;
						break;
					case 0x0220:
						utfchar = 0x019e;
						break;
					case 0x023a:
						utfchar = 0x2c65;
						break;
					case 0x023b:
						utfchar = 0x023c;
						break;
					case 0x023d:
						utfchar = 0x019a;
						break;
					case 0x023e:
						utfchar = 0x2c66;
						break;
					case 0x0241:
						utfchar = 0x0242;
						break;
					case 0x0243:
						utfchar = 0x0180;
						break;
					case 0x0244:
						utfchar = 0x0289;
						break;
					case 0x0245:
						utfchar = 0x028c;
						break;
					case 0x0386:
						utfchar = 0x03ac;
						break;
					case 0x038c:
						utfchar = 0x03cc;
						break;
					case 0x03cf:
						utfchar = 0x03d7;
						break;
					case 0x03f7:
						utfchar = 0x03f8;
						break;
					case 0x03f9:
						utfchar = 0x03f2;
						break;
					case 0x03fa:
						utfchar = 0x03fb;
						break;
					case 0x04c0:
						utfchar = 0x04cf;
						break;
					case 0x1f59:
						utfchar = 0x1f51;
						break;
					case 0x1f5b:
						utfchar = 0x1f53;
						break;
					case 0x1f5d:
						utfchar = 0x1f55;
						break;
					case 0x1f5f:
						utfchar = 0x1f57;
						break;
					case 0x1fbc:
						utfchar = 0x1fb3;
						break;
					case 0x1fcc:
						utfchar = 0x1fc3;
						break;
					case 0x1fec:
						utfchar = 0x1fe5;
						break;
					case 0x1ffc:
						utfchar = 0x1ff3;
						break;
					case 0x2132:
						utfchar = 0x214e;
						break;
					case 0x2183:
						utfchar = 0x2184;
						break;
					case 0x2c60:
						utfchar = 0x2c61;
						break;
					case 0x2c62:
						utfchar = 0x026b;
						break;
					case 0x2c63:
						utfchar = 0x1d7d;
						break;
					case 0x2c64:
						utfchar = 0x027d;
						break;
					case 0x2c6d:
						utfchar = 0x0251;
						break;
					case 0x2c6e:
						utfchar = 0x0271;
						break;
					case 0x2c6f:
						utfchar = 0x0250;
						break;
					case 0x2c72:
						utfchar = 0x2c73;
						break;
					case 0x2c75:
						utfchar = 0x2c76;
						break;
					case 0xa77d:
						utfchar = 0x1d79;
						break;
					case 0xa78b:
						utfchar = 0xa78c;
						break;
					}
				}
				*target++ = utfchar;
			}
			if( target )
				dst_bytes = (char*)target - dst_ptr;
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:					
			while( source < source_end )
			{
				target++;
				if( *source++ == 0 )		
					break;
			}
			if( target )
				dst_bytes = (char*)target - dst_ptr;
			return ::booldog::enums::string::conversion_result_targetExhausted;
		};
		booinline ::booldog::enums::string::conversion_result to_upper( const char* src_ptr , size_t src_ptr_count , char* dst_ptr , size_t dst_ptr_count , size_t& dst_bytes )
		{
			dst_bytes = 0;
			const ::booldog::uint32* source = (::booldog::uint32*)src_ptr , * source_end = (::booldog::uint32*)( src_ptr + src_ptr_count );
			::booldog::uint32* target = (::booldog::uint32*)dst_ptr , * target_end = (::booldog::uint32*)( dst_ptr + dst_ptr_count );
			::booldog::uint32 utfchar = 0;
			if( target == 0 )
				goto goto_conversion_result_targetExhausted;
			while( source < source_end )
			{
				if( target >= target_end )
					goto goto_conversion_result_targetExhausted;
				utfchar = *source++;
				if( utfchar == 0 )
				{
					*target++ = 0;
					break;
				}
				else if( utfchar > 0x60 && utfchar < 0x7b )
				{
					utfchar -= 0x20;
				}
				else if( utfchar > 0xdf && utfchar < 0xff )
				{
					switch( utfchar )
					{
					case 0xf7:
						break;
					default:
						utfchar -= 0x20;
					}
				}
				else if( utfchar > 0x0100 && utfchar < 0x0138 )
				{
					if( ::booldog::utils::odd( utfchar ) )
					{
						switch( utfchar )
						{
						case 0x0130:
						case 0x0131:
						case 0x0132:
							break;
						default:
							utfchar--;
						}
					}
				}
				else if( utfchar > 0x0139 && utfchar < 0x0149 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar--;
				}
				else if( utfchar > 0x014a && utfchar < 0x0178 )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar--;
				}
				else if( utfchar > 0x0179 && utfchar < 0x017f )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar--;
				}
				else if( utfchar > 0x0182 && utfchar < 0x0186 )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar--;
				}
				else if( utfchar > 0x01a0 && utfchar < 0x01ae )
				{
					if( ::booldog::utils::odd( utfchar ) )
					{
						switch( utfchar )
						{
						case 0x01a6:
						case 0x01a7:
						case 0x01a9:
						case 0x01aa:
						case 0x01ab:
						case 0x01ac:
							break;
						case 0x01a8:
							{
								utfchar = 0x01a7;
								break;
							}
						default:
							utfchar--;
						}
					}
				}
				else if( utfchar > 0x01b3 && utfchar < 0x01b7 )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar--;
				}
				else if( utfchar > 0x01cd && utfchar < 0x01dd )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar--;
				}
				else if( utfchar > 0x01de && utfchar < 0x0234 )
				{
					if( ::booldog::utils::odd( utfchar ) )
					{
						switch( utfchar )
						{
						case 0x01f0:
						case 0x01f1:
						case 0x01f2:
						case 0x01f4:
						case 0x01f6:
						case 0x01f7:
						case 0x01f8:
						case 0x0220:
						case 0x0221:
						case 0x0222:
							break;
						case 0x01f3:
							{
								utfchar = 0x01f1;
								break;
							}
						default:
							utfchar--;
						}
					}
				}
				else if( utfchar > 0x0246 && utfchar < 0x0250 )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar--;
				}
				else if( utfchar > 0x0255 && utfchar < 0x0258 )
				{
					utfchar -= 0xcd;
				}
				else if( utfchar > 0x0289 && utfchar < 0x028c )
				{
					utfchar -= 0xd9;
				}
				else if( utfchar > 0x0370 && utfchar < 0x0378 )
				{
					if( ::booldog::utils::odd( utfchar ) )
					{
						switch( utfchar )
						{
						case 0x0374:
						case 0x0375:
						case 0x0376:
							break;
						default:
							utfchar--;
						}
					}
				}
				else if( utfchar > 0x037a && utfchar < 0x037e )
				{
					utfchar += 0x82;
				}
				else if( utfchar > 0x03ac && utfchar < 0x03b0 )
				{
					utfchar -= 0x25;
				}
				else if( utfchar > 0x03b0 && utfchar < 0x03cc )
				{
					switch( utfchar )
					{
					case 0x03c2:
						break;
					default:
						utfchar -= 0x20;
					}
				}
				else if( utfchar > 0x03cc && utfchar < 0x03cf )
				{
					utfchar -= 0x3f;
				}
				else if( utfchar > 0x03d8 && utfchar < 0x03f0 )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar--;
				}
				else if( utfchar > 0x042f && utfchar < 0x0450 )
				{
					utfchar -= 0x20;
				}
				else if( utfchar > 0x044f && utfchar < 0x0460 )
				{
					utfchar -= 0x50;
				}
				else if( utfchar > 0x0460 && utfchar < 0x0482 )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar--;
				}
				else if( utfchar > 0x048a && utfchar < 0x04c0 )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar--;
				}
				else if( utfchar > 0x04c1 && utfchar < 0x04cf )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar--;
				}
				else if( utfchar > 0x04d0 && utfchar < 0x0524 )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar--;
				}
				else if( utfchar > 0x0560 && utfchar < 0x0587 )
				{
					utfchar -= 0x30;
				}
				else if( utfchar > 0x1e00 && utfchar < 0x1e96 )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar--;
				}
				else if( utfchar > 0x1ea0 && utfchar < 0x1f00 )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar--;
				}
				else if( utfchar > 0x1eff && utfchar < 0x1f08 )
				{
					utfchar += 0x08;
				}
				else if( utfchar > 0x1f0f && utfchar < 0x1f16 )
				{
					utfchar += 0x08;
				}
				else if( utfchar > 0x1f1f && utfchar < 0x1f28 )
				{
					utfchar += 0x08;
				}
				else if( utfchar > 0x1f2f && utfchar < 0x1f38 )
				{
					utfchar += 0x08;
				}
				else if( utfchar > 0x1f3f && utfchar < 0x1f46 )
				{
					utfchar += 0x08;
				}
				else if( utfchar > 0x1f5f && utfchar < 0x1f68 )
				{
					utfchar += 0x08;
				}
				else if( utfchar > 0x1f6f && utfchar < 0x1f72 )
				{
					utfchar += 0x4a;
				}
				else if( utfchar > 0x1f71 && utfchar < 0x1f76 )
				{
					utfchar += 0x56;
				}
				else if( utfchar > 0x1f75 && utfchar < 0x1f78 )
				{
					utfchar += 0x64;
				}
				else if( utfchar > 0x1f77 && utfchar < 0x1f7a )
				{
					utfchar += 0x80;
				}
				else if( utfchar > 0x1f79 && utfchar < 0x1f7c )
				{
					utfchar += 0x70;
				}
				else if( utfchar > 0x1f7b && utfchar < 0x1f7e )
				{
					utfchar += 0x7e;
				}
				else if( utfchar > 0x1f7f && utfchar < 0x1f88 )
				{
					utfchar += 0x08;
				}
				else if( utfchar > 0x1f8f && utfchar < 0x1f98 )
				{
					utfchar += 0x08;
				}
				else if( utfchar > 0x1f9f && utfchar < 0x1fa8 )
				{
					utfchar += 0x08;
				}
				else if( utfchar > 0x1faf && utfchar < 0x1fb2 )
				{
					utfchar += 0x08;
				}
				else if( utfchar > 0x1fcf && utfchar < 0x1fd2 )
				{
					utfchar += 0x08;
				}
				else if( utfchar > 0x1fdf && utfchar < 0x1fe2 )
				{
					utfchar += 0x08;
				}
				else if( utfchar > 0x216f && utfchar < 0x2180 )
				{
					utfchar -= 0x10;
				}
				else if( utfchar > 0x24cf && utfchar < 0x24ea )
				{
					utfchar -= 0x1a;
				}
				else if( utfchar > 0x2c2f && utfchar < 0x2c5f )
				{
					utfchar -= 0x30;
				}
				else if( utfchar > 0x2c67 && utfchar < 0x2c6d )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar--;
				}
				else if( utfchar > 0x2c80 && utfchar < 0x2ce4 )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar--;
				}
				else if( utfchar > 0x2cff && utfchar < 0x2d26 )
				{
					utfchar -= 0x1c60;
				}
				else if( utfchar > 0xa640 && utfchar < 0xa66e )
				{
					if( ::booldog::utils::odd( utfchar ) )
					{
						switch( utfchar )
						{
						case 0xa660:
						case 0xa661:
						case 0xa662:
							break;
						default:
							utfchar--;
						}
					}
				}
				else if( utfchar > 0xa680 && utfchar < 0xa698 )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar--;
				}
				else if( utfchar > 0xa722 && utfchar < 0xa770 )
				{
					if( ::booldog::utils::odd( utfchar ) )
					{
						switch( utfchar )
						{
						case 0xa730:
						case 0xa731:
						case 0xa732:
							break;
						default:
							utfchar--;
						}
					}
				}
				else if( utfchar > 0xa779 && utfchar < 0xa77d )
				{
					if( ::booldog::utils::odd( utfchar ) == false )
						utfchar--;
				}
				else if( utfchar > 0xa77e && utfchar < 0xa788 )
				{
					if( ::booldog::utils::odd( utfchar ) )
						utfchar--;
				}
				else if( utfchar > 0xff40 && utfchar < 0xff5b )
				{
					utfchar -= 0x20;
				}
				else
				{
					switch( utfchar )
					{
					case 0xff:
						utfchar = 0x0178;
						break;
					case 0x0180:
						utfchar = 0x0243;
						break;
					case 0x0188:
						utfchar = 0x0187;
						break;
					case 0x018c:
						utfchar = 0x018b;
						break;
					case 0x0192:
						utfchar = 0x0191;
						break;
					case 0x0195:
						utfchar = 0x01f6;
						break;
					case 0x0199:
						utfchar = 0x0198;
						break;
					case 0x019a:
						utfchar = 0x023d;
						break;
					case 0x019e:
						utfchar = 0x0220;
						break;
					case 0x01a8:
						utfchar = 0x01a7;
						break;
					case 0x01b0:
						utfchar = 0x01af;
						break;
					case 0x01b9:
						utfchar = 0x01b8;
						break;
					case 0x01bd:
						utfchar = 0x01bc;
						break;
					case 0x01bf:
						utfchar = 0x01f7;
						break;
					case 0x01c6:
						utfchar = 0x01c4;
						break;
					case 0x01c9:
						utfchar = 0x01c7;
						break;
					case 0x01cc:
						utfchar = 0x01ca;
						break;
					case 0x01dd:
						utfchar = 0x018e;
						break;
					case 0x01f3:
						utfchar = 0x01f1;
						break;
					case 0x023c:
						utfchar = 0x023b;
						break;
					case 0x0242:
						utfchar = 0x0241;
						break;
					case 0x0250:
						utfchar = 0x2c6f;
						break;
					case 0x0251:
						utfchar = 0x2c6d;
						break;
					case 0x0253:
						utfchar = 0x0181;
						break;
					case 0x0254:
						utfchar = 0x0186;
						break;
					case 0x0259:
						utfchar = 0x018f;
						break;
					case 0x025b:
						utfchar = 0x0190;
						break;
					case 0x0260:
						utfchar = 0x0193;
						break;
					case 0x0263:
						utfchar = 0x0194;
						break;
					case 0x0268:
						utfchar = 0x0197;
						break;
					case 0x0269:
						utfchar = 0x0196;
						break;
					case 0x026b:
						utfchar = 0x2c62;
						break;
					case 0x026f:
						utfchar = 0x019c;
						break;
					case 0x0271:
						utfchar = 0x2c6e;
						break;
					case 0x0272:
						utfchar = 0x019d;
						break;
					case 0x0275:
						utfchar = 0x019f;
						break;
					case 0x027d:
						utfchar = 0x2c64;
						break;
					case 0x0280:
						utfchar = 0x01a6;
						break;
					case 0x0283:
						utfchar = 0x01a9;
						break;
					case 0x0288:
						utfchar = 0x01ae;
						break;
					case 0x0289:
						utfchar = 0x0244;
						break;
					case 0x028c:
						utfchar = 0x0245;
						break;
					case 0x0292:
						utfchar = 0x01b7;
						break;
					case 0x03ac:
						utfchar = 0x0386;
						break;
					case 0x03cc:
						utfchar = 0x038c;
						break;
					case 0x03d7:
						utfchar = 0x03cf;
						break;
					case 0x03f2:
						utfchar = 0x03f9;
						break;
					case 0x03f8:
						utfchar = 0x03f7;
						break;
					case 0x03fb:
						utfchar = 0x03fa;
						break;
					case 0x04cf:
						utfchar = 0x04c0;
						break;
					case 0x1d79:
						utfchar = 0xa77d;
						break;
					case 0x1d7d:
						utfchar = 0x2c63;
						break;
					case 0x1f51:
						utfchar = 0x1f59;
						break;
					case 0x1f53:
						utfchar = 0x1f5b;
						break;
					case 0x1f55:
						utfchar = 0x1f5d;
						break;
					case 0x1f57:
						utfchar = 0x1f5f;
						break;
					case 0x1fb3:
						utfchar = 0x1fbc;
						break;
					case 0x1fc3:
						utfchar = 0x1fcc;
						break;
					case 0x1fe5:
						utfchar = 0x1fec;
						break;
					case 0x1ff3:
						utfchar = 0x1ffc;
						break;
					case 0x214e:
						utfchar = 0x2132;
						break;
					case 0x2184:
						utfchar = 0x2183;
						break;
					case 0x2c61:
						utfchar = 0x2c60;
						break;
					case 0x2c65:
						utfchar = 0x023a;
						break;
					case 0x2c66:
						utfchar = 0x023e;
						break;
					case 0x2c73:
						utfchar = 0x2c72;
						break;
					case 0x2c76:
						utfchar = 0x2c75;
						break;
					case 0xa78c:
						utfchar = 0xa78b;
						break;
					}
				}
				*target++ = utfchar;
			}
			if( target )
				dst_bytes = (char*)target - dst_ptr;
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:					
			while( source < source_end )
			{
				target++;
				if( *source++ == 0 )		
					break;
			}
			if( target )
				dst_bytes = (char*)target - dst_ptr;
			return ::booldog::enums::string::conversion_result_targetExhausted;
		};
		booinline ::booldog::enums::string::conversion_result to_cp1251( const char* utf32_ptr , size_t utf32_ptr_count , char* cp1251_ptr , size_t cp1251_ptr_count , size_t& cp1251_bytes )
		{
			cp1251_bytes = 0;
			const ::booldog::uint32* source = (::booldog::uint32*)utf32_ptr , * source_end = (::booldog::uint32*)( utf32_ptr + utf32_ptr_count );
			::booldog::uint8* target = (::booldog::uint8*)cp1251_ptr , * target_end = (::booldog::uint8*)( cp1251_ptr + cp1251_ptr_count );
			while( source < source_end )
			{
				if( target >= target_end )
					goto goto_conversion_result_targetExhausted;
				if( *source < 128 )
					*target++ = (::booldog::byte)*source++;
				else
				{
					if( *source > 151 && *source < 188 )
					{
						*target = ::booldog::consts::utf32::_utf32_to_cp1251_page_from_152_to_187[ *source++ - 152 ];
						if( *target++ == 0 )
							return ::booldog::enums::string::conversion_result_sourceIllegal;
					}
					else if( *source > 1024 && *source < 1170 )
					{
						*target = ::booldog::consts::utf32::_utf32_to_cp1251_page_from_1025_to_1169[ *source++ - 1025 ];
						if( *target++ == 0 )
							return ::booldog::enums::string::conversion_result_sourceIllegal;
					}
					else if( *source > 8210 && *source < 8483 )
					{
						*target = ::booldog::consts::utf32::_utf32_to_cp1251_page_from_8211_to_8482[ *source++ - 8211 ];
						if( *target++ == 0 )
							return ::booldog::enums::string::conversion_result_sourceIllegal;
					}
					else
						return ::booldog::enums::string::conversion_result_sourceIllegal;
				}
			}
			if( target )
				cp1251_bytes = (char*)target - cp1251_ptr;
			return ::booldog::enums::string::conversion_result_OK;
goto_conversion_result_targetExhausted:
			if( target )
				cp1251_bytes = (char*)target - cp1251_ptr;
			while( source < source_end )
			{
				if( *source < 128 )
				{
					source++;
					cp1251_bytes++;
				}
				else
				{
					if( *source > 151 && *source < 188 )
					{
						if( ::booldog::consts::utf32::_utf32_to_cp1251_page_from_152_to_187[ *source++ - 152 ] == 0 )
							return ::booldog::enums::string::conversion_result_sourceIllegal;
						else
							cp1251_bytes++;
					}
					else if( *source > 1024 && *source < 1170 )
					{
						if( ::booldog::consts::utf32::_utf32_to_cp1251_page_from_1025_to_1169[ *source++ - 1025 ] == 0 )
							return ::booldog::enums::string::conversion_result_sourceIllegal;
						else
							cp1251_bytes++;
					}
					else if( *source > 8210 && *source < 8483 )
					{
						if( ::booldog::consts::utf32::_utf32_to_cp1251_page_from_8211_to_8482[ *source++ - 8211 ] == 0 )
							return ::booldog::enums::string::conversion_result_sourceIllegal;
						else
							cp1251_bytes++;
					}
					else
						return ::booldog::enums::string::conversion_result_sourceIllegal;
				}
			}
			return ::booldog::enums::string::conversion_result_targetExhausted;
		};
	};
};
#endif