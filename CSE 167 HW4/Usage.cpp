void initializeGL()
{
	// Load shaders, link program for drawing sphere
	m_sphereProgramID = LoadShaders("shader/sphereShader.vert", "shader/sphereShader.frag");
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(m_sphereProgramID, "vertexPosition_modelspace");
	
	// load OpenGL resources needed by the sphere
	// pass the vertex position id to it
	sphere.init(vertexPosition_modelspaceID);
}

void paintGL() {
	// use corresponding shader program, and set the transformation matrices
	glUseProgram(m_sphereProgramID);
	GLuint projMatrixID = glGetUniformLocation(m_sphereProgramID, "projMatrix");
	GLuint mvMatrixID = glGetUniformLocation(m_sphereProgramID, "mvMatrix");
	glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr(m_projMatrix));
	glUniformMatrix4fv(mvMatrixID, 1, GL_FALSE, glm::value_ptr(m_mvMatrix));
	sphere.draw();
}

void cleanUp() {
	sphere.cleanup();
}