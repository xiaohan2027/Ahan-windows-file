#ifndef __mystyle_H__
#define __mystyle_H__

#include <TStyle.h>
void mystyle()
{
     //canvas
     gStyle->SetCanvasBorderMode(0);
     gStyle->SetCanvasBorderSize(0);


     //axes
     gStyle->SetLabelSize(0.05,"xyz");
     gStyle->SetLabelOffset(0.01,"xyz");
     gStyle->SetLabelFont(132,"xyz");

     gStyle->SetTitleFont(132,"xyz");
     gStyle->SetTitleColor(1,"xyz");
     gStyle->SetTitleSize(0.05,"xyz");
     gStyle->SetTitleOffset(1.1);

     //pad

     gStyle->SetPadGridX(1);
     gStyle->SetPadGridY(1);

     //gStyle->SetOptTitle(3);
     gStyle->SetOptStat(1);
     gStyle->SetPalette(1);

     gStyle->SetStatFont(132);
     gStyle->SetStatTextColor(1);
     gStyle->SetStatFontSize(0.05);

     gStyle->SetLabelFont(132);
     gStyle->SetPaintTextFormat("t");

     gStyle->SetTextAlign(12);
     gStyle->SetTextFont(132);

    //title
     gStyle->SetTitleTextColor(1);
     gStyle->SetTitleFont(132,"title");

     //gStyle->SetLegendBorderSize(1);
     //gStyle->SetLegendFillColor(5);
     //gStyle->SetLegendFont(132);
}

#endif 
