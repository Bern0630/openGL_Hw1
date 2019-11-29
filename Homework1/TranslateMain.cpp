#include "Common\CQuad.h"
#include "Common\CQuadEX1.h"
#include "Header\Angel.h"


#define SPACE_KEY 32


CQuad *g_Aero;	// 宣告 Quad 指標物件，結束時記得釋放


//translate position(AutomaticTranslation)
vec2 position;

mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;

int g_iAxis = 2; // 旋轉軸，0:X, 1:Y, 2:Z
GLfloat g_fAngle = 0;   // X/Y/Z 三軸的旋轉角度
GLfloat g_fDir = 1;     // 旋轉方向

bool m_bUpdate = false;
bool m_bAutoRotation = false; // Controlled by Space Key

void IdleProcess();

void init(void)
{
	// 必須在 glewInit(); 執行完後,在執行物件實體的取得
	g_Aero = new CQuad;
	//初始化
	position = vec2();
	//  產生 projection 矩陣，此處為產生正投影矩陣
	g_mxProjection = Ortho(-20.0f, 20.0f, -20.0f, 20.0f, -2.0f, 2.0f);
	g_Aero->SetShader(g_mxModelView, g_mxProjection);

	glClearColor(0.0, 0.0, 0.0, 1.0); // black background
}

void AutomaticTranslation(float delta) {
	mat4 mxTran;

	position.y += 0.005f;
	if (position.y >= -5.0f && position.y <= 5.0f)position.y += 0.05f;
	if (position.y >= 25.0f)position.y = -25.0f; 
	
	mxTran = Translate(position.x, position.y, 0.0f);
	g_Aero->SetTRSMatrix(mxTran);

	//glutPostRedisplay();     // 目前的視窗需要被重畫
}

float g_TotTime = 0;


void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window
	g_Aero->Draw();
	glutSwapBuffers();	// 交換 Frame Buffer
}

void onFrameMove(float delta)
{

	if (m_bAutoRotation) {
		AutomaticTranslation(delta);
		GL_Display();
	}
}

void reset(){
	g_iAxis = 2;
	g_fAngle = 0;
	g_fDir = 1;
	m_bAutoRotation = false;
	g_Aero->SetTRSMatrix(g_mxModelView);
	//glutPostRedisplay();
}

void Win_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case  SPACE_KEY:
		m_bAutoRotation = !m_bAutoRotation;
		break;
	case 82: // R key
	case 114: // r key
		reset();
		break;
	case 033:
		delete g_Aero;
		exit(EXIT_SUCCESS);
		break;
		}
}

void Win_Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
		break;
	case GLUT_MIDDLE_BUTTON:  // 目前按下的是滑鼠中鍵 ，換成 Y 軸
		break;
	case GLUT_RIGHT_BUTTON:   // 目前按下的是滑鼠右鍵
		break;
	default:
		break;
	}
}

void Win_SpecialKeyboard(int key, int x, int y) {
	mat4 mxRot;
	if (!m_bAutoRotation) { // 沒有自動旋轉下才有作用
		switch (key) {
		case GLUT_KEY_LEFT:		// 目前按下的是向左方向鍵
			g_fAngle += 2.0;		// 逆時針為正方向
			break;
		case GLUT_KEY_RIGHT:	// 目前按下的是向右方向鍵
			g_fAngle -= 2.0;		// 順時針為負方向
			break;
		default:
			break;
		}

		// 計算旋轉矩陣並更新到 Shader 中
		if (g_iAxis == 0)  mxRot = RotateX(g_fAngle);
		else if (g_iAxis == 1)  mxRot = RotateY(g_fAngle);
		else mxRot = RotateZ(g_fAngle);

		g_Aero->SetTRSMatrix(mxRot);
		glutPostRedisplay();
	}
}

void GL_Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Draw two triangles");

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutMouseFunc(Win_Mouse);
	glutKeyboardFunc(Win_Keyboard);	// 處理 ASCI 按鍵如 A、a、ESC 鍵...等等
	glutSpecialFunc(Win_SpecialKeyboard);	// 處理 NON-ASCI 按鍵如 F1、Home、方向鍵...等等
	glutDisplayFunc(GL_Display);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);


	glutMainLoop();
	return 0;
}
