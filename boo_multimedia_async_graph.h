#ifndef BOO_MULTIMEDIA_ASYNC_GRAPH_H
#define BOO_MULTIMEDIA_ASYNC_GRAPH_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_multimedia_graph_chain.h"
#include "boo_doubly_linked_list.h"
#include "boo_thread.h"
#include "boo_lockfree_queue.h"

#include <stdio.h>
namespace booldog
{
	namespace multimedia
	{
		namespace async
		{
			class graph
			{
			private:
				::booldog::allocator* _allocator;
				::booldog::threading::thread* _thread;
				::booldog::data::doubly_linked_list< ::booldog::multimedia::graph_chain > _video_chains;
				::booldog::data::doubly_linked_list< ::booldog::multimedia::graph_chain > _audio_chains;

				::booldog::data::lockfree::queue< ::booldog::multimedia::video::frame > _video_frames;
				::booldog::data::lockfree::queue< ::booldog::multimedia::video::frame > _avail_video_frames;

				::booldog::data::lockfree::queue< ::booldog::multimedia::audio::frame > _audio_frames;
				::booldog::data::lockfree::queue< ::booldog::multimedia::audio::frame > _avail_audio_frames;

                                bool _free_chains;
				void* _udata;
                        public:
                                ::booldog::multimedia::async::graph* volatile _next;
			public:
				graph(::booldog::allocator* allocator)
                                        : _allocator(allocator), _thread(0), _free_chains(false), _udata(0)
				{
                                }
				~graph(void)
				{
					for(;;)
					{
						::booldog::multimedia::video::frame* next = _video_frames.dequeue();
						if(next)
						{
							if(next->data)
								_allocator->free(next->data);
							_allocator->destroy(next);
						}
						else
							break;
					}
					for(;;)
					{
						::booldog::multimedia::video::frame* next = _avail_video_frames.dequeue();
						if(next)
						{
							if(next->data)
								_allocator->free(next->data);
							_allocator->destroy(next);
						}
						else
							break;
					}
					for(;;)
					{
						::booldog::multimedia::audio::frame* next = _audio_frames.dequeue();
						if(next)
						{
							if(next->data)
								_allocator->free(next->data);
							_allocator->destroy(next);
						}
						else
							break;
					}
					for(;;)
					{
						::booldog::multimedia::audio::frame* next = _avail_audio_frames.dequeue();
						if(next)
						{
							if(next->data)
								_allocator->free(next->data);
							_allocator->destroy(next);
						}
						else
							break;
					}
                                        if(_free_chains)
                                        {
                                            ::booldog::multimedia::graph_chain* chain = _video_chains.first();
                                            while(chain)
                                            {
                                                 ::booldog::multimedia::graph_chain* toremove = _audio_chains.first();
                                                while(toremove)
                                                {
                                                    ::booldog::multimedia::graph_chain* cmp = toremove;
                                                    toremove = cmp->_doubly_linked_list_next;
                                                    if(cmp == chain)
                                                        _audio_chains.remove(cmp);
                                                }
                                                toremove = chain;
                                                chain = chain->_doubly_linked_list_next;
                                                _allocator->destroy(toremove);
                                            }
                                            chain = _audio_chains.first();
                                            while(chain)
                                            {
                                                ::booldog::multimedia::graph_chain* toremove = chain;
                                                chain = chain->_doubly_linked_list_next;
                                                _allocator->destroy(toremove);
                                            }
                                        }
				}
				booinline void* udata( void )
				{
					return _udata;
				}
				booinline void udata(void* pudata)
				{
					_udata = pudata;
				}
                                booinline ::booldog::multimedia::graph_chain* first_video_chain(void)
                                {
                                    return _video_chains.first();
                                }
                                booinline ::booldog::multimedia::graph_chain* first_audio_chain(void)
                                {
                                    return _audio_chains.first();
                                }
                                booinline void free_chains(bool val)
                                {
                                    _free_chains = val;
                                }
				booinline void add_video_chain(::booldog::multimedia::graph_chain* chain)
				{
					_video_chains.add(chain);
                                }
				booinline void add_audio_chain(::booldog::multimedia::graph_chain* chain)
				{
					_audio_chains.add(chain);
                                }
                                booinline bool is_started(void)
                                {
                                    return _thread != 0;
                                }
				booinline void stop(void)
				{
					if(_thread)
					{
						::booldog::threading::thread::stop(_thread);
						::booldog::threading::thread::wait_for_stop(_thread);
						::booldog::threading::thread::destroy(_thread);
						_thread = 0;
					}
                                }
				booinline bool stopped(void)
				{
					return _thread == 0 || _thread->stopped();
				}
                                booinline void stop_async(void)
                                {
                                        if(_thread)
                                                ::booldog::threading::thread::stop(_thread);
                                }
			private:
				static void onvideoframe(void* owner, void* owner_data, ::booldog::multimedia::video::frame* frame)				{					::booldog::multimedia::async::graph* graph = 						(::booldog::multimedia::async::graph*)owner;
					::booldog::multimedia::graph_chain* chain = 
						(::booldog::multimedia::graph_chain*)owner_data;					chain = chain->_doubly_linked_list_next;					if(chain)						chain->onvideoframe(graph, chain, onvideoframe, frame);				};
				static void onaudioframe(void* owner, void* owner_data, ::booldog::multimedia::audio::frame* frame)				{					::booldog::multimedia::async::graph* graph = 						(::booldog::multimedia::async::graph*)owner;
					::booldog::multimedia::graph_chain* chain = 
						(::booldog::multimedia::graph_chain*)owner_data;					chain = chain->_doubly_linked_list_next;					if(chain)						chain->onaudioframe(graph, chain, onaudioframe, frame);				};
				static void thread(::booldog::threading::thread* thread)
				{
					::booldog::multimedia::async::graph* graph = 
						(::booldog::multimedia::async::graph*)thread->udata();
					for(;;)
					{
						bool iscontinue = false;
						{							
							::booldog::multimedia::video::frame* f = graph->_video_frames.dequeue();
							if(f)
							{
								::booldog::multimedia::graph_chain* chain = graph->_video_chains.first();
								chain->onvideoframe(graph, chain, onvideoframe, f);
                                                                if(thread->pending_in_stop() || graph->_video_frames.count() >= 140)
                                                                {
									if(f->data)
										graph->_allocator->free(f->data);
									graph->_allocator->destroy(f);
								}
                                                                else
									graph->_avail_video_frames.enqueue(f);
								iscontinue = true;
							}
						}
						{							
							::booldog::multimedia::audio::frame* f = graph->_audio_frames.dequeue();
							if(f)
							{
								::booldog::multimedia::graph_chain* chain = graph->_audio_chains.first();
								chain->onaudioframe(graph, chain, onaudioframe, f);
                                                                if(thread->pending_in_stop() || graph->_audio_frames.count() >= 140)
                                                                {
                                                                        if(f->data)
                                                                                graph->_allocator->free(f->data);
                                                                        graph->_allocator->destroy(f);
                                                                }
                                                                else
									graph->_avail_audio_frames.enqueue(f);
								iscontinue = true;
							}
						}
						if(iscontinue)
							continue;
						if(graph->_video_frames.count() == 0 && graph->_audio_frames.count() == 0 && thread->pending_in_stop())
							break;
						::booldog::threading::sleep(1);
					}
                                        {
                                            ::booldog::multimedia::graph_chain* chain = graph->_video_chains.first();
                                            while(chain)
                                            {
                                                chain->deinitialize();
                                                chain = chain->_doubly_linked_list_next;
                                            }
                                            chain = graph->_audio_chains.first();
                                            while(chain)
                                            {
                                                chain->deinitialize();
                                                chain = chain->_doubly_linked_list_next;
                                            }
                                        }
                                }
			public:
				booinline void start(void)
				{
                                        _thread = ::booldog::threading::thread::create(0, _allocator, 30 * 1024, 0, 0, thread, this);
                                }
				booinline bool onvideoframe(::booldog::multimedia::video::frame* vframe)
				{
					::booldog::multimedia::video::frame* f = _avail_video_frames.dequeue();
					if(f == 0)
					{
						if(_video_frames.count() >= 140)
						{
                                                        //printf("video %d >= 140\n", (int)_video_frames.count());
                                                        //printf("avail video frames %d\n", (int)_avail_video_frames.count());
						}
						f = _allocator->create< ::booldog::multimedia::video::frame >();
					}					
					if(f->alloc_size < vframe->size + 64)
					{
						f->alloc_size = vframe->size + 64;
						f->data = _allocator->realloc_array< unsigned char >(f->data, f->alloc_size);
					}
					::memcpy(f->data, vframe->data, vframe->size);
					f->fourcc = vframe->fourcc;
					f->width = vframe->width;
					f->height = vframe->height;
					f->size = vframe->size;
					f->timestamp = vframe->timestamp;
					_video_frames.enqueue(f);
					return true;
                                }
				booinline bool onaudioframe(::booldog::multimedia::audio::frame* aframe)
				{
					::booldog::multimedia::audio::frame* f = _avail_audio_frames.dequeue();
					if(f == 0)
					{
						if(_audio_frames.count() >= 140)
						{
                                                        //printf("audio %d >= 140\n", (int)_audio_frames.count());
                                                        //printf("avail audio frames %d\n", (int)_avail_audio_frames.count());
						}
						f = _allocator->create< ::booldog::multimedia::audio::frame >();
					}					
					if(f->alloc_size < aframe->size + 64)
					{
						f->alloc_size = aframe->size + 64;
						f->data = _allocator->realloc_array< unsigned char >(f->data, f->alloc_size);
					}
					::memcpy(f->data, aframe->data, aframe->size);
					f->fourcc = aframe->fourcc;
					f->bytes_per_sample = aframe->bytes_per_sample;
					f->channels = aframe->channels;
					f->size = aframe->size;
					f->timestamp = aframe->timestamp;
					f->sample_rate = aframe->sample_rate;
					_audio_frames.enqueue(f);
					return true;
                                }
			};
                }
        }
}
#endif
