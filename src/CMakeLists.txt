add_executable(tiffcruncher
	main.cpp panic.cpp
	FileUtils.cpp
	GfxWork.cpp
	GLRuntime.cpp GLObject.cpp
	GLContext.cpp GLBuffer.cpp GLVertexArray.cpp
	GLShader.cpp GLTexture.cpp
	GLFramebuffer.cpp GLRenderbuffer.cpp
	PixelImage.cpp
)

target_link_libraries(tiffcruncher ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARIES} ${TIFF_LIBRARY} ${PNG_LIBRARY})
