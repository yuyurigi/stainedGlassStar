#include "Branch.h"


Branch::Branch(){
    level = 0;
    num = 0;
    strutFactor = 0;
}

void Branch::setup(int _lev, int _n, vector <ofVec2f> _points, float _strutFactor, int _maxlevels){
    level = _lev;
    num = _n;
    outerPoints = _points;
    strutFactor = _strutFactor;
    maxlevels = _maxlevels;
    //midPoints = calcMidPoints();
    projPoints = calcStrutPoints();
    
    myBranches.clear();
    
    
    
    if ((level+1) < maxlevels) {
        
        
        Branch childBranch;
        childBranch.setup(level+1, 0, projPoints, strutFactor, maxlevels);
        myBranches.emplace_back(childBranch);

    }
    
             
}


void Branch::drawMe(int lineWidth){
    if(level == 0){
        ofBeginShape();
        for (int i = 0; i < outerPoints.size(); i++) {
            ofFill();
            ofSetColor(255);
            ofVertex(outerPoints[i].x, outerPoints[i].y);
        }
        ofEndShape();
    }
    
    ofSetLineWidth(lineWidth);
    ofSetColor(0, 0, 0);
    
    for (int i = 0; i < outerPoints.size(); i++){
        int nexti = i+1;
        if (nexti == outerPoints.size()) { nexti = 0; }
        ofDrawLine(outerPoints[i].x, outerPoints[i].y, outerPoints[nexti].x, outerPoints[nexti].y);
    }
    
    for (int j = 0; j < projPoints.size(); j++) {
        ofDrawLine(outerPoints[j].x, outerPoints[j].y, projPoints[j].x, projPoints[j].y);
        }
    
    if (level+1 == maxlevels){
        for (int j = 0; j < projPoints.size()-1; j++) {
            ofDrawLine(projPoints[j].x, projPoints[j].y, projPoints[j+1].x, projPoints[j+1].y);
            }
        ofDrawLine(projPoints[projPoints.size()-1].x, projPoints[projPoints.size()-1].y, projPoints[0].x, projPoints[0].y);
    }
    
    for (int k = 0; k < myBranches.size(); k++) {
        myBranches[k].drawMe(lineWidth);
    }
}

vector <ofVec2f> Branch::calcStrutPoints(){
    vector <ofVec2f> strutArray;
    strutArray.resize(outerPoints.size());
    for (int i = 0; i < outerPoints.size(); i++) {
        int nexti = i + outerPoints.size()/2;
        if (nexti >= outerPoints.size()) {nexti -= outerPoints.size();}
        ofVec2f thisSP = calcProjPoint(i, outerPoints[i], outerPoints[nexti]);
        strutArray[i] = thisSP;
    }
    return strutArray;
}

ofVec2f Branch::calcProjPoint(int n, ofVec2f mp, ofVec2f op){
    float px, py;
    float adj, opp;
    if (op.x > mp.x) {
        opp = op.x - mp.x;
    } else {
        opp = mp.x - op.x;
    }
    if (op.y > mp.y) {
        adj = op.y - mp.y;
    } else {
        adj = mp.y - op.y;
    }
    
    if(n%2 == 0){
        if (op.x > mp.x) {
            px = mp.x + (opp * strutFactor);
        } else {
            px = mp.x - (opp * strutFactor);
        }
        if (op.y > mp.y) {
            py = mp.y + (adj * strutFactor);
        } else {
            py = mp.y - (adj * strutFactor);
        }
    } else {
        float dist_op_mp = ofDist(op.x, op.y, mp.x, mp.y);
        float dist_op = ofDist(op.x, op.y, ofGetWidth()/2, ofGetHeight()/2);
        float dist = dist_op_mp - dist_op - outR*0.6;
        float strutFactor2 = dist/dist_op_mp;
        
        if (op.x > mp.x) {
            px = mp.x + (opp * strutFactor2);
        } else {
            px = mp.x - (opp * strutFactor2);
        }
        if (op.y > mp.y) {
            py = mp.y + (adj * strutFactor2);
        } else {
            py = mp.y - (adj * strutFactor2);
        }
    }
    
    if(n == 0){
        outR = ofDist(ofGetWidth()/2, ofGetHeight()/2, px, py);
    }
    
    return ofVec2f(px, py);
}

