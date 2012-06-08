/*    */


var simulator = {};


// initializer


simulator.initializer = function(tag ,start , stop){
    
  this.tag = tag;
  if (start || start==0){
      this.valid = true;
      this.start = start;
  }
  if (stop || stop==0)
        this.stop = stop;
  if (this.valid){
      this.atach();
  }   
}

simulator.initializer.prototype.atach = function(){
    window.$$((this.tag + ' @ ' + this.start).toString())
}


simulator.initializer.prototype.detach = function(){
    if (this.valid && (this.stop || this.stop==0)){
       window.$$((this.tag + ' @ ' + this.stop).toString());}
}

simulator.initializer.prototype.execute = function(){
 
}


// casevalue

simulator.valueobserver = function(tag ,start , source ,stop){
  this.tag = tag;
  if (source){
      this.valid = true;
      this.source = source;
  }
  if (start || start==0)
        this.start = start;
  if (stop || start==0)
        this.stop = stop;    
  if (this.valid){
      this.atach();
  }     
}

simulator.valueobserver.prototype.atach = function(){
    if (this.valid && (this.start || this.start==0))
       $$(this.tag + ' @ ' + this.start);
}


simulator.valueobserver.prototype.detach = function(){
    if (this.valid && (this.start || this.start==0))
       $$(this.tag + ' @ ' + this.stop)
}

simulator.valueobserver.prototype.execute = function(){
    $$(' ' + this.tag + ' @ (' + this.source + ')');
}


// differeciator

simulator.differeciator = function(tag ,start , source ,stop){
  this.tag = tag;
  if (source){
      this.valid = true;
      this.source = source;
  }
  if (start || start==0)
        this.start = start;
  if (stop || start==0)
        this.stop = stop;    
  if (this.valid){
      this.atach();
  }     
}

simulator.differeciator.prototype.atach = function(){
 
     if (this.valid && (this.start || this.start==0))
       $$(this.tag + ' @ ' + this.start);
 
    var ts = this;
    
    this.diffhandler = function(){ts.diffevent(event);};
    if (window.addExpressionListener( this.diffhandler , this.source))
        this.diffset=true; 
    else
       console.log('AddExpressionListener source no regist');
}


simulator.differeciator.prototype.detach = function(){
    if (this.valid && (this.start || this.start==0))
       $$(this.tag + ' @ ' + this.stop)
    if (this.diffhandler && this.diffset)
        window.removeExpressionListener( this.autohandler);
}

simulator.differeciator.prototype.execute = function(){
   
}

simulator.differeciator.prototype.diffevent = function(event){
    if (event.expression==this.source){
       $$(this.tag + ' @ ' + event.value)
       console.log(this.tag,event.value);
        }      
}



// simulator.valvle

simulator.valve  = function(on, off, don, doff, ron, roff, timeopen, timeclose , initpos){
    this.on= on;
    this.off=off;
    this.don= don;
    this.doff=doff; 
    this.ron= ron;
    this.roff=roff;  
    this.timeopen= timeopen!==undefined ? timeopen : 10000;
    this.timeclose= timeclose!==undefined ? timeclose : 10000; 
    this.timeopen= this.timeopen>50 ? this.timeopen : 50;
    this.timeclose= this.timeclose>50 ? this.timeclose : 50;     
    this.initpos= this.initpos ? this.initpos : 0; 
    this.state = 0;
    this.atach();
}

simulator.valve.prototype.atach = function(){
      
    var ts =this;
    if (this.ron){
        this.ronhandler = function(){
            ts.ronevent(event);
        };
        if (window.addExpressionListener( this.ronhandler , this.ron))
            this.ronset=true; 
        else
            console.log('AddExpressionListener ronno regist');
    }
    
    if (this.roff){
        this.roffhandler = function(){
            ts.roffevent(event);
        };
        if (window.addExpressionListener( this.roffhandler , this.roff))
            this.roffset=true; 
        else
            console.log('AddExpressionListener ronoff regist');
    }
    
    if (this.don){
        this.donhandler = function(){
            ts.donevent(event);
        };
        if (window.addExpressionListener( this.donhandler , this.don))
            this.donset=true; 
        else
            console.log('AddExpressionListener donno regist');
    }
    
    if (this.doff){
        this.doffhandler = function(){
            ts.doffevent(event);
        };
        if (window.addExpressionListener( this.doffhandler , this.doff))
            this.doffset=true; 
        else
            console.log('AddExpressionListener doffno regist');
    }
    
    if (this.on){
        this.onhandler = function(){
            ts.onevent(event);
        };
        if (window.addExpressionListener( this.onhandler , this.on))
            this.onset=true; 
        else
            console.log('AddExpressionListener onno regist');
    }
    
    if (this.off){
        this.offhandler = function(){
            ts.offevent(event);
        };
        if (window.addExpressionListener( this.offhandler , this.off))
            this.offset=true; 
        else
            console.log('AddExpressionListener offno regist');
    }    
   
}

simulator.valve.prototype.detach = function(){
    if (this.ronhandler && this.ronset)
        window.removeExpressionListener( this.ronhandler);
    if (this.roffhandler && this.roffset)
        window.removeExpressionListener( this.roffhandler);
    if (this.donhandler && this.donset)
        window.removeExpressionListener( this.donhandler);
    if (this.doffhandler && this.doffset)
        window.removeExpressionListener( this.doffhandler);
    if (this.onhandler && this.onset)
        window.removeExpressionListener( this.onhandler);
    if (this.offhandler && this.offset)
        window.removeExpressionListener( this.offhandler);    
}


simulator.valve.prototype.ronevent = function(event){
    if (event.expression==this.ron && event.valid){     
        var ts = this;
        if (event.value && !this._ron){
            
           this._ron=1;
           
           // Есть don или doff
            if (ts.don || ts.doff){
                setTimeout(function(){
                    if (ts.on && ts._on){
                        $$(ts.ron + ' @ 0');
                        return;
                    }                    
                    if (ts.off && ts._off) $$(ts.off + ' @ 0');
                    if (ts.roff && ts._roff) $$(ts.roff + ' @ 0');
                    if (ts.doff && ts._doff) $$(ts.doff + ' @ 0');  
                    if (ts.don && !ts._don) $$(ts.don + ' @ 1');
                },1);
                return;
            } 
              
            // Есть  on              
            if (ts.on) {
                
                if (this.intervalid)
                    clearInterval(this.intervalid);
                this.intervalid=0;
                
                if (ts.roff && ts._roff){
                setTimeout(function(){
                    $$(ts.roff + ' @ 0');
                },1);} 
            
                var intervalfunc= function(){
                    if (ts.on) $$(ts.on + ' @ 1');
                    this.state=0;
                    if (ts.intervalid){
                        clearInterval(ts.intervalid);
                        ts.intervalid=0;
                    }                
                }
                this.intervalid = setInterval(intervalfunc,this.timeopen);
                return;               
            }
            
            // Есть  off
            if (ts.off) {
                
                if (this.intervalid)
                    clearInterval(this.intervalid);
                this.intervalid=0;
                
                if (ts.roff && ts._roff){
                    setTimeout(function(){
                        $$(ts.roff + ' @ 0');
                    },1);
                } 
            
                var intervalfunc= function(){
                    if (ts.off) $$(ts.off + ' @ 0');
                    this.state=0;
                    if (ts.intervalid){
                        clearInterval(ts.intervalid);
                        ts.intervalid=0;
                    }                
                }
                
                this.intervalid = setInterval(intervalfunc,this.timeclose);
                
                return;
            }
                        
        }
        
        
        if (!event.value && this._ron){
            
            this._ron=0;
            
            if (this.intervalid)
                clearInterval(this.intervalid);
            
            if (!ts.roff){
                
                if (this.intervalid)
                    clearInterval(this.intervalid);
                this.intervalid=0;
                
      
                if (ts.doff || ts.don){
                    setTimeout(function(){
                        if (ts.doff && !ts._doff) $$(ts.doff + ' @ 1');
                        if (ts.don) $$(ts.don + ' @ 0');
                    },1);
                    return ;
                }               
                
            
                var intervalfunc= function(){
                    if (ts.off) $$(ts.off + ' @ 1');
                    if (ts.on) $$(ts.on + ' @ 0');
                    this.state=0;
                    if (ts.intervalid){
                        clearInterval(ts.intervalid);
                        ts.intervalid=0;
                    }                
                }
                
                this.intervalid = setInterval(intervalfunc,this.timeclose);
                
                return;
            }
            
            if (ts.don && ts._don)
             setTimeout(function(){
                        if (ts.don) $$(ts.don + ' @ 0');},1);
            
            
        }       
    }       
}


simulator.valve.prototype.roffevent = function(event){
    if (event.expression==this.roff && event.valid){     
        var ts = this;
        if (event.value && !this._roff){
            
           this._roff=1;
           
           // Есть don или doff
            if (ts.don || ts.doff){
                setTimeout(function(){
                     if (ts.off && ts._off){
                        $$(ts.roff + ' @ 0');
                        return;
                    }    
                    if (ts.on && ts._on) $$(ts.on + ' @ 0');
                    if (ts.ron && ts._ron) $$(ts.ron + ' @ 0');
                    if (ts.don && ts._don) $$(ts.don + ' @ 0');  
                    if (ts.doff && !ts._doff) $$(ts.doff + ' @ 1');
                },1);
                return;
            } 
            
            
            // Есть  off
            if (ts.off) {
                
                if (this.intervalid)
                    clearInterval(this.intervalid);
                this.intervalid=0;
                
                if (ts.ron && ts._ron){
                    setTimeout(function(){
                        $$(ts.ron + ' @ 0');
                    },1);
                } 
            
                var intervalfunc= function(){
                    if (ts.off) $$(ts.off + ' @ 1');
                    this.state=0;
                    if (ts.intervalid){
                        clearInterval(ts.intervalid);
                        ts.intervalid=0;
                    }                
                }
                
                this.intervalid = setInterval(intervalfunc,this.timeclose);
                
                return;
            }
            
            // Есть  on              
            if (ts.on) {
                
                if (this.intervalid)
                    clearInterval(this.intervalid);
                this.intervalid=0;
                
                if (ts.ron && ts._ron){
                setTimeout(function(){
                    $$(ts.ron + ' @ 0');
                },1);} 
            
                var intervalfunc= function(){
                    if (ts.on) $$(ts.on + ' @ 0');
                    this.state=0;
                    if (ts.intervalid){
                        clearInterval(ts.intervalid);
                        ts.intervalid=0;
                    }                
                }
                this.intervalid = setInterval(intervalfunc,this.timeopen);
                return;               
            }
            
            
        }
            
        if (!event.value && this._roff){
            
            this._roff=0;
            
            if (this.intervalid)
                clearInterval(this.intervalid);
            
             if (!ts.ron){
                
                if (this.intervalid)
                    clearInterval(this.intervalid);
                this.intervalid=0;
                
      
                if (ts.doff || ts.don){
                    setTimeout(function(){
                        if (ts.don && !ts._don) $$(ts.don + ' @ 1');
                        if (ts.doff) $$(ts.doff + ' @ 0');
                    },1);
                    return ;
                }               
                
            
                var intervalfunc= function(){
                    if (ts.on) $$(ts.on + ' @ 1');
                    if (ts.off) $$(ts.off + ' @ 0');
                    this.state=0;
                    if (ts.intervalid){
                        clearInterval(ts.intervalid);
                        ts.intervalid=0;
                    }                
                }
                
                this.intervalid = setInterval(intervalfunc,this.timeclose);
                
                return;
            }
            
            if (ts.doff && ts._doff)
                setTimeout(function(){
                    if (ts.doff) $$(ts.doff + ' @ 0');
                },1);
        }       
    }         
}

simulator.valve.prototype.donevent = function(event){
    if (event.expression==this.don && event.valid){     
        var ts = this;
        if (event.value && !this._don){       
            this._don=1;
            if (this.intervalid)
                clearInterval(this.intervalid);
            this.intervalid=0;
            
            var intervalfunc= function(){
                if (ts.on) $$(ts.on + ' @ 1');
                this.state=0;
                if (ts.intervalid){
                    clearInterval(ts.intervalid);
                    ts.intervalid=0;
                }
            }
            this.intervalid = setInterval(intervalfunc,this.timeopen);           
        }
        if (!event.value && this._don){
            
            this._don=0;
            
            if (!ts.roff){
                
                if (this.intervalid)
                    clearInterval(this.intervalid);
                this.intervalid=0;
           
                          
                var intervalfunc= function(){
                    if (ts.off) $$(ts.off + ' @ 1');
                    if (ts.on) $$(ts.on + ' @ 0');
                    this.state=0;
                    if (ts.intervalid){
                        clearInterval(ts.intervalid);
                        ts.intervalid=0;
                    }                
                }
                
                this.intervalid = setInterval(intervalfunc,this.timeclose);
                
                return;
            }
        }       
    }       
}


simulator.valve.prototype.doffevent = function(event){
    if (event.expression==this.doff && event.valid){     
        var ts = this;
        if (event.value && !this._doff){
            this._doff=1; 
            if (this.intervalid)
                clearInterval(this.intervalid);
            this.intervalid=0;           
            var intervalfunc= function(){
                if (ts.on) $$(ts.on + ' @ 0');
                if (ts.off) $$(ts.off + ' @ 1');
                this.state=0;
                if (ts.intervalid){
                    clearInterval(ts.intervalid);
                    ts.intervalid=0;
                }
            }
            this.intervalid = setInterval(intervalfunc,this.timeclose);            
        }
        if (!event.value && this._doff){
            
            this._doff=0;
            
            if (!ts.ron){
                
                if (this.intervalid)
                    clearInterval(this.intervalid);
                this.intervalid=0;
           
                          
                var intervalfunc= function(){
                    if (ts.on) $$(ts.on + ' @ 1');
                    if (ts.off) $$(ts.off + ' @ 0');
                    this.state=0;
                    if (ts.intervalid){
                        clearInterval(ts.intervalid);
                        ts.intervalid=0;
                    }                
                }
                
                this.intervalid = setInterval(intervalfunc,this.timeopen);
                
                return;
            }
        }
    }         
}

simulator.valve.prototype.onevent = function(event){
    if (event.expression==this.on && event.valid){     
        var ts = this;
        if (event.value && !this._on){
           this._on=1;
           this.state=1;
            setTimeout(function(){if (ts.ron && ts._ron && ts.roff) $$(ts.ron + ' @ 0');},1);
            if (this.intervalid)
                clearInterval(this.intervalid);
            this.intervalid=0;              
        }
        if (!event.value && this._on){
            this._on=0;
            if (this.state==1) this.state=0;
        }       
    }       
}


simulator.valve.prototype.offevent = function(event){
    if (event.expression==this.off && event.valid){     
        var ts = this;
        if (event.value && !this._off){
           this._off=1; 
           this.state=2;
           setTimeout(function(){if (ts.roff && ts._roff && ts.ron) $$(ts.roff + ' @ 0');},1);
           if (this.intervalid)
                clearInterval(this.intervalid);
           this.intervalid=0;             
        }
        if (!event.value && this._off){
            this._off=0;
            if (this.state==2) this.state=0;
        }       
    }         
}


simulator.valve.prototype.execute = function(){
  
}
 
// simulator.actuator

simulator.actuator  = function(pos, sp, tick){
    this.pos= pos;
    this.sp=sp;
    this.tick=tick ? tick : 0.05;
    this.enable=true;
}

simulator.actuator.prototype.position = function(){
    return this.pos;
}

simulator.actuator.prototype.atach = function(){

}


simulator.actuator.prototype.detach = function(){

}

simulator.actuator.prototype.sp = function(val){
    $$(this.sp + ' @  '+ val );
}

simulator.actuator.prototype.spdiff = function(val){
    $$(this.sp + ' @  ('+ this.sp + ' + '+ val + ')' );
}

simulator.actuator.prototype.execute = function(){
    $$('(abs(' + this.pos + ' - '+ this.sp + ') > ' + this.tick + ') ? (' + this.pos + ' @ (' + this.pos + ' + (' + this.sp + '<' + this.pos + ' ? (- ' + this.tick + ') : ('+ this.tick + ')  ))) : 0 ');
}


//  regulator


simulator.regulator  = function(val, valsp, pos, possp, auto,  rev, kp , ki , kd , tick){
    this.val= val;
    this.valsp=valsp;
    this.pos= pos;
    this.possp=possp;
    
    
    this.auto=auto;
    this.autostate=false;
  
    this.diff = !rev ? '(' + valsp + ' - ' + val + ') / ('+val+'.maxeu - '+val+'.mineu)' : '(' + val + ' - ' + valsp + ') / ('+val+'.maxeu - '+val+'.mineu)';
    this.diffstate = 0;
   
    
  
    this.kp= kp===undefined ? 1 : kp;
    this.ki= ki===undefined ? 10 : ki;
    this.kd= kd===undefined ? 1 : kd;
    this.tick= tick;
    
   
    this.possp=possp; 
    this.auto=auto;    
    this.tick=tick ? tick : 0.05;
    this.K = 0;
    this.I = 0;
    this.D = 0;
    this.olddiff=undefined;
    
    this.atach();
    
    
}

simulator.regulator.prototype.atach = function(){
    
    this.actuator = new simulator.actuator(this.pos, this.possp, this.tick);
    
    var ts =this;
    
    //console.log('attach regulator');
    
    this.autohandler = function(){ts.autoevent(event);};
    if (window.addExpressionListener( this.autohandler , this.auto))
        this.autoset=true; 
    else
       console.log('AddExpressionListener auto no regist');     

    this.diffhandler = function(){ts.diffevent(event);};
    
    if (window.addExpressionListener( this.diffhandler , this.diff))
        this.diffset=true;
    else
       console.log('AddExpressionListener diff no regist');
   
   this.kphandler = function(){ts.kpevent(event);};
   
   if (this.kp.constructor == String && window.addExpressionListener( this.kphandler , this.kp)){
        this.kpset=this.kp;this.kp=0;}
    
   this.kihandler = function(){ts.kievent(event);};
   
   if (this.ki.constructor == String && window.addExpressionListener( this.kihandler , this.ki)){
        this.kiset=this.ki;this.ki=0;} 
    
   this.kdhandler = function(){ts.kdevent(event);};
   
   if (this.kd.constructor == String && window.addExpressionListener( this.kdhandler , this.kd)){
        this.kdset=this.kd;this.kd=0;}       

}


simulator.regulator.prototype.detach = function(){
    if (this.autohandler && this.autoset)
        window.removeExpressionListener( this.autohandler);
    if (this.diffhandler && this.diffset)
        window.removeExpressionListener( this.diffhandler);    
    if (this.kphandler && this.kpset)
        window.removeExpressionListener( this.kphandler);
    if (this.kihandler && this.kiset)
        window.removeExpressionListener( this.kihandler);
    if (this.kdhandler && this.kdset)
        window.removeExpressionListener( this.kdhandler);      
}

simulator.regulator.prototype.autoevent = function(event){
    if (event.expression==this.auto){
        this.autostate = event.value; 
        if (!event.value){
            this.K = 0;
            this.I = 0;
            this.D = 0;
            this.olddiff=undefined;
        }
    }       
}

simulator.regulator.prototype.kpevent = function(event){
    if (event.expression==this.kpset){
        this.kp = event.value; 
        console.log('kp:',this.kp);
    }       
}

simulator.regulator.prototype.kievent = function(event){
    if (event.expression==this.kiset){
        this.ki = event.value; 
        console.log('ki:',this.ki);
    }       
}

simulator.regulator.prototype.kdevent = function(event){
    if (event.expression==this.kdset){
        this.kd = event.value; 
        console.log('kd:',this.kd);
    }       
}

simulator.regulator.prototype.diffevent = function(event){
    if (event.expression==this.diff){
        var ts = this;
        this.K = this.K + this.kp * (event.value - (this.kplast===undefined ? 0 : this.kplast));
        this.error = event.value;
   
        this.kplast = event.value;
        
        //console.log('proportial ',event.value, this.K );
        
        //if (this.K)
        //setTimeout( function() {/*console.log('add',ts.K * 100)*/;ts.actuator.spdiff(ts.K * 100);} , 1);

    }
}

simulator.regulator.prototype.delt = function(){
     var rslt = (this.K+this.I+ this.D);
     //console.log('p : ', this.K, 'i : '  ,this.I,  'd :', this.D , 'sum' ,  rslt);
     return (rslt<-1) ? - 1 : ((rslt>1) ? 1 : rslt)
}

simulator.regulator.prototype.execute = function(){
    if (this.autostate && this.actuator){
        var ts = this;
        var tmp = new Date();
        var curtime = tmp.getTime() + 0;
        var difftime = curtime - this.lasttime;
        var difftime_d = curtime - this.perflasttime;
        if (this.lasttime && this.error){         
            this.I =  this.kp * (this.error * (difftime)) / (this.ki ? this.ki : Infinity) / 1000;}
        
        if (this.lasttime && (this.error ||this.lasttime || this.perflasterror)) {
            if (this.lasttime && this.perflasttime){
                this.D = this.kp * (this.error - 2 * this.lasterror +  this.perflasterror) / (difftime_d ? difftime_d : Infinity) * this.kd * 1000;}
            else{
                if (this.lasttime)
                    this.D = this.kp * (this.error - this.lasterror) / (difftime ? difftime : Infinity) * this.kd * 1000;
                else
                    this.D = 0;
            }
        }
        
        this.perflasttime = this.lasttime;
        this.lasttime = curtime + 0 ;
        
        this.perflasterror = this.lasterror;
        this.lasterror = this.error ;
        
        //console.log('integral ',this.error, difftime, this.I );
        console.log(this.K, this.I, this.D );
        
        var d_and_i_and_k = this.I + this.D + this.K;
        
        if (d_and_i_and_k)
        ts.actuator.spdiff(d_and_i_and_k * 100);;
     
        this.K=0;
        
    }
    if (this.actuator){
       this.actuator.execute(); 
    }
}