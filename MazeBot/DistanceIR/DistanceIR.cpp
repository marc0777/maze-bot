/************************************************************************************************************
 * SharpIR.h - Arduino library for retrieving distance (in cm) from the analog GP2Y0A21Y and GP2Y0A02YK     *
 * Distance sensors                                                                                         *
 * Copyright 2014 Dr. Marcal Casas-Cartagena (marcal.casas@gmail.com)                                       *
 * Last update: 07.01.2014                                                                                  *
 ************************************************************************************************************
 
 ************************************************************************************************************
 * This library is free software; you can redistribute it and/or                                            *
 * modify it under the terms of the GNU Lesser General Public                                               *
 * License as published by the Free Software Foundation; either                                             *
 * version 2.1 of the License, or (at your option) any later version.                                       *
 *                                                                                                          *
 * This library is distributed in the hope that it will be useful,                                          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                                           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                                        *
 * Lesser General Public License for more details.                                                          *
 *                                                                                                          *
 * You should have received a copy of the GNU Lesser General Public                                         *
 * License along with this library; if not, write to the Free Software                                      *
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA                               *
 ***********************************************************************************************************/

#include "Arduino.h"
#include "SharpIR.h"



SharpIR::SharpIR(int irPin, int avg, int tolerance, int sensorModel) {
  
    _irPin=irPin;
    _avg=avg;
    _tol=tolerance/100;
    _model=sensorModel;

    pinMode(irPin,INPUT);
    analogReference(DEFAULT);
 
}

int SharpIR::cm() {
    
    int raw=analogRead(_irPin);
    float voltFromRaw=map(raw, 0, 1023, 0, 5000);   
    int puntualDistance;    
    if (_model==1080)      
        puntualDistance=27.728*pow(voltFromRaw/1000, -1.2045);
    else if (_model==20150)
        puntualDistance=61.573*pow(voltFromRaw/1000, -1.1068);
        
    return puntualDistance;
}



int SharpIR::distance() {
    _p=0;
    _sum=0;
     
    for (int i=0; i<_avg; i++){
        int foo=cm();    
        if (foo>=(_tol*_previousDistance)){       
            _previousDistance=foo;
            _sum=_sum+foo;
            _p++;        
        }      
    }  
    int accurateDistance=_sum/_p;
    
    return accurateDistance;
}




