#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
//Define parâmetros da textura
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

// Função que cria uma imagem de xadrez preto e branco na matriz checkImage
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

// Função que é responsável por criar a textura utilizando a imagem xadrez criada anteriormente
void Texture() {
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
    checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// Função que desenha o corpo da estante
void desenharCorpoEstante(){

    // Vértices do objeto
    float x_init = -1.0, x_end = 0.5, y_init = -1.0, y_end = 1.0, z_init = -1, z_end = -0.5;

    // Desenhar o paralelepípedo
    glBegin(GL_QUADS);

    // Face traseira
    glColor3f(0.15, 0.15, 0.15); // Cinza escuro
    glVertex3f(x_init, y_init, z_init);
    glVertex3f(x_init, y_end, z_init);
    glVertex3f(x_end, y_end, z_init);
    glVertex3f(x_end, y_init, z_init);

    // Face lateral esquerda
    glColor3f(0.27, 0.29, 0.32); // Cinza claro
    glVertex3f(x_init, y_init, z_init);
    glVertex3f(x_init, y_init, z_end);
    glVertex3f(x_init, y_end, z_end);
    glVertex3f(x_init, y_end, z_init);

    // Face lateral direita
    glColor3f(0.27, 0.29, 0.32); // Cinza claro
    glVertex3f(x_end, y_init, z_end);
    glVertex3f(x_end, y_init, z_init);
    glVertex3f(x_end, y_end, z_init);
    glVertex3f(x_end, y_end, z_end);

    // Face superior
    glColor3f(0.27, 0.29, 0.32); // Cinza claro
    glVertex3f(x_init, y_end, z_init);
    glVertex3f(x_end, y_end, z_init);
    glVertex3f(x_end, y_end, z_end);
    glVertex3f(x_init, y_end, z_end);

    // Face inferior
    glColor3f(0.27, 0.29, 0.32); // Cinza claro
    glVertex3f(x_init, y_init, z_init);
    glVertex3f(x_end, y_init, z_init);
    glVertex3f(x_end, y_init, z_end);
    glVertex3f(x_init, y_init, z_end);

    glEnd();
}

// Função que desenha as prateleiras da estante
void desenharPrateleiras(){
    // Vértices do objeto
    float x_init = -1.0, x_end = 0.5, y_init = 0.5, y_end = 0.4, z_init = -1.0, z_end = -0.5;

    ///Desenha duas prateleiras na estante
    for(int i = 0; i < 2; i++){
        glBegin(GL_QUADS);

        glColor3f(0.27, 0.29, 0.32);//Cinza
        //Face superior
        glVertex3f(x_init, y_end, z_init);
        glVertex3f(x_end, y_end, z_init);
        glVertex3f(x_end, y_end, z_end);
        glVertex3f(x_init, y_end, z_end);

        //Face frontal
        glColor3f(0.27, 0.29, 0.32);  // Cinza
        glVertex3f(x_init, y_init, z_end);
        glVertex3f(x_end, y_init, z_end);
        glVertex3f(x_end, y_end, z_end);
        glVertex3f(x_init, y_end, z_end);

        //Face inferior
        glColor3f(0.27, 0.29, 0.32); //Cinza
        glVertex3f(x_init, y_init, z_init);
        glVertex3f(x_end, y_init, z_init);
        glVertex3f(x_end, y_init, z_end);
        glVertex3f(x_init, y_init, z_end);

        glEnd();

        // Altera a posição da próxima prateleira a ser desenhada
        y_init -= 0.8;
        y_end -= 0.8;
    }
}

// Função que desenha os objetos na estante
void desenharObjetosEstante(){
    // Vértices do objeto
    float x_init = -0.9;
    float x_end = -0.8;

    for(int i = 0; i < 8; i++)
    {
        // Desenha um dvd
        glBegin(GL_QUADS);

        // Face frontal
        glColor3f(0.2, 0.2, 0.2);
        glVertex3f(x_end, 0, -0.5);
        glVertex3f(x_init, 0, -0.5);
        glVertex3f(x_init, 0.3, -0.5);
        glVertex3f(x_end, 0.3, -0.5);

        // Face direita
        glColor3f(0.2, 0.2, 0.2);
        glVertex3f(x_end, 0.3, -0.5);
        glVertex3f(x_end, 0.3, -1);
        glVertex3f(x_end, 0, -1);
        glVertex3f(x_end, 0, -0.5);

        // Face esquerda
        glColor3f(0.7, 0, 0);
        glVertex3f(x_init, 0.3, -0.5);
        glVertex3f(x_init, 0.3, -1);
        glVertex3f(x_init, 0, -1);
        glVertex3f(x_init, 0, -0.5);

        // Face superior
        glColor3f(0.2, 0.2, 0.2);
        glVertex3f(x_init, 0.3, -0.5);
        glVertex3f(x_end, 0.3, -0.5);
        glVertex3f(x_end, 0.3, -1);
        glVertex3f(x_init, 0.3, -1);

        glEnd();

        // Adiciona um espaço extra a cada 3 objetos
        if(i % 3 == 0){
            x_init += 0.2;
            x_end += 0.2;
        }
        else{
            x_init += 0.11;
            x_end += 0.11;
        }
    }
}

// Função que une e desenha todas as partes da estante
void desenharEstante(){
    desenharCorpoEstante();
    desenharPrateleiras();

    // Desenha os cds nas duas prateleiras
    glPushMatrix();
        glTranslatef(0.1, 0.5, 0);
        desenharObjetosEstante();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, -0.3, 0);
        desenharObjetosEstante();
    glPopMatrix();
}

// Função que desenha o disco
void desenhaDisco(){
  glColor3f(0, 0, 0); // Preto

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

// Função que desenha as teclas do piano
void desenhaTeclas()
{
    // Vértices do objeto
    float x_init = -1.0, x_end = -0.85, y_init = -0.075, y_end = 0.075, z_init = -1.0, z_end = 0.0, k = 0.2;

    // Desenha as 14 teclas
    for(int i = 0; i < 14; i++){
        glPushMatrix();
            // Translação para a animação das teclas
            if(i < 7){
                glTranslatef(0, keys_ypositions[i], 0);
            }

            // Desenhar o paralelepípedo
            glBegin(GL_QUADS);
            // Face frontal
            glColor3f(k, k, k);  
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

        // Altera a cor da próxima tecla a ser desenhada
        if(k < 1.0){
            k += 0.1;
        }
        else{
            k = 0;
        }

        // Altera a posição da próxima tecla a ser adicionada
        x_init += 0.15;
        x_end += 0.15;
    }
}

// Função que desenha o corpo do piano
void desenhaCorpoPiano(){
    // Vértices do objeto
    float x_init = -1.05, x_end = 1.15, y_init = -1.0, y_end = 1.0, z_init = -1.0, z_end = -2.0;

    //Aplica a textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

    // Desenhar o corpo
    glBegin(GL_QUADS);

    // Face traseira
    glColor3f(0.5, 0.0, 0.0); // Vermelho
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x_init, y_init, z_init);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(x_init, y_end, z_init);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x_end, y_end, z_init);
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(x_end, y_init, z_init);

    // Face lateral esquerda
    glColor3f(0.2, 0.2, 0.2); // Cinza
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
    
    // Desativa a textura
    glDisable(GL_TEXTURE_2D);
}

// Função que desenha os pés do piano
void desenhaPesPiano(){
    // Vértices do objeto
    float x_init = -1.0, x_end = -0.9, y_init = -1.0, y_end = -0.075, z_init = -0.05, z_end = -0.25;

    // Desenha os dois pés do piano
    for(int i = 0; i < 2; i++){
        glBegin(GL_QUADS);

        // Face traseira
        glColor3f(0.7, 0.2, 0.2); 
        glVertex3f(x_init, y_init, z_init);
        glVertex3f(x_init, y_end, z_init);
        glVertex3f(x_end, y_end, z_init);
        glVertex3f(x_end, y_init, z_init);

        // Face lateral esquerda
        glColor3f(0.5, 0.2, 0.2); 
        glVertex3f(x_init, y_init, z_init);
        glVertex3f(x_init, y_init, z_end);
        glVertex3f(x_init, y_end, z_end);
        glVertex3f(x_init, y_end, z_init);

        // Face lateral direita
        glColor3f(0.5, 0.2, 0.2); 
        glVertex3f(x_end, y_init, z_end);
        glVertex3f(x_end, y_init, z_init);
        glVertex3f(x_end, y_end, z_init);
        glVertex3f(x_end, y_end, z_end);

        // Face superior
        glColor3f(0.5, 0.2, 0.2); 
        glVertex3f(x_init, y_end, z_init);
        glVertex3f(x_end, y_end, z_init);
        glVertex3f(x_end, y_end, z_end);
        glVertex3f(x_init, y_end, z_end);

        // Face inferior
        glColor3f(0.5, 0.2, 0.2); 
        glVertex3f(x_init, y_init, z_init);
        glVertex3f(x_end, y_init, z_init);
        glVertex3f(x_end, y_init, z_end);
        glVertex3f(x_init, y_init, z_end);
        glEnd();

        // Altera a posição do próximo pé a ser desenhado
        x_init += 2;
        x_end += 2;
    }
}

// Função que une e desenha o piano
void desenhaPiano()
{
    desenhaTeclas();
    desenhaCorpoPiano();
    desenhaPesPiano();
}

// Função que desenha a parede de fundo
void desenhaParedeFundo(){
    glBegin(GL_QUADS);

    glColor3f(0.1, 0.5, 0.1); // Verde
    glVertex3f(-12, -1, -3.5);
    glVertex3f(-12, 3, -3.5);
    glVertex3f(12, 3, -3.5);
    glVertex3f(12, -1, -3.5);

    glEnd();

}

// Função que desenha o chao 
void desenhaChao(){
glBegin(GL_QUADS);

    glColor3f(0.9, 1.0, 0.9); // Bege
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
        desenhaPiano();
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
        desenhaDisco();
    glPopMatrix();

    desenhaParedeFundo();
    desenhaChao();

    // Trocar os buffers para exibir a cena renderizada
    glutSwapBuffers();
}

// Função de inicialização
void init(){
    glClearColor(0.5, 0.5, 0.5, 0.0); // Define a cor de fundo para cinza
    glEnable(GL_DEPTH_TEST);          // Habilita o teste de profundidade

    // Habilita a iluminação
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // Define as propriedades da fonte de luz (GL_LIGHT0)
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
    // Variação no eixo y a cada frame
    float variacao = 0.01;
    // Deslocamento máximo da tecla
    float deslocamento_max = -0.1;
    for(int i = 0; i < 7; i++){
        // Movimento vertical descendente
        if(key_pressed[i] == 1 && keys_ypositions[i] > deslocamento_max){
            keys_ypositions[i] -= variacao;
        }
        // Altera a flag de movimento
        if(keys_ypositions[i] <= deslocamento_max){
                key_pressed[i] = 0;
        }
        // Movimento vertical ascendente 
        if(key_pressed[i] == 0 && keys_ypositions[i] < 0){
            keys_ypositions[i] += variacao;
        }
    }
}

// Função para animação
void timer(int){
    cdAnimator();
    keysAnimator();

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
            // Checa se o clique do mouse corresponde a posição do disco
            if(x >= 125 && x <= 175 && y <= 195 && y >= 135)
            {
                if(animacaoCD == 1){animacaoCD = 0;} // Desativa a animação do disco
                else {animacaoCD = 1;} // Ativa a animação do disco
            }
            break;
    }
}

int main(int argc, char** argv) {
    // Inicialização do GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Loja de Instrumentos");
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
    // Criam a textura
    makeCheckImage();
    Texture();
    // Loop principal
    glutMainLoop();

    return 0;
}
