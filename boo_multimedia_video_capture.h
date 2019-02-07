/** class capture
* Simplify work with video capture from USB cameras
* Linux(sudo apt-get install libv4l-dev, sudo yum install libv4l-devel)
* Windows(libraries: Ole32 OleAut32 strmiids)
*/

#ifndef BOO_MULTIMEDIA_VIDEO_CAPTURE_H
#define BOO_MULTIMEDIA_VIDEO_CAPTURE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_multimedia_enums.h"
#include "boo_multimedia_video_frame.h"
#include "boo_time_utils.h"
#include "boo_error.h"
#include "boo_result.h"

//#if 1
#ifdef __LINUX__
#include "boo_io_directory.h"
#include <linux/videodev2.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#ifndef _LARGEFILE64_SOURCE 
#define _LARGEFILE64_SOURCE 
#endif
#include <unistd.h>
#include <sys/mman.h>
#include <sys/select.h>

#ifndef V4L2_PIX_FMT_H264
#define V4L2_PIX_FMT_H264     v4l2_fourcc('H', '2', '6', '4') /* H264 with start codes */
#endif
#elif defined(__WINDOWS__)
#include <DShow.h>
#include <dvdmedia.h>

#include "boo_utf16.h"
#include "boo_utf8.h"

#pragma comment(lib, "Ole32")
#pragma comment(lib, "OleAut32")
#pragma comment(lib, "strmiids")

#include "boo_lockfree_queue.h"
#endif
namespace booldog
{
	namespace multimedia
	{
		namespace video
		{
			class capture;
                }
        }
	namespace results
	{
		namespace multimedia
		{
			namespace video
			{
				class capture : public ::booldog::result
				{
				private:
					capture(const ::booldog::result&)
					{
                                        }
					capture(const ::booldog::results::multimedia::video::capture&)
                                            : result()
					{
                                        }
					::booldog::results::multimedia::video::capture& operator = (const ::booldog::results::multimedia::video::capture&)
					{
						return *this;
					}
				public:
					::booldog::multimedia::video::capture* video;
					capture()
						: video(0)
					{
					}
					virtual ~capture()
					{
					}
					virtual void clear() const
					{
						::booldog::results::multimedia::video::capture* _obj_ 
							= const_cast< ::booldog::results::multimedia::video::capture* >(this);
	#ifdef __UNIX__
						_obj_->dlerrorclear();
	#endif
						_obj_->error_type = ::booldog::enums::result::error_type_no_error;
						_obj_->video = 0;
                                        }
				};
                        }
                }
        }
	namespace multimedia
	{
		namespace video
		{
			namespace typedefs
			{
				typedef bool (*available_cameras_callback_t)(::booldog::allocator* allocator, void* udata, const char* name
					, const char* deviceid, ::booldog::uint32 capabilities);
				typedef bool (*available_formats_callback_t)(::booldog::allocator* allocator, void* udata
					, ::booldog::uint32 fourcc, ::booldog::uint32 width, ::booldog::uint32 height
					, ::booldog::uint32 framerate_numerator, ::booldog::uint32 framerate_denominator, const char* description);
				typedef void (*read_frame_callback_t)(::booldog::allocator* allocator, void* udata, ::booldog::multimedia::video::frame* vframe);
                        }
			class capture
#ifdef __WINDOWS__
			: public IBaseFilter
#endif
			{
				friend class ::booldog::allocator;
				::booldog::allocator* _allocator;
			private:
				bool _streaming;
				::booldog::uint32 _width;
				::booldog::uint32 _height;
				::booldog::uint32 _fourcc;
                ::booldog::uint32 _framerate_numerator;
                ::booldog::uint32 _framerate_denominator;
                ::booldog::uint32 _size;
	#ifdef __LINUX__
				struct buffer 
				{
					void* start;
					size_t length;
					bool mmap;
                                        size_t offset;
				};				
				int _capture_type;
                                ::booldog::multimedia::video::capture::buffer _buffers[10];
				int _buffers_count;
				static int xioctl(int fh, int request, void *arg)
				{
					int r;
					do
					{
						r = ioctl(fh, request, arg);
					}
					while(-1 == r && EINTR == errno);
					return r;
				}
#elif defined(__WINDOWS__)
				::booldog::data::lockfree::queue< ::booldog::multimedia::video::frame > _frames;
				::booldog::data::lockfree::queue< ::booldog::multimedia::video::frame > _avail_frames;
				class pin : public IPin, public IMemInputPin
				{
				private:
					IPin* _connected;
					::booldog::multimedia::video::capture* _filter;
					IMemAllocator* _mem_allocator;
                    BYTE _mem_allocator_read_only;
				public:
					pin(::booldog::multimedia::video::capture* filter)
						: _connected(0), _filter(filter), _mem_allocator(0), _mem_allocator_read_only(0)
					{
					}
					virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv)
					{
						if(ppv == 0)
							return E_POINTER;
						if(riid == IID_IPin)
						{
							IPin* pobj = (IPin*)this;
							*ppv = pobj;
							pobj->AddRef();
						}
						else if(riid == IID_IMemInputPin)
						{
							IMemInputPin* pobj = (IMemInputPin*)this;
							*ppv = pobj;
							pobj->AddRef();
						}
						else if(riid == IID_IQualityControl)
						{
							IPin* pobj = (IPin*)this;
							*ppv = pobj;
							pobj->AddRef();
						}
						else if(riid == IID_IUnknown)
						{
							IUnknown* pobj = (IUnknown*)(IPin*)this;
							*ppv = pobj;
							pobj->AddRef();
						}
						else
						{
							*ppv = 0;
							return E_NOINTERFACE;
						}
						return NOERROR;
					}
					virtual ULONG __stdcall AddRef()
					{
						return 1;
					}
					virtual ULONG __stdcall Release()
					{
						return 1;
					}
					virtual HRESULT __stdcall Connect(IPin* pReceivePin, const AM_MEDIA_TYPE* pmt)
					{
                        pReceivePin = pReceivePin;
                        pmt = pmt;
						return E_NOTIMPL;
					}
					virtual HRESULT __stdcall ReceiveConnection(IPin* pConnector, const AM_MEDIA_TYPE* pmt)
					{
						if(pConnector == 0 || pmt == 0)
							return E_POINTER;
						if(_connected)
							return VFW_E_ALREADY_CONNECTED;
						_connected = pConnector;
                        _connected->AddRef();
						if(pmt->formattype == FORMAT_VideoInfo)
						{
							if(pmt->cbFormat >= sizeof(VIDEOINFOHEADER))
							{
								VIDEOINFOHEADER* videoinfoheader = 
									reinterpret_cast< VIDEOINFOHEADER* >(pmt->pbFormat);
								_filter->_fourcc = videoinfoheader->bmiHeader.biCompression;
								_filter->_width = videoinfoheader->bmiHeader.biWidth;
								_filter->_height = videoinfoheader->bmiHeader.biHeight;
								_filter->_size = videoinfoheader->bmiHeader.biSize;
							}
						}
						else if(pmt->formattype == FORMAT_VideoInfo2)
						{
							if(pmt->cbFormat >= sizeof(VIDEOINFOHEADER2))
							{
								VIDEOINFOHEADER2* videoinfoheader = 
									reinterpret_cast< VIDEOINFOHEADER2* >(pmt->pbFormat);
								_filter->_fourcc = videoinfoheader->bmiHeader.biCompression;
								_filter->_width = videoinfoheader->bmiHeader.biWidth;
								_filter->_height = videoinfoheader->bmiHeader.biHeight;
								_filter->_size = videoinfoheader->bmiHeader.biSize;
							}
						}
						return NOERROR;
					}
					virtual HRESULT __stdcall Disconnect()
					{
						if(_connected)
						{
							if(_mem_allocator)
							{
								HRESULT hr = _mem_allocator->Decommit();
								if(FAILED(hr))
									return hr;
								_mem_allocator->Release();
								_mem_allocator = 0;
							}
							_connected->Release();
							_connected = 0;
							return S_OK;
						}
						else
							return S_FALSE;
					}
					virtual HRESULT __stdcall ConnectedTo(IPin** pPin)
					{
						if(pPin == 0)
							return E_POINTER;
						*pPin = _connected;
						if(_connected)
						{
							_connected->AddRef();
							return S_OK;
						}
						else
							return VFW_E_NOT_CONNECTED;
					}
					virtual HRESULT __stdcall ConnectionMediaType(AM_MEDIA_TYPE* pmt)
					{
                        pmt = pmt;
						return E_NOTIMPL;
					}
					virtual HRESULT __stdcall QueryPinInfo(PIN_INFO* pInfo)
					{
						if(pInfo == 0)
							return E_POINTER;
						pInfo->pFilter = _filter;
						wcscpy_s(pInfo->achName, 7, L"Render");
						if(_filter)
							_filter->AddRef();
						pInfo->dir = PINDIR_INPUT;
						return NOERROR;
					}
					virtual HRESULT __stdcall QueryDirection(PIN_DIRECTION* pPinDir)
					{
						if(pPinDir == 0)
							return E_POINTER;
						*pPinDir = PINDIR_INPUT;
						return NOERROR;
					}
					virtual HRESULT __stdcall QueryId(LPWSTR* Id)
					{
                        Id = Id;
						return E_NOTIMPL;
					}
					virtual HRESULT __stdcall QueryAccept(const AM_MEDIA_TYPE *pmt)
					{
                        pmt = pmt;
						return E_NOTIMPL;
					}
					virtual HRESULT __stdcall EnumMediaTypes(IEnumMediaTypes** ppEnum)
					{
                        ppEnum = ppEnum;
						return E_NOTIMPL;
					}
					virtual HRESULT __stdcall QueryInternalConnections(IPin** apPin, ULONG* nPin)
					{
                        apPin = apPin;
                        nPin = nPin;
						return E_NOTIMPL;
					}
					virtual HRESULT __stdcall EndOfStream()
                    {
						return E_NOTIMPL;
					}
					virtual HRESULT __stdcall BeginFlush()
                    {
						return E_NOTIMPL;
					}
					virtual HRESULT __stdcall EndFlush()
                    {
						return E_NOTIMPL;
					}
					virtual HRESULT __stdcall NewSegment(REFERENCE_TIME tStart, REFERENCE_TIME tStop, double dRate)
                    {
                        tStart = tStart;
                        tStop = tStop;
                        dRate = dRate;
						return E_NOTIMPL;
					}
					virtual HRESULT __stdcall GetAllocator(IMemAllocator** ppAllocator)
					{
                        ppAllocator = ppAllocator;
						return E_NOTIMPL;
					}
					virtual HRESULT __stdcall NotifyAllocator(IMemAllocator* pAllocator, BOOL bReadOnly)
					{
						if(pAllocator == 0)
							return E_POINTER;
						//TODO cs
						if(_mem_allocator)
							_mem_allocator->Release();
						_mem_allocator = pAllocator;
						_mem_allocator->AddRef();
						_mem_allocator_read_only = (BYTE)bReadOnly;
						return NOERROR;
					}
					virtual HRESULT __stdcall GetAllocatorRequirements(ALLOCATOR_PROPERTIES* pProps)
					{
                        pProps = pProps;
						return E_NOTIMPL;
					}
					virtual HRESULT __stdcall Receive(IMediaSample* pSample)
					{
						if(pSample == 0)
                            return E_POINTER;

                        ::booldog::uint64 new_last_tickcount = GetTickCount();
                        if(new_last_tickcount < _filter->_last_tickcount)
                            _filter->_last_tickcount = new_last_tickcount;
                        _filter->_timestamp += (1000ULL * (new_last_tickcount - _filter->_last_tickcount));
                        _filter->_last_tickcount = new_last_tickcount;

						AM_MEDIA_TYPE* am_media_type = 0;
						if(pSample->GetMediaType(&am_media_type) == S_OK)
						{
							if(am_media_type->formattype == FORMAT_VideoInfo)
							{
								if(am_media_type->cbFormat >= sizeof(VIDEOINFOHEADER))
								{
									VIDEOINFOHEADER* videoinfoheader = 
										reinterpret_cast< VIDEOINFOHEADER* >(am_media_type->pbFormat);
									_filter->_fourcc = videoinfoheader->bmiHeader.biCompression;
									_filter->_width = videoinfoheader->bmiHeader.biWidth;
									_filter->_height = videoinfoheader->bmiHeader.biHeight;
									_filter->_size = videoinfoheader->bmiHeader.biSize;
								}
							}
							else if(am_media_type->formattype == FORMAT_VideoInfo2)
							{
								if(am_media_type->cbFormat >= sizeof(VIDEOINFOHEADER2))
								{
									VIDEOINFOHEADER2* videoinfoheader = 
										reinterpret_cast< VIDEOINFOHEADER2* >(am_media_type->pbFormat);
									_filter->_fourcc = videoinfoheader->bmiHeader.biCompression;
									_filter->_width = videoinfoheader->bmiHeader.biWidth;
									_filter->_height = videoinfoheader->bmiHeader.biHeight;
									_filter->_size = videoinfoheader->bmiHeader.biSize;
								}
							}
							if(am_media_type->cbFormat != 0)
								CoTaskMemFree((PVOID)am_media_type->pbFormat);
							if(am_media_type->pUnk != 0)
								am_media_type->pUnk->Release();
							CoTaskMemFree(am_media_type);
							am_media_type = 0;
						}
						BYTE* buffer = 0;
						if(SUCCEEDED(pSample->GetPointer(&buffer)))
						{
							::booldog::uint32 frame_size = (::booldog::uint32)pSample->GetActualDataLength();
							::booldog::multimedia::video::frame* vframe = 0;
							if(_filter->_frames.count() >= 5)
								vframe = _filter->_frames.dequeue();
							if(vframe == 0)
								vframe = _filter->_avail_frames.dequeue();
							if(vframe == 0)
								vframe = _filter->_allocator->create< ::booldog::multimedia::video::frame >(debuginfo_macros);
							if(vframe)
							{
								if(frame_size + 64 > vframe->alloc_size)
								{
									vframe->alloc_size = frame_size + 64;
									vframe->data = _filter->_allocator->realloc_array< ::booldog::byte >(vframe->data
										, vframe->alloc_size, debuginfo_macros);
									if(vframe->data == 0)
									{
										_filter->_avail_frames.enqueue(vframe);
										return E_OUTOFMEMORY;
									}
								}
								vframe->fourcc = _filter->_fourcc;
								vframe->width = _filter->_width;
								vframe->height = _filter->_height;
                                vframe->size = frame_size;
                                vframe->timestamp = _filter->_timestamp;
								::memcpy(vframe->data, buffer, frame_size);
								_filter->_frames.enqueue(vframe);
							}
							else
								return E_OUTOFMEMORY;
						}
						return NOERROR;
					}
					virtual HRESULT __stdcall ReceiveMultiple(IMediaSample** pSamples, long nSamples, long* nSamplesProcessed)
					{
						if(pSamples == 0)
							return E_POINTER;
						HRESULT hr = S_OK;
						long samples_processed = 0;						
						while(nSamples)
						{
							 hr = Receive(pSamples[samples_processed]);
							 if(hr != S_OK)
								 break;
							 ++samples_processed;
							 --nSamples;
						}
						*nSamplesProcessed = samples_processed;
						return hr;
					}
					virtual HRESULT __stdcall ReceiveCanBlock()
					{
						printf("5RRRR\n");
						return E_NOTIMPL;
					}
				};
				class enum_pins : public IEnumPins
				{
					private:
						const ULONG _pins_count;
						ULONG _position;
						::booldog::multimedia::video::capture* _capture;
						::booldog::interlocked::atomic _refs;
					public:
						enum_pins(::booldog::multimedia::video::capture* pcapture)
							: _pins_count(1), _position(0), _capture(pcapture), _refs(1)
						{
							_capture->AddRef();
						}
						~enum_pins()
						{
							_capture->Release();
						}
						virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv)
						{
							if(ppv == 0)
								return E_POINTER;
							if(riid == IID_IEnumPins)
							{
								IEnumPins* pobj = (IEnumPins*)this;
								*ppv = pobj;
								pobj->AddRef();
							}
							else if(riid == IID_IUnknown)
							{
								IUnknown* pobj = (IUnknown*)this;
								*ppv = pobj;
								pobj->AddRef();
							}
							else
							{
								*ppv = 0;
								return E_NOINTERFACE;
							}
							return NOERROR;
						}
						virtual ULONG __stdcall AddRef()
						{
							return ::booldog::interlocked::increment(&_refs);
						}
						virtual ULONG __stdcall Release()
						{
							ULONG cref = ::booldog::interlocked::decrement(&_refs);
							if(cref == 0)
								_capture->_allocator->destroy(this);
							return cref;
						}
						virtual HRESULT __stdcall Clone(IEnumPins** ppenum)
						{
							if(ppenum == 0)
								return E_POINTER;
							::booldog::multimedia::video::capture::enum_pins* clone = 
								_capture->_allocator->create< ::booldog::multimedia::video::capture::enum_pins >(_capture
								, debuginfo_macros);
							if(clone)
							{
								clone->_position = _position;
								*ppenum = clone;
								return NOERROR;
							}
							else
								return E_OUTOFMEMORY;
						}
						virtual HRESULT __stdcall Skip(ULONG cpins)
						{
							ULONG pins_left = _pins_count - _position;
							if(cpins > pins_left)
								return S_FALSE;
							_position += cpins;
							return NOERROR;
						}
						virtual HRESULT __stdcall Reset()
						{
							_position = 0;
							return S_OK;
						}
						virtual HRESULT __stdcall Next(ULONG cpins, IPin** ppins, ULONG* fetched)
						{
							if(ppins == 0)
								return E_POINTER;
							if(fetched)
								*fetched = 0;
							else if(cpins > 1)
								return E_INVALIDARG;
							ULONG cfetched = 0;
							while(cfetched < cpins && _pins_count > _position)
							{
								IPin* pin = _capture->_pin;
								++_position;

								*ppins = pin;
								++cfetched;
								++ppins;
							}
							if(fetched)
								*fetched = cfetched;
							return (cpins == cfetched ? NOERROR : S_FALSE);
						}						
				};
	#endif
				::booldog::uint64 _difference;
				::booldog::uint64 _timestamp;
				::booldog::uint64 _last_tickcount;
				char* _filename;
				size_t _filename_len;
				size_t _filename_size;
#ifdef __LINUX__
                int _fd;
#elif defined(__WINDOWS__)
				IBaseFilter* _base_filter;
				ICaptureGraphBuilder2* _capture_graph_builder;
				IGraphBuilder* _graph_builder;
				IReferenceClock* _reference_clock;
				IFilterGraph* _filter_graph;
				IMediaEventSink* _media_event_sink;
				::booldog::multimedia::video::capture::pin* _pin;
				FILTER_STATE _filter_state;
                                bool _need_CoUninitialize;
                bool _is_preview;
            public:
                void is_preview(bool value)
                {
                    _is_preview = value;
                }
            private:
#endif
				capture()
				{
				}
				capture(::booldog::allocator* pallocator
#ifdef __LINUX__
					, int pfd
#elif defined(__WINDOWS__)
					, IBaseFilter* pbase_filter
#endif
					)
					: _allocator(pallocator), _streaming(false)
					, _width(0), _height(0), _fourcc(0xffffffff), _framerate_numerator(0)
					, _framerate_denominator(0), _filename(0), _filename_len(0), _filename_size(0)
#ifdef __LINUX__
					, _fd(pfd)
#elif defined(__WINDOWS__)
					, _base_filter(pbase_filter), _capture_graph_builder(0), _graph_builder(0), _reference_clock(0)
                    , _filter_graph(0), _media_event_sink(0), _filter_state(State_Paused), _is_preview(false)
#endif
				{
#ifdef __LINUX__
					::memset(_buffers, 0, sizeof(_buffers));
#elif defined(__WINDOWS__)
					_pin = _allocator->create< ::booldog::multimedia::video::capture::pin >(this, debuginfo_macros);
#endif
				}
				capture(const ::booldog::multimedia::video::capture&)
				{
				}
#ifdef __WINDOWS__
				virtual HRESULT __stdcall capture::QueryInterface(REFIID riid, void** ppv)
				{
					if(ppv == 0)
						return E_POINTER;
					if(riid == IID_IBaseFilter)
					{
						IBaseFilter* pobj = (IBaseFilter*)this;
						*ppv = pobj;
						pobj->AddRef();
					}
					else if(riid == IID_IMediaFilter)
					{
						IMediaFilter* pobj = (IMediaFilter*)this;
						*ppv = pobj;
						pobj->AddRef();
					}
					else if(riid == IID_IPersist)
					{
						IPersist* pobj = (IPersist*)this;
						*ppv = pobj;
						pobj->AddRef();
					}
					else if(riid == IID_IUnknown)
					{
						IUnknown* pobj = (IUnknown*)this;
						*ppv = pobj;
						pobj->AddRef();
					}
					else
					{
						*ppv = 0;
						return E_NOINTERFACE;
					}
					return NOERROR;
				}
				virtual ULONG __stdcall capture::AddRef()
				{
					return 1;
				}
				virtual ULONG __stdcall capture::Release()
				{
					return 1;
				}
				virtual HRESULT __stdcall capture::GetClassID(CLSID* pClassID)
				{
					if(pClassID == 0)
						return E_POINTER;
					//TODO
					return NOERROR;
				}
				virtual HRESULT __stdcall capture::Stop()
				{
					_filter_state = State_Stopped;
					return S_OK;
				}
				virtual HRESULT __stdcall capture::Pause()
				{
					_filter_state = State_Paused;
					return S_OK;
				}
				virtual HRESULT __stdcall capture::Run(REFERENCE_TIME tStart)
				{
                    tStart = tStart;
					_filter_state = State_Running;
					return S_OK;
				}        
				virtual HRESULT __stdcall capture::GetState(DWORD dwMilliSecsTimeout, FILTER_STATE* State)
				{
					dwMilliSecsTimeout = dwMilliSecsTimeout;
					if(State == 0)
						return E_POINTER;
					*State = _filter_state;
					return S_OK;
				}
				virtual HRESULT __stdcall capture::SetSyncSource(IReferenceClock* pClock)
				{
					//TODO cs
					if(_reference_clock)
						_reference_clock->Release();
					if(pClock)
						pClock->AddRef();
					_reference_clock = pClock;
					return NOERROR;
				}
				virtual HRESULT __stdcall capture::GetSyncSource(IReferenceClock** pClock)
				{
					//TODO cs
					if(pClock == 0)
						return E_POINTER;
					if(_reference_clock)
						_reference_clock->AddRef();
					*pClock = _reference_clock;
					return NOERROR;
				}
				virtual HRESULT __stdcall capture::EnumPins(IEnumPins** ppenum)
				{
					if(ppenum == 0)
						return E_POINTER;
					::booldog::multimedia::video::capture::enum_pins* clone = 
						_allocator->create< ::booldog::multimedia::video::capture::enum_pins >(this, debuginfo_macros);
					if(clone)
					{
						*ppenum = clone;
						return NOERROR;
					}
					else
					{
						*ppenum = 0;
						return E_OUTOFMEMORY;
					}
				}
				virtual HRESULT __stdcall capture::FindPin(LPCWSTR Id, IPin** ppPin)
				{
                    Id = Id;
                    ppPin =ppPin;
					return S_OK;
				}
				virtual HRESULT __stdcall capture::QueryFilterInfo(FILTER_INFO* pInfo)
				{
					//TODO cs
					if(pInfo == 0)
						return E_POINTER;
					wcscpy_s(pInfo->achName, 16, L"Renderer Filter");
					//TODO copy Name to pInfo->achName
					pInfo->pGraph = _filter_graph;
					if(_filter_graph)
						_filter_graph->AddRef();
					return NOERROR;
				}
				virtual HRESULT __stdcall capture::JoinFilterGraph(IFilterGraph* pGraph, LPCWSTR pName)
				{
					//TODO cs
					_filter_graph = pGraph;
					if(_filter_graph)
					{
						HRESULT hr = _filter_graph->QueryInterface(IID_IMediaEventSink, (void**)&_media_event_sink);
						if(SUCCEEDED(hr))
							_media_event_sink->Release();
					}
					else
						_media_event_sink = 0;
					pName = pName;
					//TODO copy pName to Name E_OUTOFMEMORY
					return S_OK;
				}
				virtual HRESULT __stdcall capture::QueryVendorInfo(LPWSTR* pVendorInfo)
				{
					pVendorInfo = pVendorInfo;
					return E_NOTIMPL;
				}
#endif
				::booldog::multimedia::video::capture& operator = (const ::booldog::multimedia::video::capture&)
				{
					return *this;
				}
			public:
				~capture()
				{
#ifdef __LINUX__
					for(_buffers_count = 0 ; _buffers_count < (int)(sizeof(_buffers) / sizeof(_buffers[0])) ; ++_buffers_count)
					{
						if(_buffers[_buffers_count].start)
						{
							if(_buffers[_buffers_count].mmap)
								munmap(_buffers[_buffers_count].start, _buffers[_buffers_count].length);
							else
								_allocator->free(_buffers[_buffers_count].start);
						}
					}
#elif defined(__WINDOWS__)
					_allocator->destroy(_pin);                                        
					::booldog::multimedia::video::frame* toremove = _frames.dequeue();
					while(toremove)
					{
						::booldog::multimedia::video::frame* f = toremove->_next;
						if(toremove->data)
							_allocator->free(toremove->data);
						_allocator->destroy(toremove);
						toremove = f;
					}
					toremove = _avail_frames.dequeue();
					while(toremove)
					{
						::booldog::multimedia::video::frame* f = toremove->_next;
						if(toremove->data)
							_allocator->free(toremove->data);
						_allocator->destroy(toremove);
						toremove = f;
					}
#endif
					if(_filename)
						_allocator->free(_filename);
				}
				static bool open(::booldog::results::multimedia::video::capture* pres, ::booldog::allocator* allocator
					, const char* name, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::results::multimedia::video::capture locres;
					BOOINIT_RESULT(::booldog::results::multimedia::video::capture);
	#ifdef __LINUX__
					::booldog::result simpleres;
					struct v4l2_capability cap;
					int fd = -1;
					struct stat st;
					if(stat(name, &st) == -1)
					{
						res->seterrno();
						goto goto_return;
					}
					if(S_ISCHR(st.st_mode) == 0) 
					{
						res->booerr(::booldog::enums::result::booerr_type_file_is_not_character_device);
						goto goto_return;
					}
					fd = ::open(name, O_RDWR | O_NONBLOCK, 0);
					if(fd == -1)
					{
						res->seterrno();
						goto goto_return;
					}
					else
					{
						if(xioctl(fd, VIDIOC_QUERYCAP, &cap) == -1)
						{
							res->seterrno();
							goto goto_return;
						}
						if((cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0)
						{
							res->booerr(::booldog::enums::result::booerr_type_file_is_not_video_capture_device);
							goto goto_return;
						}
					}
	goto_return:
					if(res->succeeded())
					{
						res->video = allocator->create< ::booldog::multimedia::video::capture >(allocator, fd);
						if(res->video == 0)
						{
							res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
							return false;
						}
						if(::booldog::utils::string::mbs::assign<16>(&simpleres, allocator
							, true, 0, res->video->_filename
							, res->video->_filename_len, res->video->_filename_size
							, name, 0, SIZE_MAX, debuginfo))
							return true;
						else
						{
							res->copy(simpleres);
							return false;
						}
					}
					else
					{
						if(fd != -1)
							::close(fd);
						return false;
					}
#elif defined(__WINDOWS__)					
					HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
                    bool need_CoUninitialize = true;
                    bool _need_CoUninitialize = true;
                    if(hr == RPC_E_CHANGED_MODE)
                    {
                        need_CoUninitialize = false;
                        _need_CoUninitialize = false;
                        hr = S_OK;
                    }
					if(SUCCEEDED(hr))
					{
						IBindCtx* bind_ctx = 0;
						hr = CreateBindCtx(0, &bind_ctx);
						if(SUCCEEDED(hr))
						{
							IMoniker* moniker = 0;
							ULONG eaten = 0;

							::booldog::result_mbchar mbchar(allocator);
							size_t utf8len = strlen(name), srcbyteindex = 0;
							if(::booldog::utf8::toutf16< 16 >(mbchar, name, srcbyteindex, utf8len, debuginfo))
							{
								hr = MkParseDisplayName(bind_ctx, (wchar_t*)mbchar.mbchar, &eaten, &moniker);
								if(SUCCEEDED(hr))
								{
									IBaseFilter* base_filter = 0;
									hr = moniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&base_filter);
									if(SUCCEEDED(hr))
									{
										res->video = allocator->create< ::booldog::multimedia::video::capture >(allocator, base_filter);
										if(res->video)
										{
											res->video->_need_CoUninitialize = _need_CoUninitialize;
												need_CoUninitialize = false;
											::booldog::result simpleres;
											if(::booldog::utils::string::mbs::assign<16>(&simpleres, allocator
												, true, 0, res->video->_filename
												, res->video->_filename_len, res->video->_filename_size
												, name, 0, SIZE_MAX, debuginfo) == false)
											{
												allocator->destroy(res->video);
												base_filter->Release();
												res->copy(simpleres);
											}
										}
										else
										{
											base_filter->Release();
											res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
										}
									}
									else
										res->setHRESULT(hr);
									moniker->Release();
								}
								else
									res->setHRESULT(hr);
							}
							else
								res->copy(mbchar);
							bind_ctx->Release();
						}
						else
							res->setHRESULT(hr);
						if(res->succeeded() == false && need_CoUninitialize)
							CoUninitialize();
					}
					else
						res->setHRESULT(hr);
					return res->succeeded();
	#else
					allocator = allocator;
					name = name;
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
					return res->succeeded();
	#endif				
				}
			bool open(::booldog::result* pres, const char* name, const ::booldog::debug::info& debuginfo = debuginfo_macros)
			{
					debuginfo = debuginfo;
					::booldog::results::multimedia::video::capture locres;
					BOOINIT_RESULT(::booldog::result);
#ifdef __LINUX__
					::booldog::result simpleres;
					struct v4l2_capability cap;
					struct stat st;
					if(stat(name, &st) == -1)
					{
						int err = errno;
						printf("stat, errno %d\n", err);
							res->seterrno(err);
							goto goto_return;
					}
					if(S_ISCHR(st.st_mode) == 0)
					{
							res->booerr(::booldog::enums::result::booerr_type_file_is_not_character_device);
							goto goto_return;
					}
					_fd = ::open(name, O_RDWR | O_NONBLOCK, 0);
					if(_fd == -1)
					{
						int err = errno;
						printf("open, errno %d\n", err);
							res->seterrno(err);
							goto goto_return;
					}
					else
					{
							if(xioctl(_fd, VIDIOC_QUERYCAP, &cap) == -1)
							{
								int err = errno;
								printf("xioctl, errno %d\n", err);
									res->seterrno(err);
									goto goto_return;
							}
							if((cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0)
							{
									res->booerr(::booldog::enums::result::booerr_type_file_is_not_video_capture_device);
									goto goto_return;
							}
					}
	goto_return:
					if(res->succeeded())
					{
						if(_filename == name || ::booldog::utils::string::mbs::assign<16>(res, _allocator
																	, true, 0, _filename
																	, _filename_len, _filename_size
																	, name, 0, SIZE_MAX, debuginfo))
							return true;
						else
							return false;
					}
					else
					{
							if(_fd != -1)
							{
									::close(_fd);
								_fd = -1;
							}
							return false;
					}
#elif defined(__WINDOWS__)
					HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
                    bool need_CoUninitialize = true;
                    bool _need_CoUninitialize = true;
                    if(hr == RPC_E_CHANGED_MODE)
                    {
                        need_CoUninitialize = false;
                        _need_CoUninitialize = false;
                        hr = S_OK;
                    }
					if(SUCCEEDED(hr))
					{
						IBindCtx* bind_ctx = 0;
						hr = CreateBindCtx(0, &bind_ctx);
						if(SUCCEEDED(hr))
						{
							IMoniker* moniker = 0;
							ULONG eaten = 0;

							::booldog::result_mbchar mbchar(_allocator);
							size_t utf8len = strlen(name), srcbyteindex = 0;
							if(::booldog::utf8::toutf16< 16 >(mbchar, name, srcbyteindex, utf8len, debuginfo))
							{
								hr = MkParseDisplayName(bind_ctx, (wchar_t*)mbchar.mbchar, &eaten, &moniker);
								if(SUCCEEDED(hr))
								{
									hr = moniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&_base_filter);
									if(SUCCEEDED(hr))
									{
										if(_filename != name && ::booldog::utils::string::mbs::assign<16>(res, _allocator
											, true, 0, _filename
											, _filename_len, _filename_size
											, name, 0, SIZE_MAX, debuginfo) == false)
										{
											_base_filter->Release();
											_base_filter = 0;
										}
									}
									else
										res->setHRESULT(hr);
									moniker->Release();
								}
								else
									res->setHRESULT(hr);
							}
							else
								res->copy(mbchar);
							bind_ctx->Release();
						}
						else
							res->setHRESULT(hr);
						if(res->succeeded() == false && need_CoUninitialize)
							CoUninitialize();
					}
					else
						res->setHRESULT(hr);
					return res->succeeded();
#else
					name = name;
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
					return res->succeeded();
#endif
				}
				booinline bool available_formats(::booldog::result* pres, ::booldog::allocator* allocator
					, ::booldog::multimedia::video::typedefs::available_formats_callback_t callback, void* udata
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
	#ifdef __LINUX__
					v4l2_fmtdesc fmtdesc;
					fmtdesc.index = 0;
					fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
					bool next = true;
					v4l2_frmsizeenum framesizeenum;
					v4l2_frmivalenum v4l2frameivalenum;
					for(;;)
					{
						if(xioctl(_fd, VIDIOC_ENUM_FMT, &fmtdesc) != -1)
						{
							framesizeenum.index = 0;
							framesizeenum.pixel_format = fmtdesc.pixelformat;
							v4l2frameivalenum.pixel_format = fmtdesc.pixelformat;
							for(;;)
							{
								if(xioctl(_fd, VIDIOC_ENUM_FRAMESIZES, &framesizeenum) != -1)
								{
									if(framesizeenum.type == V4L2_FRMSIZE_TYPE_DISCRETE)
									{
										v4l2frameivalenum.index = 0;	
										v4l2frameivalenum.width = framesizeenum.discrete.width;
										v4l2frameivalenum.height = framesizeenum.discrete.height;
										for(;;)
										{
											if(xioctl(_fd, VIDIOC_ENUM_FRAMEINTERVALS, &v4l2frameivalenum) != -1)
											{
												if(v4l2frameivalenum.type == V4L2_FRMIVAL_TYPE_DISCRETE)
												{
													next = callback(allocator, udata, fmtdesc.pixelformat
														, framesizeenum.discrete.width, framesizeenum.discrete.height
														, v4l2frameivalenum.discrete.numerator
														, v4l2frameivalenum.discrete.denominator
														, (const char*)fmtdesc.description);												

													++v4l2frameivalenum.index;

													if(next == false)
														break;
												}
												else
												{
													next = callback(allocator, udata, fmtdesc.pixelformat
														, framesizeenum.discrete.width
														, framesizeenum.discrete.height, 0, 0
														, (const char*)fmtdesc.description);
													++v4l2frameivalenum.index;
													break;
												}
											}
											else
												break;
										}
										if(v4l2frameivalenum.index == 0)
										{
											next = callback(allocator, udata, fmtdesc.pixelformat, framesizeenum.discrete.width
												, framesizeenum.discrete.height, 0, 0, (const char*)fmtdesc.description);
											//char sfcc[5] = {0}; *((::booldog::uint32*)sfcc) = fmtdesc.pixelformat;										
										}
										++framesizeenum.index;
										if(next == false)
											break;
									}
									else
									{
										next = callback(allocator, udata, fmtdesc.pixelformat, 0, 0, 0, 0
											, (const char*)fmtdesc.description);
										++framesizeenum.index;
										break;
									}
								}
								else
									break;
							}
							if(framesizeenum.index == 0)
								next = callback(allocator, udata, fmtdesc.pixelformat, 640, 480, 0, 0
								, (const char*)fmtdesc.description);
						}
						else
							break;
						++fmtdesc.index;
						if(next == false)
							break;
					}
#elif defined(__WINDOWS__)
					IEnumPins* enum_pins = 0;
					HRESULT hr = _base_filter->EnumPins(&enum_pins);
					if(SUCCEEDED(hr))
					{
						IPin* pin = 0;
						while(enum_pins->Next(1, &pin, 0) == S_OK)
						{
							PIN_DIRECTION pin_direction = PINDIR_OUTPUT;
							hr = pin->QueryDirection(&pin_direction);
							if(SUCCEEDED(hr))
							{
								if(pin_direction == PINDIR_OUTPUT)
								{
									IEnumMediaTypes* enum_media_types = 0;
									hr = pin->EnumMediaTypes(&enum_media_types);
									if(SUCCEEDED(hr))
									{
										bool next = true;
										AM_MEDIA_TYPE* am_media_type = 0;
										while(enum_media_types->Next(1, &am_media_type, 0) == S_OK)
										{
											if(am_media_type->formattype == FORMAT_VideoInfo)
											{
												if(am_media_type->cbFormat >= sizeof(VIDEOINFOHEADER))
												{
													VIDEOINFOHEADER* videoinfoheader = 
														reinterpret_cast< VIDEOINFOHEADER* >(am_media_type->pbFormat);
													next = callback(allocator, udata, videoinfoheader->bmiHeader.biCompression
														, videoinfoheader->bmiHeader.biWidth, videoinfoheader->bmiHeader.biHeight
														, 1, (::booldog::uint32)(10000000LL / videoinfoheader->AvgTimePerFrame), "");
												}
											}
											else if(am_media_type->formattype == FORMAT_VideoInfo2)
											{
												if(am_media_type->cbFormat >= sizeof(VIDEOINFOHEADER2))
												{
													VIDEOINFOHEADER2* videoinfoheader = 
														reinterpret_cast< VIDEOINFOHEADER2* >(am_media_type->pbFormat);
													next = callback(allocator, udata, videoinfoheader->bmiHeader.biCompression
														, videoinfoheader->bmiHeader.biWidth, videoinfoheader->bmiHeader.biHeight
														, 1, (::booldog::uint32)(10000000LL / videoinfoheader->AvgTimePerFrame), "");
												}
											}
											if(am_media_type->cbFormat != 0)
												CoTaskMemFree((PVOID)am_media_type->pbFormat);
											if(am_media_type->pUnk != 0)
												am_media_type->pUnk->Release();
											CoTaskMemFree(am_media_type);
											am_media_type = 0;
											if(next == false)
												break;
										}
									}
									else
										res->setHRESULT(hr);
									pin->Release();
									break;
								}
							}
							else
							{
								res->setHRESULT(hr);
								pin->Release();
								break;
							}
							pin->Release();
						}
						enum_pins->Release();
					}
					else
						res->setHRESULT(hr);
#else
					allocator = allocator;
					callback = callback;
					udata = udata;
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
#endif
					return res->succeeded();
				}
				booinline bool stop_capturing(::booldog::result* pres, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
	#ifdef __LINUX__
                    if(_streaming)
                    {
                        enum v4l2_buf_type type;
                        switch (_capture_type)
                        {
                        case V4L2_MEMORY_USERPTR:
                            type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                            if(xioctl(_fd, VIDIOC_STREAMOFF, &type) == -1)
                            {
                                res->seterrno();
                            }
                            else
                            {
                                struct v4l2_requestbuffers req;
                                ::memset(&req, 0, sizeof(req));
                                req.count  = 0;
                                req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                req.memory = (v4l2_memory)_capture_type;
                                xioctl(_fd, VIDIOC_REQBUFS, &req);
                                _streaming = false;
                            }
                            break;
                        case V4L2_MEMORY_MMAP:
                                type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                if(xioctl(_fd, VIDIOC_STREAMOFF, &type) == -1)
                                {
                                    res->seterrno();
                                }
                                else
                                    _streaming = false;
                                break;
                        }
                    }
#elif defined(__WINDOWS__)
					if(_graph_builder)
					{
						IMediaControl* media_control = 0;
						HRESULT hr = _graph_builder->QueryInterface(IID_IMediaControl, (void**)&media_control);											
						if(SUCCEEDED(hr))
						{
							hr = media_control->Stop();
							media_control->Release();
						}
						_capture_graph_builder->Release();
						_capture_graph_builder = 0;
						_graph_builder->Release();
						_graph_builder = 0;
					}
	#else
					debuginfo = debuginfo;
	#endif
					return res->succeeded();
				}
				booinline bool start_capturing(::booldog::result* pres, ::booldog::uint32 fourcc, ::booldog::uint32 width
					, ::booldog::uint32 height, ::booldog::uint32 framerate_numerator, ::booldog::uint32 framerate_denominator
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);					
	#ifdef __LINUX__
					::booldog::multimedia::video::capture::buffer* pbuffer = 0;
					struct timespec uptime = {};
					enum v4l2_buf_type v4l2buftype;
					struct v4l2_buffer v4l2buf;
					struct v4l2_requestbuffers req;

					struct v4l2_capability cap;
					struct v4l2_cropcap cropcap;
					struct v4l2_crop crop;
					struct v4l2_format fmt;
					struct v4l2_streamparm v4l2streamparm;
					unsigned int min = 0;

                    bool reinit = false;
                    if(_fourcc != fourcc || _width != width || _height != height
                            || _framerate_numerator != framerate_numerator
                            || _framerate_denominator != framerate_denominator)
                        reinit = true;
                    if(reinit)
                    {
                        if(xioctl(_fd, VIDIOC_QUERYCAP, &cap) == -1)
                        {
                            int err = errno;
                            printf("xioctl %d, VIDIOC_QUERYCAP\n", err);
                                res->seterrno(err);
                                goto goto_return;
                        }
                        if(cap.capabilities & V4L2_CAP_STREAMING)
                        {
                            //if(fourcc == V4L2_PIX_FMT_MJPEG)
                                _capture_type = V4L2_MEMORY_MMAP;
                            //else
                            //_capture_type = V4L2_MEMORY_USERPTR;
                        }
                        else
                        {
                                _capture_type = 0;
                                if((cap.capabilities & V4L2_CAP_READWRITE) == false)
                                {
                                        res->booerr(::booldog::enums::result::booerr_type_video_capture_device_does_not_support_neither_streaming_nor_io);
                                        goto goto_return;
                                }
                        }
                        ::memset(&cropcap, 0, sizeof(cropcap));
                        cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                        if(xioctl(_fd, VIDIOC_CROPCAP, &cropcap) == 0)
                        {
                                crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                crop.c = cropcap.defrect;
                                if(xioctl(_fd, VIDIOC_S_CROP, &crop) == -1)
                                {
                                        switch (errno) {
                                        case EINVAL:
                                                /* Cropping not supported. */
                                                break;
                                        default:
                                                /* Errors ignored. */
                                                break;
                                        }
                                }
                        }
                        else
                        {
                                /* Errors ignored. */
                        }
                        ::memset(&fmt, 0, sizeof(fmt));
                        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                        fmt.fmt.pix.width = width;
                        fmt.fmt.pix.height = height;
                        fmt.fmt.pix.pixelformat = fourcc;
                        fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;//V4L2_FIELD_ANY
                        if(xioctl(_fd, VIDIOC_S_FMT, &fmt) == -1)
                        {
                            int err = errno;
                            printf("xioctl %d, VIDIOC_S_FMT\n", err);
                                res->seterrno(err);
                                goto goto_return;
                        }
                        min = fmt.fmt.pix.width * 2;
                        if(fmt.fmt.pix.bytesperline < min)
                                fmt.fmt.pix.bytesperline = min;
                        min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
                        if(fmt.fmt.pix.sizeimage < min)
                                fmt.fmt.pix.sizeimage = min;
                        _size = fmt.fmt.pix.sizeimage;

                        if(xioctl(_fd, VIDIOC_G_FMT, &fmt) == -1)
                        {
                            int err = errno;
                            printf("xioctl %d, VIDIOC_G_FMT\n", err);
                            res->seterrno(err);
                            goto goto_return;
                        }

                        _width = fmt.fmt.pix.width;
                        _height = fmt.fmt.pix.height;

                        if(framerate_numerator != 0 || framerate_denominator != 0)
                        {
                                ::memset(&v4l2streamparm, 0, sizeof(v4l2streamparm));
                                v4l2streamparm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                if(xioctl(_fd, VIDIOC_G_PARM, &v4l2streamparm) != -1)
                                {
                                        if((v4l2streamparm.parm.capture.capability & V4L2_CAP_TIMEPERFRAME))
                                        {
                                                v4l2streamparm.parm.capture.timeperframe.numerator = framerate_numerator;
                                                v4l2streamparm.parm.capture.timeperframe.denominator = framerate_denominator;
                                                if(xioctl(_fd, VIDIOC_S_PARM, &v4l2streamparm) == -1)
                                                {
                                                    int err = errno;
                                                    printf("xioctl %d, VIDIOC_S_PARM\n", err);
                                                        res->seterrno(err);
                                                        goto goto_return;
                                                }
                                        }
                                }
                                else
                                {
                                    int err = errno;
                                    printf("xioctl %d, VIDIOC_G_PARM\n", err);
                                        res->seterrno(err);
                                        goto goto_return;
                                }
                        }
                    }
                    else if(_fourcc != 0xffffffff)
                    {

                    }

                    if(_capture_type == V4L2_MEMORY_USERPTR)
                    {
                        //if(reinit)
                        {
                            ::memset(&req, 0, sizeof(req));

                            req.count  = sizeof(_buffers) / sizeof(_buffers[0]);
                            req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                            req.memory = V4L2_MEMORY_USERPTR;

                            if(xioctl(_fd, VIDIOC_REQBUFS, &req) == -1)
                            {
                                    int errnoval = errno;
                                    if(errnoval != EINVAL)
                                    {
                                        printf("xioctl %d, VIDIOC_REQBUFS\n", errnoval);
                                            res->seterrno(errnoval);
                                            goto goto_return;
                                    }
                                    else
                                            _capture_type = V4L2_MEMORY_MMAP;
                            }
                            else if(reinit)
                            {
                                    for(_buffers_count = 0 ; _buffers_count < (int)(sizeof(_buffers) / sizeof(_buffers[0])) ; ++_buffers_count)
                                    {
                                        pbuffer = &_buffers[_buffers_count];
                                            if(pbuffer->mmap)
                                            {
                                                    if(pbuffer->start)
                                                    {
                                                            munmap(pbuffer->start, pbuffer->length);
                                                            pbuffer->start = 0;
                                                            pbuffer->length = 0;
                                                    }
                                            }
                                            if(_size > pbuffer->length)
                                            {
                                                pbuffer->start = _allocator->realloc_array<char>((char*)pbuffer->start
                                                        , _size, debuginfo);
                                                if(pbuffer->start == 0)
                                                {
                                                        res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
                                                        goto goto_return;
                                                }
                                                pbuffer->mmap = false;
                                                pbuffer->length = _size;
                                            }
                                    }
                            }
                        }
                    }
                    if(_capture_type == V4L2_MEMORY_MMAP)
                    {
                        if(reinit)
                        {
                            ::memset(&req, 0, sizeof(req));

                            req.count = sizeof(_buffers) / sizeof(_buffers[0]);
                            req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                            req.memory = V4L2_MEMORY_MMAP;

                            if(xioctl(_fd, VIDIOC_REQBUFS, &req) == -1)
                            {
                                    int errnoval = errno;
                                    if(errnoval != EINVAL)
                                    {
                                        printf("xioctl %d, VIDIOC_REQBUFS\n", errnoval);
                                            res->seterrno(errnoval);
                                            goto goto_return;
                                    }
                                    else
                                            _capture_type = 0;
                            }
                            else
                            {
                                    if(req.count < 2)
                                    {
                                            res->booerr(::booldog::enums::result::booerr_type_insufficient_memory);
                                            goto goto_return;
                                    }

                                    for(_buffers_count = 0 ;_buffers_count < (int)req.count; ++_buffers_count)
                                    {
                                            ::memset(&v4l2buf, 0, sizeof(v4l2buf));

                                            v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                            v4l2buf.memory = V4L2_MEMORY_MMAP;
                                            v4l2buf.index = _buffers_count;

                                            if(xioctl(_fd, VIDIOC_QUERYBUF, &v4l2buf) == -1)
                                            {
                                                int err = errno;
                                                printf("xioctl %d, VIDIOC_QUERYBUF\n", err);
                                                    res->seterrno(err);
                                                    goto goto_return;
                                            }
                                            pbuffer = &_buffers[_buffers_count];
                                            if(pbuffer->mmap)
                                            {
                                                    if(pbuffer->start && (pbuffer->length != v4l2buf.length || pbuffer->offset != v4l2buf.m.offset))
                                                    {
                                                            munmap(pbuffer->start, pbuffer->length);
                                                            pbuffer->start = 0;
                                                            pbuffer->length = 0;
                                                    }
                                            }
                                            else
                                            {                                                                    
                                                    if(pbuffer->start)
                                                    {
                                                            _allocator->free(pbuffer->start);
                                                            pbuffer->start = 0;
                                                            pbuffer->length = 0;
                                                    }
                                            }
                                            if(pbuffer->start == 0)
                                            {
                                                _buffers[_buffers_count].start = mmap(0, v4l2buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, _fd
                                                        , v4l2buf.m.offset);
                                                if(_buffers[_buffers_count].start == MAP_FAILED)
                                                {
                                                        _buffers[_buffers_count].start = 0;
                                                        res->booerr(::booldog::enums::result::booerr_type_map_failed);
                                                        goto goto_return;
                                                }
                                                _buffers[_buffers_count].mmap = true;
                                                _buffers[_buffers_count].length = v4l2buf.length;
                                                _buffers[_buffers_count].offset = v4l2buf.m.offset;
                                            }
                                    }
                            }
                        }
                    }
                    if(_capture_type == 0)
                    {
                            if(_buffers[0].mmap)
                            {
                                    if(_buffers[0].start)
                                    {
                                            munmap(_buffers[0].start, _buffers[0].length);
                                            _buffers[0].start = 0;
                                            _buffers[0].length = 0;
                                    }
                            }
                            if(_size > _buffers[0].length)
                            {
                                _buffers[0].start = _allocator->realloc_array<char>((char*)_buffers[0].start
                                        , _size, debuginfo);
                                if(_buffers[0].start == 0)
                                {
                                        res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
                                        goto goto_return;
                                }
                                _buffers[0].mmap = false;
                                _buffers[0].length = _size;
                            }
                    }
                    switch(_capture_type)
                    {
                    case V4L2_MEMORY_USERPTR:
                            for(int index = 0;index < _buffers_count; ++index)
                            {
                                    ::memset(&v4l2buf, 0, sizeof(v4l2buf));
                                    v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                    v4l2buf.memory = V4L2_MEMORY_USERPTR;
                                    v4l2buf.index = index;
                                    v4l2buf.m.userptr = (unsigned long)_buffers[index].start;
                                    v4l2buf.length = _buffers[index].length;
                                    if(xioctl(_fd, VIDIOC_QBUF, &v4l2buf) == -1)
                                    {
                                        int err = errno;
                                        printf("xioctl %d, VIDIOC_QBUF\n", err);
                                            res->seterrno(err);
                                            goto goto_return;
                                    }
                            }
                            break;
                    case V4L2_MEMORY_MMAP:
                            for(int index = 0;index < _buffers_count; ++index)
                            {
                                    ::memset(&v4l2buf, 0, sizeof(v4l2buf));
                                    v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                                    v4l2buf.memory = V4L2_MEMORY_MMAP;
                                    v4l2buf.index = index;
                                    if(xioctl(_fd, VIDIOC_QBUF, &v4l2buf) == -1)
                                    {
                                        int err = errno;
                                        printf("xioctl %d, VIDIOC_QBUF\n", err);
                                            res->seterrno(err);
                                            goto goto_return;
                                    }
                            }
                            break;
                    default:
                            goto goto_return;
                    }
					v4l2buftype = V4L2_BUF_TYPE_VIDEO_CAPTURE;
					if(xioctl(_fd, VIDIOC_STREAMON, &v4l2buftype) == -1)
					{
                        int err = errno;
                        printf("xioctl %d, VIDIOC_STREAMON\n", err);
                            res->seterrno(err);
						goto goto_return;
					}					
					_timestamp = ::booldog::utils::time::posix::now_as_utc();					
					clock_gettime(CLOCK_MONOTONIC,&uptime);
					_last_tickcount = uptime.tv_sec * 1000000LL + uptime.tv_nsec / 1000LL;
					//_difference = 0;
	goto_return:
					if(res->succeeded())
					{
						_streaming = true;
						_width = width;
						_height = height;
						_fourcc = fourcc;
						_framerate_numerator = framerate_numerator;
						_framerate_denominator = framerate_denominator;
						return true;
					}
					return false;
#elif defined(__WINDOWS__)
					IGraphBuilder* graph_builder = 0;
					HRESULT hr = CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER, IID_IGraphBuilder
						, (void**)&graph_builder);
                                        if(hr == CO_E_NOTINITIALIZED)
                                        {
                                            hr = CoInitializeEx(0, COINIT_MULTITHREADED);
                                            if(SUCCEEDED(hr))
                                            {
                                                _need_CoUninitialize = true;
                                                return start_capturing(pres, fourcc, width, height, framerate_numerator
                                                                       , framerate_denominator, debuginfo);
                                            }
                                        }
					if(SUCCEEDED(hr))
					{
						ICaptureGraphBuilder2* capture_graph_builder = 0;
						hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, 0, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2
							, (void**)&capture_graph_builder);
						if(SUCCEEDED(hr))
						{
							hr = capture_graph_builder->SetFiltergraph(graph_builder);
							if(SUCCEEDED(hr))
							{
								hr = graph_builder->AddFilter(_base_filter, L"Capture Filter");
								if(SUCCEEDED(hr))
								{
									hr = graph_builder->AddFilter(this, L"Renderer Filter");
									if(SUCCEEDED(hr))
									{
										IAMStreamConfig* am_stream_config = 0;
                                        hr = capture_graph_builder->FindInterface(_is_preview ? &PIN_CATEGORY_PREVIEW : &PIN_CATEGORY_CAPTURE, 0, _base_filter
											, IID_IAMStreamConfig, (void**)&am_stream_config);
                                        if(FAILED(hr))
                                        {
                                            IEnumPins* enum_pins = 0;
                                            hr = _base_filter->EnumPins(&enum_pins);
                                            if(SUCCEEDED(hr))
                                            {
                                                IPin* pin = 0;
                                                while(enum_pins->Next(1, &pin, 0) == S_OK)
                                                {
                                                    PIN_DIRECTION pin_direction = PINDIR_OUTPUT;
                                                    hr = pin->QueryDirection(&pin_direction);
                                                    if(SUCCEEDED(hr))
                                                    {
                                                        if(pin_direction == PINDIR_OUTPUT)
                                                        {
                                                            hr = pin->QueryInterface(IID_IAMStreamConfig
                                                                                , (void**)&am_stream_config);
                                                            if(SUCCEEDED(hr))
                                                            {
                                                                pin->Release();
                                                                break;
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        pin->Release();
                                                        break;
                                                    }
                                                    pin->Release();
                                                }
                                                enum_pins->Release();
                                            }
                                        }

										if(SUCCEEDED(hr))
										{
											int count = 0, size = 0;
											hr = am_stream_config->GetNumberOfCapabilities(&count, &size);
											if(SUCCEEDED(hr))
											{
                                                VIDEO_STREAM_CONFIG_CAPS scc;
                                                AM_MEDIA_TYPE* am_media_type = 0;
                                                if(width == UINT32_MAX || height == UINT32_MAX)
                                                {
                                                    int max_index = -1;
                                                    LONG max_width = 0;
                                                    for(int index = 0;index < count;++index)
                                                    {
                                                        hr = am_stream_config->GetStreamCaps(index, &am_media_type, (BYTE*)&scc);
                                                        if(SUCCEEDED(hr))
                                                        {
                                                            if(am_media_type->formattype == FORMAT_VideoInfo)
                                                            {
                                                                if(am_media_type->cbFormat >= sizeof(VIDEOINFOHEADER))
                                                                {
                                                                    VIDEOINFOHEADER* videoinfoheader =
                                                                        reinterpret_cast< VIDEOINFOHEADER* >(am_media_type->pbFormat);
                                                                    if(videoinfoheader->bmiHeader.biCompression == fourcc)
                                                                    {
                                                                        if(videoinfoheader->bmiHeader.biWidth > max_width)
                                                                        {
                                                                            max_width = videoinfoheader->bmiHeader.biWidth;
                                                                            max_index = index;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            else if(am_media_type->formattype == FORMAT_VideoInfo2)
                                                            {
                                                                if(am_media_type->cbFormat >= sizeof(VIDEOINFOHEADER2))
                                                                {
                                                                    VIDEOINFOHEADER2* videoinfoheader =
                                                                        reinterpret_cast< VIDEOINFOHEADER2* >(am_media_type->pbFormat);
                                                                    if(videoinfoheader->bmiHeader.biCompression == fourcc)
                                                                    {
                                                                        if(videoinfoheader->bmiHeader.biWidth > max_width)
                                                                        {
                                                                            max_width = videoinfoheader->bmiHeader.biWidth;
                                                                            max_index = index;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            if(am_media_type->cbFormat != 0)
                                                                CoTaskMemFree((PVOID)am_media_type->pbFormat);
                                                            if(am_media_type->pUnk != 0)
                                                                am_media_type->pUnk->Release();
                                                            CoTaskMemFree(am_media_type);
                                                            am_media_type = 0;
                                                        }
                                                    }
                                                    if(max_index > -1)
                                                        am_stream_config->GetStreamCaps(max_index, &am_media_type, (BYTE*)&scc);
                                                }
                                                else
                                                {
                                                    for(int index = 0;index < count;++index)
                                                    {
                                                        hr = am_stream_config->GetStreamCaps(index, &am_media_type, (BYTE*)&scc);
                                                        if(SUCCEEDED(hr))
                                                        {
                                                            if(am_media_type->formattype == FORMAT_VideoInfo)
                                                            {
                                                                if(am_media_type->cbFormat >= sizeof(VIDEOINFOHEADER))
                                                                {
                                                                    VIDEOINFOHEADER* videoinfoheader =
                                                                        reinterpret_cast< VIDEOINFOHEADER* >(am_media_type->pbFormat);
                                                                    if(videoinfoheader->bmiHeader.biCompression == fourcc
                                                                        && videoinfoheader->bmiHeader.biWidth == (LONG)width
                                                                        && videoinfoheader->bmiHeader.biHeight == (LONG)height)
                                                                        break;
                                                                }
                                                            }
                                                            else if(am_media_type->formattype == FORMAT_VideoInfo2)
                                                            {
                                                                if(am_media_type->cbFormat >= sizeof(VIDEOINFOHEADER2))
                                                                {
                                                                    VIDEOINFOHEADER2* videoinfoheader =
                                                                        reinterpret_cast< VIDEOINFOHEADER2* >(am_media_type->pbFormat);
                                                                    if(videoinfoheader->bmiHeader.biCompression == fourcc
                                                                        && videoinfoheader->bmiHeader.biWidth == (LONG)width
                                                                        && videoinfoheader->bmiHeader.biHeight == (LONG)height)
                                                                        break;
                                                                }
                                                            }
                                                            if(am_media_type->cbFormat != 0)
                                                                CoTaskMemFree((PVOID)am_media_type->pbFormat);
                                                            if(am_media_type->pUnk != 0)
                                                                am_media_type->pUnk->Release();
                                                            CoTaskMemFree(am_media_type);
                                                            am_media_type = 0;
                                                        }
                                                    }
                                                }
												if(am_media_type)
												{	
													if(am_media_type->formattype == FORMAT_VideoInfo)
													{
														if(am_media_type->cbFormat >= sizeof(VIDEOINFOHEADER))
														{
															VIDEOINFOHEADER* videoinfoheader = 
																reinterpret_cast< VIDEOINFOHEADER* >(am_media_type->pbFormat);
															videoinfoheader->AvgTimePerFrame = 10000000LL / framerate_denominator;
														}
													}
													else if(am_media_type->formattype == FORMAT_VideoInfo2)
													{
														if(am_media_type->cbFormat >= sizeof(VIDEOINFOHEADER2))
														{
															VIDEOINFOHEADER2* videoinfoheader = 
																reinterpret_cast< VIDEOINFOHEADER2* >(am_media_type->pbFormat);
															videoinfoheader->AvgTimePerFrame = 10000000LL / framerate_denominator;
														}
													}											
													hr = am_stream_config->SetFormat(am_media_type);
													if(am_media_type->cbFormat != 0)
														CoTaskMemFree((PVOID)am_media_type->pbFormat);
													if(am_media_type->pUnk != 0)
														am_media_type->pUnk->Release();
													CoTaskMemFree(am_media_type);
													am_media_type = 0;
													if(SUCCEEDED(hr))
													{
                                                        hr = capture_graph_builder->RenderStream(_is_preview ? &PIN_CATEGORY_PREVIEW : &PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video
															, _base_filter, 0, this);
														if(SUCCEEDED(hr))
														{
															IMediaControl* media_control = 0;
															hr = graph_builder->QueryInterface(IID_IMediaControl
																, (void**)&media_control);											
															if(SUCCEEDED(hr))
															{
                                                                ::booldog::multimedia::video::frame* vframe = _frames.dequeue();
                                                                while(vframe)
                                                                {
                                                                    _avail_frames.enqueue(vframe);
                                                                    vframe = _frames.dequeue();
                                                                }
                                                                _timestamp = ::booldog::utils::time::posix::now_as_utc();
                                                                _last_tickcount = GetTickCount();
																hr = media_control->Run();
																if(SUCCEEDED(hr))
                                                                {
																	_graph_builder = graph_builder;
																	_capture_graph_builder = capture_graph_builder;
																}
																else
																{
																	capture_graph_builder->Release();
																	graph_builder->Release();
																	res->setHRESULT(hr);
																}
																media_control->Release();
															}
															else
															{
																capture_graph_builder->Release();
																graph_builder->Release();
																res->setHRESULT(hr);
															}
														}
														else
														{
															capture_graph_builder->Release();
															graph_builder->Release();
															res->setHRESULT(hr);
														}
													}
													else
													{
														capture_graph_builder->Release();
														graph_builder->Release();
														res->setHRESULT(hr);
													}
												}
												else
												{
													capture_graph_builder->Release();
													graph_builder->Release();
													res->booerr(::booldog::enums::result::booerr_type_video_format_is_not_supported);
												}
											}
											else
											{
												capture_graph_builder->Release();
												graph_builder->Release();
												res->setHRESULT(hr);
											}
											am_stream_config->Release();
										}
										else
										{
											capture_graph_builder->Release();
											graph_builder->Release();
											res->setHRESULT(hr);
										}
									}
									else
									{
										capture_graph_builder->Release();
										graph_builder->Release();
										res->setHRESULT(hr);
									}
								}
								else
								{
									capture_graph_builder->Release();
									graph_builder->Release();
									res->setHRESULT(hr);
								}
							}
							else
							{
								capture_graph_builder->Release();
								graph_builder->Release();
								res->setHRESULT(hr);
							}
						}
						else
						{
							graph_builder->Release();
							res->setHRESULT(hr);
						}
					}
					else
						res->setHRESULT(hr);
					return res->succeeded();
#else
					fourcc = fourcc;
					width = width;
					height = height;
					framerate_numerator = framerate_numerator;
					framerate_denominator = framerate_denominator;
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
					return res->succeeded();
#endif		
                }
                booinline bool is_capturing()
                {
#ifdef __LINUX__
                    return _streaming;
#elif defined(__WINDOWS__)
                    return _graph_builder != 0;
#else
                    return false;
#endif
                }
                booinline bool is_opened()
                {
#ifdef __LINUX__
                    return _fd != -1;
#elif defined(__WINDOWS__)
                    return _base_filter != 0;
#else
                    return false;
#endif
                }
				booinline bool is_frame_available(::booldog::result_bool* pres
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::result_bool locres;
					BOOINIT_RESULT(::booldog::result_bool);
        #ifdef __LINUX__
					for(;;)
					{
						fd_set fds;
						FD_ZERO(&fds);
						FD_SET(_fd, &fds);

						struct timeval tv;
						tv.tv_sec = 0;
						tv.tv_usec = 23333;

						int resint = select(_fd + 1, &fds, 0, 0, &tv);
                                                //_timestamp = ::booldog::utils::time::posix::now_as_utc();
						if(resint == -1)
						{
							resint = errno;
							if(resint == EINTR)
								continue;
							res->seterrno(resint);
						}
						else if(resint != 0)
                                                {
							struct timespec uptime = {};
							clock_gettime(CLOCK_MONOTONIC,&uptime);
							
							::booldog::uint64 new_last_tickcount = uptime.tv_sec * 1000000LL + uptime.tv_nsec / 1000LL;
							
							//printf("Frame diff " I64u "\n", new_last_tickcount - _last_tickcount);
							
							_timestamp += new_last_tickcount - _last_tickcount;
							
							_last_tickcount = new_last_tickcount;
						
							res->bres = true;
						}
						break;
					}
#elif defined(__WINDOWS__)
					debuginfo = debuginfo;
					res->bres = _frames.count() > 0;
#else
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
#endif
					return res->succeeded();
                                }
				booinline bool read_frame(::booldog::result* pres
					, ::booldog::multimedia::video::typedefs::read_frame_callback_t callback, void* udata
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
	#ifdef __LINUX__
					//struct timespec ts = {};
					::booldog::multimedia::video::frame vframe;
					int index = 0;
					struct v4l2_buffer v4l2buf;
					switch(_capture_type)
					{
					case V4L2_MEMORY_USERPTR:
						::memset(&v4l2buf, 0, sizeof(v4l2buf));

						v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
						v4l2buf.memory = V4L2_MEMORY_USERPTR;

						if(xioctl(_fd, VIDIOC_DQBUF, &v4l2buf) == -1)
						{
                            int err = errno;
                            if(err != EIO)
                            {
                                printf("xioctl VIDIOC_DQBUF, %d\n", err);
                                res->seterrno(err);
							return false;
                                                    }
						}					
						for(;index < _buffers_count;++index)
						{
							if(v4l2buf.m.userptr == (unsigned long)_buffers[index].start
								&& v4l2buf.length == _buffers[index].length)
								break;
						}
						if(index < _buffers_count)
						{
							vframe.fourcc = _fourcc;
							vframe.width = _width;
							vframe.height = _height;
							vframe.data = (::booldog::byte*)v4l2buf.m.userptr;
							vframe.size = (::booldog::uint32)v4l2buf.bytesused;

                                                        /*switch( v4l2buf.flags & V4L2_BUF_FLAG_TIMESTAMP_MASK )
                                                        {
                                                            case V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC:
                                                            {
                                                                struct timespec uptime = {};
                                                                clock_gettime(CLOCK_MONOTONIC,&uptime);
                                                                timestamp = ::booldog::utils::time::posix::now_as_utc();

                                                                ::booldog::int64 now = uptime.tv_sec * 1000000LL + uptime.tv_nsec / 1000LL;
                                                                ::booldog::int64 frame_now = v4l2buf.timestamp.tv_sec * 1000000LL + v4l2buf.timestamp.tv_usec;
                                                                if(now >= frame_now && now - frame_now < 100000)
                                                                    _difference = now - frame_now;
                                                                printf("v4l2 diff " I64u "(" I64d " " I64u " " I64u ")\n", _difference, now - frame_now, now, timestamp);
								if(_last_timestamp < timestamp - _difference)
									timestamp -= _difference;
								else
									timestamp = _last_timestamp;
								
                                                                //float const secs =
                                                                //    (v4l2buf.timestamp.tv_sec - uptime.tv_sec) +
                                                                 //   (v4l2buf.timestamp.tv_usec - uptime.tv_nsec/1000.0f)/1000.0f;

                                                                //if( V4L2_BUF_FLAG_TSTAMP_SRC_SOE == (v4l2buf.flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK) )
                                                                 //   printf("%s: frame exposure started %.03f seconds ago\n",__FUNCTION__,-secs);
                                                                //else if( V4L2_BUF_FLAG_TSTAMP_SRC_EOF == (v4l2buf.flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK) )
                                                                 //   printf("%s: frame finished capturing %.03f seconds ago\n",__FUNCTION__,-secs);
                                                                //else printf("%s: unsupported timestamp in frame\n",__FUNCTION__);

                                                                break;
                                                            }

                                                            case V4L2_BUF_FLAG_TIMESTAMP_UNKNOWN:
                                                            case V4L2_BUF_FLAG_TIMESTAMP_COPY:
                                                            default:
								printf("%s: unknown timestamp\n",__FUNCTION__);
								
								struct timespec uptime = {};
                                                                clock_gettime(CLOCK_REALTIME,&uptime);
								float const secs =
                                                                    (v4l2buf.timestamp.tv_sec - uptime.tv_sec) +
                                                                    (v4l2buf.timestamp.tv_usec - uptime.tv_nsec/1000.0f)/1000.0f;
								if( V4L2_BUF_FLAG_TSTAMP_SRC_SOE == (v4l2buf.flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK) )
                                                                    printf("%s: frame exposure started %.03f seconds ago\n",__FUNCTION__,-secs);
                                                                else if( V4L2_BUF_FLAG_TSTAMP_SRC_EOF == (v4l2buf.flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK) )
                                                                    printf("%s: frame finished capturing %.03f seconds ago\n",__FUNCTION__,-secs);
                                                                else printf("%s: unsupported timestamp in frame\n",__FUNCTION__);
								
								if(_last_timestamp < timestamp - _difference)
									timestamp -= _difference;
								else
									timestamp = _last_timestamp;
                                                        }*/
                                                        //printf("sequence %u\n", v4l2buf.sequence);

                                                        /*if(_difference == 0)
							{
								_difference = v4l2buf.timestamp.tv_sec * 1000000ULL + v4l2buf.timestamp.tv_usec;
								if(v4l2buf.flags & V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC)
								{
									clock_gettime(CLOCK_MONOTONIC, &ts);
									_difference = ts.tv_sec * 1000000LL + (ts.tv_nsec / 1000ULL) - _difference;
									//printf("%d(%x) MONOTONIC(" I64u ", " I64u ", " I64u ")\n", index, v4l2buf.flags, (::booldog::uint64)v4l2buf.timestamp.tv_sec, (::booldog::uint64)v4l2buf.timestamp.tv_usec, _difference);
								}
								else
								{
									clock_gettime(CLOCK_REALTIME, &ts);
									_difference = ts.tv_sec * 1000000LL + (ts.tv_nsec / 1000ULL) - _difference;
								}
                                                        }
                                                        timestamp -= _difference;*/

							/*timestamp = v4l2buf.timestamp.tv_sec * 1000000ULL + v4l2buf.timestamp.tv_usec;
							if(v4l2buf.flags & V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC)
							{
							printf("%d(%x) MONOTONIC(" I64u ", " I64u ")\n", index, v4l2buf.flags, (::booldog::uint64)v4l2buf.timestamp.tv_sec, (::booldog::uint64)v4l2buf.timestamp.tv_usec);
								clock_gettime(CLOCK_MONOTONIC, &ts);
								timestamp = ts.tv_sec * 1000000LL + (ts.tv_nsec / 1000ULL) - timestamp;						
								timestamp = ::booldog::utils::time::posix::now_as_utc() - timestamp;
							}
							else
							printf("UNKNOWN(" I64u ", " I64u ")\n", (::booldog::uint64)v4l2buf.timestamp.tv_sec, (::booldog::uint64)v4l2buf.timestamp.tv_usec);*/
							vframe.timestamp = _timestamp;	
							callback(_allocator, udata, &vframe);
						}
						if(xioctl(_fd, VIDIOC_QBUF, &v4l2buf) == -1)
						{
                                                    int err = errno;
                                                    printf("xioctl %d, VIDIOC_QBUF\n", err);
                                                        res->seterrno(err);
							return false;
						}
						break;
					case V4L2_MEMORY_MMAP:

						::memset(&v4l2buf, 0, sizeof(v4l2buf));

						v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
						v4l2buf.memory = V4L2_MEMORY_MMAP;

						if(xioctl(_fd, VIDIOC_DQBUF, &v4l2buf) == -1)
						{
                                                    int err = errno;
                                                    printf("xioctl %d, VIDIOC_DBUF\n", err);
                                                        res->seterrno(err);
							return false;
						}
						//timestamp = ::booldog::utils::time::posix::now_as_utc();
						vframe.fourcc = _fourcc;
						vframe.width = _width;
						vframe.height = _height;
						vframe.data = (::booldog::byte*)_buffers[v4l2buf.index].start;
						vframe.size = (::booldog::uint32)v4l2buf.bytesused;
						/*timestamp = v4l2buf.timestamp.tv_sec * 1000000ULL + v4l2buf.timestamp.tv_usec;
						if(v4l2buf.flags & V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC)
						{
						printf("MONOTONIC(" I64u ", " I64u ")\n", (::booldog::uint64)v4l2buf.timestamp.tv_sec, (::booldog::uint64)v4l2buf.timestamp.tv_usec);
							clock_gettime(CLOCK_MONOTONIC, &ts);
							timestamp = ts.tv_sec * 1000000LL + ( ts.tv_nsec / 1000ULL ) - timestamp;						
							timestamp = ::booldog::utils::time::posix::now_as_utc() - timestamp;
						}
						else
						printf("UNKNOWN(" I64u ", " I64u ")\n", (::booldog::uint64)v4l2buf.timestamp.tv_sec, (::booldog::uint64)v4l2buf.timestamp.tv_usec);*/
						vframe.timestamp = _timestamp;
						callback(_allocator, udata, &vframe);
						if(xioctl(_fd, VIDIOC_QBUF, &v4l2buf) == -1)
						{
                                                    int err = errno;
                                                    printf("xioctl %d, VIDIOC_QBUF\n", err);
                                                        res->seterrno(err);
							return false;
						}
						break;
					default:
						if(read(_fd, _buffers[0].start, _buffers[0].length) == -1)
						{
							res->seterrno();
							return false;
						}
						//timestamp = ::booldog::utils::time::posix::now_as_utc();
						vframe.fourcc = _fourcc;
						vframe.width = _width;
						vframe.height = _height;
						vframe.data = (::booldog::byte*)_buffers[0].start;
						vframe.size = (::booldog::uint32)_buffers[0].length;
						vframe.timestamp =_timestamp;
					
						callback(_allocator, udata, &vframe);
						break;
					}
					//_last_timestamp = vframe.timestamp;
#elif defined(__WINDOWS__)
					::booldog::multimedia::video::frame* vframe = _frames.dequeue();
					if(vframe)
					{
						callback(_allocator, udata, vframe);
						_avail_frames.enqueue(vframe);
					}
					else
						res->booerr(::booldog::enums::result::booerr_type_video_capture_device_has_not_frame_yet);
	#else
					callback = callback;
					udata = udata;
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
	#endif
					return res->succeeded();
				}
				booinline bool close(::booldog::result* pres, bool destroy, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT( ::booldog::result );
	#ifdef __LINUX__
					if(_fd != -1)
					{
						if(_capture_type == V4L2_MEMORY_MMAP)
						{
							for(_buffers_count = 0 ; _buffers_count < (int)(sizeof(_buffers) / sizeof(_buffers[0])) ; ++_buffers_count)
							{
									if(_buffers[_buffers_count].start)
									{
											if(_buffers[_buffers_count].mmap)
											{
													munmap(_buffers[_buffers_count].start, _buffers[_buffers_count].length);
													_buffers[_buffers_count].start = 0;
													_buffers[_buffers_count].length = 0;
											}
									}
							}
						}
						if(::close(_fd) == -1)
						{
							int err = errno;
							printf("close, %d\n", err);
							res->seterrno(err);
							return false;
						}
					}
#elif defined(__WINDOWS__)
					stop_capturing(res, debuginfo);
					if(_base_filter)
					{
						_base_filter->Release();
						_base_filter = 0;
						if(_need_CoUninitialize)
							CoUninitialize();
					}
#else
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
#endif
                    if(destroy)
                        _allocator->destroy(this);
                    else
                    {
#ifdef __LINUX__
						_fd = -1;
#else
#endif
						_fourcc = 0xffffffff;
					}
					return res->succeeded();
				}
	#ifdef __LINUX__
				struct listdir_callback_info
				{
					::booldog::result* res;
					::booldog::result_mbchar mbchar;
					struct v4l2_capability capability;
					::booldog::multimedia::video::typedefs::available_cameras_callback_t callback;
					void* udata;
					listdir_callback_info(::booldog::allocator* allocator
						, ::booldog::multimedia::video::typedefs::available_cameras_callback_t pcallback, void* pudata)
						: mbchar(allocator), callback(pcallback), udata(pudata)
					{
					}
				};
				static bool listdir_callback(::booldog::allocator* allocator, void* udata, const char* pathname
					, const char* entry_name, ::booldog::enums::io::entry_type entry_type)
				{
					if(entry_type == ::booldog::enums::io::character_device)
					{
						listdir_callback_info* info = (listdir_callback_info*)udata;
						if(::booldog::utils::string::mbs::assign<16>(info->res, allocator, false, 0, info->mbchar.mbchar
							, info->mbchar.mblen, info->mbchar.mbsize, pathname, 0, SIZE_MAX))
						{
							if(::booldog::utils::string::mbs::assign<16>(info->res, allocator, false, info->mbchar.mblen
								, info->mbchar.mbchar, info->mbchar.mblen, info->mbchar.mbsize, entry_name, 0, SIZE_MAX))
							{
								bool next = true;
								int fd = ::open(info->mbchar.mbchar, O_RDWR | O_NONBLOCK, 0);
								if(fd != -1)
								{						
									memset(&info->capability, 0, sizeof(info->capability));
									if(xioctl(fd, VIDIOC_QUERYCAP, &info->capability) != -1)
									{
										if(info->capability.capabilities & V4L2_CAP_VIDEO_CAPTURE)
										{
											const char* name = info->mbchar.mbchar;
											if(info->capability.card && info->capability.card[0])
												name = (const char*)info->capability.card;
											::close(fd);
											fd = -1;
											next = info->callback(allocator, info->udata, name, info->mbchar.mbchar
												, info->capability.capabilities);
										}
									}
									if(fd != -1)
										::close(fd);
								}
								return next;
							}
							else
								return false;
						}
						else
							return false;
					}
					return true;
                }
	#endif
				static bool available_cameras(::booldog::result* pres, ::booldog::allocator* allocator
					, ::booldog::multimedia::video::typedefs::available_cameras_callback_t callback, void* udata
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
#ifdef __LINUX__
					listdir_callback_info info(allocator, callback, udata);
					info.res = res;
					::booldog::io::directory::mbs::listdir(res, allocator, "/dev/", listdir_callback, &info, debuginfo);
#elif defined(__WINDOWS__)
					HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
					if(SUCCEEDED(hr))
					{
						IEnumMoniker* enum_moniker = 0;
						
						ICreateDevEnum* dev_enum = 0;
						hr = CoCreateInstance(CLSID_SystemDeviceEnum, 0, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&dev_enum));
						if(SUCCEEDED(hr))
						{
							hr = dev_enum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &enum_moniker, 0);
							if(hr == S_FALSE)
							{
								hr = VFW_E_NOT_FOUND;
								res->setHRESULT(hr);
							}
							else if(SUCCEEDED(hr))
							{
								IMalloc* pmalloc = 0;
								hr = CoGetMalloc(1, &pmalloc);
								if(SUCCEEDED(hr))
								{
									::booldog::result_mbchar name(allocator), deviceid(allocator);
									IMoniker* moniker = 0;
									while(enum_moniker->Next(1, &moniker, 0) == S_OK)
									{
										IPropertyBag* property_bag = 0;
										hr = moniker->BindToStorage(0, 0, IID_PPV_ARGS(&property_bag));
										if(FAILED(hr))
										{
											moniker->Release();
											continue;
										}
										VARIANT var;
										VariantInit(&var);

										hr = property_bag->Read(L"Description", &var, 0);
										if(FAILED(hr))
											hr = property_bag->Read(L"FriendlyName", &var, 0);
										if(SUCCEEDED(hr))
										{
											size_t wlen = wcslen(var.bstrVal), srcbyteindex = 0;
											if(::booldog::utf16::toutf8< 16 >(name, (char*)var.bstrVal, srcbyteindex
												, wlen * sizeof(wchar_t), debuginfo) == false)
											{
												res->copy(name);
												VariantClear(&var);
												property_bag->Release();
												moniker->Release();
												break;
											}
											VariantClear(&var);
										}
										else
										{
											res->setHRESULT(hr);
											property_bag->Release();
											moniker->Release();
											break;
										}
										property_bag->Release();

										IBindCtx* bind_ctx = 0;
										hr = CreateBindCtx(0, &bind_ctx);
										if(SUCCEEDED(hr))
										{
											LPOLESTR moniker_display_name = 0;
											hr = moniker->GetDisplayName(bind_ctx, 0, &moniker_display_name);
											if(SUCCEEDED(hr))
											{
												if(moniker_display_name)
												{
													size_t wlen = wcslen(moniker_display_name), srcbyteindex = 0;
													if(::booldog::utf16::toutf8< 16 >(deviceid, (char*)moniker_display_name
														, srcbyteindex, wlen * sizeof(wchar_t), debuginfo) == false)
													{
														res->copy(deviceid);

														pmalloc->Free(moniker_display_name);

														bind_ctx->Release();

														moniker->Release();
														break;
													}
													pmalloc->Free(moniker_display_name);
												}
											}
											else
											{
												res->setHRESULT(hr);
												bind_ctx->Release();
												moniker->Release();
												break;
											}
											bind_ctx->Release();
										}
										else
										{
											res->setHRESULT(hr);
											moniker->Release();
											break;
										}									
										moniker->Release();
										if(callback(allocator, udata, name.mbchar, deviceid.mbchar, 0) == false)
											break;
									}
									pmalloc->Release();
								}
								else
									res->setHRESULT(hr);
								enum_moniker->Release();
							}
							else
								res->setHRESULT(hr);
							dev_enum->Release();
						}
						else
							res->setHRESULT(hr);
						CoUninitialize();
					}
					else
						res->setHRESULT(hr);
#else
					allocator = allocator;
					callback = callback;
					udata = udata;
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
#endif
					return res->succeeded();
                }
                booinline const char* name(void)
                {
                    return _filename;
                }
			};
		}
	}
}
#endif
