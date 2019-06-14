/*
 *      ----------------------------------------------------------
 *      Mosaic | OF Visual Patching Developer Platform
 *
 *      Copyright (c) 2019 Emanuele Mazza aka n3m3da
 *
 *      Mosaic is distributed under the MIT License. This gives everyone the
 *      freedoms to use Mosaic in any context: commercial or non-commercial,
 *      public or private, open or closed source.
 *
 *      See https://github.com/d3cod3/Mosaic for documentation
 *      ----------------------------------------------------------
 *
 *
 *      Empty.java: A Processing template for Mosaic
 *
 *      see https://processing.org/reference for Language Reference
 *
 */

import processing.core.*;

public class Empty extends PApplet{

    int         _dataInSize   = 6;  // Set here your Mosaic inlet data size
    int         _dataOutSize  = 2;  // Set here your Mosaic outlet data size

    ////////////////////////////////////////////////////// DO NOT EDIT
    public static void main(String[] args) {
        PApplet.main("Empty");
    }

    // MOSAIC INLET
    String[]    _dataIN;
    float[]     _mosaic_data_inlet = new float[_dataInSize];
    // MOSAIC OUTLET
    String[]    _dataOUT = new String[_dataOutSize];
    float[]     _mosaic_data_outlet = new float[_dataOutSize];
    // PROCESSING <-- TEXTURE DATA STREAM --> MOSAIC
    byte[]      _pix;
    boolean     _savedImage = false;
    boolean     _loaded     = false;
    ////////////////////////////////////////////////////// DO NOT EDIT

    public void settings() {
        // set here your processing texture size and render engine (P2D or P3D)
        size(1280, 720);
        //size(1280, 720,P3D);
    }

     public void setup() {
       //////////////// DO NOT EDIT
       mosaicSetup();
       //////////////// DO NOT EDIT


       // -------------------- YOUR SETUP CODE HERE
       frameRate(30);
       smooth();
       // ..............


       // END SETUP
     }

     public void draw() {

        // -------------------- YOUR DRAW CODE HERE
        background(0);
        // ..............


        //////////////// DO NOT EDIT
        mosaicGetDataInlet();
        mosaicSetDataOutlet();
        mosaicSendTexture();
        //////////////// DO NOT EDIT


        // END DRAW
     }

     ////////////////////////////////////////////////////// DO NOT EDIT
     // MOSAIC BRIDGE CUSTOM FUNCTIONS
     public void mosaicSetup(){
       for (int i = 0 ; i < _dataInSize; i++) {
         _mosaic_data_inlet[i] = 0.0f;
       }
       for (int i = 0 ; i < _dataOutSize; i++) {
         _mosaic_data_outlet[i] = 0.0f;
       }
     }
     public void mosaicGetDataInlet(){
       _dataIN = loadStrings("Empty_in.txt");
       if(_dataIN != null){
         for (int i = 0 ; i < _dataInSize; i++) {
           if(_dataInSize <= _dataIN.length){
             _mosaic_data_inlet[i] = Float.parseFloat(_dataIN[i]);
           }
         }
       }
     }
     public void mosaicSetDataOutlet(){
       for (int i = 0 ; i < _dataOutSize; i++) {
         _dataOUT[i] = str(_mosaic_data_outlet[i]);
       }
       saveStrings("Empty_out.txt",_dataOUT);
     }
     public void mosaicSendTexture(){
       if(!_loaded){
         _loaded = true;
         //surface.setLocation(displayWidth*2,displayHeight*2);
         surface.setVisible(false);
       }
       loadPixels();
       _pix = new byte[pixels.length*3];
       int index = 0;
       for (int i = 0; i < pixels.length; i++) {
           _pix[index] = (byte)red(pixels[i]);
           index++;
           _pix[index] = (byte)green(pixels[i]);
           index++;
           _pix[index] = (byte)blue(pixels[i]);
           index++;
       }
       saveBytes("Empty.dat", _pix);

       if(!_savedImage){
           _savedImage = true;
           saveFrame("Empty.png");
       }
     }
     ////////////////////////////////////////////////////// DO NOT EDIT
}
