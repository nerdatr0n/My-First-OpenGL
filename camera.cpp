
//#include "camera.h"
//
//#include "glm.hpp"
//#include "gtc/matrix_transform.hpp"
//#include "gtc/type_ptr.hpp"
//
//using namespace glm;
//
//
//
//// View Matrix
//mat4 view = lookAt(camPos, camPos + camLookDir, camUpDir);
//
//GLuint viewLoc = glGetUniformLocation(program, "view");
//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
//
//
//// Orthographic Center Camera
//mat4 proj;
//float halfScreenWidth = (float)SCR_WIDTH * 0.5f;
//float halfScreenHeight = (float)SCR_HEIGHT * 0.5f;
//proj = ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);
//GLuint projLoc = glGetUniformLocation(program, "proj");
//glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));