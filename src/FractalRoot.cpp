
#include "FractalRoot.h"

FractalRoot::FractalRoot(){
    
}

void FractalRoot::setup(float startAngle, int _numSides, float _strutFactor, int maxlevels){
    pointArr.clear();
    
    float centX = ofGetWidth()/2;
    float centY = ofGetHeight()/2;
    int vertexNum = _numSides*2; //頂点数（トゲの数*2）
    strutFactor = _strutFactor;
    for (int i = 0; i < vertexNum; i++) {
        float x,y;
        if (i%2 == 0) { //外側の頂点
            x = centX + 380*cos(ofDegToRad(startAngle + 360*i/vertexNum));
            y = centY + 380*sin(ofDegToRad(startAngle + 360*i/vertexNum));
        } else {
            x = centX + (380*0.6*cos(ofDegToRad(startAngle + 360*i/vertexNum)));
            y = centY + (380*0.6*sin(ofDegToRad(startAngle+360*i/vertexNum)));
        }
        ofVec2f pp (x, y);
        pointArr.push_back(pp);
    }
    rootBranch.setup(0, 0, pointArr, strutFactor, maxlevels);
}

void FractalRoot::drawShape(int lineWidth){
    rootBranch.drawMe(lineWidth);
}
