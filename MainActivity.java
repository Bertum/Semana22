package com.magudob.juego;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.Window;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_main);
        /*setContentView(new VistaJuego(this));*/
    }

    public void bottonClick (View v){
        setContentView(new VistaJuego(this));
    }
}

class VistaJuego extends View {
    private BucleJuego buclePrincipal;
    Bitmap spriteJuego;
    Canvas lienzoJuego;
    public VistaJuego(Context context) {
        super(context);
        this.setDrawingCacheEnabled(true);
        lienzoJuego = new Canvas();
        buclePrincipal = new BucleJuego(getResources(),lienzoJuego);
        buclePrincipal.start();
    }
    @SuppressLint("DrawAllocation")@Override
    protected void onMeasure (int myWidth,int myHeight){
        int width = MeasureSpec.getSize(myWidth);
        int height = MeasureSpec.getSize(myHeight);
        spriteJuego = Bitmap.createBitmap(width,height,Bitmap.Config.ARGB_8888);
        lienzoJuego.setBitmap(spriteJuego);
        setMeasuredDimension(height,width);
    }
    @Override
    protected void onDraw(Canvas canvas){
        canvas.drawBitmap(spriteJuego,0,0,new Paint());
        invalidate();
    }
}

class BucleJuego extends Thread {
    //Inicializamos las variables del bucle
    private float tasaFotogramas = 10;
    private float tasaTiempo = 1000/tasaFotogramas;
    //Creamos las variables para el juego
    private Juego logicaJuego;
    private Resources recursos;
    private Canvas lienzoJuego;

    /**
     * Constructor clase juego
     * @param misResources
     * @param miCanvas
     */
    public BucleJuego (Resources misResources, Canvas miCanvas){
        logicaJuego = new Juego(misResources,miCanvas,20);
    }

    /**
     * Sobreescritura del metodo run
     */
    @Override
    public void run (){
        while(true){
            float tiempoInicio = System.currentTimeMillis();
            logicaJuego.Actualizo();
            logicaJuego.Dibujo();
            float tiempoFinal = System.currentTimeMillis();
            long tiempoDelta = (long) (tasaTiempo - (tiempoInicio - tiempoFinal));
            try{
                Thread.sleep(tiempoDelta);
            }
            catch (InterruptedException e){}
        }
    }

}

class Juego {

    private Resources recursos;
    private Canvas lienzo;
    //Inicializacion de las variables del juego
    private int xInicial = 0;
    private int yInicial = 0;
    private int longitud = 50;
    private int nCeldas = 2600;
    private int cont;

    //Variable para dibujar la matriz del tablero
    private Paint emptyShell = new Paint();

    //Variable de tipo array de la clase Cell(objeto de cada una de los items del juego)
    private Cell[] arrayCell = new Cell[longitud*longitud];

    /**
     * Constructor de Juego
     * @param misRecursos
     * @param miLienzo
     * @param numCeldas
     */
    public Juego(Resources misRecursos, Canvas miLienzo, int numCeldas) {
        recursos = misRecursos;
        lienzo = miLienzo;
        nCeldas = numCeldas;
        emptyShell.setStyle(Paint.Style.STROKE);
        for (int x = 0; x < longitud; x++) {
            for (int y = 0; y < longitud; y++) {
                Random randomNumber = new Random();
                /*celdaX[cont] = x;
                celdaY[cont] = y;
                activo[cont] =  randomNumber.nextInt(longitud) % 2;
                pintura[cont] = new Paint();
                pintura[cont].setTextSize(longitud);*/
                arrayCell[cont] = new Cell(x,y,randomNumber.nextInt(longitud) % 2,new Paint());
                arrayCell[cont].pinturaCell.setTextSize(longitud);
                cont++;
            }
        }
    }

    /**
     * Funcion para dibujar celulas en caso de que esten activas
     */
    public void Dibujo() {
        lienzo.drawColor(Color.WHITE);
        cont = 0;
        for (int x = 0; x < longitud; x++) {
            for (int y = 0; y < longitud; y++) {
                lienzo.drawRect(new Rect(arrayCell[cont].posCellX * 20, arrayCell[cont].posCellY * 20, arrayCell[cont].posCellX * 20 + 20, arrayCell[cont].posCellY * 20 + 20), emptyShell);
                //lienzo.drawRect(new Rect(celdaX[cont] * 20, celdaY[cont] * 20, celdaX[cont] * 20 + 20, celdaY[cont] * 20 + 20), emptyShell);
                if (arrayCell[cont].activo == 1) {
                    lienzo.drawRect(new Rect(arrayCell[cont].posCellX * 20, arrayCell[cont].posCellY * 20, arrayCell[cont].posCellX * 20 + 20, arrayCell[cont].posCellY * 20 + 20), arrayCell[cont].pinturaCell);
                    //lienzo.drawRect(new Rect(celdaX[cont] * 20, celdaY[cont] * 20, celdaX[cont] * 20 + 20, celdaY[cont] * 20 + 20), pintura[cont]);
                }
                cont++;
            }
        }
    }

    /**
     * Funcion para actualizar la posicion de las celulas
     */
    public void Actualizo() {
        cont = 0;
        for (int x = 0; x < longitud; x++) {
            for (int y = 0; y < longitud; y++) {
                int nVivas = 0;
                //Compruebo si izq vive
                if (cont > longitud && cont < ((longitud * longitud) - longitud - 1)) {
                    if (arrayCell[cont - 1].activo == 1) {
                        nVivas++;
                    }
                    if (arrayCell[cont + 1].activo == 1) {
                        nVivas++;
                    }
                    if (arrayCell[cont - 1 - longitud].activo == 1) {
                        nVivas++;
                    }
                    if (arrayCell[cont - longitud].activo == 1) {
                        nVivas++;
                    }
                    if (arrayCell[cont + 1 - longitud].activo == 1) {
                        nVivas++;
                    }
                    if (arrayCell[cont - 1 + longitud].activo == 1) {
                        nVivas++;
                    }
                    if (arrayCell[cont + longitud].activo == 1) {
                        nVivas++;
                    }
                    if (arrayCell[cont + 1 + longitud].activo == 1) {
                        nVivas++;
                    }
                }
                //Implementacion HighLife
                //Celula viva con menos de dos vecinos muere
                if (arrayCell[cont].activo == 1 && nVivas < 2){
                    arrayCell[cont].activo = 0;
                }
                //Celula viva con mas de tres vecinos muere
                if (arrayCell[cont].activo == 1 && nVivas > 3){
                    arrayCell[cont].activo = 0;
                }
                //Celula viva con dos o tres vecinos no pasa na
                if (arrayCell[cont].activo == 1 && (nVivas == 2 || nVivas == 3)){
                    arrayCell[cont].pinturaCell.setColor(Color.BLUE);
                    arrayCell[cont].activo = 1;
                }
                //Celula MUERTA con tres vecinos o seis, vive
                if (arrayCell[cont].activo == 0 && (nVivas == 3 || nVivas == 6)){
                    arrayCell[cont].pinturaCell.setColor(Color.GREEN);
                    arrayCell[cont].activo = 1;
                }

                //34Life
                    /*
                    if (arrayCell[cont].activo ==1 && nVivas<=2){
                        arrayCell[cont].activo = 0;
                    }
                    //Celula viva con mas de cuatro vecinos muere
                    if (arrayCell[cont].activo ==1 && nVivas>4){
                        arrayCell[cont].activo = 0;
                    }
                    //Celula viva con dos o tres vecinos no pasa na
                    if (arrayCell[cont].activo==1 && (nVivas==3 || nVivas==4)){
                        arrayCell[cont].pintura.setColor(Color.BLUE);
                        arrayCell[cont].activo = 1;
                    }
                    //Celula MUERTA con tres vecinos o seis, vive
                    if (arrayCell[cont].activo && (nVivas==3 || nVivas==4)){
                        arrayCell[cont].pintura.setColor(Color.GREEN);
                        arrayCell[cont].activo = 1;
                    }
                    */
                //Seeds
                /*
                if (arrayCell[cont].activo == 1 && nVivas < 2){
                    arrayCell[cont].activo = 0;
                }
                //Celula viva con mas de tres vecinos muere
                if (arrayCell[cont].activo == 1 && nVivas >= 3){
                    arrayCell[cont].activo = 0;
                }
                //Celula MUERTA con tres vecinos o seis, vive
                if (arrayCell[cont].activo == 0 && nVivas == 2){
                    arrayCell[cont].pinturaCell.setColor(Color.GREEN);
                    arrayCell[cont].activo = 1;
                }*/
                cont++;
            }
        }
    }
}

class Cell{

    public int posCellX;
    public int posCellY;
    public int activo;
    public Paint pinturaCell;

    public Cell (int posX,int posY,int active,Paint pintura){
        posCellX = posX;
        posCellY = posY;
        activo = active;
        pinturaCell = pintura;
    }
}