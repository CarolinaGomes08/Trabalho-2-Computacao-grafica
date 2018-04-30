/*                               UNIVERSIDADE FEDERAL DO VALE DO SÃO FRANCISCO

                             EXERCÍCIO PRÁTICO DE OPENGL: ATRAVESSANDO O LABIRINTO

            Trabalho feito sob orientação do professor Jorge Cavalcanti, para obtenção parcial de nota
        na disciplina de Computação gráfica.


                                    ALUNAS: CAROLINA VICTORIA COSTA GOMES
                                            LAÍS FERNANDA LEITE SANTOS
*/

#include <windows.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

GLfloat xf1, xf2, xf3, xf4, yf1, yf2, yf3, yf4;
GLfloat  corRV1,corGV1,corBV1,corRV2, corGV2, corBV2;
GLclampf cor1,cor2,cor3,cor4;

//variáveis globais para saber a quantidade de vidas, e para verificar se o jogador venceu, respectivamente:
int vidas = 4;
int venceu = 0;

//Funções utilizadas para desenhar as vidas:
void desenhaCirculo(float raio, float cx, float cy);
void desenhaTriangulo(float x1, float x2, float x3, float y1, float y2, float y3);
void desenhaVida(float cx1, float cx2, float cy1, float cy2, float x1, float x2, float x3, float y1, float y2, float y3);

//Funções utilizadas para desenhar as telas que indicam o término do jogo:
void drawnText( float x, float y, int r, int g, int b, const char *string );
void telaGameOver(void);
void telaVoceVenceu(void);

//Função que define a posição inicial do objeto:
void initialPosition(void);

//Verifica quando há colisão ou quando o jogador ganhou
void collision(GLfloat x1, GLfloat x2, GLfloat x3, GLfloat x4, GLfloat y1, GLfloat y2, GLfloat y3, GLfloat y4);

// Define a janela de visualização 2D
void Inicializa (void);

// Função callback chamada para fazer o desenho
void Desenha(void);

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y);

void TeclasEspeciais(int key, int x, int y);

int main(void)
{
    int corRV1=1;
    corGV1=1;
    corBV1=1;
    corRV2=0.7;
    corGV2=0.13;
    corBV2=0.13;

    initialPosition();
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("Atravessando o Labirinto");
    glutDisplayFunc(Desenha);
    glutMouseFunc(GerenciaMouse);
    glutSpecialFunc(TeclasEspeciais);
    Inicializa();
    glutMainLoop();

    return 0;
}

void desenhaCirculo(float raio, float cx, float cy)
{
    float ang, x, y;

    glColor3f(1.0,0.0,0.0);

    glBegin( GL_POLYGON );
        for(int i = 0; i<360; i++ )
        {
            ang = (i * 3.14) / 180;
            x = cx + (cos(ang) * raio);
            y = cy + (sin(ang) * raio);
            glVertex2f(x, y);
        }
    glEnd();
}

void desenhaTriangulo(float x1, float x2, float x3, float y1, float y2, float y3)
{
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_TRIANGLES);
        glVertex3f(x1, y1, 0);
        glVertex3f(x2, y2, 0);
        glVertex3f(x3, y3, 0);
    glEnd();
}

void desenhaVida(float cx1, float cx2, float cy1, float cy2, float x1, float x2, float x3, float y1, float y2, float y3)
{
    desenhaCirculo(1, cx1, cy1);
    desenhaCirculo(1, cx2, cy2);
    desenhaTriangulo(x1, x2, x3, y1, y2, y3);
}

void drawnText( float x, float y, int r, int g, int b, const char *string ) {
	int j = strlen( string );

	glColor3f( r, g, b );
	glRasterPos2f( x, y );
	for( int i = 0; i < j; i++ ) {
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
	}
}

void telaGameOver(void)
{
   glClearColor(cor1, cor2, cor3, cor4);
   drawnText(-6, 0, 0, 1, 1, "Game Over");
   glutPostRedisplay();
}

void telaVoceVenceu(void)
{
   glClearColor(cor1, cor2, cor3, cor4);
   drawnText(-12, 0, 1, 1, 1, "Parabens! Voce Venceu!");
   glutPostRedisplay();
}

void initialPosition(void)
{
    xf1=-14.5;
    xf2=-14.5;
    xf3=-12.5;
    xf4=-12.5;
    yf1=-23;
    yf2=-21;
    yf3=-21;
    yf4=-23;
    return;
}

void collision(GLfloat x1, GLfloat x2, GLfloat x3, GLfloat x4, GLfloat y1, GLfloat y2, GLfloat y3, GLfloat y4)
{
    if(x1 > -15 && x4<-12 && y2 < -10){
        printf("-");
    }

    else if (y2<=-20.5)
    {
        initialPosition();
        glutPostRedisplay();
    }
    else if(y1>-13 && y2<-10 && x4<-12 && x1>-25){
        printf ("-");
    }
    else if(x1>-25 && x4<-22 && y1>-13 && y2<5){
        printf ("-");
    }
    else if(x1>-25 && x4<0 && y1>2 && y2<5){
        printf ("-");
    }
    else if(x1>-3 && x4<0 && y1>2 && y2<15){
        printf ("-");
    }
    else if(x1>-3 && x4<=22 && y1>12 && y2<15){
        printf ("-");
    }
    else if(x4==22.5){
        printf ("Voce ganhou!");
        venceu++;
        if(venceu){

            telaVoceVenceu();
    }
    }


    else{
        printf("morreu %d", vidas);
        initialPosition(); // Se houver uma colisão, o objeto volta à posição inicial
        vidas--;
        glutPostRedisplay();
        if(!vidas){
                      telaGameOver();

            }
    }
}

void Inicializa (void)
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-30.0,30.0,-30.0,30.0);
}

void Desenha(void)
{

    int x = 0;
    glMatrixMode(GL_MODELVIEW);
    //Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);

    // define a cor vermelha para as linhas
    glColor3f(corRV2, corGV2, corBV2);
    glLineWidth(3);

    if(vidas && !venceu){
    glBegin(GL_LINES);
        glVertex2i(-15, -20); //ponto 1
        glVertex2i(-15, -13); //ponto 2
        glVertex2i(-15, -13); //ponto 2
        glVertex2i(-25, -13); //ponto 3
        glVertex2i(-25, -13); //ponto 3
        glVertex2i(-25, 5); //ponto 4
        glVertex2i(-25, 5); //ponto 4
        glVertex2i(-3, 5); //ponto 5
        glVertex2i(-3, 5); //ponto 5
        glVertex2i(-3, 15); //ponto 6
        glVertex2i(-3, 15); //ponto 6
        glVertex2i(20, 15); //ponto 7
        glVertex2i(20, 12); //ponto 8
        glVertex2i(0, 12); //ponto 9
        glVertex2i(0, 12); //ponto 9
        glVertex2i(0, 2); //ponto 10
        glVertex2i(0, 2); //ponto 10
        glVertex2i(-22, 2); //ponto 11
        glVertex2i(-22, 2); //ponto 11
        glVertex2i(-22, -10); //ponto 12
        glVertex2i(-22, -10); //ponto 12
        glVertex2i(-12, -10); //ponto 13
        glVertex2i(-12, -10); //ponto 13
        glVertex2i(-12, -20); //ponto 14
    glEnd();

    glColor3f(corRV1, corGV1, corBV1);


     glBegin(GL_POLYGON);
               glVertex2f(xf1,yf1);
               glVertex2f(xf2,yf2);
               glVertex2f(xf3,yf3);
               glVertex2f(xf4,yf4);
     glEnd();

     collision(xf1,xf2,xf3,xf4, yf1, yf2, yf3,yf4);

     // Desenho das vidas:
     float cx1, cx2, altCirc, x1, x2, x3, altTrian;
     cx1 = -28.5;
     cx2 = -27.5;
     altCirc = 28.5; //Altura do centro dos círculos e da base do triângulo
     x1 = -29.5;
     x2 = -26.5;
     x3 = -28;
     altTrian = 26.5; //Altura da ponta do triângulo

     for(int i = 0; i<vidas; i++){
        desenhaVida(cx1+(i*4), cx2+(i*4), altCirc, altCirc, x1+(i*4), x2+(i*4), x3+(i*4), altCirc, altCirc, altTrian);
     }
    }

    else if(venceu){

            telaVoceVenceu();
    }

   else if(!vidas){

            telaGameOver();
    }

    //Executa os comandos OpenGL para renderização.
    glFlush();

}

void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
         if (state == GLUT_DOWN) {
             float min=0, max=1;
            corRV1= min + (rand() / ( RAND_MAX / ( max - min) ) ) ;
            corGV1=min + (rand() / ( RAND_MAX / ( max - min) ) ) ;
            corBV1=min + (rand() / ( RAND_MAX / ( max - min) ) ) ;
            corRV2= min + (rand() / ( RAND_MAX / ( max - min) ) ) ;
            corGV2=min + (rand() / ( RAND_MAX / ( max - min) ) ) ;
            corBV2=min + (rand() / ( RAND_MAX / ( max - min) ) ) ;
            cor1= min + (rand() / ( RAND_MAX / ( max - min) ) ) ;
            cor2=min + (rand() / ( RAND_MAX / ( max - min) ) ) ;
            cor3=min + (rand() / ( RAND_MAX / ( max - min) ) ) ;
            cor4=min + (rand() / ( RAND_MAX / ( max - min) ) ) ;

            glClearColor(cor1, cor2, cor3, cor4);
         }
    glutPostRedisplay();
}

void TeclasEspeciais(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
           yf1 = yf1+0.5;
           yf2 = yf2+0.5;
           yf3 = yf3+0.5;
           yf4 = yf4+0.5;

           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D(-30.0,30.0,-30.0,30.0);

    }
    if(key == GLUT_KEY_DOWN) {
           yf1 = yf1-0.5;
           yf2 = yf2-0.5;
           yf3 = yf3-0.5;
           yf4 = yf4-0.5;

           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D(-30.0,30.0,-30.0,30.0);
    }
    if(key == GLUT_KEY_LEFT) {
           xf1 = xf1-0.5;
           xf2 = xf2-0.5;
           xf3 = xf3-0.5;
           xf4 = xf4-0.5;

           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D(-30.0,30.0,-30.0,30.0);

    }

    if(key == GLUT_KEY_RIGHT) {
           xf1 = xf1+0.5;
           xf2 = xf2+0.5;
           xf3 = xf3+0.5;
           xf4 = xf4+0.5;

           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D(-30.0,30.0,-30.0,30.0);
    }
    glutPostRedisplay();

}
