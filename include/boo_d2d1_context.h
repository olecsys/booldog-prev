#ifndef BOO_D2D1_CONTEXT_H
#define BOO_D2D1_CONTEXT_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_base_loader.h)
#include BOOLDOG_HEADER(boo_render_context.h)
#include BOOLDOG_HEADER(boo_math_utils.h)
#include BOOLDOG_HEADER(boo_thread.h)

#ifdef __WINDOWS__
#include <D3D11.h>
//#include <DXGI.h>
#include <DXGI1_2.h>
#define COM_NO_WINDOWS_H
//#include <D2d1.h>
#include <D2d1_1.h>
#include <D2d1_1helper.h>
namespace booldog
{
	namespace typedefs
	{
		typedef BOOL (WINAPI *GetClientRect)( HWND hWnd , LPRECT lpRect );
		typedef BOOL (WINAPI *GetWindowRect)( HWND hWnd , LPRECT lpRect );
		typedef HRESULT (WINAPI *D2D1CreateFactory)( D2D1_FACTORY_TYPE factoryType , REFIID riid 
			, const D2D1_FACTORY_OPTIONS* pFactoryOptions , void** ppIFactory );
		typedef HRESULT (WINAPI *D3D11CreateDevice)( IDXGIAdapter* pAdapter , D3D_DRIVER_TYPE DriverType , HMODULE Software , UINT Flags
			, const D3D_FEATURE_LEVEL* pFeatureLevels , UINT FeatureLevels , UINT SDKVersion , ID3D11Device** ppDevice 
			, D3D_FEATURE_LEVEL* pFeatureLevel , ID3D11DeviceContext** ppImmediateContext );
	};
};
namespace booldog
{
	namespace D2d1
	{
		class context;
		class factory
		{
			friend class ::booldog::D2d1::context;
			::booldog::base::module* _D2d1;
			::booldog::base::module* _D3D11;
			::booldog::base::loader* _loader;
			::booldog::allocator* _allocator;
			ID2D1Factory1* _D2d1factory1;
			ID2D1Factory* _D2d1factory;
			::booldog::typedefs::D3D11CreateDevice _D3D11CreateDevice;
			::booldog::array< IDXGIAdapter* > _dxgi_adapters;
		public:
			factory( ::booldog::result* pres , booldog::allocator* pallocator , ::booldog::base::loader* ploader
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				: _D2d1( 0 ) , _loader( ploader ) , _allocator( pallocator ) , _D2d1factory( 0 ) , _D2d1factory1( 0 )
					, _dxgi_adapters( pallocator ) , _D3D11CreateDevice( 0 )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
				::booldog::result_module resmod;

				if( _loader->mbsload( &resmod , _allocator , "D2d1" , 0 , debuginfo_macros ) )
				{	
					_D2d1 = resmod.module;
					::booldog::result_pointer resptr;
					if( _D2d1->method( &resptr , _allocator , "D2D1CreateFactory" , debuginfo ) == false )
					{
						res->copy( resptr );
						goto goto_unload;
					}
					::booldog::typedefs::D2D1CreateFactory pD2D1CreateFactory = (::booldog::typedefs::D2D1CreateFactory)resptr.pres;
					HRESULT hr = pD2D1CreateFactory( D2D1_FACTORY_TYPE_MULTI_THREADED , __uuidof( ID2D1Factory1 ) , 0 
						, reinterpret_cast< void** >( &_D2d1factory1 ) );
					if( FAILED( hr ) )
						hr = pD2D1CreateFactory( D2D1_FACTORY_TYPE_MULTI_THREADED , __uuidof( ID2D1Factory ) , 0 
							, reinterpret_cast< void** >( &_D2d1factory ) );
					if( FAILED( hr ) )
						res->setHRESULT( hr );
goto_unload:
					;
				}
				else
					res->copy( resmod );
				if( _D2d1factory1 )
				{
					if( _loader->mbsload( &resmod , _allocator , "D3D11" , 0 , debuginfo_macros ) )
					{	
						_D3D11 = resmod.module;

						::booldog::array< IDXGIAdapter* > dxgi_adapters( _allocator );
						D3D_FEATURE_LEVEL D3D11_feature_level;
						ID3D11Device* D3D11_device = 0;
						IDXGIDevice* dxgi_device = 0;
						IDXGIAdapter* dxgi_adapter = 0;
						IDXGIFactory1* dxgi_factory = 0;

						::booldog::result_pointer resptr;
						if( _D3D11->method( &resptr , _allocator , "D3D11CreateDevice" , debuginfo ) == false )
						{
							res->copy( resptr );
							goto goto_unload0;
						}
						_D3D11CreateDevice = (::booldog::typedefs::D3D11CreateDevice)resptr.pres;
						UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
						D3D_FEATURE_LEVEL featureLevels[] = 
						{
							//D3D_FEATURE_LEVEL_11_1,
							D3D_FEATURE_LEVEL_11_0,
							D3D_FEATURE_LEVEL_10_1,
							D3D_FEATURE_LEVEL_10_0,
							D3D_FEATURE_LEVEL_9_3,
							D3D_FEATURE_LEVEL_9_2,
							D3D_FEATURE_LEVEL_9_1
						};
						HRESULT hr = _D3D11CreateDevice( 0 , D3D_DRIVER_TYPE_HARDWARE , 0 , creationFlags , featureLevels 
							, ARRAYSIZE( featureLevels ) , D3D11_SDK_VERSION , &D3D11_device , &D3D11_feature_level , 0 );
						if( FAILED( hr ) )
						{
							res->setHRESULT( hr );
							goto goto_unload0;
						}
						hr = D3D11_device->QueryInterface( __uuidof( IDXGIDevice ), reinterpret_cast<void**>( &dxgi_device ) );
						if( FAILED( hr ) )
						{
							res->setHRESULT( hr );
							goto goto_unload0;
						}
						hr = dxgi_device->GetAdapter( &dxgi_adapter );
						if( FAILED( hr ) )
						{
							res->setHRESULT( hr );
							goto goto_unload0;
						}
						hr = dxgi_adapter->GetParent( __uuidof( IDXGIFactory1 ) , reinterpret_cast< void** >( &dxgi_factory ) );
						if( FAILED( hr ) )
						{
							res->setHRESULT( hr );
							goto goto_unload0;
						}
						UINT index0 = 0; 
						IDXGIAdapter* dxgi_adapter0 = 0; 
						while( dxgi_factory->EnumAdapters( index0++ , &dxgi_adapter0 ) != DXGI_ERROR_NOT_FOUND ) 
						{ 
							DXGI_ADAPTER_DESC dxgi_adapter_desc;

							dxgi_adapter0->GetDesc( &dxgi_adapter_desc );
							
							UINT output_count = 0;
							IDXGIOutput* dxgi_output = 0;
							while( dxgi_adapter0->EnumOutputs( output_count , &dxgi_output ) != DXGI_ERROR_NOT_FOUND )
							{
								DXGI_OUTPUT_DESC dxgi_output_desc;
								hr = dxgi_output->GetDesc( &dxgi_output_desc );

								printf( "%u %S %d, %d ,%d, %d\n" , index0 , dxgi_adapter_desc.Description 
									, (int)dxgi_output_desc.DesktopCoordinates.left 
									, (int)dxgi_output_desc.DesktopCoordinates.top , (int)dxgi_output_desc.DesktopCoordinates.right
									, (int)dxgi_output_desc.DesktopCoordinates.bottom );

								dxgi_output->Release();
								++output_count;
							}
							if( output_count )
								dxgi_adapters.add( dxgi_adapter0 );
							else
								dxgi_adapter0->Release();
						}
						if( dxgi_adapters.count() > 1 )
						{
							ID3D11Device* D3D11_device0 = 0;
							for( index0 = 0 ; index0 < dxgi_adapters.count() ; index0++ )
							{
								hr = _D3D11CreateDevice( dxgi_adapters[ index0 ] , D3D_DRIVER_TYPE_UNKNOWN , 0 , creationFlags , featureLevels 
									, ARRAYSIZE( featureLevels ) , D3D11_SDK_VERSION , &D3D11_device0 , &D3D11_feature_level , 0 );
								if( SUCCEEDED( hr ) )
								{
									D3D11_device0->Release();
									_dxgi_adapters.add( dxgi_adapters[ index0 ] );
								}
								else
									dxgi_adapters[ index0 ]->Release();
							}
						}
						else if( dxgi_adapters.count() == 1 )
							dxgi_adapters[ 0 ]->Release();
						if( _dxgi_adapters.count() == 0 )
						{
							_dxgi_adapters.add( dxgi_adapter );
							dxgi_adapter = 0;
						}
goto_unload0:
						if( dxgi_device )
							dxgi_device->Release();
						if( dxgi_adapter )
							dxgi_adapter->Release();
						if( dxgi_factory )
							dxgi_factory->Release();
						if( D3D11_device )
							D3D11_device->Release();
					}
				}
			};
			~factory( void )
			{
				if( _D2d1factory1 )
					_D2d1factory1->Release();
				if( _D2d1factory )
					_D2d1factory->Release();
				for( size_t index0 = 0 ; index0 < _dxgi_adapters.count() ; index0++ )
					_dxgi_adapters[ index0 ]->Release();
				if( _D2d1 )
					_loader->unload( 0 , _D2d1 , 0 , 0 , debuginfo_macros );
				if( _D3D11 )
					_loader->unload( 0 , _D3D11 , 0 , 0 , debuginfo_macros );
			};
			::booldog::allocator* allocator( void )
			{
				return _allocator;
			};
		};
#define booctor_null_macro( FUNC ) _##FUNC( 0 )
		class context : public ::booldog::rendering::context
		{
		public:
			bool _multithreaded;
			::booldog::D2d1::factory* _factory;
			ID2D1DeviceContext* _D2d1device_ctx;
			IDXGISwapChain1* _dxgi_swap_chain1;
			ID2D1HwndRenderTarget* _hwnd_render_target;
			HWND _hwnd;
			::booldog::threading::thread* _thread;
			::booldog::pid_t _render_thread_id;
			int _resize_width;
			int _resize_height;
		public:
			context( ::booldog::result* pres , HWND hwnd , ::booldog::events::typedefs::oncontextcreated poncontextcreated
				, bool multithreaded , ::booldog::D2d1::factory* pfactory 
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				: ::booldog::rendering::context( poncontextcreated ) , _factory( pfactory ) , _hwnd_render_target( 0 ) , _hwnd( hwnd )
					, _D2d1device_ctx( 0 ) , _dxgi_swap_chain1( 0 ) , _multithreaded( multithreaded ) , _thread( 0 )
					, _render_thread_id( 0 ) , _resize_width( INT32_MAX ) , _resize_height( INT32_MAX )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
				create( res , debuginfo );
				if( res->succeeded() )
					destroy();
			};
			~context( void )
			{
				destroy();
			};
			::booldog::D2d1::factory* factory( void )
			{
				return _factory;
			};
			bool create( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
				if( _hwnd_render_target == 0 && _D2d1device_ctx == 0 )
				{
					::booldog::result_module resmodUser32;
					if( _factory->_loader->mbsload( &resmodUser32 , _factory->_allocator , "User32" , 0 , debuginfo ) )
					{
						::booldog::result_pointer resptr;
						if( resmodUser32.module->method( &resptr , _factory->_allocator , "GetClientRect" , debuginfo ) == false )
						{
							res->copy( resptr );
							goto goto_unload;
						}
						::booldog::typedefs::GetClientRect pGetClientRect = (::booldog::typedefs::GetClientRect)resptr.pres;
						if( resmodUser32.module->method( &resptr , _factory->_allocator , "GetWindowRect" , debuginfo ) == false )
						{
							res->copy( resptr );
							goto goto_unload;
						}
						::booldog::typedefs::GetWindowRect pGetWindowRect = (::booldog::typedefs::GetWindowRect)resptr.pres;					

						RECT rc;
						HRESULT hr = S_OK;
						if( _factory->_D2d1factory1 )
						{
							pGetWindowRect( _hwnd , &rc );
							UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
							D3D_FEATURE_LEVEL featureLevels[] = 
							{
								//D3D_FEATURE_LEVEL_11_1,
								D3D_FEATURE_LEVEL_11_0,
								D3D_FEATURE_LEVEL_10_1,
								D3D_FEATURE_LEVEL_10_0,
								D3D_FEATURE_LEVEL_9_3,
								D3D_FEATURE_LEVEL_9_2,
								D3D_FEATURE_LEVEL_9_1
							};
							if( _factory->_dxgi_adapters.count() )
							{
								ID3D11Device* d3d11device = 0;
								IDXGIDevice* dxgi_device = 0;
								IDXGIAdapter* dxgi_adapter = 0;
								ID2D1Device* D2d1device = 0;
								ID2D1Bitmap1* D2d1bitmap1 = 0;
								if( _factory->_dxgi_adapters.count() > 1 )
								{
									for( size_t index0 = 0 ; index0 < _factory->_dxgi_adapters.count() ; index0++ )
									{
										dxgi_adapter = _factory->_dxgi_adapters[ index0 ];
										UINT output_count = 0;
										IDXGIOutput* dxgi_output = 0;
										while( dxgi_adapter->EnumOutputs( output_count++ , &dxgi_output ) != DXGI_ERROR_NOT_FOUND )
										{
											DXGI_OUTPUT_DESC dxgi_output_desc;
					  						hr = dxgi_output->GetDesc( &dxgi_output_desc );
											if( SUCCEEDED( hr ) )
											{
												if( ::booldog::utils::math::geometry::is_rectangles_intersect( rc.left , rc.top 
													, rc.right , rc.bottom , dxgi_output_desc.DesktopCoordinates.left 
													, dxgi_output_desc.DesktopCoordinates.top , dxgi_output_desc.DesktopCoordinates.right
													, dxgi_output_desc.DesktopCoordinates.bottom ) )
												{
													hr = _factory->_D3D11CreateDevice( dxgi_adapter , D3D_DRIVER_TYPE_UNKNOWN , 0 
														, creationFlags , featureLevels , ARRAYSIZE( featureLevels ) , D3D11_SDK_VERSION
														, &d3d11device , 0 , 0 );
													if( FAILED( hr ) )
														goto goto_release;
													hr = d3d11device->QueryInterface( __uuidof( IDXGIDevice )
														, reinterpret_cast<void**>( &dxgi_device ) );
													if( FAILED( hr ) )
														goto goto_release;

													DXGI_ADAPTER_DESC dxgi_adapter_desc;
													dxgi_adapter->GetDesc( &dxgi_adapter_desc );

													printf( "%S %d, %d ,%d, %d, %d, %d, %d, %d\n" , dxgi_adapter_desc.Description , (int)rc.left , (int)rc.top 
														, (int)( rc.right - rc.left ) , (int)( rc.bottom - rc.top ) , (int)dxgi_output_desc.DesktopCoordinates.left 
														, (int)dxgi_output_desc.DesktopCoordinates.top , (int)( dxgi_output_desc.DesktopCoordinates.right - dxgi_output_desc.DesktopCoordinates.left )
														, (int)( dxgi_output_desc.DesktopCoordinates.bottom - dxgi_output_desc.DesktopCoordinates.top ) );

													dxgi_output->Release();
													goto goto_found;
												}
											}
											dxgi_output->Release();
										}
goto_release:
										if( d3d11device )
										{
											d3d11device->Release();
											d3d11device = 0;
										}
										if( dxgi_device )
										{
											dxgi_device->Release();
											dxgi_device = 0;
										}
									}
								}
goto_found:
								if( dxgi_device == 0 )
								{
									dxgi_adapter = _factory->_dxgi_adapters[ 0 ];
																		
									hr = _factory->_D3D11CreateDevice( dxgi_adapter , D3D_DRIVER_TYPE_UNKNOWN , 0 , creationFlags
										, featureLevels , ARRAYSIZE( featureLevels ) , D3D11_SDK_VERSION , &d3d11device 
										, 0 , 0 );
									if( FAILED( hr ) )
										goto goto_next;
									hr = d3d11device->QueryInterface( __uuidof( IDXGIDevice )
										, reinterpret_cast<void**>( &dxgi_device ) );
									if( FAILED( hr ) )
										goto goto_next;
								}
								if( dxgi_device )
								{
									hr = _factory->_D2d1factory1->CreateDevice( dxgi_device , &D2d1device );
									if( FAILED( hr ) )
										goto goto_next;
									hr = D2d1device->CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS 
										, &_D2d1device_ctx );
									if( FAILED( hr ) )
										goto goto_next;									
									
									IDXGIFactory2* dxgi_factory2 = 0;
									IDXGISurface* dxgi_surface = 0;

									FLOAT dpi_x = 0 , dpi_y = 0;
									_factory->_D2d1factory1->GetDesktopDpi( &dpi_x , &dpi_y );									
									D2D1_BITMAP_PROPERTIES1 d2d1_bitmap_properties = D2D1::BitmapProperties1( 
										D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW 
										, D2D1::PixelFormat( DXGI_FORMAT_B8G8R8A8_UNORM , D2D1_ALPHA_MODE_IGNORE ) , dpi_x , dpi_y );
									DXGI_SWAP_CHAIN_DESC1 dxgi_swap_chain_desc1 = {0};
									dxgi_swap_chain_desc1.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
									dxgi_swap_chain_desc1.SampleDesc.Count = 1;
									dxgi_swap_chain_desc1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
									dxgi_swap_chain_desc1.BufferCount = 2;
									/*
									DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {0};
									swapChainDesc.Width = 0;
									swapChainDesc.Height = 0;
									swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
									swapChainDesc.Stereo = false; 
									swapChainDesc.SampleDesc.Count = 1;
									swapChainDesc.SampleDesc.Quality = 0;
									swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
									swapChainDesc.BufferCount = 2;
									swapChainDesc.Scaling = DXGI_SCALING_NONE;
									swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
									swapChainDesc.Flags = 0;*/				

									hr = dxgi_adapter->GetParent( IID_PPV_ARGS( &dxgi_factory2 ) );
									if( FAILED( hr ) )
										goto goto_release0;
											
									hr = dxgi_factory2->CreateSwapChainForHwnd( d3d11device , _hwnd , &dxgi_swap_chain_desc1 , 0 , 0
										, &_dxgi_swap_chain1 );
									if( FAILED( hr ) )
										goto goto_release0;
										
									IDXGIDevice1* dxgi_device1 = 0;								
									hr = d3d11device->QueryInterface( __uuidof( IDXGIDevice1 )
										, reinterpret_cast<void**>( &dxgi_device1 ) );
									if( SUCCEEDED( hr ) )
									{
										dxgi_device1->SetMaximumFrameLatency( 1 );
										dxgi_device1->Release();
									}
									
									hr = _dxgi_swap_chain1->GetBuffer( 0 , IID_PPV_ARGS( &dxgi_surface ) );
									if( FAILED( hr ) )
										goto goto_release0;									

									hr = _D2d1device_ctx->CreateBitmapFromDxgiSurface( dxgi_surface , &d2d1_bitmap_properties 
										, &D2d1bitmap1 );
									if( FAILED( hr ) )
										goto goto_release0;

									_D2d1device_ctx->SetTarget( D2d1bitmap1 );
									_D2d1device_ctx->SetDpi( dpi_x , dpi_y );

									printf( "Direct2D 1.1\n" );
goto_release0:
									if( dxgi_surface )
										dxgi_surface->Release();
									if( dxgi_factory2 )
										dxgi_factory2->Release();									
								}
goto_next:
								if( D2d1bitmap1 )
									D2d1bitmap1->Release();
								if( D2d1device )
									D2d1device->Release();								
								if( dxgi_device )
									dxgi_device->Release();
								if( d3d11device )
									d3d11device->Release();
							}
						}
						else if( _factory->_D2d1factory )
						{
							pGetClientRect( _hwnd , &rc );
							D2D1_SIZE_U size = D2D1::SizeU( rc.right - rc.left , rc.bottom - rc.top );

							hr = _factory->_D2d1factory->CreateHwndRenderTarget( D2D1::RenderTargetProperties() 
								, D2D1::HwndRenderTargetProperties( _hwnd, size ) , &_hwnd_render_target );
							
							printf( "Direct2D\n" );
						}
						if( FAILED( hr ) )
						{
							destroy();
							res->setHRESULT( hr );
						}
					}
					else
						res->copy( resmodUser32 );
goto_unload:
					if( resmodUser32.module )
						_factory->_loader->unload( 0 , resmodUser32.module , 0 , 0 , debuginfo_macros );
				}
				return res->succeeded();
			};
			void destroy( void )
			{
				if( _oncontextbeforedestroy )
					_oncontextbeforedestroy( _udata , this );
				if( _dxgi_swap_chain1 )
				{
					_dxgi_swap_chain1->Release();
					_dxgi_swap_chain1 = 0;
				}
				if( _D2d1device_ctx )
				{
					_D2d1device_ctx->Release();
					_D2d1device_ctx = 0;
				}
				if( _hwnd_render_target )
				{
					_hwnd_render_target->Release();
					_hwnd_render_target = 0;
				}
			};
			virtual void resize( int width , int height )
			{
				if( _render_thread_id == 0 || _render_thread_id == ::booldog::threading::threadid() )
				{
					if( _hwnd_render_target )
					{
						D2D1_SIZE_U size = D2D1::SizeU( width , height );
						_hwnd_render_target->Resize( size );
					}
					else if( _dxgi_swap_chain1 )
					{
						if( FAILED( _dxgi_swap_chain1->ResizeBuffers( 0 , 0 , 0 , DXGI_FORMAT_UNKNOWN , 0 ) ) )
							destroy();
					}
					if( _oncontextresize )
						_oncontextresize( _udata , this , width , height );
				}
				else
				{
					_resize_width = width;
					_resize_height = height;
				}
			};
			virtual void before_resize( void )
			{
			};
			virtual void after_resize( void )
			{
			};
			static void onrenderprocedure( ::booldog::threading::thread* thr )
			{
				::booldog::D2d1::context* ctx = (::booldog::D2d1::context*)thr->udata();
				ctx->_render_thread_id = ::booldog::threading::threadid();
				while( thr->pending_in_stop() == false )
				{
					if( ctx->_resize_width != INT32_MAX )
					{
						ctx->resize( ctx->_resize_width , ctx->_resize_height );
						ctx->_resize_width = ctx->_resize_height = INT32_MAX;
					}

					::booldog::result res;
					ctx->create( &res );
					if( ctx->_hwnd_render_target )
					{
						ctx->_hwnd_render_target->BeginDraw();

						ctx->_hwnd_render_target->Clear( D2D1::ColorF( D2D1::ColorF::Yellow ) );

						ctx->_oncontextrender( ctx->_udata , ctx );

						HRESULT hr = ctx->_hwnd_render_target->EndDraw();

						if( hr == D2DERR_RECREATE_TARGET )
							ctx->destroy();
					}
					else if( ctx->_dxgi_swap_chain1 )
					{
						//GLfloat image_left = 0 , image_top = 0 , image_width = rgbawidth , image_height = rgbaheight;
						//GLfloat left = 10 , top = 10 , width = 1000 , height = 800 , zindex = 0;

						/*ID2D1Bitmap1* d2d1bitmap = (ID2D1Bitmap1*)ctx->udata();
						if( d2d1bitmap == 0 )
						{
							D2D1_SIZE_U  size = { rgbawidth, rgbaheight };
							D2D1_BITMAP_PROPERTIES1 properties = {{ DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED }, 96, 96, D2D1_BITMAP_OPTIONS_TARGET, 0 };
							HRESULT hr = D2d1ctx->_D2d1device_ctx->CreateBitmap( size , 0 , 0 , properties , &d2d1bitmap );
							if( SUCCEEDED( hr ) )
							{
								ctx->udata( d2d1bitmap );
								__d2d1bitmap = d2d1bitmap;
							}
						//}
						//if( d2d1bitmap )
						//{
							//D2D1_RECT_U rect = { 0 , 0 , rgbawidth , rgbaheight };
				
							d2d1bitmap->CopyFromMemory( 0 , rgba , 4 * rgbawidth );
						}*/

						ctx->_D2d1device_ctx->BeginDraw();

						ctx->_D2d1device_ctx->Clear( D2D1::ColorF( D2D1::ColorF::Yellow ) );

						ctx->_oncontextrender( ctx->_udata , ctx );

						/*if( d2d1bitmap )
						{
							D2D1_RECT_F rectf = { left , top , width , height };
							D2d1ctx->_D2d1device_ctx->DrawBitmap( d2d1bitmap , &rectf );
						}*/

						ctx->_D2d1device_ctx->EndDraw();

						HRESULT hr = ctx->_dxgi_swap_chain1->Present( 1 , 0 );
						if( FAILED( hr ) && hr != DXGI_STATUS_OCCLUDED )
							ctx->destroy();
					}
					::booldog::threading::sleep( 1 );
				}
			};
			virtual void oncontextrender( ::booldog::events::typedefs::oncontextrender poncontextrender )
			{
				_oncontextrender = poncontextrender;
				if( _multithreaded )
				{
					if( _thread == 0 )
					{
						::booldog::result res;
						_thread = ::booldog::threading::thread::create( &res , _factory->_allocator , 1024 * 1024 , 0 , 0 
							, onrenderprocedure , this , debuginfo_macros );
					}
				}
			};
		};
		static booinline void* create_factory( void* allocator , void* loader )
		{
		   ::booldog::allocator* pallocator = (::booldog::allocator*)allocator;
		   ::booldog::base::loader* ploader = (::booldog::base::loader*)loader;

		   ::booldog::result res;
			::booldog::D2d1::factory* factory = pallocator->create< ::booldog::D2d1::factory >( &res , pallocator , ploader	
				, debuginfo_macros , debuginfo_macros );
			if( res.succeeded() == false && factory )
			{
				pallocator->destroy( factory );
				factory = 0;
			}
			return factory;
		};
		static booinline void destroy_factory( void* factory )
		{
			::booldog::D2d1::factory* pfactory = (::booldog::D2d1::factory*)factory;
			::booldog::allocator* pallocator = pfactory->allocator();
			pallocator->destroy( pfactory );
		};
		static booinline void* create_context( HWND hwnd , void* udata , void* factory
			, ::booldog::events::typedefs::oncontextcreated poncontextcreated
			, ::booldog::events::typedefs::oncontextresize poncontextresize
			, ::booldog::events::typedefs::oncontextrender poncontextrender 
			, ::booldog::events::typedefs::oncontextbeforedestroy poncontextbeforedestroy )
		{
			::booldog::D2d1::factory* pfactory = (::booldog::D2d1::factory*)factory;
			::booldog::allocator* pallocator = pfactory->allocator();
			bool is_multithreaded = true;
			::booldog::result res;
			::booldog::D2d1::context* pctx = pallocator->create< ::booldog::D2d1::context >( 
				&res , hwnd , poncontextcreated , is_multithreaded , pfactory , debuginfo_macros , debuginfo_macros );
			if( res.succeeded() )
			{
				pctx->udata( udata );
				pctx->oncontextbeforedestroy( poncontextbeforedestroy );
				pctx->oncontextresize( poncontextresize );
				if( is_multithreaded )
					pctx->oncontextrender( poncontextrender );
			}
			else if( pctx )
			{
				pallocator->destroy( pctx );
				pctx = 0;
			}
			return pctx;
		};
		static void raise_onwindowresize( void* ctx , int width , int height )
		{
			::booldog::D2d1::context* pctx = (::booldog::D2d1::context*)ctx;
			pctx->raise_onwindowresize( width , height );
		};
		static void destroy_context( void* ctx )
		{
			::booldog::D2d1::context* pctx = (::booldog::D2d1::context*)ctx;
			::booldog::allocator* pallocator = pctx->factory()->allocator();
			pallocator->destroy( pctx );
		};
	};
};
#endif
#endif