in vec4 vPosition;
in vec4 vColors;
out vec4 colors;

uniform mat4 ModelView;
uniform mat4 Projection;

void main(){
gl_position = Projection * ModelView * vPosition;
colors = vColors;
}