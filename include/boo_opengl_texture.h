#ifndef BOO_OPENGL_TEXTURE_H
#define BOO_OPENGL_TEXTURE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_opengl_buffer.h"
#include "boo_math_utils.h"
namespace booldog
{
	namespace opengl
	{
		class framebuffer;
		class texture
		{
			friend class framebuffer;
			::booldog::opengl::context* _ctx;
			::booldog::opengl::buffer* _buffer;
			GLuint _id;
			GLenum _target;
			GLint _internalformat;
			GLint _format;
			GLenum _type;
			GLsizei _width;
			GLsizei _height;
			GLsizei _data_width;
			GLsizei _data_height;
			GLint _min_filter_texparameter;
			GLint _mag_filter_texparameter;
			void* _udata;
		public:
			texture( ::booldog::opengl::context* ctx )
				: _ctx( ctx ) , _buffer( 0 ) , _target( GL_TEXTURE_2D ) , _internalformat( GL_RGBA ) , _format( GL_RGBA ) 
				, _type( GL_UNSIGNED_BYTE ) , _width( 0 ) , _height( 0 ) , _id( 0 ) , _data_width( 0 ) , _data_height( 0 )
				, _min_filter_texparameter( GL_NEAREST_MIPMAP_LINEAR ) , _mag_filter_texparameter( GL_LINEAR ) , _udata( 0 )
			{
			};
			~texture( void )
			{
				if( _buffer )
					_ctx->_allocator->destroy< ::booldog::opengl::buffer >( _buffer );
				if( _width > 0 && _height > 0 )
					_ctx->_glDeleteTextures( 1 , &_id );
			};
			void* udata( void )
			{
				return _udata;
			};
			void udata( void* pudata )
			{
				_udata = pudata;
			};
			static booinline GLsizei texture::size( GLint format , GLenum type , GLsizei width , GLsizei height )
			{
				GLsizei size = 1;
				if( type == GL_FLOAT )
					size = 4;
				if( format == GL_RGBA || format == GL_BGRA_EXT )
					return 4 * size * width * height;
				else if( format == GL_RGB || format == GL_BGR_EXT )
					return 3 * size * width * height;
				else if( format == GL_LUMINANCE_ALPHA )
					return 2 * size * width * height;
				else
					return size * width * height;
			};
			GLenum target( void )
			{
				return _target;
			};
			void texture::alloc( GLenum target , GLint internalformat , GLint format , GLenum type , GLsizei width
				, GLsizei height , GLint min_filter_texparameter , GLint mag_filter_texparameter )
			{
				if( width > 0 && height > 0 )
				{
					if( _width > 0 && _height > 0 && 
						( _data_height != height || _data_width != width || _target != target
						|| _format != format || _internalformat != internalformat || _type != type ) )
					{
						_ctx->_glDeleteTextures( 1 , &_id );
						_width = 0;
						_height = 0;
					}
					if( _width == 0 && _height == 0 )
					{
						if( target == GL_TEXTURE_RECTANGLE )
						{
							_width = width;
							_height = height;
						}
						else
						{
							_width = ::booldog::utils::math::nextpowerof2( width );
							if( target == GL_TEXTURE_1D )
								_height = 1;
							else
								_height = ::booldog::utils::math::nextpowerof2( height );
						}
						_mag_filter_texparameter = mag_filter_texparameter;
						_min_filter_texparameter = min_filter_texparameter;
						_data_width = width;
						_data_height = height;
						_target = target;
						_format = format;
						_internalformat = internalformat;	
						_type = type;
						_ctx->_glGenTextures( 1 , &_id );
						if( _ctx->_glGenBuffers )
						{
							//if( _buffer == 0 )
							//	_buffer = _ctx->_allocator->create< ::booldog::opengl::buffer >( _ctx , debuginfo_macros );
						}
						_ctx->_glBindTexture( _target , _id );
						//_ctx->_glPixelStorei( GL_UNPACK_ALIGNMENT , 1 );

						_ctx->_glTexParameteri( _target , GL_TEXTURE_MIN_FILTER , _min_filter_texparameter );
						_ctx->_glTexParameteri( _target , GL_TEXTURE_MAG_FILTER , _mag_filter_texparameter );
						if( _target != GL_TEXTURE_RECTANGLE )
						{
							if( _min_filter_texparameter != GL_NEAREST && _min_filter_texparameter != GL_LINEAR )
							{
								_ctx->_glTexParameteri( _target , GL_TEXTURE_BASE_LEVEL , 0 );
								_ctx->_glTexParameteri( _target , GL_TEXTURE_MAX_LEVEL , 0 );
							}
						}

						if( _target == GL_TEXTURE_1D )
							_ctx->_glTexImage1D( _target , 0 , _internalformat , _width , 0 , _format , _type , NULL );
						else							
							_ctx->_glTexImage2D( _target , 0 , _internalformat , _width , _height , 0 , _format , _type , NULL );
						_ctx->_glBindTexture( _target , 0 );
						if( _buffer )
							_buffer->alloc( size( _format , _type , _width , _height ) , GL_PIXEL_UNPACK_BUFFER , GL_STREAM_DRAW );
					}
					else if( _min_filter_texparameter != min_filter_texparameter 
						|| _mag_filter_texparameter != mag_filter_texparameter )
					{
						_mag_filter_texparameter = mag_filter_texparameter;
						_min_filter_texparameter = min_filter_texparameter;

						_ctx->_glBindTexture( _target , _id );

						_ctx->_glTexParameteri( _target , GL_TEXTURE_MIN_FILTER , _min_filter_texparameter );
						_ctx->_glTexParameteri( _target , GL_TEXTURE_MAG_FILTER , _mag_filter_texparameter );
						if( _target != GL_TEXTURE_RECTANGLE )
						{
							if( _min_filter_texparameter != GL_NEAREST && _min_filter_texparameter != GL_LINEAR )
							{
								_ctx->_glTexParameteri( _target , GL_TEXTURE_BASE_LEVEL , 0 );
								_ctx->_glTexParameteri( _target , GL_TEXTURE_MAX_LEVEL , 0 );
							}
						}

						_ctx->_glBindTexture( _target , 0 );
					}
				}
			};
			void texture::copy( GLenum target , GLint internalformat , GLint format , GLenum type , GLsizei width
				, GLsizei height , void* data , GLint min_filter_texparameter , GLint mag_filter_texparameter )
			{
				alloc( target , internalformat , format , type , width , height , min_filter_texparameter , mag_filter_texparameter );
				if( _buffer )
				{
					_buffer->alloc( size( _format , _type , _width , _height ) , GL_PIXEL_UNPACK_BUFFER , GL_STREAM_DRAW );

					_buffer->copy( size( _format , _type , width , height ) , data , GL_PIXEL_UNPACK_BUFFER , GL_STREAM_DRAW );

					_ctx->_glBindTexture( _target , _id );
					if( _format == GL_RGBA || _format == GL_BGRA )
						_ctx->_glPixelStorei( GL_UNPACK_ALIGNMENT , 4 );
					else
						_ctx->_glPixelStorei( GL_UNPACK_ALIGNMENT , 1 );

					_buffer->bind();
					if( _target == GL_TEXTURE_1D )
						_ctx->_glTexImage1D( _target , 0 , _internalformat , _width , 0 , _format , _type , NULL );
					else
						_ctx->_glTexImage2D( _target , 0 , _internalformat , _width , _height , 0 , _format , _type 
							, NULL );
					_buffer->unbind();

					_ctx->_glBindTexture( _target , 0 );
				}
				else if( _width > 0 && _height > 0 )
				{
					_ctx->_glBindTexture( _target , _id );

					if( _target == GL_TEXTURE_1D )
						_ctx->_glTexSubImage1D( _target, 0 , 0 , width , _format , _type , data );
					else
						_ctx->_glTexSubImage2D( _target, 0 , 0 , 0 , width , height , _format , _type , data );

					_ctx->_glBindTexture( _target , 0 );
				}
			};
			GLsizei texture::height( void )
			{
				return _height;
			};
			GLsizei texture::data_width( void )
			{
				return _data_width;
			};
			GLsizei texture::data_height( void )
			{
				return _data_height;
			};
			GLsizei texture::width( void )
			{
				return _width;
			};
			void texture::enable( GLenum target )
			{
				_ctx->_glEnable( target );
			};
			void texture::disable( void )
			{
				_ctx->_glDisable( _target );
			};
			void texture::bind( void )
			{
				_ctx->_glBindTexture( _target , _id );
			};
			void texture::unbind( void )
			{
				_ctx->_glBindTexture( _target , 0 );
			};
			void texture::make_active_in_shader( GLenum texture , GLint shader_location )
			{
				//_ctx->_glEnable( _target );
				_ctx->_glActiveTexture( texture );
				_ctx->_glUniform1i( shader_location , texture - GL_TEXTURE0 );
				_ctx->_glBindTexture( _target , _id );
			};
		};
	};
};
#endif