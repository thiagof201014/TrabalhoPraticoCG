#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <GL/gl.h>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_mixer.h>

#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

#ifdef GL_VERSION_1_1
    static GLuint texName;
#endif

// Define se a iluminação está ligada ou desligada
int light0Ligado = 1;
// Define se a animação do cd está ligada ou desligada
int animacaoCD = 0;

// Ponto central do piano
float PCpiano_x = 0.0;
float PCpiano_y = 0.0;
float PCpiano_z = -1.0;

// Escala do piano
float Epiano_x = 1.0;
float Epiano_y = 1.0;
float Epiano_z = 1.0;

// Angulo de rotacao do CD
int rotationCD = 0;

// Parametros para animação das teclas do piano
int key_pressed[7] = {0, 0, 0, 0, 0, 0, 0};
float keys_ypositions[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};


void makeCheckImage(void)
{
    int i, j, c;
    for (i = 0; i < checkImageHeight; i++) {
        for (j = 0; j < checkImageWidth; j++) {
            c = ((((i&0x8)==0)^((j&0x8))==0))*255;
            checkImage[i][j][0] = (GLubyte) c;
            checkImage[i][j][1] = (GLubyte) c;
            checkImage[i][j][2] = (GLubyte) c;
            checkImage[i][j][3] = (GLubyte) 255;
        }
    }
}

GLuint texId;

void Texture() {
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
    checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void desenharEstante(){
    float x_init = -1.0, x_end = 0.5, y_init = -1.0, y_end = 1.0, z_init = -1.0, z_end = -0.5;

    // Desenhar o paralelepípedo
    glBegin(GL_QUADS);

    // Face traseira
    glColor3f(0.15, 0.15, 0.15);
    glVertex3f(x_init, y_init, z_init);
    glVertex3f(x_init, y_end, z_init);
    glVertex3f(x_end, y_end, z_init);
    glVertex3f(x_end, y_init, z_init);

    // Face lateral esquerda
    glColor3f(0.27, 0.29, 0.32);
    glVertex3f(x_init, y_init, z_init);
    glVertex3f(x_init, y_init, z_end);
    glVertex3f(x_init, y_end, z_end);
    glVertex3f(x_init, y_end, z_init);

    // Face lateral direita
    glColor3f(0.27, 0.29, 0.32);
    glVertex3f(x_end, y_init, z_end);
    glVertex3f(x_end, y_init, z_init);
    glVertex3f(x_end, y_end, z_init);
    glVertex3f(x_end, y_end, z_end);

    // Face superior
    glColor3f(0.27, 0.29, 0.32);
    glVertex3f(x_init, y_end, z_init);
    glVertex3f(x_end, y_end, z_init);
    glVertex3f(x_end, y_end, z_end);
    glVertex3f(x_init, y_end, z_end);

    // Face inferior
    glColor3f(0.27, 0.29, 0.32);
    glVertex3f(x_init, y_init, z_init);
    glVertex3f(x_end, y_init, z_init);
    glVertex3f(x_end, y_init, z_end);
    glVertex3f(x_init, y_init, z_end);

    glEnd();
}

void desenhaCD(){
  glColor3f(0, 0, 0); // Define a cor vermelha

  // Desenha o círculo externo do CD
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(0.0f, 0.0f, 0.1f); // Centro do círculo
  for (float angle = 0.0f; angle <= 360.0f; angle += 1.0f) {
    float radian = angle * (M_PI / 180.0f);
    float x = 0.9f * sin(radian);
    float y = 0.9f * cos(radian);
    glVertex2f(x, y);
  }
  glEnd();

  // Desenha o círculo interno do CD
  glColor3f(1, 1, 1); // Define a cor branca
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(0.0f, 0.0f, 0.2f); // Centro do círculo
  for (float angle = 0.0f; angle <= 360.0f; angle += 1.0f) {
    float radian = angle * (M_PI / 180.0f);
    float x = 0.4f * sin(radian);
    float y = 0.4f * cos(radian);
    glVertex2f(x, y);
  }
  glEnd();

}

void desenhar_teclas()
{
    float x_init = -1.0, x_end = -0.85, y_init = -0.075, y_end = 0.075, z_init = -1.0, z_end = 0.0, k = 0.2;
    for(int i = 0; i < 14; i++){
        glPushMatrix();
            // Translação para a animação das teclas
            if(i < 7){
                glTranslatef(0, keys_ypositions[i], 0);
            }

            // Desenhar o paralelepípedo
            glBegin(GL_QUADS);
            // Face frontal
            glColor3f(k, k, k);  // Vermelho
            glVertex3f(x_init, y_init, z_end);
            glVertex3f(x_end, y_init, z_end);
            glVertex3f(x_end, y_end, z_end);
            glVertex3f(x_init, y_end, z_end);

            // Face traseira
            glColor3f(k, k, k);
            glVertex3f(x_init, y_init, z_init);
            glVertex3f(x_end, y_init, z_init);
            glVertex3f(x_end, y_end, z_init);
            glVertex3f(x_init, y_end, z_init);

            // Face lateral esquerda
            glColor3f(k, k, k);
            glVertex3f(x_init, y_init, z_init);
            glVertex3f(x_init, y_init, z_end);
            glVertex3f(x_init, y_end, z_end);
            glVertex3f(x_init, y_end, z_init);

            // Face lateral direita
            glColor3f(k, k, k);
            glVertex3f(x_end, y_init, z_init);
            glVertex3f(x_end, y_init, z_end);
            glVertex3f(x_end, y_end, z_end);
            glVertex3f(x_end, y_end, z_init);

            // Face superior
            glColor3f(k, k, k);
            glVertex3f(x_init, y_end, z_init);
            glVertex3f(x_end, y_end, z_init);
            glVertex3f(x_end, y_end, z_end);
            glVertex3f(x_init, y_end, z_end);

            // Face inferior
            glColor3f(k, k, k);
            glVertex3f(x_init, y_init, z_init);
            glVertex3f(x_end, y_init, z_init);
            glVertex3f(x_end, y_init, z_end);
            glVertex3f(x_init, y_init, z_end);

            glEnd();
        glPopMatrix();

        if(k < 1.0){
            k += 0.1;
        }
        else{
            k = 0;
        }

        x_init += 0.15;
        x_end += 0.15;
    }
}

void desenhar_corpo_piano(){
    float x_init = -1.05, x_end = 1.15, y_init = -1.0, y_end = 1.0, z_init = -1.0, z_end = -2.0;

    //Aplica a textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

    // Desenhar o corpo
    glBegin(GL_QUADS);

    // Face traseira
    glColor3f(0.5, 0.0, 0.0); // Veermelho
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x_init, y_init, z_init);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(x_init, y_end, z_init);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x_end, y_end, z_init);
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(x_end, y_init, z_init);


    // Face lateral esquerda
    glColor3f(0.2, 0.2, 0.2); // Preto
    glVertex3f(x_init, y_init, z_init);
    glVertex3f(x_init, y_init, z_end);
    glVertex3f(x_init, y_end, z_end);
    glVertex3f(x_init, y_end, z_init);

    // Face lateral direita
    glColor3f(0.2, 0.2, 0.2); // Cinza
    glVertex3f(x_end, y_init, z_end);
    glVertex3f(x_end, y_init, z_init);
    glVertex3f(x_end, y_end, z_init);
    glVertex3f(x_end, y_end, z_end);

    // Face superior
    glColor3f(0.0, 0.0, 0.0); // Preto
    glVertex3f(x_init, y_end, z_init);
    glVertex3f(x_end, y_end, z_init);
    glVertex3f(x_end, y_end, z_end);
    glVertex3f(x_init, y_end, z_end);

    // Face inferior
    glColor3f(0.0, 0.0, 0.0); // Preto
    glVertex3f(x_init, y_init, z_init);
    glVertex3f(x_end, y_init, z_init);
    glVertex3f(x_end, y_init, z_end);
    glVertex3f(x_init, y_init, z_end);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void desenhar_pes_piano(){
    float x_init = -1.0, x_end = -0.9, y_init = -1.0, y_end = -0.075, z_init = -0.05, z_end = -0.25;

    for(int i = 0; i < 2; i++){
        glBegin(GL_QUADS);

        // Face traseira
        glColor3f(1.0, 1.0, 0.0); // Verde
        glVertex3f(x_init, y_init, z_init);
        glVertex3f(x_init, y_end, z_init);
        glVertex3f(x_end, y_end, z_init);
        glVertex3f(x_end, y_init, z_init);

        // Face lateral esquerda
        glColor3f(0.0, 0.0, 1.0); // Azul
        glVertex3f(x_init, y_init, z_init);
        glVertex3f(x_init, y_init, z_end);
        glVertex3f(x_init, y_end, z_end);
        glVertex3f(x_init, y_end, z_init);

        // Face lateral direita
        glColor3f(1.0, 0.0, 0.0); // Amarelo
        glVertex3f(x_end, y_init, z_end);
        glVertex3f(x_end, y_init, z_init);
        glVertex3f(x_end, y_end, z_init);
        glVertex3f(x_end, y_end, z_end);

        // Face superior
        glColor3f(1.0, 0.0, 1.0); // Magenta
        glVertex3f(x_init, y_end, z_init);
        glVertex3f(x_end, y_end, z_init);
        glVertex3f(x_end, y_end, z_end);
        glVertex3f(x_init, y_end, z_end);

        // Face inferior
        glColor3f(0.0, 1.0, 1.0); // Ciano
        glVertex3f(x_init, y_init, z_init);
        glVertex3f(x_end, y_init, z_init);
        glVertex3f(x_end, y_init, z_end);
        glVertex3f(x_init, y_init, z_end);
        glEnd();

        x_init += 2;
        x_end += 2;
    }
}

void desenhar_piano()
{
    desenhar_teclas();
    desenhar_corpo_piano();
    desenhar_pes_piano();
}

void desenhar_parede_fundo(){
    glBegin(GL_QUADS);

    glColor3f(0.1, 0.5, 0.1); // Verde
    glVertex3f(-12, -1, -3.5);
    glVertex3f(-12, 3, -3.5);
    glVertex3f(12, 3, -3.5);
    glVertex3f(12, -1, -3.5);

    glEnd();

}

void desenhar_chao(){
glBegin(GL_QUADS);

    glColor3f(0.9, 1.0, 0.9); // Verde
    glVertex3f(-12, -1, -3.5);
    glVertex3f(-12, -1, 3);
    glVertex3f(12, -1, 3);
    glVertex3f(12, -1, -3.5);

    glEnd();
}

// Função de renderização
void renderScene() {
    // Limpar o buffer de cor e o buffer de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Definir a matriz de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);

    // Definir a matriz de visualização
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 2.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Desenhar o piano
    glPushMatrix();
        glTranslatef(PCpiano_x-0.5, PCpiano_y, PCpiano_z); // Move o piano ao seu ponto central
        glScalef(Epiano_x, Epiano_y, Epiano_z); // Ajusta a escala do piano
        desenhar_piano();
    glPopMatrix();

    // Desenhar a estante
    glPushMatrix();
        glTranslatef(2.5, 0.52, -2);
        glScalef(1.25, 1.5, 1);
        desenharEstante();
    glPopMatrix();

    // Desenhar o disco
    glPushMatrix();
        glScalef(0.25, 0.25, 1.0);
        glTranslatef(-9.0, 5.0, -3.0);
        glRotatef(rotationCD, 0.05, 0, 1);
        desenhaCD();
    glPopMatrix();

    desenhar_parede_fundo();
    desenhar_chao();

    // Trocar os buffers para exibir a cena renderizada
    glutSwapBuffers();
}

// Função de inicialização
void init(){
    glClearColor(0.5, 0.5, 0.5, 0.0); // Define a cor de fundo para cinza
    glEnable(GL_DEPTH_TEST);          // Habilita o teste de profundidade

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // Define as propriedades da primeira fonte de luz (GL_LIGHT0)
    GLfloat light0Position[] = {2.0, 2.0, 2.0, 0.0};   // Posição da luz
    GLfloat light0Diffuse[] = {1.0, 1.0, 1.0, 1.0};    // Cor difusa da luz
    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0); // Define a perspectiva de visualização
    glMatrixMode(GL_MODELVIEW);
}

// Função para a animação do cd
void cdAnimator(){
    if(animacaoCD == 1){
        if(rotationCD < 360){rotationCD += 10;}
        else {rotationCD = 0;}
    }
}

// Função para a animação das teclas do piano
void keysAnimator(){
    float variacao = 0.01;
    float deslocamento_max = -0.1;
    for(int i = 0; i < 7; i++){
        if(key_pressed[i] == 1 && keys_ypositions[i] > deslocamento_max){
            keys_ypositions[i] -= variacao;
        }
        if(keys_ypositions[i] <= deslocamento_max){
                key_pressed[i] = 0;
            }
        if(key_pressed[i] == 0 && keys_ypositions[i] < 0){
            keys_ypositions[i] += variacao;
        }
    }
}

// Função para animação
void timer(int){
    cdAnimator();
    keysAnimator();

    renderScene();
    glutPostRedisplay();
    glutTimerFunc(1000/30, timer, 0);
}

// Função para tratar os inputs do teclado
void GerenciaTeclado(unsigned char key, int x, int y){
    switch (key) {
        // ---------- ILUMINAÇÃO ----------
        case 'q':
            light0Ligado = !light0Ligado;
            if (light0Ligado)
                glEnable(GL_LIGHT0);
            else
                glDisable(GL_LIGHT0);
            glutPostRedisplay();
            break;

        // ---------- TRANSFORMAÇÕES GEOMÉTRICAS NO PIANO ----------
        case 'i': // Move o piano para frente
            PCpiano_z -= 0.1;
            glutPostRedisplay();
            break;
        case 'j': // Move o piano para a esquerda
            PCpiano_x -= 0.1;
            glutPostRedisplay();
            break;
        case 'k': // Move o piano para tras
            PCpiano_z += 0.1;
            glutPostRedisplay();
            break;
        case 'l': // Move o piano para a direita
            PCpiano_x += 0.1;
            glutPostRedisplay();
            break;
        case 'o': // Aumenta o piano
            Epiano_x += 0.1;
            Epiano_y += 0.1;
            Epiano_z += 0.1;
            glutPostRedisplay();
            break;
        case 'p': // Diminui o piano
            Epiano_x -= 0.1;
            Epiano_y -= 0.1;
            Epiano_z -= 0.1;
            glutPostRedisplay();
            break;

        // ---------- Animação das teclas do piano ----------
        case 'z':
            //Mix_Music* notes[7];
            //notes[0] = Mix_LoadMUS("do.wav");
            //Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
            //Mix_PlayMusic(notes[0], -1);

            //Mix_FreeMusic(notes[0]);


            key_pressed[0] = 1;
            break;
        case 'x':
            key_pressed[1] = 1;
            break;
        case 'c':
            key_pressed[2] = 1;
            break;
        case 'v':
            key_pressed[3] = 1;
            break;
        case 'b':
            key_pressed[4] = 1;
            break;
        case 'n':
            key_pressed[5] = 1;
            break;
        case 'm':
            key_pressed[6] = 1;
            break;
    }
}

// Função para tratar os inputs do mouse
void GerenciaMouse(int botao, int estado, int x, int y){
    switch(estado){
        case GLUT_DOWN:
            if(x >= 125 && x <= 175 && y <= 195 && y >= 135)
            {
                if(animacaoCD == 1){animacaoCD = 0;}
                else {animacaoCD = 1;}
            }
            break;
    }
}

int main(int argc, char** argv) {
    // Inicialização do GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Loja 3D");
    // Configurar a função de renderização
    glutDisplayFunc(renderScene);
    // Permitir utilização de teclado
    glutKeyboardFunc(GerenciaTeclado);
    // Permitir utilização de mouse
    glutMouseFunc(GerenciaMouse);
    // Configurações iniciais
    init();
    // Permitir utilização de animações
    glutTimerFunc(0, timer, 0);
    makeCheckImage();
    Texture();
    //SDL_Init(SDL_INIT_AUDIO);
    // Loop principal do GLUT
    //Mix_CloseAudio();
    //SDL_Quit();
    glutMainLoop();

    return 0;
}
