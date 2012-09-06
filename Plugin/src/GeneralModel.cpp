/*
 * GeneralModel.cpp
 *
 *  Created on: Mar 20, 2010
 *      Author: ksgy
 */

#include "GeneralModel.h"

GeneralModel::GeneralModel() {
	XPlaneData = new XpData();

}

GeneralModel::~GeneralModel() {
	delete XPlaneData;
}


void GeneralModel::run(){

}
