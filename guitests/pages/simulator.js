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
    //alert(' (abs(' + this.pos + ' - '+ this.sp + ') < ' + this.tick + ') ? (' + this.pos + ' @ (' + this.pos + ' + ((' + this.sp + '-' + this.pos + ')<0 ? (- ' + this.tick + ') : ('+ this.tick + ')  ))) : 0');
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
   
    
  
    this.kp= kp===undefined ? 4.8 : kp;
    this.ki= ki===undefined ? 2.0 : ki;
    this.kd= kd===undefined ? 20 : kd;
    this.tick= tick;
    
   
    this.possp=possp; 
    this.auto=auto;    
    this.tick=tick ? tick : 1;
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
        this.K = this.kp * (event.value - (this.kplast===undefined ? 0 : this.kplast));
        this.error = event.value;
   
        this.kplast = event.value;

        //console.log('proportial ',event.value, this.K );
        
        if (this.K)
        setTimeout( function() {/*console.log('add',ts.K * 100)*/;ts.actuator.spdiff(ts.K * 100);} , 1);

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
                this.D = this.kp * (this.error - 2 * this.lasterror +  this.perflasterror) / (difftime_d ? difftime_d : Infinity) * this.kd;}
            else{
                if (this.lasttime)
                    this.D = this.kp * (this.error - this.lasterror) / (difftime ? difftime : Infinity) * this.kd;
                else
                    this.D = 0;
            }
        }
        
        this.perflasttime = this.lasttime;
        this.lasttime = curtime + 0 ;
        
        this.perflasterror = this.lasterror;
        this.lasterror = this.error ;
        
        //console.log('integral ',this.error, difftime, this.I );
        console.log('diff ',this.error, difftime_d, this.D );
        
        var d_and_i = this.I + this.D;
        
        if (d_and_i)
        setTimeout( function() {/*console.log( tmp , 'add integral_and_diff', d_and_i * 100);*/ts.actuator.spdiff(d_and_i * 100);} , 1);
        
    }
    if (this.actuator){
       this.actuator.execute(); 
    }
}