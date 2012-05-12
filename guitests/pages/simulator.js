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
    
    window.$$((this.tag + ' @= ' + this.start).toString())
}


simulator.initializer.prototype.detach = function(){
    if (this.valid && (this.stop || this.stop==0)){
       window.$$((this.tag + ' @= ' + this.stop).toString());}
}

simulator.initializer.prototype.execute = function(){
     //alert('execute'); 
}


// casevalue

/*simulator.valueobserver = function(tag ,start , source ,stop){
  this.tag = tag;
  if (source){
      this.valid = true;
      this.source = source;
  }
  if (start)
        this.start = start;
  if (stop)
        this.stop = stop;    
  if (this.valid){
      this.atach();
  }     
}

simulator.valueobserver.prototype.atach = function(){
    if (this.valid && this.stop)
       $$(this.tag + ' @= ' + this.start);
}


simulator.valueobserver.prototype.detach = function(){
    if (this.valid && this.stop)
       $$(this.tag + ' @= ' + this.stop)
}

simulator.valueobserver.prototype.execute = function(){
    $$(this.tag + ' @= ' + this.source);
}*/
