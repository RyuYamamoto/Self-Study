#include <stdio.h>
#include <math.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>

typedef struct
{
	int all_alea;
	int white;
	int black;
}area;
area space={0};

int sum,num;
float ave;

IplImage *img = NULL;
IplImage *imgR, *imgG, *imgB, *imgThreshold_R, *imgThreshold_G, *imgThreshold_B, *imgResult, *imgTmp;

//マウスカーソルが置かれているところの座標とRGB値の取得
void onMouse(int event, int x, int y, int flags, void* param){
  printf("x:%d y:%d r:%d g:%d b:%d %s", x, y, // マウス座標とRGBを出力
    (unsigned char)imgR->imageDataOrigin[x+y*imgR->width],
    (unsigned char)imgG->imageDataOrigin[x+y*imgG->width],
    (unsigned char)imgB->imageDataOrigin[x+y*imgB->width],
    "\n");
}

int main(int argc, char** argv) {
  bool isStop = false;
  CvCapture *capture = NULL;
  capture = cvCreateCameraCapture(0);
  //capture = cvCaptureFromAVI("test.avi");
  if(capture == NULL){
    printf("capture device not found!!");
    return -1;
  }

  img = cvQueryFrame(capture);
  const int w = img->width;
  const int h = img->height;

  imgR = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
  imgG = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
  imgB = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
  imgThreshold_R = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
  imgThreshold_G = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
  imgThreshold_B = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
  imgResult = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
  imgTmp = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);

  char winNameCapture[] = "Capture";
  char winNameResult[] = "Result";

  cvNamedWindow(winNameCapture, CV_WINDOW_AUTOSIZE);
  cvNamedWindow(winNameResult, CV_WINDOW_AUTOSIZE);

  cvSetMouseCallback(winNameCapture, onMouse, 0);
  cvSetMouseCallback(winNameResult, onMouse, 0);
  
  int waitKey;
  while (1) {
    if(!isStop){
		num++;
	  space.white=0;
      if((img = cvQueryFrame(capture)) == NULL) break;
      cvSplit(img, imgB, imgG, imgR, NULL); // BGRを分解
      
      // RGB要素をそれぞれ調べて、赤いピクセルを論理積で抽出
      cvThreshold(imgR, imgThreshold_R, 60, 255, CV_THRESH_BINARY_INV); // 赤が150以上
      cvThreshold(imgG, imgThreshold_G, /*115*/80, 255, CV_THRESH_BINARY_INV); // 緑が100以下
      cvThreshold(imgB, imgThreshold_B, /*80*/55, 255, CV_THRESH_BINARY );
      cvAnd(imgThreshold_B, imgThreshold_R, imgTmp, NULL);
      cvAnd(imgTmp, imgThreshold_G, imgResult, NULL);
	  for(int y=0;y<imgResult->height;y++){
		  for(int x=0;x<imgResult->width;x++){
			  const int val=imgResult->imageData[y*imgResult->widthStep+x];
			  if(val&255){
				  ++space.white;
			  }
		  }
	  }
	  float cm;
	  cm = 241399.608352735*pow(space.white,-0.921749038);
	  printf("距離：%f\n",cm);
	  //sum+=space.white;
	  //printf("面積%d\n",space.white);

      cvShowImage(winNameCapture, img);
      cvShowImage(winNameResult, imgResult);
    }

    waitKey = cvWaitKey(33);
    if(waitKey == 'q') break;
    if(waitKey == ' '){
      isStop = !isStop;
      if(isStop) printf("stop\n");
      else printf("start\n");
    }
  }
  
  cvReleaseCapture(&capture);
  cvDestroyWindow(winNameCapture);
  cvDestroyWindow(winNameResult);
  ave = (float)sum/num;
  printf("%f\n",ave);
  while(1);
  return 0;
}