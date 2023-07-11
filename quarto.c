#include <GL/glut.h>
//#include <cstdio.h>

typedef struct{
  float x, y;
} Vetor;

int larguraTela = 500;
int alturaTela = 500;
Vetor dimObjetos[4];
Vetor posicaoObjetos[4];
int objSelecionado = -1;

void Paredes(void){
  glBegin( GL_LINE_LOOP );
    glColor3f(1.0f,1.0f,1.0f);

    glVertex3f(-0.9f,0.9f,0.0f);

    // Inicio da janela
    glVertex3f(-0.3f,0.9f,0.0f);
    glVertex3f(-0.3f,0.92f,0.0f);
    glVertex3f(0.3f,0.92f,0.0f);
    glVertex3f(0.3f,0.9f,0.0f);
    glVertex3f(0.9f,0.9f,0.0f);
    // Fim da janela

    glVertex3f(0.9f,-0.9f,0.0f);
    glVertex3f(-0.5f,-0.9f,0.0f);

    // Inicio da porta
    glVertex3f(-0.5f,-0.92f,0.0f);
    glVertex3f(-0.8f,-0.92f,0.0f);
    glVertex3f(-0.8f,-0.9f,0.0f);
    // Fim da porta

    glVertex3f(-0.9f,-0.9f,0.0f);
    glVertex3f(-0.9f, 0.9f,0.0f);
  glEnd();

  glBegin( GL_LINE_LOOP );
    glColor3f(1.0f,1.0f,1.0f);
    glVertex3f(-0.92f,0.92f,0.0f);
    glVertex3f(0.92f,0.92f,0.0f);
    glVertex3f(0.92f,-0.92f,0.0f);
    glVertex3f(-0.92f,-0.92f,0.0f);
    glVertex3f(-0.92f, 0.92f,0.0f);
  glEnd();
}

void Computador(void){
  glBegin( GL_POLYGON );
    glColor3f(0.1f,0.5f,0.99f);
    glVertex3f(posicaoObjetos[0].x-(dimObjetos[0].x/2),posicaoObjetos[0].y+(dimObjetos[0].y/2),0.0f);
    glVertex3f(posicaoObjetos[0].x-(dimObjetos[0].x/2),posicaoObjetos[0].y-(dimObjetos[0].y/2),0.0f);
    glVertex3f(posicaoObjetos[0].x+(dimObjetos[0].x/2),posicaoObjetos[0].y-(dimObjetos[0].y/2),0.0f);
    glVertex3f(posicaoObjetos[0].x+(dimObjetos[0].x/2),posicaoObjetos[0].y+(dimObjetos[0].y/2),0.0f);
  glEnd();
}

void Cama(void) {
  glBegin( GL_POLYGON );
    glColor3f(0.5f,0.3f,0.2f);
    //glVertex3f(0.87f,0.87f,0.0f);
    //glVertex3f(0.87f,0.0f,0.0f);
    //glVertex3f(0.5f,0.0f,0.0f);
    //glVertex3f(0.5f,0.87f,0.0f);
    glVertex3f(posicaoObjetos[1].x-(dimObjetos[1].x/2),posicaoObjetos[1].y+(dimObjetos[1].y/2),0.0f);
    glVertex3f(posicaoObjetos[1].x-(dimObjetos[1].x/2),posicaoObjetos[1].y-(dimObjetos[1].y/2),0.0f);
    glVertex3f(posicaoObjetos[1].x+(dimObjetos[1].x/2),posicaoObjetos[1].y-(dimObjetos[1].y/2),0.0f);
    glVertex3f(posicaoObjetos[1].x+(dimObjetos[1].x/2),posicaoObjetos[1].y+(dimObjetos[1].y/2),0.0f);
  glEnd();
}

void GuardaRoupa(void){
  glBegin( GL_POLYGON );
    glColor3f(0.12f, 0.23f, 0.34f);
    //glVertex3f(-0.89f,0.89f,0.0f);
    //glVertex3f(-0.89f,-0.5f,0.0f);
    //glVertex3f(-0.4f,-0.5f,0.0f);
    //glVertex3f(-0.4f,0.89f,0.0f);
    glVertex3f(posicaoObjetos[2].x-(dimObjetos[2].x/2),posicaoObjetos[2].y+(dimObjetos[2].y/2),0.0f);
    glVertex3f(posicaoObjetos[2].x-(dimObjetos[2].x/2),posicaoObjetos[2].y-(dimObjetos[2].y/2),0.0f);
    glVertex3f(posicaoObjetos[2].x+(dimObjetos[2].x/2),posicaoObjetos[2].y-(dimObjetos[2].y/2),0.0f);
    glVertex3f(posicaoObjetos[2].x+(dimObjetos[2].x/2),posicaoObjetos[2].y+(dimObjetos[2].y/2),0.0f);
  glEnd();
}

void Escrivaninha(void){
  glBegin( GL_POLYGON );
    glColor3f(0.98f,0.76f,0.54f);
    //glVertex3f(0.1f,-0.87f,0.0f);
    //glVertex3f(0.1f,-0.5f,0.0f);
    //glVertex3f(0.87f,-0.5f,0.0f);
    //glVertex3f(0.87f,-0.87f,0.0f);
    glVertex3f(posicaoObjetos[3].x-(dimObjetos[3].x/2),posicaoObjetos[3].y+(dimObjetos[3].y/2),0.0f);
    glVertex3f(posicaoObjetos[3].x-(dimObjetos[3].x/2),posicaoObjetos[3].y-(dimObjetos[3].y/2),0.0f);
    glVertex3f(posicaoObjetos[3].x+(dimObjetos[3].x/2),posicaoObjetos[3].y-(dimObjetos[3].y/2),0.0f);
    glVertex3f(posicaoObjetos[3].x+(dimObjetos[3].x/2),posicaoObjetos[3].y+(dimObjetos[3].y/2),0.0f);
  glEnd();
}

void RenderScene(void){
  glClearColor(0.0f,0.0f,0.0f,0.0f);
  glClear( GL_COLOR_BUFFER_BIT );

  //Paredes();
  Cama();
  GuardaRoupa();
  Escrivaninha();
  Computador();

  glutSwapBuffers();
  glFlush();
}

Vetor conversoesPos_tela(Vetor posicao){
  Vetor novaPosicao;
  if(posicao.x >= 0){
    novaPosicao.x = (posicao.x*(larguraTela/2)) + (larguraTela/2);
  }
  else{
    novaPosicao.x = (larguraTela/2)-((-1)*posicao.x*larguraTela/2);
  }
  if(posicao.y >= 0){
    novaPosicao.y = (alturaTela/2)-(posicao.y*alturaTela/2);
  }
  else{
    novaPosicao.y = ((-1)*posicao.y*(alturaTela/2)) + (alturaTela/2);
  }
  return novaPosicao;
}

Vetor conversoesTela_pos(Vetor posicao){
  Vetor novaPosicao;
  novaPosicao.x = (posicao.x-(larguraTela/2))/(larguraTela/2);
  novaPosicao.y = (-1)*(posicao.y-(alturaTela/2))/(alturaTela/2);
  return novaPosicao;
}

int BuscaObjeto(int x, int y){
  for(int i = 0; i < 4; i++){
    if(x > conversoesPos_tela(posicaoObjetos[i]).x - ((dimObjetos[i].x*(larguraTela/2))/2) && x < conversoesPos_tela(posicaoObjetos[i]).x + ((dimObjetos[i].x*(larguraTela/2))/2) && y > conversoesPos_tela(posicaoObjetos[i]).y - ((dimObjetos[i].y*(alturaTela/2))/2) && y < conversoesPos_tela(posicaoObjetos[i]).y + ((dimObjetos[i].y*(alturaTela/2))/2)){
      return i; // Objeto encontrado
    }
  }
  return -1; // Nao foi possivel encontrar algum objeto
}

// Trata os cliques do mouse
void Mouse(int botao, int estado, int x, int y){
  switch(estado){
    case GLUT_DOWN:
      if(objSelecionado!=-1){ // Um objeto esta selecionado
        Vetor v;
        v.x = x;
        v.y = y;

        posicaoObjetos[objSelecionado].x = conversoesTela_pos(v).x;
        posicaoObjetos[objSelecionado].y = conversoesTela_pos(v).y;
        objSelecionado = -1;
      }
      else if(objSelecionado==-1 && BuscaObjeto(x, y) != -1){
        objSelecionado = BuscaObjeto(x,y); // Seleciona um objeto
      }
      break;
  }
}

// Define posicoes e dimensoes dos objetos no inicio do programa
void inicio(void){
  // Computador
  posicaoObjetos[0].x = 0.0f;
  posicaoObjetos[0].y = 0.0f;
  dimObjetos[0].x = 0.2f;
  dimObjetos[0].y = 0.2f;
  // Cama
  posicaoObjetos[1].x = 0.1f;
  posicaoObjetos[1].y = 0.0f;
  dimObjetos[1].x = 0.2f;
  dimObjetos[1].y = 0.2f;
  // Guarda Roupas
  posicaoObjetos[2].x = -0.1f;
  posicaoObjetos[2].y = 0.0;
  dimObjetos[2].x = 0.2f;
  dimObjetos[2].y = 0.2f;
  // Escrivaninha
  posicaoObjetos[3].x = 0.485;
  posicaoObjetos[3].y = -0.685;
  dimObjetos[3].x = 0.77f;
  dimObjetos[3].y = 0.37f;
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (larguraTela, alturaTela);
  glutInitWindowPosition (100, 100);
  glutCreateWindow("OpenGL - Planta Baixa");
  inicio();
  glutIdleFunc(RenderScene);
  glutMouseFunc(Mouse);
  glutMainLoop();
  return 0;
}
