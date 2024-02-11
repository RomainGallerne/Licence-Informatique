int flou(OCTET *ImgIn,int nW,int t[9],int x,int y) {
 int res=0;
 if (t[0]) {res+=ImgIn[(x-1)*nW+y-1];}
 if (t[1]) {res+=ImgIn[(x-1)*nW+y];}
 if (t[2]) {res+=ImgIn[(x-1)*nW+y+1];}
 if (t[3]) {res+=ImgIn[x*nW+y-1];}
 if (t[4]) {res+=ImgIn[x*nW+y];}
 if (t[5]) {res+=ImgIn[x*nW+y+1];}
 if (t[6]) {res+=ImgIn[(x+1)*nW+y-1];}
 if (t[7]) {res+=ImgIn[(x+1)*nW+y];}
 if (t[8]) {res+=ImgIn[(x+1)*nW+y+1];}
 return res/9;
}