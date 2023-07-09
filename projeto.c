#include <GL/glut.h>

int light0Ligado = 1;

// Ponto central do piano
float PCpiano_x = 0.0;
float PCpiano_y = 0.0;
float PCpiano_z = -1.0;

// Escala do piano
float Epiano_x = 1.0;
float Epiano_y = 1.0;
float Epiano_z = 1.0;

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

void desenhar_teclas()
{
    float x_init = -1.0, x_end = -0.85, y_init = -0.075, y_end = 0.075, z_init = -1.0, z_end = 0.0, k = 0.2;
    for(int i = 0; i < 14; i++){
        glPushMatrix();
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

    // Desenhar o corpo
    glBegin(GL_QUADS);

    // Face traseira
    glColor3f(0.0, 1.0, 0.0); // Verde
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
    glColor3f(1.0, 1.0, 0.0); // Amarelo
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
        glTranslatef(PCpiano_x, PCpiano_y, PCpiano_z); // Move o piano ao seu ponto central
        glScalef(Epiano_x, Epiano_y, Epiano_z); // Ajusta a escala do piano
        desenhar_piano();
    glPopMatrix();

    // Desenhar a estante
    glPushMatrix();
        glTranslatef(3, 0, -3);
        desenharEstante();
    glPopMatrix();

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

void GerenciaTeclado(unsigned char key, int x, int y){
    switch (key) {
        case 'q':
            light0Ligado = !light0Ligado;
            if (light0Ligado)
                glEnable(GL_LIGHT0);
            else
                glDisable(GL_LIGHT0);
            glutPostRedisplay();
            break;
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
    // Configurações iniciais
    init();

    // Loop principal do GLUT
    glutMainLoop();

    return 0;
}

