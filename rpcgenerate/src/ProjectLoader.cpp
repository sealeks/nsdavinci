/* 
 * File:   ProjectLoader.cpp
 * Author: Serg Alexeev sealeks@mail.ru Alexeev sealeks@mail.ru
 * 
 * Created on 29 Декабрь 2009 г., 17:12
 */

#include "ProjectLoader.h"

 // путь к проекту
std::string basePath;
 // тмя проекта
std::string name;


void dvnci::LoadProjectSetting(){
   basePath=getAppPath();
}

tagsbase* dvnci::loadMainBase(int& error_){
    dvnci::LoadProjectSetting();
    error_=0;
    try {
        return new tagsbase(basePath);

    }
    catch(...){
        error_=1;
    }
    return (tagsbase*)0;
}

// загрузка пути основного проекта из реестра
std::string dvnci::getLocalAppInfo(){
     return getAppPath();
}

// заgbcm пути основного проекта в реестр
void dvnci::setLocalAppInfo(std::string path_){
    setAppPath(path_);
}

