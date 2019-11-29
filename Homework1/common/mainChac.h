#ifndef HMAINCHAC
#define HMAINCHAC

#include "../header/Angel.h"

typedef Angel::vec4 color4;
typedef Angel::vec4 point4;

#define QUAD_Num 6

class cMainChac {
private:
	vec4 _Points[QUAD_Num];
	vec4 _Colors[QUAD_Num];
	//vao
	GLuint _uiVao;
	//vbo
	GLuint _uiBuffer;
	//shader
	GLuint _uiProgram;
	//vertex position attribute
	GLuint _uiModelView;
	GLuint _uiProjection;
	//matrix
	mat4 _mxView;
	mat4 _mxProjection;
	mat4 _mxMVFinal;
	mat4 _mxTRS;

	//record changes for matrix
	bool _bUpdateMV;
	bool _bUpdateProj;
	void CreateBufferObject();

public:
	cMainChac();
	void SetShader(mat4 &mxModelView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _uiProgram; }
	void SetViewMatrix(mat4 &mat);
	void SetProjectionMatrix(mat4 &mat);
	void SetTRSMatrix(mat4 &mat);
	void SetColors(GLfloat vColor[4]);
	void SetVTXColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]);

	void Draw();
	void DrawW();
};
#endif // HMainChac
