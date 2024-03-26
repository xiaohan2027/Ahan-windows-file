/*
 * @Begin: *********************************
 * @Author: Liuchangqi
 * @Company: LZU
 * @Date: 2020-04-26 20:32:24
 * @LastEditTime: 2020-06-22 23:10:50
 * @Email: liuchq16@lzu.edu.cn
 * @Descripttion: 
 * @End:   *********************************
 */

#include <iostream>
#include <iomanip>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include "TStyle.h"
#include <TApplication.h>
#include <vector>
#include <math.h>
#include <string.h> 
#include <fstream>
#include <TCanvas.h> 

using namespace std;

void test()
{

    ifstream in;
    in.open("Results.txt",ios_base::in);  //读取数据

    int flag = 1;


    int eventID,TrackID;
    double Xpos,Ypos,Zpos,edepStep,kine,Seckine;
     int EventID_old = 0;
    int TrackID_old = 0;
    string name_old,processN_old;
    string name,processN;
    double kine_old=0,Seckine_old=0;
    double position_x_old;
    double  position_y_old;
    double  position_z_old,edepStep_old;
    string s("scater"),a("absorb"),c("compt"),p("phot");

   string str;
    int nlines = 0;

    gStyle->SetOptTitle(3);
    gStyle->SetOptStat(1);   
    gStyle->SetPalette(1);   //二维数据图例设置

       //漏掉第一行字符

    // ------------ Txt for Coincidence ----------------// 
    ofstream fout_Coincidence;
    fout_Coincidence.open("Coincidence.txt",ios_base::in|ios_base::trunc);//
    fout_Coincidence <<"eventID"<<"\t"<<"TrackID"<<"\t" <<"Xpos"<<"\t"<<"Ypos"<< "\t"<<"Zpos" <<"\t"<<"edepStep"<< "\t"<<"kine"
   << "\t"<<"Seckine"<<"\t"<<"name"<<"\t"<<"processN"<<endl;

ofstream fout_data;
    fout_data.open("data.txt",ios_base::in|ios_base::trunc);//
    fout_data <<"eventID"<<"\t" <<"Xpos"<<"\t"<<"Ypos"<< "\t"<<"Zpos" <<"\t"<<"kine" << "\t"<<"Seckine"<<"\t"<<"name"<<"\t"<<"processN"<<endl;

    ofstream fout_DATA;
    fout_DATA.open("DATA.txt",ios_base::in|ios_base::trunc);//
    fout_DATA <<"eventID"<<"\t" <<"SXpos"<<"\t"<<"SYpos"<< "\t"<<"SZpos" <<"\t"<<"AXpos"
    <<"\t"<<"AYpos"<< "\t"<<"AZpos"<<"\t"<<"E2" << "\t"<<"E1" << endl;

    while(1)
    {
        getline(in, str)>>eventID>>TrackID>>Xpos>>Ypos>>Zpos>>edepStep>>kine>>Seckine>>name>>processN;  //一行一行输入
        if(!in.good()) 
        {
            printf("read line:%d!\n",nlines);
            break;
        }
        
        if(eventID == EventID_old)
        {//if(abs(kine_old + Seckine_old - 662) < 0.002 )
            if(name_old==s && name==a && processN_old==c && processN==p && abs(kine_old + Seckine_old - 0.662) < 0.002 && kine==0)
            {
                 fout_Coincidence<< EventID_old<< "\t"<<TrackID<<"\t"<< position_x_old  <<"\t"<< position_y_old  << "\t" <<  position_z_old << "\t" 
                << edepStep_old  <<"\t"<<kine_old  << "\t" << Seckine_old << "\t" 
                << name_old <<"\t"<<processN_old<<endl;

                fout_Coincidence<< eventID << "\t"  <<TrackID<<"\t"<< Xpos  <<"\t"<< Ypos  << "\t" <<  Zpos << "\t" 
                << edepStep  <<"\t"<<kine << "\t" << Seckine << "\t" 
                << name <<"\t"<<processN<<endl;
                
                 fout_data<< EventID_old << "\t"  << position_x_old  <<"\t"<< position_y_old  << "\t" <<  position_z_old  <<"\t"<<kine_old << "\t" << Seckine_old << "\t" 
                << name_old <<"\t"<<processN_old<<endl; 
                fout_data<< eventID << "\t"  << Xpos  <<"\t"<< Ypos  << "\t" <<  Zpos  <<"\t"<<kine << "\t" << Seckine << "\t" 
                << name <<"\t"<<processN<<endl; 
                
                fout_DATA<< eventID << "\t"  <<position_x_old  <<"\t"<< position_y_old  << "\t" <<  position_z_old << "\t"<< Xpos  <<"\t"<< Ypos  << "\t" <<  Zpos 
                << "\t" <<kine_old  << "\t" << Seckine_old <<endl;


            }
     
        }
EventID_old = eventID;
name_old=name;
kine_old=kine;
Seckine_old=Seckine;
processN_old=processN;
position_x_old = Xpos;
position_y_old = Ypos;
position_z_old = Zpos;
edepStep_old=edepStep;
        
       nlines++;    //how many events we have 	
    }
	in.close();

}
