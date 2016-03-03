#ifndef BOO_OPENGL_FRAMEBUFFER_H
#define BOO_OPENGL_FRAMEBUFFER_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef BOOLDOG_HEADER
#define BOOLDOG_HEADER( header ) <header>
#endif
#include BOOLDOG_HEADER(boo_opengl_texture.h)
namespace booldog
{
	namespace opengl
	{
		class framebuffer
		{
			::booldog::opengl::texture _texture;
			GLuint _depth_stencil_id;
			GLuint _framebuffer_id;
		public:
			bool resize( ::booldog::result* pres , GLsizei width , GLsizei height )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );

				_texture.enable( GL_TEXTURE_2D ); 
				_texture.alloc( GL_TEXTURE_2D , GL_RGBA , GL_RGBA , GL_UNSIGNED_BYTE , width , height , GL_NEAREST , GL_NEAREST );

				_texture._ctx->_glBindRenderbuffer( GL_RENDERBUFFER, _depth_stencil_id );
				_texture._ctx->_glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8 , _texture.width() 
					, _texture.height() );
				_texture._ctx->_glBindRenderbuffer( GL_RENDERBUFFER, 0 );
					
				_texture._ctx->_glBindFramebuffer( GL_FRAMEBUFFER , _framebuffer_id );
				_texture._ctx->_glFramebufferTexture2D( GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D 
					, _texture._id , 0 );
				_texture._ctx->_glFramebufferRenderbuffer( GL_FRAMEBUFFER , GL_DEPTH_ATTACHMENT , GL_RENDERBUFFER 
					, _depth_stencil_id );
				_texture._ctx->_glFramebufferRenderbuffer( GL_FRAMEBUFFER , GL_STENCIL_ATTACHMENT , GL_RENDERBUFFER 
					, _depth_stencil_id );
				GLenum status = _texture._ctx->_glCheckFramebufferStatus( GL_FRAMEBUFFER );
				if( status != GL_FRAMEBUFFER_COMPLETE )
					res->glGetError( status );
				
				_texture._ctx->_glBindFramebuffer( GL_FRAMEBUFFER , 0 );
				_texture.disable();
				
				return res->succeeded();
			};
			framebuffer( ::booldog::opengl::context* ctx )
				: _texture( ctx )
			{
				_texture._ctx->_glGenRenderbuffers( 1, &_depth_stencil_id );
				_texture._ctx->_glGenFramebuffers( 1 , &_framebuffer_id );
			};
			~framebuffer( void )
			{
				_texture._ctx->_glDeleteFramebuffers( 1 , &_framebuffer_id );
				_texture._ctx->_glDeleteRenderbuffers( 1 , &_depth_stencil_id );
			};
			::booldog::opengl::texture* texture( void )
			{
				return &_texture;
			};
			void framebuffer::bind( void )
			{
				_texture._ctx->_glBindFramebuffer( GL_FRAMEBUFFER , _framebuffer_id );
			};
			void framebuffer::unbind( void )
			{
				_texture._ctx->_glBindFramebuffer( GL_FRAMEBUFFER , 0 );
			};
		};
	};
};
#endif