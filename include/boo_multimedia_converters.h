#ifndef BOO_MULTIMEDIA_CONVERTERS_H
#define BOO_MULTIMEDIA_CONVERTERS_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_result.h)
#include BOOLDOG_HEADER(boo_error.h)
#define booclip(x) x > 0 ? x < 255 ? x : 255 : 0
namespace booldog
{
	namespace converters
	{
		namespace multimedia
		{
			namespace image
			{
                            namespace I420
                            {
                                booinline bool to_rgb32(::booldog::result_buffer* pres, booldog::allocator* allocator
                                        , const ::booldog::byte* src, ::booldog::uint32 width, ::booldog::uint32 height
                                        , ::booldog::byte alpha, const ::booldog::debug::info& debuginfo = debuginfo_macros)
                                {
                                        ::booldog::result_buffer locres( allocator );
                                        BOOINIT_RESULT( ::booldog::result_buffer );

                                        ::booldog::uint32 y_count = width * height;
                                        ::booldog::uint32 uv_count = y_count / 4;
                                        res->bufdatasize = y_count * 4;
                                        ::booldog::int32 index1 = 0 , r_coef = 0 , g_coef = 0 , b_coef = 0 , D = 0 , C = 0;//, temp = 0;
                                        ::booldog::byte y = 0 , v = 0 , u = 0;
                                        if(res->bufdatasize > res->bufsize)
                                        {
                                                res->bufsize = res->bufdatasize;
                                                res->buf = res->allocator->realloc_array< unsigned char >(res->buf, res->bufsize, debuginfo);
                                                if(res->buf == 0)
                                                {
                                                        res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
                                                        goto goto_return;
                                                }
                                        }
                                        for(::booldog::uint32 index0 = 0;index0 < uv_count;++index0)
                                        {
                                            y = src[index1];
                                            v = src[y_count + index0];
                                            u = src[y_count + uv_count + index0];

                                            C = 298 * (y - 16);
                                            D = u - 128;
                                            r_coef = 409 * (v - 128) + 128;
                                            g_coef = - 100 * D - 208 * (v - 128) + 128;
                                            b_coef = 516 * D + 128;
                                            res->buf[(index1 + 1) * 4] = (::booldog::uint8)(booclip((C + r_coef) >> 8));
                                            res->buf[(index1 + 1) * 4 + 1] = (::booldog::uint8)(booclip((C + g_coef) >> 8));
                                            res->buf[(index1 + 1) * 4 + 2] = (::booldog::uint8)(booclip((C + b_coef) >> 8));
                                            res->buf[(index1 + 1) * 4 + 3] = alpha;
                                            y = src[index1 + 1];
                                            C = 298 * (y - 16);
                                            res->buf[index1 * 4 ] = (::booldog::uint8)(booclip((C + r_coef) >> 8));
                                            res->buf[index1 * 4 + 1 ] = (::booldog::uint8)(booclip((C + g_coef) >> 8));
                                            res->buf[index1 * 4 + 2 ] = (::booldog::uint8)(booclip((C + b_coef) >> 8));
                                            res->buf[index1 * 4 + 3 ] = alpha;
                                            y = src[index1 + width];
                                            C = 298 * ( y - 16 );
                                            res->buf[(width + index1 + 1) * 4] = (::booldog::uint8)(booclip((C + r_coef) >> 8));
                                            res->buf[(width + index1 + 1) * 4 + 1] = (::booldog::uint8)(booclip((C + g_coef) >> 8));
                                            res->buf[(width + index1 + 1) * 4 + 2] = (::booldog::uint8)(booclip((C + b_coef) >> 8));
                                            res->buf[(width + index1 + 1) * 4 + 3] = alpha;
                                            y = src[index1 + width + 1];
                                            C = 298 * ( y - 16 );
                                            res->buf[(width + index1) * 4] = (::booldog::uint8)(booclip((C + r_coef) >> 8));
                                            res->buf[(width + index1) * 4 + 1] = (::booldog::uint8)(booclip((C + g_coef) >> 8));
                                            res->buf[(width + index1) * 4 + 2] = (::booldog::uint8)(booclip((C + b_coef) >> 8));
                                            res->buf[(width + index1) * 4 + 3] = alpha;
                                            index1 += 2;
                                            if(index1 != 0 && index1 % width == 0)
                                                index1 += width;
                                        }
        goto_return:
                                        return res->succeeded();
                                }
                            }
				namespace i422
				{
					booinline void to_i420(::booldog::byte* src, ::booldog::uint32 width, ::booldog::uint32 height)
					{
						::booldog::uint32 y_size = width * height;
						::booldog::uint32 uv_size = y_size / 2;
						::booldog::uint32 i420linesize = width / 2;
						::booldog::byte* ptr = &src[y_size];
						::booldog::byte* end = ptr + uv_size, * src_ptr = ptr + width;
						ptr += i420linesize;
						while(src_ptr < end)
						{
							::memcpy(ptr, src_ptr, i420linesize);
							ptr += i420linesize;
							src_ptr += width;
						}
						end = src_ptr + uv_size;						
						while(src_ptr < end)
						{
							::memcpy(ptr, src_ptr, i420linesize);
							ptr += i420linesize;
							src_ptr += width;
						}
					}                                        
				}
				namespace yuy2
				{
					booinline bool to_yv12(::booldog::result_buffer* pres, booldog::allocator* allocator
						, const ::booldog::byte* src, ::booldog::uint32 width, ::booldog::uint32 height
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_buffer locres( allocator );
						BOOINIT_RESULT( ::booldog::result_buffer );

						::booldog::uint32 y_count = width * height;
                                                //::booldog::uint32 y_width = width / 2;
                                                //::booldog::uint32 uv_width = width / 2;
                                                //::booldog::uint32 uv_count = width * height / 4;
						res->bufdatasize = y_count * 3 / 2;
						if(res->bufdatasize > res->bufsize)
						{
							res->bufsize = res->bufdatasize;
							res->buf = res->allocator->realloc_array< unsigned char >(res->buf, res->bufsize, debuginfo);
							if(res->buf == 0)
							{
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								goto goto_return;
							}
						}
						for(::booldog::uint32 i = 0;i != y_count; ++i)
							res->buf[i] = src[2 * i];

						
						//for(::booldog::uint32 i = 0;i != uv_count; ++i)
						//{
							//i / uv_width
							/// uv_width
							//res->buf[y_count + i] = src[2 * width * (2 * (i / uv_width)) + 4 * i + 3]
						//}
		goto_return:		
						return res->succeeded();
					};

/*byte YUY2Source[M * N * 2] = 
byte YV12Dest[M * N * 3/2];

for (unsigned int i = 0; i != M * N; ++i)
{
    YV12Dest[i] = YUY2Source[2 * i];
}

for (unsigned int j = 0; j != M * N / 4; ++j)
{
    YV12Dest[M * N + j]       = ( YUY2Source[N*(j / N/2    ) + 4 * j + 3]
                                + YUY2Source[N*(j / N/2 + 1) + 4 * j + 3] ) / 2;

    YV12Dest[M * N * 5/4 + j] = ( YUY2Source[N*(j / N/2    ) + 4 * j + 1]
                                + YUY2Source[N*(j / N/2 + 1) + 4 * j + 1] ) / 2;
}*/

					booinline bool to_rgb24(::booldog::result_buffer* pres, booldog::allocator* allocator
						, const ::booldog::byte* src, ::booldog::uint32 width, ::booldog::uint32 height
						, const ::booldog::debug::info& debuginfo = debuginfo_macros )
					{
						::booldog::result_buffer locres( allocator );
						BOOINIT_RESULT( ::booldog::result_buffer );

						::booldog::uint32 temp = width * height;
						res->bufdatasize = 3 * temp;
						::booldog::uint32 pixels_count = 2 * temp;
						::booldog::int32 index1 = 0, r_coef = 0, g_coef = 0, b_coef = 0, D = 0, C = 0;
						if(res->bufdatasize > res->bufsize)
						{
							res->bufsize = res->bufdatasize;
							res->buf = res->allocator->realloc_array< unsigned char >(res->buf, res->bufsize, debuginfo);
							if(res->buf == 0)
							{
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								goto goto_return;
							}
						}
						for(::booldog::uint32 index0 = 0;index0 < pixels_count;index0 += 4)
						{						
							C = 298 * (src[index0] - 16);//Y - 16					
							D = src[index0 + 1] - 128;				//U - 128
							r_coef = 409 * (src[index0 + 3] - 128) + 128;//409 * ( V - 128 ) + 128
							g_coef = -100 * D - 208 * (src[index0 + 3] - 128) + 128;//- 100 * D - 208 * ( V - 128 ) + 128
							b_coef = 516 * D + 128;
							res->buf[index1] = (::booldog::byte)(booclip((C + b_coef) >> 8));
							res->buf[++index1] = (::booldog::byte)(booclip((C + g_coef) >> 8));
							res->buf[++index1] = (::booldog::byte)(booclip((C + r_coef) >> 8));
												
							C = 298 * (src[index0 + 2] - 16);				
							res->buf[++index1] = (::booldog::byte)(booclip((C + b_coef) >> 8));
							res->buf[++index1] = (::booldog::byte)(booclip((C + g_coef) >> 8));
							res->buf[++index1] = (::booldog::byte)(booclip((C + r_coef) >> 8));						
							++index1;
						}
		goto_return:
						return res->succeeded();
					};
					booinline bool to_rgb32(::booldog::result_buffer* pres, booldog::allocator* allocator
						, const ::booldog::byte* src, ::booldog::uint32 width, ::booldog::uint32 height
						, ::booldog::byte alpha, const ::booldog::debug::info& debuginfo = debuginfo_macros)
					{
						::booldog::result_buffer locres( allocator );
						BOOINIT_RESULT( ::booldog::result_buffer );

						::booldog::uint32 temp = width * height;
						res->bufdatasize = 4 * temp;
						::booldog::uint32 pixels_count = 2 * temp;
						::booldog::int32 index1 = 0, r_coef = 0, g_coef = 0, b_coef = 0, D = 0, C = 0;
						if(res->bufdatasize > res->bufsize)
						{
							res->bufsize = res->bufdatasize;
							res->buf = res->allocator->realloc_array< unsigned char >(res->buf, res->bufsize, debuginfo);
							if(res->buf == 0)
							{
								res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
								goto goto_return;
							}
						}
						for(::booldog::uint32 index0 = 0;index0 < pixels_count;index0 += 4)
						{						
							C = 298 * (src[index0] - 16);//Y - 16					
							D = src[index0 + 1] - 128;				//U - 128
							r_coef = 409 * (src[index0 + 3] - 128) + 128;//409 * ( V - 128 ) + 128
							g_coef = -100 * D - 208 * (src[index0 + 3] - 128) + 128;//- 100 * D - 208 * ( V - 128 ) + 128
							b_coef = 516 * D + 128;
							res->buf[index1] = (::booldog::byte)(booclip((C + b_coef) >> 8));
							res->buf[++index1] = (::booldog::byte)(booclip((C + g_coef) >> 8));
							res->buf[++index1] = (::booldog::byte)(booclip((C + r_coef) >> 8));
							res->buf[++index1] = alpha;
												
							C = 298 * (src[index0 + 2] - 16);				
							res->buf[++index1] = (::booldog::byte)(booclip((C + b_coef) >> 8));
							res->buf[++index1] = (::booldog::byte)(booclip((C + g_coef) >> 8));
							res->buf[++index1] = (::booldog::byte)(booclip((C + r_coef) >> 8));						
							res->buf[++index1] = alpha;
							++index1;
						}
		goto_return:
						return res->succeeded();
					};
				};
			};
		};
	};
};
#endif
