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
     //alert('execute'); 
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
 
// simulator.actuator

simulator.actuator  = function(pos, sp, tick){
    this.pos= pos;
    this.sp=sp;
    this.tick=tick ? tick : 0.05;
    this.enable=true;
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
   
    

        
    
    this.kp= kp===undefined ? 4.5 : kp;
    this.ki= ki===undefined ? 0.5 : ki;
    this.kd= kd===undefined ? 1.5 : kd;
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
}


simulator.regulator.prototype.detach = function(){
    if (this.autohandler && this.autoset)
        window.removeExpressionListener( this.autohandler);
    if (this.diffhandler && this.diffset)
        window.removeExpressionListener( this.diffhandler);    
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

simulator.regulator.prototype.diffevent = function(event){
    if (event.expression==this.diff){
        
        this.K = this.kp * event.value;
        
        var newI = this.I + ((event.value) * this.ki) / 10;
        //console.log('newI ',newI);
        this.I = ((newI>-1) && (newI<1)) ? newI : this.I ;
        
        if (this.olddiff===undefined){
            this.olddiff=event.value;
        }
        else{
            var newD =  (this.olddiff-event.value) * this.kd /10 ;
            this.D =  ((newD>-1) && (newD<1)) ? newD : this.D ;
            this.olddiff=event.value;
        }
        console.log(this.K,this.I,this.D );
    }
}

simulator.regulator.prototype.delt = function(){
     var rslt = (this.K+this.I);
     return (rslt<-1) ? - 1 : ((rslt>1) ? 1 : rslt)
}

simulator.regulator.prototype.execute = function(){
    if (this.autostate && this.actuator){
        //console.log('delt',this.delt());
        this.actuator.spdiff(this.delt()/5);
    }
    if (this.actuator){
       this.actuator.execute(); 
    }
}