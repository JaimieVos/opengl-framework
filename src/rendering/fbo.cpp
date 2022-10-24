#include "fbo.h"

#include <GL/glew.h>

FBO::FBO()
{
	glGenFramebuffers(1, &m_Id);
}

void FBO::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
}

void FBO::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}