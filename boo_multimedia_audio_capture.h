/** class capture
* Simplify work with audio capture
* Linux(sudo apt-get install libasound2-dev, sudo yum install TODO, libraries: asound)
* Windows(libraries: Ole32 OleAut32 strmiids)
* Linux name example: hw:0
*/
#ifndef BOO_MULTIMEDIA_AUDIO_CAPTURE_H
#define BOO_MULTIMEDIA_AUDIO_CAPTURE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_multimedia_audio_frame.h"
#include "boo_multimedia_enums.h"
#include "boo_error.h"
#include "boo_result.h"
#include "boo_time_utils.h"

#include "boo_fps_counter.h"
#ifdef __LINUX__
#include <alsa/asoundlib.h>
#elif defined(__WINDOWS__)
#include <DShow.h>

#include "boo_utf16.h"
#include "boo_utf8.h"

#pragma comment(lib, "Ole32")
#pragma comment(lib, "OleAut32")
#pragma comment(lib, "strmiids")
#endif
#include <stdio.h>
namespace booldog
{
	namespace multimedia
	{
		namespace audio
		{
			class capture;
                }
        }
	namespace results
	{
		namespace multimedia
		{
			namespace audio
			{
				class capture : public ::booldog::result
				{
				private:
					capture(const ::booldog::result&)
					{
                                        }
					capture(const ::booldog::results::multimedia::audio::capture&)
                                            : result()
					{
                                        }
					::booldog::results::multimedia::audio::capture& operator = 
						(const ::booldog::results::multimedia::audio::capture&)
					{
						return *this;
                                        }
				public:
					::booldog::multimedia::audio::capture* audio;
                    capture()
						: audio(0)
                    {
                    }
                    virtual ~capture()
					{
                                        }
                    virtual void clear() const
					{
						::booldog::results::multimedia::audio::capture* _obj_ 
							= const_cast< ::booldog::results::multimedia::audio::capture* >(this);
	#ifdef __UNIX__
						_obj_->dlerrorclear();
	#endif
						_obj_->error_type = ::booldog::enums::result::error_type_no_error;
						_obj_->audio = 0;
					}
				};
			}
		}
	}
	namespace multimedia
	{		
		namespace audio
		{
			namespace typedefs
			{
				typedef bool (*available_capture_devices_callback_t)(::booldog::allocator* allocator, void* udata, const char* name
					, const char* deviceid, ::booldog::uint32 capabilities);
				typedef bool (*available_formats_callback_t)(::booldog::allocator* allocator, void* udata
					, ::booldog::uint32 fourcc, ::booldog::uint32 sample_rate, ::booldog::uint32 channels
					, ::booldog::uint32 bytes_per_sample, const char* description);
				typedef void (*read_frame_callback_t)(::booldog::allocator* allocator, void* udata, ::booldog::multimedia::audio::frame* aframe);
			}
			class capture
#ifdef __WINDOWS__
				: public IBaseFilter
#endif
			{	
				friend class ::booldog::allocator;
			private:
#ifdef __WINDOWS__
				::booldog::data::lockfree::queue< ::booldog::multimedia::audio::frame > _frames;
				::booldog::data::lockfree::queue< ::booldog::multimedia::audio::frame > _avail_frames;
				class pin : public IPin, public IMemInputPin
				{
				private:
					IPin* _connected;
					::booldog::multimedia::audio::capture* _filter;
					IMemAllocator* _mem_allocator;
					BYTE _mem_allocator_read_only;
				public:
					pin(::booldog::multimedia::audio::capture* filter)
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
						if(pmt->formattype == FORMAT_WaveFormatEx)
						{
							if(pmt->cbFormat >= sizeof(WAVEFORMATEX))
							{
								WAVEFORMATEX* waveformatex = 
									reinterpret_cast< WAVEFORMATEX* >(pmt->pbFormat);
								_filter->_fourcc = waveformatex->wFormatTag;
								_filter->_bytes_per_sample = waveformatex->wBitsPerSample / 8;
								_filter->_channels = waveformatex->nChannels;
								_filter->_sample_rate = waveformatex->nSamplesPerSec;
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
                        bool timestamp_inited = false;
                        if(_filter->_timestamp)
                        {
                            _filter->_timestamp = ::booldog::utils::time::posix::now_as_utc();
                            timestamp_inited = true;
                        }
						AM_MEDIA_TYPE* am_media_type = 0;
						if(pSample->GetMediaType(&am_media_type) == S_OK)
						{
							if(am_media_type->formattype == FORMAT_WaveFormatEx)
							{
								if(am_media_type->cbFormat >= sizeof(WAVEFORMATEX))
								{
									WAVEFORMATEX* waveformatex = 
										reinterpret_cast< WAVEFORMATEX* >(am_media_type->pbFormat);
									_filter->_fourcc = waveformatex->wFormatTag;
									_filter->_bytes_per_sample = waveformatex->wBitsPerSample / 8;
									_filter->_channels = waveformatex->nChannels;
									_filter->_sample_rate = waveformatex->nSamplesPerSec;
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
							::booldog::multimedia::audio::frame* vframe = 0;
							if(_filter->_frames.count() >= 5)
								vframe = _filter->_frames.dequeue();
							if(vframe == 0)
								vframe = _filter->_avail_frames.dequeue();
							if(vframe == 0)
								vframe = _filter->_allocator->create< ::booldog::multimedia::audio::frame >(debuginfo_macros);
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
								vframe->bytes_per_sample = _filter->_bytes_per_sample;
								vframe->channels = _filter->_channels;
								vframe->sample_rate = _filter->_sample_rate;
								vframe->size = frame_size;
                                if(timestamp_inited)
                                    _filter->_timestamp -= ((1000000ULL * (frame_size / (_filter->_bytes_per_sample * _filter->_channels))) / _filter->_sample_rate);
                                vframe->timestamp = _filter->_timestamp;
								::memcpy(vframe->data, buffer, frame_size);
                                _filter->_frames.enqueue(vframe);
                                _filter->_timestamp += (1000000ULL * (frame_size / (_filter->_bytes_per_sample * _filter->_channels))) / _filter->_sample_rate;
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
						return E_NOTIMPL;
					}
				};
				class enum_pins : public IEnumPins
				{
					private:
						const ULONG _pins_count;
						ULONG _position;
						::booldog::multimedia::audio::capture* _capture;
						::booldog::interlocked::atomic _refs;
					public:
						enum_pins(::booldog::multimedia::audio::capture* pcapture)
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
							::booldog::multimedia::audio::capture::enum_pins* clone = 
								_capture->_allocator->create< ::booldog::multimedia::audio::capture::enum_pins >(_capture
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
				bool _snd_pcm_started;
				::booldog::counters::fps _boofps;
			
				::booldog::allocator* _allocator;
#ifdef __LINUX__
				snd_pcm_t* _snd_pcm;
#endif
				int _bytes_per_sample;
				unsigned int _channels;
#ifdef __LINUX__
				snd_pcm_uframes_t _buffer_frames;
#endif
				char* _buffer;
#ifdef __LINUX__
				struct pollfd* _ufds;
				unsigned int _ufds_count;
#endif
				::booldog::uint32 _buffer_size;
				::booldog::uint32 _fourcc;
				::booldog::uint64 _timestamp;
				::booldog::uint32 _sample_rate;
#ifdef __WINDOWS__
				IBaseFilter* _base_filter;
				ICaptureGraphBuilder2* _capture_graph_builder;
				IGraphBuilder* _graph_builder;
				IReferenceClock* _reference_clock;
				IFilterGraph* _filter_graph;
				IMediaEventSink* _media_event_sink;
				::booldog::multimedia::audio::capture::pin* _pin;
				FILTER_STATE _filter_state;
				bool _need_CoUninitialize;
#endif
				char* _filename;
				size_t _filename_len;
				size_t _filename_size;
                bool _capturing;
			private:
				capture(::booldog::allocator* allocator, ::booldog::typedefs::tickcount ptickcount
#ifdef __LINUX__
					, snd_pcm_t* snd_pcm
#elif defined(__WINDOWS__)
					, IBaseFilter* pbase_filter
#endif
					)
					: _boofps(ptickcount), _allocator(allocator)
#ifdef __LINUX__
					, _snd_pcm(snd_pcm), _buffer_frames(0)
#endif
					, _buffer(0)
#ifdef __LINUX__
					, _ufds(0)
#endif
					, _sample_rate(44100)
#ifdef __WINDOWS__
					, _base_filter(pbase_filter), _capture_graph_builder(0), _graph_builder(0), _reference_clock(0)
					, _filter_graph(0), _media_event_sink(0), _filter_state(State_Paused)
#endif
                    , _filename(0), _filename_len(0), _filename_size(0), _capturing(false)
				{
#ifdef __WINDOWS__
					_pin = _allocator->create< ::booldog::multimedia::audio::capture::pin >(this, debuginfo_macros);
#endif
				}
				capture(const ::booldog::multimedia::audio::capture&)
					: _boofps(0)
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
					::booldog::multimedia::audio::capture::enum_pins* clone = 
						_allocator->create< ::booldog::multimedia::audio::capture::enum_pins >(this, debuginfo_macros);
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
                    ppPin = ppPin;
					return E_NOTIMPL;
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
				::booldog::multimedia::audio::capture& operator = (const ::booldog::multimedia::audio::capture&)
				{
					return *this;
				}
			public:				
				~capture(void)
				{
#ifdef __LINUX__
					if(_ufds)
						_allocator->free(_ufds);
#elif defined(__WINDOWS__)
					_allocator->destroy(_pin);                                        
					::booldog::multimedia::audio::frame* toremove = _frames.dequeue();
					while(toremove)
					{
						::booldog::multimedia::audio::frame* f = toremove->_next;
						if(toremove->data)
							_allocator->free(toremove->data);
						_allocator->destroy(toremove);
						toremove = f;
					}
					toremove = _avail_frames.dequeue();
					while(toremove)
					{
						::booldog::multimedia::audio::frame* f = toremove->_next;
						if(toremove->data)
							_allocator->free(toremove->data);
						_allocator->destroy(toremove);
						toremove = f;
					}
#endif
					if(_buffer)
						_allocator->free(_buffer);
					if(_filename)
						_allocator->free(_filename);
				}
                bool open(::booldog::result* pres, const char* name, const ::booldog::debug::info& debuginfo = debuginfo_macros)
                {
                    debuginfo = debuginfo;
                    ::booldog::result locres;
                    BOOINIT_RESULT(::booldog::result);
#ifdef __LINUX__
                    int err = snd_pcm_open(&_snd_pcm, name, SND_PCM_STREAM_CAPTURE, 0);
                    if(err < 0)
                    {
                        res->setalsaerror(err);
                        return false;
                    }
                    else
                    {
                        if(_filename == name || ::booldog::utils::string::mbs::assign<16>(res, _allocator
							, true, 0, _filename, _filename_len, _filename_size, name, 0, SIZE_MAX, debuginfo))
                            return true;
                        else
                        {
                            snd_pcm_close(_snd_pcm);
                            _snd_pcm = 0;
                            res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
                            return false;
						}
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
				static bool open(::booldog::results::multimedia::audio::capture* pres, ::booldog::allocator* allocator, ::booldog::typedefs::tickcount ptickcount
					, const char* name, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::results::multimedia::audio::capture locres;
					BOOINIT_RESULT(::booldog::results::multimedia::audio::capture);
	#ifdef __LINUX__
					snd_pcm_t* snd_pcm = 0;
					int err = snd_pcm_open(&snd_pcm, name, SND_PCM_STREAM_CAPTURE, 0);
					if(err < 0)
					{
						res->setalsaerror(err);
						return false;
					}
					else
					{
						res->audio = allocator->create< ::booldog::multimedia::audio::capture >(allocator, ptickcount, snd_pcm, debuginfo);
						if(res->audio == 0)
						{
							snd_pcm_close(snd_pcm);
							res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
							return false;
						}
						return true;
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
										res->audio = allocator->create< ::booldog::multimedia::audio::capture >(allocator, ptickcount
											, base_filter, debuginfo);
										if(res->audio)
										{
											res->audio->_need_CoUninitialize = _need_CoUninitialize;
												need_CoUninitialize = false;
											::booldog::result simpleres;
											if(::booldog::utils::string::mbs::assign<16>(&simpleres, allocator
												, true, 0, res->audio->_filename
												, res->audio->_filename_len, res->audio->_filename_size
												, name, 0, SIZE_MAX, debuginfo) == false)
											{
												allocator->destroy(res->audio);
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
                booinline bool close(::booldog::result* pres, bool destroy
                                     , const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
#ifdef __LINUX__
					int err = snd_pcm_close(_snd_pcm);
					if(err < 0)
						res->setalsaerror(err);
                    _snd_pcm = 0;
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
					return res->succeeded();
                }
				booinline bool stop_capturing(::booldog::result* pres, const ::booldog::debug::info& debuginfo = debuginfo_macros)
                {
                    debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
#ifdef __LINUX__                    
                    if(_snd_pcm_started)
                    {
                        int err = snd_pcm_drop(_snd_pcm);
                        if(err < 0)
                        {
                            res->setalsaerror(err);
                            return false;
                        }
                        _snd_pcm_started = false;
                    }
                    _capturing = false;
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
#endif
					return true;
				}
				booinline bool start_capturing(::booldog::result* pres, ::booldog::uint32 fourcc, ::booldog::uint32 sample_rate
					, ::booldog::uint32 channels, ::booldog::uint32 bytes_per_sample
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					fourcc = fourcc;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
#ifdef __LINUX__
                    unsigned int min_channels = 0, max_channels = 0, buffer_time = 0;
                    _sample_rate = sample_rate;
					_snd_pcm_started = false;
					_bytes_per_sample = 0;
                                        _channels = channels;
					_timestamp = 0;
					//snd_pcm_uframes_t buffer_size = 0;
					
					int dir = 0;
                                        _buffer_frames = 0;
                                        snd_pcm_uframes_t buffer_frames = 8 * _buffer_frames;
					
                                        unsigned int rate = _sample_rate;
					snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;
					switch(bytes_per_sample)
					{
					case 1:
						format = SND_PCM_FORMAT_S8;
						break;
					case 3:
						format = SND_PCM_FORMAT_S24_LE;
						break;
					case 4:
						format = SND_PCM_FORMAT_S32_LE;
						break;
					}
					//snd_pcm_format_t format = SND_PCM_FORMAT_FLOAT_LE;

                                        snd_pcm_sw_params_t* sw_params = 0;
					snd_pcm_hw_params_t* hw_params = 0;
					int err = snd_pcm_hw_params_malloc(&hw_params);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));
						res->setalsaerror(err);
						goto goto_return;
					}
					err = snd_pcm_hw_params_any(_snd_pcm, hw_params);
					if(err < 0)
					{
										printf("%d, error %s\n", __LINE__, snd_strerror(err));
						res->setalsaerror(err);
						goto goto_return;
					}
					err = snd_pcm_hw_params_set_access(_snd_pcm, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
					}
					err = snd_pcm_hw_params_set_format(_snd_pcm, hw_params, format);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
					}
					err = snd_pcm_hw_params_set_rate_near(_snd_pcm, hw_params, &rate, 0);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
                                        }
					
					err = snd_pcm_hw_params_test_channels(_snd_pcm, hw_params, _channels);
					if(err < 0)
					{
						err = snd_pcm_hw_params_get_channels_min(hw_params, &min_channels);
						if(err < 0)
						{
						printf("%d, error %s\n", __LINE__, snd_strerror(err));					
							res->setalsaerror(err);
							goto goto_return;
						}
						err = snd_pcm_hw_params_get_channels_max(hw_params, &max_channels);
						if(err < 0)
						{
						printf("%d, error %s\n", __LINE__, snd_strerror(err));					
							res->setalsaerror(err);
							goto goto_return;
						}		
						for(unsigned int i = min_channels;i <= max_channels; ++i) 
						{
							if(snd_pcm_hw_params_test_channels(_snd_pcm, hw_params, i) == 0)
								printf("channels %u\n", i);
						}						
					}
					else
					{					
						err = snd_pcm_hw_params_set_channels(_snd_pcm, hw_params, _channels);
						if(err < 0)
						{
						printf("%d, error %s\n", __LINE__, snd_strerror(err));					
							res->setalsaerror(err);
							goto goto_return;
						}
					}
                                        if(_buffer_frames == 0)
                                        {
                                            err = snd_pcm_hw_params_get_buffer_time_max(hw_params, &buffer_time, &dir);
                                            if(err < 0)
                                            {
                                                printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                    res->setalsaerror(err);
                                                    goto goto_return;
                                            }
                                            if(buffer_time > 500000)
                                                buffer_time = 500000;

                                            err = snd_pcm_hw_params_set_buffer_time_near(_snd_pcm, hw_params, &buffer_time, &dir);
                                            if(err < 0)
                                            {
                                                printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                    res->setalsaerror(err);
                                                    goto goto_return;
                                            }
                                            buffer_time /= 4;
                                            err = snd_pcm_hw_params_set_period_time_near(_snd_pcm, hw_params, &buffer_time, &dir);
                                            if(err < 0)
                                            {
                                                printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                    res->setalsaerror(err);
                                                    goto goto_return;
                                            }
                                        }
                                        else
                                        {
                                            err = snd_pcm_hw_params_set_period_size_near(_snd_pcm, hw_params, &_buffer_frames, &dir);
                                            if(err < 0)
                                            {
                                            printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                    res->setalsaerror(err);
                                                    goto goto_return;
                                            }

                                            err = snd_pcm_hw_params_set_buffer_size_near(_snd_pcm, hw_params, &buffer_frames);
                                            if(err < 0)
                                            {
                                            printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                    res->setalsaerror(err);
                                                    goto goto_return;
                                            }
                                        }

					err = snd_pcm_hw_params(_snd_pcm, hw_params);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
                                        }
					
					err = snd_pcm_hw_params_get_sbits(hw_params);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
					}
					_bytes_per_sample = err / 8;
                                        printf("bytes per sample %d\n", err);
					
					err = snd_pcm_hw_params_get_channels(hw_params, &_channels); 
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
					}
					printf("channels %u\n", _channels);
					
                                        err = snd_pcm_hw_params_get_buffer_size(hw_params, &buffer_frames);
                                        if(err < 0)
                                        {
                                                res->setalsaerror(err);
                                                goto goto_return;
                                        }
                                        printf("buffer size %u\n", (::booldog::uint32)buffer_frames);

					err = snd_pcm_hw_params_get_period_size(hw_params, &_buffer_frames, &dir);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
					}
					printf("period size %u\n", (::booldog::uint32)_buffer_frames);

                                        err = snd_pcm_hw_params_get_rate(hw_params, &_sample_rate, &dir);
                                        if(err < 0)
                                        {
                                        printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                res->setalsaerror(err);
                                                goto goto_return;
                                        }
                                        printf("sample rate %u\n", _sample_rate);




                                        err = snd_pcm_sw_params_malloc(&sw_params);
                                        if(err < 0)
                                        {
                                        printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                res->setalsaerror(err);
                                                goto goto_return;
                                        }

                                        err = snd_pcm_sw_params_current(_snd_pcm, sw_params);
                                        if(err < 0)
                                        {
                                        printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                res->setalsaerror(err);
                                                goto goto_return;
                                        }

                                        err = snd_pcm_sw_params_set_avail_min(_snd_pcm, sw_params, _buffer_frames);
                                        if(err < 0)
                                        {
                                        printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                res->setalsaerror(err);
                                                goto goto_return;
                                        }

                                        err = snd_pcm_sw_params_set_start_threshold(_snd_pcm, sw_params, 0);
                                        if(err < 0)
                                        {
                                        printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                res->setalsaerror(err);
                                                goto goto_return;
                                        }

                                        /*err = snd_pcm_sw_params_set_xfer_align(_snd_pcm, sw_params, 1);
                                        if(err < 0)
                                        {
                                        printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                res->setalsaerror(err);
                                                goto goto_return;
                                        }*/


                                        err = snd_pcm_sw_params(_snd_pcm, sw_params);
                                        if(err < 0)
                                        {
                                        printf("%d, error %s\n", __LINE__, snd_strerror(err));
                                                res->setalsaerror(err);
                                                goto goto_return;
                                        }


					
					_buffer_size = _buffer_frames * _bytes_per_sample * _channels;
					_buffer = _allocator->realloc_array< char >(_buffer, _buffer_size, debuginfo);
					if(_buffer == 0)
					{
										printf("%d, error %s\n", __LINE__, snd_strerror(err));
						res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
						goto goto_return;
					}
						
					_ufds_count = snd_pcm_poll_descriptors_count(_snd_pcm);
					
					printf("ufds count %u\n", (::booldog::uint32)_ufds_count);
					
					_ufds = _allocator->realloc_array< struct pollfd >(_ufds, _ufds_count, debuginfo);
					if(_ufds == 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
						goto goto_return;
					}
						
					err = snd_pcm_poll_descriptors(_snd_pcm, _ufds, _ufds_count);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
					}
					
					err = snd_pcm_prepare(_snd_pcm);
					if(err < 0)
					{
					printf("%d, error %s\n", __LINE__, snd_strerror(err));					
						res->setalsaerror(err);
						goto goto_return;
                    }
                    _capturing = true;
goto_return:
					if(hw_params)
						snd_pcm_hw_params_free(hw_params);
                                        if(sw_params)
                                                snd_pcm_sw_params_free(sw_params);
					return res->succeeded();
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
                            return start_capturing(pres, fourcc, sample_rate, channels, bytes_per_sample, debuginfo);
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
										hr = capture_graph_builder->FindInterface(&PIN_CATEGORY_CAPTURE, 0, _base_filter
											, IID_IAMStreamConfig, (void**)&am_stream_config);
										if(SUCCEEDED(hr))
										{
											int count = 0, size = 0;
											hr = am_stream_config->GetNumberOfCapabilities(&count, &size);
											if(SUCCEEDED(hr))
											{
												WORD wFormatTag = WAVE_FORMAT_PCM;
												switch(fourcc)
												{
												case ::booldog::enums::multimedia::audio::PCM:
													wFormatTag = WAVE_FORMAT_PCM;
													break;
												}
												AUDIO_STREAM_CONFIG_CAPS scc;
												AM_MEDIA_TYPE* am_media_type = 0;
												for(int index = 0;index < count;++index)
												{
													hr = am_stream_config->GetStreamCaps(index, &am_media_type, (BYTE*)&scc);
													if(SUCCEEDED(hr))
													{
														if(am_media_type->formattype == FORMAT_WaveFormatEx)
														{
															if(am_media_type->cbFormat >= sizeof(WAVEFORMATEX))
															{
																WAVEFORMATEX* waveformatex = 
																	reinterpret_cast< WAVEFORMATEX* >(am_media_type->pbFormat);
																if(waveformatex->wFormatTag == wFormatTag 
																	&& waveformatex->nChannels == channels
																	&& waveformatex->nSamplesPerSec == sample_rate
																	&& waveformatex->wBitsPerSample == 8 * bytes_per_sample)
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
												if(am_media_type)
												{						
													hr = am_stream_config->SetFormat(am_media_type);
													if(am_media_type->cbFormat != 0)
														CoTaskMemFree((PVOID)am_media_type->pbFormat);
													if(am_media_type->pUnk != 0)
														am_media_type->pUnk->Release();
													CoTaskMemFree(am_media_type);
													am_media_type = 0;
													if(SUCCEEDED(hr))
													{
                                                        IAMBufferNegotiation* am_buffer_negotiation = 0;
                                                        if(SUCCEEDED(_base_filter->QueryInterface(IID_IAMBufferNegotiation, (void**)&am_buffer_negotiation)))
                                                        {
                                                            ALLOCATOR_PROPERTIES props;
                                                            props.cbAlign = -1;
                                                            props.cbBuffer = (sample_rate * bytes_per_sample * channels) / 4;
                                                            props.cbPrefix = -1;
                                                            props.cBuffers = -1;
                                                            am_buffer_negotiation->SuggestAllocatorProperties(&props);
                                                            am_buffer_negotiation->Release();
                                                        }

														hr = capture_graph_builder->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Audio
															, _base_filter, 0, this);
														if(SUCCEEDED(hr))
														{
															IMediaControl* media_control = 0;
															hr = graph_builder->QueryInterface(IID_IMediaControl
																, (void**)&media_control);											
															if(SUCCEEDED(hr))
															{
                                                                ::booldog::multimedia::audio::frame* vframe = _frames.dequeue();
                                                                while(vframe)
                                                                {
                                                                    _avail_frames.enqueue(vframe);
                                                                    vframe = _frames.dequeue();
                                                                }
                                                                _timestamp = 0;
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

					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);					
					return res->succeeded();
#endif
                }
				booinline bool is_frame_available(::booldog::result_bool* pres
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
					debuginfo = debuginfo;
					::booldog::result_bool locres;
					BOOINIT_RESULT(::booldog::result_bool);
	#ifdef __LINUX__
					int resint = 0;
					unsigned short revents = 0;
					if(_snd_pcm_started == false)
					{
						int err = snd_pcm_start(_snd_pcm);						
                                                if(err >= 0)
                                                    _snd_pcm_started = true;
						else
						{
							res->setalsaerror(err);
							goto goto_return;
						}
					}
					for(;;)
                                        {
                                                resint = ::poll(_ufds, _ufds_count, 40);
						if(resint == -1)
						{
							printf("poll error %d\n", resint);
							resint = errno;
							if(resint == EINTR || resint == EAGAIN)
								continue;
							res->seterrno(resint);
						}
						else if(resint != 0)
						{
							revents = 0;
							resint = snd_pcm_poll_descriptors_revents(_snd_pcm, _ufds, _ufds_count, &revents);
							if(resint == 0)
							{
								if (revents & POLLIN)
                                                                {
                                                                    if(_timestamp == 0)
                                                                        _timestamp = ::booldog::utils::time::posix::now_as_utc();
									//avail_frames = snd_pcm_avail_update(_snd_pcm);
									//printf("avail audio frames %u\n", (unsigned int)avail_frames);									
								
									res->bres = true;
								}
							}
							else
								res->setalsaerror(resint);
                                                }
						break;
					}
goto_return:
#elif defined(__WINDOWS__)
					debuginfo = debuginfo;
					res->bres = _frames.count() > 0;
#else
					debuginfo = debuginfo;
					res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
#endif
					return res->succeeded();
                }
                booinline bool read_frame(::booldog::result* pres, ::booldog::allocator* allocator, ::booldog::multimedia::audio::frame* aframe
                        , const ::booldog::debug::info& debuginfo = debuginfo_macros)
                {
                    ::booldog::result locres;
                    BOOINIT_RESULT(::booldog::result);
#ifdef __LINUX__
					allocator = allocator;
					debuginfo = debuginfo;
					::booldog::uint32 buffer_frames = _buffer_frames;
					::booldog::byte* data = aframe->data;
					while(buffer_frames > 0)
					{
						int rc = snd_pcm_readi(_snd_pcm, data, buffer_frames);
						if(rc == -EAGAIN)
							continue;
						else if(rc == -EPIPE)
						{
								int err = snd_pcm_avail(_snd_pcm);
								printf("overrun occurred(%d)\n", err);

								err = snd_pcm_prepare(_snd_pcm);
								if(err < 0)
										res->setalsaerror(err);
								continue;
						}
						else if(rc == -ESTRPIPE)
						{
							for(;;)
							{
								rc = snd_pcm_resume(_snd_pcm);
								if(rc != -EAGAIN)
									break;
							}
							if(rc < 0)
							{
								rc = snd_pcm_prepare(_snd_pcm);
								if(rc < 0)
										res->setalsaerror(rc);
							}
							continue;
						}
						else if(rc < 0)
						{
								printf("snd_pcm_readi error %d\n", rc);
								res->setalsaerror(rc);
								return false;
						}
						if(_timestamp == 0)
							_timestamp = ::booldog::utils::time::posix::now_as_utc();
						::booldog::uint32 readen_bytes = rc * _bytes_per_sample * _channels;
						buffer_frames -= rc;
						data += readen_bytes;
					}
					aframe->fourcc = 0;
					aframe->bytes_per_sample = _bytes_per_sample;
					aframe->channels = _channels;
					aframe->sample_rate = _sample_rate;
					aframe->size = _buffer_size;
					aframe->timestamp = _timestamp;
					_timestamp += (1000000ULL * _buffer_frames) / _sample_rate;
					return true;
#elif defined(__WINDOWS__)
					::booldog::multimedia::audio::frame* vframe = _frames.dequeue();
					if(vframe)
					{
						if(vframe->alloc_size > aframe->alloc_size)
                        {
                            aframe->alloc_size = vframe->alloc_size;
                            aframe->data = allocator->realloc_array< ::booldog::byte >(aframe->data, aframe->alloc_size, debuginfo);
                            if(aframe->data == 0)
                            {
                                    res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
									_avail_frames.enqueue(vframe);
                                    return false;
                            }
                        }
						aframe->fourcc = vframe->fourcc;
						aframe->bytes_per_sample = vframe->bytes_per_sample;
						aframe->channels = vframe->channels;
						aframe->sample_rate = vframe->sample_rate;
						aframe->size = vframe->size;
						aframe->timestamp = vframe->timestamp;
						::memcpy(aframe->data, vframe->data, vframe->size);						
						_avail_frames.enqueue(vframe);
						return true;
					}
					else
					{
						res->booerr(::booldog::enums::result::booerr_type_video_capture_device_has_not_frame_yet);
						return false;
					}
#else
                    aframe = aframe;
                    debuginfo = debuginfo;
                    res->booerr(::booldog::enums::result::booerr_type_method_is_not_implemented_yet);
                    return res->succeeded();
#endif
                }
				booinline bool read_frame(::booldog::result* pres
					, ::booldog::multimedia::audio::typedefs::read_frame_callback_t callback, void* udata
					, const ::booldog::debug::info& debuginfo = debuginfo_macros)
				{
#ifdef __WINDOWS__
                    debuginfo = debuginfo;
					::booldog::result locres;
					BOOINIT_RESULT(::booldog::result);
					::booldog::multimedia::audio::frame* vframe = _frames.dequeue();
					if(vframe)
					{
						callback(_allocator, udata, vframe);
						_avail_frames.enqueue(vframe);
						return true;
					}
					else
					{
						res->booerr(::booldog::enums::result::booerr_type_video_capture_device_has_not_frame_yet);
						return false;
					}
#else
                    ::booldog::multimedia::audio::frame aframe;
                    aframe.data = (::booldog::byte*)_buffer;
                    if(read_frame(pres, _allocator, &aframe,debuginfo))
                    {
                        callback(_allocator, udata, &aframe);
                        return true;
                    }
                    else
                        return false;
#endif
                }
                booinline bool prepare_frame(::booldog::result* pres, ::booldog::allocator* allocator
                        , ::booldog::multimedia::audio::frame* aframe
                        , const ::booldog::debug::info& debuginfo = debuginfo_macros)
                {
                    ::booldog::result locres;
                    BOOINIT_RESULT(::booldog::result);
                    if(_buffer_size > aframe->alloc_size)
                    {
                        aframe->alloc_size = _buffer_size;
                        aframe->data = allocator->realloc_array< ::booldog::byte >(aframe->data, aframe->alloc_size, debuginfo);
                        if(aframe->data == 0)
                        {
                                res->booerr(::booldog::enums::result::booerr_type_cannot_alloc_memory);
                                return false;
                        }
                    }
                    return true;
                }
                static bool available_capture_devices(::booldog::result* pres, ::booldog::allocator* allocator
                    , ::booldog::multimedia::audio::typedefs::available_capture_devices_callback_t callback
                    , void* udata, const ::booldog::debug::info& debuginfo = debuginfo_macros)
                {
                    ::booldog::result locres;
                    BOOINIT_RESULT(::booldog::result);
#ifdef __WINDOWS__
                    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
                    if(SUCCEEDED(hr))
                    {
                        IEnumMoniker* enum_moniker = 0;

                        ICreateDevEnum* dev_enum = 0;
                        hr = CoCreateInstance(CLSID_SystemDeviceEnum, 0, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&dev_enum));
                        if(SUCCEEDED(hr))
                        {
                            hr = dev_enum->CreateClassEnumerator(CLSID_AudioInputDeviceCategory, &enum_moniker, 0);
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
                booinline bool available_formats(::booldog::result* pres, ::booldog::allocator* allocator
                    , ::booldog::multimedia::audio::typedefs::available_formats_callback_t callback, void* udata
                    , const ::booldog::debug::info& debuginfo = debuginfo_macros)
                {
                    debuginfo = debuginfo;
                    ::booldog::result locres;
                    BOOINIT_RESULT(::booldog::result);
#ifdef __WINDOWS__
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
                                            if(am_media_type->formattype == FORMAT_WaveFormatEx)
                                            {
                                                if(am_media_type->cbFormat >= sizeof(WAVEFORMATEX))
                                                {
                                                    WAVEFORMATEX* waveformatex =
                                                        reinterpret_cast< WAVEFORMATEX* >(am_media_type->pbFormat);
													::booldog::uint32 fourcc = 0;
													switch(waveformatex->wFormatTag)
													{
													case WAVE_FORMAT_PCM:
														fourcc = ::booldog::enums::multimedia::audio::PCM;
														break;
													default:
														fourcc = (::booldog::uint32)::booldog::enums::multimedia::audio::Unknown;
														break;
													}

                                                    next = callback(allocator, udata, fourcc
                                                        , waveformatex->nSamplesPerSec, waveformatex->nChannels
                                                        , waveformatex->wBitsPerSample / 8, "");
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
                booinline const char* name(void)
                {
                    return _filename;
                }
                booinline bool is_capturing()
                {
#ifdef __WINDOWS__
                    return _graph_builder != 0;
#else
                    return _capturing;
#endif
                }
                booinline bool is_opened()
                {
#ifdef __LINUX__
                    return _snd_pcm != 0;
#elif defined(__WINDOWS__)
                    return _base_filter != 0;
#else
                    return false;
#endif
                }
            };
        }
    }
}
#endif
