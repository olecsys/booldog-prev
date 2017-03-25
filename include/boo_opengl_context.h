#ifndef BOO_OPENGL_CONTEXT_H
#define BOO_OPENGL_CONTEXT_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "boo_base_loader.h"
#include "boo_render_context.h"

#include <GL/gl.h>
#ifndef WINAPI
#define WINAPI
#endif
#ifndef GL_BGR
#define GL_BGR                            0x80E0
#endif
#ifndef GL_BGRA
#define GL_BGRA                           0x80E1
#endif
#ifndef GL_COLOR_ATTACHMENT0
#define GL_COLOR_ATTACHMENT0              0x8CE0
#endif
#ifndef GL_DEPTH_ATTACHMENT
#define GL_DEPTH_ATTACHMENT               0x8D00
#endif
#ifndef GL_STENCIL_ATTACHMENT
#define GL_STENCIL_ATTACHMENT             0x8D20
#endif
#ifndef GL_FRAMEBUFFER_COMPLETE
#define GL_FRAMEBUFFER_COMPLETE           0x8CD5
#endif
#ifndef GL_DEPTH24_STENCIL8
#define GL_DEPTH24_STENCIL8               0x88F0
#endif
#ifndef GL_FRAMEBUFFER
#define GL_FRAMEBUFFER                    0x8D40
#endif
#ifndef GL_RENDERBUFFER
#define GL_RENDERBUFFER                   0x8D41
#endif
#ifndef WGL_CONTEXT_MAJOR_VERSION_ARB
#define WGL_CONTEXT_MAJOR_VERSION_ARB           0x2091
#endif
#ifndef WGL_CONTEXT_MINOR_VERSION_ARB
#define WGL_CONTEXT_MINOR_VERSION_ARB           0x2092
#endif
#ifndef WGL_CONTEXT_LAYER_PLANE_ARB
#define WGL_CONTEXT_LAYER_PLANE_ARB             0x2093
#endif
#ifndef WGL_CONTEXT_FLAGS_ARB
#define WGL_CONTEXT_FLAGS_ARB                   0x2094
#endif
#ifndef WGL_CONTEXT_PROFILE_MASK_ARB
#define WGL_CONTEXT_PROFILE_MASK_ARB            0x9126
#endif
#ifndef WGL_CONTEXT_DEBUG_BIT_ARB
#define WGL_CONTEXT_DEBUG_BIT_ARB               0x0001
#endif
#ifndef WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB  0x0002
#endif
#ifndef WGL_CONTEXT_CORE_PROFILE_BIT_ARB
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB        0x00000001
#endif
#ifndef WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#endif
#ifndef GL_TEXTURE_MAX_LEVEL
#define GL_TEXTURE_MAX_LEVEL              0x813D
#endif
#ifndef GL_TEXTURE_BASE_LEVEL
#define GL_TEXTURE_BASE_LEVEL             0x813C
#endif
#ifndef GL_SHADING_LANGUAGE_VERSION
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C
#endif
#ifndef GL_TEXTURE0
#define GL_TEXTURE0                       0x84C0
#endif
#ifndef GL_STREAM_DRAW
#define GL_STREAM_DRAW                    0x88E0
#endif
#ifndef GL_PIXEL_UNPACK_BUFFER
#define GL_PIXEL_UNPACK_BUFFER            0x88EC
#endif
#ifndef GL_WRITE_ONLY
#ifdef __ANDROID__
#define GL_WRITE_ONLY GL_WRITE_ONLY_OES
#else
#define GL_WRITE_ONLY                     0x88B9
#endif
#endif
#ifndef GL_TEXTURE_RECTANGLE
#define GL_TEXTURE_RECTANGLE              0x84F5
#endif
typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
namespace booldog
{
#ifdef __WINDOWS__
#define glGetProcAddress( function ) _wglGetProcAddress( function )
#elif defined( __UNIX__ )
#ifdef __ANDROID__
#define glGetProcAddress( function ) _eglGetProcAddress( function )
#else
#define glGetProcAddress( function ) _glXGetProcAddress( (GLubyte*)function )
#endif
#endif
	namespace typedefs
	{
		typedef void (WINAPI *glAttachShader)( GLuint program , GLuint shader );
		typedef void (WINAPI *glDetachShader)( GLuint program , GLuint shader );
		typedef void (WINAPI *glDeleteShader)( GLuint shader );
		typedef void (WINAPI *glCompileShader)(	GLuint shader );
		typedef void (WINAPI *glShaderSource)( GLuint shader , GLsizei count , const GLchar** string , const GLint* length );
		typedef GLuint (WINAPI *glCreateShader)( GLenum shaderType );
		typedef GLuint (WINAPI *glCreateProgram)( void );
		typedef void (WINAPI *glBufferSubData)(	GLenum target , GLintptr offset , GLsizeiptr size , const GLvoid* data );
		typedef void (WINAPI *glBufferData)( GLenum target , GLsizeiptr size , const GLvoid* data , GLenum usage );
		typedef void (WINAPI *glVertexAttribPointer)( GLuint index​ , GLint size​ , GLenum type​ , GLboolean normalized​ , GLsizei stride​ 
			, const GLvoid* pointer​ );
		typedef void (WINAPI *glBindBuffer)( GLenum target , GLuint buffer );
		typedef void (WINAPI *glGenBuffers)( GLsizei n , GLuint* buffers );
		typedef void (WINAPI *glUniform1i)(	GLint location , GLint v0 );
		typedef void (WINAPI *glActiveTexture)(	GLenum texture );
		typedef void (WINAPI *glFramebufferRenderbuffer)( GLenum target , GLenum attachment , GLenum renderbuffertarget 
			, GLuint renderbuffer );
		typedef void (WINAPI *glGetFramebufferAttachmentParameteriv)( GLenum target , GLenum attachment , GLenum pname , GLint* params );
		typedef void (WINAPI *glGetInternalformativ)( GLenum target​ , GLenum internalformat​ , GLenum pname​ , GLsizei bufSize​ 
			, GLint* params​ );
		typedef void (WINAPI *glRenderbufferStorage)( GLenum target , GLenum internalformat , GLsizei width , GLsizei height );
		typedef void (WINAPI *glGenRenderbuffers)( GLsizei n , GLuint* renderbuffers );
		typedef void (WINAPI *glDeleteRenderbuffers)( GLsizei n​ , GLuint* renderbuffers​ );
		typedef void (WINAPI *glBindRenderbuffer)( GLenum target , GLuint renderbuffer );
		typedef void (WINAPI *glGetRenderbufferParameteriv)( GLenum target , GLenum pname, GLint* params );
		typedef void (WINAPI *glFramebufferTexture1D)( GLenum target , GLenum attachment , GLenum textarget , GLuint texture 
			, GLint level );
		typedef GLboolean (WINAPI *glIsFramebuffer)( GLuint framebuffer );
		typedef void (WINAPI *glFramebufferTexture3D)( GLenum target , GLenum attachment , GLenum textarget , GLuint texture ,
			GLint level , GLint zoffset );
		typedef GLboolean (WINAPI *glIsRenderbuffer)( GLuint renderbuffer );
		typedef void (WINAPI *glFramebufferTexture2D)( GLenum target , GLenum attachment , GLenum textarget , GLuint texture 
			, GLint level );
		typedef GLenum (WINAPI *glCheckFramebufferStatus)( GLenum target );
		typedef void (WINAPI *glGenerateMipmap)( GLenum target );
		typedef void (WINAPI *glGenFramebuffers)( GLsizei n , GLuint* ids );
		typedef void (WINAPI *glDeleteFramebuffers)( GLsizei n , GLuint* framebuffers );
		typedef void (WINAPI *glBindFramebuffer)( GLenum target , GLuint framebuffer );
		typedef void (WINAPI *glMultiDrawArrays)( GLenum mode , const GLint* first , const GLsizei* count , GLsizei drawcount );
		typedef void (WINAPI *glActiveStencilFace)( GLenum face );
		typedef void (WINAPI *glStencilOpSeparate)(	GLenum face , GLenum sfail , GLenum dpfail , GLenum dppass );
		typedef void (WINAPI *glGetInfoLog)( GLuint obj , GLsizei maxLength , GLsizei* length , GLchar* infoLog );
		typedef void (WINAPI *glGetObjectParameteriv)( GLuint obj , GLenum pname , GLint *params );
		typedef void (WINAPI *glUniform4f)(	GLint location , GLfloat v0 , GLfloat v1 , GLfloat v2 , GLfloat v3 );
		typedef void (WINAPI *glUniform1fv)( GLint location , GLsizei count , const GLfloat* value );
		typedef void (WINAPI *glUniform1f)(	GLint location , GLfloat v0 );
		typedef GLboolean (WINAPI *glUnmapBuffer)( GLenum target );
		typedef void* (WINAPI *glMapBuffer)( GLenum target , GLenum access );
		typedef void (WINAPI *glUniform4fv)( GLint location , GLsizei count , const GLfloat* value );
		typedef void (WINAPI *glEnableVertexAttribArray)( GLuint index​ );
		typedef void (WINAPI *glDisableVertexAttribArray)( GLuint index​ );
		typedef void (WINAPI *glDeleteProgram)(	GLuint program );
		typedef void (WINAPI *glGetShaderiv)( GLuint shader , GLenum pname , GLint* params );
		typedef void (WINAPI *glGetProgramiv)( GLuint program​ , GLenum pname​ , GLint* params​ );
		typedef void (WINAPI *glValidateProgram)( GLuint program );
		typedef void (WINAPI *glUseProgram)( GLuint program );
		typedef GLint (WINAPI *glGetUniformLocation)( GLuint program , const GLchar* name );
		typedef GLint (WINAPI *glGetAttribLocation)( GLuint program , const GLchar* name );
		typedef void (WINAPI *glBindFragDataLocation)( GLuint program , GLuint colorNumber , const char* name );
		typedef void (WINAPI *glLinkProgram)( GLuint program );
		typedef void (WINAPI *glDeleteBuffers)(	GLsizei n , const GLuint* buffers );

		typedef void (WINAPI *glClearDepthf)( GLclampf depth );
		typedef void (WINAPI *glClearDepth)( GLclampd depth );
		typedef void (WINAPI *glDrawPixels)( GLsizei width , GLsizei height , GLenum format , GLenum type , const GLvoid* pixels );
		typedef void (WINAPI *glPixelZoom)( GLfloat xfactor , GLfloat yfactor );
		typedef void (WINAPI *glRasterPos3f)( GLfloat x , GLfloat y , GLfloat z );
		typedef void (WINAPI *glGetIntegerv)( GLenum pname , GLint* params );
		typedef void (WINAPI *glBegin)( GLenum mode );
		typedef void (WINAPI *glTexCoord2f)( GLfloat s , GLfloat t );
		typedef void (WINAPI *glVertex3f)( GLfloat x , GLfloat y , GLfloat z );
		typedef void (WINAPI *glEnd)( void );
		typedef void (WINAPI *glPopMatrix)( void );
		typedef void (WINAPI *glFinish)( void );
		typedef void (WINAPI *glFlush)( void );
		typedef void (WINAPI *glHint)( GLenum target , GLenum mode );
		typedef void (WINAPI *glScalef)( GLfloat x , GLfloat y , GLfloat z );
		typedef void (WINAPI *glClear)( GLbitfield mask );
		typedef const GLubyte* (WINAPI *glGetString)( GLenum name );
		typedef void (WINAPI *glViewport)( GLint x , GLint y , GLsizei width , GLsizei height );
		typedef void (WINAPI *glShadeModel)( GLenum mode );
		typedef void (WINAPI *glClearColor)( GLclampf red , GLclampf green , GLclampf blue , GLclampf alpha );
		typedef void (WINAPI *glOrtho)( GLdouble left , GLdouble right , GLdouble bottom , GLdouble top , GLdouble zNear , GLdouble zFar );
		typedef void (WINAPI *glDepthFunc)( GLenum func );
		typedef void (WINAPI *glMatrixMode)( GLenum mode );
		typedef void (WINAPI *glPushMatrix)( void );
		typedef void (WINAPI *glTexSubImage1D)( GLenum target , GLint level , GLint xoffset , GLsizei width , GLenum format 
			, GLenum type , const GLvoid* pixels );
		typedef void (WINAPI *glTexSubImage2D)( GLenum target , GLint level , GLint xoffset , GLint yoffset , GLsizei width 
			, GLsizei height , GLenum format , GLenum type , const GLvoid* pixels );
		typedef void (WINAPI *glColorPointer)( GLint size , GLenum type , GLsizei stride , const GLvoid* pointer );
		typedef void (WINAPI *glClearStencil)( GLint s );
		typedef void (WINAPI *glTexCoordPointer)( GLint size , GLenum type , GLsizei stride , const GLvoid* pointer );
		typedef void (WINAPI *glEnableClientState)( GLenum array );
		typedef void (WINAPI *glDeleteTextures)( GLsizei n , const GLuint* textures );
		typedef void (WINAPI *glGenTextures)( GLsizei n , GLuint* textures );
		typedef void (WINAPI *glLoadIdentity)( void );
		typedef void (WINAPI *glTexImage1D)( GLenum target , GLint level , GLint internalformat , GLsizei width , GLint border 
			, GLint format , GLenum type , const GLvoid* pixels );
		typedef void (WINAPI *glTexImage2D)( GLenum target , GLint level , GLint internalformat , GLsizei width , GLsizei height
			, GLint border , GLint format , GLenum type , const GLvoid* pixels );
		typedef void (WINAPI *glTexEnvf)( GLenum target , GLenum pname , GLfloat param );
		typedef void (WINAPI *glTexParameteri)( GLenum target , GLenum pname , GLint param );
		typedef void (WINAPI *glGetBooleanv)( GLenum pname , GLboolean* params );
		typedef void (WINAPI *glGetFloatv)( GLenum pname , GLfloat* params );
		typedef void (WINAPI *glBlendFunc)( GLenum sfactor , GLenum dfactor );
		typedef void (WINAPI *glStencilOp)( GLenum fail , GLenum zfail , GLenum zpass );
		typedef void (WINAPI *glColorMask)( GLboolean red , GLboolean green , GLboolean blue , GLboolean alpha );
		typedef void (WINAPI *glStencilFunc)( GLenum func , GLint ref , GLuint mask );
		typedef void (WINAPI *glDisable)( GLenum cap );
		typedef void (WINAPI *glBindTexture)( GLenum target , GLuint texture );
		typedef void (WINAPI *glEnable)( GLenum cap );
		typedef void (WINAPI *glPixelStorei)( GLenum pname , GLint param );
#ifdef __WINDOWS__
		typedef BOOL (WINAPI *wglMakeCurrent)( HDC hdc , HGLRC hglrc );
		typedef PROC (WINAPI *wglGetProcAddress)( LPCSTR lpszProc );
		typedef BOOL (WINAPI *wglShareLists)( HGLRC hglrc1 , HGLRC hglrc2 );
		typedef HDC (WINAPI *wglGetCurrentDC)( void );
		typedef HGLRC (WINAPI *wglCreateContext)( HDC hdc );
		typedef BOOL (WINAPI *wglDeleteContext)( HGLRC hglrc );
		typedef HGLRC (WINAPI *wglGetCurrentContext)( void );

		typedef BOOL (WINAPI *SetPixelFormat)( HDC hdc , int iPixelFormat , const PIXELFORMATDESCRIPTOR* ppfd );
		typedef int (WINAPI *DescribePixelFormat)( HDC hdc , int iPixelFormat , UINT nBytes , LPPIXELFORMATDESCRIPTOR ppfd );
		typedef int (WINAPI *ChoosePixelFormat)( HDC hdc , const PIXELFORMATDESCRIPTOR* ppfd );

		typedef HDC (WINAPI *GetDC)( HWND hWnd );
		typedef int (WINAPI *ReleaseDC)( HWND hWnd , HDC hDC );
		typedef BOOL (WINAPI *SwapBuffers)( HDC hdc );

		typedef BOOL (WINAPI *wglSwapInterval)( int interval );
		typedef int (WINAPI *wglGetSwapInterval)( void );

		typedef HGLRC (WINAPI *wglCreateContextAttribs)( HDC hDC , HGLRC hShareContext , const int* attribList );
#endif
		typedef void (WINAPI *glColor4f)( GLfloat red , GLfloat green , GLfloat blue , GLfloat alpha );
		typedef void (WINAPI *glRotatef)( GLfloat angle , GLfloat x , GLfloat y , GLfloat z );
		typedef GLenum (WINAPI *glGetError)( void );
		typedef void (WINAPI *glDisableClientState)( GLenum array );
		typedef void (WINAPI *glDrawArrays)( GLenum mode , GLint first , GLsizei count );
		typedef void (WINAPI *glVertexPointer)( GLint size , GLenum type , GLsizei stride , const GLvoid* pointer );
	};
};
namespace booldog
{
	namespace opengl
	{
#define booctor_null_macro( FUNC ) _##FUNC( 0 )
#define declare_opengl_function( FUNC )\
		::booldog::typedefs::FUNC _##FUNC
#define glGetProcAddress_macro( FUNC )\
		this->_##FUNC = (::booldog::typedefs::FUNC)glGetProcAddress( #FUNC );\
		if( this->_##FUNC == 0 )\
		{\
			this->_##FUNC = (::booldog::typedefs::FUNC)glGetProcAddress( #FUNC"EXT" );\
			if( this->_##FUNC == 0 )\
			{\
				this->_##FUNC = (::booldog::typedefs::FUNC)glGetProcAddress( #FUNC"OES" );\
				if( this->_##FUNC == 0 )\
					this->_##FUNC = (::booldog::typedefs::FUNC)glGetProcAddress( #FUNC"ARB" );\
			}\
		}\
		if( this->_##FUNC == 0 )\
			printf( "OpenGL function '"#FUNC"' not found\n" )
#define get_opengl_function( FUNC )\
		if( resmod.module->method( &resptr , _allocator , #FUNC , debuginfo_macros ) )\
			_##FUNC = (::booldog::typedefs::FUNC)resptr.pres;\
		else if( resmod.module->method( &resptr , _allocator , #FUNC"EXT" , debuginfo_macros ) )\
			_##FUNC = (::booldog::typedefs::FUNC)resptr.pres;\
		else if( resmod.module->method( &resptr , _allocator , #FUNC"OES" , debuginfo_macros ) )\
			_##FUNC = (::booldog::typedefs::FUNC)resptr.pres;\
		else if( resmod.module->method( &resptr , _allocator , #FUNC"ARB" , debuginfo_macros ) )\
			_##FUNC = (::booldog::typedefs::FUNC)resptr.pres;\
		else\
			printf( "OpenGL function '"#FUNC"' not found\n" )
		class context : public ::booldog::rendering::context
		{
			const char* _renderer;
			GLint _max_texture_size;
			::booldog::base::module* _opengl;
#ifdef __WINDOWS__
			HGLRC _ctx;
			HDC _hdc;
			HWND _hwnd;
#elif defined( __UNIX__ )
#ifdef __ANDROID__
			EGLContext _ctx;
#else
			GLXContext _ctx;
#endif
#endif
		public:
			::booldog::allocator* _allocator;
			::booldog::base::loader* _loader;
#ifdef __WINDOWS__
			declare_opengl_function( SwapBuffers );
			declare_opengl_function( wglShareLists );
			declare_opengl_function( wglGetProcAddress );
			declare_opengl_function( wglGetCurrentDC );
			declare_opengl_function( wglCreateContext );
			declare_opengl_function( wglDeleteContext );
			declare_opengl_function( wglMakeCurrent );
			declare_opengl_function( wglGetCurrentContext );
			declare_opengl_function( wglGetSwapInterval );
			declare_opengl_function( wglCreateContextAttribs );
			declare_opengl_function( wglSwapInterval );
#else
#ifdef __ANDROID__
			declare_opengl_function( eglGetProcAddress );
#else
			declare_opengl_function( glXQueryExtension );
			declare_opengl_function( glXGetConfig );
			declare_opengl_function( glXGetProcAddress );
			declare_opengl_function( glXCreateContext );
			declare_opengl_function( glXDestroyContext );
			declare_opengl_function( glXSwapBuffers );
			declare_opengl_function( glXGetCurrentContext );
			declare_opengl_function( glXMakeCurrent );			
#endif
#endif							
			declare_opengl_function( glColor4f );
			declare_opengl_function( glRotatef );
			declare_opengl_function( glGetError );
			declare_opengl_function( glDisableClientState );
			declare_opengl_function( glDrawArrays );
			declare_opengl_function( glVertexPointer );
			declare_opengl_function( glPixelStorei );
			declare_opengl_function( glEnable );
			declare_opengl_function( glBindTexture );
			declare_opengl_function( glDisable );
			declare_opengl_function( glStencilFunc );
			declare_opengl_function( glColorMask );
			declare_opengl_function( glStencilOp );
			declare_opengl_function( glBlendFunc );
			declare_opengl_function( glGetFloatv );
			declare_opengl_function( glGetBooleanv );
			declare_opengl_function( glTexParameteri );
			declare_opengl_function( glTexEnvf );
			declare_opengl_function( glTexImage2D );
			declare_opengl_function( glTexImage1D );
			declare_opengl_function( glLoadIdentity );							
			declare_opengl_function( glGenTextures );
			declare_opengl_function( glDeleteTextures );
			declare_opengl_function( glEnableClientState );
			declare_opengl_function( glTexCoordPointer );
			declare_opengl_function( glClearStencil );
			declare_opengl_function( glColorPointer );
			declare_opengl_function( glTexSubImage2D );
			declare_opengl_function( glTexSubImage1D );
			declare_opengl_function( glPushMatrix );
			declare_opengl_function( glMatrixMode );
			declare_opengl_function( glDepthFunc );
			declare_opengl_function( glClearDepthf );
			declare_opengl_function( glClearDepth );
			declare_opengl_function( glScalef );
#ifdef __ANDROID__
			declare_opengl_function( glOrthof );
#else
			declare_opengl_function( glOrtho );
			declare_opengl_function( glGetObjectParameteriv );
			declare_opengl_function( glGetInfoLog );
#endif
			declare_opengl_function( glClearColor );
			declare_opengl_function( glShadeModel );
			declare_opengl_function( glViewport );
			declare_opengl_function( glGetString );
			declare_opengl_function( glClear );
			declare_opengl_function( glHint );
			declare_opengl_function( glFlush );
			declare_opengl_function( glFinish );
			declare_opengl_function( glPopMatrix );
			declare_opengl_function( glEnd );
			declare_opengl_function( glVertex3f );
			declare_opengl_function( glTexCoord2f );
			declare_opengl_function( glBegin );							
			declare_opengl_function( glGetIntegerv );
			declare_opengl_function( glRasterPos3f );
			declare_opengl_function( glPixelZoom );
			declare_opengl_function( glDrawPixels );

			declare_opengl_function( glDeleteBuffers );
			declare_opengl_function( glLinkProgram );
			declare_opengl_function( glBindFragDataLocation );
			declare_opengl_function( glGetAttribLocation );
			declare_opengl_function( glGetUniformLocation );
			declare_opengl_function( glUseProgram );
			declare_opengl_function( glValidateProgram );
			declare_opengl_function( glGetProgramiv );
			declare_opengl_function( glGetShaderiv );
			declare_opengl_function( glDeleteProgram );
			declare_opengl_function( glDisableVertexAttribArray );
			declare_opengl_function( glUniform4fv );
			declare_opengl_function( glMapBuffer );
			declare_opengl_function( glUnmapBuffer );
			declare_opengl_function( glUniform1f );
			declare_opengl_function( glUniform1fv );
			declare_opengl_function( glUniform4f );
			declare_opengl_function( glStencilOpSeparate );
			declare_opengl_function( glActiveStencilFace );
			declare_opengl_function( glMultiDrawArrays );
			declare_opengl_function( glBindFramebuffer );
			declare_opengl_function( glDeleteFramebuffers );
			declare_opengl_function( glGenFramebuffers );
			declare_opengl_function( glGenerateMipmap );
			declare_opengl_function( glCheckFramebufferStatus );
			declare_opengl_function( glFramebufferTexture2D );
			declare_opengl_function( glFramebufferTexture3D );
			declare_opengl_function( glBindRenderbuffer );
			declare_opengl_function( glGetRenderbufferParameteriv );
			declare_opengl_function( glFramebufferTexture1D );
			declare_opengl_function( glIsFramebuffer );
			declare_opengl_function( glIsRenderbuffer );
			declare_opengl_function( glDeleteRenderbuffers );
			declare_opengl_function( glGenRenderbuffers );
			declare_opengl_function( glRenderbufferStorage );
			declare_opengl_function( glGetInternalformativ );
			declare_opengl_function( glFramebufferRenderbuffer );
			declare_opengl_function( glGetFramebufferAttachmentParameteriv );
			declare_opengl_function( glActiveTexture );
			declare_opengl_function( glUniform1i );
			declare_opengl_function( glGenBuffers );
			declare_opengl_function( glEnableVertexAttribArray );
			declare_opengl_function( glBindBuffer );
			declare_opengl_function( glVertexAttribPointer );
			declare_opengl_function( glBufferData );
			declare_opengl_function( glBufferSubData );
			declare_opengl_function( glCreateProgram );
			declare_opengl_function( glCreateShader );
			declare_opengl_function( glShaderSource );
			declare_opengl_function( glCompileShader );
			declare_opengl_function( glDeleteShader );
			declare_opengl_function( glDetachShader );
			declare_opengl_function( glAttachShader );
		public:
			void supporting( const char* extensions , bool& GL_ARB_shader_objects , bool& GL_ARB_shading_language_100
				, bool& GL_ARB_vertex_shader , bool& GL_ARB_fragment_shader , bool& GL_ARB_vertex_buffer_object 
				, bool& WGL_EXT_swap_control , bool& WGL_ARB_create_context , bool& GL_EXT_framebuffer_object )
			{
				if( extensions )
				{
					//printf( "%s\n\n" , extensions );
					char str[ 128 ] = {0};

					const char* ptr = extensions , * begin = ptr;
					for( ; ; )
					{
						switch( *ptr )
						{
						case ' ':
						case 0:
							{
								size_t len = ptr - begin;
								if( len )
								{
									memcpy( str , begin , len );
									str[ len ] = 0;
									printf( "%s\n" , str );

									if( strncmp( begin , "GL_ARB_shader_objects" , len ) == 0 )
										GL_ARB_shader_objects = true;
									if( strncmp( begin , "WGL_ARB_create_context" , len ) == 0 )
										WGL_ARB_create_context = true;
									if( strncmp( begin , "WGL_EXT_swap_control" , len ) == 0 )
										WGL_EXT_swap_control = true;
									else if( strncmp( begin , "GL_ARB_vertex_buffer_object" , len ) == 0 )
										GL_ARB_vertex_buffer_object = true;
									else if( strncmp( begin , "GL_ARB_shading_language_100" , len ) == 0 )
										GL_ARB_shading_language_100 = true;
									else if( strncmp( begin , "GL_ARB_vertex_shader" , len ) == 0 )
										GL_ARB_vertex_shader = true;
									else if( strncmp( begin , "GL_ARB_fragment_shader" , len ) == 0 )
										GL_ARB_fragment_shader = true;
									else if( strncmp( begin , "GL_EXT_framebuffer_object" , len ) == 0 )
										GL_EXT_framebuffer_object = true;
									else if( strncmp( begin , "WGL_NV_gpu_affinity" , len ) == 0 )
										printf( "\n%s\n" , "WGL_NV_gpu_affinity supported" );
									else if( strncmp( begin , "WGL_AMD_gpu_association" , len ) == 0 )
										printf( "\n%s\n" , "WGL_AMD_gpu_association" );
								}
								begin = ptr + 1;
								break;
							}
						}
						if( *ptr == 0 )
							break;
						ptr++;
					}
				}
			};
			context( ::booldog::result* pres , booldog::allocator* allocator , ::booldog::base::loader* ploader , HWND hwnd 
				, ::booldog::events::typedefs::oncontextcreated poncontextcreated , bool multithreaded 
				, const ::booldog::debug::info& debuginfo = debuginfo_macros )
				: ::booldog::rendering::context( poncontextcreated ) , _allocator( allocator ) , _loader( ploader ) , _opengl( 0 ) 
					, _ctx( 0 ) , _hdc( 0 ) 
					, _hwnd( 0 ) , _max_texture_size( 0 ) , _renderer( 0 )
#ifdef __WINDOWS__
					, booctor_null_macro( SwapBuffers )
					, booctor_null_macro( wglShareLists )
					, booctor_null_macro( wglGetProcAddress )
					, booctor_null_macro( wglGetCurrentDC )
					, booctor_null_macro( wglCreateContext )
					, booctor_null_macro( wglDeleteContext )
					, booctor_null_macro( wglMakeCurrent )
					, booctor_null_macro( wglGetCurrentContext )
					, booctor_null_macro( wglGetSwapInterval )
					, booctor_null_macro( wglCreateContextAttribs )
					, booctor_null_macro( wglSwapInterval )
		#else
		#ifdef __ANDROID__
					, booctor_null_macro( eglGetProcAddress )
		#else
					, booctor_null_macro( glXQueryExtension )
					, booctor_null_macro( glXGetConfig )
					, booctor_null_macro( glXGetProcAddress )
					, booctor_null_macro( glXCreateContext )
					, booctor_null_macro( glXDestroyContext )
					, booctor_null_macro( glXSwapBuffers )
					, booctor_null_macro( glXGetCurrentContext )
					, booctor_null_macro( glXMakeCurrent )
		#endif
		#endif							
					, booctor_null_macro( glColor4f )
					, booctor_null_macro( glRotatef )
					, booctor_null_macro( glGetError )
					, booctor_null_macro( glDisableClientState )
					, booctor_null_macro( glDrawArrays )
					, booctor_null_macro( glVertexPointer )
					, booctor_null_macro( glPixelStorei )
					, booctor_null_macro( glEnable )
					, booctor_null_macro( glBindTexture )
					, booctor_null_macro( glDisable )
					, booctor_null_macro( glStencilFunc )
					, booctor_null_macro( glColorMask )
					, booctor_null_macro( glStencilOp )
					, booctor_null_macro( glBlendFunc )
					, booctor_null_macro( glGetFloatv )
					, booctor_null_macro( glGetBooleanv )
					, booctor_null_macro( glTexParameteri )
					, booctor_null_macro( glTexEnvf )
					, booctor_null_macro( glTexImage2D )
					, booctor_null_macro( glTexImage1D )
					, booctor_null_macro( glLoadIdentity )
					, booctor_null_macro( glGenTextures )
					, booctor_null_macro( glDeleteTextures )
					, booctor_null_macro( glEnableClientState )
					, booctor_null_macro( glTexCoordPointer )
					, booctor_null_macro( glClearStencil )
					, booctor_null_macro( glColorPointer )
					, booctor_null_macro( glTexSubImage2D )
					, booctor_null_macro( glTexSubImage1D )
					, booctor_null_macro( glPushMatrix )
					, booctor_null_macro( glMatrixMode )
					, booctor_null_macro( glDepthFunc )
					, booctor_null_macro( glClearDepthf )
					, booctor_null_macro( glClearDepth )
					, booctor_null_macro( glScalef )
		#ifdef __ANDROID__
					, booctor_null_macro( glOrthof )
		#else
					, booctor_null_macro( glOrtho )
					, booctor_null_macro( glGetObjectParameteriv )
					, booctor_null_macro( glGetInfoLog )
		#endif
					, booctor_null_macro( glClearColor )
					, booctor_null_macro( glShadeModel )
					, booctor_null_macro( glViewport )
					, booctor_null_macro( glGetString )
					, booctor_null_macro( glClear )
					, booctor_null_macro( glHint )
					, booctor_null_macro( glFlush )
					, booctor_null_macro( glFinish )
					, booctor_null_macro( glPopMatrix )
					, booctor_null_macro( glEnd )
					, booctor_null_macro( glVertex3f )
					, booctor_null_macro( glTexCoord2f )
					, booctor_null_macro( glBegin )						
					, booctor_null_macro( glGetIntegerv )
					, booctor_null_macro( glRasterPos3f )
					, booctor_null_macro( glPixelZoom )
					, booctor_null_macro( glDrawPixels )

					, booctor_null_macro( glDeleteBuffers )
					, booctor_null_macro( glLinkProgram )
					, booctor_null_macro( glBindFragDataLocation )
					, booctor_null_macro( glGetAttribLocation )
					, booctor_null_macro( glGetUniformLocation )
					, booctor_null_macro( glUseProgram )
					, booctor_null_macro( glValidateProgram )
					, booctor_null_macro( glGetProgramiv )
					, booctor_null_macro( glGetShaderiv )
					, booctor_null_macro( glDeleteProgram )
					, booctor_null_macro( glDisableVertexAttribArray )
					, booctor_null_macro( glUniform4fv )
					, booctor_null_macro( glMapBuffer )
					, booctor_null_macro( glUnmapBuffer )
					, booctor_null_macro( glUniform1f )
					, booctor_null_macro( glUniform1fv )
					, booctor_null_macro( glUniform4f )
					, booctor_null_macro( glStencilOpSeparate )
					, booctor_null_macro( glActiveStencilFace )
					, booctor_null_macro( glMultiDrawArrays )
					, booctor_null_macro( glBindFramebuffer )
					, booctor_null_macro( glDeleteFramebuffers )
					, booctor_null_macro( glGenFramebuffers )
					, booctor_null_macro( glGenerateMipmap )
					, booctor_null_macro( glCheckFramebufferStatus )
					, booctor_null_macro( glFramebufferTexture2D )
					, booctor_null_macro( glFramebufferTexture3D )
					, booctor_null_macro( glBindRenderbuffer )
					, booctor_null_macro( glGetRenderbufferParameteriv )
					, booctor_null_macro( glFramebufferTexture1D )
					, booctor_null_macro( glIsFramebuffer )
					, booctor_null_macro( glIsRenderbuffer )
					, booctor_null_macro( glDeleteRenderbuffers )
					, booctor_null_macro( glGenRenderbuffers )
					, booctor_null_macro( glRenderbufferStorage )
					, booctor_null_macro( glGetInternalformativ )
					, booctor_null_macro( glFramebufferRenderbuffer )
					, booctor_null_macro( glGetFramebufferAttachmentParameteriv )
					, booctor_null_macro( glActiveTexture )
					, booctor_null_macro( glUniform1i )
					, booctor_null_macro( glGenBuffers )
					, booctor_null_macro( glEnableVertexAttribArray )
					, booctor_null_macro( glBindBuffer )
					, booctor_null_macro( glVertexAttribPointer )
					, booctor_null_macro( glBufferData )
					, booctor_null_macro( glBufferSubData )
					, booctor_null_macro( glCreateProgram )
					, booctor_null_macro( glCreateShader )
					, booctor_null_macro( glShaderSource )
					, booctor_null_macro( glCompileShader )
					, booctor_null_macro( glDeleteShader )
					, booctor_null_macro( glDetachShader )
					, booctor_null_macro( glAttachShader )
			{
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
				::booldog::result_module resmod;
				if( _loader->mbsload( &resmod , _allocator , "opengl32" , 0 , debuginfo_macros ) )
				{	
					_opengl = resmod.module;

					::booldog::result_pointer resptr;
#ifdef __WINDOWS__
					get_opengl_function( wglShareLists );
					get_opengl_function( wglGetProcAddress );
					get_opengl_function( wglGetCurrentDC );
					get_opengl_function( wglCreateContext );
					get_opengl_function( wglDeleteContext );
					get_opengl_function( wglMakeCurrent );
					get_opengl_function( wglGetCurrentContext );
#else
#ifdef __ANDROID__
					get_opengl_function( eglGetProcAddress );
#else
					get_opengl_function( glXQueryExtension );
					get_opengl_function( glXGetConfig );
					get_opengl_function( glXGetProcAddress );
					get_opengl_function( glXCreateContext );
					get_opengl_function( glXDestroyContext );
					get_opengl_function( glXSwapBuffers );
					get_opengl_function( glXGetCurrentContext );
					get_opengl_function( glXMakeCurrent );			
#endif
#endif							
					get_opengl_function( glColor4f );
					get_opengl_function( glRotatef );
					get_opengl_function( glGetError );
					get_opengl_function( glDisableClientState );
					get_opengl_function( glDrawArrays );
					get_opengl_function( glVertexPointer );
					get_opengl_function( glPixelStorei );
					get_opengl_function( glEnable );
					get_opengl_function( glBindTexture );
					get_opengl_function( glDisable );
					get_opengl_function( glStencilFunc );
					get_opengl_function( glColorMask );
					get_opengl_function( glStencilOp );
					get_opengl_function( glBlendFunc );
					get_opengl_function( glGetFloatv );
					get_opengl_function( glGetBooleanv );
					get_opengl_function( glTexParameteri );
					get_opengl_function( glTexEnvf );
					get_opengl_function( glTexImage2D );
					get_opengl_function( glTexImage1D );
					get_opengl_function( glLoadIdentity );							
					get_opengl_function( glGenTextures );
					get_opengl_function( glDeleteTextures );
					get_opengl_function( glEnableClientState );
					get_opengl_function( glTexCoordPointer );
					get_opengl_function( glClearStencil );
					get_opengl_function( glColorPointer );
					get_opengl_function( glTexSubImage2D );
					get_opengl_function( glTexSubImage1D );
					get_opengl_function( glPushMatrix );
					get_opengl_function( glMatrixMode );
					get_opengl_function( glDepthFunc );
					get_opengl_function( glClearDepthf );
					get_opengl_function( glClearDepth );
#ifdef __ANDROID__
					get_opengl_function( glOrthof );
#else
					get_opengl_function( glOrtho );
#endif
					get_opengl_function( glClearColor );
					get_opengl_function( glShadeModel );
					get_opengl_function( glViewport );
					get_opengl_function( glGetString );
					get_opengl_function( glClear );
					get_opengl_function( glScalef );
					get_opengl_function( glHint );
					get_opengl_function( glFlush );
					get_opengl_function( glFinish );
					get_opengl_function( glPopMatrix );
					get_opengl_function( glEnd );
					get_opengl_function( glVertex3f );
					get_opengl_function( glTexCoord2f );
					get_opengl_function( glBegin );							
					get_opengl_function( glGetIntegerv );
					get_opengl_function( glRasterPos3f );
					get_opengl_function( glPixelZoom );
					get_opengl_function( glDrawPixels );
#ifdef __WINDOWS__
					::booldog::result_module resmodGdi32 , resmodUser32;
					if( _loader->mbsload( &resmodGdi32 , _allocator , "Gdi32" , 0 , debuginfo ) )
					{
						if( _loader->mbsload( &resmodUser32 , _allocator , "User32" , 0 , debuginfo ) )
						{
							::booldog::result_pointer resptr;
							if( resmodGdi32.module->method( &resptr , _allocator , "SetPixelFormat" , debuginfo ) == false )
							{
								res->copy( resptr );
								goto goto_unload;
							}
							::booldog::typedefs::SetPixelFormat pSetPixelFormat = (::booldog::typedefs::SetPixelFormat)resptr.pres;
							if( resmodGdi32.module->method( &resptr , _allocator , "ChoosePixelFormat" , debuginfo ) == false )
							{
								res->copy( resptr );
								goto goto_unload;
							}
							::booldog::typedefs::ChoosePixelFormat pChoosePixelFormat = (::booldog::typedefs::ChoosePixelFormat)resptr.pres;
							if( resmodGdi32.module->method( &resptr , _allocator , "DescribePixelFormat" , debuginfo ) == false )
							{
								res->copy( resptr );
								goto goto_unload;
							}
							::booldog::typedefs::DescribePixelFormat pDescribePixelFormat = (::booldog::typedefs::DescribePixelFormat)resptr.pres;
							if( resmodUser32.module->method( &resptr , _allocator , "GetDC" , debuginfo ) == false )
							{
								res->copy( resptr );
								goto goto_unload;
							}
							::booldog::typedefs::GetDC pGetDC = (::booldog::typedefs::GetDC)resptr.pres;
							if( resmodGdi32.module->method( &resptr , _allocator , "SwapBuffers" , debuginfo ) == false )
							{
								res->copy( resptr );
								goto goto_unload;
							}
							_SwapBuffers = (::booldog::typedefs::SwapBuffers)resptr.pres;

							PIXELFORMATDESCRIPTOR pfd;
							pfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );
							pfd.nVersion = 1;
							pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
							pfd.iPixelType = PFD_TYPE_RGBA;
							pfd.cColorBits = 32;//pfd.cColorBits     = 32;
							pfd.cRedBits = 0;//pfd.cRedBits       = 8;
							pfd.cRedShift = 0;//pfd.cRedShift      = 16;
							pfd.cGreenBits = 0;//pfd.cGreenBits     = 8;
							pfd.cGreenShift = 0;//pfd.cGreenShift    = 8;
							pfd.cBlueBits = 0;//pfd.cBlueBits      = 8;
							pfd.cBlueShift = 0;
							pfd.cAlphaBits = 0;
							pfd.cAlphaShift = 0;
							pfd.cAccumBits = 0;    //pfd.cAccumBits     = 64;    
							pfd.cAccumRedBits = 0;//pfd.cAccumRedBits  = 16;
							pfd.cAccumGreenBits = 0;//pfd.cAccumGreenBits   = 16;
							pfd.cAccumBlueBits = 0;//pfd.cAccumBlueBits    = 16;
							pfd.cAccumAlphaBits = 0;
							pfd.cDepthBits = 32;
							pfd.cStencilBits = 32;//pfd.cStencilBits      = 8;
							pfd.cAuxBuffers = 0;
							pfd.iLayerType = PFD_MAIN_PLANE;
							pfd.bReserved = 0;
							pfd.dwLayerMask = 0;
							pfd.dwVisibleMask = 0;
							pfd.dwDamageMask = 0;		

							_hwnd = hwnd;
							_hdc = pGetDC( _hwnd );

							int pixel_format_index = pChoosePixelFormat( _hdc , &pfd );
							if( pixel_format_index == 0 )						
							{
								pixel_format_index = 1;    
								if( pDescribePixelFormat( _hdc , pixel_format_index , sizeof( PIXELFORMATDESCRIPTOR ) , &pfd ) == 0 )
								{
									res->GetLastError();
									goto goto_unload;
								}
							}
							if( pSetPixelFormat( _hdc, pixel_format_index, &pfd ) == FALSE )
							{
								res->GetLastError();
								goto goto_unload;
							}
							_ctx = _wglCreateContext( _hdc );
						}
						else
						{
							res->copy( resmodUser32 );
							goto goto_unload;
						}
					}
					else
					{
						res->copy( resmodGdi32 );
						goto goto_unload;
					}
#else
#ifdef __ANDROID__
#else
					_gl_context = ::rux::gui::engine::OpenGL::glXCreateContext( window->_x_display , ::rux::gui::engine::_x_visual_info , NULL , true );
					if( _gl_context == NULL )
						_gl_context = ::rux::gui::engine::OpenGL::glXCreateContext( window->_x_display , ::rux::gui::engine::_x_visual_info , NULL , false );
#endif
#endif				
					if( _ctx == 0 )
					{
						res->glGetError( _glGetError() );
						goto goto_unload;
					}
					if( make_current( res , debuginfo ) )
					{
						bool GL_ARB_shader_objects = false , GL_ARB_shading_language_100 = false 
							, GL_ARB_vertex_shader = false , GL_ARB_fragment_shader = false , GL_ARB_vertex_buffer_object = false 
							, WGL_EXT_swap_control = false , WGL_ARB_create_context = false , GL_EXT_framebuffer_object = false;
#ifdef __WINDOWS__
						PROC wglGetExtString = glGetProcAddress("wglGetExtensionsStringEXT"); 
						if( wglGetExtString )
							supporting( ( (char* ( __stdcall* )( HDC ) )wglGetExtString )( _hdc ) , GL_ARB_shader_objects 
							, GL_ARB_shading_language_100 , GL_ARB_vertex_shader , GL_ARB_fragment_shader , GL_ARB_vertex_buffer_object
							, WGL_EXT_swap_control , WGL_ARB_create_context , GL_EXT_framebuffer_object );
						wglGetExtString = glGetProcAddress("wglGetExtensionsStringARB"); 
						if( wglGetExtString )
							supporting( ( (char* ( __stdcall* )( HDC ) )wglGetExtString )( _hdc ) , GL_ARB_shader_objects 
							, GL_ARB_shading_language_100 , GL_ARB_vertex_shader , GL_ARB_fragment_shader , GL_ARB_vertex_buffer_object 
							, WGL_EXT_swap_control , WGL_ARB_create_context , GL_EXT_framebuffer_object );
#endif
						if( _glGetString )
						{
							const char* string = (char*)_glGetString( GL_VERSION );
							_renderer = (char*)_glGetString ( GL_RENDERER );
							string = (char*)_glGetString( GL_SHADING_LANGUAGE_VERSION );

							supporting( (const char*)_glGetString( GL_EXTENSIONS ) , GL_ARB_shader_objects 
							, GL_ARB_shading_language_100 , GL_ARB_vertex_shader , GL_ARB_fragment_shader , GL_ARB_vertex_buffer_object
							, WGL_EXT_swap_control , WGL_ARB_create_context , GL_EXT_framebuffer_object );
						}
#ifdef __WINDOWS__
						if( WGL_ARB_create_context )
						{
							glGetProcAddress_macro( wglCreateContextAttribs );
							if( _wglCreateContextAttribs )
							{
								int attribs[] =
								{
									WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
									WGL_CONTEXT_MINOR_VERSION_ARB, 1,
									WGL_CONTEXT_FLAGS_ARB, 0,
									0
								};
							}
						}
#endif


						if( GL_EXT_framebuffer_object )
						{
							glGetProcAddress_macro( glIsRenderbuffer );
							glGetProcAddress_macro( glBindRenderbuffer );
							glGetProcAddress_macro( glDeleteRenderbuffers );
							glGetProcAddress_macro( glGenRenderbuffers );
							glGetProcAddress_macro( glRenderbufferStorage );
							glGetProcAddress_macro( glGetRenderbufferParameteriv );
							glGetProcAddress_macro( glIsFramebuffer );
							glGetProcAddress_macro( glBindFramebuffer );
							glGetProcAddress_macro( glDeleteFramebuffers );
							glGetProcAddress_macro( glGenFramebuffers );
							glGetProcAddress_macro( glCheckFramebufferStatus );
							glGetProcAddress_macro( glFramebufferTexture1D );
							glGetProcAddress_macro( glFramebufferTexture2D );
							glGetProcAddress_macro( glFramebufferTexture3D );
							glGetProcAddress_macro( glFramebufferRenderbuffer );
							glGetProcAddress_macro( glGetFramebufferAttachmentParameteriv );
							glGetProcAddress_macro( glGenerateMipmap );
						}

						if( GL_ARB_vertex_buffer_object )
						{
							glGetProcAddress_macro( glBindBuffer );
							if( _glBindBuffer )
							{
								_glBindBuffer( GL_PIXEL_UNPACK_BUFFER , 0 );
								if( _glGetError() == 0 )
								{
									glGetProcAddress_macro( glGenBuffers );
									glGetProcAddress_macro( glBufferData );
									glGetProcAddress_macro( glMapBuffer );
									glGetProcAddress_macro( glUnmapBuffer );
									glGetProcAddress_macro( glDeleteBuffers );
								}
								else
									_glBindBuffer = 0;
							}
						}
						glGetProcAddress_macro( glLinkProgram );
						glGetProcAddress_macro( glBindFragDataLocation );
						glGetProcAddress_macro( glGetAttribLocation );
						glGetProcAddress_macro( glGetUniformLocation );
						glGetProcAddress_macro( glUseProgram );
						glGetProcAddress_macro( glValidateProgram );
						glGetProcAddress_macro( glGetProgramiv );
						glGetProcAddress_macro( glGetShaderiv );
						glGetProcAddress_macro( glDeleteProgram );
						glGetProcAddress_macro( glDisableVertexAttribArray );
						glGetProcAddress_macro( glUniform4fv );
						
						
						glGetProcAddress_macro( glUniform1f );
						glGetProcAddress_macro( glUniform1fv );
						glGetProcAddress_macro( glUniform4f );
		#ifdef __ANDROID__
		#else
						glGetProcAddress_macro( glGetObjectParameteriv );
						glGetProcAddress_macro( glGetInfoLog );
		#endif
						glGetProcAddress_macro( glStencilOpSeparate );
						glGetProcAddress_macro( glActiveStencilFace );
		#ifdef __WINDOWS__
						if( WGL_EXT_swap_control )
						{
							glGetProcAddress_macro( wglGetSwapInterval );
							glGetProcAddress_macro( wglSwapInterval );
						}
		#endif
						glGetProcAddress_macro( glMultiDrawArrays );










						glGetProcAddress_macro( glGetInternalformativ );

						glGetProcAddress_macro( glActiveTexture );
						glGetProcAddress_macro( glUniform1i );
						
						glGetProcAddress_macro( glEnableVertexAttribArray );
						
						glGetProcAddress_macro( glVertexAttribPointer );
						
						glGetProcAddress_macro( glBufferSubData );
						glGetProcAddress_macro( glCreateProgram );
						glGetProcAddress_macro( glCreateShader );
						glGetProcAddress_macro( glShaderSource );
						glGetProcAddress_macro( glCompileShader );
						glGetProcAddress_macro( glDeleteShader );
						glGetProcAddress_macro( glDetachShader );
						glGetProcAddress_macro( glAttachShader );

						if( _glGetIntegerv )
							_glGetIntegerv( GL_MAX_TEXTURE_SIZE , &_max_texture_size );
				
						_glClearColor( 1.0f , 0.0f , 0.0f , 0.0f );
						_glShadeModel( GL_SMOOTH );
						if( _glClearDepthf )
							_glClearDepthf( 1.0f );
						else if( _glClearDepth )
							_glClearDepth( 1.0 );
						_glEnable( GL_DEPTH_TEST );
						_glDepthFunc( GL_LESS );
#ifdef __WINDOWS__
						if( _wglSwapInterval )
						{
							if( _wglSwapInterval( 0 ) == FALSE )
								printf( "wglSwapInterval FALSE\n" );
						}
#endif
						make_empty( res , debuginfo );
					}
goto_unload:
#ifdef __WINDOWS__
					if( resmodUser32.module )
						_loader->unload( 0 , resmodUser32.module , 0 , 0 , debuginfo );
					if( resmodGdi32.module )
						ploader->unload( 0 , resmodGdi32.module , 0 , 0 , debuginfo );
#endif
				}
				else
					res->copy( resmod );
			};
			~context( void )
			{
				if( _hdc )
				{
					::booldog::result_module resmodUser32;
					if( _loader->mbsload( &resmodUser32 , _allocator , "User32" , 0 , debuginfo_macros ) )
					{
						::booldog::result_pointer resptr;
						if( resmodUser32.module->method( &resptr , _allocator , "ReleaseDC" , debuginfo_macros ) )
						{
							::booldog::typedefs::ReleaseDC pReleaseDC = (::booldog::typedefs::ReleaseDC)resptr.pres;					
							pReleaseDC( _hwnd , _hdc );
						}
						_loader->unload( 0 , resmodUser32.module , 0 , 0 , debuginfo_macros );
					}
				}
				if( _opengl )
					_loader->unload( 0 , _opengl , 0 , 0 , debuginfo_macros );
			};
			bool swap_buffers( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
#ifdef __WINDOWS__
				if( _SwapBuffers( _hdc ) == FALSE )
					res->GetLastError();
				//if( ::rux::gui::engine::_use_gl_finish )
				//	::rux::gui::engine::OpenGL::glFinish( __FUNCTION__ , __LINE__ , ___rux__thread_index1986 );
#elif defined( __UNIX__ )		
#ifdef __ANDROID__
#else
				_glXSwapBuffers( _x_display , _x_window );
#endif
#endif
				return res->succeeded();
			};
			virtual void before_resize( void )
			{
				::booldog::result res;
				make_current( &res , debuginfo_macros );
			};
			virtual void after_resize( void )
			{
				::booldog::result res;
				make_empty( &res , debuginfo_macros );
			};
			virtual void resize( int width , int height )
			{
				if( _ctx )
				{
					_glLoadIdentity();
					_glViewport( 0 , 0 , width , height );
					_glMatrixMode( GL_PROJECTION );
					_glLoadIdentity();
#ifdef __ANDROID__
					_glOrthof( 0 , width , height , 0 , -1.f , 1.f );
#else
					_glOrtho( 0 , width , height , 0 , -1.f , 1.f );
#endif
					_glMatrixMode( GL_MODELVIEW );
					_glLoadIdentity();
				}
			};
			bool make_empty( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
#ifdef __WINDOWS__
				if( _wglMakeCurrent( _hdc , NULL ) == FALSE )
#elif defined( __UNIX__ )				
#ifdef __ANDROID__
#else
				if( _glXMakeCurrent( _x_display , None , NULL ) == 0 )
#endif
#endif
					res->glGetError( _glGetError() );
				return res->succeeded();
			};
			bool make_current( ::booldog::result* pres , const ::booldog::debug::info& debuginfo = debuginfo_macros )
			{
				debuginfo = debuginfo;
				::booldog::result locres;
				BOOINIT_RESULT( ::booldog::result );
#ifdef __WINDOWS__
				if( _wglMakeCurrent( _hdc , _ctx ) == FALSE )
#elif defined( __UNIX__ )
#ifdef __ANDROID__
#else
				if( _glXMakeCurrent( _x_display , _x_window , _ctx ) == 0 )
#endif
#endif
					res->glGetError( _glGetError() );
				return res->succeeded();
			};
		};
	};
};
#endif