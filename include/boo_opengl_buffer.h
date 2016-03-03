#ifndef BOO_OPENGL_BUFFER_H
#define BOO_OPENGL_BUFFER_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_opengl_context.h)
namespace booldog
{
	namespace opengl
	{
		class buffer
		{
			::booldog::opengl::context* _ctx;
			GLenum _target;
			GLenum _usage;
			GLsizeiptr _size;
			GLuint _id;
		public:
			buffer( ::booldog::opengl::context* ctx )
				: _ctx( ctx ) , _size( 0 ) , _id( 0 ) , _target( GL_PIXEL_UNPACK_BUFFER ) , _usage( GL_STREAM_DRAW )
			{
			};
			~buffer( void )
			{
				if( _size )
					_ctx->_glDeleteBuffers( 1 , &_id  );
			};
			void buffer::alloc( GLsizeiptr size , GLenum target , GLenum usage )
			{
				if( size > 0 )
				{
					if( _size > 0 && ( _size < size || _target != target || _usage != usage ) )
					{
						_ctx->_glDeleteBuffers( 1 , &_id );
						_size = 0;
					}
					if( _size == 0 )
					{
						_target = target;
						_usage = usage;
						_size = size;
						_ctx->_glBindBuffer( _target , 0 );
						_ctx->_glGenBuffers( 1 , &_id );
						_ctx->_glBindBuffer( _target , _id );
						_ctx->_glBufferData( _target , _size , NULL, _usage );
						_ctx->_glBindBuffer( _target , 0 );
					}
				}
			};
			void buffer::copy( GLsizeiptr size , void* data , GLenum target , GLenum usage )
			{
				if( size > 0 )
				{
					alloc( size , target , usage );
					if( _size > 0 )
					{
						_ctx->_glBindBuffer( _target , _id );
						if( _ctx->_glMapBuffer )
						{
							GLvoid* data_ptr = _ctx->_glMapBuffer( _target , GL_WRITE_ONLY );
							if( data_ptr )
							{
								memcpy( data_ptr , data , size );
								_ctx->_glUnmapBuffer( _target );
							}
						}
						else
							_ctx->_glBufferSubData( _target , 0 , size , data );
						_ctx->_glBindBuffer( _target , 0 );
					}
				}
			};
			void buffer::bind( void )
			{
				_ctx->_glBindBuffer( _target , _id );
			};
			void buffer::unbind( void )
			{
				_ctx->_glBindBuffer( _target , 0 );
			};
		};
	};
};
#endif